---
description: Show QMK layer reference tables with a layout graph per layer
argument-hint: '[layer-name] [--save]'
---

Render the layer reference for the jatap crkbd keymap in `keyboards/crkbd/keymaps/jatap/`.

Layer to show: ${@:-all layers (Base, Niri, Nav, Emacs, Sym, Num, Apps, Extra)}. If the argument does not match a layer name, list the valid names and stop.

## Sources of truth (read all before writing)

- `keymap_colemakdh.c`: layer grid defines (`<LAYER>_L1`, `_L2`, `_L3`, `_R1`, `_R2`, `_R3`, and `_LEFT`/`_RIGHT` thumb rows) and which keys are `XXXXXXX` (disabled).
- `macros.h`: the `QMK_M*` enum; `macros.c`: each macro's `SEND_STRING` (the actual chord) and its `@emacs`/`@niri` doc comment.
- `keycodes.h`: thumb layer-tap keycodes (`LAYER_NIRI`, `LAYER_NAV`, `LAYER_EMACS`, `LAYER_SYM`, `LAYER_NUM`, `LAYER_APPS`, `LAYER_EXTRA`) and `HOME_*` home-row mods.

## Output format, per requested layer

0. Start each layer with a `# <LayerName>` heading (for example `# Apps`), using the layer's name from the layer list above.
1. A GitHub Flavoured Markdown table with columns Position, Key, Chord, Does. One row per physical key. Order rows column by column, top to bottom within each half: the full left half first (L1-1, L2-1, L3-1, then L1-2, L2-2, L3-2, through L1-5/L2-5/L3-5), then the full right half the same way with `R` prefixes, then the left thumb rows `LT-1`, `LT-2`, `LT-3`, then the right thumb rows `RT-1`, `RT-2`, `RT-3`. Use exactly these thumb labels in every layer. Disabled keys (`XXXXXXX`) get `-` (ASCII hyphen) in Key, Chord, and Does.
2. Directly below the table, add a second table for the layout graph. Its header is `ROW`, columns `1` to `5`, one empty gap column, then columns `1` to `5` again. Rows `L1`, `L2`, `L3` hold the grid keys (left half before the gap, right half after it), matching the grid defines exactly. The final `THUMBS` row places left thumb keys in left columns 1 to 3 and right thumb keys in right columns 1 to 3; all other thumb cells are empty. Give the graph table ASCII border lines instead of a `| --- |` separator row: one above the header, one below the header, one above the `THUMBS` row, and one below it. Use `-` for disabled keys. Graph cells: tap-hold home-row mods show `Super / A`; layer-tap thumbs show only the hold layer (`Niri`); wrapped chord keys show the base key (`Q`, `1`, `Escape`, `Backspace`); numpad keys use `Plus`/`Minus`; media keys use short plain-English labels. Add the required footnotes from rule 4 whenever a graph label is shorter than its table value.
3. Semantics:
   - Key: the readable base key (`Q`, `Backspace`, `Numpad Plus`) for wrapped combinations; macro name (`M23`) for macros; bare modifier name (`Shift`) for hold-only modifiers. Do not duplicate the full combination in Key: Chord owns that detail. Never use modifier glyphs; write Shift, Ctrl, Alt, Super. Never smash a modifier and a key together. A simultaneous combination always uses `+` between every part. Numpad keys are `Numpad Plus`/`Numpad Minus`, never abbreviations.
   - Cell text is ASCII-only. Never place box-drawing characters or ambiguous-width symbols in a cell: spell out Left, Right, Up, Down, pound sign, euro sign, Plus, Minus, and other names. Use ASCII `|` only as the GFM table delimiter. Escape a literal pipe key or pipe in Does as `\|` so it remains one cell. Write the word `Backtick` instead of a literal backtick key.
   - Wrapped chord keycodes: QMK's four-mod wrapper becomes `Ctrl+Alt+Shift+Super+<key>` in Chord; its three-mod wrapper becomes `Ctrl+Alt+Shift+<key>`. Key contains only the readable base key. The wrapper nicknames must never appear in generated output. `LCTL(KC_0)` has Key `0` and Chord `Ctrl+0`; keypad variants have Key `Numpad Plus`/`Numpad Minus` and Chord `Ctrl+Numpad Plus`/`Ctrl+Numpad Minus`. Spell out `Enter`, `Escape`, `Backspace`, `Delete`, `Page Up`, and `Page Down`.
   - Pure modifier keys (LSFT/RSFT/LCTL/RCTL/LALT/RALT/LGUI/RGUI): Key is the bare mod (`Shift`), Chord is `Left Shift`/`Right Shift`/..., Does is `Shift modifier (left hand)` or `Shift modifier (right hand)`.
   - Tap-hold keys (home row, layer thumbs): Key and Chord are both `<Mod> / <tap>` with spaces around the slash, mod first (`Super / A`, `Alt / R`); Does is `A on tap; left Super on hold` — name the hand for mods. Layer-tap thumbs are `Tab / Niri` in the table with Does `Tab on tap; Niri layer on hold`. A thumb that only holds a layer gets Chord `-` and Does `<Layer> layer on hold (<what it holds>)`.
   - Table style: write ASCII bordered tables. Delimiters are ASCII `|` with one space of padding. The key table has one `| --- |` separator row directly under its header. The layout graph table has no `| --- |` row; it uses border lines in that position instead. Every table gets a top border line above its header and a bottom border line below its last row, with no blank line between a border and its table. Derive every border from the table's column widths, so it is exactly as long as the other lines. Pad every cell to its column width so that all lines of one table, borders included, share one length. Never shrink an empty gap column: keep its existing width. Keep every table line at 160 columns or fewer. Never use box-drawing characters or pseudo-table rules.
   - Never run Prettier on `docs/*.md`. Prettier reflows a border line into the first table column, turns the bottom border into a data row, and re-pads columns to the widest cell, which breaks border alignment. Format these tables by hand to the rule above. After editing a table, rebuild its two border lines from the header line and confirm every line of that table has the same length.
   - Chord: what the key or macro sends, derived from `SEND_STRING` or `tap_code`, not from comments. A simultaneous combination joins every key with `+`, for example `Ctrl+Alt+Shift+Super+Q`, `Ctrl+Numpad Minus`, `Alt+Shift+G`. A sequence separates presses with `, then `, for example `Ctrl+X, then P, then Period`. Do not use application-specific modifier abbreviations or compressed key names; spell out every modifier and key. Linux keysyms are valid exact chords (`XF86AudioPrev`). QMK-internal actions are not chords: for `MO()` layer holds and `QK_BOOT` write `-` and describe the behaviour in Does.
   - Does: the verified effect in the target application (the Emacs command name, the Niri action), prefixed with who consumes it: `Niri:`, `Emacs:`, `Kitty:`, `System:`, `Media:`, or `App:`. Printable characters use `Types <char>`; non-printing keys use `Sends <name>`. If the effect is not verifiable, write `unverified: <what you checked>`, with a colon. For base-layer rows, Does is the behaviour (letter, modifier on hold, layer switch on hold/tap).
   - Legends: do not add modifier or notation legends; the table must use complete readable key names without requiring a legend.
