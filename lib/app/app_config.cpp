#include "app_config.h"
#include "app_priv.h"
#include "app_init.h"
#include "types.h"

const board_t board_systemBoards[] = {
    {
        "BOARD_001",
        "DHT11_001",
        "DHT11_001",
        "SOIL_001",
        11,      // DHT11 data pin
        34      // Soil humidity sensor pin (ESP32 ADC pin)
    },
    {
        "BOARD_002",
        "DHT11_002",
        "DHT11_002",
        "SOIL_002",
        11,      // DHT11 data pin
        34      // Soil humidity sensor pin (ESP32 ADC pin)
    },
    {
        "BOARD_003",
        "DHT11_003",
        "DHT11_003",
        "SOIL_003",
        11,      // DHT11 data pin
        34      // Soil humidity sensor pin (ESP32 ADC pin)
    }
};