/*
 *  This sketch receives led data to the sense-chess database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */

#include <Adafruit_NeoPixel.h>

#define LEDSPIN 6
#define NUMLEDS 64

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMLEDS, LEDSPIN, NEO_GRB + NEO_KHZ800);

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

int message1;
int message2;
int message3;

int myArray[64] = {};
int sizeArray;

boolean newData = false;

//============

void setup() {
    leds.begin();
    Serial.begin(9600);
    Serial.println();
    establishContact();
}

//============

void loop() {

    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        //showParsedData();
        if(myArray[0] == -1)
        {
          
          allLEDsOff();
          Serial.println("Aus");
        }
        else
        {
          for(int t =0; t<=sizeArray-1;t++)
          {
          Serial.println(myArray[t]);
          leds.setPixelColor(myArray[t], leds.Color(255,255,255));
         }
        leds.show();
        }
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index
    strtokIndx = strtok(tempChars,",");
    sizeArray = 0;
    

    int i = 0;
    while(strtokIndx != NULL) {
      myArray[i] = atoi(strtokIndx);
      i++;
      strtokIndx = strtok(NULL, ",");
    }

    sizeArray = i;

}

//============

void showParsedData() {
    for(int t =0; t<sizeArray;t++)
      {
        Serial.println(myArray[t]);
      }
}

//============

void allLEDsOff()
{
  for(int led=0;led<NUMLEDS;led++)
  {
    leds.setPixelColor(led, leds.Color(0,0,0));
    
  }
  leds.show(); 
}

//============

void establishContact() 
{
  while (Serial.available() <= 0) {
    Serial.println("connecting");
    delay(300);
  }
}