4. Footnotes after the graph, only when needed: if the graph shortens any base key or chord label, add exactly one `Graph uses short key names; the table lists the full key or chord.` line. If the graph shows a hold layer instead of a layer-tap pair, add exactly one `Thumb keys show the hold layer; tap sends the key listed in the table.` line. Never duplicate a footnote.

## `--save` flag

- If the argument contains `--save`, strip the flag from it first and treat the remainder as the layer argument (default: all layers).
- After rendering, save the output to `docs/` relative to this keymap directory, one file per requested layer named `<layer-name>.md` in lowercase (for example `apps.md`), overwriting the file if it exists.
- Each saved file contains the layer's `# <LayerName>` heading, its GFM Position/Key/Chord/Does table, its GFM layout-graph table, and only the required footnotes, with no chat framing, headings for other layers, or closing notes. The Base file additionally ends with its Combos block.

## Base layer extra block

- The Base file ends with a Combos block: the plain line `Combos (Base layer positions):`, then a GFM table with columns Keys, Chord, Does, one row per combo in `combos.c`. Keys joins simultaneous keys with `+` and spells punctuation (`H+Comma`, `Comma+Period`); Chord shows the `send_string`/`tap_code16` output; Does uses `Types` or `Sends`.

## Verification rules

- Before writing any Does cell that claims an application effect, grep the consuming config for the exact chord (`~/.config/niri/config.kdl`, `~/.config/kitty/kitty.conf`, `~/.emacs.d/lisp/`). A grep with no hits means `unverified: no bind found for <chord>` — never assert that a bind does or does not exist without the grep, and never invent an effect.
- `SEND_STRING` in `macros.c` wins over any comment or table entry: derive every chord from it. If a comment and the chord disagree, trust the chord, fix the comment in the same change, and report the fix.
- Check the disabled-key placeholder too: every disabled position must show `-` in Key, Chord, and Does — never `—`.
- Every table row must correspond to an entry in a grid define; never add rows that are not in `keymap_colemakdh.c`.
