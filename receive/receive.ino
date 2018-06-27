/*
 *  This sketch receives led data to the sense-chess database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */

const int ledfield = 2;
const int ledpin = 1;
char val;
int ledPins[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,
                 11,12,13,14,15,16,17,18,19,20,
                 21,22,23,24,25,26,27,28,29,30,
                 31,32,33,34,35,36,37,38,39,40,
                 41,42,43,44,45,46,47,48,49,50,
                 51,52,53,54,55,56,57,58,59,60,
                 61,62,63,64};

void setup(void) 
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  for(int p=0; p<64; p++)
  {
    pinMode(ledPins[p], OUTPUT); // Set the mode to OUTPUT
  }
  establishContact();
}

void loop(void) 
{  
  if (Serial.available() > 0) { // If data is available to read,
    val = Serial.read(); // read it and store it in val
      memset(myArray, 0, sizeof(myArray));
                
      // initialisieren und ersten Abschnitt erstellen
      ptr = strtok(val, delimiter);
      int i = 0;
      while(ptr != NULL) {
        myArray[i]=atoi(ptr);
        // naechsten Abschnitt erstellen
        ptr = strtok(NULL, delimiter);
        i++;
      }
      digitalWrite(LED_BUILTIN, LOW);
      for(int p=0; p<64; p++)
      {
        digitalWrite(ledPins[p], LOW); // Set the mode to OUTPUT
      }
      for(int t =0; t<=sizeof(myArray);t++){;
        digitalWrite(myArray[t], HIGH);
        Serial.println(myArray[t]);
        // for testing
        if(myArray[t]==64){
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println("g3");
          delay(15000);
        }  
    }    
    delay(100);
  } 
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("connecting");
    delay(300);
  }
}
