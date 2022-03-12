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

#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
    CDH = 0,
    SYM,
    NAV,
    NUM,
    WIN,
    MAC
};
// Tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CDHHM_T:
            return TT_SHIFT;
        case CDHHM_N:
            return TT_SHIFT;
        case CDHHM_R:
            return TT_ALT;
        case CDHHM_I:
            return TT_ALT;
        default:
            return TAPPING_TERM;
    }
};

// Macros
enum custom_keycodes {
  MAC_USER = SAFE_RANGE,
  MAC_EMAIL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC_USER:
            if (record->event.pressed) {
                SEND_STRING("tiwalker");
            }
            break;

        case MAC_EMAIL:
        if (record->event.pressed) {
            SEND_STRING("tiwalker@starbucks.com");
        }
        break;
    }

    return true;
};

// Combos
enum combos {
  SS_CAPS,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ss_combo[] = {CDHHM_T, CDHHM_N, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
  [SS_CAPS] = COMBO(ss_combo, KC_CAPS)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Colemak DH
  [CDH] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, CDHHM_A, CDHHM_R, CDHHM_S, CDHHM_T,    KC_G,                         KC_M, CDHHM_N, CDHHM_E, CDHHM_I, CDHHM_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OSL(MAC),    KC_Z,    KC_X,     KC_C,   KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            MO(NUM),   MO(SYM),  LT(NAV, KC_BSPC),    LT(NAV, KC_SPC), MO(WIN), MO(NUM)
                                      //`--------------------------'  `--------------------------'

  ),
  // Symbols
  [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                      KC_AMPR, KC_ASTR,  KC_LT,    KC_GT, KC_QUES, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                       KC_MINS,  KC_EQL, KC_PLUS, KC_UNDS, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                      KC_BSLS,   KC_NO, KC_COMM,  KC_DOT, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
  // Nav
  [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                        KC_NO, KC_PGUP,   KC_UP,   KC_NO,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_APP, OS_UNDO,  OS_CUT, OS_COPY, OS_PSTE, OS_PSTE,                  RCS(KC_TAB), KC_PGDN,   KC_NO,  KC_NO, C(KC_TAB), _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  KC_DEL,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
  // Num
  [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,                        KC_NO,    KC_7,    KC_8,    KC_9,   KC_NO, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,                        KC_NO,    KC_4,    KC_5,    KC_6,   KC_NO, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,                        KC_NO,    KC_1,    KC_2,    KC_3,   KC_NO, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   KC_0, KC_DOT
                                      //`--------------------------'  `--------------------------'
  ),
  // Win/Adjust
  [WIN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, _______, _______, _______, _______, _______,                       KC_NO,   WIN_TL,   WIN_U,  WIN_TR,  WIN_LG, ZOOM_IN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                       KC_NO,   WIN_L,    WIN_D,   WIN_R, WIN_FUL, WIN_PSC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                       KC_NO,  WIN_BL,   KC_NO,  WIN_BR,  WIN_SM, ZOOM_OUT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
  // Macros
  [MAC] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, DM_PLY1, DM_PLY2,                                     _______, _______, MAC_USER, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, DM_RSTP, _______, _______,                                     _______, _______, MAC_EMAIL, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, DM_REC1,    DM_REC2, _______, _______
                                      //`--------------------------'  `--------------------------'
    ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}


void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case CDH:
            oled_write_ln_P(PSTR("Colemak-DH"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case NAV:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case WIN:
            oled_write_ln_P(PSTR("Win"), false);
            break;
        case MAC:
            oled_write_ln_P(PSTR("Macros"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined"), false);
    }
}

void oled_render_lock_state(void) {
    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_layer_state();
    oled_render_lock_state();
  } else {
    oled_render_logo();
  }
  return false;
}

#endif // OLED_ENABLE
