#include <Wire.h>


///////////////////////////////BLYNK///////////////////////////////////////
//#define BLYNK_DEBUG // Optional, this enables lots of prints
//Tenda_1A2E08
#define BLYNK_PRINT Serial
#define BLYNK_MAX_READBYTES 1024
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char auth[] = "d7bbe02e404f4a469dec9543c0887073";
char ssid[] = "Tenda_1A2E08";
char pass[] = "12345678";
#define EspSerial Serial
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
BlynkTimer timer;
/////////////////////////////////////////////////////////////////////////






//Blynk timed virtual pins
/*
  BLYNK_READ(V0) {
  Blynk.virtualWrite(0, y);
  }
  BLYNK_READ(V1) {
  Blynk.virtualWrite(1, x);
  }
  BLYNK_READ(V2) {
  Blynk.virtualWrite(2, distance);
  }

  BLYNK_READ(V3) {
  Blynk.virtualWrite(3, km);
  }


  BLYNK_READ(V5) {
  Blynk.virtualWrite(5, inFence);
  }

  BLYNK_READ(V6) {
  Blynk.virtualWrite(6, npol);
  }
*/
byte manual = 0;
byte lr = 0;
byte ud = 0;
/////add to fence//////////////////////////
BLYNK_WRITE(0) {
  if (param.asInt() == 1) {
    manual = 1;
    //digitalWrite(LED_BUILTIN, HIGH);

  }
  else {
    manual = 0;

  }
}

BLYNK_WRITE(1) {
  lr = param.asInt();

}

BLYNK_WRITE(2) {
  ud = param.asInt();

}






///////////////MAIN LOOP/////////////////////////////
//Blynk pushed virtual pin // all loop functions here
void myTimerEvent() {
  if (manual == 1)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
  Wire.beginTransmission(8);
  Wire.write(manual);
  Wire.write(lr);
  Wire.write(ud);
  Wire.endTransmission();

}//mytimer MAIN LOOP
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////








void setup() {
  Wire.begin(9);                // join i2c bus with address #9
  //Wire.onReceive(receiveEvent); // register event

  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);

  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);


  timer.setInterval(100L, myTimerEvent);

}



void loop()
{
  Blynk.run();
  timer.run();
}








