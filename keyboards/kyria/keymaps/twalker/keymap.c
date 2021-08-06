/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "icons.h"

enum layers {
    QWERTY = 0,
    SYM,
    NAV,
    NUM,
    WIN,
    MOUSE
};

// Tab dance
enum {
  TD_TBCP = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TBCP] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_CAPS)
};

// Keymap array
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * Base Layer: QWERTY
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |  TAB   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  BS    |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |  ESC   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? | Enter  |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      | Space|      |      |      |
    *                        |      | Num  | Sym  | Nav  | WIN  |  | MS   | Nav  |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [QWERTY] = LAYOUT(
      TD(TD_TBCP),   KC_Q,   KC_W,     KC_E,   KC_R,   KC_T,                                           KC_Y,   KC_U,   KC_I,   KC_O,      KC_P, KC_BSLS,
      KC_ESC, HOME_A, HOME_S,   HOME_D, HOME_F,   KC_G,                                           KC_H, HOME_J, HOME_K, HOME_L, HOME_SCLN, KC_QUOT,
      KC_NO,    KC_Z,   KC_X,     KC_C,   KC_V,   KC_B, KC_NO, KC_NO,      KC_NO, KC_NO, KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH,  KC_ENT,
                       KC_NO,  MO(NUM), MO(SYM), MO(NAV), MO(WIN),  TG(MOUSE), LT(NAV, KC_SPC), KC_NO,  KC_NO, KC_NO
    ),
    /*
    * Symbols
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |  !   |  @   |  {   |  }   |  |   |                              |  &   |  *   |      |      |      |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        |  #   |  $   |  (   |  )   |  `   |                              |   -  |  =   |  +   |  _   | ; :  |  ' "   |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |      |  \   |  ,   |  .   |  / ? |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [SYM] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     KC_AMPR, KC_ASTR,  KC_NO,   KC_NO,   KC_NO, _______,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_MINS, KC_EQL, KC_PLUS, KC_UNDS, KC_SCLN, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_NO, KC_BSLS,  KC_COMM, KC_DOT,  KC_SLSH, _______,
                                 _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______
    ),

    /*
    * Navigation
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |      |      |      |      |      |                              | HOME | PGDN | PGUP | END  |      |  DEL   |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        | LCTL | LALT | LGUI | LSFT |      |                              | LEFT | DOWN |  UP  | RGHT |      |        |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        | UNDO | CUT  | COPY | PSTE |      |      |      |  |      |      | <TAB |      |      | TAB> |      |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, KC_DEL,
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                                     KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, _______, _______,
      _______, OS_UNDO, OS_CUT,  OS_COPY, OS_PSTE, _______, _______, _______, _______, _______, RCS(KC_TAB), KC_NO, KC_NO, C(KC_TAB), _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
    * Num Layer: Number keys, function keys
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |  F1  |  F2  |  F3  |  F4  |      |                              |      |  7   |  8   |  9   |      |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      |  4   |  5   |  6   |      |        |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        |  F9  | F10  | F11  | F12  |      |      |      |  |      |      |      |  1   |  2   |  3   |      |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |  0   |  .   |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [NUM] = LAYOUT(
    _______, KC_F1,  KC_F2,    KC_F3,   KC_F4,   _______,                                     KC_NO,    KC_7,    KC_8,    KC_9,   KC_NO, _______,
    _______, KC_F5,  KC_F6,    KC_F7,   KC_F8,   _______,                                     KC_NO,    KC_4,    KC_5,    KC_6,   KC_NO, _______,
    _______, KC_F9,   KC_F10,  KC_F11, KC_F12,   _______, _______, _______, _______, _______, KC_NO,    KC_1,    KC_2,    KC_3,   KC_NO, _______,
                                _______, _______, _______, _______, _______, _______, _______, KC_0,  KC_DOT, _______
    ),
    /*
    * Window managment
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |      |      |      |      |      |                              | W TL |      |      |  TR  | W LG |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        | MUTE | MPRV | MPLY | MNXT |      |                              | W L  | W D  | W U  | W R  | W FUL| W PSC  |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        |      |      |      |      |      |      |      |  |      |      | W BL |      |      | W BR | W SM |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [WIN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     WIN_TL, KC_NO, KC_NO, WIN_TR, WIN_LG, KC_NO,
      _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                     WIN_L, WIN_D, WIN_U,  WIN_R, WIN_FUL, WIN_PSC,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, WIN_BL, KC_NO, KC_NO, WIN_BR, WIN_SM, KC_NO,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /*
    * Mouse
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |      |      |      |      |      |                              | WH_L | WH_D | WH_U | WH_R |      |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        | LCTL | LALT | LGUI | LSFT |      |                              | MS_L | MS_D | MS_U | MS_R |      |        |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        | UNDO | CUT  | COPY | PSTE |      |      |      |  |      |      |      |      |      |      |      |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      | ACL1 | ACL2 | BTN1 | BTN2 |  |      |      |      |      |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [MOUSE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
      _______, OS_UNDO, OS_CUT,  OS_COPY, OS_PSTE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, KC_ACL1, KC_ACL2, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______
    ),


};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_status(void) {
    // QMK Logo and version information
    // render_qmk_logo();
    // oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    // oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            // oled_write_P(PSTR("QWERTY\n"), false);
            render_base_icon();
            break;
        case SYM:
            // oled_write_P(PSTR("Symbols\n"), false);
            render_sym_icon();
            break;
        case NUM:
            // oled_write_P(PSTR("Numbers\n"), false);
            render_num_icon();
            break;
        case NAV:
            // oled_write_P(PSTR("Navigation\n"), false);
            render_nav_icon();
            break;
        case WIN:
            // oled_write_P(PSTR("Window\n"), false);
            render_win_icon();
            break;
        case MOUSE:
            // oled_write_P(PSTR("Mouse\n"), false);
            render_mouse_icon();
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_qmk_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            // tap_code(KC_WH_U);
            // tap_code(C(KC_TAB));
            tap_code16(S(C(KC_TAB)));
            // tap_code(KC_PGUP);
        } else {
            // tap_code(KC_PGDN);
            tap_code16(C(KC_TAB));
        }
    }
    return true;
}
#endif
