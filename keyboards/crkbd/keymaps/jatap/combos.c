#include "combos.h"

// Remove the COMBO_COUNT define and use this instead!
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM clear_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_H, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    [TAB] = COMBO_ACTION(tab_combo),
    [CLEAR_SCREEN] = COMBO_ACTION(clear_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CLEAR_SCREEN:
      if (pressed) {
        SEND_STRING("cls\n");
      }
      break;
    case TAB:
      if (pressed) {
        tap_code16(KC_TAB);
      }
      break;
  }
}
