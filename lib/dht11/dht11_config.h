#ifndef DHT11_CONFIG_H
#define DHT11_CONFIG_H
#include "../../include/reefPlusFirmware_config.h"
// Configuration settings for DHT11 module

// Define the GPIO pin used for DHT11 data
#define DHT11PIN board_systemBoards[boardID-1].dht11DataPin

#endif // DHT11_CONFIG_H
