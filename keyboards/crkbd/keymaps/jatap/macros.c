#include QMK_KEYBOARD_H

#include "macros.h"

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

    // Free slot
    // case QMK_M6:

    case QMK_M7:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_B) SS_TAP(X_C));
        }
        break;

    // Free slot
    // case QMK_M8:

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

    case QMK_M12:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(" ") SS_TAP(X_LBRC));
        }
        break;

    case QMK_M13:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(" ") SS_TAP(X_MINS));
        }
        break;

    case QMK_M14:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(" ") SS_LSFT(SS_TAP(X_BSLS)));
        }
        break;

    }
    return true;
};


