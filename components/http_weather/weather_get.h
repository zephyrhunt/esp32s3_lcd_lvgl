#ifndef _WEATHER_GET_H
#define _WEATHER_GET_H
#include "stdint.h"
typedef struct {
  char weather[20];
  char date[20];
  char temp_high[6];
  char temp_low[6];
}WeatherInfo_t;

extern WeatherInfo_t weather_info;
void WEATHER_HttpInit();
uint8_t WEATHER_HttpGet();
#endif
