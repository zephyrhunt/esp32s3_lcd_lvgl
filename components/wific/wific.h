#ifndef _WIFI_CONNECT_H
#define _WIFI_CONNECT_H

#include "stdint.h"
void WIFI_StaInit(void);
uint8_t WIFI_GetConnectStatus();
uint16_t WIFI_Scan(void);

#endif
