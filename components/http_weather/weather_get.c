#include "weather_get.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "esp_log.h"

#define WEB_PATH "https://api.seniverse.com/v3/weather/daily.json?key=ScVuOBExK0jxY9pzd&location=wuhan&language=en"          // 天气获取路径
#define TAG "weather_get"



WeatherInfo_t weather_info;

/**
 * @brief 心知天气（seniverse） 天气各项数据结构体
 */
typedef struct{
	char *date;
	char *text_day;
	char *code_day;
	char *text_night;
	char *code_night;
	char *high;
	char *low;
	char *rainfall;
	char *precip;
	char *wind_direction;
	char *wind_direction_degree;
	char *wind_speed;
	char *wind_scale;
	char *humidity;

} user_seniverse_day_config_t;

/**
 * @brief 心知天气（seniverse） 数据结构体
 */
typedef struct {
	char *id;
	char *name;
	char *country;
	char *path;
	char *timezone;
	char *timezone_offset;
    user_seniverse_day_config_t day_config[3];/*这里的3是指心知天气URL中的 days=3*/
	char *last_update;

} user_seniverse_config_t;

/**
 * @brief 解析天气数据（JSON）
 *
 * @param analysis_buf 数据的存储空间
 * @return true 解析成功
 * @return false 解析失败
 */
static bool parse_json_data(const char *analysis_buf) {
    uint8_t i,j;
	uint8_t result_array_size = 0;
//	uint8_t daily_array_size = 0;

	cJSON *item = NULL;
	cJSON *root = NULL;
	cJSON *results_root = NULL;
	cJSON *daily_root = NULL;
	user_seniverse_config_t user_sen_config = {}; //会自动释放
    /* print the version */
	root = cJSON_Parse(analysis_buf);   /*json_data 为心知天气的原始数据*/
    if (!root)
    {
      printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	  return  0;
	}
    printf("%s\n\n", cJSON_Print(root));   /*将完整的数据以JSON格式打印出来*/
	cJSON *Presult = cJSON_GetObjectItem(root, "results");  /*results 的键值对为数组，*/

	result_array_size = cJSON_GetArraySize(Presult);  /*求results键值对数组中有多少个元素, 只有一个*/
    for(i = 0;i < result_array_size;i++)
    {
		cJSON *item_results = cJSON_GetArrayItem(Presult, i);

        char *sresults = cJSON_PrintUnformatted(item_results);
		results_root = cJSON_Parse(sresults);
		if (!results_root)
	    {
	      printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		  return  0;
		}
		cJSON *Plocation = cJSON_GetObjectItem(results_root, "location");

	    item = cJSON_GetObjectItem(Plocation, "id");
		user_sen_config.id = cJSON_Print(item);
	    item = cJSON_GetObjectItem(Plocation, "name");
		user_sen_config.name = cJSON_Print(item);
	    item = cJSON_GetObjectItem(Plocation, "country");
        user_sen_config.country = cJSON_Print(item);
	    item = cJSON_GetObjectItem(Plocation, "path");
        user_sen_config.path = cJSON_Print(item);
	    item = cJSON_GetObjectItem(Plocation, "timezone");
		user_sen_config.timezone = cJSON_Print(item);
		item = cJSON_GetObjectItem(Plocation, "timezone_offset");
		user_sen_config.timezone_offset = cJSON_Print(item);
		cJSON *Pdaily = cJSON_GetObjectItem(results_root, "daily");
//		daily_array_size = cJSON_GetArraySize(Pdaily); // 3天，只要第一天
//        for(j = 0;j < daily_array_size;j++)
//        {
			cJSON *item_daily = cJSON_GetArrayItem(Pdaily, 0);
			char *sdaily = cJSON_PrintUnformatted(item_daily);
			daily_root = cJSON_Parse(sdaily);
			if (!daily_root)
		    {
		      printf("Error before: [%s]\n",cJSON_GetErrorPtr());
			  return  0;
			}
		    item = cJSON_GetObjectItem(daily_root, "date");
            strcpy(weather_info.date, item->valuestring);
		    item = cJSON_GetObjectItem(daily_root, "text_day");
            strcpy(weather_info.day_weather, item->valuestring);
		    item = cJSON_GetObjectItem(daily_root, "code_day");
            weather_info.day_code = atoi(item->valuestring);
            printf("day code:%d\n", weather_info.day_code);
			item = cJSON_GetObjectItem(daily_root, "text_night");
            strcpy(weather_info.night_weather, item->valuestring);
			item = cJSON_GetObjectItem(daily_root, "code_night");
            weather_info.night_code = atoi(item->valuestring);
            printf("night code:%d\n", weather_info.night_code);

			item = cJSON_GetObjectItem(daily_root, "high");
            weather_info.temp_high = atoi(item->valuestring);
			item = cJSON_GetObjectItem(daily_root, "low");
            weather_info.temp_low = atoi(item->valuestring);
            // back
			item = cJSON_GetObjectItem(daily_root, "wind_speed");
			item = cJSON_GetObjectItem(daily_root, "wind_scale");
			item = cJSON_GetObjectItem(daily_root, "humidity");
            //
			cJSON_Delete(daily_root);/*每次调用cJSON_Parse函数后，都要释放内存*/
//        }
	/*-------------------------------------------------------------------*/
		item = cJSON_GetObjectItem(results_root, "last_update");
		user_sen_config.last_update = cJSON_Print(item);
		cJSON_Delete(results_root);  /*每次调用cJSON_Parse函数后，都要释放内存*/
    }
	cJSON_Delete(root);/*每次调用cJSON_Parse函数后，都要释放内存*/
	return  0;
}
esp_http_client_handle_t  client;
void WEATHER_HttpInit()
{
    esp_http_client_config_t config = {};
    memset(&config, 0, sizeof(esp_http_client_config_t));
    config.buffer_size = 256;
    config.url = WEB_PATH;

    client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_GET);
}


char output_buffer[1224] = {0};
uint8_t WEATHER_HttpGet()
{
    esp_http_client_open(client, 0);
    int content_length = esp_http_client_fetch_headers(client);
    if (content_length < 0) {
        ESP_LOGE(TAG, "Fetch Failed\n");
        return 0;
    } else {
        ESP_LOGI(TAG, "Got Content Length: %d\n", content_length);
    }
    esp_http_client_read(client, output_buffer, content_length);
    ESP_LOGI(TAG, "Read content: %s, %d\n", output_buffer, content_length);
    parse_json_data(output_buffer);
    esp_http_client_close(client);
    return 1;
}
