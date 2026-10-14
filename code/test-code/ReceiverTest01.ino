// Add header comment
#include <Arduino.h>

constexpr uint8_t IR_PIN = 1;
constexpr uint16_t MAX_PULSES = 100;
volatile uint16_t raw[MAX_PULSES];
volatile uint16_t pulseCount = 0;
volatile uint32_t lastEdge = 0;
volatile bool capturing = false;

void IRAM_ATTR onIREdge() {
  uint32_t now = micros();
  if (!capturing) {
    if (digitalRead(IR_PIN) == LOW) {
      capturing = true;
      pulseCount = 0;
    }
  } else if (pulseCount < MAX_PULSES) {
    uint32_t duration = now - lastEdge;
    raw[pulseCount++] = duration > 65535 ? 65535 : duration;
  }
  lastEdge = now;
}

bool matches(uint16_t duration, uint16_t expected) {
  return duration >= expected * 7UL / 10 &&
         duration <= expected * 13UL / 10;
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);
  attachInterrupt(IR_PIN, onIREdge, CHANGE);
}

void loop() {
  uint16_t timings[MAX_PULSES];
  uint16_t count;

  noInterrupts();
  if (!capturing || micros() - lastEdge < 15000) {
    interrupts();
    return;
  }
  count = pulseCount;
  for (uint16_t i = 0; i < count; i++) timings[i] = raw[i];
  capturing = false;
  interrupts();
  if (count == 0) return;

  if (count == 3 && matches(timings[0], 9000) &&
      matches(timings[1], 2250) && matches(timings[2], 560)) {
    Serial.println("NEC repeat");
    return;
  }

  bool nec = count == 67 && matches(timings[0], 9000) &&
             matches(timings[1], 4500) && matches(timings[66], 560);
  bool laser = (count == 19 || count == 67) &&
               matches(timings[0], 4000) && matches(timings[1], 4000) &&
               matches(timings[count - 1], 560);
  uint8_t bits = nec ? 32 : laser ? (count - 3) / 2 : 0;
  bool decoded = nec || laser;
  uint32_t packet = 0;
  if (decoded) {
    for (int bit = 0; bit < bits; bit++) {
      uint16_t mark = timings[2 + bit * 2];
      uint16_t space = timings[3 + bit * 2];
      if (!matches(mark, 560) ||
          (!matches(space, 560) && !matches(space, 1690))) {
        decoded = false;
        break;
      }
      bool one = matches(space, 1690);
      if (nec) {
        if (one) packet |= uint32_t(1) << bit;
      } else {
        packet = (packet << 1) | one; 
      }
    }
  }

  if (decoded) {
    Serial.print(nec ? "NEC HEX: 0x" : "LASER TAG HEX: 0x");
    Serial.print(packet, HEX);
    Serial.print("  BIN: ");
    for (int bit = bits - 1; bit >= 0; bit--) Serial.print((packet >> bit) & 1U);
  } else {
    Serial.print("Unknown format: decode unavailable");
  }
  Serial.print("  RAW mark timings (us): ");
  for (uint16_t i = 0; i < count; i++) {
    Serial.print(timings[i]);
    Serial.print(' ');
  }
  Serial.println();
}
