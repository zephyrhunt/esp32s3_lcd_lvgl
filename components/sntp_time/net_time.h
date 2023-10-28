#ifndef _NET_TIME_H
#define _NET_TIME_H

extern time_t now;
extern struct tm timeinfo;
uint8_t SNTP_TimeUpdate();
#endif
