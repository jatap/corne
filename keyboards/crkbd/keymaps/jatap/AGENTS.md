# AGENTS.md — jatap keymap

## Scope and precedence

These rules apply to `keyboards/crkbd/keymaps/jatap/`. Order of authority: explicit user instructions, then this file, then `README.md`. `README.md` is the human reference; code is the source of truth. When code and README disagree, code wins and README must be corrected in the same commit.

## Build and validation

- The `qmk` CLI lives in the uv-managed `.venv` at the qmk_firmware repo root. Use `PATH="$PWD/.venv/bin:$PATH" make crkbd:jatap` from the repo root.
- A clean build is required before claiming any code change here is done. Report real command output.
- Never flash (`make crkbd:jatap:flash` or `qmk flash`) without explicit user confirmation.

## Compile model

- `keymap.c` is the compiled entry point. Other `.c` files in this directory are reached through includes, not auto-compiled.
- Include chain: `keymap.c` → `keymap_colemakdh.c` → `macros.c` and `combos.c`.
- New `.c` code must be included in that chain or listed via `SRC +=` in `rules.mk`, never both.

## Editing rules

- Key placement belongs in `keymap_colemakdh.c`; `keymap.c` only assembles layers and holds tap-hold behavior.
- Append new `QMK_M*` entries at the end of `macros.h`, then add the matching `macros.c` case and README table entry.
- Append combos before `COMBO_LENGTH` in `combos.h`, then update `combos.c` and README.
- Keep `// clang-format off/on` blocks and manual alignment around layer grids.
- Do not remove annotated placeholders in `config.h` as dead code.
- Personal email expansions in `combos.c` are intentional, not secrets.
