/*
 *  This sketch tests the sense-chess LEDs.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */
 
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMLEDS 64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

const int SETLEDS = 5000; // delay for half a second
const int mini = 24;
const int maxi = 40;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library
}

void loop() {
  for(int i=mini;i<maxi;i++){
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  for(int i=mini;i<maxi;i++){
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
}
