#include "soilHumid_config.h"
#include "soilHumid_init.h"
#include "soilHumid_priv.h"
#include <Arduino.h>

void soilHumid_init(void){
    // Initialization code for soil humidity module
}

float returnSoilHumid(void){

    int value = analogRead(SOIL_HUMID_PIN);

    // Map the analog value to a humidity percentage
    float humidity = map(value, 0, 4095, 100, 0);
    return humidity;
}