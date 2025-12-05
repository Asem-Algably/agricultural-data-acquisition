// main component library
#include <dht11.h>
#include "types.h"
#include "dht11_config.h"
#include "dht11_init.h"
#include "dht11_priv.h"

dht11 DHT11;
extern board_t board_systemBoards[];

void dht11_init(void){
    // No special init required for this library
}

dht11_object returnDHT11Readings(void){

    if(disable_sensors == 1U){return (dht11_object){3.14f, 3.14f};}

    int chk = DHT11.read(DHT11PIN);

    dht11_object readings;
    readings.airHumid = (float)DHT11.humidity;
    readings.airTemp = (float)DHT11.temperature;

    return readings;
}
