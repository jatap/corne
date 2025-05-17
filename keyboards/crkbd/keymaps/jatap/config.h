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

// Combos
#define COMBO_TERM 25
#define COMBO_MOD_TERM 150
#define COMBO_MUST_HOLD_MODS
#define EXTRA_SHORT_COMBOS
#define COMBO_STRICT_TIMER
// Layers
#define DYNAMIC_KEYMAP_LAYER_COUNT 7
#define LAYER_STATE_8BIT
// Tap hold
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// Remove the auto-repeat ability and activate the hold function instead
#define QUICK_TAP_TERM 0
#define CHORDAL_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
// Caps word
#define CAPS_WORD_IDLE_TIMEOUT 3000
// One shot
#define NO_ACTION_ONESHOT
// Corne specifics
#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

// Select hand configuration
#define MASTER_LEFT

#define USE_SERIAL_PD2
