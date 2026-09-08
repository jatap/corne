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

- Layer docs in `docs/` follow `docs/FORMAT.md`; `docs/PLAN.md` records why that contract exists. Regenerate with `python3 docs/tools/layer_tables.py generate --write <layer>` and verify with `generate --check <layer>` plus the normal source-aware `check`. Use `format` only to repair layout, never hand-align a table, and never run Prettier on a layer file. The normal `check` compares `Key`, `Chord`, macro `Does` and graph cells with `keymap_colemakdh.c`, `keycodes.h` and `macros.c`; `--no-source` is only for isolated fixtures. After changing the checker, run `python3 -m unittest discover -s docs/tools -p 'test_*.py'`. `FORMAT.md`, `PLAN.md` and `README.md` are ordinary Markdown and follow the repo's Prettier rule.
- A source change that alters what a key does or sends must update `docs/<layer>.md` in the same commit. Run `/layers <layer> --save` or the generator directly, then finish with `generate --check` and the source-aware `check`. A direct application claim without a source annotation may be corrected in its layer document; generated cells must be corrected at their authoritative source.
- Key placement belongs in `keymap_colemakdh.c`; `keymap.c` only assembles layers and holds tap-hold behavior.
- Append new `QMK_M*` entries at the end of `macros.h`, then add the matching `macros.c` case with one-line `@emacs`, `@niri` or `@system` annotations. The annotation payload is the authoritative macro `Does` text. Regenerate the affected layer instead of editing its macro row.
- Append combos before `COMBO_LENGTH` in `combos.h`, then update `combos.c` and the combo table in `docs/base.md`.
- Keep `// clang-format off/on` blocks and manual alignment around layer grids.
- Do not remove annotated placeholders in `config.h` as dead code.
- Personal email expansions in `combos.c` are intentional, not secrets.
