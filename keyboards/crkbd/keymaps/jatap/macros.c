#include "macros.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /**
         * @emacs
         * @neovim
         */
        case QMK_M0:
            if (record->event.pressed) {
                SEND_STRING("cls\n");
            }
            break;

        /**
         * emacs consult-ripgrep (search in project)
         * @neovim (same)
         */
        case QMK_M1:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_COMM));
            }
            break;

        /**
         * @emacs
         * @neovim
         */
        case QMK_M2:
            if (record->event.pressed) {
                SEND_STRING("]d");
            }
            break;

        /**
         * @emacs consult-buffer (show all opened buffers)
         * @neovim move to the previous buffer
         */
        case QMK_M3:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_B));
            }
            break;

        /**
         * @emacs
         * @neovim
         */
        case QMK_M4:
            if (record->event.pressed) {
                SEND_STRING("[d");
            }
            break;

        /**
         * @emacs bufler (show all opened buffers with bufler)
         * @neovim move to the next buffer
         */
        case QMK_M5:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_B) SS_LSFT(SS_TAP(X_2)));
            }
            break;

        /**
         * @emacs
         * @neovim
         */
        case QMK_M6:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_Q) SS_TAP(X_S));
            }
            break;

        /**
         * @emacs delete-window
         * @neovim (same)
         */
        case QMK_M7:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_B) SS_TAP(X_D));
            }
            break;

        /**
         * @emacs
         * @neovim
         */
        case QMK_M8:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_Q) SS_TAP(X_N));
            }
            break;

        /**
         * @emacs magit-status (git status)
         * @neovim (same)
         */
        case QMK_M9:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_S));
            }
            break;

        /**
         * @emacs magit-log-current (git log)
         * @neovim (same)
         */
        case QMK_M10:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_L));
            }
            break;

        /**
         * @emacs magit-log-buffer-file (git log for the current file)
         * @neovim (same)
         */
        case QMK_M11:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_F));
            }
            break;

        /**
         * @emacs jatap/consult-word-at-point
         * @neovim
         */
        case QMK_M12:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_SEMICOLON));
            }
            break;

        /**
         * @emacs isearch-forward-thing-at-point
         * @neovim
         */
        case QMK_M13:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_LALT(SS_TAP(X_DOT)));
            }
            break;

        /**
         * @emacs delete-other-windows
         * @neovim
         */
        case QMK_M14:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_1));
            }
            break;

        /**
         * @emacs avy-goto-char-2
         * @neovim
         */
        case QMK_M15:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("g") SS_TAP(X_SLASH));
            }
            break;

        /**
         * @emacs split-window-below
         * @neovim
         */
        case QMK_M16:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_2));
            }
            break;

        /**
         * @emacs jatap/consult-ripgrep-at-point (search word at point on the project)
         * @neovim (same)
         */
        case QMK_M17:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_DOT));
            }
            break;

        /**
         * @emacs project-find-file
         * @neovim (same)
         */
        case QMK_M18:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_F));
            }
            break;

        /**
         * @emacs consult-project-buffer (show opened buffers on the project)
         * @neovim (same)
         */
        case QMK_M19:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_LSFT(SS_TAP(X_B)));
            }
            break;

        /**
         * @emacs git-gutter:previous hunk
         * @neovim (same)
         */
        /* > 42 keys */
        case QMK_M20:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_P));
            }
            break;

        /**
         * @emacs git-gutter:next hunk
         * @neovim (same)
         */
        /* > 42 keys */
        case QMK_M21:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_G) SS_TAP(X_N));
            }
            break;

        /**
         * @emacs backward-paragraph
         * @neovim (same)
         */
        case QMK_M22:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("{"));
            }
            break;

        /**
         * @emacs forward-paragraph
         * @neovim (same)
         */
        case QMK_M23:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("}"));
            }
            break;

        /**
         * @emacs consult-line (search in the current buffer)
         * @neovim (same)
         */
        case QMK_M24:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("s") SS_TAP(X_L));
            }
            break;

        /**
         * @emacs dired-jump (open dired with the location of the current buffer)
         * @neovim (same)
         */
        case QMK_M25:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_LCTL("j"));
            }
            break;

        /**
         * @emacs comment-line (comment current line or region)
         * @neovim (same)
         */
        case QMK_M26:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_C));
            }
            break;

        /**
         * @emacs project-switch-project
         * @neovim (same)
         */
        /* > 42 keys */
        case QMK_M27:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_P) SS_TAP(X_P));
            }
            break;

        /**
         * @emacs consult-imenu (show symbols)
         * @neovim show git UI to perform git operations (lazygit)
         */
        case QMK_M28:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("g") SS_TAP(X_COMM));
            }
            break;

        /**
         * @emacs ace-window (move focus to the next window)
         * @neovim (same)
         */
        case QMK_M29:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_O));
            }
            break;

        /**
         * @emacs multi-vterm-dedicated-toggle (toggle dedicated term)
         * @neovim (similar)
         */
        case QMK_M30:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c") SS_TAP(X_T) SS_TAP(X_D));
            }
            break;

        /**
         * @emacs split-window-right
         * @neovim (similar)
         */
        case QMK_M31:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x") SS_TAP(X_3));
            }
            break;
    }
    return true;
};
