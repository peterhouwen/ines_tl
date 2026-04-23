idf_component_register(SRCS "src/main.c" "dio_cfg.c" "dio.c"
                       INCLUDE_DIRS "." "include"
                       REQUIRES heartbeat esp_driver_i2c)