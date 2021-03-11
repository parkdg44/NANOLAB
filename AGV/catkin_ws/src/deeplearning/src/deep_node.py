#! /usr/bin/env python3

import cv_bridge
import cv2
from darkflow.net.build import TFNet
import numpy as np
import time
import tensorflow as tf
import rospy
import rospkg
import os
from test_mapping.msg import Cmd_val
from test_mapping.msg import PSD
from std_msgs.msg import String
from std_msgs.msg import Int16

config = tf.ConfigProto()
config.gpu_options.allow_growth = True
session = tf.Session(config=config)

rospack = rospkg.RosPack()
rospack.list()
path = rospack.get_path('deeplearning')
os.chdir(path)

session = tf.Session(config=config)

options = {
    'model': 'cfg/KyooLee.cfg',
    'load': 29000,
    'threshold': 0.3,
    'gpu': 0.9
}

tfnet = TFNet(options)
colors = [tuple(255 * np.random.rand(3)) for _ in range(3)]

capture = cv2.VideoCapture(1)
capture.set(cv2.CAP_PROP_FRAME_WIDTH, 1080)
capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
time_i = 0

rospy.init_node('deep_node', anonymous=True)
pub_deeplearning = rospy.Publisher('deep_msg', String, queue_size=30)

deep_msg = ""

while True:
    stime = time.time()
    ret, frame = capture.read()
    
    if ret:
        if time_i>=0.4:
            #stime_eachF = time.time()            
            results = tfnet.return_predict(frame)
            for color, result in zip(colors, results):
                tl = (result['topleft']['x'], result['topleft']['y'])
                br = (result['bottomright']['x'], result['bottomright']['y'])
                label = result['label']

                confidence = result['confidence']
                text = '{}: {:.0f}%'.format(label, confidence * 100)
                frame = cv2.rectangle(frame, tl, br, color, 3)
                mx = (tl[0]+br[0])/2
                my = (tl[1]+br[1])/2
                frame = cv2.putText(frame, text, tl, cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 3)
                if label != 'Box':
                    print(label)          
                if label == 'Box':
                    print(label,'Middle=',mx,',',my)
                    box_width=br[0]-tl[0]
                    box_height=br[1]-tl[1]
                    print('Box width,hieght = (%d,%d)'%(box_width,box_height))
                    center_x = int((tl[0]+br[0])/2)
                    center_y = int((tl[1]+br[1])/2)
                    #roi = frame[center_y-200:center_y+200, center_x-200:center_x+200]
                
                pub_deeplearning.publish(label)

            #cv2.imshow('ROI',roi)
            cv2.imshow('Frame', frame)
            #print('FPS {:.1f}'.format(1 / (time.time() - stime)))
            #print('{}'.format(time.time() - stime_eachF))

        time_i = time_i + (time.time() - stime)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

capture.release()
cv2.destroyAllWindows()
