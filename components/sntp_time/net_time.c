#include "esp_netif_sntp.h"
#include "esp_sntp.h"
#include "esp_log.h"
#include "net_time.h"

#define TAG "sntp"

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}

static void print_servers(void)
{
    ESP_LOGI(TAG, "List of configured NTP servers:");

    for (uint8_t i = 0; i < SNTP_MAX_SERVERS; ++i){
        if (esp_sntp_getservername(i)){
            ESP_LOGI(TAG, "server %d: %s", i, esp_sntp_getservername(i));
        } else {
            // we have either IPv4 or IPv6 address, let's print it
            char buff[48];
            ip_addr_t const *ip = esp_sntp_getserver(i);
            if (ipaddr_ntoa_r(ip, buff, 48) != NULL)
                ESP_LOGI(TAG, "server %d: %s", i, buff);
        }
    }
}

static uint8_t obtain_time(void)
{
    ESP_LOGI(TAG, "Initializing and starting SNTP");
    /*
     * This is the basic default config with one server and starting the service
     */
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    config.sync_cb = time_sync_notification_cb;     // Note: This is only needed if we want

    esp_netif_sntp_init(&config);
    print_servers();

    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 20;
    while (esp_netif_sntp_sync_wait(500 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
    }

    time(&now);
    localtime_r(&now, &timeinfo);
    esp_netif_sntp_deinit();

    if (retry >= retry_count)
        return 0;
    else
        return 1;
}

time_t now;
struct tm timeinfo;
char strftime_buf[64];
uint8_t SNTP_TimeUpdate()
{
    setenv("TZ", "CST-8", 1);
    tzset();
    uint8_t is_update = obtain_time();

    if (is_update == 0) {
        ESP_LOGE(TAG, "Time is not updated");
        return 0;
    }
    time(&now);
    // Set timezone to China Standard Time
    localtime_r(&now, &timeinfo);

    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time is: %s", strftime_buf);
    if (sntp_get_sync_mode() == SNTP_SYNC_MODE_SMOOTH) {
        struct timeval outdelta;
        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_IN_PROGRESS) {
            adjtime(NULL, &outdelta);
            ESP_LOGI(TAG, "Waiting for adjusting time ... outdelta = %jd sec: %li ms: %li us",
                     (intmax_t)outdelta.tv_sec,
                     outdelta.tv_usec/1000,
                     outdelta.tv_usec%1000);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }

    return 1;
}
