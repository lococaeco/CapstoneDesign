import rospy
from Total_msgs.msg import Control

from gamepad_controller import ShanWanGamepad


if __name__ == '__main__':
    rospy.init_node('serial_control_test_node', anonymous=True)
    pub = rospy.Publisher('control_msg', Control, queue_size=1)

    shanwan_gamepad = ShanWanGamepad()

    msg = Control()
    pre_throttle = None
    pre_steering = None

    try:
        while not rospy.is_shutdown():
            gamepad_input = shanwan_gamepad.read_data()

            LV = gamepad_input.analog_stick_left.y
            RH = gamepad_input.analog_stick_right.y

            LV = 0.0 if -0.05 < LV < 0.05 else LV
            RH = 0.0 if -0.05 < RH < 0.05 else RH

            throttle = 0
            steering = 0

            if LV > 0:
                throttle += int(LV * 100)
            elif LV < 0:
                throttle += int(LV * 100)

            if RH > 0:
                steering += int(RH * 100) * -1
            elif RH < 0:
                steering += int(RH * 100) * -1

            if throttle != pre_throttle or steering != pre_steering:
                msg.s16_throttle = throttle
                msg.s16_steering = steering
                pub.publish(msg)
                
                pre_throttle = throttle
                pre_steering = steering

    except rospy.ROSInterruptException:
        pass
