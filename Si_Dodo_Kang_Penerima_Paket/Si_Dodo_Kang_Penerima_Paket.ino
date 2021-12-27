#include <Servo.h>

#define trigPin 4
#define echoPin 3
#define soundbuzzer 2
int sound = 500;

Servo servo;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(soundbuzzer, OUTPUT);
  servo.attach(13);
  servo.write(90);  // set servo
}

void loop() {
  long durationindigit, distanceincm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationindigit = pulseIn(echoPin, HIGH);
  distanceincm = (durationindigit/5) / 29.1;

if (distanceincm > 10 || distanceincm <= 0){
  Serial.println("Outside the permissible range of distances");
  noTone(soundbuzzer);
  }
else {
  servo.read();
  Serial.print(distanceincm);
  Serial.println(" cm");
  tone(soundbuzzer, sound);
  }

delay(300);
}
