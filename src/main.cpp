#include "includes.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(20);
  app_init();
  Serial.println("setup code finished");
}


void loop() {
  Serial.println("Starting new cycle");
  if (boardID == 1) {
    Serial.println("app master task calling");
    app_masterTask();
    Serial.println("app master task had been called");
    delay(2000);
    Serial.println("                           ");
    Serial.println("***************************");
    Serial.println("***** cycle completed *****");
    Serial.println("***************************");
    Serial.println("                           ");
  }
}
