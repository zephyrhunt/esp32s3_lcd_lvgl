#include "weather_get.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "esp_log.h"

#define WEB_PATH "https://api.seniverse.com/v3/weather/daily.json?key=ScVuOBExK0jxY9pzd&location=wuhan&language=en"          // 天气获取路径
#define TAG "weather_get"



WeatherInfo_t weather_info;
/**
 * @brief 解析天气数据（JSON）
 *
 * @param analysis_buf 数据的存储空间
 * @return true 解析成功
 * @return false 解析失败
 */
static bool parse_json_data(const char *analysis_buf) {
    cJSON *json_data = NULL;
    /* 截取有效json */
    char *index = strchr(analysis_buf, '{');
    // strcpy(weather_buf, index);

    json_data = cJSON_Parse(index);
    if (json_data == NULL) // 判断字段是否json格式
    {
        return false;
    }

    // ESP_LOGI(TAG, "Start parsing data");
    cJSON *cjson_item = cJSON_GetObjectItem(json_data, "results");
    cJSON *cjson_results = cJSON_GetArrayItem(cjson_item, 0);

    /* 获取天气的地址 */
    cJSON *cjson_location = cJSON_GetObjectItem(cjson_results, "location");
    cJSON *cjson_temperature_name = cJSON_GetObjectItem(cjson_location, "name");
//    strcpy(user_weather_info.location_name,cjson_temperature_name->valuestring);

    /* 天气信息 */
    cJSON *cjson_daily = cJSON_GetObjectItem(cjson_results, "daily");

    /* 当天的天气信息 */
    cJSON *cjson_daily_1 = cJSON_GetArrayItem(cjson_daily, 0);

//    ESP_LOGI(TAG, "day_one_code is: %s", cJSON_GetObjectItem(cjson_daily_1, "code_day")->valuestring);
//    ESP_LOGI(TAG, "day_one_temp_high is: %s", cJSON_GetObjectItem(cjson_daily_1, "high")->valuestring);
//    ESP_LOGI(TAG, "day_three_temp_low is: %s", cJSON_GetObjectItem(cjson_daily_1, "low")->valuestring);
    ESP_LOGI(TAG, "day_one_humi is: %s", cJSON_GetObjectItem(cjson_daily_1, "humidity")->valuestring);
//    ESP_LOGI(TAG, "day_one_windspeed is: %s", cJSON_GetObjectItem(cjson_daily_1, "wind_speed")->valuestring);
//    ESP_LOGI(TAG, "day_one_date is: %s", cJSON_GetObjectItem(cjson_daily_1, "date")->valuestring);
//    ESP_LOGI(TAG, "day_one_weather is: %s", cJSON_GetObjectItem(cjson_daily_1, "text_day")->valuestring);
//    ESP_LOGI(TAG, "day_one_name is: %s", cJSON_GetObjectItem(cjson_location, "name")->valuestring);

//    strcpy(weather_info.date, cJSON_GetObjectItem(cjson_daily_1, "date")->valuestring);
//    strcpy(weather_info.weather, cJSON_GetObjectItem(cjson_daily_1, "text_day")->valuestring);
//    strcpy(weather_info.temp_high, cJSON_GetObjectItem(cjson_daily_1, "high")->valuestring);
//    strcpy(weather_info.temp_low, cJSON_GetObjectItem(cjson_daily_1, "low")->valuestring);

    return 1;
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
    int64_t content_length = esp_http_client_fetch_headers(client);
    if (content_length < 0) {
        ESP_LOGE(TAG, "Fetch Failed\n");
        return 0;
    } else {
        ESP_LOGI(TAG, "Got Content Length: %lld\n", content_length);
    }
    esp_http_client_read(client, output_buffer, content_length);
    ESP_LOGI(TAG, "Read content: %s, %lld\n", output_buffer, content_length);
//    parse_json_data(output_buffer);
    esp_http_client_close(client);
    return 1;
}
