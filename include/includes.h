#ifndef INCLUDES_H
#define INCLUDES_H

// main general headers includes
#include "./reefPlusFirmware_config.h"
#include "./reefPlusFirmware_priv.h"
#include "./types.h"

// arduino and esp32 related includes
#include <string>
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <dht11.h>

// HAL includes
#include "HAL/dht11/dht11_init.h"
#include "HAL/soilHumid/soilHumid_init.h"
#include "HAL/networkServices/networkServices_init.h"
#include "HAL/postServices/postServices_init.h"

// app includes
#include "app/app_init.h"

// MCAL includes
#include "MCAL/esp_now/esp_now_init.h"

#endif // INCLUDES_H