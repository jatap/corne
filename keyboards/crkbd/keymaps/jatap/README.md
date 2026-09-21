# Jatap's Corne keymap

Crkbd (36-key, 3x5+3) with Colemak-DH. This file is the map and the notation key. The per-layer detail — every position, chord and effect — lives in [`docs/`](#the-layer-documents), one file per layer, generated from the firmware.

## How to read

- Keys are described by physical position, never by what the host types. Grids show five left-hand keys then five right-hand keys per row, with the thumb row last.
- Simultaneous keys use `+`; sequential presses use `, then `. So `Ctrl+X, then B` means press and release `Ctrl+X`, then `B`.
- Modifiers are named Super, Alt, Ctrl and Shift. A chord carrying three or four of them uses QMK's own name: `HYPR+<key>` is Ctrl+Alt+Shift+Super and `MEH+<key>` is Ctrl+Alt+Shift, as defined in `quantum/quantum_keycodes.h`. This keymap uses only those two; QMK's `LCAG` (Ctrl+Alt+Super) appears nowhere here.
- `M##` is a QMK macro. Each layer document lists what its macros send and do.
- Home-row keys and base thumbs are tap-hold: tap sends the key, hold activates the modifier or layer.
- `-` is a disabled key, not a transparent key.

## Layers

Hold a thumb to reach a layer. Base is Colemak-DH with home-row modifiers; its document also carries the combo table.

| Layer           | Reach                   | What it is for                                                                        |
| --------------- | ----------------------- | ------------------------------------------------------------------------------------- |
| `docs/base.md`  | —                       | Colemak-DH, home-row mods, layer-tap thumbs, combos                                   |
| `docs/niri.md`  | hold left thumb 1       | Window and column management, terminal and launcher spawns, column widths             |
| `docs/nav.md`   | hold left thumb 2       | Arrow cluster, Home/End/Page keys, Caps Lock, Caps Word, Emacs multiple-cursor chords |
| `docs/emacs.md` | hold left thumb 3       | Emacs commands as macros: buffers, windows, marks, projects, Magit, comment, grep     |
| `docs/sym.md`   | hold right thumb 1      | Symbols and brackets, Compose sequences for £ and €                                   |
| `docs/num.md`   | hold right thumb 2      | Numpad block with arithmetic keys                                                     |
| `docs/apps.md`  | hold right thumb 3      | App-level chords: Niri window actions, zoom, Emacs window commands                    |
| `docs/extra.md` | hold Niri right thumb 3 | Function keys, media keys, bootloader                                                 |

### Notes worth having

These are the decisions a table cannot show.

- **Copy, cut, paste and undo are still not on the keymap.** They live in the applications: your Emacs binds the Super chords to other commands (`compile`, `crux` helpers, `vundo`). The Nav layer does carry the Emacs multiple-cursor chords (`mc/*`), because those need macro payloads and sit under the left-thumb Nav layer.
- **Compose uses the `compose:caps` XKB option.** The £ and € macros on the Sym layer tap Caps Lock, which Niri maps to Compose; they are not modifier chords.
- **Zoom keys are cross-application.** `Ctrl+0`, `Ctrl+Numpad Minus` and `Ctrl+Numpad Plus` reset or step the font size in Kitty, Emacs and Zen Browser alike, which is the point of sending the plain chords rather than app-specific ones. The one-shot combined modifiers that used to sit on the Num layer were removed; one-shot support is still configured in `config.h`.
- **`Boot` on the Extra layer** resets the keyboard into bootloader mode.
- **The `<?php` combo was removed**, not lost: it shared both keys with the `L+U` email combo, so QMK could never tell them apart and it never fired.

## The layer documents

`docs/<layer>.md` is a generated reference. `/layers` rebuilds its source-owned content from the firmware and macro annotations, while `layer_tables.py` owns the layout. Each file holds a key table (position, key, chord, effect), a layout graph, and only the footnotes that still apply. Two files govern it:

- `docs/FORMAT.md` — the contract: table shapes, the 140-column cap, cell vocabulary, what is prohibited.
- `docs/PLAN.md` — the design record: why the layout is derived by a script, which measurements set the numbers, and the places the original plan proved wrong.

`docs/tools/layer_tables.py` generates source-owned cells and enforces the layout. It owns every column width, border and ` ```text ` fence, so a table is never aligned by hand:

```sh
python3 docs/tools/layer_tables.py generate --write <layer>   # regenerate one layer
python3 docs/tools/layer_tables.py generate --check all       # compare all generated documents in memory
python3 docs/tools/layer_tables.py check docs/*.md             # verify layout and source correspondence
```

Prettier is never run on a layer file; see `docs/FORMAT.md`. It still applies to this file.

### Regenerating after a firmware change

`.pi/prompts/layers.md` rebuilds a document from the keymap sources. Run it after anything that changes what a layer _is_ — keys moved, a layer added, a macro rewritten:

```sh
pi -a "/layers niri --save"        # or, inside a pi session: /layers niri --save
```

It reads `keymap_colemakdh.c`, `keycodes.h`, `macros.c` and `combos.c`. Firmware expressions define chords, while strict `@emacs`, `@niri` and `@system` annotations define macro effects. If a macro effect needs correction, edit its annotation and regenerate the layer. Direct application shortcuts without annotations retain their reviewed document claim. The generator reports changed or missing claims for manual review and never invents application behaviour.

## Behaviour notes

- Layer thumbs (Niri, Nav, Sym, Num, Apps) are `LT()` keys with permissive hold enabled, so tapping one and rolling into another key inside the tapping term activates the layer. Two intentional toggles: `HOLD_ON_OTHER_KEY_PRESS_PER_KEY` stays commented out, so `get_hold_on_other_key_press()` in `keymap.c` is not compiled (uncomment the define to activate it); `TAPPING_FORCE_HOLD_PER_KEY` compiles `get_tapping_force_hold()`, but this QMK tree's core no longer calls it — the feature became `QUICK_TAP_TERM` (see `docs/ChangeLog/20230226.md` in the firmware tree).
- Tapping terms are shortened per key: home-row mods by 10-30 ms, layer thumbs by 30 ms (see `keymap.c`).
- Auto-shift is enabled for digits and symbols only (`NO_AUTO_SHIFT_ALPHA`, 175 ms timeout). Holding a letter does nothing special; holding `1` types `!`.
- Accepted side effects: inside pi, `Ctrl+X` copies the message and `Ctrl+C` copies the selection (clears the editor on a second press). The Emacs macros target Emacs; pi keybindings stay untouched.
- Macros tagged `@emacs`, `@niri` or `@system` in `macros.c` carry the authoritative `Does` text. Generation guarantees that the layer document matches that annotation; manual review remains responsible for application correctness.

## Build and clangd database

For a normal firmware build, run only this command from the repo root:

```sh
PATH="$PWD/.venv/bin:$PATH" make crkbd:jatap
```

Regenerate the clangd database only when it is missing, after switching back from another board, after changing build flags in `rules.mk` or `info.json`, or after updating QMK or the toolchain:

```sh
.venv/bin/qmk generate-compilation-database -kb crkbd -km jatap
PATH="$PWD/.venv/bin:$PATH" make crkbd:jatap
```

`generate-compilation-database` rewrites the repo-level `compile_commands.json` and runs `make clean`, so always run the real build afterwards. Clangd reads one database for the whole repo; after working on the SplitKB Aurora Corne, regenerate the crkbd database before trusting LSP diagnostics in this directory.

## Hardware and recovery

- Board: foostan Corne rev1 hotswap, USB-C plugged into the left half. `MASTER_LEFT` in `config.h` matches this setup.
- Build from the repo root with `PATH="$PWD/.venv/bin:$PATH" make crkbd:jatap`. Flash only when you intend to write firmware: `PATH="$PWD/.venv/bin:$PATH" make crkbd:jatap:flash`.
- Normal bootloader entry: hold left thumb 1 (Niri), then right thumb 3 on that layer (Extra), then press the `Boot` key at the outer left palm-row position (`QK_BOOT` in firmware).
- Emergency bootloader entry, for when the `Boot` key is unreachable: unplug USB-C, hold the top-left key (`Q`), plug in while still holding, wait a few seconds, then release. This runs QMK Bootmagic Lite, clears EEPROM settings, and jumps to the Caterina bootloader.
- Bootloader evidence: `dmesg` shows `2341:0037 Arduino Micro` and `ttyACM0`. Normal firmware shows `4653:0001 foostan Corne`. Caterina returns to normal firmware after about 8 seconds if no flash starts.

## Files

- `keymap.c`, `keymap_colemakdh.c` — layer layouts
- `macros.c` — macro definitions and authoritative `Does` annotations
- `combos.c` — combos
- `keycodes.h`, `layers.h` — home-row mods, layer-tap keys, layer names
- `docs/` — generated layer reference, one file per layer
- `docs/FORMAT.md` — the table contract; `docs/tools/layer_tables.py` enforces it
- `docs/PLAN.md` — the design record behind that contract and script
- `.pi/prompts/layers.md` — the prompt that regenerates `docs/`
- Niri side: `~/.dotfiles/niri/.config/niri/config.kdl` and `KEYBINDINGS.md`
