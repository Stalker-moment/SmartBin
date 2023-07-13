#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Deklerasi Pin Relay
#define P1 D0 //Master Switch
#define P2 D1 //reset count

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPLRXpO506W"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "rOFxKOYyuzloQ3wOZdR-KIWQg6l3APK3"

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "test";
char pass[] = "Kata Sandi";

//Deklarasi untuk parsing data
String dataIn;
String dt[25];
int i;
boolean parsing=false;


//Data String
String atas = "";
String dalam = "";
String depan = "";
String kanan = "";
String tengah = "";
String kiri = "";
String jalanke = "";
String temp = "";
String humi = "";
String counter = "";
String isAuto = "";

int tanklevel;
int TankCapacity = 38;

BlynkTimer timer;

BLYNK_WRITE(V0) {
  bool value1 = param.asInt();
  if (value1 == 1) {
    digitalWrite(P1, LOW);
  } else {
    digitalWrite(P1, HIGH);
  }
}

BLYNK_WRITE(V9) {
  bool value2 = param.asInt();
  if (value2 == 1) {
    digitalWrite(P2, LOW);
  } else {
    digitalWrite(P2, HIGH);
  }
}

void sendSensor()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, atas);
  Blynk.virtualWrite(V2, dalam+" Cm");
  Blynk.virtualWrite(V3, depan); 
  Blynk.virtualWrite(V4, counter+"|"+isAuto); 
  Blynk.virtualWrite(V5, temp+" °C");  
  Blynk.virtualWrite(V6, humi+" %");  
  Blynk.virtualWrite(V7, kanan+"|"+tengah+"|"+kiri+"|"+jalanke);  
  Blynk.virtualWrite(V8, String(tanklevel)+" %");  
}

void setup() {
   Serial.begin(9600);
   dataIn="";

  //set mode
   pinMode(P1, OUTPUT);
   pinMode(P2, OUTPUT);

   //set booting
   digitalWrite(P1, HIGH);
   digitalWrite(P2, HIGH);

       //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

}

void loop() {
   Blynk.run();
  timer.run();
    if(Serial.available()>0) {
    char inChar = (char)Serial.read();
    dataIn += inChar;
    if (inChar == '\n') {
    parsing = true;
  }
}
 
if(parsing){
    parsingData();
    parsing=false;
    dataIn="";
  }
}

void parsingData(){
int j=0;
 
//kirim data yang telah diterima sebelumnya
Serial.print("data masuk : ");
Serial.print(dataIn);
 
//inisialisasi variabel, (reset isi variabel)
dt[j]="";
//proses parsing data
for(i=1;i<dataIn.length();i++){
//pengecekan tiap karakter dengan karakter (#) dan (,)
if ((dataIn[i] == '#') || (dataIn[i] == ','))
{
//increment variabel j, digunakan untuk merubah index array penampung
j++;
dt[j]="";       //inisialisasi variabel array dt[j]
}
else
{
//proses tampung data saat pengecekan karakter selesai.
dt[j] = dt[j] + dataIn[i];
}
}
 
//kirim data hasil parsing
Serial.print("data 1 (distance atas) : ");
Serial.println(dt[0]);
Serial.print("data 2 (distance dalam) : ");
Serial.println(dt[1]);
Serial.print("data 3 (distance depan) : ");
Serial.println(dt[2]);
Serial.print("data 4 (data kanan) : ");
Serial.println(dt[3]);
Serial.print("data 5 (data tengah) : ");
Serial.println(dt[4]);
Serial.print("data 6 (data kiri) : ");
Serial.println(dt[5]);
Serial.print("data 7 (Index Jalan) : ");
Serial.println(dt[6]);
Serial.print("data 8 (Temp) : ");
Serial.println(dt[7]);
Serial.print("data 9 (Humidity) : ");
Serial.println(dt[8]);
Serial.print("data 10 (Count) : ");
Serial.println(dt[9]);
Serial.print("data 11 (Auto?) : ");
Serial.println(dt[10]);
Serial.print("\n\n");

//Wrapping data untuk di definisikan
atas = dt[0];
dalam = dt[1];
depan = dt[2];
kanan = dt[3];
tengah = dt[4];
kiri = dt[5];
jalanke = dt[6];
temp = dt[7];
humi = dt[8];
counter = dt[9];
tanklevel = map(dalam.toInt(), TankCapacity, 10, 0, 100);
isAuto = dt[10];

//------------------Ga usah Delay--------------------//
}

