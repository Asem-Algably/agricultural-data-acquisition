#ifndef NETWORK_SERVICES_INIT_H
#define NETWORK_SERVICES_INIT_H
#include "types.h"

// Initialization function for network services module
int networkServices_init(void);
int networkServices_upstreamPacket(packet_t packet);
int networkServices_downstreamPacket(packet_t packet);
void receive_NetworkServices_procedure();

#endif // NETWORK_SERVICES_INIT_H