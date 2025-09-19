void setup() {
  // Initialisierungscode
  Serial.begin(9600);
  delay(1000);
}



float fakeTemp = 25.0;

void loop() {
  Serial.print("Simulierte Temperatur: ");
  Serial.print(fakeTemp);
  Serial.println(" °C");

  fakeTemp += 0.1; // Temperatur steigt langsam
  if (fakeTemp > 30.0) fakeTemp = 25.0;

  delay(1000);
}
