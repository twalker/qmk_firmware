
#pragma once


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
#undef PMW33XX_CS_PIN
#define PMW33XX_CS_PIN F7

// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define POINTING_DEVICE_INVERT_X
#define ROTATIONAL_TRANSFORM_ANGLE  -25
/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT

// #define EE_HANDS

/* serial.c configuration for split keyboard */
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D2
#define EE_HANDS

#define ENCODERS_PAD_A \
    { D5 }
#define ENCODERS_PAD_B \
    { C7 }

/* PMW33XX Settings */
// #define PMW33XX_CS_PIN B6

