#include QMK_KEYBOARD_H
#include "process_magic.h"
#include "icons.h"

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
  MAC,
  MSE
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
  APP_MNU,
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
  WIN_SM,
  NAN_DPI
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACOS_TG:
      if (record->event.pressed) {
        user_config.is_macos ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        // Swap Control and Super/GUI keys when in mac OS.
        // Unlike register_mods(mod_config(MOD_LCTL)),
        // SEND_STRING does not apply the swapped modifiers--CTL is CTL, GUI is GUI.
        if (user_config.is_macos) {
          process_magic(QK_MAGIC_SWAP_CTL_GUI, record);
        } else {
          process_magic(QK_MAGIC_UNSWAP_CTL_GUI, record);
        }
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
    case APP_MNU:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          // Opens mac OS's menu bar search
          SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_SLSH))));
        } else {
          // Application context menu on linux
          SEND_STRING(SS_TAP(X_APP));
        }
      }
      return false;
    case KC_LSTRT:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
        } else {
          tap_code(KC_HOME);
        }
      }
      return false;
    case KC_LEND:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_RGHT)));
        } else {
          tap_code(KC_END);
        }
      }
      return false;
    case KC_COPY:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_C)));
        } else {
          SEND_STRING(SS_LCTL(SS_TAP(X_C)));
        }
      }
      return false;
    case KC_PSTE:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_V)));
        } else {
          SEND_STRING(SS_LCTL(SS_TAP(X_V)));
        }
      }
      return false;
    case KC_CUT:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_X)));
        } else {
          SEND_STRING(SS_LCTL(SS_TAP(X_X)));
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
        SEND_STRING(SS_LCTL(SS_TAP(X_TAB)));
      }
      return false;
    case TAB_PRV:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))));
      }
      return false;
    case ZOOM_IN:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_EQL)));
        } else {
          SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_EQL))));
        }
      }
      return false;
    case ZOOM_OUT:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LGUI(SS_TAP(X_MINS)));
        } else {
          SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_MINS))));
        }
      }
      return false;
    case SCRNSHT:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          // Shift+CMD+5 for Skitch capture.
          SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_5))));
        } else {
          tap_code16(KC_PSCR);
        }
      }
      return false;
    // Window management (rectange on macos)
    case WIN_L:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_LEFT))));
        } else {
          // Pop OS
          SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_LEFT))));
        }
      }
      return false;
    case WIN_R:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_RGHT))));
        } else {
          SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_RGHT))));
        }
      }
      return false;
    case WIN_U:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_UP))));
        } else {
          SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_UP))));
        }
      }
      return false;
    case WIN_D:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DOWN))));
        } else {
          SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_DOWN))));
        }
      }
      return false;
    case WIN_FUL:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_ENTER))));
        } else {
          SEND_STRING(SS_LGUI(SS_TAP(X_M)));
        }
      }
      return false;

    // TOREVISIT: SM and LG on Pop os
    case WIN_LG:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_EQL))));
        } else {
          SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)) SS_LSFT(SS_TAP(X_RGHT)) SS_TAP(X_ESC));
        }
      }
      return false;
    case WIN_SM:
      if (record->event.pressed) {
        if (user_config.is_macos) {
          SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_MINS))));
        } else {
          SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)) SS_LSFT(SS_TAP(X_LEFT)) SS_TAP(X_ESC));
        }
      }
      return false;
    // Ploopy Nano commands
    case NAN_DPI:
      if (record->event.pressed) {
        // Capslock works for macro on MacOS, and numlock works for macro on linux.
        // Using capslock on MacOS, and numlock on Linux to cycle DPI.
        if (user_config.is_macos) {
          SEND_STRING(SS_TAP(X_CAPS_LOCK) SS_TAP(X_CAPS_LOCK));
        } else {
          SEND_STRING(SS_TAP(X_NUM_LOCK) SS_TAP(X_NUM_LOCK));
        }
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
      KC_NO,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT,   KC_NO,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      KC_NO, CDHHM_A, CDHHM_R, CDHHM_S, CDHHM_T,    KC_G,                                        KC_M, CDHHM_N, CDHHM_E, CDHHM_I, CDHHM_O,   KC_NO,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
   OSL(MAC),    KC_Z,    KC_X,     KC_C,   KC_D,    KC_V,   KC_NO,   KC_NO,  MO(MSE),  KC_NO,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,   KC_NO,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                             KC_KB_MUTE,   KC_NO, MO(NUM), LT(SYM, KC_ESC), LT(NAV, KC_BSPC),  LT(NAV, KC_SPC), LT(MSE, KC_ENT),  MO(WIN), KC_NO, WIN_FUL
                            //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
  ),

  [SYM] = LAYOUT(
//,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
    _______, KC_EXLM,   KC_AT, KC_LCBR, KC_RCBR, KC_PIPE,                                     KC_AMPR, KC_ASTR,   KC_LT,   KC_GT, KC_QUOT, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, KC_HASH,  KC_DLR, KC_LPRN, KC_RPRN,  KC_GRV,                                     KC_MINS,  KC_EQL, KC_PLUS, KC_UNDS, KC_SCLN, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_BSLS, KC_COLN, KC_COMM,  KC_DOT, KC_SLSH, _______,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                            //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
  ),

  [NAV] = LAYOUT(
//,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
    _______, _______, _______, _______, _______, _______,                                       KC_NO, KC_PGUP,   KC_UP,   KC_NO,  KC_INS, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                                    KC_LSTRT, KC_LEFT, KC_DOWN, KC_RGHT, KC_LEND, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, KC_UNDO,  KC_CUT, KC_COPY, APP_MNU, KC_PSTE, _______, _______, _______, _______, TAB_PRV, KC_PGDN,   KC_NO,   KC_NO, TAB_NXT, _______,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                               _______, _______, _______, _______,  KC_DEL, KC_TAB, _______, _______, _______, _______
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
                               _______, _______, _______, _______, _______,   KC_NO,    KC_0,  KC_DOT,  KC_NO,   KC_NO
    //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
  ),


  [WIN] = LAYOUT(
//,-----------------------------------------------------.                                   ,-----------------------------------------------------.
    _______, _______, _______, KC_VOLU, _______, _______,                                       KC_NO, ZOOM_IN,   WIN_U,  WIN_LG,   KC_NO,   KC_NO,
//| -------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                     SCRNSHT,   WIN_L,   WIN_D,   WIN_R, WIN_FUL,   KC_NO,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, KC_VOLD, KC_MUTE, _______, _______, _______, _______, _______,   KC_NO,ZOOM_OUT,   KC_NO,   WIN_SM,  KC_NO,   KC_NO,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                            //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
  ),


  [MAC] = LAYOUT(
//,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
    QK_BOOT, _______, _______, _______, DM_PLY1, DM_PLY2,                                     _______, _______, USERNAME, _______, _______,QK_BOOT,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    RGB_TOG, _______, _______, DM_RSTP, _______, _______,                                    MACOS_TG, _______,   EMAIL, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______, _______, DM_REC1, DM_REC2, _______, _______, _______, _______, _______, _______, _______,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                            //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
  ),

  [MSE] = LAYOUT(
//,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
    _______, _______,   KC_NO, KC_MS_U,   KC_NO, _______,                                     NAN_DPI, KC_WH_U, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                                     KC_WH_L, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_R, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______, KC_LCTL, KC_LSFT, _______, _______, _______, KC_WH_D, _______, _______, _______, _______,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                            //`---O---+--------+--------+--------+--------|--------+--------+--------+--------+---O----'
  ),
};


