// main component library
#include <dht11.h>

#include "dht11_config.h"
#include "dht11_init.h"
#include "dht11_priv.h"

dht11 DHT11;

void dht11_init(void){
    // No special init required for this library
}

dht11_object returnDHT11Readings(void){
    int chk = DHT11.read(DHT11PIN);

    dht11_object readings;
    readings.airhumid = (float)DHT11.humidity;
    readings.airtemp = (float)DHT11.temperature;

    return readings;
}
