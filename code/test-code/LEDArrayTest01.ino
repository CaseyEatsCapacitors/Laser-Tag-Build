#include <FastLED.h>

constexpr uint8_t MATRIX_PIN = 3;
CRGB leds[64];

const uint8_t heart[8] = {
  0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00
};
const CRGB colours[3] = {CRGB::Green, CRGB::Red, CRGB::Blue};

void setup() {
  FastLED.addLeds<WS2812B, MATRIX_PIN, GRB>(leds, 64);
  FastLED.setMaxPowerInVoltsAndMilliamps(3.3, 200);
  FastLED.setBrightness(90);
}

void loop() {
  CRGB colour = colours[(millis() / 3000) % 3];

  for (uint8_t y = 0; y < 8; y++) {
    for (uint8_t x = 0; x < 8; x++) {
      int index = y * 8 + ((y & 1) ? 7 - x : x);
      leds[index] = (heart[y] & (0x80 >> x))
                    ? colour : CRGB::Black;
    }
  }

  FastLED.show();
  delay(25);
}