#pragma once

// Combos
#define COMBO_MOD_TERM 40
/* #define COMBO_STRICT_TIMER */
#define COMBO_NO_TIMER
#define EXTRA_EXTRA_LONG_COMBOS
#define COMBO_BUFFER_LENGTH 4
// Layers
#define LAYER_STATE_8BIT
// Tap hold
#define QUICK_TAP_TERM 100
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define CHORDAL_HOLD
#define FLOW_TAP_TERM 150
/* #define HOLD_ON_OTHER_KEY_PRESS */
/* #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY */
/* #define PERMISSIVE_HOLD */
#define PERMISSIVE_HOLD_PER_KEY
// One shot
#define NO_ACTION_ONESHOT
// Corne specifics
#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

#define FORCE_NKRO

// Select hand configuration
/* #define MASTER_LEFT */
