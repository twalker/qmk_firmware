/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

//#define USE_MATRIX_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

// Configure the global tapping term (default: 200ms)
// #define TAPPING_TERM 170
// #define TAPPING_TERM_PER_KEY
// #define TT_SHIFT 150
// #define TT_ALT 220
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define TT_SHIFT 120
#define TT_ALT 180

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// CAPS_WORD rules!
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

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

#define OS_COPY LGUI(KC_C)
#define OS_UNDO LGUI(KC_Z)
#define OS_PSTE LGUI(KC_V)
#define OS_CUT LGUI(KC_X)

// Win/Adjust
#define WIN_TL LCA(KC_U)
#define WIN_TR LCA(KC_I)
#define WIN_BL LCA(KC_J)
#define WIN_BR LCA(KC_K)

#define WIN_L LCA(KC_LEFT)
#define WIN_R LCA(KC_RGHT)
#define WIN_U LCA(KC_UP)
#define WIN_D LCA(KC_DOWN)

#define WIN_LG LCA(KC_EQL)
#define WIN_SM LCA(KC_MINS)
#define WIN_FUL LCA(KC_ENT)
#define WIN_PSC SCMD(KC_5)
#define ZOOM_IN LGUI(KC_EQL)
#define ZOOM_OUT LGUI(KC_MINS)

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
