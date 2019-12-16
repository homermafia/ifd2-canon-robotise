// #include <Arduino.h>
// #include <WiFi.h>
// #include <MQTT.h>

// MQTTClient client;
// WiFiClient wificlient;

// char ssid[] = "Crunch LAB";
// char pwd[] = "90xV@FsT";
// const char hostname[20] = "192.168.1.90";//MQTT Broker IP


// unsigned long lastMillis = 0;


// void printWifiStatus() {
//   // print the SSID of the network you're attached to:
//   Serial.print("SSID: ");
//   Serial.println(WiFi.SSID());

//   // print your WiFi shield's IP address:
//   IPAddress ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);

//   // print the received signal strength:
//   long rssi = WiFi.RSSI();
//   Serial.print("signal strength (RSSI):");
//   Serial.print(rssi);
//   Serial.println(" dBm");
// }





// void connect() {
// printWifiStatus();
//   Serial.print("checking wifi...");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print(".");
//     delay(1000);
//   }

//   Serial.print("connecting...");
//   while (!client.connect("arduino", "try", "try")) {
//     Serial.print("+");
//     delay(1000);
//   }

//   Serial.println("\nconnected!");

//   client.subscribe("/hello");
//   // client.unsubscribe("/hello");
// }

// void messageReceived(String &topic, String &payload) {
//   Serial.println("incoming: " + topic + " - " + payload);
// }


// void setup()
// {
//   Serial.begin(9600);
//   Serial.println("WELCOME");
//   WiFi.begin(ssid, pwd);
//   Serial.println();
//   Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

//   //dht.setup(12,DHT::DHT11); // data pin 12

  
//   client.begin(hostname, 1883, wificlient);
//   client.onMessage(messageReceived);

//   connect();
// }
// float temperature = 10;
// void loop()
// {
//  client.loop();

//   if (!client.connected()) {
//     connect();
//   }


//   // char hum[10];
  
// char temp[10];
//   // publish a message roughly every second.
//   if (millis() - lastMillis > 1000) {
//     lastMillis = millis();

//     temperature+=1;
//     sprintf(temp,"%f",temperature);
//     client.publish("/sensor/temp", temp);
//     Serial.print(temperature, 1);

//     // sprintf(temp,"%f",temperature);
//     // sprintf(hum,"%f",humidity);

//     // client.publish("/sensor/temp", temp);
//     // client.publish("/sensor/humidity", hum);

//     // Serial.print(dht.getStatusString());
//     // Serial.print("\t");
//     // Serial.print(humidity, 1);
//     // Serial.print("\t\t");
//     // Serial.print(temperature, 1);
//     // Serial.print("\t\t");
//     // Serial.println(dht.toFahrenheit(temperature), 1);
//   }

  
// }




// #include <MQTT.h>
// // #include <ESP8266WiFi.h>
// #include <WiFi.h>
// #include <driver/adc.h>

// MQTTClient client;
// WiFiClient wificlient;


//  char ssid[] = "Crunch LAB";
//  char pass[] = "90xV@FsT";
//  const char hostname[14] = "192.168.1.90";//MQTT Broker IP

// //const char ssid[] = "utbm_visiteurs";
// //const char pass[] = "";
// //const char hostname[15] = "172.17.24.105";//MQTT Broker IP
// //const char hostname[13] = "172.17.1.196";//MQTT Broker IP

// unsigned long lastMillis = 0;

// void connect() {

//   Serial.println("checking wifi...");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print(".");
//     delay(1000);
//   }

//   Serial.println("connecting...");
//   while (!client.connect("arduino", "try", "try")) {
//     Serial.print("+");
//     delay(1000);
//   }

//   Serial.println("\nconnected!");

//   client.subscribe("/hello");
//   // client.unsubscribe("/hello");
// }

// void messageReceived(String &topic, String &payload) {
//   Serial.println("incoming: " + topic + " - " + payload);
// }


// void setup()
// {
//   Serial.begin(9600);
//   Serial.println("WELCOME");
//   WiFi.begin(ssid, pass);
//   Serial.println();
//   Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  
//   client.begin(hostname, 1883, wificlient);
//   client.onMessage(messageReceived);

//   connect();
// }
// float temperature = 10;
// void loop()
// {
//  client.loop();

//   if (!client.connected()) {
//     connect();
//   }


// adc1_config_width(ADC_WIDTH_BIT_12);
//     adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0);
//     int light = adc1_get_raw(ADC1_CHANNEL_0);
//   // int light = analogRead(36);
//   //delay(dht.getMinimumSamplingPeriod());
  

//   // publish a message roughly every second.
//   if (millis() - lastMillis > 10000) {
//     lastMillis = millis();

//     client.publish("/sensor/temp", "10");


//     //Serial.print("\t\t");
//     //Serial.println(dht.toFahrenheit(temperature), 1);
//   }

  
// }
#include <Arduino.h>
#include <DHT.h>
#include <MQTT.h>
// #include <ESP8266WiFi.h>
#include <WiFi.h>
#include <driver/adc.h>

MQTTClient client;
WiFiClient wificlient;
DHT dht;

 //char ssid[] = "Crunch LAB";
 //char pass[] = "90xV@FsT";
 char ssid[] = "utbm_visiteurs";
 char pass[] = "";
 //char ssid[] = "theo";
 const char hostname[14] = "172.17.25.249";//MQTT Broker IP

//const char ssid[] = "utbm_visiteurs";
//const char pass[] = "";
//const char hostname[15] = "172.17.24.105";//MQTT Broker IP
//const char hostname[13] = "172.17.1.196";//MQTT Broker IP

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

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}


void setup()
{
  Serial.begin(9600);
  Serial.println("WELCOME");
  WiFi.begin(ssid, pass);

  dht.setup(4,DHT::DHT11); // data pin 12

  
  client.begin(hostname, 1883, wificlient);
  client.onMessage(messageReceived);

  connect();
}
float etat = 0;
void loop()
{
 client.loop();

  if (!client.connected()) {
    connect();
  }


adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0);
    int light = adc1_get_raw(ADC1_CHANNEL_0);
  // int light = analogRead(36);
  //delay(dht.getMinimumSamplingPeriod());

   //float humidity = dht.getHumidity();
   //float temperature = dht.getTemperature();
   char etat_m[10];
   //char hum[10];
   //char lightChar[10];
  

  // publish a message roughly every second.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    if(etat==0)
    {
      etat=1;
    }
    else
    {
      etat=0;
    }
    
    sprintf(etat_m,"%f",etat);
    //sprintf(hum,"%f",humidity);
        //sprintf(lightChar,"%d",light);

    client.publish("/LCDB/canon/detonateur", etat_m);
    //client.publish("/sensor/humidity", hum);
    //client.publish("/sensor/light", lightChar);

    //Serial.print(dht.getStatusString());
    //Serial.println("\thum:");
    //Serial.print(humidity, 1);
    Serial.print("etat:");
    Serial.println(etat, 1);
    //Serial.print("\t\tlight:");
    //Serial.println(light, 1);
    //Serial.print("\t\t");
    //Serial.println(dht.toFahrenheit(temperature), 1);
  }

  
}