#pragma once

#include QMK_KEYBOARD_H

#include "tap_dance.h"

qk_tap_dance_action_t tap_dance_actions[] = {
    [T_C_SC] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_SEMICOLON),
};
