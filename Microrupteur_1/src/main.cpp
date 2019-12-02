#include "Arduino.h"


int button = 4; // pull pin of uno r3
int button2 = 5;

void setup() {
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  Serial.begin(9600);
}

void loop() {

  //PULL_UP force to one
  int stateb = digitalRead(button);
  Serial.print("Button State : ");
  Serial.println(stateb);
  delay(20);

  //int stateb2 = digitalRead(button2);
  //Serial.print("Button2 State : ");
  //Serial.println(stateb2);
  //delay(20);

}