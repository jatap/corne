#pragma once

#include "keycodes.h"
#include "macros.c"
#include "combos.c"

// clang-format off
#define _____________________BASE_L1______________________ KC_Q,   KC_W,   KC_F,   KC_P,   KC_B
#define _____________________BASE_L2______________________ HOME_A, HOME_R, HOME_S, HOME_T, KC_G
#define _____________________BASE_L3______________________ KC_Z,   KC_X,   KC_C,   KC_D,   KC_V

#define _____________________BASE_R1______________________ KC_J,   KC_L,   KC_U,     KC_Y,   KC_QUOT
#define _____________________BASE_R2______________________ KC_M,   HOME_N, HOME_E,   HOME_I, HOME_O
#define _____________________BASE_R3______________________ KC_K,   KC_H,   KC_COMMA, KC_DOT, KC_SLSH

#define _____________BASE_LEFT_____________ LAYER_NIRI, LAYER_NAV, LAYER_EMACS
#define _____________BASE_RIGHT____________ LAYER_SYM,   LAYER_NUM, LAYER_APPS

#define _____________________NIRI_L1______________________ HYPR(KC_C), HYPR(KC_ESC), XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________NIRI_L2______________________ KC_LGUI,    KC_LALT,      KC_LCTL, KC_LSFT, XXXXXXX
#define _____________________NIRI_L3______________________ XXXXXXX,    XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________NIRI_R1______________________ HYPR(KC_F), QMK_M30, HYPR(KC_A), HYPR(KC_BSPC), XXXXXXX
#define _____________________NIRI_R2______________________ XXXXXXX,    QMK_M29, HYPR(KC_T), XXXXXXX,       XXXXXXX
#define _____________________NIRI_R3______________________ XXXXXXX,    QMK_M28, HYPR(KC_4), HYPR(KC_X),    XXXXXXX

#define _____________NIRI_LEFT_____________ XXXXXXX,    XXXXXXX,    XXXXXXX
#define _____________NIRI_RIGHT____________ HYPR(KC_U), HYPR(KC_D), LAYER_EXTRA

#define _____________________NAV_L1_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________NAV_L2_______________________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define _____________________NAV_L3_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________NAV_R1_______________________ KC_CAPS,             LGUI(KC_Z), KC_UP,   LGUI(KC_C), LGUI(KC_X)
#define _____________________NAV_R2_______________________ QK_CAPS_WORD_TOGGLE, KC_LEFT,    KC_DOWN, KC_RIGHT,   LGUI(KC_V)
#define _____________________NAV_R3_______________________ XXXXXXX,             KC_HOME,    KC_PGUP, KC_PGDN,    KC_END

#define _____________NAV_LEFT______________ XXXXXXX, XXXXXXX, XXXXXXX
#define _____________NAV_RIGHT_____________ KC_BSPC, MO(6), KC_DEL

#define _____________________EMACS_L1_____________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________EMACS_L2_____________________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define _____________________EMACS_L3_____________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________EMACS_R1_____________________ QMK_M17, QMK_M18, QMK_M19, QMK_M4, QMK_M20
#define _____________________EMACS_R2_____________________ QMK_M14, QMK_M15, QMK_M16, QMK_M5, QMK_M21
#define _____________________EMACS_R3_____________________ QMK_M13, QMK_M1,  QMK_M2,  QMK_M6, QMK_M22

#define _____________EMACS_LEFT____________ XXXXXXX, XXXXXXX, XXXXXXX
#define _____________EMACS_RIGHT___________ QMK_M0,  QMK_M3,  QMK_M12

#define _____________________SYM_L1_______________________ LSFT(KC_LBRC),  LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_RBRC)
#define _____________________SYM_L2_______________________ LSFT(KC_SCLN),  LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_KP_PLUS
#define _____________________SYM_L3_______________________ LSFT(KC_GRAVE), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_BSLS)

#define _____________________SYM_R1_______________________ XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX
#define _____________________SYM_R2_______________________ XXXXXXX, KC_RSFT,   KC_RCTL,    KC_RALT, KC_RGUI
#define _____________________SYM_R3_______________________ XXXXXXX, QMK_M26,   QMK_M27,    XXXXXXX, XXXXXXX

#define _____________SYM_LEFT______________ LSFT(KC_9), LSFT(KC_0), LSFT(KC_MINS)
#define _____________SYM_RIGHT_____________ XXXXXXX,    XXXXXXX,    XXXXXXX

#define _____________________NUM_L1_______________________ KC_LBRC,  KC_7, KC_8, KC_9, KC_RBRC
#define _____________________NUM_L2_______________________ KC_SCLN,  KC_4, KC_5, KC_6, KC_EQL
#define _____________________NUM_L3_______________________ KC_GRAVE, KC_1, KC_2, KC_3, KC_BSLS

#define _____________________NUM_R1_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________NUM_R2_______________________ XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI
#define _____________________NUM_R3_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________NUM_LEFT______________ KC_DOT,  KC_0,    KC_MINS
#define _____________NUM_RIGHT_____________ XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________APPS_L1______________________ HYPR(KC_Q), LCTL(KC_0), LCTL(KC_KP_MINUS), LCTL(KC_KP_PLUS), QMK_M23
#define _____________________APPS_L2______________________ XXXXXXX,    MEH(KC_I),  MEH(KC_B),         MEH(KC_S),        QMK_M11
#define _____________________APPS_L3______________________ HYPR(KC_R), MEH(KC_P),  HYPR(KC_1),        HYPR(KC_N),       QMK_M9

#define _____________________APPS_R1______________________ XXXXXXX,    QMK_M24, HYPR(KC_3),  HYPR(KC_2),  HYPR(KC_ENT)
#define _____________________APPS_R2______________________ HYPR(KC_9), KC_RSFT, KC_RCTL,     KC_RALT,     KC_RGUI
#define _____________________APPS_R3______________________ HYPR(KC_0), QMK_M25, XXXXXXX,     HYPR(KC_5),  HYPR(KC_6)

#define _____________APPS_LEFT_____________ QMK_M8, QMK_M7, QMK_M10
#define _____________APPS_RIGHT____________ XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________EXTRA_L1______________________ KC_F10,  KC_F9,   KC_F8,   KC_F7,   KC_F6
#define _____________________EXTRA_L2______________________ XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
#define _____________________EXTRA_L3______________________ XXXXXXX, KC_F12,  KC_F11,  XXXXXXX, QK_BOOT

#define _____________________EXTRA_R1______________________ KC_F5,   KC_F4,   KC_F3,   KC_F2,   KC_F1
#define _____________________EXTRA_R2______________________ XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI
#define _____________________EXTRA_R3______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________EXTRA_LEFT_____________ KC_MUTE, KC_MPLY, XXXXXXX
#define _____________EXTRA_RIGHT____________ XXXXXXX, XXXXXXX, XXXXXXX
// clang-format on
