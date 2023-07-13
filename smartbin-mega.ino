#include <Servo.h>
#include "DHT.h"

//UltraSonic Pin Area
#define echo1 24
#define trig1 25
#define echo2 26
#define trig2 27
#define echo3 28
#define trig3 29

//Driver Kanan Pin Area
#define ENA1 A0
#define ENA2 A1
#define driver1 30
#define driver2 31
#define driver3 32
#define driver4 33

//Driver Kiri Pin Area
#define ENB1 A2
#define ENB2 A3
#define driver5 34
#define driver6 35
#define driver7 36
#define driver8 37

//Line tracer pin area
#define right 38
#define center 39
#define left 40

//Servo Pin Area
#define servo1 2
int pos = 0;
//#define servo2 //Jaga2

//DHT
#define DHTPIN 3
#define DHTTYPE DHT22

//PULLUP PIN
#define MasterSwitch 22
#define ResetCount 23

//PULLUP MANUAL
#define MasterManual 41
#define P1 42 //maju
#define P2 43 //kiri
#define P3 44 //kanan
#define P4 45 //mundur
#define P5 46 //special 

//DFPLAYER
int suara = 4;
int counter = 0;

DHT dht(DHTPIN, DHTTYPE);
Servo servo;  


long duration_atas, distance_atas, duration_dalam, distance_dalam, duration_depan, distance_depan; 
int ValueMasterSwitch, ValueResetCount, ValueMasterManual;
int ValueRight, ValueCenter, ValueLeft;

String disatas;
String disdalam;
String disdepan;
String dakanan;
String datengah;
String dakiri;
String jalanke;
String dadhtemp;
String dadhthum;
String isAuto;

//===========================[NORMAL MOVE]==============================//
void maju(){
  digitalWrite(driver1, HIGH);
  digitalWrite(driver2, LOW);

  digitalWrite(driver3, HIGH);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, HIGH);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, HIGH);
  digitalWrite(driver8, LOW);

  jalanke = "Maju";
}

void kanan(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, HIGH);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, HIGH);

  digitalWrite(driver5, HIGH);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, HIGH);
  digitalWrite(driver8, LOW);

  jalanke = "Kanan";
}

void kiri(){
  digitalWrite(driver1, HIGH);
  digitalWrite(driver2, LOW);

  digitalWrite(driver3, HIGH);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, LOW);
  digitalWrite(driver6, HIGH);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, HIGH);

  jalanke = "Kiri";
}

void mundur(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, HIGH);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, HIGH);

  digitalWrite(driver5, LOW);
  digitalWrite(driver6, HIGH);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, HIGH);

  jalanke = "Mundur";
}

void stop(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, LOW);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, LOW);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, LOW);

  jalanke = "Stop";
}

//==============================[Special Move]===============================//

void maju_kanan(){
  digitalWrite(driver1, HIGH);
  digitalWrite(driver2, LOW);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, LOW);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, HIGH);
  digitalWrite(driver8, LOW);

  jalanke = "Maju-Kanan";
}

void maju_kiri(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, LOW);

  digitalWrite(driver3, HIGH);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, HIGH);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, LOW);

  jalanke = "Maju-Kiri";
}

void slide_kanan(){
  digitalWrite(driver1, HIGH);
  digitalWrite(driver2, LOW);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, HIGH);

  digitalWrite(driver5, LOW);
  digitalWrite(driver6, HIGH);

  digitalWrite(driver7, HIGH);
  digitalWrite(driver8, LOW);

  jalanke = "Slide-Kanan";
}

void slide_kiri(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, HIGH);

  digitalWrite(driver3, HIGH);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, HIGH);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, HIGH);

  jalanke = "Slide-Kiri";
}

void mundur_kanan(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, LOW);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, HIGH);

  digitalWrite(driver5, LOW);
  digitalWrite(driver6, HIGH);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, LOW);

  jalanke = "Mundur-Kanan";
}

void mundur_kiri(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, HIGH);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, LOW);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, HIGH);

  jalanke = "Mundur-Kiri";
}

