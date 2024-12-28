import rospy
from Total_msgs.msg import Control

import serial


arduino_port = '/dev/ttyACM1'
baud_rate = 115200
arduino = serial.Serial(arduino_port, baud_rate)

pre_string = 'b00m00\n'


def msgCallback(msg):
    global arduino, pre_string

    string = ''

    if msg.s16_throttle > 0:
        string += 'f' + str(abs(msg.s16_throttle)).zfill(2)[-2:]
    elif msg.s16_throttle < 0:
        string += 'r' + str(abs(msg.s16_throttle)).zfill(2)[-2:]
    else:
        string = 'b00'

    if msg.s16_steering > 0:
        string += 'n' + str(abs(msg.s16_steering)).zfill(2)[-2:]
    elif msg.s16_steering < 0:
        string += 'p' + str(abs(msg.s16_steering)).zfill(2)[-2:]
    else:
        string += 'm00'

    string += '\n'

    if pre_string != string:
        arduino.write(string.encode())
        pre_string = string

        print(string)


if __name__ == '__main__':
    rospy.init_node('serial_control_node', anonymous=True)
    rospy.Subscriber("control_msg", Control, msgCallback)

    try:
        rospy.spin()

    except KeyboardInterrupt:
        pass

    finally:
        arduino.write('b00m00\n'.encode())
        arduino.close()
