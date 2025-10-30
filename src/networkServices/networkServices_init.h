#ifndef NETWORK_SERVICES_INIT_H
#define NETWORK_SERVICES_INIT_H

#include "userLib/types.h"

typedef struct {
    char packetType;
    dht11_object dht11;
    float soilHumid;
    int dht11ID;
    int soilHumidID;
    int boardID;
} networkServices_object;

// Initialization function for network services module
int networkServices_init(void);
int networkServices_upstreamPacket(networkServices_object);
int networkServices_downstreamPacket(networkServices_object);

#endif // NETWORK_SERVICES_INIT_H