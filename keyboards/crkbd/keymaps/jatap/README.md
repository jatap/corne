# Jatap's Corne keymap — layer reference

Crkbd (36-key, 3×5+3) with Colemak-DH. This document is a reading reference: what each layer has, and which app or system consumes each key. The source of truth is the keymap code (see [Files](#files)).

## How to read

- Grids show the physical layout. Each row is left hand (5 keys), right hand (5 keys). The last line of each grid is the thumb row, in physical left-to-right order.
- `Hypr` = Super+Alt+Ctrl+Shift. `Meh` = Alt+Ctrl+Shift. In the Niri config these are Tier 1 (primary operations) and Tier 2 (utilities).
- `M##` = QMK macro; look it up in the table under that layer.
- Modifiers: ⌘ Super, ⌥ Alt, ⌃ Ctrl, ⇧ Shift.
- Home-row keys and base thumbs are tap-hold: tap gives the printed key, hold gives the printed modifier or layer.
- `—` means a disabled key (no-op), not a transparent key.
- "Acts on" says what receives the chord: `Niri` (window manager), `Emacs`, `Neovim`, `System` (OS-level, XKB compose), or `App` (the focused application).

## Base (Colemak-DH)

```
 Q       W       F       P       B         J       L       U       Y       '
 A ⌘     R ⌥     S ⌃     T ⇧     G         M       N ⇧     E ⌃     I ⌥     O ⌘
 Z       X       C       D       V         K       H       ,       .       /

                 Tab     Esc     Space     Bksp    Enter   Del
                 Media   Nav     Vim       Sym     Num     Apps
```

- Home row: hold = modifier (A ⌘, R ⌥, S ⌃, T ⇧ / N ⇧, E ⌃, I ⌥, O ⌘), tap = letter.
- Thumbs: tap = top key, hold = bottom layer.

## Media (hold left thumb 1)

```
 HyprC   HyprEsc HyprDel —       —         HyprF   Hypr7   HyprA   HyprT   HyprS
 ⌘       ⌥       ⌃       ⇧       —         M30     M29     M28     HyprBsp HyprW
 —       MehZ    MehV    —       —         M31     Hypr8   Hypr4   HyprX   HyprE

                                   HyprU   HyprD   Extra
```

| Key     | Acts on | Function                             |
| ------- | ------- | ------------------------------------ |
| HyprC   | Niri    | Config reload notification           |
| HyprEsc | Niri    | Launch Waybar                        |
| HyprDel | Niri    | Quit Niri                            |
| HyprF   | Niri    | Maximise window to edges             |
| Hypr7   | Niri    | Consume or expel window left         |
| HyprA   | Niri    | Focus first column                   |
| HyprT   | Niri    | Centre column                        |
| HyprS   | Niri    | Toggle column tabbed display         |
| HyprBsp | Niri    | Toggle floating + 28% width + centre |
| HyprW   | Niri    | Consume window into column (group)   |
| Hypr8   | Niri    | Consume or expel window right        |
| Hypr4   | Niri    | Focus last column                    |
| HyprX   | Niri    | Switch focus floating/tiling         |
| HyprE   | Niri    | Expel window from column (ungroup)   |
| HyprU   | Niri    | Helper script menu                   |
| HyprD   | Niri    | Toggle fuzzel launcher               |
| MehZ    | Niri    | Woomer spotlight                     |
| MehV    | Niri    | Voxtype voice input toggle           |
| Extra   | —       | Hold for Extra layer                 |

| Macro | Sends          | Acts on | Function              |
| ----- | -------------- | ------- | --------------------- |
| M30   | `Super+Ctrl+1` | Niri    | Set column width 16%  |
| M28   | `Super+Ctrl+2` | Niri    | Set column width 28%  |
| M29   | `Super+Ctrl+4` | Niri    | Set column width 44%  |
| M31   | `Super+Ctrl+8` | Niri    | Set column width 100% |

## Nav (hold left thumb 2)

```
 —       —       —       —       —         Caps    ⌘Z      ↑       ⌘C      ⌘X
 ⌘       ⌥       ⌃       ⇧       —         CapWrd  ←       ↓       →       ⌘V
 —       —       —       —       —         Home    PgUp    PgDn    End

                                   Bksp    Apps    Del
```

- `CapWrd` toggles Caps Word.
- The Apps thumb is hold-only (no tap key on this layer).
- `⌘Z`, `⌘C`, `⌘X`, `⌘V` act on the focused application.

## Vim (hold left thumb 3)

```
 —       —       —       —       —         M17     M18     M19     M4      M20
 ⌘       ⌥       ⌃       ⇧       —         M14     M15     M16     M5     M21
 —       —       —       —       —         M13     M1      M2      M6     M22

                                   M0      M3      M12
```

| Macro | Sends            | Acts on      | Function                                      |
| ----- | ---------------- | ------------ | --------------------------------------------- |
| M17   | `M-s l`          | Emacs+Neovim | Occur (search in current buffer)              |
| M18   | `C-x C-j`        | Emacs+Neovim | Dired-jump (open dired at current buffer)     |
| M19   | `C-c c`          | Emacs+Neovim | Comment line or region                        |
| M4    | `C-c g s`        | Emacs+Neovim | Magit status (git status)                     |
| M20   | `M-%`            | Emacs/Neovim | query-replace / git UI (lazygit)              |
| M14   | `Super+Enter`, b | Emacs+Neovim | Activities: switch buffer of current activity |
| M15   | `M-{`            | Emacs+Neovim | Backward paragraph                            |
| M16   | `M-}`            | Emacs+Neovim | Forward paragraph                             |
| M5    | `C-c g l`        | Emacs+Neovim | Magit log current                             |
| M21   | `C-x o`          | Emacs+Neovim | Other window                                  |
| M13   | `C-x p f`        | Emacs+Neovim | Project find file                             |
| M1    | `C-x b`          | Emacs/Neovim | switch-to-buffer / previous buffer            |
| M2    | `C-c b @`        | Neovim       | Next buffer (unbound in Emacs)                |
| M6    | `C-c g i`        | Emacs+Neovim | Magit log for current file                    |
| M22   | `C-c t d`        | Emacs+Neovim | New vterm session                             |
| M0    | `C-x p ,`        | Emacs+Neovim | Project find regexp                           |
| M3    | `C-c b d`        | Emacs+Neovim | Delete window                                 |
| M12   | `C-x p .`        | Emacs+Neovim | Project find regexp at point                  |

## Sym (hold right thumb 1)

```
 {       &       *       (       }         —       —       —       —       —
 :       $       %       ^       +         —       ⇧       ⌃       ⌥       ⌘
 ~       !       @       #       |         —       M26     M27     —       —

 (       )       _
```

| Macro | Sends         | Acts on | Function                   |
| ----- | ------------- | ------- | -------------------------- |
| M26   | Compose `-` l | System  | Pound sign £ (XKB compose) |
| M27   | Compose `=` e | System  | Euro sign € (XKB compose)  |

Compose uses the `compose:caps` XKB option: the macro taps Caps Lock, which Niri maps to Compose.

## Num (hold right thumb 2)

```
 [       7       8       9       ]         —       —       —       —       —
 ;       4       5       6       =         —       ⇧       ⌃       ⌥       ⌘
 `       1       2       3       \         A       OSHypr  OSMeh   —       —

 .       0       -
```

- `OSHypr` / `OSMeh`: one-shot (sticky) Hyper / Meh modifiers.

## Apps (hold right thumb 3)

```
 HyprQ   ⌃0      ⌃-      ⌃+      M23       —       M24     Hypr3   Hypr2   HyprRet
 —       MehI    MehB    MehS    M11       Hypr9   ⇧       ⌃       ⌥       ⌘
 HyprR   MehP    Hypr1   HyprN   M9       Hypr0   M25     —       Hypr5   Hypr6

 M8     M7     M10
```

| Key     | Acts on | Function                     |
| ------- | ------- | ---------------------------- |
| HyprQ   | Niri    | Close window                 |
| HyprR   | Niri    | Switch preset column width   |
| Hypr1   | Niri    | Screen record menu           |
| HyprN   | Niri    | Clipboard history (cliphist) |
| Hypr2   | Niri    | Floating terminal            |
| Hypr3   | Niri    | Floating big terminal        |
| Hypr5   | Niri    | Floating left terminal       |
| Hypr6   | Niri    | Floating right terminal      |
| Hypr9   | Niri    | Floating big left terminal   |
| Hypr0   | Niri    | Floating big right terminal  |
| HyprRet | Niri    | Spawn kitty terminal         |
| MehB    | Niri    | Bluetui (Bluetooth TUI)      |
| MehI    | Niri    | Rustnet (network monitor)    |
| MehS    | Niri    | Wiremix (audio mixer)        |
| MehP    | Niri    | Power menu (fuzzel)          |
| ⌃0      | App     | Reset zoom                   |
| ⌃-      | App     | Zoom out                     |
| ⌃+      | App     | Zoom in                      |

| Macro | Sends         | Acts on      | Function                                |
| ----- | ------------- | ------------ | --------------------------------------- |
| M23   | `C-x 3`       | Emacs+Neovim | Split window right                      |
| M11   | `C-x 2`       | Emacs+Neovim | Split window below                      |
| M9    | `C-x 1`       | Emacs+Neovim | Delete other windows                    |
| M24   | `C-u C-Spc`   | Emacs+Neovim | Move point to previous mark (mark ring) |
| M25   | `C-Spc C-Spc` | Emacs+Neovim | Set mark without activating             |
| M8    | `M-s M-.`     | Emacs        | Isearch thing at point                  |
| M7    | `M-s ,`       | Emacs        | Occur word at point                     |
| M10   | `M-s r`       | Emacs        | Replace regexp as diff                  |

## Extra (hold Media right thumb 3)

```
 F10     F9      F8      F7      F6        F5      F4      F3      F2      F1
 —       Prev    Vol-    Vol+    Next      —       ⇧       ⌃       ⌥       ⌘
 —       F12     F11     —       Boot      —       —       —       —       —

 Mute    Play    —
```

- Media keys act at system level (WirePlumber / brightnessctl).
- `Boot` resets the keyboard into bootloader mode.

## Combos (Base layer positions)

| Combo | Types          |
| ----- | -------------- |
| H + , | Tab            |
| , + . | `->`           |
| X + C | `=>`           |
| J + L | personal email |
| L + U | work email     |

- The old `U + L` `<?php` combo was removed: it shared both keys with `L + U`, so QMK could never tell them apart and `<?php` never fired.

## Behaviour notes

- Layer thumbs (Media, Nav, Sym, Num, Apps) are `LT()` keys with permissive hold enabled, so tapping one and rolling into another key inside the tapping term activates the layer. Two intentional toggles: `HOLD_ON_OTHER_KEY_PRESS_PER_KEY` stays commented out, so `get_hold_on_other_key_press()` in `keymap.c` is not compiled (uncomment the define to activate it); `TAPPING_FORCE_HOLD_PER_KEY` compiles `get_tapping_force_hold()`, but this QMK tree's core no longer calls it — the feature became `QUICK_TAP_TERM` (see `docs/ChangeLog/20230226.md` in the firmware tree).
- Tapping terms are shortened per key: home-row mods by 10-30 ms, layer thumbs by 30 ms (see `keymap.c`).
- Auto-shift is enabled for digits and symbols only (`NO_AUTO_SHIFT_ALPHA`, 175 ms timeout). Holding a letter does nothing special; holding `1` types `!`.
- One-shot Hyper and Meh live on the Num layer, with `ONESHOT_TIMEOUT 2000` and `ONESHOT_TAP_TOGGLE 5`.
- Macros tagged `@emacs` / `@neovim` / `@niri` are documented in `macros.c`.

## Files

- `keymap.c`, `keymap_colemakdh.c` — layer layouts
- `macros.c` — macro definitions and app tags
- `combos.c` — combos
- `keycodes.h`, `layers.h` — home-row mods, layer-tap keys, layer names
- Niri side: `~/.dotfiles/niri/.config/niri/config.kdl` and `KEYBINDINGS.md`
