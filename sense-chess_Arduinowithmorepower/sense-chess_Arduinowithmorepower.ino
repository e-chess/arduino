/*
 *  This sketch sends test data to the sense-chess test database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */

String field = "d7";
char val;
char delimiter[] = ",;";
char *ptr;
int myArray[] = {};
const int ledfield = 2;
const int ledpin = 1;
// !!!! dynamic storage of Arduino is too small for all 64 fields !!!!
int pinMatrix[8][8] = { {"a1",1}, {"a2",2}, {"a3",3}, {"a4",4}, {"a5",5}, {"a6",6}, {"a7",7}, {"a8",8} 
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

    if(rec == "connected") {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(rec == "connecting"){
      digitalWrite(LED_BUILTIN, LOW);
    }
    else{
      memset(myArray, 0, sizeof(myArray));
                
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
        for(int j =0; j<=sizeof(pinMatrix);j++){
           if(pinMatrix[j][0]==myArray[t]){
              //digitalWrite(pinMatrix[j][1], HIGH);
              digitalWrite(LED_BUILTIN, HIGH);
              Serial.println(pinMatrix[j][0]);
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
