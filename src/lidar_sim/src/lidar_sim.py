#!/usr/bin/env python
import rospy
from sensor_msgs.msg import LaserScan 
import serial
import sys
import time
import numpy


def pub_scan():
 data_port.write("\x9f")
 #if(hex(int(check_data,16)) == hex(78)):
 range_data = data_port.readline()
 range_data = data_port.readline()
 while not rospy.is_shutdown():
    range_data = data_port.readline()
    range_data = range_data.rstrip(",4F\n")                                                                                                                          
    range_data = range_data.lstrip("4E ,")
    rospy.loginfo(range_data)
    range_data = map(float, range_data.split(','))
    scan_msg.header.stamp = rospy.get_rostime()
    scan_msg.ranges = range_data;
    scan_publisher.publish(scan_msg)
    rospy.loginfo(range_data)

if __name__ == '__main__':
 rospy.init_node("lidar_sim")
 rate = rospy.Rate(0.5)
 scan_publisher = rospy.Publisher("/lidar_scan",LaserScan, queue_size=1000)
 scan_msg = LaserScan()
 scan_msg.header.frame_id = "laser_frame"
 scan_msg.angle_min = 0;
 scan_msg.angle_max = 180;
 scan_msg.angle_increment = 10;
 scan_msg.range_min = 0;
 scan_msg.range_max = 80;
 data_port = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
 )
 pub_scan()



  