// main component library
#include <dht11.h>
#include "../../include/types.h"
#include "dht11_config.h"
#include "dht11_init.h"
#include "dht11_priv.h"

dht11 DHT11;
extern const board_t board_systemBoards[];

void dht11_init(void){
    // No special init required for this library
}

dht11_object returnDHT11Readings(void){

    if(disable_sensors == 1U){return (dht11_object){2.71f, 2.71f};}

    int chk = DHT11.read(DHT11PIN);

    dht11_object readings;
    readings.airHumid = (float)DHT11.humidity;
    readings.airTemp = (float)DHT11.temperature;

    return readings;
}
