#include <Servo.h>
#include "Arduino.h"

#define trigPin 4
#define echoPin 3
#define pir 5
#define buzzer 2

Servo servo;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pir, INPUT);
  servo.attach(13);
  servo.write(180);  // set servo
}

void loop() {
  long durationindigit, distanceincm;
  int motion=0;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationindigit = pulseIn(echoPin, HIGH);
  distanceincm = (durationindigit/5) / 29.1;

if (distanceincm > 10 || distanceincm <= 0){
  Serial.println("Outside the permissible range of distances");
  }
else {
  Serial.print(distanceincm);
  Serial.println(" cm");
  servo.read();
  }

  motion = digitalRead(pir);   // read sensor value
  if (motion == HIGH) {           // check if the sensor is HIGH
    digitalWrite(buzzer, HIGH);   // turn BUZZER ON
    Serial.println("Motion Detected!"); 
  } else {
    digitalWrite(buzzer, LOW);
    Serial.println("Motion stopped!");
  }
  delay(500);
}
