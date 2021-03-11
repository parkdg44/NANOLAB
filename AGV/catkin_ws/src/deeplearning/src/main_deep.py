#! /usr/bin/env python3

import cv_bridge
import cv2
#from darkflow.net.build import TFNet
import numpy as np
import time
#import tensorflow as tf
import rospy
import rospkg
import os
import subprocess

from test_mapping.msg import Cmd_val
from test_mapping.msg import PSD
from std_msgs.msg import String
from std_msgs.msg import Int16

from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from actionlib import simple_action_client

######################################## initialization #############################
# config = tf.ConfigProto()
# config.gpu_options.allow_growth = True
# session = tf.Session(config=config)

rospack = rospkg.RosPack()
rospack.list()
path = rospack.get_path('deeplearning')
os.chdir(path)

# session = tf.Session(config=config)

options = {
    'model': 'cfg/KyooLee.cfg',
    'load': 29000,
    'threshold': 0.3,
    'gpu': 0.9
}


######################################## Camera ####################################
### for reference, the output of v4l2-ctl -d /dev/video1 -l (helpful for min/max/defaults)
#                     brightness (int)    : min=0 max=255 step=1 default=128 value=128
#                       contrast (int)    : min=0 max=255 step=1 default=128 value=128
#                     saturation (int)    : min=0 max=255 step=1 default=128 value=128
# white_balance_temperature_auto (bool)   : default=1 value=1
#                           gain (int)    : min=0 max=255 step=1 default=0 value=0
#           power_line_frequency (menu)   : min=0 max=2 default=2 value=2
#      white_balance_temperature (int)    : min=2000 max=6500 step=1 default=4000 value=2594 flags=inactive
#                      sharpness (int)    : min=0 max=255 step=1 default=128 value=128
#         backlight_compensation (int)    : min=0 max=1 step=1 default=0 value=0
#                  exposure_auto (menu)   : min=0 max=3 default=3 value=1
#              exposure_absolute (int)    : min=3 max=2047 step=1 default=250 value=333
#         exposure_auto_priority (bool)   : default=0 value=1
#                   pan_absolute (int)    : min=-36000 max=36000 step=3600 default=0 value=0
#                  tilt_absolute (int)    : min=-36000 max=36000 step=3600 default=0 value=0
#                 focus_absolute (int)    : min=0 max=250 step=5 default=0 value=125
#                     focus_auto (bool)   : default=1 value=0
#                  zoom_absolute (int)    : min=100 max=500 step=1 default=100 value=100

### I created a dict of the settings of interest
### note that if you have any auto settings on, e.g. focus_auto=1,
### it will complain when it goes to set focus_absolute, but I didn't have
### any issues other than the warning
cam_props = {'brightness': 128, 'contrast': 128, 'saturation': 128,
             'gain': 0, 'sharpness': 128, 'exposure_auto': 1,
             'exposure_absolute': 400, 'exposure_auto_priority': 0,
             'focus_auto': 1, 'white_balance_temperature_auto': 0, 'white_balance_temperature': 3900}

### go through and set each property; remember to change your video device if necessary~
### on my RPi, video0 is the usb webcam, but for my laptop the built-in one is 0 and the
### external usb cam is 1
'''
for key in cam_props:
    subprocess.call(['v4l2-ctl -d /dev/video1 -c {}={}'.format(key, str(cam_props[key]))],
                    shell=True)
'''
### uncomment to print out/verify the above settings took
# subprocess.call(['v4l2-ctl -d /dev/video1 -l'], shell=True)
  
### showing that I *think* one should only create the opencv capture object after these are set
### also remember to change the device number if necessary


######################################## Deep Learning #############################
deep_sign = {"CJ":0,    "Hyundai":0,
             "Post":0,  "Incheon":0,
             "Seoul":0, "Gwangju":0}

time_i = time.time()
logo_location = []

######################################## Detect Box ################################
H_range = [130,180]
S_range = [10,50]
V_range = [145,200]


######################################## Cmd_vel,PSD ################################
isReady = False
cmd_val = Cmd_val()

PSD_L = 30.0
PSD_R = 30.0    


######################################## Flags ################################
step_main = 1
# step_maim -> 0 : Find box & set the robot to center of box
#              1 : pick up the box
#              2 : detect rogo and location
#              3 : go to goal

flag_gripper = 0
# flag_gripper -> 0 : Stop 
#                 1 : grip & raise the box
#                 2 : put down the box


