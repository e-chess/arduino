/*
 *  This sketch receives led data to the sense-chess database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */

#include <Adafruit_NeoPixel.h>

#define LEDSPIN 6
#define NUMLEDS 64

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMLEDS, LEDSPIN, NEO_GRB + NEO_KHZ800);

char val;
char delimiter[] = ",;";
char *ptr;
int myArray[] = {};
int ledPins[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,
                 11,12,13,14,15,16,17,18,19,20,
                 21,22,23,24,25,26,27,28,29,30,
                 31,32,33,34,35,36,37,38,39,40,
                 41,42,43,44,45,46,47,48,49,50,
                 51,52,53,54,55,56,57,58,59,60,
                 61,62,63,64};

void setup(void) 
{
  leds.begin();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  establishContact();
}

void loop(void) 
{  
  if (Serial.available() > 0) { // If data is available to read
    val = Serial.read(); // read data and store it in val
    Serial.println("val: "+val);
    memset(myArray, 0, sizeof(myArray));
    allLEDsOff();           
    // initialisieren und ersten Abschnitt erstellen
    ptr = strtok(val, delimiter);
    int i = 0;
    while(ptr != NULL) {
      //myArray[i]=atoi(ptr);
      myArray[i]=ptr;
      // naechsten Abschnitt erstellen
      ptr = strtok(NULL, delimiter);
      i++;
    }
    Serial.println(sizeof(myArray));
    if(myArray[0] == -1)
    {
      allLEDsOff();
    }
    else
    {
      for(int t =0; t<=sizeof(myArray);t++)
      {
        Serial.println(myArray[t]);
        //leds.setPixelColor(myArray[t], leds.Color(255,255,255));
        
      }
      leds.show();
    }
  } 
}

void allLEDsOff()
{
  for(int led=0;led<NUMLEDS;led++)
  {
    leds.setPixelColor(led, leds.Color(0,0,0));
    leds.show();
  } 
}

void establishContact() 
{
  while (Serial.available() <= 0) {
    Serial.println("connecting");
    delay(300);
  }
}
