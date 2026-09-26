/*
 * board.h (Ojueti)
 * Pin map and board-level helpers for the Waveshare ESP32-P4-WIFI6.
 *
 * Every pin here comes from the official Waveshare schematic. I keep all hardware
 * details in this one file so the application code never hard-codes a GPIO number.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---------- Shared I2C bus: codec, camera, display, 40-pin header ---------- */
/* The board already has 2.2K pull-ups on these lines, so I leave the internal ones off. */
#define BOARD_I2C_PORT        I2C_NUM_0
#define BOARD_I2C_SDA         GPIO_NUM_7
#define BOARD_I2C_SCL         GPIO_NUM_8
#define BOARD_I2C_FREQ_HZ     400000

#define BOARD_I2C_ADDR_ES8311 0x18 /* audio codec */
#define BOARD_I2C_ADDR_OV5647 0x36 /* camera sensor on the Raspberry Pi Camera (B) */

/* ---------- Audio: ES8311 codec over I2S, NS4150B amplifier ---------- */
#define BOARD_I2S_MCLK        GPIO_NUM_13
#define BOARD_I2S_SCLK        GPIO_NUM_12
#define BOARD_I2S_ASDOUT      GPIO_NUM_11 /* codec to P4: microphone data */
#define BOARD_I2S_LRCK        GPIO_NUM_10
#define BOARD_I2S_DSDIN       GPIO_NUM_9  /* P4 to codec: speaker data */
#define BOARD_PA_EN           GPIO_NUM_53 /* amplifier enable, active high, 10K pull-down */

/* ---------- MicroSD, 4-bit SDMMC ---------- */
#define BOARD_SD_CLK          GPIO_NUM_43
#define BOARD_SD_CMD          GPIO_NUM_44
#define BOARD_SD_D0           GPIO_NUM_39
#define BOARD_SD_D1           GPIO_NUM_40
#define BOARD_SD_D2           GPIO_NUM_41
#define BOARD_SD_D3           GPIO_NUM_42
#define BOARD_SD_PWR          GPIO_NUM_45 /* drives a P-MOS switch: low = card powered */
#define BOARD_SD_IO_LDO_CHAN  4           /* card I/O rail comes from the P4 internal LDO VO4 */

/* ---------- ESP32-C6 wireless co-processor over SDIO ---------- */
/* Same wiring as the Espressif P4 Function-EV-Board, so esp_hosted defaults apply. */
#define BOARD_C6_SDIO_CLK     GPIO_NUM_18
#define BOARD_C6_SDIO_CMD     GPIO_NUM_19
#define BOARD_C6_SDIO_D0      GPIO_NUM_14
#define BOARD_C6_SDIO_D1      GPIO_NUM_15
#define BOARD_C6_SDIO_D2      GPIO_NUM_16
#define BOARD_C6_SDIO_D3      GPIO_NUM_17
#define BOARD_C6_RESET        GPIO_NUM_54 /* drives C6 CHIP_PU */
#define BOARD_C6_IO2          GPIO_NUM_6

/* ---------- Buttons ---------- */
#define BOARD_BOOT_BUTTON     GPIO_NUM_35 /* also a strapping pin, active low */

/**
 * Bring up the board-level hardware I need before anything else runs:
 * the amplifier is forced off and the shared I2C bus is created.
 */
esp_err_t board_init(void);

/** Handle to the shared I2C bus, valid after board_init(). */
i2c_master_bus_handle_t board_i2c_bus(void);

/** Scan the I2C bus, log every device found, and return the device count. */
int board_i2c_scan(void);

/** True if a device acknowledges at the given 7-bit address. */
bool board_i2c_device_present(uint16_t addr);

/** Switch the speaker amplifier on or off. */
void board_amp_enable(bool on);

#ifdef __cplusplus
}
#endif