void lacteral_arc(){
  digitalWrite(driver1, LOW);
  digitalWrite(driver2, HIGH);

  digitalWrite(driver3, LOW);
  digitalWrite(driver4, LOW);

  digitalWrite(driver5, HIGH);
  digitalWrite(driver6, LOW);

  digitalWrite(driver7, LOW);
  digitalWrite(driver8, LOW);

  jalanke = "Lacteral-Arc";
}

void setup() {
  //Serial
  Serial.begin(9600);
  servo.attach(servo1);

  //setup enable driver
  analogWrite(ENA1, 150);
  analogWrite(ENA2, 150);
  analogWrite(ENB1, 150);
  analogWrite(ENB2, 150);

  //setup driver
  pinMode(driver1, OUTPUT);
  pinMode(driver2, OUTPUT);
  pinMode(driver3, OUTPUT);
  pinMode(driver4, OUTPUT);
  pinMode(driver5, OUTPUT);
  pinMode(driver6, OUTPUT);
  pinMode(driver7, OUTPUT);
  pinMode(driver8, OUTPUT);

  //setup line tracer
  pinMode(right, INPUT);
  pinMode(center, INPUT);
  pinMode(left, INPUT);

  //setup ultrasonic
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  //PullUp Pin
  pinMode(MasterSwitch, INPUT_PULLUP);
  pinMode(ResetCount, INPUT_PULLUP);

  //Pullup manual
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
  pinMode(P4, INPUT_PULLUP);
  pinMode(P5, INPUT_PULLUP);
}

