/*

                                        █         █    █            ▄▄▄▀▀▀▀▀▀▄▄▄        █▀▀▀▀▀▀▀▀▀▀█
                                        █        █     █          ▄▀            ▀▄      █          █
                                        █       █      █        ▄▀                ▀▄    █          █
                                        █      █       █        █                  █    █          █
                                        █     █        █       █                    █   █          █
                                        █    █         █       █                    █   █▄▄▄▄▄▄▄▄▄▄█
                                        █   █ █        █       █                    █   █      █
                                        █  █   █       █        █                  █    █       █
                                        █ █     █      █        ▀▄                ▄▀    █        █
                                        ██       █     █          ▀▄            ▄▀      █         █
                                        █         █    █▄▄▄▄▄▄▄▄    ▀▀▀▄▄▄▄▄▄▀▀▀        █          █

                                        ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
                                        D E F A U L T

*/
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "process_magic.h"
#include <string.h>
#include "klor.h"



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
  user_config.is_macos = true; // mac OS by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM
}
// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                                 │
// └───────────────────────────────────────────────────────────┘

enum layers {
  CDH = 0,
  SYM,
  NAV,
  NUM,
  WIN,
  MSE,
  MAC
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   k e y c o d e s                             │
// └───────────────────────────────────────────────────────────┘

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
  NAN_DPI,
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s                         │
// └───────────────────────────────────────────────────────────┘

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


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
   ┌───────────────────────────────────────────────────────────┐
   │ c o l e m a k                                             │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    Q    │    W    │    F    │    P    │    G    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    J    │    L    │    U    │    Y    │    ;    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   TAB   │    A    │    R    │    S    │    T    │    D    ├─╯                ╰─┤    H    │    N    │    E    │    I    │    O    │    "    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │   DEL   │    Z    │    X    │    C    │    V    │    B    ││ SHIFT  ││PLY/PSE ││    K    │    M    │    ,    │    .    │    /    │  SHIFT  │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │  CTRL   │  LOWER  │  SPACE  │   ALT   ││ CMD/WIN │  ENTER  │  RAISE  │  BSPCE  │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */


   [CDH] = LAYOUT_yubitsume(
              KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                          KC_J,     KC_L,     KC_U,     KC_Y,     KC_QUOT,
              CTL_A,    ALT_R,    GUI_S,    SHT_T,    KC_G,                          KC_M,     SHT_N,    GUI_E,    ALT_I,    CTL_O,
              KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,   KC_MUTE,   KC_MPLY,    KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,
                        MO(MAC),  MO(NUM),  LT(SYM, KC_ESC), LT(NAV, KC_BSPC),  LT(NAV, KC_SPC), LT(MSE, KC_ENT),  MO(WIN), MO(MAC)
 ),
   [SYM] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,                       KC_AMPR,  KC_ASTR,  KC_LT,    KC_GT,    KC_QUOT,
              KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,                        KC_MINS,  KC_EQL,   KC_PLUS,  KC_UNDS,  KC_SCLN,
              KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,   _______,  _______,  KC_BSLS,  KC_COLN, KC_COMM,   KC_DOT,   KC_SLSH,
                        _______, _______,  _______,  _______,   _______,  _______,  _______, _______
 ),

   [NAV] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  _______,  _______,  _______,                       KC_NO,    KC_PGUP,  KC_UP,    KC_NO,    KC_INS,
              KC_LCTL,  KC_LALT,  KC_LGUI,  KC_LSFT,  _______,                       KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END,
              KC_UNDO,  KC_CUT,   KC_COPY,  APP_MNU,  KC_PSTE,   _______,  _______,  TAB_PRV,  KC_PGDN,  KC_NO,    KC_NO,    TAB_NXT,
                        _______, _______,  _______,   KC_DEL,   KC_TAB,   _______,  _______, _______
 ),

   [NUM] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_F1,    KC_F2,    KC_F3,    KC_F4,    _______,                       KC_NO,    KC_7,     KC_8,     KC_9,     KC_NO,
              KC_F5,    KC_F6,    KC_F7,    KC_F8,    _______,                       KC_NO,    KC_4,     KC_5,     KC_6,     KC_NO,
              KC_F9,   KC_F10,    KC_F11,   KC_F12,   _______,   _______,  _______,  KC_NO,    KC_1,     KC_2,     KC_3,     KC_NO,
                       _______,   _______, _______,   _______,   KC_NO,    KC_0,  KC_DOT, _______
 ),

   [WIN] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  KC_VOLU,  _______,  _______,                       KC_NO,    ZOOM_IN,  WIN_U,    WIN_LG,   KC_NO,
              _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,                       SCRNSHT,  WIN_L,    WIN_D,    WIN_R,    WIN_FUL,
              _______,  _______,  KC_VOLD,  KC_MUTE,  _______,   _______,  _______,  _______,  ZOOM_OUT, KC_NO,    WIN_SM,   KC_NO,
                        _______, _______, _______,   _______,   _______,  _______,  _______, _______
 ),

   [MSE] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  KC_NO,    KC_MS_U,  KC_NO,    _______,                       NAN_DPI,  KC_WH_U,  _______,  _______,  _______,
              _______, KC_MS_L,   KC_MS_D,  KC_MS_R,  _______,                       KC_WH_L,  KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_WH_R,
              _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  KC_WH_D,  _______,  _______,  _______,
                       _______,   _______,  KC_LCTL,  KC_LSFT,   _______,  _______,  _______, _______
 ),

   [MAC] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷

              QK_BOOT,  _______,  _______,  DM_PLY1,  DM_PLY2,                       _______,  _______,  USERNAME, _______,  QK_BOOT,
              _______,  _______,  DM_RSTP,  _______,  _______,                       MACOS_TG, _______,  EMAIL,     OS_OUT,  _______,
              _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  DM_REC1,  DM_REC2,  _______,  _______,
                        _______,  _______,  _______,   _______,  _______,  _______,  _______, _______
 )

};



// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ O L E D                                                                                                                                    │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef OLED_ENABLE

// ┌───────────────────────────────────────────────────────────┐
// │ d y n a m i c   m a c r o                                 │
// └───────────────────────────────────────────────────────────┘

char layer_state_str[24];
char o_text[24] = "";
int dmacro_num = 0;

#ifdef DYNAMIC_MACRO_ENABLE
    char dmacro_text[4][24] = { "", "RECORDING", "STOP RECORDING",  "PLAY RECORDING"};
    static uint16_t dmacro_timer;
    const char PROGMEM rec_ico[] = {0xD1, 0xE1, 0};
    const char PROGMEM stop_ico[] = {0xD3, 0xE1, 0};
    const char PROGMEM play_ico[] = {0xD2, 0xE1, 0};


    // DYNMACRO RECORD ├─────────────────────────────────────────────────────────────┐
    void dynamic_macro_record_start_user(void) {
          dmacro_num = 1;
        return;
    }

    // DYNMACRO STOP RECORDING ├─────────────────────────────────────────────────────┐
    void dynamic_macro_record_end_user(int8_t direction) {
          dmacro_num = 2;
          dmacro_timer = timer_read();
        return;
    }

    // DYNMACRO PLAY RECORDING ├─────────────────────────────────────────────────────┐
    void dynamic_macro_play_user(int8_t direction) {
          dmacro_num = 3;
          dmacro_timer = timer_read();
        return;
    }
#endif //DYNAMIC_MACRO_ENABLE


void matrix_scan_user(void) {
  #ifdef DYNAMIC_MACRO_ENABLE
    // DynMacroTimer
    if(dmacro_num > 0){
        if (timer_elapsed(dmacro_timer) < 3000) {
            strcpy ( o_text, dmacro_text[dmacro_num] );
          }
        else {
            if (dmacro_num == 1) {
                strcpy ( o_text, dmacro_text[1] );
              }
            else {
                strcpy ( o_text, layer_state_str );
                dmacro_num = 0;
              }
          }
      }
   #endif //DYNAMIC_MACRO_ENABLE
}


// ┌───────────────────────────────────────────────────────────┐
// │ o l e d   g r a p h i c s                                 │
// └───────────────────────────────────────────────────────────┘

void render_os_lock_status(void) {
    static const char PROGMEM sep_v[] = {0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0};
    static const char PROGMEM sep_h1[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM sep_h2[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM face_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xE1, 0};
    static const char PROGMEM face_2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xE1, 0};
    static const char PROGMEM os_m_1[] = {0x95, 0x96, 0};
    static const char PROGMEM os_m_2[] = {0xB5, 0xB6, 0};
    static const char PROGMEM os_w_1[] = {0x97, 0x98, 0};
    static const char PROGMEM os_w_2[] = {0xB7, 0xB8, 0};
    static const char PROGMEM s_lock[] = {0x8F, 0x90, 0};
    static const char PROGMEM n_lock[] = {0x91, 0x92, 0};
    static const char PROGMEM c_lock[] = {0x93, 0x94, 0};
    static const char PROGMEM b_lock[] = {0xE1, 0xE1, 0};

// os mode status ────────────────────────────────────────┐

    oled_write_ln_P(sep_v, false);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(os_m_1, false); // ──── MAC
    } else {
        oled_write_P(os_w_1, false); // ──── WIN
    }

    oled_write_P(sep_h1, false);
    oled_write_P(face_1, false);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(os_m_2, false); // ──── MAC
    } else {
        oled_write_P(os_w_2, false); // ──── WIN
    }

    oled_write_P(sep_h1, false);
    oled_write_P(face_2, false);
    oled_write_ln_P(sep_v, false);


// lock key layer status ─────────────────────────────────┐

    led_t led_usb_state = host_keyboard_led_state();

    if (led_usb_state.num_lock) {
        oled_write_P(n_lock, false); // ──── NUMLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    if (led_usb_state.caps_lock) {
        oled_write_P(c_lock, false); // ─── CAPSLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    if (led_usb_state.scroll_lock) { // ─ SCROLLLOCK
        oled_write_P(s_lock, false);
    } else {
        oled_write_P(b_lock, false);
    }

