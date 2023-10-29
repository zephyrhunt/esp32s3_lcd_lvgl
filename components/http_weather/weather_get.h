#ifndef _WEATHER_GET_H
#define _WEATHER_GET_H
#include "stdint.h"
typedef struct {
  char day_weather[20];
  char night_weather[20];

  char date[20];
//  char temp_high[6];
//  char temp_low[6];
    int16_t temp_high;
    int16_t temp_low;

  uint8_t day_code; // reference https://docs.seniverse.com/api/start/code.html
  uint8_t night_code;
}WeatherInfo_t;

extern WeatherInfo_t weather_info;
void WEATHER_HttpInit();
uint8_t WEATHER_HttpGet();
#endif
