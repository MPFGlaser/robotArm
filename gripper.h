#ifndef GRIPPER_H_
#define GRIPPER_H_

class Gripper {
  public:
    Gripper();
    void open(int steps);
    void close(int steps);
  private:
    void move(int steps);
    void stepper(int xw);
    void SetDirection();
    int StepperSteps;
    bool Clockwise;
    unsigned long last_time;
    unsigned long currentMillis;
    long time;
};

#endif
