#include <Arduino.h>

const int LEFT_PIN = 37, RIGHT_PIN = 13;
const unsigned long DEBOUNCE_MS = 30;
uint8_t rawState, stableState;
unsigned long changedAt = 0;

uint8_t readSwitch() {
  return (digitalRead(LEFT_PIN) == LOW ? 1 : 0) |
         (digitalRead(RIGHT_PIN) == LOW ? 2 : 0);
}

void printPosition() {
  switch (stableState) {
    case 0: Serial.println("CENTRE OFF - both pins HIGH"); break;
    case 1: Serial.println("LEFT / GREEN - GPIO37 LOW, GPIO13 HIGH"); break;
    case 2: Serial.println("RIGHT / BLUE - GPIO37 HIGH, GPIO13 LOW"); break;
    case 3: Serial.println("INVALID - both pins LOW"); break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  rawState = stableState = readSwitch();
  Serial.println("Slide-switch test: move between the three positions.");
  printPosition();
}

void loop() {
  uint8_t reading = readSwitch();
  unsigned long now = millis();

  if (reading != rawState) {
    rawState = reading;
    changedAt = now;
  }

  if (rawState != stableState && now - changedAt >= DEBOUNCE_MS) {
    stableState = rawState;
    printPosition();
  }
}
