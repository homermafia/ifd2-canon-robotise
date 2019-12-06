#include "Arduino.h"


int button = 4; // pull pin of uno r3
// brancher NC (bleu) sur port A5
// NO (jaune) sur port A4
// C (rouge)sur port 3V

void setup() {
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  int etat = digitalRead(button);
  Serial.print("Button State : ");
  Serial.println(etat);
  delay(20);
}