idf_component_register(SRCS "src/main.c" "src/heartbeat.c"
                       PRIV_INCLUDE_DIRS "include"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES esp_driver_ledc esp_driver_gpio esp_pm)