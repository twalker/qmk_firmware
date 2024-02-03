#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define MASTER_LEFT
// #define MASTER_RIGHT

//#define TAPPING_TERM 170
/* #define TAPPING_TERM 170 */

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
/* #define TAPPING_FORCE_HOLD */

// Auto Shift
/* #define NO_AUTO_SHIFT_ALPHA */
/* #define AUTO_SHIFT_TIMEOUT TAPPING_TERM */
/* #define AUTO_SHIFT_NO_SETUP */
/**/
/* #undef LOCKING_SUPPORT_ENABLE */
/* #undef LOCKING_RESYNC_ENABLE */
/* #define NO_ACTION_ONESHOT */


#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define TT_SHIFT 110
#define TT_ALT 160

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD true
#define TAPPING_FORCE_HOLD_PER_KEY

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// COLEMAK DH homerow mods
// Left-hand
/* #define CDHHM_A LCTL_T(KC_A) */
/* #define CDHHM_R LALT_T(KC_R) */
/* #define CDHHM_S LGUI_T(KC_S) */
/* #define CDHHM_T LSFT_T(KC_T) */
/* // Right-hand */
/* #define CDHHM_N RSFT_T(KC_N) */
/* #define CDHHM_E RGUI_T(KC_E) */
/* #define CDHHM_I LALT_T(KC_I) */
/* #define CDHHM_O RCTL_T(KC_O) */

