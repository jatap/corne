#include QMK_KEYBOARD_H

enum {
    TD_COMMA_SEMICOLON,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_COMMA_SEMICOLON] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_SEMICOLON),
};