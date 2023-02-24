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

#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "combos.c"
#include "macros.c"
#include "keymap_colemakdh.c"

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_O:
        case HOME_R:
        case HOME_I:
        case HOME_S:
        case HOME_E:
            return TAPPING_TERM + 100;
        case HOME_T:
        case HOME_N:
            return TAPPING_TERM + 50;
        // case LAYER_NUM:
        //     return TAPPING_TERM - 25;
        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef IGNORE_MOD_TAP_INTERRUPT_PER_KEY
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
            return true;
        default:
            return false;
    }
}
#endif

#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
            return true;
        default:
            return false;
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_MEDIA:
        case LAYER_NAV:
        // case LAYER_NUM:
        case LAYER_SYM:
        case LAYER_VIM:
        case LAYER_APPS:
            return true;
        default:
            return false;
    }
}
#endif

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_MEDIA:
        case LAYER_NAV:
        // case LAYER_NUM:
        case LAYER_SYM:
        case LAYER_VIM:
        case LAYER_APPS:
            return true;
        default:
            return false;
    }
}
#endif

