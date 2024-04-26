# MCU name
MCU = atmega32u4
# Bootloader selection
BOOTLOADER = atmel-dfu

CONVERT_TO = elite_pi
PIN_COMPATIBLE = elite_c

# Tapping settings
IGNORE_MOD_TAP_INTERRUPT = yes
TAPPING_FORCE_HOLD = no    # Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
PERMISSIVE_HOLD = no

# Caps word
CAPS_WORD_ENABLE = yes
BOTH_SHIFTS_TURNS_ON_CAPS_WORD = yes

# Macros
DYNAMIC_MACRO_ENABLE = yes

# Combos
COMBO_ENABLE = no

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
# AUDIO_ENABLE = yes          # Audio output

RGB_MATRIX_ENABLE = no     # Enable WS2812 RGB matrix
RGB_MATRIX_DRIVER = ws2812
SPLIT_KEYBOARD = yes

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no

LAYOUTS = split_3x6_3




