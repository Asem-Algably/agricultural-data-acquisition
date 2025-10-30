#ifndef TYPES_H
#define TYPES_H

// Module init headers
#include "../dht11/dht11_init.h"
#include "../soilHumid/soilHumid_init.h"
#include "../networkServices/networkServices_init.h"
#include "../../reefPlusFirmware_config.h"

#include <Arduino.h>

typedef struct {
    int id;
    float temperature;
    float soilHumid;
    float airhumid;
} state;

typedef struct {
    int commandId;
    state stateData;
} command;

#endif // TYPES_H