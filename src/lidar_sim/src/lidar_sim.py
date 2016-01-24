#!/usr/bin/env python
import rospy
from sensor_msgs.msg import LaserScan 
import serial
import sys
import time

data_size = 5;


def pub_scan():
 while(hex(int(check_data,16)) == hex(78)):
  data_port.write("\x9f")
  check_data = data_port.read(2)
 while not rospy.is_shutdown():
    for i in range(1,data_size+1):
  	 data = data_port.read()
  	 rospy.loginfo(data) 
 
 

if __name__ == '__main__':
 rospy.init_node("lidar_sim")
 rate = rospy.Rate(0.5)
 scan_publisher = rospy.Publisher("/lidar_scan",LaserScan, queue_size=1000)
 data_port = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
 )
 pub_scan()



  