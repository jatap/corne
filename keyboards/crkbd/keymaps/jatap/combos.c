#include "combos.h"

// Remove the COMBO_COUNT define and use this instead!
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM clear_combo[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM space_combo[] = {KC_L, KC_U, COMBO_END};
// const uint16_t PROGMEM tmux_combo[] = {KC_H, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    // [TMUX] = COMBO_ACTION(tmux_combo),
    [CLEAR_SCREEN] = COMBO_ACTION(clear_combo),
    [SPACE] = COMBO_ACTION(space_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CLEAR_SCREEN:
      if (pressed) {
        SEND_STRING("cls\n");
      }
      break;
    case SPACE:
      if (pressed) {
        tap_code(KC_SPC);
      }
      break;
    // case TMUX:
    //   if (pressed) {
    //     tap_code16(LCTL(KC_SPC));
    //   }
    //   break;
  }
}
