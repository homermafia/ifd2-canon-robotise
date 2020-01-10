#include <MQTT.h>
#include <WiFi.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

MQTTClient client;
WiFiClient wificlient;

const char ssid[] = "Crunch LAB";
const char pass[] = "90xV@FsT";
char hostname[14] = "192.168.1.15";//MQTT Broker IP
int prev_phase=0;
int phase = 0;

unsigned long lastMillis = 0;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// // On prend sur port M1 l'actionneur horizontal
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
// // On prend sur M2 l'actionneur vertical
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);

void connect() {

  Serial.println("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(1000);
  }

  Serial.println("connecting...");
  while (!client.connect("canon1", "try", "try")) {
  Serial.print("+");
  delay(1000);
}

Serial.println("\nconnected!");

client.subscribe("/LCDB/canon/canon");

}


void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: ");
  Serial.println(topic);
  Serial.println(" - ");
  Serial.println(payload);
  if (payload == "1"){
    if (phase == 0) {
      phase = 1;
      prev_phase = 0;
      lastMillis = millis();
    }
  }
}

void setup()
{
  AFMS.begin();  // create with the default frequency 1.6KHz
  AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  Motor1->setSpeed(150);
  Motor1->run(FORWARD);
  // turn on motor
  Motor1->run(RELEASE);
  Motor2->setSpeed(150);
  Motor2->run(FORWARD);
  // turn on motor
  Motor2->run(RELEASE);

  Serial.begin(9600);
  Serial.println("WELCOME");
  WiFi.begin(ssid, pass);
  Serial.println();
  client.begin(hostname, 1883, wificlient);
  client.onMessage(messageReceived);

  connect();

  
}

 

void loop()
{
  client.loop();

  if (phase == 0){ // canon au repos
    if (!client.connected()) {
      connect();
    }
  }
  else {
    // début séquence

    switch (phase) {
      case 1: { // acceleration avant
        if (phase != prev_phase) {
          Motor1->run(FORWARD);
          prev_phase = 1;
        }
        if (millis() - lastMillis > 5100) {
          Motor1->setSpeed(255);
          phase = 2;
        }
        else {
          Motor1->setSpeed((millis() - lastMillis)*255/5100);
        }
      }
      break;
      case 2: { // vitesse constante avant
        if (millis() - lastMillis > 7000) {
          phase = 3;
        }
        else {
          prev_phase = 2;
        }
      }
      break;
      case 3: { // deceleration
        if (millis() - lastMillis > 5100) {
          Motor1->setSpeed(0);
          phase = 4;
        }
        else {
          Motor1->setSpeed(255 - (millis() - lastMillis)*255/5100);
          prev_phase = 3;
        }
      }
      break;
      case 4: { // lever canon
        if (phase != prev_phase) {
          Motor2->run(FORWARD);
          Motor2->setSpeed(255);
          prev_phase = 4;
        }
        if (millis() - lastMillis > 16000) {
          Motor2->setSpeed(0);
          phase = 5;
        }
      }
      break;
      case 5: { // attendre 2 secondes
        if (millis() - lastMillis > 2000) {
          phase = 6;
        }
        else {
          prev_phase = 5;
        }
      }
      break;
      case 6: { // descendre canon
        if (phase != prev_phase) {
          Motor2->run(BACKWARD);
          Motor2->setSpeed(200);
          prev_phase = 6;
        }
        if (millis() - lastMillis > 4000) {
          Motor2->setSpeed(0);
          phase = 7;
        }
      }
      break;
      case 7: { // attendre 2 secondes
        if (millis() - lastMillis > 2000) {
          phase = 8;
        }
        else {
          prev_phase = 7;
        }
      }
      break;
      case 8: { // lever canon
          if (phase != prev_phase) {
            Motor2->run(FORWARD);
            Motor2->setSpeed(200);
            prev_phase = 8;
          }
          if (millis() - lastMillis > 8000) {
            Motor2->setSpeed(0);
            phase = 9;
          }
      }
      break;
      case 9: { // attendre 2 secondes
        if (millis() - lastMillis > 2000) {
          phase = 10;
        }
        else {
          prev_phase = 9;
        }
      }
      break;
      case 10: { // tir du canon (recul du canon)
        if (phase != prev_phase) {
          Motor1->run(BACKWARD);
          // jouer le son de tir ici
          prev_phase = 10;
        }
        if (millis() - lastMillis > 2000) {
          Motor1->setSpeed(0);
          phase = 11;
        }
        else {
          Motor1->setSpeed(255 - (millis() - lastMillis)*255/2000);
        }
      }
      break;
      case 11: { // jouer son explosion après 5 secondes
        if (millis() - lastMillis > 5000) {
          // jouer le son d'explosion ici
          phase = 12;
        }
        else {
          prev_phase = 11;
        }
      }
      break;
      case 12: { // attendre 5 secondes
        if (millis() - lastMillis > 5000) {
          phase = 13;
        }
        else {
          prev_phase = 12;
        }
      }
      break;
      case 13: { // descendre canon (remise à l'horizontale)
        if (phase != prev_phase) {
          Motor2->run(BACKWARD);
          Motor2->setSpeed(255);
          prev_phase = 13;
        }
        if (millis() - lastMillis > 16000) {
          Motor2->setSpeed(0);
          phase = 14;
        }
      }
      break;
      case 14: { // acceleration arrière
        if (phase != prev_phase) {
          Motor1->run(BACKWARD);
          prev_phase = 14;
        }
        if (millis() - lastMillis > 5100) {
          Motor1->setSpeed(255);
          phase = 15;
        }
        else {
          Motor1->setSpeed((millis() - lastMillis)*255/5100);
        }
      }
      break;
      case 15: { // vitesse constante arrière
        if (millis() - lastMillis > 15000) {
          phase = 16;
        }
        else {
          prev_phase = 15;
        }
      }
      break;
      case 16: { // vérification des coordonés rentré en jouer le son victoire ou defaite
        if (phase != prev_phase) {
          // vérifier les coordonnés et jouer le son ici
          Motor1->setSpeed(0);
          prev_phase = 16;
        }
        if (millis() - lastMillis > 10000) {
          phase = 0; // fin de la séquence, réinitialisation
        }
      }
      break;
    }
  }

  if (phase != prev_phase) {
    lastMillis = millis();
  }
}


  