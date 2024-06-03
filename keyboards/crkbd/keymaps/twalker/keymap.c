#include QMK_KEYBOARD_H
#include "process_magic.h"
#include <stdio.h>

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
  WIN_SM
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
        SEND_STRING("tim.twalker@gmail.com");
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
  }

  return true;
}
#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Colemak DH
  [CDH] = LAYOUT_split_3x6_3(
  //,--------+--------+--------+--------+--------+--------.                    ,--------+--------+--------+--------+--------+--------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, CDHHM_A, CDHHM_R, CDHHM_S, CDHHM_T,    KC_G,                         KC_M, CDHHM_N, CDHHM_E, CDHHM_I, CDHHM_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     OSL(MAC),    KC_Z,    KC_X,     KC_C,   KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MO(NUM), MO(SYM), LT(NAV, KC_BSPC),  LT(NAV, KC_SPC), LT(WIN, KC_ENT), MO(MSE)
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
      _______, _______, _______, _______, _______, _______,                        KC_NO, KC_PGUP,   KC_UP,   KC_NO,  KC_INS, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                     KC_LSTRT, KC_LEFT, KC_DOWN, KC_RGHT, KC_LEND, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_UNDO,  KC_CUT, KC_COPY, APP_MNU, KC_PSTE,                      TAB_PRV, KC_PGDN,   KC_NO,   KC_NO, TAB_NXT, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  KC_DEL,     KC_TAB, _______, _______
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
      _______, _______, _______, KC_VOLU, _______, _______,                       KC_NO,  ZOOM_IN,   WIN_U,  WIN_LG,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                       KC_NO,   WIN_L,    WIN_D,   WIN_R, WIN_FUL, SCRNSHT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, KC_VOLD, KC_MUTE, _______,                       KC_NO, ZOOM_OUT,   KC_NO,  WIN_SM,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // Macros
  [MAC] = LAYOUT_split_3x6_3(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      QK_BOOT, _______, _______, _______, DM_PLY1, DM_PLY2,                                     _______, _______, USERNAME, _______, _______,QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, DM_RSTP, _______, _______,                                    MACOS_TG, _______,   EMAIL, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, DM_REC1,    DM_REC2, _______, _______
                                      //`--------------------------'  `--------------------------'
    ),

  // Mouse
  [MSE] = LAYOUT_split_3x6_3(
  //,--------+--------+--------+--------+--------+--------.                                   ,--------+--------+--------+--------+--------+--------.
      TO(CDH), _______,   KC_NO, KC_MS_U,   KC_NO, _______,                                     _______, KC_WH_U, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                                     KC_WH_L, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_R, _______,
  //|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                     _______, KC_WH_D, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______, _______, _______, _______
                                      //`--------------------------' `--------------------------'
    ),
};

#ifdef OLED_ENABLE
// TODO: Add OS selection to OLED display
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
        case MSE:
            oled_write_ln_P(PSTR("Mouse"), false);
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
