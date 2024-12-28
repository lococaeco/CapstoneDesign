import serial
import time

from gamepad_controller import ShanWanGamepad


if __name__ == '__main__':
    arduino_port = '/dev/ttyACM0'
    baud_rate = 115200
    arduino = serial.Serial(arduino_port, baud_rate)
    time.sleep(1)

    shanwan_gamepad = ShanWanGamepad()

    pre_msg = 'b00m00\n'

    try:
        while True:
            gamepad_input = shanwan_gamepad.read_data()

            LV = gamepad_input.analog_stick_left.y
            RH = gamepad_input.analog_stick_right.y

            LV = 0.0 if -0.05 < LV < 0.05 else LV
            RH = 0.0 if -0.05 < RH < 0.05 else RH

            msg = ''

            if LV > 0:
                msg += 'f' + '{:.2f}'.format(LV)[-2:]
            elif LV < 0:
                msg += 'r' + '{:.2f}'.format(LV)[-2:]
            else:
                msg = 'b00'

            if RH > 0:
                msg += 'p' + '{:.2f}'.format(RH)[-2:]
            elif RH < 0:
                msg += 'n' + '{:.2f}'.format(RH)[-2:]
            else:
                msg += 'm00'

            msg += '\n'

            if pre_msg != msg:
                arduino.write(msg.encode())
                pre_msg = msg

    finally:
        arduino.write('b00m00\n'.encode())
        arduino.close()
