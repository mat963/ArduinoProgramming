#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  if (!bme.begin(0x76)) {
    Serial.println("Sensor nicht gefunden!");
    //while (1);
  Wire.begin(21, 22);
  }
}

void loop() {
  Serial.print("Temperatur: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Luftdruck: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  delay(1000);
}
