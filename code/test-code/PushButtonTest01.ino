#include <Arduino.h>

const int BUTTON_PIN = 14;
const unsigned long DEBOUNCE_MS = 25;
bool rawState, stableState;
unsigned long changedAt = 0, count = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  rawState = stableState = digitalRead(BUTTON_PIN);
  Serial.println("Button test: press and release GPIO14 button.");
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN);
  unsigned long now = millis();

  if (reading != rawState) {
    rawState = reading;
    changedAt = now;
  }

  if (rawState != stableState && now - changedAt >= DEBOUNCE_MS) {
    bool previous = stableState;
    stableState = rawState;
    if (previous == LOW && stableState == HIGH) {
      Serial.print("Button released - count: ");
      Serial.println(++count);
    }
  }
}
