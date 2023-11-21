#include "keycodes.h"
#include "tap_dance.c"
#include "macros.c"
#include "combos.c"

#define _____________________BASE_L1______________________ KC_Q,   KC_W,   KC_F,   KC_P,   KC_B
#define _____________________BASE_L2______________________ HOME_A, HOME_R, HOME_S, HOME_T, KC_G
#define _____________________BASE_L3______________________ KC_Z,   KC_X,   KC_C,   KC_D,   KC_V

#define _____________________BASE_R1______________________ KC_J,   KC_L,   KC_U,     KC_Y,   KC_QUOT
#define _____________________BASE_R2______________________ KC_M,   HOME_N, HOME_E,   HOME_I, HOME_O
#define _____________________BASE_R3______________________ KC_K,   KC_H,   KC_COMMA, KC_DOT, KC_SLSH

#define _____________BASE_LEFT_____________ LAYER_MEDIA, LAYER_NAV, LAYER_VIM
#define _____________BASE_RIGHT____________ LAYER_SYM,   LAYER_NUM, LAYER_APPS

#define _____________________MEDIA_L1_____________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________MEDIA_L2_____________________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define _____________________MEDIA_L3_____________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________MEDIA_R1_____________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________MEDIA_R2_____________________ XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
#define _____________________MEDIA_R3_____________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________MEDIA_LEFT____________ XXXXXXX, XXXXXXX, XXXXXXX
#define _____________MEDIA_RIGHT___________ KC_MUTE, KC_MPLY, XXXXXXX

#define _____________________NAV_L1_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________NAV_L2_______________________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define _____________________NAV_L3_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________NAV_R1_______________________ KC_CAPS, LGUI(KC_Z), KC_UP,   LGUI(KC_C), LGUI(KC_X)
#define _____________________NAV_R2_______________________ CAPSWRD,    KC_LEFT, KC_DOWN, KC_RIGHT,   LGUI(KC_V)
#define _____________________NAV_R3_______________________ QK_BOOT,    KC_HOME, KC_PGDN, KC_PGUP,    KC_END

#define _____________NAV_LEFT______________ XXXXXXX, XXXXXXX, XXXXXXX
#define _____________NAV_RIGHT_____________ KC_BSPC, MO(6), KC_DEL

#define _____________________VIM_L1_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________VIM_L2_______________________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define _____________________VIM_L3_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________VIM_R1_______________________ XXXXXXX, QMK_M2,  QMK_M4,        QMK_M9,         XXXXXXX
#define _____________________VIM_R2_______________________ XXXXXXX, LSFT(KC_RBRC), LSFT(KC_LBRC), QMK_M10,  XXXXXXX
#define _____________________VIM_R3_______________________ XXXXXXX, QMK_M3, QMK_M5,        QMK_M11,         XXXXXXX

#define _____________VIM_LEFT______________ XXXXXXX, XXXXXXX, XXXXXXX
#define _____________VIM_RIGHT_____________ QMK_M1,  QMK_M7,  QMK_M17

#define _____________________SYM_L1_______________________ LSFT(KC_LBRC),  LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_RBRC)
#define _____________________SYM_L2_______________________ LSFT(KC_SCLN),  LSFT(KC_4), LSFT(KC_5), LSFT(KC_6),    KC_KP_PLUS
#define _____________________SYM_L3_______________________ LSFT(KC_GRAVE), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_BSLS)

#define _____________________SYM_R1_______________________ XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX
#define _____________________SYM_R2_______________________ XXXXXXX, KC_RSFT,   KC_RCTL,    KC_LALT, KC_RGUI
#define _____________________SYM_R3_______________________ XXXXXXX, LSA(KC_2), LALT(KC_3), XXXXXXX, XXXXXXX

#define _____________SYM_LEFT______________ LSFT(KC_9), LSFT(KC_0), LSFT(KC_MINS)
#define _____________SYM_RIGHT_____________ XXXXXXX,    XXXXXXX,    XXXXXXX

#define _____________________NUM_L1_______________________ KC_LBRC,  KC_7, KC_8, KC_9, KC_RBRC
#define _____________________NUM_L2_______________________ KC_SCLN,  KC_4, KC_5, KC_6, KC_EQL
#define _____________________NUM_L3_______________________ KC_GRAVE, KC_1, KC_2, KC_3, KC_BSLS

#define _____________________NUM_R1_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________NUM_R2_______________________ XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI
#define _____________________NUM_R3_______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________NUM_LEFT______________ KC_DOT,  MO(7),    KC_MINS
#define _____________NUM_RIGHT_____________ XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________APPS_L1______________________ XXXXXXX, LGUI(KC_0), LGUI(KC_KP_MINUS), LGUI(KC_KP_PLUS), XXXXXXX
#define _____________________APPS_L2______________________ KC_F3,   HYPR(KC_C), HYPR(KC_D),        HYPR(KC_F),       QMK_M16
#define _____________________APPS_L3______________________ XXXXXXX, KC_F12,     SGUI(KC_4),        HYPR(KC_N),       QMK_M14

#define _____________________APPS_R1______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________APPS_R2______________________ XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI
#define _____________________APPS_R3______________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________APPS_LEFT_____________ QMK_M13, QMK_M12, QMK_M15
#define _____________APPS_RIGHT____________ XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________NUMR_L1______________________ XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _____________________NUMR_L2______________________ KC_LGUI,  KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define _____________________NUMR_L3______________________ XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _____________________NUMR_R1______________________ KC_LBRC,  KC_7, KC_8, KC_9, KC_RBRC
#define _____________________NUMR_R2______________________ KC_SCLN,  KC_4, KC_5, KC_6, KC_EQL
#define _____________________NUMR_R3______________________ KC_GRAVE, KC_1, KC_2, KC_3, KC_BSLS

#define _____________NUMR_LEFT_____________ XXXXXXX, XXXXXXX, XXXXXXX
#define _____________NUMR_RIGHT____________ KC_BSPC, KC_0,    KC_DOT

