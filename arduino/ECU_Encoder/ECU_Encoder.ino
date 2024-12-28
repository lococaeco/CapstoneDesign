#define ENCODER_R_A 2
#define ENCODER_R_B 4
#define ENCODER_L_A 3
#define ENCODER_L_B 5
#define PULSES_PER_REVOLUTION 13500

volatile int RightPulseCount = 0;
volatile int LeftPulseCount = 0;

unsigned long previousMillis = 0;

int RightRPM = 0;
int LeftRPM = 0;

void encoderISR_R() {
  int stateB = digitalRead(ENCODER_R_B);
  if (stateB == HIGH) {
    RightPulseCount++;
  } else {
    RightPulseCount--;
  }
}

void encoderISR_L() {
  int stateB = digitalRead(ENCODER_L_B);
  if (stateB == HIGH) {
    LeftPulseCount++;
  } else {
    LeftPulseCount--;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ENCODER_R_A, INPUT);
  pinMode(ENCODER_R_B, INPUT);
  pinMode(ENCODER_L_A, INPUT);
  pinMode(ENCODER_L_B, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ENCODER_R_A), encoderISR_R, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_L_A), encoderISR_L, RISING);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 50) {
    previousMillis = currentMillis;
    
    float revolutions_R = RightPulseCount / (float)PULSES_PER_REVOLUTION;
    float revolutions_L = LeftPulseCount / (float)PULSES_PER_REVOLUTION;
    RightRPM = revolutions_R * 1200;
    LeftRPM = revolutions_L * -1200;

    Serial.print(RightRPM);
    Serial.print("_");
    Serial.println(LeftRPM);
    
    RightPulseCount = 0;
    LeftPulseCount = 0;
  }
}
