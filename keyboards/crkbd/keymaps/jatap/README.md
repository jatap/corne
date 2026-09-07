# Jatap's Corne keymap — layer reference

Crkbd (36-key, 3x5+3) with Colemak-DH. This document is a reading reference: what each layer has, and which app or system consumes each key. The source of truth is the keymap code (see [Files](#files)).

## How to read

- Grids show the physical layout. Each row contains five left-hand keys followed by five right-hand keys. The last line is the thumb row in physical left-to-right order.
- Chords spell out every key. Simultaneous keys use `+`; sequential presses use `, then `.
- `M##` is a QMK macro; look it up in the table under that layer.
- Modifiers use the names Super, Alt, Ctrl, and Shift.
- Home-row keys and base thumbs are tap-hold: tap sends the key, while hold activates the modifier or layer.
- `-` is a disabled key, not a transparent key.
- "Acts on" identifies the consumer: `Niri` (window manager), `Emacs`, `System` (OS-level or XKB Compose), or `App` (the focused application).

## Base (Colemak-DH)

Full generated key table: [docs/base.md](docs/base.md).

```
Q           W         F          P           B    J    L          U         Y         '
Super / A   Alt / R   Ctrl / S   Shift / T   G    M    Shift / N  Ctrl / E  Alt / I   Super / O
Z           X         C          D           V    K    H          ,         .         /

Tab       Escape   Space   Backspace   Enter   Delete
Niri      Nav      Emacs   Sym         Num     Apps
```

- Home row: tap sends the letter; hold activates the modifier shown before `/`.
- Thumbs: tap sends the top key; hold activates the bottom layer.

## Niri (hold left thumb 1)

Full generated key table: [docs/niri.md](docs/niri.md).

```
C       Escape   -      -       -      F   M30   A   Backspace   -
Super   Alt      Ctrl   Shift   -      -   M29   T   -           -
-       -        -      -       -      -   M28   4   X           -

U   D   Extra
```

The grid shows base keys. The Chord column gives every modifier.

| Key       | Chord                          | Acts on | Function                             |
| --------- | ------------------------------ | ------- | ------------------------------------ |
| C         | Ctrl+Alt+Shift+Super+C         | Niri    | Config reload notification           |
| Escape    | Ctrl+Alt+Shift+Super+Escape    | Niri    | Launch Waybar                        |
| F         | Ctrl+Alt+Shift+Super+F         | Niri    | Maximise window to edges             |
| A         | Ctrl+Alt+Shift+Super+A         | Niri    | Focus first column                   |
| T         | Ctrl+Alt+Shift+Super+T         | Niri    | Centre column                        |
| Backspace | Ctrl+Alt+Shift+Super+Backspace | Niri    | Toggle floating + 28% width + centre |
| 4         | Ctrl+Alt+Shift+Super+4         | Niri    | Focus last column                    |
| X         | Ctrl+Alt+Shift+Super+X         | Niri    | Switch focus floating/tiling         |
| U         | Ctrl+Alt+Shift+Super+U         | Niri    | Helper script menu                   |
| D         | Ctrl+Alt+Shift+Super+D         | Niri    | Toggle fuzzel launcher               |
| Extra     | -                              | Niri    | Hold for Extra layer                 |

| Macro | Sends        | Acts on | Function             |
| ----- | ------------ | ------- | -------------------- |
| M30   | Super+Ctrl+1 | Niri    | Set column width 16% |
| M29   | Super+Ctrl+4 | Niri    | Set column width 44% |
| M28   | Super+Ctrl+2 | Niri    | Set column width 28% |

## Nav (hold left thumb 2)

Full generated key table: [docs/nav.md](docs/nav.md).

```
-       -      -      -       -      Caps Lock   -          Up          -       -
Super   Alt    Ctrl   Shift   -      Caps Word   Left       Down        Right   -
-       -      -      -       -      Home        Page Up    Page Down   End     -

-   -   -
```

- `Caps Word` toggles Caps Word.
- Copy, cut, paste, and undo live in the applications: your Emacs binds the Super chords to other commands (`compile`, `crux` helpers, `vundo`), so these keys are not on the keymap.

## Emacs (hold left thumb 3)

Full generated key table: [docs/emacs.md](docs/emacs.md).

```
-       -      -      -       -      M17   M18   M19   M4   M20
Super   Alt    Ctrl   Shift   -      M14   M15   M16   M5   M21
-       -      -      -       -      M13   M1    M2    M6   M22

M0   M3   M12
```

| Macro | Sends                        | Acts on | Function                                      |
| ----- | ---------------------------- | ------- | --------------------------------------------- |
| M17   | Alt+S, then L                | Emacs   | Occur (search in current buffer)              |
| M18   | Ctrl+X, then Ctrl+J          | Emacs   | Dired-jump (open dired at current buffer)     |
| M19   | Ctrl+C, then C               | Emacs   | Comment line or region                        |
| M4    | Ctrl+C, then G, then S       | Emacs   | Magit status (git status)                     |
| M20   | Alt+Shift+G, then G          | Emacs   | Unverified: no matching Emacs binding         |
| M14   | Super+Enter, then B          | Emacs   | Activities: switch buffer of current activity |
| M15   | Alt+Shift+Left Bracket       | Emacs   | Backward paragraph                            |
| M16   | Alt+Shift+Right Bracket      | Emacs   | Forward paragraph                             |
| M5    | Ctrl+C, then G, then L       | Emacs   | Magit log current                             |
| M21   | Ctrl+X, then O               | Emacs   | Other window                                  |
| M13   | Ctrl+X, then P, then F       | Emacs   | Project find file                             |
| M1    | Ctrl+X, then B               | Emacs   | switch-to-buffer (prompt for a buffer)        |
| M2    | Ctrl+C, then B, then Shift+2 | Emacs   | Ibuffer (list buffers)                        |
| M6    | Ctrl+C, then G, then I       | Emacs   | Magit log for current file                    |
| M22   | Ctrl+C, then T, then D       | Emacs   | New vterm session                             |
| M0    | Ctrl+X, then P, then Comma   | Emacs   | Project find regexp                           |
| M3    | Ctrl+C, then B, then D       | Emacs   | Delete window                                 |
| M12   | Ctrl+X, then P, then Period  | Emacs   | Project find regexp at point                  |

## Sym (hold right thumb 1)

Full generated key table: [docs/sym.md](docs/sym.md).

```
{   &   *   (              }      -   -       -      -     -
:   $   %   ^              Numpad Plus   -   Shift   Ctrl   Alt   Super
~   !   @   #              Pipe   -      M26     M27    -     -

(   )   _
```

| Macro | Sends                         | Acts on | Function                 |
| ----- | ----------------------------- | ------- | ------------------------ |
| M26   | Caps Lock, then Minus, then L | System  | Pound sign (XKB Compose) |
| M27   | Caps Lock, then Equal, then E | System  | Euro sign (XKB Compose)  |

Compose uses the `compose:caps` XKB option: the macro taps Caps Lock, which Niri maps to Compose.

## Num (hold right thumb 2)

Full generated key table: [docs/num.md](docs/num.md).

```
[          7   8   9   ]           -   -       -      -     -
;          4   5   6   =           -   Shift   Ctrl   Alt   Super
Backtick   1   2   3   Backslash   -   -       -      -     -

.   0   -
```

- One-shot combined modifiers were removed; one-shot modifier support remains configured in `config.h`.

## Apps (hold right thumb 3)

Full generated key table: [docs/apps.md](docs/apps.md).

```
Q   0   Numpad Minus   Numpad Plus   M23   -   M24   3   2   Enter
-   I   B              S              M11   9   Shift  Ctrl   Alt   Super
R   P   1              N              M9    0   M25    -      5     6

M8   M7   M10
```

The grid shows base keys. The Chord column gives every modifier.

| Key          | Chord                      | Acts on | Function                     |
| ------------ | -------------------------- | ------- | ---------------------------- |
| Q            | Ctrl+Alt+Shift+Super+Q     | Niri    | Close window                 |
| R            | Ctrl+Alt+Shift+Super+R     | Niri    | Switch preset column width   |
| 1            | Ctrl+Alt+Shift+Super+1     | Niri    | Screen record menu           |
| N            | Ctrl+Alt+Shift+Super+N     | Niri    | Clipboard history (cliphist) |
| 2            | Ctrl+Alt+Shift+Super+2     | Niri    | Floating terminal            |
| 3            | Ctrl+Alt+Shift+Super+3     | Niri    | Floating big terminal        |
| 5            | Ctrl+Alt+Shift+Super+5     | Niri    | Floating left terminal       |
| 6            | Ctrl+Alt+Shift+Super+6     | Niri    | Floating right terminal      |
| 9            | Ctrl+Alt+Shift+Super+9     | Niri    | Floating big left terminal   |
| 0            | Ctrl+Alt+Shift+Super+0     | Niri    | Floating big right terminal  |
| Enter        | Ctrl+Alt+Shift+Super+Enter | Niri    | Spawn kitty terminal         |
| B            | Ctrl+Alt+Shift+B           | Niri    | Bluetui (Bluetooth TUI)      |
| I            | Ctrl+Alt+Shift+I           | Niri    | Rustnet (network monitor)    |
| S            | Ctrl+Alt+Shift+S           | Niri    | Wiremix (audio mixer)        |
| P            | Ctrl+Alt+Shift+P           | Niri    | Power menu (fuzzel)          |
| 0            | Ctrl+0                     | App     | Reset zoom                   |
| Numpad Minus | Ctrl+Numpad Minus          | App     | Zoom out                     |
| Numpad Plus  | Ctrl+Numpad Plus           | App     | Zoom in                      |

| Macro | Sends                       | Acts on | Function                                |
| ----- | --------------------------- | ------- | --------------------------------------- |
| M23   | Ctrl+X, then 3              | Emacs   | Split window right                      |
| M11   | Ctrl+X, then 2              | Emacs   | Split window below                      |
| M9    | Ctrl+X, then 1              | Emacs   | Delete other windows                    |
| M24   | Ctrl+U, then Ctrl+Space     | Emacs   | Move point to previous mark (mark ring) |
| M25   | Ctrl+Space, then Ctrl+Space | Emacs   | Set mark without activating             |
| M8    | Alt+S, then Alt+Period      | Emacs   | Isearch thing at point                  |
| M7    | Alt+S, then Comma           | Emacs   | Occur word at point                     |
| M10   | Alt+S, then R               | Emacs   | Replace regexp as diff                  |

## Extra (hold Niri right thumb 3)

Full generated key table: [docs/extra.md](docs/extra.md).

```
F10   F9               F8            F7          F6           F5   F4      F3     F2    F1
-     Previous Track   Volume Down   Volume Up   Next Track   -    Shift   Ctrl   Alt   Super
-     F12              F11           -           Boot         -    -       -      -     -

Mute   Play / Pause   -
```

- Media keys send standard XF86 media and volume keysyms to the desktop session.
- `Boot` resets the keyboard into bootloader mode.

## Combos (Base layer positions)

| Combo        | Types          |
| ------------ | -------------- |
| H+Comma      | Tab            |
| Comma+Period | `->`           |
| X+C          | `=>`           |
| J+L          | personal email |
| L+U          | work email     |

- The old `U+L` `<?php` combo was removed: it shared both keys with `L+U`, so QMK could never tell them apart and `<?php` never fired.

## Behaviour notes

- Layer thumbs (Niri, Nav, Sym, Num, Apps) are `LT()` keys with permissive hold enabled, so tapping one and rolling into another key inside the tapping term activates the layer. Two intentional toggles: `HOLD_ON_OTHER_KEY_PRESS_PER_KEY` stays commented out, so `get_hold_on_other_key_press()` in `keymap.c` is not compiled (uncomment the define to activate it); `TAPPING_FORCE_HOLD_PER_KEY` compiles `get_tapping_force_hold()`, but this QMK tree's core no longer calls it — the feature became `QUICK_TAP_TERM` (see `docs/ChangeLog/20230226.md` in the firmware tree).
- Tapping terms are shortened per key: home-row mods by 10-30 ms, layer thumbs by 30 ms (see `keymap.c`).
- Auto-shift is enabled for digits and symbols only (`NO_AUTO_SHIFT_ALPHA`, 175 ms timeout). Holding a letter does nothing special; holding `1` types `!`.
- Zoom keys on the Apps layer (`Ctrl+0`, `Ctrl+Numpad Minus`, `Ctrl+Numpad Plus`) keep zooming consistent across Emacs, Zen Browser, and Kitty: the same chords reset or change zoom or font size in all three.
- Accepted side effects: inside pi, `Ctrl+X` copies the message and `Ctrl+C` copies the selection (clears the editor on a second press). The Emacs macros target Emacs; pi keybindings stay untouched.
- Macros tagged `@emacs` / `@niri` are documented in `macros.c`.

## Rendering this reference with pi

- The pi prompt `.pi/prompts/layers.md` regenerates the layer reference from the keymap sources: `/layers apps` renders one layer, `/layers` renders all of them.
- Add `--save` to write the output to files instead of the chat: `/layers apps --save` writes `docs/apps.md`, and `/layers --save` writes one file per layer. File names use the lowercase layer name, and existing files are overwritten. Each saved file starts with a `# <Layer name>` heading and contains a GFM key table and layout table. Tables use ASCII `|` delimiters, escape a literal pipe key as `\|`, and contain no box-drawing characters. Prettier formats every saved table with prose wrapping preserved.
- The prompt derives every chord from `SEND_STRING` or `tap_code` in `macros.c`, checks the consuming Niri, Kitty, or Emacs config before stating an effect, and marks unverified effects explicitly. Disabled keys are `-`; thumb positions are `LT-1` to `RT-3`; held modifiers read like `Shift modifier (right hand)`. Simultaneous keys use `+`, while sequences use `, then `. Key contains the readable base key and Chord contains the full combination. Tap-hold keys read like `Super / A`; layer-tap thumbs read like `Backspace / Sym`. A graph may use a shorter plain-English label, with one footnote pointing to the full table value. The Base file ends with a Combos table built from `combos.c`.

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
- `macros.c` — macro definitions and app tags
- `combos.c` — combos
- `keycodes.h`, `layers.h` — home-row mods, layer-tap keys, layer names
- `.pi/prompts/layers.md` — pi prompt that renders this reference; saved output goes to `docs/`
- Niri side: `~/.dotfiles/niri/.config/niri/config.kdl` and `KEYBINDINGS.md`
