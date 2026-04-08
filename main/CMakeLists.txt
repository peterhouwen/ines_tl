idf_component_register(SRCS "src/main.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES esp_driver_ledc esp_driver_gpio esp_pm)