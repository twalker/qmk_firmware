#include QMK_KEYBOARD_H

enum layers {
    CDH = 0,
    SYM,
    NAV,
    NUM,
    WIN,
    MOUSE
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

// Tap dance
enum {
  TD_TBCP = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TBCP] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_CAPS)
};

// Keymap array
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * Base Layer: Colemak DH
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |  TAB   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  BS    |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |  ESC   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |  O   |  ' "   |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        |   Z  |   X  |   C  |   D  |   V  |      | WIN  |  | MS   |      |   K  |   H  | ,  < | . >  | /  ? | Enter  |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      | Space|      |      |      |
    *                        |      | Num  | Sym  | Nav  | BSPC |  | DEL  | Nav  |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [CDH] = LAYOUT(
      TD(TD_TBCP),  KC_Q,   KC_W,     KC_F,   KC_P,   KC_B,                                       KC_J,   KC_L,   KC_U,   KC_Y,    KC_SCLN, KC_BSPC,
      KC_ESC, CDHHM_A, CDHHM_R,   CDHHM_S, CDHHM_T,   KC_G,                                       KC_M, CDHHM_N, CDHHM_E, CDHHM_I, CDHHM_O, KC_QUOT,
       KC_NO,    KC_Z,   KC_X,     KC_C,   KC_D,   KC_V, KC_NO, MO(WIN),      MO(MOUSE), KC_NO, KC_K,    KC_H, KC_COMM, KC_DOT, KC_SLSH,  KC_ENT,
                       KC_NO,  MO(NUM), MO(SYM), MO(NAV), KC_BSPC,           KC_DEL, LT(NAV, KC_SPC), KC_NO,  KC_NO, KC_NO
    ),

    /*
    * Symbols
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |        |  !   |  @   |  {   |  }   |  |   |                              |  &   |  *   |  <   |  >   |  ?   |        |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |        |  #   |  $   |  (   |  )   |  `   |                              |   -  |  =   |  +   |  _   | ; :  |  ' "   |
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   \  |      |  ,   |  .   |  / ? |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [SYM] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     KC_AMPR, KC_ASTR,  KC_LT,   KC_GT, KC_QUES, _______,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_MINS, KC_EQL, KC_PLUS, KC_UNDS, KC_SCLN, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_BSLS, KC_NO,  KC_COMM,  KC_DOT, KC_SLSH, _______,
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
      _______, OS_UNDO, OS_CUT,  OS_COPY, OS_PSTE, OS_PSTE, _______, _______, _______, _______, RCS(KC_TAB), KC_NO, KC_NO, C(KC_TAB), _______, _______,
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
                                _______, _______, _______, _______, _______, _______,  KC_NO, KC_0,  KC_DOT, _______
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
    * | PLY1   | UNDO | CUT  | COPY | PSTE |      | RSTP | REC1 |  |      |      |      |      |      |      |      |        |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |      | ACL1 | ACL2 | BTN1 | BTN2 |  |      |      |      |      |      |
    *                        |      |      |      |      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    */
    [MOUSE] = LAYOUT(
      _______, KC_NO,    KC_NO,  KC_NO,   KC_NO,   _______,                                     KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
      DM_PLY1, OS_UNDO, OS_CUT,  OS_COPY, OS_PSTE, _______, DM_RSTP, DM_REC1, _______, _______, KC_NO,     KC_NO,   KC_NO,   KC_NO, _______, _______,
                                 _______, KC_ACL1, KC_ACL2, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______
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
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

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
        case MOUSE:
            oled_write_P(PSTR("Mouse\n"), false);
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
    render_status();
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
