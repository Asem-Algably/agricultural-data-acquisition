#include "reefPlusFirmware_config.h" 
#include "reefPlusFirmware_priv.h"
#include "includes.h"



void setup() {
  Serial.begin(115200);
  delay(20);
  app_init();
}


void loop() {
  if (boardID == 1) {
    app_masterTask();
  }
}
