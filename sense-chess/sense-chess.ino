/*
 *  This sketch sends test data to the sense-chess test database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */

String field = "d7";
char val;
int myArray[] = {};
String ledArray[] = { "a1 1","a2 2"};
const int ledfield = 2;
const int ledpin = 1;
int pinMatrix[64][64] = { {"a1",1}, {"a2",2}, {"a3",3}, {"a4",4}, {"a5",5}, {"a6",6}, {"a7",7}, {"a8",8} 
};

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

    String rec = String(val);

    if(val == "connected") {
        digitalWrite(LED_BUILTIN, HIGH);
    }else{
      // !!!!!!
      // only works if Arduino receives only 5 fields, f.e.: d5, h7, g2, a6, f3
      // !!!!!!
 /*     int reclength = rec.length();
      if(reclength>=17){
        String stringFive.substring(16, 18);
        String stringFour.substring(12, 14);
        String stringThree.substring(8, 10);
        String stringTwo.substring(4, 6);
        String stringOne.substring(0, 2);
      }
      else if (reclength>=13){
        String stringFour.substring(12, 14);
        String stringThree.substring(8, 10);
        String stringTwo.substring(4, 6);
        String stringOne.substring(0, 2);
      }
      else if (reclength>=9){
        String stringThree.substring(8, 10);
        String stringTwo.substring(4, 6);
        String stringOne.substring(0, 2);
      }
      else if (reclength>=5){
        String stringTwo.substring(4, 6);
        String stringOne.substring(0, 2);
      }
      else{
        String stringOne.substring(0, 2);
      }
  */  memset(myArray, 0, sizeof(myArray));
      char delimiter[] = ",;";
      char *ptr;
          
      // initialisieren und ersten Abschnitt erstellen
      ptr = strtok(val, delimiter);
      int i = 0;
      while(ptr != NULL) {
        myArray[i]=ptr;
        // naechsten Abschnitt erstellen
        ptr = strtok(NULL, delimiter);
        i++;
      }
      digitalWrite(LED_BUILTIN, LOW);
      for(int t =0; t<=sizeof(myArray);t++){
        for(int j =0; j<=sizeof(ledArray);j++){
           if(pinMatrix[j][0]==myArray[t]){
              digitalWrite(LED_BUILTIN, HIGH);
           }
        }
      }  
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
