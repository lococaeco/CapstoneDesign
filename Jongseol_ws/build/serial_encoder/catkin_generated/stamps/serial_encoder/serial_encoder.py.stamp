import rospy
from Total_msgs.msg import Encoder

import serial

if __name__ == '__main__':
    rospy.init_node('serial_encoder_node', anonymous=True)
    pub = rospy.Publisher('encoder_msg', Encoder, queue_size=1)

    port = '/dev/ttyACM0'
    baudrate = 115200
    arduino = serial.Serial(port, baudrate)

    msg = Encoder()

    try:
        while True:
            if arduino.in_waiting > 0:
                message = arduino.readline().decode('utf-8').strip()
                right, left = map(int, message.split('_'))
                msg.s16_RightWheelRPM = right
                msg.s16_LeftWheelRPM = left
                pub.publish(msg)

    except KeyboardInterrupt:

        pass

    finally:
        arduino.close()
