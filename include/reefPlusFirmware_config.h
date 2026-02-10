#ifndef REEF_PLUS_FIRMWARE_CONFIG_H
#define REEF_PLUS_FIRMWARE_CONFIG_H

#include "reefPlusFirmware_priv.h"
#include "./types.h"

// testing modes
#define disable_sensors (0U) // set to (1u) to disable sensors for testing purposes 
#define serial_output   (1U) // set to (1u) to enable serial output for debugging purposes

// configuration for the board
#define boardID    1U

#endif // REEF_PLUS_FIRMWARE_CONFIG_H