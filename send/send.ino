/*
 *  This sketch sends field data to Processing.
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
  establishContact();
}

void loop(void) 
{  
  sendData();
  delay(random(10, 50));
}

void establishContact()
{
  while (Serial.available() <= 0)
  {
    Serial.println("connecting");
    delay(300);
    val = Serial.read(); // read it and store it in val
    String rec = String(val);    
  }
}

void sendData()
{
   Serial.println(field);
}
