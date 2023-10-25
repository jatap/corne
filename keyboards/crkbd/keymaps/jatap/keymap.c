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

#include QMK_KEYBOARD_H

#include "layers.h"
#include "keycodes.h"
#include "keymap_colemakdh.c"

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_wrapper(
          _____________________BASE_L1______________________,      _____________________BASE_R1______________________,
          _____________________BASE_L2______________________,      _____________________BASE_R2______________________,
          _____________________BASE_L3______________________,      _____________________BASE_R3______________________,
                         _____________BASE_LEFT_____________,      _____________BASE_RIGHT____________
  ),
  [_MEDIA] = LAYOUT_wrapper(
          _____________________MEDIA_L1_____________________,      _____________________MEDIA_R1_____________________,
          _____________________MEDIA_L2_____________________,      _____________________MEDIA_R2_____________________,
          _____________________MEDIA_L3_____________________,      _____________________MEDIA_R3_____________________,
                         _____________MEDIA_LEFT____________,      _____________MEDIA_RIGHT___________
  ),
  [_NAV] = LAYOUT_wrapper(
          _____________________NAV_L1_______________________,      _____________________NAV_R1_______________________,
          _____________________NAV_L2_______________________,      _____________________NAV_R2_______________________,
          _____________________NAV_L3_______________________,      _____________________NAV_R3_______________________,
                         _____________NAV_LEFT______________,      _____________NAV_RIGHT_____________
  ),
  [_VIM] = LAYOUT_wrapper(
          _____________________VIM_L1_______________________,      _____________________VIM_R1_______________________,
          _____________________VIM_L2_______________________,      _____________________VIM_R2_______________________,
          _____________________VIM_L3_______________________,      _____________________VIM_R3_______________________,
                         _____________VIM_LEFT______________,      _____________VIM_RIGHT_____________
  ),
  [_SYM] = LAYOUT_wrapper(
          _____________________SYM_L1_______________________,      _____________________SYM_R1_______________________,
          _____________________SYM_L2_______________________,      _____________________SYM_R2_______________________,
          _____________________SYM_L3_______________________,      _____________________SYM_R3_______________________,
                         _____________SYM_LEFT______________,      _____________SYM_RIGHT_____________
  ),
  [_NUM] = LAYOUT_wrapper(
          _____________________NUM_L1_______________________,      _____________________NUM_R1_______________________,
          _____________________NUM_L2_______________________,      _____________________NUM_R2_______________________,
          _____________________NUM_L3_______________________,      _____________________NUM_R3_______________________,
                         _____________NUM_LEFT______________,      _____________NUM_RIGHT_____________
  ),
  [_APPS] = LAYOUT_wrapper(
          _____________________APPS_L1______________________,      _____________________APPS_R1______________________,
          _____________________APPS_L2______________________,      _____________________APPS_R2______________________,
          _____________________APPS_L3______________________,      _____________________APPS_R3______________________,
                         _____________APPS_LEFT_____________,      _____________APPS_RIGHT____________
  ),
};

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_O:
        case HOME_R:
        case HOME_I:
        case HOME_S:
        case HOME_E:
            return TAPPING_TERM + 50;
        case HOME_T:
        case HOME_N:
            return TAPPING_TERM - 10;
        // case LAYER_NUM:
        //     return TAPPING_TERM + 20;
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
        case LAYER_NUM:
        case LAYER_SYM:
        /* case LAYER_VIM: */
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
        case LAYER_NUM:
        case LAYER_SYM:
        /* case LAYER_VIM: */
        case LAYER_APPS:
            return true;
        default:
            return false;
    }
}
#endif
