// main file includes
#include <Arduino.h>
#include "reefPlusFirmware_config.h" 
#include "reefPlusFirmware_priv.h"

// library files includes
#include "./src/userLib/types.h"

// services includes
#include "./src/dht11/dht11_init.h"
#include "./src/soilHumid/soilHumid_init.h"
#include "./src/networkServices/networkServices_init.h"

#include "./src/app/app_init.h"

// Create DHT11 instance

void setup() {
  Serial.begin(9600);
}


void loop() {
  // Read the Analog Input
  int value = returnSoilHumid();
  Serial.print("value is ");
  Serial.println(value);
}
