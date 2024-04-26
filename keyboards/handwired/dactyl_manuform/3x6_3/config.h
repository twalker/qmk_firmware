/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2021 @dlford
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

// promicro pins
// #define MATRIX_ROW_PINS { B1, B3, B2, B6 }
// #define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

// Activate double tap run/reset on elite_pi
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET


/*
  elite_c == elite_pi pins:
MATRIX_ROW_PINS { F0 == D16, F1 == D15, C7 == D14, D5 == D13 }
MATRIX_COL_PINS { D4 == D4, C6 == D5, D7 == D6, E6 == D7, B4 == D8, B5 == D9 }
*/
// same elite_c for elite pi as my tractyl
#define MATRIX_ROW_PINS { F0, F1, C7, D5 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

/*
serial.c configuration (for split keyboard).
SOFT_SERIAL_PIN D2
*/
// #define SERIAL_USART_FULL_DUPLEX     // Enable full duplex operation mode.
// #define SERIAL_USART_DRIVER SD1

//#define SOFT_SERIAL_PIN D0

// #define SERIAL_USART_FULL_DUPLEX
// #define SERIAL_USART_TX_PIN A9
// #define SERIAL_USART_RX_PIN A10

/* Enables This makes it easier for fast typists to use dual-function keys */
// #undef PERMISSIVE_HOLD
