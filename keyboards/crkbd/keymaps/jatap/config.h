#pragma once

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// Layers
#define LAYER_STATE_8BIT
// Tap hold
#define QUICK_TAP_TERM 120
#define TAPPING_TERM 200
/* #define TAPPING_TERM_PER_KEY */
/* #define CHORDAL_HOLD */
#define FLOW_TAP_TERM 150
/* #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY */
/* #define PERMISSIVE_HOLD_PER_KEY */
#define PERMISSIVE_HOLD
// One shot
#define NO_ACTION_ONESHOT

// Corne specifics
#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

// #define NKRO_DEFAULT_ON true

// Select hand configuration
#define MASTER_LEFT
