#include QMK_KEYBOARD_H

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

#ifdef DYNAMIC_MACRO_ENABLE
// Macros
enum custom_keycodes {
  MAC_USER = SAFE_RANGE,
  MAC_EMAIL,
  KC_LSTRT,
  KC_LEND,
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
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;

    }

    return true;
}
#endif

// Keymap array
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [CDH] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
       KC_TAB,     KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
       KC_ESC, CDHHM_A, CDHHM_R, CDHHM_S, CDHHM_T,    KC_G,                                        KC_M, CDHHM_N, CDHHM_E, CDHHM_I, CDHHM_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
     OSL(MAC),    KC_Z,    KC_X,     KC_C,   KC_D,    KC_V,  KC_NO, KC_NO,    KC_NO, KC_NO,        KC_K,    KC_H, KC_COMM, KC_DOT, KC_SLSH,  KC_ENT,
  //`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                                   KC_NO, KC_NO, MO(NUM), MO(SYM), LT(NAV, KC_BSPC), LT(NAV, KC_SPC), MO(WIN), KC_MEH, KC_NO, KC_NO
                              //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
    ),

    [SYM] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      _______, KC_EXLM,   KC_AT, KC_LCBR, KC_RCBR, KC_PIPE,                                     KC_AMPR, KC_ASTR,   KC_LT,   KC_GT, KC_QUES, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, KC_HASH,  KC_DLR, KC_LPRN, KC_RPRN,  KC_GRV,                                     KC_MINS,  KC_EQL, KC_PLUS, KC_UNDS, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_BSLS,   KC_NO, KC_COMM,  KC_DOT, KC_SLSH, _______,
  //`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                              //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
    ),

    [NAV] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                                       KC_NO, KC_PGUP,   KC_UP,   KC_NO,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
   LCTL(KC_C), KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                                    KC_LSTRT, KC_LEFT, KC_DOWN, KC_RGHT, KC_LEND, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
       KC_APP, KC_UNDO,  KC_CUT, KC_COPY, _______, KC_PASTE, _______, _______, _______, _______, RCS(KC_TAB),  KC_PGDN, KC_NO, KC_NO, C(KC_TAB), _______,
  //`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                              //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
    ),

    [NUM] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,                                       KC_NO,    KC_7,    KC_8,    KC_9,   KC_NO, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,                                       KC_NO,    KC_4,    KC_5,    KC_6,   KC_NO, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______, _______, _______, _______,   KC_NO,    KC_1,    KC_2,    KC_3,   KC_NO, _______,
  //`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                                 _______, _______, _______, _______, _______, _______,   KC_NO,    KC_0,  KC_DOT, _______
                              //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
    ),


    [WIN] = LAYOUT(
  //,-----------------------------------------------------.                                   ,-----------------------------------------------------.
        RESET, _______, _______, KC_VOLU, _______, _______,                                       KC_NO,  WIN_TL,   WIN_U,  WIN_TR,  WIN_LG, ZOOM_IN,
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                       KC_NO,   WIN_L,   WIN_D,   WIN_R, WIN_FUL, WIN_PSC,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, KC_VOLD, KC_MUTE, _______, _______, _______, _______, _______,   KC_NO,  WIN_BL,   KC_NO,  WIN_BR,  WIN_SM, ZOOM_OUT,
  //`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                              //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
    ),


    [MAC] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, DM_PLY1, DM_PLY2,                                     _______, _______, MAC_USER, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, DM_RSTP, _______, _______,                                    CG_TOGG, _______, MAC_EMAIL, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, DM_REC1, DM_REC2, _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                              //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
    ),

};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_ln_P(PSTR("Kyria rev1.0"), false);
    // OS
    oled_write_P(PSTR("OS: "), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(PSTR("MAC"), false);
    } else {
        oled_write_P(PSTR("NIX"), false);
    }
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case CDH:
            oled_write_P(PSTR("Colemak DH\n"), false);
            break;
        case SYM:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case NUM:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case WIN:
            oled_write_P(PSTR("Window\n"), false);
            break;
        case MAC:
            oled_write_P(PSTR("Macros\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }


    // Write host Keyboard LED Status to OLEDs
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
}

bool oled_task_user(void) {
    render_status();
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Page up/down
        if (clockwise) {
            // tap_code(KC_PGUP);
            // tap_code(KC_UP);
            tap_code(KC_MS_WH_UP);
        } else {
            // tap_code(KC_PGDN);
            // tap_code(KC_DOWN);
            tap_code(KC_MS_WH_DOWN);
        }
    } else if (index == 1) {
        //  Tab next/previous
        if (clockwise) {
            tap_code16(S(C(KC_TAB)));
        } else {
            tap_code16(C(KC_TAB));
        }
    }
    return false;
}
#endif