def detect_box(video):
    global H_range,S_range,V_range, PSD_L,PSD_R
    _, image = video.read()
    
    image = cv2.cvtColor(image,cv2.COLOR_BGR2HSV)
    image = cv2.resize(image,(800,600))

    image_H, image_S, image_V = cv2.split(image) 

    bin_H_min = cv2.threshold(image_H,H_range[0],255,cv2.THRESH_BINARY)
    bin_H_max = cv2.threshold(image_H,H_range[1],255,cv2.THRESH_BINARY_INV)
    bin_S_min = cv2.threshold(image_S,S_range[0],255,cv2.THRESH_BINARY)
    bin_S_max = cv2.threshold(image_S,S_range[1],255,cv2.THRESH_BINARY_INV)
    bin_V_min = cv2.threshold(image_V,V_range[0],255,cv2.THRESH_BINARY)
    bin_V_max = cv2.threshold(image_V,V_range[1],255,cv2.THRESH_BINARY_INV)

    bin_H = cv2.bitwise_and(bin_H_min[1],bin_H_max[1])
    bin_S = cv2.bitwise_and(bin_S_min[1],bin_S_max[1])
    bin_V = cv2.bitwise_and(bin_V_min[1],bin_V_max[1])

    bin_image = cv2.bitwise_and(bin_H,bin_V)
    bin_image = cv2.bitwise_and(bin_image,bin_S)

    kernel = np.ones((16, 16), np.uint8)
    result = cv2.morphologyEx(bin_image, cv2.MORPH_CLOSE, kernel)
    kernel = np.ones((6, 6), np.uint8)
    result = cv2.erode(result, kernel, iterations = 1)

    n_labels, img_labeled, lab_stats, _ = cv2.connectedComponentsWithStats(result,labels=3,connectivity=8,ltype=cv2.CV_16U)
    
    #cv2.imshow("IMAGE",image)
    cv2.imshow("RESULT",result)
    ch = cv2.waitKey(10) 
    if ch != -1 : key = ch

    label = []
    label_dic = {}
    for i in range(n_labels):
        if i == 0 : continue
        if lab_stats[i][4] >= 3000 :
            label_dic[lab_stats[i][4]] = i

    label_sort = list(label_dic.items())
    if len(label_sort) == 0: return
    lab_biggest = label_sort[len(label_sort)-1][1]

    roi_start = (lab_stats[lab_biggest][0],lab_stats[lab_biggest][1])
    roi_length = lab_stats[lab_biggest][2]
    roi_height = lab_stats[lab_biggest][3]

    offset = 0
    lab = (img_labeled[roi_start[1]-offset:roi_start[1]+roi_height+offset,
                    roi_start[0]-offset:roi_start[0]+roi_length+offset]).copy()
    roi = (image[roi_start[1]-offset:roi_start[1]+roi_height+offset,
                    roi_start[0]-offset:roi_start[0]+roi_length+offset]).copy()

    center = (roi_start[0]+roi_length / 2, roi_start[1]+roi_height/2)
    
    lab[lab==lab_biggest] = 255
    # 파이썬 행렬 조건식 처리를 이용한 방법 (처리속도 UP)

    lab = cv2.convertScaleAbs(lab)
    box_error = 400 - center[0]
    
    global step_main

    if ((PSD_L <= 7.0) and (PSD_R <= 7.0)):
        cmd_val.cmd_L = 0
        cmd_val.cmd_R = 0
        cmd_val.isControl = True
        step_main = 1
        print("Next step! (step : {})".format(step_main))
        cv2.destroyAllWindows()
    
    else :
        print(center[0])
        if box_error >= 50 : 
            cmd_val.cmd_L = 15
            cmd_val.cmd_R = 30
            cmd_val.isControl = True
            print("Turn LEFT!")
        elif box_error < -50 :
            cmd_val.cmd_L = 30
            cmd_val.cmd_R = 15
            cmd_val.isControl = True
            print("Turn RIGHT!")
        # elif (PSD_L <= 20.0) and (PSD_R <= 20.0) and (PSD_L - PSD_R <= -3.0):
        #     cmd_val.cmd_L = 15
        #     cmd_val.cmd_R = 30
        #     cmd_val.isControl = True
        #     print("Turn LEFT! (PSD)")
        # elif (PSD_L <= 20.0) and (PSD_R <= 20.0) and (PSD_L - PSD_R >= 3.0):
        #     cmd_val.cmd_L = 30
        #     cmd_val.cmd_R = 15
        #     cmd_val.isControl = True
        #     print("Turn RIGHT! (PSD)")
        else : 
            cmd_val.cmd_L = 20
            cmd_val.cmd_R = 20
            cmd_val.isControl = True
            print("go STRAGHT!")
