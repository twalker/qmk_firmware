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
          process_magic(MAGIC_SWAP_CTL_GUI, record);
        } else {
          process_magic(MAGIC_UNSWAP_CTL_GUI, record);
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
     KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,   KC_NO,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
     KC_ESC, CDHHM_A, CDHHM_R, CDHHM_S, CDHHM_T,    KC_G,                                        KC_M, CDHHM_N, CDHHM_E, CDHHM_I, CDHHM_O, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
   OSL(MAC),    KC_Z,    KC_X,     KC_C,   KC_D,    KC_V,   KC_NO,   KC_NO,  MO(MSE),  KC_NO,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
//`--------+--------+--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------+--------.
                             KC_KB_MUTE,   KC_NO, MO(NUM), MO(SYM), LT(NAV, KC_BSPC),  LT(NAV, KC_SPC), LT(WIN, KC_ENT),  MO(MSE), KC_NO, WIN_FUL
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
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                       KC_NO,   WIN_L,   WIN_D,   WIN_R, WIN_FUL, SCRNSHT,
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
    TO(CDH), _______,   KC_NO, KC_MS_U,   KC_NO, _______,                                     NAN_DPI, KC_WH_U, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                                     KC_WH_L, KC_BTN1, KC_BTN2, KC_BTN3, KC_WH_R, _______,
//|--------+--------+--------+--------+--------+--------|                                   |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_D, _______, _______, _______, _______,
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
  // clang-format off
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
  };
  // clang-format on
  oled_write_P(qmk_logo, false);
}


static void render_kyria_logo(void) {
  // clang-format off
  static const char PROGMEM kyria_logo[] = {
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
      0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
      0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  };
  // clang-format on
  oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
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


bool oled_task_user(void) {
    if (is_keyboard_master()) {
      render_status();
    } else {
      render_kyria_logo();
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
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
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
