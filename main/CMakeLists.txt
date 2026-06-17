idf_component_register(SRCS "src/main.c" "src/io_hal.c" "src/mcp23017.c" "src/controller.c" 
                        "src/traffic_light1.c" "src/traffic_light2.c" "src/init_hardware.c"
                        "src/button.c"
                        PRIV_INCLUDE_DIRS "include"
                        INCLUDE_DIRS "."
                        REQUIRES heartbeat esp_driver_i2c)