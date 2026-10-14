constexpr int SPEAKER_PIN = 21;
unsigned long soundNumber = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_PIN, LOW);
}

void pew() {
  Serial.print("PEW ");
  Serial.println(++soundNumber);

  for (int frequency = 3000; frequency >= 300; frequency -= 100) {
    int halfPeriod = 500000 / frequency;

    for (int cycle = 0; cycle < 6; cycle++) {
      digitalWrite(SPEAKER_PIN, HIGH);
      delayMicroseconds(halfPeriod);
      digitalWrite(SPEAKER_PIN, LOW);
      delayMicroseconds(halfPeriod);
    }
  }
}

void loop() {
  pew();
  delay(100);
  pew();
  delay(1000);
}