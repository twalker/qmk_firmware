#include QMK_KEYBOARD_H
#include <stdio.h>
#include "process_magic.h"

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
void eeconfig_init_user(void) {  // EEPROM is getting reset
  user_config.raw = 0;
  user_config.is_macos = true; // mac OS by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM
}

enum layers {
  CDH = 0,
  SYM,
  NAV,
  NUM,
  WIN,
  MSE,
  MAC
};

// COLEMAK DH homerow mods
// Left-hand
#define CTL_A LCTL_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define GUI_S LGUI_T(KC_S)
#define SHT_T LSFT_T(KC_T)
// Right-hand
#define SHT_N RSFT_T(KC_N)
#define GUI_E RGUI_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define CTL_O RCTL_T(KC_O)

// Tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SHT_T:
      return TT_SHIFT;
    case SHT_N:
      return TT_SHIFT;
    case ALT_R:
      return TT_ALT;
    case ALT_I:
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

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
  set_auto_mouse_layer(MSE);
  set_auto_mouse_enable(true);
}
#endif

#ifdef POINTING_DEVICE_ENABLE
// mouse DPI speed toggling (sniper mode)
const int mouse_dpi_settings[] = MSE_DPI_OPTIONS;
int current_dpi_index = 0;
void cycle_dpi(void){
  current_dpi_index = (current_dpi_index + 1) % (sizeof(mouse_dpi_settings) / sizeof(mouse_dpi_settings[0]));
  pointing_device_set_cpi(mouse_dpi_settings[current_dpi_index]);
}

// Drag scroll
bool set_scrolling = false;
// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 100.0
#define SCROLL_DIVISOR_V 100.0
// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}
#endif

#ifdef DYNAMIC_MACRO_ENABLE
// Macros
enum custom_keycodes {
  MACOS_TG = SAFE_RANGE,
  USERNAME,
  EMAIL,
  OS_OUT,
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
  MSE_DPI,
  MSE_DRG,
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
          // Use swap by karabiner instead of in firmware.
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
    case OS_OUT:
      if (record->event.pressed) {
        SEND_STRING(user_config.is_macos ? "macOS" : "linux");
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
    // Trackball commands
    case MSE_DPI:
      if (record->event.pressed) {
        // Cycle trackball DPI
        cycle_dpi();
      }
      return false;
    case MSE_DRG:
      // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
      set_scrolling = record->event.pressed;
      return false;
  }

  return true;
}

#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [CDH] = LAYOUT_split_3x5_4(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷
     KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,      KC_J,     KC_L,     KC_U,     KC_Y,     KC_QUOT,
     CTL_A,    ALT_R,    GUI_S,    SHT_T,    KC_G,      KC_M,     SHT_N,    GUI_E,    ALT_I,    CTL_O,
     KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,      KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,
               MO(NUM),  LT(SYM, KC_ESC), LT(NAV, KC_BSPC), MO(MSE),/**/MO(MAC), LT(NAV, KC_SPC), LT(SYM, KC_ENT),  MO(WIN)
 ),

   [SYM] = LAYOUT_split_3x5_4(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷
     KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,   KC_AMPR,  KC_ASTR,  KC_LT,    KC_GT,    KC_QUOT,
     KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,    KC_MINS,  KC_EQL,   KC_PLUS,  KC_UNDS,  KC_SCLN,
     KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,   KC_BSLS,  KC_COLN, KC_COMM,   KC_DOT,   KC_SLSH,
               _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 ),

   [NAV] = LAYOUT_split_3x5_4(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷
     _______,  _______,  _______,  _______,  _______,   KC_NO,    KC_PGUP,  KC_UP,    KC_NO,    KC_INS,
     KC_LCTL,  KC_LALT,  KC_LGUI,  KC_LSFT,  _______,   KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END,
     KC_UNDO,  KC_CUT,   KC_COPY,  APP_MNU,  KC_PSTE,   TAB_PRV,  KC_PGDN,  KC_NO,    KC_NO,    TAB_NXT,
               _______,  _______,   KC_DEL,   _______,  _______,  KC_TAB,   _______,  _______
 ),

   [NUM] = LAYOUT_split_3x5_4(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷
     KC_F1,    KC_F2,    KC_F3,    KC_F4,    _______,   KC_NO,    KC_7,     KC_8,     KC_9,     KC_NO,
     KC_F5,    KC_F6,    KC_F7,    KC_F8,    _______,   KC_NO,    KC_4,     KC_5,     KC_6,     KC_NO,
     KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,   KC_NO,    KC_1,     KC_2,     KC_3,     KC_NO,
               _______,  _______, _______,   _______,   _______,  KC_NO,    KC_0,     KC_DOT
 ),

   [WIN] = LAYOUT_split_3x5_4(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷
     _______,  _______,  KC_VOLU,  _______,  _______,   KC_NO,    ZOOM_IN,  WIN_U,    WIN_LG,   KC_NO,
     _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,   SCRNSHT,  WIN_L,    WIN_D,    WIN_R,    WIN_FUL,
     _______,  _______,  KC_VOLD,  KC_MUTE,  _______,   _______,  ZOOM_OUT, KC_NO,    WIN_SM,   KC_NO,
               _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 ),

   [MSE] = LAYOUT_split_3x5_4(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷
     _______,  KC_NO,    KC_MS_U,  KC_NO,    _______,   MSE_DPI,  KC_WH_U,  MSE_DRG,  _______,  _______,
     _______, KC_MS_L,   KC_MS_D,  KC_MS_R,  _______,   KC_WH_L,  KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_WH_R,
     _______,  _______,  _______,  _______,  _______,   _______,  KC_WH_D,  _______,  _______,  _______,
               _______,  KC_LCTL,  KC_LSFT,  _______,   _______,  KC_LSFT,  KC_LGUI,  _______

 ),

   [MAC] = LAYOUT_split_3x5_4(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷
     QK_BOOT,  _______,  _______,  DM_PLY1,  DM_PLY2,   _______,  _______,  USERNAME, _______,  QK_BOOT,
     _______,  _______,  DM_RSTP,  _______,  _______,   MACOS_TG, _______,  EMAIL,     OS_OUT,  _______,
     _______,  _______,  _______,  _______,  _______,   _______,  DM_REC1,  DM_REC2,  _______,  _______,
               _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 ),
};
