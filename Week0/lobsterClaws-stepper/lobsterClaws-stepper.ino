#include <Stepper.h>

const int stepsPerRevolution = 2048;

Stepper motor1(stepsPerRevolution, 2, 4, 3, 5);
Stepper motor2(stepsPerRevolution, 8, 10, 9, 11);

const int totalSteps = 512;
int stepsLeft = totalSteps;
bool goingForward = true;

void setup() {
  motor1.setSpeed(10);
  motor2.setSpeed(10);
}

void loop() {
  if (stepsLeft > 0) {
    motor1.step(goingForward ? 5 : -5);   // motor1 forward or back
    motor2.step(goingForward ? -5 : 5);   // motor2 always opposite
    stepsLeft -= 5;
  } else {
    goingForward = !goingForward;
    stepsLeft = totalSteps;
    delay(500);
  }
}