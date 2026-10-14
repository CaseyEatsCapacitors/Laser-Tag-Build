#include <Arduino.h>

constexpr uint8_t IR_PIN = 2;
constexpr uint8_t MESSAGE = 0xA5;
constexpr uint8_t MESSAGE2 = 67;

void pulse(uint16_t markUs, uint16_t spaceUs) {
  ledcWrite(IR_PIN, 128);
  delayMicroseconds(markUs);
  ledcWrite(IR_PIN, 0);
  delayMicroseconds(spaceUs);
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, OUTPUT);
  digitalWrite(IR_PIN, LOW);
  ledcAttach(IR_PIN, 38000, 8);
  ledcWrite(IR_PIN, 0);
}

void loop() {
  pulse(4000, 4000);

  for (int bit = 7; bit >= 0; bit--) {
    pulse(560, ((MESSAGE >> bit) & 1U) ? 1690 : 560);
  }

  pulse(560, 10000);

  Serial.print("Sent: 0x");
  Serial.print(MESSAGE, HEX);
  Serial.print("\t");
  Serial.print(MESSAGE, BIN);
  Serial.print("\t");
  Serial.println(MESSAGE, DEC);

  delay(5000);

  pulse(4000, 4000);

  for (int bit = 7; bit >= 0; bit--) {
    pulse(560, ((MESSAGE2 >> bit) & 1U) ? 1690 : 560);
  }

  pulse(560, 10000);

  Serial.print("Sent: 0x");
  Serial.print(MESSAGE2, HEX);
  Serial.print("\t");
  Serial.print(MESSAGE2, BIN);
  Serial.print("\t\t");
  Serial.println(MESSAGE2, DEC);

  delay(5000);
}