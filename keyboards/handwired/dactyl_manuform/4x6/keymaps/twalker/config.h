#pragma once

#define ___ KC_NO
/* Use I2C or Serial, not both */
#define USE_SERIAL
//#define USE_I2C

/* Select hand configuration */
// #define MASTER_LEFT
#define MASTER_RIGHT

// #define EE_HANDS

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
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define POINTING_DEVICE_INVERT_Y
// #define ROTATIONAL_TRANSFORM_ANGLE  -25
#define ROTATIONAL_TRANSFORM_ANGLE  -20
#define PMW33XX_CPI 750

// | `PMW33XX_CS_PIN`             | (Required) Sets the Cable Select pin connected to the sensor.                               | `POINTING_DEVICE_CS_PIN` |
// | `PMW33XX_CS_PINS`            | (Alternative) Sets the Cable Select pins connected to multiple sensors.                     | _not defined_            |
// | `PMW33XX_CPI`                | (Optional) Sets counts per inch sensitivity of the sensor.                                  | _varies_                 |
// | `PMW33XX_CLOCK_SPEED`        | (Optional) Sets the clock speed that the sensor runs at.                                    | `2000000`                |
// | `PMW33XX_SPI_DIVISOR`        | (Optional) Sets the SPI Divisor used for SPI communication.                                 | _varies_                 |
// | `PMW33XX_LIFTOFF_DISTANCE`   | (Optional) Sets the lift off distance at run time                                           | `0x02`                   |
// | `ROTATIONAL_TRANSFORM_ANGLE` | (Optional) Allows for the sensor data to be rotated +/- 127 degrees directly in the sensor. | `0`                      |
