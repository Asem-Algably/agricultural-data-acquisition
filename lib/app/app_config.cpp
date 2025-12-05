#include "app_config.h"
#include "app_priv.h"
#include "app_init.h"
#include "../../include/types.h"

const board_t board_systemBoards[] = {
    {
        "BOARD_001",
        "DHT11_001",
        "DHT11_001",
        "SOIL_001",
        11,      // DHT11 data pin
        34,      // Soil humidity sensor pin (ESP32 ADC pin)
        {0x14, 0x2B, 0x2F, 0xC1, 0xF5, 0x78} // MAC Address
    },
    {
        "BOARD_002",
        "DHT11_002",
        "DHT11_002",
        "SOIL_002",
        11,      // DHT11 data pin
        34,      // Soil humidity sensor pin (ESP32 ADC pin)
        {0xEC, 0x64, 0xC9, 0x7C, 0x0F, 0x98} // MAC Address
    },
    {
        "BOARD_003",
        "DHT11_003",
        "DHT11_003",
        "SOIL_003",
        11,      // DHT11 data pin
        34,      // Soil humidity sensor pin (ESP32 ADC pin)
        {0x14, 0x2b, 0x2f, 0xc0, 0xd1, 0xb8} // MAC Address
    }
};