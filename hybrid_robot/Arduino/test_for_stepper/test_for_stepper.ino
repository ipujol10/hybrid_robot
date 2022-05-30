

void setup() {
  
  //Serial is starting communciation on UART0
    //Serial is used for debugging purpose
    Serial.begin(115200);
    //Serial3 is starting communciation on UART1
    //Serial3 is used for communicating with the ustepper
    Serial3.begin(115200);
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
