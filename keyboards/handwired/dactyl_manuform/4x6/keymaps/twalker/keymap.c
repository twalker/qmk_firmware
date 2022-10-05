#include QMK_KEYBOARD_H

enum layers {
  CDH = 0,
  SYM,
  NAV,
  NUM,
  WIN,
  MAC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Coordinates 
     * +-----------------------------------------+                             +-----------------------------------------+
     * 1      |      |      |      |      |      |                             1      |      |      |      |      |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * 2      |      |      |      |      |      |                             2      |      |      |      |      |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * 3      |      |      |      |      |      |                             3      |      |      |      |      |      |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               4      |      |                                                         4      |      |
     *               +-------------+                                                         +-------------+
     *                             +------+------+                                    +------|
     *                             4      |      |                                    4      |
     *                             +-------------+                                    +------+
     *                                           +-------------+        +------+
     *                                           5      |      |        5      |
     *                                           |------+------| +------+------|
     *                                           5      |      | 5      |      |
     *                                           +-------------+ +-------------+
     */

    // [LAYER] = LAYOUT(
    // //=======*=======*=======*=======*=======*=======*            =======*=======*=======*=======*=======*=======*
    //   _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
    //   _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
    //   _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
    // //                =======*=======*                                            =======*=======*                
    //                   _______,_______,                                            _______,_______,
    //                                           _______,_______,            _______,
    //                                           _______,_______,            _______,
    //                                           _______,_______,    _______,_______
    // //                                        =======*=======*    =======*=======*
    // ),
   // MO(NUM), MO(SYM), LT(NAV, KC_BSPC),  LT(NAV, KC_SPC), LT(WIN, KC_ENT),  MO(NUM)
    [CDH] = LAYOUT(
    //-------+-------+-------+-------+-------+-------+            -------+-------+-------+-------+-------+-------+
      QK_BOOT,   KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,               KC_J,   KC_L,   KC_U,   KC_Y,KC_SCLN, QK_BOOT,
       KC_ESC,CDHHM_A,CDHHM_R,CDHHM_S,CDHHM_T,   KC_G,               KC_M,CDHHM_N,CDHHM_E,CDHHM_I,CDHHM_O, KC_QUOT,
        KC_NO,   KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,               KC_K,   KC_H,KC_COMM, KC_DOT,KC_SLSH, KC_BSLS,
    //                -------+-------+                                            -------+-------+                
                      KC_LBRC,MO(NUM),                                         KC_MS_BTN1, KC_MS_BTN2,
    //                                        -------+-------+                   -------+
                                            MO(SYM), LT(NAV, KC_BSPC),   LT(NAV, KC_SPC),    
                                               KC_TAB, KC_HOME,          LT(WIN, KC_ENT),
                                              KC_BSPC,  KC_GRV,          KC_LGUI, KC_LALT
    //                                        -------+-------+           -------+-------+
    ),
    [SYM] = LAYOUT(
    //=======*=======*=======*=======*=======*=======*            =======*=======*=======*=======*=======*=======*
      _______,KC_EXLM,  KC_AT,KC_LCBR,KC_RCBR,KC_PIPE,            KC_AMPR, KC_ASTR, KC_LT,  KC_GT,KC_QUES,_______,
      _______,KC_HASH, KC_DLR,KC_LPRN,KC_RPRN, KC_GRV,            KC_MINS, KC_EQL,KC_PLUS,KC_UNDS,KC_SCLN,KC_QUOT,
      _______,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,            KC_BSLS,  KC_NO,KC_COMM, KC_DOT,KC_SLSH,_______,
    //                =======*=======*                                            =======*=======*                
                      _______,_______,                                            _______,_______,
                                              _______,_______,            _______,
                                              _______,_______,            _______,
                                              _______,_______,    _______,_______
    //                                        =======*=======*    =======*=======*
    ),
    [NAV] = LAYOUT(
    //=======*=======*=======*=======*=======*=======*            =======*=======*=======*=======*=======*=======*
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
    //                =======*=======*                                            =======*=======*                
                      _______,_______,                                            _______,_______,
                                              _______,_______,            _______,
                                              _______,_______,            _______,
                                              _______,_______,    _______,_______
    //                                        =======*=======*    =======*=======*
    ),
    [NUM] = LAYOUT(
    //=======*=======*=======*=======*=======*=======*            =======*=======*=======*=======*=======*=======*
      _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4, _______,             KC_NO,    KC_7,  KC_8,   KC_9,  KC_NO,_______,
      _______,  KC_F5,  KC_F6,  KC_F7,  KC_F8, _______,             KC_NO,    KC_4,  KC_5,   KC_6,  KC_NO,_______,
      _______,  KC_F9, KC_F10, KC_F10, KC_F12, _______,             KC_NO,    KC_1,  KC_2,   KC_3,  KC_NO,_______,
    //                =======*=======*                                            =======*=======*                
                      _______,_______,                                               KC_0, KC_DOT,
                                              _______,_______,            _______,
                                              _______,_______,            _______,
                                              _______,_______,    _______,_______
    //                                        =======*=======*    =======*=======*
    ),
    [WIN] = LAYOUT(
    //=======*=======*=======*=======*=======*=======*            =======*=======*=======*=======*=======*=======*
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
    //                =======*=======*                                            =======*=======*                
                      _______,_______,                                            _______,_______,
                                              _______,_______,            _______,
                                              _______,_______,            _______,
                                              _______,_______,    _______,_______
    //                                        =======*=======*    =======*=======*
    ),
    [MAC] = LAYOUT(
    //=======*=======*=======*=======*=======*=======*            =======*=======*=======*=======*=======*=======*
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
      _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,_______,
    //                =======*=======*                                            =======*=======*                
                      _______,_______,                                            _______,_______,
                                              _______,_______,            _______,
                                              _______,_______,            _______,
                                              _______,_______,    _______,_______
    //                                        =======*=======*    =======*=======*
    )
};

// void persistent_default_layer_set(uint16_t default_layer) {
//     eeconfig_update_default_layer(default_layer);
//     default_layer_set(default_layer);
// }
