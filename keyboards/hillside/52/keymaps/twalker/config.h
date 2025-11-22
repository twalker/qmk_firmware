/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

/* Select hand configuration */

#if !defined(MASTER_RIGHT) && !defined(MASTER_LEFT)
    #define MASTER_RIGHT
#endif

#define RGBLIGHT_ENABLE_MODE_STATIC_LIGHT
#define RGBLIGHT_CONFIG_HUE 128
#define RGBLIGHT_CONFIG_SAT 255
#define RGBLIGHT_CONFIG_VAL 255

// #ifdef RGBLIGHT_ENABLE
//     #define RGBLIGHT_EFFECT_BREATHING
//     #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//     #define RGBLIGHT_EFFECT_SNAKE
//     #define RGBLIGHT_EFFECT_KNIGHT
//     #define RGBLIGHT_EFFECT_CHRISTMAS
//     #define RGBLIGHT_EFFECT_STATIC_GRADIENT
// //  #define RGBLIGHT_EFFECT_RGB_TEST
// //  #define RGBLIGHT_EFFECT_ALTERNATING
// //  #define RGBLIGHT_EFFECT_TWINKLE
//     #define RGBLIGHT_LIMIT_VAL 120
//     #define RGBLIGHT_HUE_STEP 10
//     #define RGBLIGHT_SAT_STEP 17
//     #define RGBLIGHT_VAL_STEP 17
// #endif
#ifdef PS2_DRIVER_BUSYWAIT
# define PS2_CLOCK_PIN   D1
# define PS2_DATA_PIN    D2
#endif


// #define PS2_CLOCK_PIN A8
// #define PS2_DATA_PIN  A9
#define PS2_PIO_USE_PIO1
// #define PS2_CLOCK_PIN A8
// #define PS2_DATA_PIN  A9

// #define PS2_DATA_PIN    GP2
// #define PS2_CLOCK_PIN   GP3

#define PS2_CLOCK_PIN D1
#define PS2_DATA_PIN  D2
