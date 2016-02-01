#!/usr/bin/env python

import rospy 
from sensor_msgs.msg import LaserScan
import math
import array
import numpy as np

PI = 3.14

if __name__ == '__main__':
	rospy.init_node("lidar_line_sim")
	rate = rospy.Rate(0.5)
	line_publisher = rospy.Publisher("/lidar_line_sim",LaserScan,queue_size=1000)
	scan = LaserScan()
	range_data = []
	k = 0;
	angles= np.linspace(-1.57,1.57,18)
	for i in range(0,len(angles)):
		range_data.append(1/math.cos(angles[i]))
	scan.header.frame_id = "laser_frame"
	scan.angle_min = -1.57;
	scan.angle_max = 1.57;
	scan.range_min = 0;
	scan.range_max = 20;
	scan.angle_increment = 10*PI/180;
	scan.ranges = range_data;
	while not rospy.is_shutdown():
		scan.header.stamp = rospy.get_rostime()
		line_publisher.publish(scan)
		rate.sleep()
