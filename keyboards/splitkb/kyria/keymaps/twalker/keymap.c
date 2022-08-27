#include QMK_KEYBOARD_H


// Store is_macos in EEPROM.
typedef union {
  uint32_t raw;
  struct {
    bool is_macos :1;
  };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
}
void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.is_macos = false; // Disable want mac OS by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM
}

enum layers {
  CDH = 0,
  SYM,
  NAV,
  NUM,
  WIN,
  MAC
};

void matrix_init_user(void) {
  if (user_config.is_macos) {
    set_unicode_input_mode(UC_OSX);
  } else {
    set_unicode_input_mode(UC_LNX);
  }
}

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

// Tapping force per key
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(NAV, KC_BSPC):
    case LT(NAV, KC_SPC):
      return false;
    default:
      return true;
  }
}


#ifdef DYNAMIC_MACRO_ENABLE
// Macros
enum custom_keycodes {
  MACOS_TG = SAFE_RANGE,
  USERNAME,
  EMAIL,
  KC_LSTRT,
  KC_LEND,
  ZOOM_IN,
  ZOOM_OUT,
  SCRNSHT,
  TAB_PRV,
  TAB_NXT,
  WIN_L,
  WIN_R,
  WIN_U,
  WIN_D,
  WIN_FUL,
  WIN_LG,
  WIN_SM
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACOS_TG:
      if (record->event.pressed) {
        user_config.is_macos ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
      }
      break;
    case USERNAME:
      if (record->event.pressed) {
        SEND_STRING("tiwalker");
      }
      break;

    case EMAIL:
      if (record->event.pressed) {
        SEND_STRING("tiwalker@starbucks.com");
      }
      break;
    case KC_LSTRT:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
        } else {
          tap_code(KC_HOME);
        }
      }
      break;
    case KC_LEND:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_RGHT)));
        } else {
          tap_code(KC_END);
        }
      }
      break;
    case KC_COPY:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI("c"));
        } else {
          SEND_STRING(SS_LCTL("c"));
        }
      }
      return false;
    case KC_PSTE:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI("v"));
        } else {
          SEND_STRING(SS_LCTL("v"));
        }
      }
      return false;
    case KC_CUT:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI("x"));
        } else {
          SEND_STRING(SS_LCTL("x"));
        }
      }
      return false;
    case KC_UNDO:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI("z"));
        } else {
          SEND_STRING(SS_LCTL("z"));
        }
      }
      return false;

    case TAB_NXT:
      if (record->event.pressed) {
        // CTL+TAB on Mac, but we have CTL and GUI swapped
        if (user_config.is_macos) {
          register_mods(mod_config(MOD_LGUI));
        } else {
          register_mods(mod_config(MOD_LCTL));
        }
        register_code(KC_TAB);
      } else {
        if (user_config.is_macos) {
          unregister_mods(mod_config(MOD_LGUI));
        } else {
          unregister_mods(mod_config(MOD_LCTL));
        }
        unregister_code(KC_TAB);
      }
      break;
    case TAB_PRV:
      if (record->event.pressed) {
        // CTL+SFT+TAB on Mac, but we have CTL and GUI swapped
        if (user_config.is_macos) {
          register_mods(mod_config(MOD_LGUI));
        } else {
          register_mods(mod_config(MOD_LCTL));
        }
        register_mods(mod_config(MOD_LSFT));
        register_code(KC_TAB);
      } else {
        if (user_config.is_macos) {
          unregister_mods(mod_config(MOD_LGUI));
        } else {
          unregister_mods(mod_config(MOD_LCTL));
        }
        unregister_mods(mod_config(MOD_LSFT));
        unregister_code(KC_TAB);
      }
      break;
    case ZOOM_IN:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_LCTL));
        register_code(KC_EQL);
      } else {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(KC_EQL);
      }
      break;
    case ZOOM_OUT:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_LCTL));
        register_code(KC_MINS);
      } else {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(KC_MINS);
      }
      break;
    case SCRNSHT:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          // Shift+CMD+5 for Skitch capture.
          SEND_STRING(SS_LGUI(SS_LSFT("5")));
        } else {
          tap_code16(KC_PSCR);
        }
      }
      break;
    // Window management (rectange on macos)
    case WIN_L:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          // Actual: (LCA(KC_LEFT))
          SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_LEFT))));
        } else {
          // Pop OS
          SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_LEFT))));
        }
      }
      break;
    case WIN_R:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_RGHT))));
        } else {
          SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_RGHT))));
        }
      }
      break;
    case WIN_U:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_UP))));
        } else {
          SEND_STRING(SS_LGUI(SS_LCTRL(SS_TAP(X_UP))));
        }
      }
      break;
    case WIN_D:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DOWN))));
        } else {
          SEND_STRING(SS_LGUI(SS_LCTRL(SS_TAP(X_DOWN))));
        }
      }
      break;
    case WIN_FUL:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_ENTER))));
        } else {
          SEND_STRING(SS_LGUI(SS_TAP(X_M)));
        }
      }
      break;
     
    // TOREVISIT: SM and LG on Pop os 
    case WIN_LG:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_EQL))));
        } else {
          SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)) SS_LSFT(SS_TAP(X_RGHT)) SS_TAP(X_ESC));
        }
      }
      break;
    case WIN_SM:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_MINS))));
        } else {
          SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)) SS_LSFT(SS_TAP(X_LEFT)) SS_TAP(X_ESC));
        }
      }
      break;
  }

  return true;
}
#endif

// Keymap array
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CDH] = LAYOUT(
//,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
     KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_NO /* To become DEL*/,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
     KC_ESC, CDHHM_A, CDHHM_R, CDHHM_S, CDHHM_T,    KC_G,                                        KC_M, CDHHM_N, CDHHM_E, CDHHM_I, CDHHM_O, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
   OSL(MAC),    KC_Z,    KC_X,     KC_C,   KC_D,    KC_V,  KC_NO,  KC_NO,   KC_NO, KC_NO,        KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
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
    _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                                    KC_LSTRT, KC_LEFT, KC_DOWN, KC_RGHT, KC_LEND, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
     KC_APP, KC_UNDO,  KC_CUT, KC_COPY, _______, KC_PSTE, _______, _______, _______, _______, TAB_PRV, KC_PGDN,   KC_NO,   KC_NO, TAB_NXT, _______,
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
    _______, _______, _______, KC_VOLU, _______, _______,                                       KC_NO,   KC_NO,   WIN_U,   KC_NO,  WIN_LG, ZOOM_IN,
//,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                       KC_NO,   WIN_L,   WIN_D,   WIN_R, WIN_FUL, SCRNSHT,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, KC_VOLD, KC_MUTE, _______, _______, _______, _______, _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  WIN_SM, ZOOM_OUT,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                            //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
  ),


  [MAC] = LAYOUT(
//,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      RESET, _______, _______, _______, DM_PLY1, DM_PLY2,                                     _______, _______, USERNAME, _______, _______,  RESET,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, DM_RSTP, _______, _______,                                    MACOS_TG, _______,   EMAIL, _______, _______, _______,
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
  if (user_config.is_macos) {
    oled_write_P(PSTR("MAC"), false);
  } else {
    oled_write_P(PSTR("Linux"), false);
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
      tap_code(KC_PGUP);
    } else {
      tap_code(KC_PGDN);
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
