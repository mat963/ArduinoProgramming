// Pins für den Encoder (anpassen!)
const int pinA = 2;   // GPIO für Kanal A
const int pinB = 4;   // GPIO für Kanal B

volatile long encoderTicks = 0;
volatile int direction = 0; // 1 = vorwärts, -1 = rückwärts

unsigned long lastTime = 0;
float rpm = 0.0;

// Interrupt-Routine für Kanal A
void IRAM_ATTR handleEncoderA() {
  int stateA = digitalRead(pinA);
  int stateB = digitalRead(pinB);

  if (stateA == stateB) {
    encoderTicks++;
    direction = 1; // vorwärts
  } else {
    encoderTicks--;
    direction = -1; // rückwärts
  }
}

// Interrupt-Routine für Kanal B (optional, für höhere Genauigkeit)
void IRAM_ATTR handleEncoderB() {
  int stateA = digitalRead(pinA);
  int stateB = digitalRead(pinB);

  if (stateA != stateB) {
    encoderTicks++;
    direction = 1;
  } else {
    encoderTicks--;
    direction = -1;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), handleEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), handleEncoderB, CHANGE);

  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= 1000) { // alle 1 Sekunde berechnen
    // 600 Pulse pro Umdrehung (PPR)
    float revolutions = (float)encoderTicks / 600.0;
    rpm = revolutions * 60.0; // Umdrehungen pro Minute

    Serial.print("Drehzahl (RPM): ");
    Serial.println(rpm);

    Serial.print("Richtung: ");
    if (direction == 1) Serial.println("Vorwärts");
    else if (direction == -1) Serial.println("Rückwärts");
    else Serial.println("Unbekannt");

    encoderTicks = 0; // zurücksetzen fürs nächste Intervall
    lastTime = currentTime;
  }
}
