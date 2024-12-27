#include "combos.h"

// Remove the COMBO_COUNT define and use this instead!
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM tab_combo[]        = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM multiarrow_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    [TAB]        = COMBO_ACTION(tab_combo),
    [MULTIARROW] = COMBO_ACTION(multiarrow_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case TAB:
            if (pressed) {
                tap_code16(KC_TAB);
            }
            break;

        case MULTIARROW:
            if (pressed) {
                send_string("->");
            }
            break;
    }
}