void loop() {
  ValueMasterSwitch = digitalRead(MasterSwitch);
  ValueResetCount = digitalRead(ResetCount);
  ValueMasterManual = digitalRead(MasterManual);

  if(ValueResetCount == 0) return counter = 0;

  if(ValueMasterManual == 0){

    isAuto = "true";

    if(ValueMasterSwitch == 0){

      ValueRight = digitalRead(right);
      ValueCenter = digitalRead(center);
      ValueLeft = digitalRead(left);

      if(ValueRight == 1){
        dakanan = "HIGH";
      } else {
        dakanan = "LOW";
      }

      if(ValueCenter == 1){
        datengah = "HIGH";
      } else {
        datengah = "LOW";
      }

      if(ValueLeft == 1){
        dakiri = "HIGH";
      } else {
        dakiri = "LOW";
      }

      digitalWrite(trig1, LOW);
      delayMicroseconds(2);
      digitalWrite(trig1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig1, LOW);
      duration_atas = pulseIn(echo1, HIGH);
      distance_atas = duration_atas/58.2; 

      disatas = String(distance_atas + " Cm");
      //Serial.print(distance_atas);
      //Serial.println(" Centimeter");
      delay(50);

      digitalWrite(trig2, LOW);
      delayMicroseconds(2);
      digitalWrite(trig2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig2, LOW);
      duration_dalam = pulseIn(echo2, HIGH);
      distance_dalam = duration_dalam/58.2; 

      disdalam = String(distance_dalam);
      //Serial.print(distance_dalam);
      //Serial.println(" Centimeter");
      delay(50);

      digitalWrite(trig3, LOW);
      delayMicroseconds(2);
      digitalWrite(trig3, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig3, LOW);
      duration_depan = pulseIn(echo3, HIGH);
      distance_depan = duration_depan/58.2; 

      disdepan = String(distance_depan + " Cm");
      //Serial.print(distance_depan);
      //Serial.println(" Centimeter");
      delay(50);

      //------------------------------< Read DHT22 >-----------------------------------//
      float temp = dht.readTemperature();
      float humidity = dht.readHumidity();

      //-----------------------< DHT REMOVE NAN DISPLAY >---------------------------//
      if(isnan(temp)){
        dadhtemp = "-";
      } else{
        dadhtemp = String(temp);
      }

      if(isnan(humidity)){
        dadhthum = "-";
      } else {
        dadhthum = String(humidity);
      }

      if(distance_dalam > 0 && distance_dalam < 10){
        if(distance_depan > 0 && distance_depan < 20) return stop();
        if(ValueCenter == 0 && ValueRight == 1 && ValueLeft == 1){
          maju();
          //jalanke = "Maju";
          }
        if(ValueCenter == 0 && ValueRight == 0 && ValueLeft == 1){
          kanan();
          //jalanke = "Kanan";
          }
        if(ValueCenter == 0 && ValueRight == 1 && ValueLeft == 0){
          kiri();
          //jalanke = "Kiri";
          }
        if(ValueCenter == 1 && ValueRight == 0 && ValueLeft == 1){
          kanan();
          //jalanke = "Kanan";
          }
        if(ValueCenter == 1 && ValueRight == 1 && ValueLeft == 0){
          kiri();
          //jalanke = "Kiri";
          }
        if(ValueCenter == 1 && ValueRight == 1 && ValueLeft == 1){
          stop();
          //jalanke = "Stop";
          }
        if(ValueCenter == 0 && ValueRight == 0 && ValueLeft == 0){
          stop();
          //jalanke = "Stop";
          }

      } else {
        if(distance_atas > 0 && distance_atas < 40){
        servo.writeMicroseconds(1000);
          pos = -720;
          
          delay(3000);
        
          servo.writeMicroseconds(1500); 
          pos = 0;
          
          delay(5000);
          digitalWrite(suara,LOW);
          delay(100);
          digitalWrite(suara,HIGH);
          //delay(3000);
          
          servo.writeMicroseconds(2000); 
          pos = 720;
          
          delay(3000);
          
          servo.writeMicroseconds(1500); 
          pos = 0;
          
          delay(500);  

          counter = counter + 1;
        } else {
          //myservo.write(0); //do nothing
        }
      }

    } else {
      //Serial.println("Bin Disable"); //do nothing
    }
  } else {

    isAuto = "false";

    digitalRead(P1);
    digitalRead(P2);
    digitalRead(P3);
    digitalRead(P4);
    digitalRead(P5);

    //------------------------------------[MANUAL MOVE]-------------------------------------//
    if(P1 == LOW && P2 == HIGH && P3 == HIGH && P4 == HIGH && P5 == HIGH){
      maju();
    } else if(P1 == HIGH && P2 == LOW && P3 == HIGH && P4 == HIGH && P5 == HIGH){
      kiri();
    } else if(P1 == HIGH && P2 == HIGH && P3 == LOW && P4 == HIGH && P5 == HIGH){
      kanan();
    } else if(P1 == HIGH && P2 == HIGH && P3 == HIGH && P4 == LOW && P5 == HIGH){
      mundur();
    } else if(P1 == LOW && P2 == HIGH && P3 == LOW && P4 == HIGH && P5 == HIGH){
      maju_kanan();
    } else if(P1 == LOW && P2 == LOW && P3 == HIGH && P4 == HIGH && P5 == HIGH){
      maju_kiri();
    } else if(P1 == HIGH && P2 == HIGH && P3 == LOW && P4 == LOW && P5 == HIGH){
      mundur_kanan();
    } else if(P1 == HIGH && P2 == LOW && P3 == HIGH && P4 == LOW && P5 == HIGH){
      mundur_kiri();
    } else if(P1 == HIGH && P2 == HIGH && P3 == LOW && P4 == HIGH && P5 == LOW){
      slide_kanan();
    } else if(P1 == HIGH && P2 == LOW && P3 == HIGH && P4 == HIGH && P5 == LOW){
      slide_kiri();
    } else {
      stop();
    }
  }

  //---------------------[ Send Serial To Nodemcu ESP8266 ]----------------------//
  //Serial.println("testto");
  Serial.println("*"+disatas+","+disdalam+","+disdepan+","+dakanan+","+datengah+","+dakiri+","+jalanke+","+dadhtemp+","+dadhthum+","+String(counter)+","+isAuto+"#"); //inject wrapping
  delay(1000);
}
