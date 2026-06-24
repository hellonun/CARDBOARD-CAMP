#include <Servo.h>

const int BUTTON_PINS[] = {2, 3, 4};
const int SERVO_PINS[]  = {6, 7, 8};
const int NUM_PAIRS     = 3;

Servo servos[NUM_PAIRS];

bool lastButtonState[NUM_PAIRS]     = {false, false, false};
bool servoActive[NUM_PAIRS]         = {false, false, false};
unsigned long servoTimer[NUM_PAIRS] = {0, 0, 0};

const int          BASE_ANGLE = 90;
const int          MOVE_ANGLE = 180;
const unsigned long HOLD_MS   = 2000;

void setup() {
  Serial.begin(9600);
  Serial.println("System ready. Waiting for button presses...");

  for (int i = 0; i < NUM_PAIRS; i++) {
    pinMode(BUTTON_PINS[i], INPUT);
    servos[i].attach(SERVO_PINS[i]);
    servos[i].write(BASE_ANGLE);
  }
}

void loop() {
  unsigned long now = millis();

  for (int i = 0; i < NUM_PAIRS; i++) {
    bool currentState = digitalRead(BUTTON_PINS[i]) == HIGH;

    if (currentState && !lastButtonState[i] && !servoActive[i]) {
      Serial.print("[");
      Serial.print(now);
      Serial.print("ms] Button D");
      Serial.print(BUTTON_PINS[i]);
      Serial.print(" pressed → Servo D");
      Serial.print(SERVO_PINS[i]);
      Serial.println(" moving to 135°");

      servos[i].write(BASE_ANGLE - MOVE_ANGLE);
      servoActive[i] = true;
      servoTimer[i]  = now;
    }

    if (servoActive[i] && (now - servoTimer[i] >= HOLD_MS)) {
      Serial.print("[");
      Serial.print(now);
      Serial.print("ms] Servo D");
      Serial.print(SERVO_PINS[i]);
      Serial.println(" returning to 90°");

      servos[i].write(BASE_ANGLE);
      servoActive[i] = false;
    }

    lastButtonState[i] = currentState;
  }
}