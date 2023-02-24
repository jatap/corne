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

#include QMK_KEYBOARD_H

enum custom_keycodes {
    QMK_M0 = SAFE_RANGE,
    QMK_M1,
    QMK_M2,
    QMK_M3,
    QMK_M4,
    QMK_M5,
    QMK_M6,
    QMK_M7,
    QMK_M8,
    QMK_M9,
    QMK_M10,
    QMK_M11,
};

// Left-hand home row mods
// #define HOME_A LGUI_T(KC_A)
// #define HOME_R LALT_T(KC_R)
// #define HOME_S LCTL_T(KC_S)
// #define HOME_T LSFT_T(KC_T)
#define HOME_Z LGUI_T(KC_Z)
#define HOME_X LALT_T(KC_X)
#define HOME_C LCTL_T(KC_C)
#define HOME_D LSFT_T(KC_D)

// Right-hand home row mods
// #define HOME_N RSFT_T(KC_N)
// #define HOME_E RCTL_T(KC_E)
// #define HOME_I LALT_T(KC_I)
// #define HOME_O RGUI_T(KC_O)
#define HOME_H RSFT_T(KC_H)
#define HOME_COMM RCTL_T(KC_COMM)
#define HOME_DOT LALT_T(KC_DOT)
#define HOME_SLSH RGUI_T(KC_SLSH)

// #define LAYER_MEDIA LT(1, KC_TAB)
#define LAYER_NAV LT(2, KC_ESC)
// #define LAYER_NUM LT(3, KC_SPC)
#define LAYER_NUM LT(3, KC_TAB)
#define LAYER_SYM LT(4, KC_BSPC)
#define LAYER_VIM LT(5, KC_ENT)
#define LAYER_APPS LT(6, KC_DEL)

// Combos
// enum combos {
//     COMBO_LCTL,
//     COMBO_LALT,
//     COMBO_LGUI,
//     COMBO_LSFT,
//     COMBO_RCTL,
//     COMBO_RALT,
//     COMBO_RGUI,
//     COMBO_RSFT,
// };

// const uint16_t PROGMEM ts_combo[] = {KC_T, KC_S, COMBO_END};
// const uint16_t PROGMEM tr_combo[] = {KC_T, KC_R, COMBO_END};
// const uint16_t PROGMEM ta_combo[] = {KC_T, KC_A, COMBO_END};
// const uint16_t PROGMEM ar_combo[] = {KC_A, KC_R, COMBO_END};
// const uint16_t PROGMEM ne_combo[] = {KC_N, KC_E, COMBO_END};
// const uint16_t PROGMEM ni_combo[] = {KC_N, KC_I, COMBO_END};
// const uint16_t PROGMEM no_combo[] = {KC_N, KC_O, COMBO_END};
// const uint16_t PROGMEM oi_combo[] = {KC_O, KC_I, COMBO_END};

