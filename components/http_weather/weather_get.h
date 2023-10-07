#ifndef _WEATHER_GET_H
#define _WEATHER_GET_H

typedef struct {
  char weather[20];
  char date[20];
  char temp_high[6];
  char temp_low[6];
}WeatherInfo_t;

void WEATHER_HttpInit();
void WEATHER_HttpGet();
#endif
