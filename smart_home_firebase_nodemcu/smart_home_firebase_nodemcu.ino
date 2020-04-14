#include <ESP8266WiFi.h>;
#include <FirebaseArduino.h> 
// Set these to run example.
#define FIREBASE_HOST "Firebase_host_name"
#define FIREBASE_AUTH "Authentication ti=oken"
#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "wifi_password"
String status,on,colour;
void setup() {
Serial.begin(9600);
pinMode(D4, OUTPUT);
pinMode(D5,OUTPUT);
pinMode(D6,OUTPUT);
// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
// get value
status = Firebase.getString("status");
if(status!=NULL){
 Firebase.setString("ButtonStatus","on");
 Serial.println("ButtonStatus is on"); 
 }
else{
on = Firebase.getString("on");
colour = Firebase.getString("colour");
if(on=="1"){
  if(colour=="red"){
    digitalWrite(D4,HIGH);
    Serial.println("RED LED ON");
  }
  else if(colour=="green"){
    digitalWrite(D5,HIGH);
    Serial.println("GREEN LED ON");
  }
  else{
    digitalWrite(D6,HIGH);
    Serial.println("BLUE LED ON");
  }
}
else {
  if(colour=="red"){
    Serial.println("RED LED OFF");
    digitalWrite(D4,LOW);
  }
  else if(colour=="green"){
    digitalWrite(D5,LOW);
    Serial.println("GREEN LED OFF");
  }
  else{
    digitalWrite(D6,LOW);
    Serial.println("BLUE LED OFF");
  } 
return;
}
}
}
