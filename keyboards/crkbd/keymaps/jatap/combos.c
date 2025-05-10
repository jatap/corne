#include "combos.h"

// Remove the COMBO_COUNT define and use this instead!
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM tab_combo[]               = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM phpopen_combo[]           = {KC_U, KC_L, COMBO_END};
const uint16_t PROGMEM multiarrow_combo[]        = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM double_multiarrow_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM personalmail_combo[]      = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM workmail_combo[]          = {KC_L, KC_U, COMBO_END};

combo_t key_combos[]    = {
    [TAB]               = COMBO_ACTION(tab_combo),
    [PHPOPEN]           = COMBO_ACTION(phpopen_combo),
    [MULTIARROW]        = COMBO_ACTION(multiarrow_combo),
    [DOUBLE_MULTIARROW] = COMBO_ACTION(double_multiarrow_combo),
    [PERSONALMAIL]      = COMBO_ACTION(personalmail_combo),
    [WORKMAIL]          = COMBO_ACTION(workmail_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case TAB:
            if (pressed) {
                tap_code16(KC_TAB);
            }
            break;

        case PHPOPEN:
            if (pressed) {
                send_string("<?php");
            }
            break;

        case MULTIARROW:
            if (pressed) {
                send_string("->");
            }
            break;

        case DOUBLE_MULTIARROW:
            if (pressed) {
                send_string("=>");
            }
            break;

        case PERSONALMAIL:
            if (pressed) {
                send_string("julio.antunez.tarin@gmail.com");
            }
            break;

        case WORKMAIL:
            if (pressed) {
                send_string("julio.antunez.tarin@glowingblue.com");
            }
            break;

    }
}
