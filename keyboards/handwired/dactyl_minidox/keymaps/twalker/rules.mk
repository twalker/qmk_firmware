# MCU = atmega32u4
# Bootloader selection
# BOOTLOADER = atmel-dfu
# MCU = RP2040
# DEVELOPMENT_BOARD = elite_pi
# CONVERT_TO = helios # elite_pi
# PIN_COMPATIBLE = elite_c

# CONVERT_TO = elite_c
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3389

IGNORE_MOD_TAP_INTERRUPT = yes
TAPPING_FORCE_HOLD = no # Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
PERMISSIVE_HOLD = no

# Caps word
CAPS_WORD_ENABLE = yes
BOTH_SHIFTS_TURNS_ON_CAPS_WORD = yes

# Macros
DYNAMIC_MACRO_ENABLE = yes

EXTRAKEY_ENABLE = yes # enable/disable media key and volume control

# space savings
LTO_ENABLE = yes
ENABLE_CTL_GUI_SWAP = no
MOUSEKEY_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
