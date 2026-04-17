idf_component_register(SRCS "src/main.c"
                       INCLUDE_DIRS "."
                       REQUIRES heartbeat esp_driver_i2c)