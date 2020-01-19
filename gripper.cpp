#include "gripper.h"
#include "arduino.h"
#include "pinout.h"

#define IN1 STEPPER_GRIPPER_PIN_0
#define IN2 STEPPER_GRIPPER_PIN_1
#define IN3 STEPPER_GRIPPER_PIN_2
#define IN4 STEPPER_GRIPPER_PIN_3

int StepperSteps = 0;
boolean Open = true;
unsigned long last_time;
unsigned long currentMillis;
long time;


Gripper::Gripper()
{

}

void Gripper::open(int steps)
{
  Open = true;
  move(steps * 10);
}

void Gripper::close(int steps)
{
  Open = false;
  move(steps * 10);
}

void Gripper::move(int steps)
{
  while (steps > 0) {
    currentMillis = micros();
    if (currentMillis - last_time >= 1000) {
      stepper(1);
      time = time + micros() - last_time;
      last_time = micros();
      steps--;
    }
  }
}

void Gripper::stepper(int xw)
{
  for (int x = 0; x < xw; x++) {
    switch (StepperSteps) {
      case 0:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      case 1:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        break;
      case 2:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 3:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 4:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 5:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 6:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 7:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      default:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
    }
    SetDirection();
  }
}

void Gripper::SetDirection() {
  if (Open == 1) {
    StepperSteps++;
  }
  if (Open == 0) {
    StepperSteps--;
  }
  if (StepperSteps > 7) {
    StepperSteps = 0;
  }
  if (StepperSteps < 0) {
    StepperSteps = 7;
  }
}
