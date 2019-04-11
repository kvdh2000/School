import numpy as np
import cv2
import math



def op11():
    img = cv2.imread('D:\GitHub\School\P2.4\CV\opencv-logo-white.png')
    cv2.imshow('logo', img)
    k = cv2.waitKey(0)
    print k
    cv2.destroyAllWindows()

def op12():
    cap = cv2.VideoCapture(0)
    while(True):
        ret, frame = cap.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow('frame', gray)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()

def op13():
    cap = cv2.VideoCapture(0)
    while(True):
        _,frame = cap.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        lower_blue = np.array([110,50,50])
        upper_blue = np.array([130,255,255])
        lower_red = np.array([0,50,50])
        upper_red = np.array([20,255,255])
        lower_green = np.array([50,50,50])
        upper_green = np.array([70,255,255])

        mask1 = cv2.inRange(hsv, lower_blue, upper_blue)
        mask2 = cv2.inRange(hsv, lower_red, upper_red)
        mask3 = cv2.inRange(hsv, lower_green, upper_green)
        res1 = cv2.bitwise_and(frame,frame, mask = mask1)
        res2 = cv2.bitwise_and(frame,frame, mask = mask2)
        res3 = cv2.bitwise_and(frame,frame, mask = mask3)

        cv2.imshow('res1', res1)
        cv2.imshow('res2', res2)
        cv2.imshow('res3', res3)
                
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()

def op14():
    img = cv2.imread('D:\GitHub\School\P2.4\CV\opencv-logo-white.png')
    cv2.imshow('logo', img)

    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    lower_blue = np.array([110,50,50])
    upper_blue = np.array([130,255,255])
    lower_red = np.array([0,50,50])
    upper_red = np.array([20,255,255])
    lower_green = np.array([50,50,50])
    upper_green = np.array([70,255,255])

    mask1 = cv2.inRange(hsv, lower_blue, upper_blue)
    mask2 = cv2.inRange(hsv, lower_red, upper_red)
    mask3 = cv2.inRange(hsv, lower_green, upper_green)
    res1 = cv2.bitwise_and(img,img, mask = mask1)
    res2 = cv2.bitwise_and(img,img, mask = mask2)
    res3 = cv2.bitwise_and(img,img, mask = mask3)

    cv2.imshow('res1', res1)
    cv2.imshow('res2', res2)
    cv2.imshow('res3', res3)

    k = cv2.waitKey(0)
    print k
    cv2.destroyAllWindows()

def op21():
    img = cv2.imread('D:\GitHub\School\P2.4\CV\opencv-logo-white.png')

    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    lower_red = np.array([0,50,50])
    upper_red = np.array([20,255,255])
    mask2 = cv2.inRange(hsv, lower_red, upper_red)
    
    contours, hierarchy = cv2.findContours(mask2,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    
    
    cnt=contours[0]
    M = cv2.moments(cnt)
    cX = int(M['m10']/M['m00'])
    cY = int(M['m01']/M['m00'])
    cv2.circle(img, (cX, cY), 5, (255, 255, 255), -1) 
    cnt = cv2.convexHull(cnt)
    
    cv2.drawContours(img, [cnt], -1, (0,255,0), 3)
    cv2.imshow('logo',img)
    
    k = cv2.waitKey(0)
    print k
    cv2.destroyAllWindows()

def op31():
    img = cv2.imread('D:/GitHub/School/P2.4/CV/bouten_moeren.jpg')
    
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray,(5,5),0)
    ret,th = cv2.threshold(gray,180,255,cv2.THRESH_BINARY_INV)
    contours, hierarchy = cv2.findContours(th,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    cnt = contours[0]
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area > 100:
            cv2.drawContours(img, [cnt], -1, (0,255,255), 3)

    cv2.imshow('img',img)
    cv2.waitKey(0)
    print k
    cv2.destroyAllWindows()

def op41():
    img = cv2.imread('D:/GitHub/School/P2.4/CV/bouten_moeren.jpg')
    
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray,(5,5),0)
    ret,th = cv2.threshold(gray,180,255,cv2.THRESH_BINARY_INV)
    contours, hierarchy = cv2.findContours(th,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    hierarchy = hierarchy[0]

    for cnr in range(len(contours)):
        cnt = contours[cnr]
        area = cv2.contourArea(cnt)
        perimeter = cv2.arcLength(cnt, True)
        factor = 4 * math.pi * area / perimeter**2

        holes = 0
        child = hierarchy[cnr][2]
        while child >= 0:
            holes += cv2.contourArea(contours[child])
            child = hierarchy[child][0]
        print area, holes, factor
        if area > 3500:
            cv2.drawContours(img, [cnt], -1, (0,255,255), 3)
        elif factor < 0.8:
            cv2.drawContours(img, [cnt], -1, (255,0,0), 3)
        elif holes > 100:
            cv2.drawContours(img, [cnt], -1, (0,255,0),3)
        elif area >600: 
            cv2.drawContours(img, [cnt], -1, (0,0,255),3)
            
    cv2.imshow('img',img)
    cv2.waitKey(0)
    print k
    cv2.destroyAllWindows()

def op51():
    img = cv2.imread('D:/GitHub/School/P2.4/CV/dobbelstenen.png')
    
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    ret, th = cv2.threshold(gray,10,255,cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(th,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    
    hierarchy = hierarchy[0]
    
    diceRolls = []
    print len(contours)
    
    for cnr in range(len(contours)):
        x,y,w,h = cv2.boundingRect(contours[cnr])
        die = gray[y:y+h, x:x+w]
        
        ret2, th2 = cv2.threshold(die,200,255,cv2.THRESH_BINARY)
        contours2, hierarchy2 = cv2.findContours(th2,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

        myEyes = 0
        
        for cnr2 in range(len(contours2)):
            cnt2 = contours2[cnr2]
            area = cv2.contourArea(cnt2)
            perimeter = cv2.arcLength(cnt2, True)
            if perimeter > 0:
                factor = 4 * math.pi * area / perimeter**2
                if area > 100:
                    if factor > 0.5 :
                         myEyes += 1
                         
        diceRolls.append(myEyes)
        diceRolls.sort()
        print diceRolls


    cv2.imshow('img',img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    
