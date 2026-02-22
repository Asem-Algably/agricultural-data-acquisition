#include "soilHumid_config.h"
#include "soilHumid_init.h"
#include "soilHumid_priv.h"
#include "includes.h"


void soilHumid_init(void){
    // Initialization code for soil humidity module
}

float returnSoilHumid(void){
    if(disable_sensors == 1U){return 3.14f;}

    int value = analogRead(SOIL_HUMID_PIN);
    
    // check if the sensor is available
    if(value > 3900 || value < 100){
        (serial_output == 1U) ? Serial.println("Soil humidity sensor not available on this board") : 1;
        return -1.0f; // Return an error value
    }
    
    // Map the analog value to a humidity percentage
    float humidity = map(value, 0, 4095, 100, 0);
    return humidity;
}