int incomingByte = 0;

void setup() {
  Serial.begin(9600); //Starts the serial connection
  pinMode(LED_BUILTIN, OUTPUT); //Sets pin 2 to be output
}

void loop() {

  if(Serial.available() > 0){
    //Serial.write("OK");
    //Serial.read(); //Removes the message from the serial cache
    digitalWrite(LED_BUILTIN, true); //Enables the led on pin 2
    delay(100); //Waits 100 ms
    digitalWrite(LED_BUILTIN, false); //Disables the led on pin 2
  }
}
