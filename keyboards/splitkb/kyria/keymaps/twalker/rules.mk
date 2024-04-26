# Elite-pi for my kyria rev3
# comment out for for rev1
CONVERT_TO = elite_pi
PIN_COMPATIBLE = elite_c

RGB_MATRIX_ENABLE = no     # Disable keyboard RGB matrix, as it is enabled by default on rev3

OLED_ENABLE = yes # Enables the use of OLED displays--not enough space with elite-c
ENCODER_ENABLE = yes # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes # Enable keyboard RGB underglow--disable on rev1 for space savings
RGBLIGHT_LIMIT_VAL = 80

# Tapping settings
IGNORE_MOD_TAP_INTERRUPT = yes
TAPPING_FORCE_HOLD = no # Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
PERMISSIVE_HOLD = no

# Caps word
CAPS_WORD_ENABLE = yes
BOTH_SHIFTS_TURNS_ON_CAPS_WORD = yes

WPM_ENABLE = no

# Macros
DYNAMIC_MACRO_ENABLE = yes

# Combos
COMBO_ENABLE = no # There's not enough memory to enable combos without disabling other features

# Space savings
LTO_ENABLE = yes
MOUSEKEY_ENABLE = yes # adds 5% to the firmware size
EXTRAKEY_ENABLE = yes # disables media key and volume control
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
