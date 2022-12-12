# MCU name
# MCU = STM32F411

# Bootloader selection
# BOOTLOADER = tinyuf2
# CONVERT_TO = stemcell

# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu
PIN_COMPATIBLE = elite_c
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
# AUDIO_ENABLE = yes          # Audio output

RGB_MATRIX_ENABLE = no     # Enable WS2812 RGB matrix
RGB_MATRIX_DRIVER = WS2812
SPLIT_KEYBOARD = yes

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no

LAYOUTS = split_3x6_3
