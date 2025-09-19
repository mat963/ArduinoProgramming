
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


const char* ssid = "Vodafone-D9DF";
const char* password = "D4aNemA8tHngCnRg";
const char* mqttServer = "192.168.0.206"; //"broker.mqtt-dashboard.com";
const int mqttPort = 1883;


WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_BME280 bme;

void setup() {
  //delay(2000);
  Serial.begin(9600);
  Wire.begin(21, 22);
  if (!bme.begin(0x76)){
    Serial.println("Sensor nicht gefunden!");
    
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    client.connect("ESP32Client");
  
  }

}

void loop() {
  client.loop();
  float temp = bme.readTemperature();
  String payload = String(temp);
  client.publish("esp32/temperatur", payload.c_str());
  //client.publish("esp32/temperatur", payload.c_str(), false);  // retain = false
  Serial.println("Testausgabe Serial:");
  Serial.println(WiFi.localIP());

  delay(5000); // alle 5 Sekunden senden  funktioniert alles 18.09.25
}
