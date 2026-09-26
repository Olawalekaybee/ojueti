/*
 * board.c
 * Board bring-up for the Waveshare ESP32-P4-WIFI6.
 */
#include "board.h"

#include "esp_check.h"
#include "esp_log.h"

static const char *TAG = "board";

static i2c_master_bus_handle_t s_i2c_bus = NULL;

/* Names for the devices I expect to see on this board, so the scan output reads clearly. */
static const char *describe_device(uint16_t addr)
{
    switch (addr) {
    case BOARD_I2C_ADDR_ES8311:
        return "ES8311 audio codec";
    case BOARD_I2C_ADDR_OV5647:
        return "OV5647 camera sensor";
    default:
        return "unrecognised device";
    }
}

esp_err_t board_init(void)
{
    /* I force the amplifier off first. The pull-down already keeps it off at reset,
     * but I prefer to own the pin state explicitly so there is no pop on the speaker. */
    const gpio_config_t amp_cfg = {
        .pin_bit_mask = 1ULL << BOARD_PA_EN,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&amp_cfg), TAG, "amplifier GPIO config failed");
    gpio_set_level(BOARD_PA_EN, 0);

    const i2c_master_bus_config_t bus_cfg = {
        .i2c_port = BOARD_I2C_PORT,
        .sda_io_num = BOARD_I2C_SDA,
        .scl_io_num = BOARD_I2C_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = false, /* external 2.2K pull-ups on the board */
    };
    ESP_RETURN_ON_ERROR(i2c_new_master_bus(&bus_cfg, &s_i2c_bus), TAG, "I2C bus init failed");

    ESP_LOGI(TAG, "Board initialised: amplifier off, I2C bus ready on SDA=%d SCL=%d",
             BOARD_I2C_SDA, BOARD_I2C_SCL);
    return ESP_OK;
}

i2c_master_bus_handle_t board_i2c_bus(void)
{
    return s_i2c_bus;
}

bool board_i2c_device_present(uint16_t addr)
{
    if (s_i2c_bus == NULL) {
        return false;
    }
    return i2c_master_probe(s_i2c_bus, addr, 50) == ESP_OK;
}

int board_i2c_scan(void)
{
    if (s_i2c_bus == NULL) {
        ESP_LOGE(TAG, "I2C bus not initialised, call board_init() first");
        return 0;
    }

    /* Empty addresses are expected during a scan, so I silence the driver while probing. */
    esp_log_level_set("i2c.master", ESP_LOG_NONE);

    int found = 0;
    ESP_LOGI(TAG, "Scanning I2C bus...");
    for (uint16_t addr = 0x08; addr <= 0x77; addr++) {
        if (i2c_master_probe(s_i2c_bus, addr, 50) == ESP_OK) {
            ESP_LOGI(TAG, "  0x%02X  %s", addr, describe_device(addr));
            found++;
        }
    }

    esp_log_level_set("i2c.master", ESP_LOG_INFO);
    ESP_LOGI(TAG, "Scan complete: %d device(s) found", found);
    return found;
}

void board_amp_enable(bool on)
{
    gpio_set_level(BOARD_PA_EN, on ? 1 : 0);
    ESP_LOGI(TAG, "Speaker amplifier %s", on ? "enabled" : "disabled");
}
