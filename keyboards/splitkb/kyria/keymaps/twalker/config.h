#pragma once

#ifdef OLED_ENABLE
  #define OLED_DISPLAY_128X64
#endif

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2
#define ENCODER_DIRECTION_FLIP yes

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS


#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_SLEEP
#endif

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Configure the global tapping term (default: 200ms)
// #define TAPPING_TERM 170
// #define TAPPING_TERM_PER_KEY
// #define TT_SHIFT 150
// #define TT_ALT 220
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define TT_SHIFT 120
#define TT_ALT 180

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD
 
// COLEMAK DH homerow mods
// Left-hand
#define CDHHM_A LCTL_T(KC_A)
#define CDHHM_R LALT_T(KC_R)
#define CDHHM_S LGUI_T(KC_S)
#define CDHHM_T LSFT_T(KC_T)
// Right-hand
#define CDHHM_N RSFT_T(KC_N)
#define CDHHM_E RGUI_T(KC_E)
#define CDHHM_I LALT_T(KC_I)
#define CDHHM_O RCTL_T(KC_O)

// Window management (rectange on macos)
#define WIN_TL LCA(KC_U)
#define WIN_TR LCA(KC_I)
#define WIN_BL LCA(KC_J)
#define WIN_BR LCA(KC_K)

#define WIN_L LCA(KC_LEFT)
#define WIN_R LCA(KC_RGHT)
#define WIN_U LCA(KC_UP)
#define WIN_D LCA(KC_DOWN)

#define WIN_LG LCA(KC_EQL)
#define WIN_SM LCA(KC_MINS)
#define WIN_FUL LCA(KC_ENT)
#define WIN_PSC SCMD(KC_5)
#define ZOOM_IN LGUI(KC_EQL)
#define ZOOM_OUT LGUI(KC_MINS)

#define OS_COPY LGUI(KC_C)
#define OS_UNDO LGUI(KC_Z)
#define OS_PSTE LGUI(KC_V)
#define OS_CUT LGUI(KC_X)
