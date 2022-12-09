// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
  CDH = 0,
  SYM,
  NAV,
  NUM,
  WIN,
  MAC,
  MSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │TAB│ Q │ W │ F │ P │ B │       │ J │ L │ U │ Y │ ; │BS │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │ESC│ A │ R │ S │ T │ G │       │ M │ N │ E │ I │ O │ " │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │MAC│ Z │ X │ C │ D │ V │       │ K │ H │ , │ . │ / │ENT│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *
      *             ┌───┐                       ┌───┐
      *             │NUM├───┐               ┌───┤MSE│
      *             └───┤SYM├───┐       ┌───┤WIN├───┘
      *                 └───┤NAV│       │NAV├───┘
      *                     └───┘       └───┘
      */
    [0] = LAYOUT_split_3x6_3(
        KC_NO,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
        KC_NO,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_NO,
        KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
                                KC_LGUI, KC_BSPC,  KC_SPC,    KC_SPC,  KC_ENT,  KC_RALT
    )
};

