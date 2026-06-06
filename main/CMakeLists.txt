idf_component_register(SRCS "src/main.c" "src/io_hal.c" "src/mcp23017.c"
                        PRIV_INCLUDE_DIRS "include"
                        INCLUDE_DIRS "."
                        REQUIRES heartbeat esp_driver_i2c)