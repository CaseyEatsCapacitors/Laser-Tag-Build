#include <FastLED.h>

const int DATA_PIN = 3;
CRGB leds[3];
const CRGB colours[] = {CRGB::Red, CRGB::Green, CRGB::Blue};

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, 3);
  FastLED.setBrightness(40);
  FastLED.clear(true);
}

void loop() {
  for (int colour = 0; colour < 3; colour++) {
    for (int led = 0; led < 3; led++) {
      leds[led] = colours[colour];
      FastLED.show();
      delay(300);
    }
    delay(500);
  }
}