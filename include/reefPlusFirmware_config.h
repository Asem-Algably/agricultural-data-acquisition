#ifndef REEF_PLUS_FIRMWARE_CONFIG_H
#define REEF_PLUS_FIRMWARE_CONFIG_H

#include "reefPlusFirmware_priv.h"
#include "src/userLib/types.h"

// Configuration settings for Reef Plus firmware
#define boardsChainLength 3

// testing modes
#define disable_sensors (1U) // set to (1u) to disable sensors for testing purposes 
#define serial_output   (1U) // set to (1u) to enable serial output for debugging purposes
// configuration for the board
#define boardID    1
#define boardRole  RoleMaster

#endif // REEF_PLUS_FIRMWARE_CONFIG_H