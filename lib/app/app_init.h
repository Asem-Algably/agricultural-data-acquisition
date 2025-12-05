#ifndef APP_INIT_H
#define APP_INIT_H
#include "../../include/types.h"

void app_init(void);
void app_onDataReceived(packet_t packet);


void app_masterTask(void);


#endif // APP_INIT_H