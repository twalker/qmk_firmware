
#pragma once


// row-driven
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { F0, F1, C7, D5, B7 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

/* COL2ROW or ROW2COL */
#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT

// #define EE_HANDS
