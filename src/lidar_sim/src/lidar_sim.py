#!/usr/bin/env python
import rospy
from sensor_msgs.msg import LaserScan 
from std_msgs.msg import Bool
import serial
import sys
import time
import numpy


def pub_scan(generate_scan):
 if generate_scan:
  rospy.loginfo("Generating scan\n")
  data_port.write("\x9f")
  #if(hex(int(check_data,16)) == hex(78)):
  range_data = data_port.readline()
  range_data = range_data.rstrip(",4F\n")                                                                                                                          
  range_data = range_data.lstrip("4E ,")
  range_data = map(float, range_data.split(','))
  scan_msg.header.stamp = rospy.get_rostime()
  scan_msg.ranges = range_data;
  scan_publisher.publish(scan_msg)
  rospy.loginfo(range_data)
  range_data = data_port.readline()
  range_data = range_data.rstrip(",4F\n")                                                                                                                          
  range_data = range_data.lstrip("4E ,")
  range_data = map(float, range_data.split(','))
  scan_msg.header.stamp = rospy.get_rostime()
  range_data = range_data[::-1]
  scan_msg.ranges = range_data;
  scan_publisher.publish(scan_msg)
  rospy.loginfo(range_data)

if __name__ == '__main__':
 rospy.init_node("lidar_sim")
 rate = rospy.Rate(0.5)
 scan_publisher = rospy.Publisher("/lidar_scan",LaserScan, queue_size=1000)
 scan_trigger = rospy.Subscriber("/generate_scan",Bool,pub_scan)
 scan_msg = LaserScan()
 scan_msg.header.frame_id = "laser_frame"
 scan_msg.angle_min = 0;
 scan_msg.angle_max = 3.14;
 scan_msg.angle_increment = 0.01744;
 scan_msg.range_min = 0;
 scan_msg.range_max = 80;
 data_port = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
 )
 time.sleep(2)
 rospy.spin()


  