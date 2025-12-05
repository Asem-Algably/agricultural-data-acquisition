#include "reefPlusFirmware_config.h" 
#include "reefPlusFirmware_priv.h"
#include "includes.h"
#include "app_bodge_config.h"
#include "../lib/app/app_config.h"



void setup() {
  Serial.begin(115200);
  delay(20);
  app_init();
}


void loop() {
  if (boardID == 1) {
    app_masterTask();
    Serial.println("                           ");
    Serial.println("***************************");
    Serial.println("***** cycle completed *****");
    Serial.println("***************************");
    Serial.println("                           ");
  }
}
