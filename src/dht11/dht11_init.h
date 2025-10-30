#ifndef DHT11_INIT_H
#define DHT11_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float airhumid;
    float airtemp;
} dht11_object;




// Initialization function for DHT11 module
void dht11_init(void);

dht11_object returnDHT11Readings(void);

#ifdef __cplusplus
}
#endif

#endif // DHT11_INIT_H
