# FORMAT.md — how these tables are built

This is the contract for every table in this directory. It exists because prose rules alone did not survive contact with different models: the same instructions produced different content and column widths. `tools/layer_tables.py` now generates source-owned cells and derives every column width, border and fence. Do not hand-align a table, and do not restate these rules somewhere else; a second copy is how the two drift apart.

`tools/layer_tables.py` is the executable form of this document. If the two disagree, fix both in the same commit. `PLAN.md` is the design record: what was measured, which numbers are load-bearing, and the five places the original plan turned out wrong.

## Usage

Run these from the keymap directory, the one that contains `docs/`:

```bash
python3 docs/tools/layer_tables.py generate --write base   # regenerate one layer atomically
python3 docs/tools/layer_tables.py generate --check all    # compare every generated document in memory
python3 docs/tools/layer_tables.py format docs/base.md      # repair layout without changing cell text
python3 docs/tools/layer_tables.py check docs/*.md          # verify layout and source-owned cells
python3 docs/tools/layer_tables.py verify-cells docs/new/base.md --against docs/old/base.md
python3 -m unittest discover -s docs/tools -p 'test_*.py'
```

`check` passing means `format` is a no-op and every recognised layer's `Key`, `Chord`, macro `Does` and graph cells match `keymap_colemakdh.c`, `keycodes.h` and `macros.c`. Use `check --no-source` only for isolated table fixtures that have no firmware source; it is not valid for a `/layers` run. `generate --check` additionally byte-compares complete generated documents, including combo rows and deterministic ordinary-key effects. It exits 2 when review items explain a difference and exits 1 for source drift without a review item.

## The fence is the format

Every table sits inside a fenced code block opened with ` ```text ` and closed with a bare ` ``` `. Nothing else goes inside the fence: the table's first border line is the first line and its last border line is the last.

This is not decoration. The fence is what makes each of these true at once:

- Prettier cannot reach the content, so no formatter can fold a border into a column. This is the reason the files are not plain GFM tables.
- `pi` and `glow` print the block verbatim instead of parsing it as a GFM table, which previously swallowed the bottom border as a data row and stretched a column to 64 characters.
- A cell can contain a literal backtick, backslash or pipe with no escaping, which a GFM table cannot do.
- Emacs with `markdown-fontify-code-blocks-natively` treats the block as fixed-pitch code.

The trade-off is accepted deliberately: GitHub renders these files as code blocks, not as HTML tables. They are read in `cat`, Emacs and a terminal, where byte-exact layout matters more than clickable HTML.

## File anatomy

Per layer file, in this order: `# <LayerName>` heading, blank line, fenced key table, blank line, fenced graph table, blank line, then footnotes if any, each separated by a blank line. `base.md` additionally includes `Home-row keys tap the letter, hold the mod.`, followed by `Combos (Base layer positions):`, a blank line and its fenced combos table. No trailing whitespace, no tabs, ASCII only inside table fences, and exactly one newline at end of file.

## Key table and combos table

Five kinds of line: top border, header, border, data rows, bottom border. Header cells are `Position`, `Key`, `Chord`, `Does` for a key table and `Keys`, `Chord`, `Does` for the combos table. There is no `| --- |` separator row; the line under the header is a border, exactly like the ones above and below.

Row order follows the physical board, not the row labels: left half column by column (`L1-1`, `L2-1`, `L3-1`, `L1-2`, and so on), then the right half the same way with `R` prefixes, then `LT-1` to `LT-3`, then `RT-1` to `RT-3`.

## Graph table

Line kinds: border, header, border, `L1`, `L2`, `L3`, border, `THUMBS`, border. The interior border above `THUMBS` is required, because the thumbs are physically separated from the key rows. The label is `THUMBS`, never `THUMB`.

Header cells are `ROW`, then `1` to `5`, then one dead gap column, then `1` to `5`. The gap column exists to hold the physical space between the two halves of the board. It is empty in every row and always 5 columns wide regardless of what the content would need; a content-derived width collapses it to 3 and flattens the drawing.

## Width rules

