#include <Arduino.h>
#include <MQTT.h>
#include <WiFi.h>

MQTTClient client;
WiFiClient wificlient;

 char ssid[] = "Crunch LAB";
 char pass[] = "90xV@FsT";
 //char ssid[] = "utbm_visiteurs";
 //char pass[] = "";
 const char hostname[14] = "192.168.1.15";//MQTT Broker IP

unsigned long lastMillis = 0;

void connect() {

  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("connecting...");
  while (!client.connect("toto", "try", "try")) {
    Serial.print("+");
    delay(1000);
  }

  Serial.println("\nconnected!");

}

int button = 4;
int compteur = 0;
char etat_z[10]="";

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  client.begin(hostname, 1883, wificlient);

  connect();

  pinMode(button, INPUT);
  sprintf(etat_z, "%d", 0);

  client.publish("/LCDB/canon/detonateur", etat_z);//chanel sur laquelle la carte publish
  Serial.print("etat:");
  Serial.println(0, 1);
}

int etat = 0;
int etatb = 1;
char etat_m[10];

void loop()
{
    if(etat==1)
  {
    delay(5000);
    etat=0;
    sprintf(etat_m, "%d", etat);

    client.publish("/LCDB/canon/detonateur", etat_m);//chanel sur laquelle la carte publish
    Serial.print("etat:");
    Serial.println(etat, 1);
  }
  etatb = digitalRead(button);
  compteur=0;

  while (etatb != 1&&compteur<3)
  {
    compteur= compteur +1;
    delay(100);
    etatb = digitalRead(button);
  }

  if (compteur >= 3) {
    Serial.println ("lancement de la séquence de tir !!");
    etat=1;
  }
   delay (300);

 client.loop();

  if (!client.connected()) {
    connect();
  }

  if(etat==1)
  {
    sprintf(etat_m, "%d", etat);

    client.publish("/LCDB/canon/detonateur", etat_m);//chanel sur laquelle la carte publish
    Serial.print("etat:");
    Serial.println(etat, 1);
  }
}