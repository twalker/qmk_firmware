/* Select hand configuration */
/* serial.c configuration for split keyboard */
#define USE_SERIAL
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP3

// Activate double tap run/reset on elite_pi
/* #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET */
// #define EE_HANDS
#define MASTER_LEFT

/*
  elite_c == elite_pi pins:
MATRIX_ROW_PINS { F0 == GP16, F1 == GP15, C7 == GP14, D5 == GP13 }
MATRIX_COL_PINS { C6 == GP5, D7 == GP6, E6 == GP7, B4 == GP8, B5 == GP9 }
*/
// row-driven
#undef MATRIX_ROW_PINS
// #define MATRIX_ROW_PINS { F0, F1, C7, D5 }
#define MATRIX_ROW_PINS { GP16, GP15, GP14, GP13 }
#undef MATRIX_COL_PINS
// #define MATRIX_COL_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { GP5, GP6, GP7, GP8, GP9 }

/* COL2ROW or ROW2COL */
#undef DIODE_DIRECTION
#define DIODE_DIRECTION COL2ROW

/* PMW3389 settings. */
/*
 * Pinout:
 * MI = MISO
 * MO = MOSI
 * SS = Slave Select / Chip Select
 * SC = SPI Clock
 * MT = Motion (active low interrupt line)
 * RS = Reset
 * GD = Ground
 * VI = Voltage in up to +5.5V
 */

// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE
// Pointing device is on the right split.
/* #define POINTING_DEVICE_RIGHT */
#define POINTING_DEVICE_LEFT

// Limits the frequency that the sensor is polled for motion.
// #define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define POINTING_DEVICE_INVERT_Y
/*#define ROTATIONAL_TRANSFORM_ANGLE  -15*/
// #define PMW33XX_CPI 650 // sent in keymap based on OS.

// | `PMW33XX_CS_PIN`             | (Required) Sets the Cable Select pin connected to the sensor.                               | `POINTING_DEVICE_CS_PIN` |
// | `PMW33XX_CS_PINS`            | (Alternative) Sets the Cable Select pins connected to multiple sensors.                     | _not defined_            |
// | `PMW33XX_CPI`                | (Optional) Sets counts per inch sensitivity of the sensor.                                  | _varies_                 |
// | `PMW33XX_CLOCK_SPEED`        | (Optional) Sets the clock speed that the sensor runs at.                                    | `2000000`                |
// | `PMW33XX_SPI_DIVISOR`        | (Optional) Sets the SPI Divisor used for SPI communication.                                 | _varies_                 |
// | `PMW33XX_LIFTOFF_DISTANCE`   | (Optional) Sets the lift off distance at run time                                           | `0x02`                   |
// | `ROTATIONAL_TRANSFORM_ANGLE` | (Optional) Allows for the sensor data to be rotated +/- 127 degrees directly in the sensor. | `0`                      |


#define PMW33XX_CS_PIN GP26
// Sensor pins: SS to F7, SC to B1, MI to B2, M0 to B3
#undef SPI_SCK_PIN
#define SPI_SCK_PIN GP22
#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN GP23
#undef SPI_MISO_PIN
#define SPI_MISO_PIN GP20
#define SPI_DRIVER SPID0
#define PMW33XX_LIFTOFF_DISTANCE 0x03

// The CPI range is 50-16000, in increments of 50. Defaults to 2000 CPI.
#define PMW33XX_CPI 1500 // also sent in keymap based on OS.
                         //
// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE false
// #define AUTO_MOUSE_TIME 250

// Configure the global tapping term (default: 200ms)
#undef TAPPING_TERM
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define TT_SHIFT 110
#define TT_ALT 160

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD true
#define TAPPING_FORCE_HOLD_PER_KEY

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

