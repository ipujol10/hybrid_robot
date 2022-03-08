#include <uStepperS.h>
#include <Wire.h>
#include <Arduino.h>

#define DEBUG true
#define MAXACCELERATION 1500  //Max acceleration = 1500 Steps/s^2
#define MAXVELOCITY 1500      //Max velocity = 1500 steps/s

uStepperS stepper;
int cmd = 0;
char msg[4];
void setup() {
    /*
   uint8_t mode = NORMAL,
       uint16_t stepsPerRevolution = 200,
       float pTerm = 10.0,
       float iTerm = 0.0,
       float dTerm = 0.0,
       uint16_t dropinStepSize = 16,
       bool setHome = true,
       uint8_t invert = 0,
       uint8_t runCurrent = 50,
       uint8_t holdCurrent = 30)
 */

    stepper.setup(NORMAL,
                  200,
                  10.0,
                  0.0,
                  0.0,
                  16,
                  true,
                  0,
                  50,
                  30);
    stepper.runContinous(CW);
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop() {

    if (0 < Serial1.available()) { // loop through all but the last
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
    delay(1000);
}

