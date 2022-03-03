

void setup() {
  
  Serial.begin(9600);
  Serial3.begin(9600);
}

byte x = 0;

void loop() {

  x += 10;
  if (x>100){
    x= 0;
    }
  Serial.println(x);
  Serial3.println(x);
  delay(10000);
}
