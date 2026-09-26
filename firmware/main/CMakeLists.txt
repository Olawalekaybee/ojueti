idf_component_register(
    SRCS "app_main.c"
    INCLUDE_DIRS "."
    REQUIRES board esp_psram spi_flash esp_app_format esp_hw_support
)
