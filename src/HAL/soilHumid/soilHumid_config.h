#ifndef SOIL_HUMID_CONFIG_H
#define SOIL_HUMID_CONFIG_H
#include "includes.h"

// Define the ADC channel used for soil humidity measurement
#define SOIL_HUMID_PIN board_systemBoards[boardID-1].soilHumiditySensorPin

#endif // SOIL_HUMID_CONFIG_H