/*
 * Ojueti
 * Camera + audio edge-AI device on the Waveshare ESP32-P4-WIFI6.
 *
 * Episode 1: board health check.
 * Before I build any pipeline, I want proof that the chip, flash, PSRAM and the shared
 * I2C bus all behave the way the schematic says they should.
 */
#include <inttypes.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_app_desc.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_psram.h"

#include "board.h"

static const char *TAG = "ojueti";

#define HEARTBEAT_PERIOD_MS 10000

static void print_system_report(void)
{
    const esp_app_desc_t *app = esp_app_get_description();

    esp_chip_info_t chip;
    esp_chip_info(&chip);

    uint32_t flash_bytes = 0;
    esp_flash_get_size(NULL, &flash_bytes);

    ESP_LOGI(TAG, "==============================================");
    ESP_LOGI(TAG, " Ojueti  |  firmware %s", app->version);
    ESP_LOGI(TAG, " Built %s %s with ESP-IDF %s", app->date, app->time, app->idf_ver);
    ESP_LOGI(TAG, "==============================================");

    /* The revision is encoded as major * 100 + minor. I print it because it decides
     * which chip-revision setting the firmware must be built with. */
    ESP_LOGI(TAG, "Chip      : ESP32-P4, %d cores, revision v%d.%d", chip.cores,
             chip.revision / 100, chip.revision % 100);
    ESP_LOGI(TAG, "Flash     : %" PRIu32 " MB", flash_bytes / (1024 * 1024));

    if (esp_psram_is_initialized()) {
        ESP_LOGI(TAG, "PSRAM     : %u MB", (unsigned)(esp_psram_get_size() / (1024 * 1024)));
    } else {
        ESP_LOGW(TAG, "PSRAM     : not initialised, check CONFIG_SPIRAM in sdkconfig");
    }

    ESP_LOGI(TAG, "Free heap : %u KB internal, %u KB PSRAM",
             (unsigned)(heap_caps_get_free_size(MALLOC_CAP_INTERNAL) / 1024),
             (unsigned)(heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024));
}

static void check_expected_devices(void)
{
    /* The codec is soldered on the board, so it must always answer. */
    if (board_i2c_device_present(BOARD_I2C_ADDR_ES8311)) {
        ESP_LOGI(TAG, "Audio     : ES8311 codec detected");
    } else {
        ESP_LOGE(TAG, "Audio     : ES8311 codec missing, check the I2C bus and power");
    }

    /* The camera is on a cable, so a missing sensor is a warning, not a failure. */
    if (board_i2c_device_present(BOARD_I2C_ADDR_OV5647)) {
        ESP_LOGI(TAG, "Camera    : OV5647 sensor detected");
    } else {
        ESP_LOGW(TAG, "Camera    : OV5647 not detected, check the CSI ribbon orientation");
    }
}

/* A small heartbeat so I can leave the board running and spot memory leaks early. */
static void heartbeat_task(void *arg)
{
    (void)arg;
    uint32_t beats = 0;
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(HEARTBEAT_PERIOD_MS));
        beats++;
        ESP_LOGI(TAG, "Heartbeat %" PRIu32 " | uptime %" PRIu32 " s | free %u KB internal, %u KB PSRAM",
                 beats, (uint32_t)(xTaskGetTickCount() / configTICK_RATE_HZ),
                 (unsigned)(heap_caps_get_free_size(MALLOC_CAP_INTERNAL) / 1024),
                 (unsigned)(heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024));
    }
}

void app_main(void)
{
    print_system_report();

    ESP_ERROR_CHECK(board_init());
    board_i2c_scan();
    check_expected_devices();

    ESP_LOGI(TAG, "Health check complete. Heartbeat every %d s.", HEARTBEAT_PERIOD_MS / 1000);
    xTaskCreate(heartbeat_task, "heartbeat", 3072, NULL, 1, NULL);
}
