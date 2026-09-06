#pragma once

// Combos
#define COMBO_TERM 25
// COMBO_MOD_TERM and COMBO_MUST_HOLD_MODS are inert while no combo in
// combos.c uses modifier keys; kept for future mod-combos.
#define COMBO_MOD_TERM 150
#define COMBO_MUST_HOLD_MODS
#define EXTRA_SHORT_COMBOS
#define COMBO_STRICT_TIMER

// Layers
// Only consumed by VIA/VIAL dynamic keymaps (both disabled in rules.mk);
// kept in case VIA is enabled.
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// Tap hold
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
/* #define IGNORE_MOD_TAP_INTERRUPT_PER_KEY */
#define TAPPING_FORCE_HOLD_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
/* #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY */
// Only used by TT() keys; the layout has none. Kept for future use.
#define TAPPING_TOGGLE 2
/* #define ONESHOT_TAP_TOGGLE 2 */

// Autoshift
#define AUTO_SHIFT_TIMEOUT 175
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_NO_SETUP

// Caps word
#define CAPS_WORD_IDLE_TIMEOUT 3000
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// One shot keys, mostly for Hyper
#define ONESHOT_TAP_TOGGLE 5
#define ONESHOT_TIMEOUT 2000

// Corne specifics
#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

// Select hand configuration
#define MASTER_LEFT

#define USE_SERIAL_PD2