#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

static void render_status(void) {
  // QMK Logo and version
  render_qmk_logo();
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
    case MSE:
      oled_write_P(PSTR("Mouse\n"), false);
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

static void render_icon(void) {
  switch (get_highest_layer(layer_state)) {
    case SYM:
      render_sym_icon();
      break;
    case NUM:
      render_num_icon();
      break;
    case NAV:
      render_nav_icon();
      break;
    case WIN:
      render_win_icon();
      break;
    case MSE:
      render_mouse_icon();
      break;
    case MAC:
      render_cat_icon();
      break;
    default:
      if (user_config.is_macos) {
        render_base_icon_macos();
      } else {
        render_base_icon_linux();
      }
  }
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
      render_icon();
    } else {
      render_status();
    }
    return false;
}

#endif

#ifdef ENCODER_ENABLE
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    // Volume control
    if (!clockwise) {
      if (user_config.is_macos) {
        tap_code(KC_VOLD);
      } else {
        tap_code(KC_VOLU);
      }
    } else {
      if (user_config.is_macos) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
    }
  } else if (index == 1) {
    // Alt-Tab window switcher
    if (!clockwise) {
      if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      tap_code16(KC_TAB);
    } else {
      if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      tap_code16(S(KC_TAB));
    }
  }
  return false;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

#endif

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case NAV:
      rgblight_sethsv(HSV_TEAL);
      break;
    case SYM:
      rgblight_sethsv(HSV_CHARTREUSE);
      break;
    case NUM:
      rgblight_sethsv(HSV_ORANGE);
      break;
    case WIN:
      rgblight_sethsv(HSV_YELLOW);
      break;
    case MAC:
      rgblight_sethsv(HSV_RED);
      break;
    case MSE:
      rgblight_sethsv(HSV_PURPLE);
      break;
    default: // for any other layers, or the default layer
      if (user_config.is_macos) {
        rgblight_sethsv(HSV_BLUE);
      } else {
        rgblight_sethsv(HSV_GREEN);
      }
      break;
  }
  return state;
}
#endif