// combo_t key_combos[COMBO_COUNT] = {
//     [COMBO_LCTL] = COMBO(ts_combo, KC_LCTL),
//     [COMBO_LALT] = COMBO(tr_combo, KC_LALT),
//     [COMBO_LGUI] = COMBO(ta_combo, KC_LGUI),
//     [COMBO_LSFT] = COMBO(ar_combo, KC_LSFT),
//     [COMBO_RCTL] = COMBO(ne_combo, KC_RCTL),
//     [COMBO_RALT] = COMBO(ni_combo, KC_LALT),
//     [COMBO_RGUI] = COMBO(no_combo, KC_RGUI),
//     [COMBO_RSFT] = COMBO(oi_combo, KC_RSFT),
// };

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMK_M0:
        if (record->event.pressed) {
            SEND_STRING("cls\n");
        }
        break;

    case QMK_M1:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_LSFT(SS_TAP(X_9)));
        }
        break;

    case QMK_M2:
        if (record->event.pressed) {
            SEND_STRING("]d");
        }
        break;

    case QMK_M3:
        if (record->event.pressed) {
            SEND_STRING("]b");
        }
        break;

    case QMK_M4:
        if (record->event.pressed) {
            SEND_STRING("[d");
        }
        break;

    case QMK_M5:
        if (record->event.pressed) {
            SEND_STRING("[b");
        }
        break;

    case QMK_M6:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_Q) SS_TAP(X_S));
        }
        break;

    case QMK_M7:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_B) SS_TAP(X_C));
        }
        break;

    case QMK_M8:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_Q) SS_TAP(X_N));
        }
        break;

    case QMK_M9:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_G) SS_TAP(X_S) SS_TAP(X_T));
        }
        break;

    case QMK_M10:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_G) SS_TAP(X_D) SS_TAP(X_O));
        }
        break;

    case QMK_M11:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_G) SS_TAP(X_D) SS_TAP(X_C));
        }
        break;

    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3(
         KC_Q,   KC_W,   KC_F,   KC_P, KC_B,                                       KC_J,       KC_L,    KC_U,   KC_Y, KC_QUOT,
       // HOME_A, HOME_R, HOME_S, HOME_T, KC_G,                                       KC_M,     HOME_N,  HOME_E, HOME_I,  HOME_O,
         KC_A,   KC_R,   KC_S,   KC_T, KC_G,                                       KC_M,       KC_N,    KC_E,   KC_I,    KC_O,
         // KC_Z,   KC_X,   KC_C,   KC_D, KC_V,                                       KC_K,       KC_H, KC_COMM, KC_DOT, KC_SLSH,
         HOME_Z,   HOME_X,   HOME_C,   HOME_D, KC_V,                                       KC_K,       HOME_H, HOME_COMM, HOME_DOT, HOME_SLSH,
                     // LAYER_MEDIA, LAYER_NAV, LAYER_NUM,            LAYER_SYM, LAYER_VIM, LAYER_APPS
                     LAYER_NUM, LAYER_NAV, KC_SPC,                 LAYER_SYM, LAYER_VIM, LAYER_APPS
  ),

  [1] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                              XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX,            KC_MUTE, KC_MPLY, XXXXXXX
  ),

  [2] = LAYOUT_split_3x5_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            SGUI(KC_Z), LGUI(KC_Z),   KC_UP, LGUI(KC_C), LGUI(KC_X),
      // KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                               CAPSWRD,    KC_LEFT, KC_DOWN,   KC_RIGHT, LGUI(KC_V),
      OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), XXXXXXX,                               CAPSWRD,    KC_LEFT, KC_DOWN,   KC_RIGHT, LGUI(KC_V),
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               QK_BOOT,    KC_HOME, KC_PGDN,    KC_PGUP,     KC_END,
                                 XXXXXXX, XXXXXXX, XXXXXXX,              KC_BSPC, KC_ENT, KC_DEL
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
      // XXXXXXX, QMK_M10, LSFT(KC_LBRC), LSFT(KC_RBRC),  QMK_M1,                               XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
      XXXXXXX, QMK_M10, LSFT(KC_LBRC), LSFT(KC_RBRC),  QMK_M1,                               XXXXXXX, OSM(MOD_RSFT), OSM(MOD_RCTL), OSM(MOD_LALT), OSM(MOD_RGUI),
      XXXXXXX, QMK_M11,        QMK_M5,        QMK_M3, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                      QMK_M8, QMK_M7,  QMK_M6,                      XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [6] = LAYOUT_split_3x5_3(
      XXXXXXX, LGUI(KC_0), LGUI(KC_KP_MINUS), LGUI(KC_KP_PLUS), XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F3, HYPR(KC_C),        HYPR(KC_D),       HYPR(KC_F),  QMK_M0,              XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
      XXXXXXX,     KC_F12,        SGUI(KC_4),       HYPR(KC_N), XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                         MO(1), XXXXXXX, LCTL(KC_SPACE),     XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case HOME_A:
        // case HOME_O:
            // return TAPPING_TERM + 50;

        // case HOME_R:
        // case HOME_I:
            // return TAPPING_TERM + 50;

        // case HOME_S:
        // case HOME_E:
            // return TAPPING_TERM - 80;

        // case HOME_T:
        // case HOME_N:
            // return TAPPING_TERM - 50;

        // case LAYER_NUM:
        //     return TAPPING_TERM + 10;

        case HOME_Z:
        case HOME_X:
        case HOME_C:
        case HOME_D:
        case HOME_H:
        case HOME_COMM:
        case HOME_DOT:
        case HOME_SLSH:
            return TAPPING_TERM + 20;
        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef IGNORE_MOD_TAP_INTERRUPT_PER_KEY
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case HOME_A:
        // case HOME_R:
        // case HOME_S:
        // case HOME_T:
        // case HOME_N:
        // case HOME_E:
        // case HOME_I:
        // case HOME_O:
        case HOME_Z:
        case HOME_X:
        case HOME_C:
        case HOME_D:
        case HOME_H:
        case HOME_COMM:
        case HOME_DOT:
        case HOME_SLSH:
            return true;
        default:
            return false;
    }
}
#endif

#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case HOME_A:
        // case HOME_R:
        // case HOME_S:
        // case HOME_T:
        // case HOME_N:
        // case HOME_E:
        // case HOME_I:
        // case HOME_O:
        case HOME_Z:
        case HOME_X:
        case HOME_C:
        case HOME_D:
        case HOME_H:
        case HOME_COMM:
        case HOME_DOT:
        case HOME_SLSH:
            return true;
        default:
            return false;
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LAYER_MEDIA:
        case LAYER_NAV:
        case LAYER_NUM:
        case LAYER_SYM:
        case LAYER_VIM:
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
        // case LAYER_MEDIA:
        case LAYER_NAV:
        case LAYER_NUM:
        case LAYER_SYM:
        case LAYER_VIM:
        case LAYER_APPS:
            return true;
        default:
            return false;
    }
}
#endif

