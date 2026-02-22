#include "includes.h"


#ifndef POSTSERVICES_INIT_H
#define POSTSERVICES_INIT_H

void postServices_init();

bool postServices_postData(sensorsData_t data, u8 boardNum);

#endif // POSTSERVICES_INIT_H