// hardware feature status ──────────────────────────────┐

    oled_write_P(sep_h2, false);
}


// layer status ──────────────────────────────────────────┐

int layerstate = 0;

layer_state_t layer_state_set_kb(layer_state_t state) {
      switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                strcpy ( layer_state_str, "CDH");
                break;
            case 1:
                strcpy ( layer_state_str, "SYM");
                break;
            case 2:
                strcpy ( layer_state_str, "NAV");
                break;
            case 3:
                strcpy ( layer_state_str, "NUM");
                break;
            case 4:
                strcpy ( layer_state_str, "WIN");
                break;
            case 5:
                strcpy ( layer_state_str, "MSE");
                break;
            case 6:
                strcpy ( layer_state_str, "MAC");
                break;
            default:
                strcpy ( layer_state_str, "XXXXXX");
        }
      if (dmacro_num < 1) {
          strcpy ( o_text, layer_state_str );
    }
    return state;
    // return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


// ┌───────────────────────────────────────────────────────────┐
// │ w r i t e   t o   o l e d                                 │
// └───────────────────────────────────────────────────────────┘

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {  // ────────────────────────── PRIMARY SIDE

        // layer status ──────────────────────────────────────────────────┐
        #ifdef DYNAMIC_MACRO_ENABLE
            if(dmacro_num == 1){ oled_write_P(rec_ico, false); }
            if(dmacro_num == 2){ oled_write_P(stop_ico, false); }
            if(dmacro_num == 3){ oled_write_P(play_ico, false); }
        #endif //DYNAMIC_MACRO_ENABLE

        oled_write_ln(o_text, false);
        render_os_lock_status();

    } else {  // ─────────────────────────────────────────── SECONDARY SIDE

        // KLOR face ─────────────────────────────────────────────────────┐

        static const char PROGMEM klor_face[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
            0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0,
            0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        oled_write_raw_P(klor_face, sizeof(klor_face));
    }
    return false;
}
#endif // OLED_ENABLE



// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case SHT_T:
//             return TAPPING_TERM - 150;
//         case SHT_N:
//             return TAPPING_TERM - 150;
//         default:
//             return TAPPING_TERM;
//     }
// }


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ M A C R O S                                                                                                                                │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACOS_TG:
      if (record->event.pressed) {
        user_config.is_macos ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
        if (ENABLE_CTL_GUI_SWAP) {
          // Swap Control and Super/GUI keys when in mac OS.
          // Unlike register_mods(mod_config(MOD_LCTL)),
          // SEND_STRING does not apply the swapped modifiers--CTL is CTL, GUI is GUI.
          // Use swap by karabiner instead of in firmware.
          if (user_config.is_macos) {
            process_magic(MAGIC_SWAP_CTL_GUI, record);
          } else {
            process_magic(MAGIC_UNSWAP_CTL_GUI, record);
          }
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
        // SEND_STRING(user_config.is_macos ? "macOS" : "linux");
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


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ E N C O D E R                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef ENCODER_ENABLE

// ┌───────────────────────────────────────────────────────────┐
// │ e n c o d e r  L                                          │
// └───────────────────────────────────────────────────────────┘

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }

// ┌───────────────────────────────────────────────────────────┐
// │ e n c o d e r  R                                          │
// └───────────────────────────────────────────────────────────┘

    } else if (index == 1) {
      if(IS_LAYER_ON(CDH)){
          if (clockwise) {
              tap_code(KC_MNXT);
          } else {
              tap_code(KC_MPRV);
          }
      }else {
            if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
      }
    }
    return true;
}

#endif // ENCODER_ENABLE



/*

                                                       ▐█    ▟▛ ▐█     ▄▆▀▀▀▀▀▀▆▄  ▐█▀▀▀▀▀█▌
                                                       ▐█   ▟▛  ▐█    ▟▛        ▜▙ ▐█     █▌
                                                       ▐█  ▟▛   ▐█   ▐█          █▋▐█     █▌
                                                       ▐█ ▟█▙   ▐█   ▐█          █▋▐█▀▀▜█▀▀▘
                                                       ▐█▟▛ ▜▙  ▐█    ▜▙        ▟▛ ▐█   ▜▙
                                                       ▐█▛   ▜▙ ▐█▄▄▄▄ ▀▜▆▄▄▄▄▆▛▀  ▐█    ▜▙

                                                                 ▄██████████████▄
                                                                 ████████████████
                                                            ▄██████▀  ▀████▀  ▀██████▄
                                                            ███████▄  ▄████▄  ▄███████
                                                            ███████████▀▀▀▀███████████
                                                            ▀█████████▀ ▄▄ ▀█████████▀
                                                                 ████▀ ▄██▄ ▀████
                                                                 ████▄▄████▄▄████

*/



