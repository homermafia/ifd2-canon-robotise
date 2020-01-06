#include <Arduino.h>
#include <MQTT.h>
#include <WiFi.h>

MQTTClient client;
WiFiClient wificlient;

 //char ssid[] = "Crunch LAB";
 //char pass[] = "90xV@FsT";
 char ssid[] = "utbm_visiteurs";
 char pass[] = "";
 const char hostname[14] = "172.17.14.254";//MQTT Broker IP

unsigned long lastMillis = 0;

void connect() {

  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("connecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print("+");
    delay(1000);
  }

  Serial.println("\nconnected!");

}

//void messageReceived(String &topic, String &payload) {
//  Serial.println("incoming: " + topic + " - " + payload);
//}

int button = 4;
int compteur = 0;
char etat_z[10]="";

// brancher NC (bleu) sur port A5
// NO (jaune) sur port A4
// C (rouge) sur port 3V

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  client.begin(hostname, 1883, wificlient);

  connect();

  pinMode(button, INPUT);
  sprintf(etat_z, "%d", 0);

  client.publish("/LCDB/canon/detonateur", etat_z);
  Serial.print("etat:");
  Serial.println(0, 1);
}


float etat = 0;
float etatb = 1;
void loop()
{
  etat=0;
  etatb = digitalRead(button);
  delay(300);

  while (etatb != 1)
  {
    compteur= compteur +1;
    delay(100);
    etatb = digitalRead(button);
  }

  if (compteur >= 2) {
    Serial.println ("lancement de la séquence de tir !!");
    etat=1;
  }
   delay (500);

   if (!etatb == 0)
   {
     compteur =0;
   }

 client.loop();

  if (!client.connected()) {
    connect();
  }

   char etat_m[10];

  // if (millis() - lastMillis > 100) {
  //   lastMillis = millis();
    
    
  //   sprintf(etat_m,"%f",etat);

  //   client.publish("/LCDB/canon/detonateur", etat_m);
  //   Serial.print("etat:");
  //   Serial.println(etat, 1);
  
  // } 
  if(etat==1)
  {
    sprintf(etat_m, "%f", etat);

    client.publish("/LCDB/canon/detonateur", etat_m);
    Serial.print("etat:");
    Serial.println(etat, 1);
  }
}