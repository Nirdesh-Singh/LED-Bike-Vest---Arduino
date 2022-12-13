#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define LED_LEFT    4
#define LED_RIGHT   6

#define LED_COUNT 60 // Define the number of LEDs in the strip

char state = 0; 
int light_delay = 50; 

Adafruit_NeoPixel strip_left(LED_COUNT, LED_LEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_right(LED_COUNT, LED_RIGHT, NEO_GRB + NEO_KHZ800);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip_left.begin();           
  strip_left.show();            
  strip_left.setBrightness(150); 

  strip_right.begin();           
  strip_right.show();            
  strip_right.setBrightness(150);
  Serial.begin(9600);
  delay(1000);
}

void loop() {

  if (Serial.available() > 0) {


    state = Serial.read();
    Serial.print(state);

    if (state == 'L') {
      leftBlink();
      delay(light_delay);

    }

    if (state == 'R') {
      rightBlink();
      delay(light_delay);

    }

  }

}


void colorWipeLeft(uint32_t color, int wait) {
  for (int i = 0; i < strip_left.numPixels(); i++) { 
    strip_left.setPixelColor(i, color);         
    strip_left.show();                          
    delay(wait);                          
    strip_left.clear();
  }
}


void rightBlink() {

  for (int i = 0; i < 4; i++) {

    colorBlinkersRight(strip_right.Color(255,   0,   0), 50); //Red
    delay(400);
    colorBlinkersRight(strip_right.Color(0,   0,   0), 25); //Red
    delay(300);

  }
}

void colorBlinkersRight(uint32_t c, int wait) {

  for(int i=0;i<30;i++) {
    strip_right.setPixelColor(i, c);
  }

  strip_right.show();
  delay(wait);
  strip_right.clear();
  delay(wait);

}

void hazardBlink() {

  for (int i = 0; i < 4; i++) { 

    colorBlinkersLeft(strip_left.Color(255,   0,   0), 50); //Red
    colorBlinkersRight(strip_right.Color(255,   0,   0), 50); //red

    delay(400);
    colorBlinkersLeft(strip_left.Color(0,   0,   0), 25); //Red
    colorBlinkersRight(strip_right.Color(0,   0,   0), 50); //Red

    delay(300);

  }
}


void leftBlink() {

  for (int i = 0; i < 4; i++) {

    colorBlinkersLeft(strip_left.Color(255,   0,   0), 50); //red
    delay(400);
    colorBlinkersLeft(strip_left.Color(0,   0,   0), 25); //Red
    delay(300);

  }
}

void colorBlinkersLeft(uint32_t c, int wait) {

  for(int i=0;i<30;i++) {
    strip_left.setPixelColor(i, c);
  }


  strip_left.show();
  delay(wait);
  strip_left.clear();
  delay(wait);

}

void colorWipeRight(uint32_t color, int wait) {
  for (int i = 0; i < strip_right.numPixels(); i++) {
    strip_right.setPixelColor(i, color);         
    strip_right.show();                          
    delay(wait);                          
    strip_right.clear();
  }
}

void rainbow_left(int wait) {

  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip_left.numPixels(); i++) {

      int pixelHue = firstPixelHue + (i * 65536L / strip_left.numPixels());

      strip_left.setPixelColor(i, strip_left.gamma32(strip_left.ColorHSV(pixelHue)));
    }
    strip_left.show();
    delay(wait);  // Pause for a moment
  }
}

void rainbow_right(int wait) {

  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip_right.numPixels(); i++) {

      int pixelHue = firstPixelHue + (i * 65536L / strip_right.numPixels());

      strip_right.setPixelColor(i, strip_right.gamma32(strip_right.ColorHSV(pixelHue)));
    }
    strip_right.show();
    delay(wait);  // Pause for a moment
  }
}

void clearLights() {
  strip_left.clear();
  strip_right.clear();
}
