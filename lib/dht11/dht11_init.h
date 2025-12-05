#ifndef DHT11_INIT_H
#define DHT11_INIT_H

typedef struct {
    float airHumid;
    float airTemp;
} dht11_object;


// Initialization function for DHT11 module
void dht11_init(void);

dht11_object returnDHT11Readings(void);

#endif // DHT11_INIT_H
