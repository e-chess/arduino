/*
 *  This sketch sends test data to the sense-chess test database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */

String field = "d7";
char val;

void setup(void) 
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  establishContact();
}

void loop(void) 
{  
  if (Serial.available() > 0) { // If data is available to read,
    val = Serial.read(); // read it and store it in val

    if(val == "connected") {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(val == "d1") {
        digitalWrite(LED_BUILTIN, HIGH);
    }else if(val == "d6") {
        digitalWrite(LED_BUILTIN, LOW);
    }
    else{ 
        digitalWrite(LED_BUILTIN, LOW);
    }
    delay(100);
  } 
  else {
    sendData();
    delay(1500);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("connecting");
    delay(300);
  }
}

void sendData() {
   Serial.println(field);
}
