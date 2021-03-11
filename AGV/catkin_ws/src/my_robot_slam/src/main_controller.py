#! /usr/bin/env python
import rospy
import cv2
import cv_bridge
import numpy as np
from test_mapping.msg import Cmd_val
from test_mapping.msg import PSD
from std_msgs.msg import String
from std_msgs.msg import Int16

H_range = [140,180]
S_range = [0,50]
V_range = [150,220]

deep_sign = [0, 0, 0, 0]
# deep_sign[0] : CJ
# deep_sign[1] : post
# deep_sign[2] : Seoul
# deep_sign[3] : Incheon

isReady = False
cmd_val = Cmd_val()


flag_gripper = 0
# flag_gripper -> 0 : Stop 
#                 1 : grip & raise the box
#                 2 : put down the box
PSD_L = 0.0
PSD_R = 0.0

def detect_box(video):
    global H_range,S_range,V_range
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

    kernel = np.ones((12, 12), np.uint8)
    result = cv2.morphologyEx(bin_image, cv2.MORPH_CLOSE, kernel)
    kernel = np.ones((4, 4), np.uint8)
    result = cv2.erode(result, kernel, iterations = 1)

    n_labels, img_labeled, lab_stats, _ = cv2.connectedComponentsWithStats(result,labels=3,connectivity=8,ltype=cv2.CV_16U)

    cv2.imshow("RESULT",result)
    cv2.imshow("IMAGE",image)
    ch = cv2.waitKey(10) 
    if ch != -1 : key = ch

    label = []
    label_dic = {}
    for i in range(n_labels):
        if i == 0 : continue
        if lab_stats[i][4] >= 10000 :
            label_dic[lab_stats[i][4]] = i

    label_sort = label_dic.items()
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

    if center[1] >= 400 and (roi_height >= 280) : 
        box_dist = roi_length
        cmd_val.cmd_L = 0
        cmd_val.cmd_R = 0
        cmd_val.isControl = False
        if (box_dist >= 450) and (box_dist <= 620) : print("2호 박스")
        elif (box_dist >= 700) and (box_dist <= 800) : print("3호 박스")
        else : print("Detect Nothing!")
    
    else :
        box_error = 400 - center[0]
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
        else : 
            cmd_val.cmd_L = 20
            cmd_val.cmd_R = 20
            cmd_val.isControl = True
            print("go STRAGHT!")

def deep_callback(deep_data):
    global deep_sign,isReady
    deep_string = deep_data.data

    if (isReady == True):    
        if (deep_string=='RED'):
            deep_sign[0]=1
        elif (deep_string=='Green'):
            deep_sign[1]=1
        elif (deep_string=='StraightLeft'):
            deep_sign[2]=1
        elif (deep_string=='Left'):
            deep_sign[3]=1

def PSD_callback(PSD_data):
    global PSD_L,PSD_R
    PSD_L = PSD_data.PSD_L
    PSD_R = PSD_data.PSD_R    

step_main = 0
# step_maim -> 0 : Find box
#              1 : move robot for setting box to center
#              2 : detect rogo and location
#              3 : pick up the box
#              4 : go to goal


if __name__ == '__main__':
    rospy.init_node("main_controller")

    pub_cmd = rospy.Publisher("cmd_val_controller",Cmd_val,queue_size=1)
    pub_grip = rospy.Publisher("flag_gripper",Int16,queue_size=1)

    rospy.Subscriber("deeplearning",String,deep_callback)
    rospy.Subscriber("PSD_distance",PSD,PSD_callback)

    cam = cv2.VideoCapture(1)
    while True:
        try:
            if(step_main == 0):
                detect_box(cam)
                


            #detect_box(cam)
            #flag_gripper = 1
            #pub_cmd.publish(cmd_val)
            #pub_grip.publish(Int16(flag_gripper))
    
        except (KeyboardInterrupt, RuntimeError):
            cv2.destroyAllWindows()
            quit()