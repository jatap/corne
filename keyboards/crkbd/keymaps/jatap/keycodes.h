#pragma once

// Macros
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
    QMK_M12,
    QMK_M13,
    QMK_M14,
};

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

// Layers
#define LAYER_MEDIA LT(1, KC_TAB)
#define LAYER_NAV LT(2, KC_ESC)
// #define LAYER_NUM LT(3, KC_SPC)
#define LAYER_SYM LT(4, KC_BSPC)
#define LAYER_VIM LT(5, KC_ENT)
#define LAYER_APPS LT(6, KC_DEL)

