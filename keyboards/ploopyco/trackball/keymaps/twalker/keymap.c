#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN1, KC_BTN3, KC_BTN2,
          KC_BTN4, LT(1, KC_BTN5)
    ),
    [1] = LAYOUT(
        DRAG_SCROLL, _______, _______,
          DPI_CONFIG, _______
    )
};