- Column width is 2 plus the longest cell content in that column, measured over the header and every data row. One space of padding on each side is part of that 2.
- The graph gap column is the constant 5, exempt from the rule above.
- Every line of one table, borders included, has exactly the same length.
- No table line exceeds 140 columns. The number comes from the terminal these files are read in: about 153 usable columns, and `pi` indents a fence by 2 while `glow` indents by 4, so 140 plus the worst renderer still fits.
- If generated content would exceed 140, shorten the `Does` wording. Do not shorten the header names, do not wrap a cell across two lines, and do not raise the cap. `Does` is the only column with room to give.
- Borders are always derived from column widths, never typed.

## Cell vocabulary

- A command chord keeps its modifiers in `Key`, `Chord` and the graph. For example, `LCTL(KC_0)` is `Ctrl+0` in all three places. A shortened graph label may omit `Numpad` but never the modifier: `Ctrl+Numpad Minus` becomes `Ctrl+Minus`.
- `HYPR(kc)` in the C source is written `HYPR+<Key>`, and `MEH(kc)` is written `MEH+<Key>`. The expanded forms `Ctrl+Alt+Shift+Super+<key>` and `Ctrl+Alt+Shift+<key>` are prohibited; `HYPR` and `MEH` are defined in the parent `README.md` and are firmware vocabulary, not invented notation.
- Simultaneous keys use `+`, sequences use `, then `, and modifiers are spelled `Ctrl`, `Alt`, `Shift`, `Super`.
- For a pure modifier, `Key` uses the modifier name, such as `Super`, while `Chord` includes the side, such as `Left Super` or `Right Shift`.
- `-` in `Key` means a disabled key. A QMK-internal action keeps a readable key name such as `Extra` for `MO()` or `Boot` for `QK_BOOT`, while its `Chord` is `-`.
- Tap-hold keys read `Super / A`; layer-tap thumbs read `Backspace / Sym`.
- Key names stay readable: `Escape`, `Backspace`, `Page Up`, `Numpad Plus`, `Numpad Minus`.
- A backtick, backslash and pipe are written as literal characters in `Key`, `Chord` and graph cells. The words `Backtick`, `Backslash` and `Pipe` are prohibited there, and so is the escaped pipe, which a fence makes unnecessary.
- In `Does` prose a character is named in lower case instead: `Types backtick`, `Types backslash`, `Types pipe`. A lone backtick at the end of a sentence is easy to miss.
- Name the consumer (`Niri:`, `Emacs:`, `Kitty:`) in `Does` only when the file mixes consumers, which `apps.md` does. In a single-consumer layer file the prefix repeats the heading on all rows and is left out.
- A macro `Does` value is copied exactly from its one-line `@emacs`, `@niri` or `@system` annotation in `macros.c`. The Apps layer adds the annotation target as a prefix because it mixes consumers. If a direct application shortcut has no existing human-reviewed claim, generation writes `Review required` and reports the position; it never invents an effect.

## Footnotes

Both footnotes are conditional, and their condition is computed from the finished tables rather than remembered from an earlier draft.

- Emit `Graph uses short key names; the table lists the full key or chord.` only if at least one graph cell is shorter than the `Key` value at the same position in the table. Once every graph cell matches the table, the sentence is false and must be deleted.
- Emit `Thumb keys show the hold layer; tap sends the key listed in the table.` only if at least one graph thumb cell shows the hold layer where the table shows a tap-hold pair.

## Prohibited

- Box-drawing characters anywhere in these files, and any non-ASCII character inside a table fence. Outside a fence, prose may use an em dash; a wide character in a cell silently breaks column alignment, which is why the rule is scoped that way.
- A table line outside a fence, and prose inside a table fence.
- Prettier, or any other formatter, on a layer file (`base.md`, `niri.md`, `nav.md`, `emacs.md`, `sym.md`, `num.md`, `apps.md`, `extra.md`). The fence makes a stray run harmless, but the script derives widths and a formatter does not. `FORMAT.md`, `PLAN.md` and `README.md` are ordinary Markdown and follow the repository's Prettier rule.
- Hand-edited padding, borders or column widths: run `format`.
- Raising the 140-column cap, wrapping a cell across lines, or shortening a header name to buy width. Shorten `Does` wording instead.
