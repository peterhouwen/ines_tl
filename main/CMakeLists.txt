idf_component_register(SRCS "src/main.c" "src/io_hal.c" "src/mcp23017.c"
                       INCLUDE_DIRS "." "include"
                       REQUIRES heartbeat esp_driver_i2c)