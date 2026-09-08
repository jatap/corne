---
description: Show or regenerate deterministic QMK layer references
argument-hint: '[layer-name] [--save]'
---

Show or regenerate the jatap crkbd layer reference requested by `${@:-all}`.

Valid layer names are `base`, `niri`, `nav`, `emacs`, `sym`, `num`, `apps`, and `extra`. Accept one layer name or `all`, with an optional `--save`. If the request is invalid, list the valid forms and stop.

Run every command from `keyboards/crkbd/keymaps/jatap/`.

## Required workflow

1. Read `docs/FORMAT.md`.
2. Without `--save`, run `python3 docs/tools/layer_tables.py generate --check <layer-or-all>` and do not modify any file.
3. With `--save`, run `python3 docs/tools/layer_tables.py generate --write <layer-or-all>`.
4. A generator exit status of `1` is `FAIL`. Stop and reproduce its complete failure output. Do not edit a source or document to bypass it.
5. A generator exit status of `2` is `REVIEW REQUIRED`. With `--save`, the deterministic write succeeded; without `--save`, nothing was written and the existing document may be stale. Preserve the complete review report for the final response.
6. After a successful write, run the normal source-aware check on every requested layer file. Never use `--no-source`.
7. Never run Prettier on a layer file.
8. Never edit `keymap_colemakdh.c`, `macros.c`, `combos.c`, `keycodes.h`, or any application configuration during this prompt.

`docs/tools/layer_tables.py` owns all generated content and layout. Firmware defines positions, keys and chords. The strict `@emacs`, `@niri`, and `@system` annotations in `macros.c` define macro `Does` cells. The prompt must not author, preserve, reinterpret, or repair a table cell.

## Response

For a read-only request that passes generation checking, print the requested existing layer document or documents.

For `--save`, report each file that the generator rewrote and its source-aware check result.

If the generator printed `REVIEW REQUIRED`, copy every line from `REVIEW REQUIRED (...)` through `--- END REVIEW REPORT ---` into one fenced block after the file results. The count line and both boundary markers are mandatory. Do not omit, summarise, relabel or independently interpret any line.

Finish with a concise `## Pass Log` containing no more than three passes. A deterministic generator failure is the final pass unless the user changes its authoritative input.
