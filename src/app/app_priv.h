#ifndef APP_PRIV_H
#define APP_PRIV_H

#include "includes.h"

// Private function prototypes and definitions for app module    
sensorsData_t app_collectSensorData(void);
void clearSysArr();
void app_printBoardsData();

#endif // APP_PRIV_H