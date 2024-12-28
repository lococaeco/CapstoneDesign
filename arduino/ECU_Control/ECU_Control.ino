/*
    Brakes | Forward | Reverse
IN1 0      | 1       | 0
IN2 0      | 0       | 1
ENA (PWM) -> OUT1 & OUT2

SERVO: 50(MIN)-90(MID)-120(MAX)
*/

#include <Servo.h>

Servo myServo;

int SRV = 6;
int VCC = 7;
int IN1 = 9;
int IN2 = 10;
int ENA = 11;

void setup() {
  myServo.attach(SRV);
  pinMode(VCC, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  myServo.write(90);
  digitalWrite(VCC, 1);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  analogWrite(ENA, 0);

  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    String incomingString = Serial.readStringUntil('\n');
    incomingString.trim();

    String mode = incomingString.substring(0, 1);
    int speed = incomingString.substring(1, 3).toInt();
    String sign = incomingString.substring(3, 4);
    int angle = incomingString.substring(4, 6).toInt();

    if (sign == "m") {
      myServo.write(90);

    } else if (sign == "p") {
      if (angle == 0) {
        myServo.write(120);
      } else {
        myServo.write(map(angle, 0, 99, 90, 120));
      }

    } else if (sign == "n") {
      if (angle == 0) {
        myServo.write(50);
      } else {
        myServo.write(map(angle, 0, 99, 90, 50));
      }
    }
    
    if (mode == "b") {
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      analogWrite(ENA, 0);

    } else if (mode == "f") {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      if (speed == 0) {
        analogWrite(ENA, 50);
      } else {
        analogWrite(ENA, map(speed, 0, 99, 0, 50));
      }

    } else if (mode == "r") {
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      if (speed == 0) {
        analogWrite(ENA, 50);
      } else {
        analogWrite(ENA, map(speed, 0, 99, 0, 50));
      }
    }
  }
}
