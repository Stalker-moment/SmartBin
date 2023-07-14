/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "Bin Controll"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate   
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 64 bytes
  { 255,4,0,0,0,57,0,16,24,1,10,48,23,35,15,15,4,26,31,77,
  97,110,117,97,108,0,31,65,117,116,111,0,5,32,16,60,30,30,2,26,
  31,10,48,47,57,8,8,51,0,31,77,69,67,72,65,0,31,78,79,82,
  77,65,76,0 };
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t b_cswitch; // =1 if state is ON, else =0 
  int8_t joystick_x; // from -100 to 100  
  int8_t joystick_y; // from -100 to 100  
  uint8_t pushSwitch_1; // =1 if state is ON, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 


#define P1 D0
#define P2 D1
#define P3 D2
#define P4 D3
#define P5 D4
#define P6 D5

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(9600);
  
  // TODO you setup code
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  pinMode(P4, OUTPUT);
  pinMode(P5, OUTPUT);
  pinMode(P6, OUTPUT);
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  Serial.print("X : ");
  Serial.println(RemoteXY.joystick_x);
  Serial.print("Y : ");
  Serial.println(RemoteXY.joystick_y);

  if(RemoteXY.b_cswitch == 1){
    digitalWrite(P1, LOW);
    if (RemoteXY.joystick_x <= 50 && RemoteXY.joystick_x >= -50 ){
      if (RemoteXY.joystick_y >= 50){
        Serial.println("MAJUUU");
        digitalWrite(P2, LOW);
        digitalWrite(P3, HIGH);
        digitalWrite(P4, HIGH);
        digitalWrite(P5, HIGH);
        digitalWrite(P6, HIGH);
      }
      if (RemoteXY.joystick_y <= -50){
        Serial.println("MUNDURRR");
        digitalWrite(P2, HIGH);
        digitalWrite(P3, HIGH);
        digitalWrite(P4, HIGH);
        digitalWrite(P5, LOW);
        digitalWrite(P6, HIGH);
      }
    }

    if (RemoteXY.joystick_x < -50){
      if (RemoteXY.joystick_y > 25){
        Serial.println("SERONG KIRIII ATASSS");

        digitalWrite(P2, LOW);
        digitalWrite(P3, LOW);
        digitalWrite(P4, HIGH);
        digitalWrite(P5, HIGH);
        digitalWrite(P6, HIGH);
      }
      else if (RemoteXY.pushSwitch_1 == 0 && RemoteXY.joystick_y <= 25 && RemoteXY.joystick_y >= -25){
        Serial.println("BELOK KIRII");

        digitalWrite(P2, HIGH);
        digitalWrite(P3, LOW);
        digitalWrite(P4, HIGH);
        digitalWrite(P5, HIGH);
        digitalWrite(P6, HIGH);
      }
      else if (RemoteXY.pushSwitch_1 == 1 && RemoteXY.joystick_y <= 25 && RemoteXY.joystick_y >= -25){
        Serial.println("SLIDE KIRII");

        digitalWrite(P2, HIGH);
        digitalWrite(P3, LOW);
        digitalWrite(P4, HIGH);
        digitalWrite(P5, HIGH);
        digitalWrite(P6, LOW);
      }
      else if (RemoteXY.joystick_y < -25){
        Serial.println("SERONG KIRI BAWAHHH");

        digitalWrite(P2, HIGH);
        digitalWrite(P3, LOW);
        digitalWrite(P4, HIGH);
        digitalWrite(P5, LOW);
        digitalWrite(P6, HIGH);
      }
    }

    if (RemoteXY.joystick_x > 50){
      if (RemoteXY.joystick_y > 25){
        Serial.println("SERONG KANAN ATASSS");

        digitalWrite(P2, LOW);
        digitalWrite(P3, HIGH);
        digitalWrite(P4, LOW);
        digitalWrite(P5, HIGH);
        digitalWrite(P6, HIGH);
      }
      else if (RemoteXY.pushSwitch_1 == 0 && RemoteXY.joystick_y <= 25 && RemoteXY.joystick_y >= -25){
        Serial.println("BELOK Kanannn");

        digitalWrite(P2, HIGH);
        digitalWrite(P3, HIGH);
        digitalWrite(P4, LOW);
        digitalWrite(P5, HIGH);
        digitalWrite(P6, HIGH);
      }
      else if (RemoteXY.pushSwitch_1 == 1 && RemoteXY.joystick_y <= 25 && RemoteXY.joystick_y >= -25){
        Serial.println("SLIDE Kanannn");

        digitalWrite(P2, HIGH);
        digitalWrite(P3, HIGH);
        digitalWrite(P4, LOW);
        digitalWrite(P5, HIGH);
        digitalWrite(P6, LOW);
      }
      else if (RemoteXY.joystick_y < -25){
        Serial.println("SERONG KANANANNNN BAWAHHH");

        digitalWrite(P2, HIGH);
        digitalWrite(P3, HIGH);
        digitalWrite(P4, LOW);
        digitalWrite(P5, LOW);
        digitalWrite(P6, HIGH);
      }
    }

    if(RemoteXY.joystick_x == 0 && RemoteXY.joystick_y == 0) {
      digitalWrite(P2, HIGH);
      digitalWrite(P3, HIGH);
      digitalWrite(P4, HIGH);
      digitalWrite(P5, HIGH);
      digitalWrite(P6, HIGH);
      Serial.print("ON STOP");
    }


  } else {
      digitalWrite(P1, HIGH);
      digitalWrite(P2, HIGH);
      digitalWrite(P3, HIGH);
      digitalWrite(P4, HIGH);
      digitalWrite(P5, HIGH);
      digitalWrite(P6, HIGH);
      Serial.print("OFF STOP");
  }
   
}
