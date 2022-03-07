#include <uStepperS.h>

#define DEBUG true
#define MAXACCELERATION 1500  //Max acceleration = 1500 Steps/s^2
#define MAXVELOCITY 1500      //Max velocity = 1500 steps/s

uStepperS stepper;
int cmd = 0;
char msg[4];
void setup() {
  // put your setup code here, to run once:
  stepper.setup();
  stepper.runContinous(CCW);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {

  if (3 < Serial1.available()) { // loop through all but the last
    cmd = Serial1.readBytes(msg, 4);
    cmd = atoi(msg);
    Serial.print("commaded speed is ");
    Serial.println(cmd);

  }

  if ((cmd == 0)) //Stop
  {
    stepper.stop();
  }
  else {
    stepper.setRPM(cmd);
  }
  Serial1.print(stepper.getRPM())
  delay(1000);
}


