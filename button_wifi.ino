#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "uTimerLib.h"

WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.108", 1883);
Adafruit_MQTT_Publish bouttonPub(&mqttClient, "/boutton");
int compteur = 0;

void bouttonStatut() {
    int down = digitalRead(27);
    int up = digitalRead(26);

    if(up == 1){
      compteur += 1;
      bouttonPub.publish(compteur);

      }
    if(down == 1){
      compteur -= 1;
      bouttonPub.publish(compteur);
      }      
}

void setup() {
Serial.begin(115200);


WiFi.begin("createch2019", "createch2019");
delay(4000);

pinMode(27, INPUT); 
pinMode(26, INPUT); 

TimerLib.setInterval_s(bouttonStatut, 0.5);
}

void loop() {

if (mqttClient.connected()) {
    mqttClient.processPackets(10000);
    mqttClient.ping();
  } else {
    mqttClient.disconnect();
    mqttClient.connect();
  }

}
