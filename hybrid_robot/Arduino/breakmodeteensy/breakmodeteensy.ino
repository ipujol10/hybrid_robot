#include <Servo.h>

Servo leftservo;
Servo rightservo;

int leftbreakpos = 0;
int leftopenpos = 86;

int rightbreakpos = 0;
int rightopenpos = 100;

String cmd = "0";

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  leftservo.attach(9);  // attaches the servo on pin 9 to the servo object
  rightservo.attach(8);
}

void loop()
{
  while (Serial1.available() > 0) {
    cmd = Serial1.readStringUntil('\n');
    Serial.print(cmd);
  }
  while (Serial.available() > 0) {
    cmd = Serial.readStringUntil('\n');
    Serial.print(cmd);
  }
  if (cmd == "0") {
    leftservo.write(leftbreakpos);  // attaches the servo on pin 9 to the servo object
    rightservo.write(rightbreakpos);
  } else {
    leftservo.write(leftopenpos);  // attaches the servo on pin 9 to the servo object
    rightservo.write(rightopenpos);
  }

}
