// main component library
#include "includes.h"
#include "./dht11_config.h"
#include "./dht11_init.h"
#include "./dht11_priv.h"

dht11 DHT11;
extern const board_t board_systemBoards[];

void dht11_init(void){
    // No special init required for this library
}

dht11_object returnDHT11Readings(void){

    if(disable_sensors == 1U){return (dht11_object){2.71f, 2.71f};}

    unsigned long startTime = millis();
    int chk;
    const unsigned long timeout = 1000; // 1 second timeout

    do {
        chk = DHT11.read(DHT11PIN);
        if (chk == DHTLIB_OK) break;
        delay(10);
    } while (millis() - startTime < timeout);

    dht11_object readings;
    if (chk == DHTLIB_OK) {
        readings.airHumid = (float)DHT11.humidity;
        readings.airTemp = (float)DHT11.temperature;
    } else {
        readings.airHumid = -1.0f; // Indicate error
        readings.airTemp = -1.0f;
    }

    return readings;
}
