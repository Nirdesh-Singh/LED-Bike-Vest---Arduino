#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 56

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  for(int i=0;i<56;i++) {
    if(i%2 == 0) {
      leds[i] = CRGB(255, 0, 0);
    FastLED.show();
    delay(100);
    } else {
      leds[i] = CRGB(0, 0, 255);
    FastLED.show();
    delay(100);
    }
  }
}
