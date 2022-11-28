# MCU = atmega32u4

# Bootloader selection
# BOOTLOADER = atmel-dfu
# Elite-pi conversion
CONVERT_TO = elite_pi
PIN_COMPATIBLE = elite_c

# Build Options
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes
# Caps word
CAPS_WORD_ENABLE = yes
BOTH_SHIFTS_TURNS_ON_CAPS_WORD = yes
# Tapping settings
IGNORE_MOD_TAP_INTERRUPT = yes
TAPPING_FORCE_HOLD = no    # Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
PERMISSIVE_HOLD = no

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3389
DYNAMIC_MACRO_ENABLE = yes 

