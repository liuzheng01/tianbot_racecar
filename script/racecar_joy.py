#!/usr/bin/env python
import rospy
import time
from  sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

twist = Twist()

def callback(data):

	pub = rospy.Publisher('~/car/cmd_vel', Twist, queue_size=5)

	twist.linear.x = 1500
	twist.angular.z = 90

	if data.buttons[4]==1:
		twist.linear.x = int(1500 + data.axes[1] * 500)

	if data.buttons[5]==1:
		twist.angular.z = int(90 + 30 * data.axes[3])

        pub.publish(twist)

def joystick_controller():
	rospy.init_node('racecar_joy',anonymous=True)
	rospy.loginfo('start!')
	rospy.Subscriber('/joy', Joy, callback)
	rospy.spin()

if __name__ == '__main__':
	joystick_controller()
