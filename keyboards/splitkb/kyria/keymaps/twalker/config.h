#pragma once

#ifdef OLED_ENABLE
  #define OLED_DISPLAY_128X64
#endif

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2

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



// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY
#define TT_SHIFT 150

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD


// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RCTL_T(KC_SCLN)


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

#define OS_COPY LGUI(KC_C)
#define OS_UNDO LGUI(KC_Z)
#define OS_PSTE LGUI(KC_V)
#define OS_CUT LGUI(KC_X)
