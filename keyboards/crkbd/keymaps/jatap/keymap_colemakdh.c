#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "tap_dance.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3(
         KC_Q,   KC_W,   KC_F,   KC_P, KC_B,                                       KC_J,       KC_L,    KC_U,   KC_Y, KC_QUOT,
       HOME_A, HOME_R, HOME_S, HOME_T, KC_G,                                       KC_M,     HOME_N,  HOME_E, HOME_I,  HOME_O,
         KC_Z,   KC_X,   KC_C,   KC_D, KC_V,                                       KC_K,       KC_H, TD(TD_COMMA_SEMICOLON), KC_DOT, KC_SLSH,
                          KC_TAB, LAYER_NAV, KC_SPC,               LAYER_SYM, LAYER_VIM, KC_DEL
  ),

  [1] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                              XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX,            KC_MUTE, KC_MPLY, XXXXXXX
  ),

  [2] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            SGUI(KC_Z), LGUI(KC_Z),   KC_UP, LGUI(KC_C), LGUI(KC_X),
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                               CAPSWRD,    KC_LEFT, KC_DOWN,   KC_RIGHT, LGUI(KC_V),
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               QK_BOOT,    KC_HOME, KC_PGDN,    KC_PGUP,     KC_END,
                                 XXXXXXX, XXXXXXX, XXXXXXX,              KC_BSPC, MO(6), KC_DEL
  ),

  [3] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                                KC_SCLN, KC_4, KC_5, KC_6,  KC_EQL,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               KC_GRAVE, KC_1, KC_2, KC_3, KC_BSLS,
                                 XXXXXXX, XXXXXXX, XXXXXXX,                 KC_MINS, KC_0, KC_DOT
  ),

  [4] = LAYOUT_split_3x5_3(
      LSFT(KC_LBRC),  LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_RBRC),                               XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,
      LSFT(KC_SCLN),  LSFT(KC_4), LSFT(KC_5), LSFT(KC_6),    KC_KP_PLUS,                               XXXXXXX,   KC_RSFT,    KC_RCTL, KC_LALT, KC_RGUI,
      LSFT(KC_GRAVE), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_BSLS),                               XXXXXXX, LSA(KC_2), LALT(KC_3), XXXXXXX, XXXXXXX,
                                                 LSFT(KC_9), LSFT(KC_0), LSFT(KC_MINS),       XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [5] = LAYOUT_split_3x5_3(
      XXXXXXX,  QMK_M9,        QMK_M4,        QMK_M2, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, QMK_M10, LSFT(KC_LBRC), LSFT(KC_RBRC),  QMK_M1,                               XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
      XXXXXXX, QMK_M11,        QMK_M5,        QMK_M3, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                QMK_M7, MO(1), MO(3),               XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [6] = LAYOUT_split_3x5_3(
      XXXXXXX, LGUI(KC_0), LGUI(KC_KP_MINUS), LGUI(KC_KP_PLUS), XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F3, HYPR(KC_C),        HYPR(KC_D),       HYPR(KC_F),  QMK_M0,              XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
      XXXXXXX,     KC_F12,        SGUI(KC_4),       HYPR(KC_N), QMK_M14,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                       QMK_M13, QMK_M12, LCTL(KC_SPACE),     XXXXXXX, XXXXXXX, XXXXXXX
  ),
};


