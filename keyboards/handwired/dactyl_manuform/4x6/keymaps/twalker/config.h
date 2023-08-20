#pragma once

#define ___ KC_NO
/* Use I2C or Serial, not both */
#define USE_SERIAL
//#define USE_I2C

/* Select hand configuration */
/* serial.c configuration for split keyboard */
// Activate double tap run/reset on elite_pi
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
// #define SOFT_SERIAL_PIN D2
// #define EE_HANDS
#define MASTER_LEFT
// #define MASTER_RIGHT

// row-driven
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { F0, F1, C7, D5, B7 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

/* COL2ROW or ROW2COL */
#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

/* PMW3360 settings. */
// try B0 F0
// failed: B1, B0 -- success with F7 (Y is reversed)
#define PMW33XX_CS_PIN F7

// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE
// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

// Limits the frequency that the sensor is polled for motion.
// #define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define POINTING_DEVICE_INVERT_Y
// #define ROTATIONAL_TRANSFORM_ANGLE  -25
#define ROTATIONAL_TRANSFORM_ANGLE  -15
// #define PMW33XX_CPI 650 // sent in keymap based on OS.

// | `PMW33XX_CS_PIN`             | (Required) Sets the Cable Select pin connected to the sensor.                               | `POINTING_DEVICE_CS_PIN` |
// | `PMW33XX_CS_PINS`            | (Alternative) Sets the Cable Select pins connected to multiple sensors.                     | _not defined_            |
// | `PMW33XX_CPI`                | (Optional) Sets counts per inch sensitivity of the sensor.                                  | _varies_                 |
// | `PMW33XX_CLOCK_SPEED`        | (Optional) Sets the clock speed that the sensor runs at.                                    | `2000000`                |
// | `PMW33XX_SPI_DIVISOR`        | (Optional) Sets the SPI Divisor used for SPI communication.                                 | _varies_                 |
// | `PMW33XX_LIFTOFF_DISTANCE`   | (Optional) Sets the lift off distance at run time                                           | `0x02`                   |
// | `ROTATIONAL_TRANSFORM_ANGLE` | (Optional) Allows for the sensor data to be rotated +/- 127 degrees directly in the sensor. | `0`                      |

// elite pi pins:
// F7 = 26U
// try B0 F0
// failed: B1, B0 -- success with F7 (Y is reversed)

#define PMW33XX_CS_PIN F7
#undef SPI_SCK_PIN
#define SPI_SCK_PIN B1
#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN B2
#undef SPI_MISO_PIN
#define SPI_MISO_PIN B3
// I'm not confident in the SPI_DRIVER value:
#define SPI_DRIVER SPID0
// Sensor pins: SS to F7, SC to B1, MO to B2, MI to B3
#undef SPI_SCK_PIN
#define SPI_SCK_PIN B1
#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN B2
#undef SPI_MISO_PIN
#define SPI_MISO_PIN B3

// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE
// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

#define POINTING_DEVICE_INVERT_Y
#define ROTATIONAL_TRANSFORM_ANGLE  -15

// The CPI range is 50-16000, in increments of 50. Defaults to 2000 CPI.
#define PMW33XX_CPI 900 // also sent in keymap based on OS.

// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE

// TODO: LED strip
// WS2812 RGB LED strip input and number of LEDs
// https://www.diykeyboards.com/projects/add-underglow-to-qmk-boards
#undef RGB_DI_PIN
#define RGB_DI_PIN      D3
#undef RGBLED_NUM
#define RGBLED_NUM      20
#define RGBLIGHT_SPLIT
#undef RGBLED_SPLIT
#define RGBLED_SPLIT \
    { 10, 10 }
#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 80
// #undef RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_SLEEP

/* OLED 128x32 */
// TODO: find pin for oled
/*
   elite-c I2C pins: D0 (clock), D1 (data)  serial pins: D2, D3
    Pin 1: GND (ground)
    Pin 2: VCC (power cord)
    Pin 3: SCL (clock line of I2C commication) -- A3 on pi/c
    Pin 4: SDA (data line of the I2C communication) -- A2 on pi/c
*/

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define TT_SHIFT 120
#define TT_ALT 180

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD true
#define TAPPING_FORCE_HOLD_PER_KEY

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// COLEMAK DH homerow mods
// Left-hand
#define CDHHM_A LCTL_T(KC_A)
#define CDHHM_R LALT_T(KC_R)
#define CDHHM_S LGUI_T(KC_S)
#define CDHHM_T LSFT_T(KC_T)
// Right-hand
#define CDHHM_N RSFT_T(KC_N)
#define CDHHM_E RGUI_T(KC_E)
#define CDHHM_I LALT_T(KC_I)
#define CDHHM_O RCTL_T(KC_O)


#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
