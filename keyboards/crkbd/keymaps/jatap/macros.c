#include "macros.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /**
         * @emacs project-find-regexp (search in project)
         */
        case QMK_M0:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_COMM));
            }
            break;

        /**
         * @emacs switch-to-buffer (prompt for a buffer)
         */
        case QMK_M1:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_B));
            }
            break;

        /**
         * @emacs (unbound key, nothing happens)
         */
        case QMK_M2:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_B) SS_LSFT(SS_TAP(X_2)));
            }
            break;

        /**
         * @emacs delete-window
         */
        case QMK_M3:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_B) SS_TAP(X_D));
            }
            break;

        /**
         * @emacs magit-status (git status)
         */
        case QMK_M4:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_S));
            }
            break;

        /**
         * @emacs magit-log-current (git log)
         */
        case QMK_M5:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_L));
            }
            break;

        /**
         * @emacs  magit-log-buffer-file (git log for the current file)
         */
        case QMK_M6:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_I));
            }
            break;

        /**
         * @emacs jatap/occur-word-at-point
         */
        case QMK_M7:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_COMMA));
            }
            break;

        /**
         * @emacs isearch-forward-thing-at-point
         */
        case QMK_M8:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_LALT(SS_TAP(X_DOT)));
            }
            break;

        /**
         * @emacs delete-other-windows
         */
        case QMK_M9:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_1));
            }
            break;

        /**
         * @emacs replace-regexp-as-diff
         */
        case QMK_M10:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_R));
            }
            break;

        /**
         * @emacs split-window-below
         */
        case QMK_M11:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_2));
            }
            break;

        /**
         * @emacs jatap/project-find-regexp-at-point (search word at point on the project)
         */
        case QMK_M12:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_DOT));
            }
            break;

        /**
         * @emacs project-find-file
         */
        case QMK_M13:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_F));
            }
            break;

        /**
         * @emacs activities-switch-buffer (show buffers of the current activity)
         */
        case QMK_M14:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)) SS_TAP(X_B));
            }
            break;

        /**
         * @emacs backward-paragraph
         */
        case QMK_M15:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("{"));
            }
            break;

        /**
         * @emacs forward-paragraph
         */
        case QMK_M16:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("}"));
            }
            break;

        /**
         * @emacs occur (search in the current buffer)
         */
        case QMK_M17:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_L));
            }
            break;

        /**
         * @emacs dired-jump (open dired with the location of the current buffer)
         */
        case QMK_M18:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_LCTL("j"));
            }
            break;

        /**
         * @emacs comment-line (comment current line or region)
         */
        case QMK_M19:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_C));
            }
            break;

        /**
         * @emacs goto-line
         */
        case QMK_M20:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("G") SS_TAP(X_G));
            }
            break;

        /**
         * @emacs other-window (move focus to the next window)
         */
        case QMK_M21:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_O));
            }
            break;

        /**
         * @emacs jatap/vterm-new (new vterm session)
         */
        case QMK_M22:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_T) SS_TAP(X_D));
            }
            break;

        /**
         * @emacs split-window-right
         */
        case QMK_M23:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_3));
            }
            break;

        /**
         * @emacs set-mark-command (Move point to where the mark was,
         * and restore the mark from the ring of former marks).
         */
        case QMK_M24:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("u") SS_LCTL(SS_TAP(X_SPACE)));
            }
            break;

        /**
         * @emacs Set the mark, pushing it onto the mark ring, without
         * activating it.
         */
        case QMK_M25:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(" ") SS_LCTL(SS_TAP(X_SPACE)));
            }
            break;

        /**
         * Pound sign via Linux Compose: Compose - l
         * @emacs
         */
        case QMK_M26:
            if (record->event.pressed) {
                tap_code(KC_CAPS);
                tap_code(KC_MINS);
                tap_code(KC_L);
            }
            break;

        /**
         * Euro sign via Linux Compose: Compose = e
         * @emacs
         */
        case QMK_M27:
            if (record->event.pressed) {
                tap_code(KC_CAPS);
                tap_code(KC_EQL);
                tap_code(KC_E);
            }
            break;

        /**
         * @niri set column width 28% (Super+Ctrl+2)
         */
        case QMK_M28:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_2))));
            }
            break;

        /**
         * @niri set column width 44% (Super+Ctrl+4)
         */
        case QMK_M29:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_4))));
            }
            break;

        /**
         * @niri set column width 16% (Super+Ctrl+1)
         */
        case QMK_M30:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_1))));
            }
            break;
    }
    return true;
};
