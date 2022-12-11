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
    [CDH] = LAYOUT_split_3x6_3(
        KC_1,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_4,
        KC_2,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,       KC_O,    KC_5,
        KC_3,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, KC_COMM,  KC_DOT,    KC_SLSH,    KC_6,
                                  KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F
    )
};

