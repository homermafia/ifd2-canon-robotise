#include <MQTT.h>
#include <WiFi.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

MQTTClient client;
WiFiClient wificlient;

const char ssid[] = "Crunch LAB";
const char pass[] = "90xV@FsT";
char hostname[14] = "192.168.1.15";//MQTT Broker IP
int signal=0;

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
    signal=1;
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

  if (!client.connected()) {
  connect();
  }

;
if (signal == 1){
                                                                      // début séquence
  int i=0;

    Motor1->run(FORWARD);
    for (i=0; i<=255; i++) {
      Motor1->setSpeed(i);  
      delay(20); // a voir si modifier
    }

    delay(7000); // modifier pour le temps de sortie du canon

    for (i=255; i>=0; i--) {
      Motor1->setSpeed(i);  
      delay(20);
    }   
    Motor1->setSpeed(0);
    // lancer sequence : lever canon

    Motor2->run(FORWARD);
    Motor2 ->setSpeed(255);       //monter
    delay(16000);

    Motor2->setSpeed(0);          //attendre
    delay(2000);

    Motor2->run(BACKWARD);         //descendre
    Motor2 ->setSpeed(200);
    delay(4000);

    Motor2->setSpeed(0);          //attendre
    delay(2000);

    Motor2->run(FORWARD);        //monter
    Motor2 ->setSpeed(200);
    delay(8000);

    Motor2->setSpeed(0);
    delay(2000);

    // jouer son de tir


    Motor1->run(BACKWARD);          // sequence de recul car tir
      for (i=255; i>=0; i=i-3) {
        Motor1->setSpeed(i);  
        delay(20);
      }
      Motor1->setSpeed(0);
      delay(5000);

      // jouer son explosion

      delay(5000);
      Motor2->run(BACKWARD);          // Remise à l'horizontale
      Motor2->setSpeed(255);
      delay(16000);                  // Trouver le temps pour mettre a l'horizontal
      Motor2->setSpeed(0);

      Motor1->run(BACKWARD);          // rentrer canon
      for (i=0; i<=255; i++) {
        Motor1->setSpeed(i);  
        delay(20);                   // a voir si modifier
      }
      delay(15000);
        Motor1->setSpeed(0);

        // Vérifier coordonnées et jouer le son correspondant (victoire ou défaite)

        delay(20000);
        
        signal = 0;
                                                                      // fin séquence
}
else {
 Serial.println("En attente de déclenchement");
}
delay(1000);
}


  