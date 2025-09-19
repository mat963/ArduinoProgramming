int pins[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33}; // Nutze nur sichere GPIOs
int numPins = sizeof(pins) / sizeof(pins[0]);

void setup() {
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < numPins; i++) {
    digitalWrite(pins[i], HIGH);
  }
  delay(500);

  for (int i = 0; i < numPins; i++) {
    digitalWrite(pins[i], LOW);
  }
  delay(500);
}
