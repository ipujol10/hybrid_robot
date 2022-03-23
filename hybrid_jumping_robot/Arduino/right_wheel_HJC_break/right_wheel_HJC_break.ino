#include <uStepperS.h>



#define DEBUG true
#define MAXACCELERATION 1500  //Max acceleration = 1500 Steps/s^2
#define MAXVELOCITY 1500      //Max velocity = 1500 steps/s

#define BREAK_ANGLE 90 // POS were servo is breaking pos
#define BREAK_RELAESE_ANGLE 0 // POS were servo is breaking is an relaesed pos
String value;
uStepperServo servo;  // create a servo object in the documentation from ustepper it is on pin3 of the ustepper board

uStepperS stepper;
String cmd = "0";
char msg[4];
void setup() {
  // put your setup code here, to run once:

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
        uint8_t holdCurrent = 30);
  */

  stepper.setup(NORMAL,
                200,
                10.0,
                0.0,
                0.0,
                16,
                true,
                0,
                80,
                80);
  stepper.runContinous(CCW);
  stepper.setMaxDeceleration(10000.0);//float
  /**
     @brief

     @param[in]   mode  -  this parameter specifies how the motor should brake during standstill.
            available modes:
            FREEWHEELBRAKE - This will result in no holding torque at standstill
            COOLBRAKE 1 - This will make the motor brake by shorting the two bottom FET's of the H-Bridge. This will provide less holding torque, but will significantly reduce driver heat
            HARDBRAKE 2 - This will make the motor brake by sending the full specified current through the coils. This will provide high holding torque, but will make the driver (and motor) dissipate power

     @param[in]   brakeCurrent (optional) -  if HARDBRAKE is use as mode, this argument can set the current to use for braking (0-100% of 2A).
            If argument is not specified, the motor will brake with 25% of max current
  */
  stepper.setBrakeMode( 2, 75.0 );
  stepper.disableStallguard();
  //Serial is starting communciation on UART0
  //Serial is used for debugging purpose
  Serial.begin(115200);
  //Serial1 is starting communciation on UART1
  //Serial1 is used for communicating with the raspberry
  Serial1.begin(115200);

  servo.setup();

}

void loop() {

  if (1 < Serial1.available())
  {
    cmd = Serial1.readStringUntil('\n');
    Serial.print("commaded speed is ");
    Serial.println(cmd);
    Serial.flush();
  }

  if ((cmd == "0")) //Stop
  {
    stepper.stop();
    servo.write(BREAK_ANGLE);
  }
  else {
    stepper.setRPM(cmd.toInt());
    servo.write(BREAK_RELAESE_ANGLE);
  }
  Serial1.println(stepper.encoder.getRPM());
  delay(5);
}
