/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// #define VIAL_KEYBOARD_UID {0xE1, 0x6F, 0x65, 0xC5, 0xFE, 0xF8, 0xD6, 0x58}
// #define VIAL_UNLOCK_COMBO_ROWS {1, 1}
// #define VIAL_UNLOCK_COMBO_COLS {1, 2}

#define DYNAMIC_KEYMAP_LAYER_COUNT 7

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define TAPPING_FORCE_HOLD_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// #define RETRO_TAPPING
// #define RETRO_TAPPING_PER_KEY

#define TAPPING_TOGGLE 2

#define AUTO_SHIFT_TIMEOUT 175
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_NO_SETUP
// #define AUTO_SHIFT_REPEAT

// #define COMBO_TERM 25
// #define COMBO_MUST_HOLD_MODS
// #define COMBO_MOD_TERM 175

#define CAPS_WORD_IDLE_TIMEOUT 3000
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

//#define USE_MATRIX_I2C
#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2
