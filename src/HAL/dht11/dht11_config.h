#ifndef DHT11_CONFIG_H
#define DHT11_CONFIG_H
#include "includes.h"
// Configuration settings for DHT11 module

// Define the GPIO pin used for DHT11 data
#define DHTPIN board_systemBoards[boardID-1].dht11DataPin
#define DHTTYPE    DHT11

#endif // DHT11_CONFIG_H
