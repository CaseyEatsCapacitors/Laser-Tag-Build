constexpr int HAPTIC_PIN = 21;

void setup() {
  pinMode(HAPTIC_PIN, OUTPUT);
  digitalWrite(HAPTIC_PIN, LOW);
}

void loop() {
  digitalWrite(HAPTIC_PIN, HIGH);
  delay(1000);

  digitalWrite(HAPTIC_PIN, LOW);
  delay(1000);
}