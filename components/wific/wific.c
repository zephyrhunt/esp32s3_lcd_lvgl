#include "esp_wifi.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include <freertos/event_groups.h>
#include "wific.h"
#include "string.h"

static EventGroupHandle_t s_wifi_event_group;
#define TAG "wifi_station"
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define EXAMPLE_ESP_WIFI_SSID      "OnePlus Lcj"
#define EXAMPLE_ESP_WIFI_PASS      "123456788"
static int s_retry_num = 0;
uint8_t wifi_connect_status = 0;
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < 5) { // connect 5 times
            esp_wifi_connect();
            s_retry_num++;
            wifi_connect_status = 0;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        wifi_connect_status = 1;
    }
}

wifi_ap_record_t ap_info[20]; // 20 MAX
char wifi_ssid[20][40];
/* Initialize Wi-Fi as sta and set scan method */
uint16_t WIFI_Scan(void)
{
    uint16_t number = 20;
    uint16_t ap_count = 0;
    memset(wifi_ssid, 0, sizeof(wifi_ssid));
    memset(ap_info, 0, sizeof(ap_info));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ESP_LOGI(TAG, "Total APs scanned = %u", ap_count); // all
    if (ap_count > 20) ap_count = 20;
    for (int i = 0; (i < 20) && (i < ap_count); i++) {
        strcpy(wifi_ssid[i], (char *)ap_info[i].ssid);
        ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
//        ESP_LOGI(TAG, "SSID \t\t%s", wifi_ssid[i]);
//        ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
//        ESP_LOGI(TAG, "Channel \t\t%d\n", ap_info[i].primary);
    }
    return ap_count;
}

void WIFI_Connect(char * ssid)
{

}

void WIFI_StaInit(void)
{
    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
//    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
//                                                        ESP_EVENT_ANY_ID,
//                                                        &wifi_event_handler,
//                                                        NULL,
//                                                        &instance_any_id));
//    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
//                                                        IP_EVENT_STA_GOT_IP,
//                                                        &wifi_event_handler,
//                                                        NULL,
//                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
//    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
//    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "WIFI_StaInit finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
//    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
//                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
//                                           pdFALSE,
//                                           pdFALSE,
//                                           portMAX_DELAY);
//
//    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
//     * happened. */
//    if (bits & WIFI_CONNECTED_BIT) {
//        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
//                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//    } else if (bits & WIFI_FAIL_BIT) {
//        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
//                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//    } else {
//        ESP_LOGE(TAG, "UNEXPECTED EVENT");
//    }
}

uint8_t WIFI_GetConnectStatus()
{
    return wifi_connect_status;
}