#include <Servo.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#define trigPin 4
#define echoPin 3
#define pir 5
#define buzzer 2
Servo servo;
long distance, duration;
bool motion=0;

SoftwareSerial mySerial(8,9);

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pir, INPUT);
  servo.attach(11);

  mySerial.begin(9600);
  mp3_set_serial (mySerial);
  mp3_set_volume(30);
  delay (5);
  
}
bool cekOrang(){
  unsigned long time;
  time = millis();
  
  //beritahu kang paket
  motion = digitalRead(pir); 
  if (motion == HIGH) {       
    digitalWrite(buzzer, HIGH);
    Serial.println("ADA YANG GERAK TUH!!"); 
  } else {
    digitalWrite(buzzer, LOW);
    Serial.println("KOSONG");
    delay(500);
  }
  
  //tunggu 10 detik
  while(millis()<time+10000){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) * 0.034;
    Serial.print("Jarak : ");
    Serial.println(distance);
    if(distance < 15){
      Serial.println("KANG PAKET NYARI KOTAK TUH");
      return true;
    }
    delay(500);
  }
  return false;
}

void loop() {
  Serial.println("...................................................");
  //pir
  if(digitalRead(pir)){
    if(cekOrang()){
      unsigned long time;
      time = millis();
      //tunggu kang paket masukin barang
      
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(75);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
   
      while(millis()<time+10000){
        digitalWrite(trigPin, LOW);
        delayMicroseconds(10);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distance = (duration/2) * 0.034;
        Serial.print("Jarak : ");
        Serial.println(distance);
        if(distance <= 10){
          servo.write(180);
          Serial.println("SUDAH DEKAT!");
          mp3_play (1);
          delay(500);
        }
        else if(distance >= 10 && distance < 50){
          servo.write(0);
          Serial.println("MASIH JAUH");
          delay(500);
        }
        else{
          break;
          Serial.println("DIA PERGI, SEPERTINYA BUKAN KANG PAKET!");
          delay(500);
        }
      }
      servo.write(0);
    }
  }

  //nunggu 1/2 detik
  delay(500);
}
