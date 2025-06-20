#pragma once

// Layers
#define LAYER_STATE_8BIT
// Tap hold
#define QUICK_TAP_TERM 100
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// #define CHORDAL_HOLD
#define FLOW_TAP_TERM 150
// #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
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
// #define MASTER_LEFT
