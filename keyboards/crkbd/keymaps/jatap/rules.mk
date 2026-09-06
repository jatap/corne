BACKLIGHT_ENABLE    = no
RGBLIGHT_ENABLE     = no
RGB_MATRIX_ENABLE   = no
BLUETOOTH_ENABLE    = no
CONSOLE_ENABLE      = no
COMMAND_ENABLE      = no
OLED_ENABLE         = no
AUDIO_ENABLE        = no
KEY_OVERRIDE_ENABLE = no
LEADER_ENABLE       = no
QMK_SETTINGS        = no
VIA_ENABLE          = no
VIAL_ENABLE         = no
COMBO_ENABLE        = yes
MOUSEKEY_ENABLE     = no
NKRO_ENABLE         = yes
EXTRAKEY_ENABLE     = yes
LTO_ENABLE          = yes
SPLIT_KEYBOARD      = yes
CAPS_WORD_ENABLE    = yes
AUTO_SHIFT_ENABLE   = yes
TAP_DANCE_ENABLE    = no

# GCC 16 compatibility; mirrors QMK PR #26216.
EXTRAFLAGS += -Wunused-but-set-variable=1
