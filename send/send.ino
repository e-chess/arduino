/*
 *  This sketch sends field data to the sense-chess database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */

String field = "d7";
bool contact = false;
char val;
char delimiter[] = ",;";
char *ptr;
int myArray[] = {};

void setup(void) 
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  establishContact();
}

void loop(void) 
{  
  sendData();
  delay(1500);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("connecting");
    delay(300);
    val = Serial.read(); // read it and store it in val
    String rec = String(val);
    if(rec == "connecting"){
      Serial.println("h3");
    }
    
  }
}

void sendData() {
   Serial.println(field);
}
