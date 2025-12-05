#include "soilHumid_config.h"
#include "soilHumid_init.h"
#include "soilHumid_priv.h"
#include "../../include/types.h"
#include <Arduino.h>

extern const board_t board_systemBoards[];

void soilHumid_init(void){
    // Initialization code for soil humidity module
}

float returnSoilHumid(void){
    if(disable_sensors == 1U){return 3.14f;}

    int value = analogRead(SOIL_HUMID_PIN);

    // Map the analog value to a humidity percentage
    float humidity = map(value, 0, 4095, 100, 0);
    return humidity;
}