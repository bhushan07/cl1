import numpy as np
import cv2
import math

def ret_code(angle):
  if(angle>=-22 and angle<=22):
      return 0
  elif(angle>=22 and angle<=67):
      return 7
  elif(angle>=67 and angle<=112):
      return 6
  elif(angle>=112 and angle<=157):
      return 5
  elif(angle>=-157 and angle<=-112):
      return 3
  elif(angle>=-112 and angle<=-67):
      return 2
  elif(angle>=-67 and angle<=-22):
      return 1
  else:
      return 4



def chain_codes(approx):
    for i in range(len(approx)-1):
      pnta=approx[i+1]; pntpa=approx[i]
      pnt=pnta[0];      pntp=pntpa[0]
      x=pnt[0];         px=pntp[0]
      y=pnt[1];         py=pntp[1]
      print str(ret_code(math.degrees(math.atan2((y-py),(x-px)))))+"  ,  ",

    lastpnt=approx[len(approx)-1]; firstpnt=approx[0]
    lp=lastpnt[0]; fp=firstpnt[0]
    lx=lp[0];fx=fp[0];
    ly=lp[1];fy=fp[1];
    print str(ret_code(math.degrees(math.atan2((fy-ly),(fx-lx)))))   
 
img = cv2.imread('shapes2.png')
imgray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
ret,thresh = cv2.threshold(imgray,127,255,0)
contours, hierarchy = cv2.findContours(thresh,cv2.RETR_LIST,cv2.CHAIN_APPROX_SIMPLE)

#cv2.drawContours(img,contours,(255,0,0),0,1,3)
cv2.drawContours(img, contours, -1, (0,0,255), 3)


for i in range(len(contours)):
  print "Countour Number"+str(i+1)
  cnt=contours[i]
  epsilon= 0.01*cv2.arcLength(cnt,True)
  
  approx=cv2.approxPolyDP(cnt,epsilon,True)
  if len(approx)==3:
     cv2.drawContours(img, [approx], 0, (255,0,0), 3)
  elif len(approx)==4:
     cv2.drawContours(img, [approx], 0, (0,0,255), 3)
  print approx
  print "Chain Codes for countour are   ",
  chain_codes(approx)
  print "  "
  M=cv2.moments(cnt)
  H=cv2.HuMoments(M)
  print "Hu Moments for contour are:  "
  print H
  print cv2.contourArea(cnt)


cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()