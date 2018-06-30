/*
 *  This tests the sense-chess LEDs.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
 */
 
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMLEDS 64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

const int SETLEDS = 500; // delay for half a second

void setup()
{
  pixels.begin(); // This initializes the NeoPixel library
}

void loop()
{
  allOff();
  for(int i=0;i<8;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  allOff();
  for(int i=8;i<16;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  allOff();
  for(int i=16;i<24;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  allOff();
  for(int i=24;i<32;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  allOff();
  for(int i=32;i<40;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  allOff();
  for(int i=40;i<48;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  allOff();
  for(int i=48;i<56;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
  allOff();
  for(int i=56;i<64;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
  delay(SETLEDS);
}

void allOff()
{
  for(int i=0;i<64;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware
  }
}

