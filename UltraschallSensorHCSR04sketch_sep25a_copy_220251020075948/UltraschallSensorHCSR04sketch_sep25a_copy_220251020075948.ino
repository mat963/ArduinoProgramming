#include<Wire.h>

const int trigPin = 25;
const int echoPin = 26;

void setup() {
  Serial.begin(9600);
   Serial.println("Setup gestartet");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(12);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  Serial.print("Duration:");
  Serial.println(duration);

  

  float distance = duration *0.034 / 2;

  Serial.print("Entfernung: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1500);
}
