// main file includes
#include "reefPlusFirmware_config.h" 
#include "reefPlusFirmware_priv.h"

// library files includes
#include "./src/userLib/types.h"

// services includes
#include "./src/dht11/dht11_init.h"
#include "./src/soilHumid/soilHumid_init.h"
#include "./src/networkServices/networkServices_init.h"

void setup() {
  Serial.begin(115200);
}


void loop() {
  Serial.println("Reading Soil Humidity...");
  delay(2000);
}
