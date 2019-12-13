#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// On prend sur port M1 l'actionneur horizontal
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
// On prend sur M2 l'actionneur vertical
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  Motor1->setSpeed(150);
  Motor1->run(FORWARD);
  // turn on motor
  Motor1->run(RELEASE);

  Motor2->setSpeed(150);
  Motor2->run(FORWARD);
  // turn on motor
  Motor2->run(RELEASE);
}

void loop() {
int i=0;

   Motor1->run(FORWARD);
   for (i=0; i<=255; i++) {
     Motor1->setSpeed(i);  
     delay(20); // a voir si modifier
   }

   delay(3000); // modifier pour le temps de sortie du canon

   for (i=255; i>=0; i--) {
     Motor1->setSpeed(i);  
     delay(20);
   }   
   Motor1->setSpeed(0);
// lancer sequence : lever canon

Motor2->run(BACKWARD);
Motor2 ->setSpeed(150);       //monter
delay(1000);

Motor2->setSpeed(0);          //attendre
delay(300);

Motor2->run(FORWARD);         //descendre
Motor2 ->setSpeed(150);
delay(1500);

Motor2->setSpeed(0);          //attendre
delay(300);

Motor2->run(BACKWARD);        //monter
Motor2 ->setSpeed(150);
delay(1000);

Motor2->setSpeed(0);
delay(1000);

// jouer son de tir




Motor1->run(BACKWARD);          // sequence de recul
   for (i=255; i>=0; i=i-3) {
     Motor1->setSpeed(i);  
     delay(5);
   }  
   delay(10000);
  Motor1->setSpeed(0);

  Motor2->run(BACKWARD);          // sequence de recul
   for (i=255; i>=0; i=i-3) {
     Motor1->setSpeed(i);  
     delay(5);
   }  
   delay(10000);
  Motor2->setSpeed(0);
}