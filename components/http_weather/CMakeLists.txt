set(include_dirs .)

idf_component_register(SRC_DIRS .
                       INCLUDE_DIRS .
                       REQUIRES driver json esp_http_client)
