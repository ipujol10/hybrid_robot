#include <uStepperS.h>

#define DEBUG true
#define MAXACCELERATION 1500  //Max acceleration = 1500 Steps/s^2
#define MAXVELOCITY 1500      //Max velocity = 1500 steps/s

uStepperS stepper;
String cmd = "0";
char msg[4];
void setup() {
    // put your setup code here, to run once:
    stepper.setup();
    stepper.runContinous(CCW);
    Serial.begin(115200);
    Serial1.begin(115200);
}

void loop() {

    if (1 < Serial1.available())
    {
        cmd = Serial1.readStringUntil('\n');
        Serial.print("commaded speed is ");
        Serial.println(cmd);
        Serial1.flush();
    }

    if ((cmd == "0")) //Stop
    {
        stepper.stop();
    }
    else {
        stepper.setRPM(cmd.toInt());
    }
    Serial1.println(stepper.encoder.getRPM());
    delay(5);
}