'''
def detect_logo_location(capture):
    global deep_sign, step_main, logo_location
    stime = time.time()
    ret, frame = capture.read()
    
    if ret:
        if time_i>=0.4:
            #stime_eachF = time.time()            
            results = tfnet.return_predict(frame)
            for color, result in zip(colors, results):
                tl = (result['topleft']['x'], result['topleft']['y'])
                br = (result['bottomright']['x'], result['bottomright']['y'])
                
                center_x = int((tl[0]+br[0])/2)
                center_y = int((tl[1]+br[1])/2)
                # center_point

                label = result['label']
                # label

                confidence = result['confidence']
                text = '{}: {:.0f}%'.format(label, confidence * 100)
                frame = cv2.rectangle(frame, tl, br, color, 3)
                frame = cv2.putText(frame, text, tl, cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 3)
                
                if label != "Box":
                    deep_sign[label] = deep_sign[label] + 1
                #else:
                #    box_center = [center_x,center_y]
                
                if label[max(deep_sign)] >= 20:
                    logo_location.append[max(deep_sign)]
                    deep_sign.pop(max(deep_sign))
                    logo_location.append[max(deep_sign)]
                    
                    if ((logo_location[0] == "Seoul") or (logo_location[0] == "Incheon") or
                        (logo_location[0] == "Gwangju")):
                        logo_location.reverse()       
                    
                    
                    print("Next step! (step : {})".format(step_main))
                    print(logo_location)

                    step_main = 2
                    
                # logo_location[0] : logo
                # logo_location[1] : location
            cv2.imshow('Frame', frame)

            #print('FPS {:.1f}'.format(1 / (time.time() - stime)))
            #print('{}'.format(time.time() - stime_eachF))

        time_i = time_i + (time.time() - stime)
'''
def PSD_callback(PSD_data):
    global PSD_L,PSD_R
    PSD_L = PSD_data.PSD_L
    PSD_R = PSD_data.PSD_R


if __name__ == '__main__':
    rospy.init_node("main_controller")
    # tfnet = TFNet(options)
    colors = [tuple(255 * np.random.rand(3)) for _ in range(3)]
    cam = cv2.VideoCapture(1)
    cam.set(cv2.CAP_PROP_FRAME_WIDTH, 1080)
    cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

    pub_cmd = rospy.Publisher("cmd_val_controller",Cmd_val,queue_size=1)
    
    rospy.Subscriber("PSD_distance",PSD,PSD_callback)
    ac = simple_action_client.SimpleActionClient("move_base",MoveBaseAction)

    time_grip = 0

    while True:
        try:
            if(step_main == 0):
                detect_box(cam)
                pub_cmd.publish(cmd_val)

            elif (step_main == 1):
                #pub_grip.publish(flag_gripper)
                # cmd_val.isControl = False
                # pub_cmd.publish(cmd_val)
                # detect_logo_location(cam)
                logo_location = ["CJ","Seoul"]
                print(logo_location)
                step_main = 2

            elif (step_main == 2):
                if(PSD_L >= 14) and (PSD_R >= 14):
                    step_main = 3
                    
            elif (step_main == 3):
                ac.wait_for_server()
                goal = MoveBaseGoal()
                goal.target_pose.header.frame_id = "map"
                goal.target_pose.header.stamp = rospy.Time.now()
                goal.target_pose.pose.orientation.w = 1.0
            
                if(logo_location[0] == "CJ"):
                    goal.target_pose.pose.position.x = 15
                elif(logo_location[0] == "Hyundai"):
                    goal.target_pose.pose.position.x = 17
                elif(logo_location[0] == "Post"):
                    goal.target_pose.pose.position.x = 19
                
                if(logo_location[1] == "Incheon"):
                    goal.target_pose.pose.position.y = -0.35
                elif(logo_location[1] == "Seoul"):
                    goal.target_pose.pose.position.y = 0
                elif(logo_location[1] == "Gwangju"):
                    goal.target_pose.pose.position.y = 0.35

                ac.send_goal(goal)
                wait = ac.wait_for_result()
                isDone = False
                
                if not wait:
                    rospy.logerr("Action server not available!")
                    rospy.signal_shutdown("Action server not available!")
                else:
                    isDone = ac.get_result()
                
                if isDone:
                    print("Finish!")
                    step_main = 3
                    
        except (KeyboardInterrupt, RuntimeError):
            cv2.destroyAllWindows()
            quit()
