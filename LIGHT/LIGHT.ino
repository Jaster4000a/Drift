
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6

#define NUMPIXELS      30

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 5;

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); 
}

void loop() {

  for(int j=0;j<256;j++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(j,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
    }
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,j,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
    }
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,j));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
    }
    delay(10);
  }
}
