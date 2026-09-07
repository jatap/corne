---
description: Show QMK layer reference tables with a layout graph per layer
argument-hint: "[layer-name] [--save]"
---
Render the layer reference for the jatap crkbd keymap in `keyboards/crkbd/keymaps/jatap/`.

Layer to show: ${@:-all layers (Base, Niri, Nav, Emacs, Sym, Num, Apps, Extra)}. If the argument does not match a layer name, list the valid names and stop.

## Sources of truth (read all before writing)

- `keymap_colemakdh.c`: layer grid defines (`<LAYER>_L1`, `_L2`, `_L3`, `_R1`, `_R2`, `_R3`, and `_LEFT`/`_RIGHT` thumb rows) and which keys are `XXXXXXX` (disabled).
- `macros.h`: the `QMK_M*` enum; `macros.c`: each macro's `SEND_STRING` (the actual chord) and its `@emacs`/`@niri` doc comment.
- `keycodes.h`: thumb layer-tap keycodes (`LAYER_NIRI`, `LAYER_NAV`, `LAYER_EMACS`, `LAYER_SYM`, `LAYER_NUM`, `LAYER_APPS`, `LAYER_EXTRA`) and `HOME_*` home-row mods.

## Output format, per requested layer

1. A table with columns: Position, Key, Chord, Does. One row per physical key. Order rows column by column, top to bottom: L1-1, L2-1, L3-1, then L1-2, L2-2, L3-2, and so on through L1-5/L2-5/L3-5 (use `R` prefixes for the right half); the thumb rows come after all grid rows, in left-to-right order. Disabled keys (`XXXXXXX`) get Position and `—` in Key, Chord, and Does.
2. Directly below the table, a Markdown layout-graph table with column and row separators: header `| Row | 1 | 2 | 3 | 4 | 5 | | 1 | 2 | 3 | 4 | 5 |`, where the unlabeled column separates the left and right halves. Rows `L1`, `L2`, `L3` hold the grid keys (left half in columns 1–5 before the gap, right half after it), matching the grid defines exactly. After the grid rows add one empty row, then the `Thumb` row: left thumb keys occupy left-half columns 1–3 and right thumb keys occupy right-half columns 1–3, in left-to-right order; all other thumb cells are empty. Use `—` for disabled keys.
3. Semantics:
   - Key: macro name (`M23`), named key (`HyprQ`, `⌃0`), or hold-only mods (`⇧ ⌃ ⌥ ⌘`).
   - Chord: what the key or macro sends (`C-x 3`, `Hypr+Q`, `Ctrl+Kp-`, `M-s M-.`), derived from the macro's `SEND_STRING`, not from comments.
   - Does: the verified effect in the target application (the Emacs command name, the Niri action). For base-layer rows, Does is the behavior (letter, mod on hold, layer switch on hold/tap).

## `--save` flag

- If the argument contains `--save`, strip the flag from it first and treat the remainder as the layer argument (default: all layers).
- After rendering, save the output to `docs/` relative to this keymap directory, one file per requested layer named `<layer-name>.md` in lowercase (for example `apps.md`), overwriting the file if it exists.
- Each saved file contains only that layer's Position/Key/Chord/Does table and its layout-graph table, with no chat framing, headings for other layers, or closing notes.

## Verification rules

- `SEND_STRING` in `macros.c` wins over any comment or table entry: derive every chord from it. If a comment and the chord disagree, trust the chord, fix the comment in the same change, and report the fix.
- If a binding's effect in the target app is not verifiable from `~/.emacs.d/lisp/`, `~/.config/niri/config.kdl`, or `~/.dotfiles/kitty/.config/kitty/kitty.conf`, say so explicitly in the Does cell as "unverified" instead of inventing an effect.
- Every table row must correspond to an entry in a grid define; never add rows that are not in `keymap_colemakdh.c`.
