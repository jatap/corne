#include "macros.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /** @emacs project-find-regexp (search in project) */
        case QMK_M0:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_COMM));
            }
            break;

        /** @emacs switch-to-buffer */
        case QMK_M1:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_B));
            }
            break;

        /** @emacs ibuffer (list buffers) */
        case QMK_M2:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_B) SS_LSFT(SS_TAP(X_2)));
            }
            break;

        /** @emacs delete-window */
        case QMK_M3:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_B) SS_TAP(X_D));
            }
            break;

        /** @emacs magit-status */
        case QMK_M4:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_S));
            }
            break;

        /** @emacs magit-log-current */
        case QMK_M5:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_L));
            }
            break;

        /** @emacs magit-log-buffer-file */
        case QMK_M6:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_I));
            }
            break;

        /** @emacs jatap/occur-word-at-point */
        case QMK_M7:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_COMMA));
            }
            break;

        /** @emacs isearch-forward-thing-at-point */
        case QMK_M8:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_LALT(SS_TAP(X_DOT)));
            }
            break;

        /** @emacs delete-other-windows */
        case QMK_M9:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_1));
            }
            break;

        /** @emacs replace-regexp-as-diff */
        case QMK_M10:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_R));
            }
            break;

        /** @emacs split-window-below */
        case QMK_M11:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_2));
            }
            break;

        /** @emacs jatap/project-find-regexp-at-point (search word in project) */
        case QMK_M12:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_DOT));
            }
            break;

        /** @emacs project-find-file */
        case QMK_M13:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_F));
            }
            break;

        /** @emacs activities-switch-buffer (buffers of the current activity) */
        case QMK_M14:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)) SS_TAP(X_B));
            }
            break;

        /** @emacs backward-paragraph */
        case QMK_M15:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("{"));
            }
            break;

        /** @emacs forward-paragraph */
        case QMK_M16:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("}"));
            }
            break;

        /** @emacs occur (list matching lines) */
        case QMK_M17:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_L));
            }
            break;

        /** @emacs dired-jump (dired at the current buffer's directory) */
        case QMK_M18:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_LCTL("j"));
            }
            break;

        /** @emacs comment-line */
        case QMK_M19:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_C));
            }
            break;

        /** @emacs goto-line */
        case QMK_M20:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("g") SS_TAP(X_G));
            }
            break;

        /** @emacs other-window (focus next window) */
        case QMK_M21:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_O));
            }
            break;

        /** @emacs jatap/vterm-new (new vterm session) */
        case QMK_M22:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_T) SS_TAP(X_D));
            }
            break;

        /** @emacs split-window-right */
        case QMK_M23:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_3));
            }
            break;

        /** @emacs jumps to the mark and pops the mark ring */
        case QMK_M24:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("u") SS_LCTL(SS_TAP(X_SPACE)));
            }
            break;

        /** @emacs set-mark-command twice (sets mark without activating) */
        case QMK_M25:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(" ") SS_LCTL(SS_TAP(X_SPACE)));
            }
            break;

        /** @system Types the pound sign via Linux text input */
        case QMK_M26:
            if (record->event.pressed) {
                tap_code(KC_CAPS);
                tap_code(KC_MINS);
                tap_code(KC_L);
            }
            break;

        /** @system Types the euro sign via Linux text input */
        case QMK_M27:
            if (record->event.pressed) {
                tap_code(KC_CAPS);
                tap_code(KC_EQL);
                tap_code(KC_E);
            }
            break;

        /** @niri Sets column width to 28% (set-column-width) */
        case QMK_M28:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_2))));
            }
            break;

        /** @niri Sets column width to 44% (set-column-width) */
        case QMK_M29:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_4))));
            }
            break;

        /** @niri Sets column width to 16% (set-column-width) */
        case QMK_M30:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_1))));
            }
            break;
    }
    return true;
};
