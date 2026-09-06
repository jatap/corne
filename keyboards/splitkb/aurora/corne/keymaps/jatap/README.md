# Jatap's SplitKB Aurora Corne keymap

SplitKB Aurora Corne rev1 keymap for a Liatris controller. The source of truth is the keymap code in this directory.

## Build and clangd database

For a normal firmware build, run only this command from the repo root:

```sh
PATH="$PWD/.venv/bin:$PATH" make splitkb/aurora/corne/rev1:jatap
```

Regenerate the clangd database only when it is missing, after switching from another board, after changing build flags in `rules.mk` or `info.json`, or after updating QMK or the toolchain:

```sh
.venv/bin/qmk generate-compilation-database -kb splitkb/aurora/corne/rev1 -km jatap
PATH="$PWD/.venv/bin:$PATH" make splitkb/aurora/corne/rev1:jatap
```

`generate-compilation-database` rewrites the repo-level `compile_commands.json` and runs `make clean`, so always run the real build afterwards. Clangd reads one database for the whole repo; after returning to the crkbd keymap, regenerate the crkbd database before trusting LSP diagnostics there.

## Hardware notes

- `rules.mk` sets `CONVERT_TO = liatris`, which converts the Elite-C footprint to the Liatris RP2040 controller.
- The build output is `splitkb_aurora_corne_rev1_jatap_liatris.uf2`.
- Do not flash hardware unless you intend to write firmware to the board.

## Files

- `keymap.c`, `keymap_colemakdh.c` — layer layouts
- `macros.c`, `macros.h` — macro definitions
- `combos.c`, `combos.h` — combos
- `config.h`, `rules.mk` — keymap build and behaviour settings
- `keycodes.h`, `layers.h` — custom keycodes and layer names
