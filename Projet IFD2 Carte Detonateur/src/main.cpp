#include <Arduino.h>
#include <MQTT.h>
#include <WiFi.h>

MQTTClient client;
WiFiClient wificlient;

const char hostname[13] = "172.17.11.7";//MQTT Broker IP

int button = 4; // pull pin of uno r3
// brancher NC (bleu) sur port A5
// NO (jaune) sur port A4
// C (rouge)sur port 3V

unsigned long lastMillis = 0;

void connect() 
{

  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("connecting...");
  while (!client.connect("arduino", "try", "try")) 
  {
    Serial.print("+");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
}

void messageReceived(String &topic, String &payload) 
{
  Serial.println("incoming: " + topic + " - " + payload);
}


void setup()
{
  Serial.begin(9600);
  Serial.println("WELCOME");
  WiFi.begin("utbm_visiteurs","");
  
  client.begin(hostname, 1883, wificlient);
  client.onMessage(messageReceived);

  connect();

  pinMode(button, INPUT);
}

void loop()
{
 client.loop();

  if (!client.connected()) 
  {
    connect();
  }
  
  int etat = digitalRead(button);
  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) 
  {
    lastMillis = millis();
    char etat_m[3];
    sprintf(etat_m,"%d",etat);
    client.publish("/LCDB/canonrobotise/etatdetonateur/microrupteur", "1");
    Serial.println(etat);
  }
}