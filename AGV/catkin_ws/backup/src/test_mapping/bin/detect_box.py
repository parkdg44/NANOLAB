import cv2
import os
import numpy as np
import time
import v4l2

video = cv2.VideoCapture("/dev/video1")

key = 0
while True:
    
    if key == 27: break
    
    start = time.time()  
    # 시작 시간 저장

    #image =  cv2.imread("/home/park/python/detect_box/2Ho.png", cv2.IMREAD_COLOR)
    _, image = video.read()
    image = cv2.cvtColor(image,cv2.COLOR_BGR2HSV)
    image = cv2.resize(image,(800,600))

    image_H, image_S, image_V = cv2.split(image) 

    bin_H_min = cv2.threshold(image_H,70,255,cv2.THRESH_BINARY)
    bin_H_max = cv2.threshold(image_H,100,255,cv2.THRESH_BINARY_INV)
    bin_S_min = cv2.threshold(image_S,0,255,cv2.THRESH_BINARY)
    bin_S_max = cv2.threshold(image_S,30,255,cv2.THRESH_BINARY_INV)
    bin_V_min = cv2.threshold(image_V,150,255,cv2.THRESH_BINARY)
    bin_V_max = cv2.threshold(image_V,255,255,cv2.THRESH_BINARY_INV)

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
    if len(label_sort) == 0: continue
    lab_biggest = label_sort[len(label_sort)-1][1]

    roi_start = (lab_stats[lab_biggest][0],lab_stats[lab_biggest][1])
    roi_length = lab_stats[lab_biggest][2]
    roi_height = lab_stats[lab_biggest][3]
    #print(roi_start)
    #roi_length = abs(roi_max[0]-roi_min[0])
    #roi_height = abs(roi_max[1]-roi_min[1])

    #lab = img_labeled[roi_min[1]:roi_max[1]][roi_max[0]:roi_min[0]]
    offset = 0
    lab = (img_labeled[roi_start[1]-offset:roi_start[1]+roi_height+offset,
                    roi_start[0]-offset:roi_start[0]+roi_length+offset]).copy()
    roi = (image[roi_start[1]-offset:roi_start[1]+roi_height+offset,
                    roi_start[0]-offset:roi_start[0]+roi_length+offset]).copy()

    center = (roi_start[0]+roi_length / 2, roi_start[1]+roi_height/2)
    
    lab[lab==lab_biggest] = 255
    # 파이썬 행렬 조건식 처리를 이용한 방법 (처리속도 UP)

    '''
    for i in range(len(lab)-1):
        for j in range(len(lab[1])-1):
            if lab[i][j] == lab_biggest:
                lab[i][j] = 255
            else:
                lab[i][j] = 0
    '''
    # 1x1 mask를 이동시키면서 변환하는 방법

    lab = cv2.convertScaleAbs(lab)

    '''
    dst = cv2.cornerHarris(lab, 5, 5, 0.09)

    roi[dst>0.01*dst.max()]=[255,255,255]

    a = 0.01*dst.max()
    x = []; y = []

    for i in range(len(dst)-1):
        for j in range(len(dst[1])-1):
            if dst[i][j] > a:
                x.append(j)

    box_dist = max(x) - min(x)

    if (box_dist >= 500) and (box_dist <= 600) : print("2호 박스")
    elif (box_dist >= 700) and (box_dist <= 800) : print("3호 박스")
    else : print("Detect Nothing!")
    '''
    # Harris Corner Detection을 이용한 방식
    if center[1] >= 400 and (roi_height >= 280) : 
        box_dist = roi_length
        if (box_dist >= 450) and (box_dist <= 620) : print("2호 박스")
        elif (box_dist >= 700) and (box_dist <= 800) : print("3호 박스")
        else : print("Detect Nothing!")
    
    else :
        box_error = 400 - center[0]
        print(center[0])
        if box_error >= 50 : print("GO LEFT!")
        elif box_error < -50 : print("GO RIGHT!")
        else : print("GO STRAIGHT!")

    # ROI의 X 길이를 이용한 방식

    #cv2.imshow("result",lab)
    ch = cv2.waitKey(10)
    if ch != -1 : key = ch
    #cv2.imshow("result2",roi)
    #print("time : {}".format(time.time() - start))  # 현재시각 - 시작시간 = 실행 시간

    #k = cv2.waitKey(0)
    #if k == 27: break
    # esc key
        
cv2.destroyAllWindows()
# H 18     S 64, 67     V 204, 199