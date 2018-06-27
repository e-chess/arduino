/*
 *  This sketch tests the sense-chess LEDs.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */
 
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMLEDS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

const int SETLEDS = 500; // delay for half a second

void setup() {
  pixels.begin(); // This initializes the NeoPixel library
}

void loop() {
  for(int i=0;i<NUMLEDS;i++){
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
    delay(SETLEDS);
  }
}
