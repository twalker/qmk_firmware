#pragma once

// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_LEFT
#define SPI_DRIVER SPID0
// NOTE: If trackball tracking is janky, try a different colored trackball.
// Low contrast or sparkply trackballs seem to track poorly.
//#define PMW33XX_LIFTOFF_DISTANCE 0x03
#define PMW33XX_CS_PIN GP26
#define SPI_SCK_PIN GP22
#define SPI_MOSI_PIN GP23
#define SPI_MISO_PIN GP20

#define POINTING_DEVICE_INVERT_Y
#define ROTATIONAL_TRANSFORM_ANGLE  90
// | `PMW33XX_CS_PIN`             | (Required) Sets the Cable Select pin connected to the sensor.                               | `POINTING_DEVICE_CS_PIN` |
// | `PMW33XX_CS_PINS`            | (Alternative) Sets the Cable Select pins connected to multiple sensors.                     | _not defined_            |
// | `PMW33XX_CPI`                | (Optional) Sets counts per inch sensitivity of the sensor.                                  | _varies_                 |
// | `PMW33XX_CLOCK_SPEED`        | (Optional) Sets the clock speed that the sensor runs at.                                    | `2000000`                |
// | `PMW33XX_SPI_DIVISOR`        | (Optional) Sets the SPI Divisor used for SPI communication.                                 | _varies_                 |
// | `PMW33XX_LIFTOFF_DISTANCE`   | (Optional) Sets the lift off distance at run time                                           | `0x02`                   |
// | `ROTATIONAL_TRANSFORM_ANGLE` | (Optional) Allows for the sensor data to be rotated +/- 127 degrees directly in the sensor. | `0`                      |

// #define PMW33XX_CPI 650 // sent in keymap based on OS.
// pmw3360 -- The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.
// pmw3389 -- The CPI range is 50-16000, in increments of 50. Defaults to 2000 CPI
#define MSE_DPI_OPTIONS { 1300, 400}
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE

// Configure the global tapping term (default: 200ms)
#undef TAPPING_TERM
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define TT_SHIFT 110
#define TT_ALT 160

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD
