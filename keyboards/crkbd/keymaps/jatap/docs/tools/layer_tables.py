#!/usr/bin/env python3
"""Format and verify the ASCII layer tables in this docs directory.

The models that generate these tables emit cell text; this script owns every
column width, border and fence. That division is deliberate: prose rules did
not produce stable tables across different models, a checker does.

Subcommands
    check FILE...        verify layout and generated source-owned cells
    format FILE...       rewrite tables in place (layout only, never cell text)
    generate --write LAYER|all          atomically regenerate layer documents
    generate --check [LAYER|all]        compare generated documents in memory
    verify-cells FILE --against OTHER   prove a format run changed no content

`check` reads keymap_colemakdh.c, keycodes.h and macros.c beside docs/ by
default. Use `--no-source` only for isolated fixtures without firmware sources.

The contract itself lives in ../FORMAT.md; ../PLAN.md records why it took this
shape. This script is the contract's executable form; when the two disagree,
fix both in the same commit.
"""

from __future__ import annotations

import argparse
import ast
import os
import re
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

CAP = 140  # hard maximum table line length, see FORMAT.md "Width rules"
GAP_WIDTH = 5  # the graph table's fixed dead column between the two halves
GAP_COLUMN = 6  # its zero-based index in a graph row
FOOTNOTE_SHORT = "Graph uses short key names; the table lists the full key or chord."
FOOTNOTE_THUMB = "Thumb keys show the hold layer; tap sends the key listed in the table."

COLUMNS = {
    "key": ["Position", "Key", "Chord", "Does"],
    "combos": ["Keys", "Chord", "Does"],
    "graph": ["ROW"] + [str(i) for i in (1, 2, 3, 4, 5)] + ["gap"] + [str(i) for i in (1, 2, 3, 4, 5)],
}
CHAR_WORDS = ("Backtick", "Backslash", "Pipe")  # only legal, lowercase, inside `Does`
BANNED = [
    (re.compile(r"Ctrl\+Alt\+Shift\+Super"), "expanded HYPR chord, write HYPR+<Key>"),
    (re.compile(r"Ctrl\+Alt\+Shift+(?=[A-Za-z0-9])"), "expanded MEH chord, write MEH+<Key>"),
]
LAYERS = {"base", "niri", "nav", "emacs", "sym", "num", "apps", "extra"}
KEY_NAMES = {
    "BSPC": "Backspace",
    "BSLS": "\\",
    "CAPS": "Caps Lock",
    "COMMA": "Comma",
    "DEL": "Delete",
    "DOT": "Period",
    "DOWN": "Down",
    "END": "End",
    "ENT": "Enter",
    "EQL": "Equal",
    "ESC": "Escape",
    "GRAVE": "`",
    "HOME": "Home",
    "KP_MINUS": "Numpad Minus",
    "KP_PLUS": "Numpad Plus",
    "LALT": "Alt",
    "LCTL": "Ctrl",
    "LEFT": "Left",
    "LGUI": "Super",
    "LSFT": "Shift",
    "LBRC": "Left Bracket",
    "MINS": "Minus",
    "MNXT": "Next Track",
    "MPLY": "Play / Pause",
    "MPRV": "Previous Track",
    "MUTE": "Mute",
    "PGDN": "Page Down",
    "PGUP": "Page Up",
    "QUOT": "Apostrophe",
    "RALT": "Alt",
    "RBRC": "Right Bracket",
    "RCTL": "Ctrl",
    "RGUI": "Super",
    "RIGHT": "Right",
    "RSFT": "Shift",
    "SCLN": "Semicolon",
    "SLSH": "Slash",
    "SPC": "Space",
    "TAB": "Tab",
    "UP": "Up",
    "VOLD": "Volume Down",
    "VOLU": "Volume Up",
}
SHIFTED_NAMES = {
    "0": ")",
    "1": "!",
    "2": "@",
    "3": "#",
    "4": "$",
    "5": "%",
    "6": "^",
    "7": "&",
    "8": "*",
    "9": "(",
    "BSLS": "|",
    "GRAVE": "~",
    "LBRC": "{",
    "MINS": "_",
    "RBRC": "}",
    "SCLN": ":",
}
GRAPH_NAMES = {
    "Apostrophe": "'",
    "Comma": ",",
    "Equal": "=",
    "Left Bracket": "[",
    "Minus": "-",
    "Next Track": "Next",
    "Numpad Minus": "Minus",
    "Numpad Plus": "Plus",
    "Period": ".",
    "Play / Pause": "Play",
    "Previous Track": "Previous",
    "Right Bracket": "]",
    "Semicolon": ";",
    "Slash": "/",
    "Volume Down": "Volume -",
    "Volume Up": "Volume +",
}


class Bad(Exception):
    """A source or layout problem that makes generation unsafe."""


@dataclass(frozen=True)
class KeyEvent:
    modifiers: tuple[str, ...]
    key: str

    def render(self) -> str:
        return "+".join((*self.modifiers, self.key))


@dataclass(frozen=True)
class Macro:
    name: str
    annotations: dict[str, str]
    events: tuple[KeyEvent, ...]
    line: int

    @property
    def chord(self) -> str:
        return ", then ".join(event.render() for event in self.events)


@dataclass(frozen=True)
class ReviewItem:
    layer: str
    position: str
    macro: str
    source: str
    qmk: str
    previous: str
    generated: str
    reason: str


# --------------------------------------------------------------------------
# geometry: fences, table blocks, column boundaries
# --------------------------------------------------------------------------


def is_table_line(line: str) -> bool:
    return line.startswith(("|", "+"))


def fence_spans(lines: list[str]) -> list[tuple[int, int]]:
    """(open, close) index pairs of ``` fences, both inclusive."""
    spans, start = [], None
    for i, line in enumerate(lines):
        if line.startswith("```"):
            if start is None:
                start = i
            elif i == start + 1:
                raise Bad(f"line {start + 1}: empty code fence")
            else:
                spans.append((start, i))
                start = None
    if start is not None:
        raise Bad(f"line {start + 1}: unclosed code fence")
    return spans


def in_fence(spans: list[tuple[int, int]], i: int) -> bool:
    return any(a < i < b for a, b in spans)


def table_blocks(lines: list[str]) -> list[tuple[int, int]]:
    """Maximal runs of consecutive table lines, as (start, end) inclusive."""
    blocks, start = [], None
    for i, line in enumerate(lines):
        if is_table_line(line):
            if start is None:
                start = i
        elif start is not None:
            blocks.append((start, i - 1))
            start = None
    if start is not None:
        blocks.append((start, len(lines) - 1))
    return blocks


# --------------------------------------------------------------------------
# one parsed table
# --------------------------------------------------------------------------


class Table:
    """Cell text plus provenance. Padding is derived on output, never stored."""

    def __init__(self, kind, rows, shape, line, src_widths=None):
        self.kind = kind  # key | combos | graph
        self.rows = rows  # list of cell-text lists, first is the header
        self.shape = shape  # one char per source line: B border, R row, S separator
        self.line = line  # 1-based source line of the block's first line
        self.src_widths = src_widths  # column widths as actually written, or None

    @property
    def ncols(self) -> int:
        return len(self.rows[0])

    def widths(self) -> list[int]:
        w = [max(len(r[c]) for r in self.rows) + 2 for c in range(self.ncols)]
        if self.kind == "graph":
            w[GAP_COLUMN] = GAP_WIDTH
        return w

    def render(self) -> list[str]:
        w = self.widths()
        bar = "+" + "+".join("-" * x for x in w) + "+"
        line = lambda cells: "|" + "|".join(" " + c.ljust(x - 2) + " " for c, x in zip(cells, w)) + "|"
        head, body = line(self.rows[0]), [line(r) for r in self.rows[1:]]
        if self.kind == "graph":
            return [bar, head, bar, *body[:3], bar, *body[3:], bar]
        return [bar, head, bar, *body, bar]


def kind_of(header: list[str]) -> str:
    for name, kind in (("ROW", "graph"), ("Position", "key"), ("Keys", "combos")):
        if header[0] == name:
            return kind
    raise Bad(f"unknown table header {header[0]!r}; expected Position, ROW or Keys")


def slice_cells(line: str, bounds: list[int], lineno: int) -> list[str]:
    """Cut a row at the border offsets.

    Deliberately not `split('|')`: a cell may contain a literal pipe, and
    splitting on pipes would silently invent columns.
    """
    if len(line) != bounds[-1] + 1:
        # `format` must be able to repair a hand-edited final Does cell whose
        # content no longer fits the old border. Earlier boundaries remain
        # authoritative because those cells may contain literal pipes.
        if not line.endswith("|") or any(line[offset] != "|" for offset in bounds[:-1]):
            raise Bad(f"line {lineno}: row is {len(line)} wide, the table border is {bounds[-1] + 1}")
        bounds = [*bounds[:-1], len(line) - 1]
    cells = []
    for lo, hi in zip(bounds, bounds[1:]):
        if line[lo] != "|":
            raise Bad(f"line {lineno}: expected `|` at column {lo + 1}, found {line[lo]!r}")
        field = line[lo + 1 : hi]
        if field.strip() and not (field.startswith(" ") and field.endswith(" ")):
            raise Bad(f"line {lineno}: the cell at column {lo + 1} lacks one space of padding")
        cells.append(field.strip())
    return cells


def is_separator(cells: list[str]) -> bool:
    """True for a `| --- | --- |` row: every populated column is pure dashes.

    Safe because the first column of every table here is a label (`Position`,
    `ROW`, `Keys`), so a real data row can never look like this.
    """
    got = [c for c in cells if c]
    return bool(got) and all(re.fullmatch(r"-+", c) for c in got)


def split_bare_row(line: str) -> list[str]:
    r"""Fallback split for a borderless GFM table, honouring the `\|` escape.

    Only used when a block has no border line at all, which means it cannot
    contain an unescaped literal pipe: that form is legal solely inside a table
    this script has already laid out.
    """
    parts, cur, i = [], "", 0
    while i < len(line):
        ch = line[i]
        if ch == "\\" and i + 1 < len(line) and line[i + 1] == "|":
            cur += "|"
            i += 2
            continue
        if ch == "|":
            parts.append(cur)
            cur = ""
            i += 1
            continue
        cur += ch
        i += 1
    if cur.strip() or not cur:
        parts.append(cur)
    if parts and not parts[0].strip():
        parts = parts[1:]
    if parts and not parts[-1].strip():
        parts = parts[:-1]
    return [p.strip() for p in parts]


def parse_block(lines: list[str], start: int, end: int) -> Table:
    block = lines[start : end + 1]
    borders = [b for b in block if b.startswith("+")]
    shape, rows = "", []
    if not borders:
        # A model that ignored the border rule still gets repaired, not rejected.
        synthetic = True
    else:
        synthetic = False
        bounds = [i for i, ch in enumerate(borders[0]) if ch == "+"]
        if len(bounds) < 3:
            raise Bad(f"line {start + 1}: the border defines fewer than two columns")
    for offset, raw in enumerate(block):
        lineno = start + offset + 1
        if raw.startswith("+"):
            shape += "B"
            continue
        if raw.startswith("```"):
            raise Bad(f"line {lineno}: fence marker inside a table block")
        cells = split_bare_row(raw) if synthetic else slice_cells(raw, bounds, lineno)
        if is_separator(cells):
            shape += "S"  # a separator carries no content; it becomes a border
            continue
        shape += "R"
        if not rows:
            rows.append(cells)
        elif len(cells) != len(rows[0]):
            raise Bad(f"line {lineno}: row has {len(cells)} cells, the header has {len(rows[0])}")
        else:
            rows.append(cells)
    if not rows:
        raise Bad(f"line {start + 1}: table block has no header row")
    src = None
    if not synthetic:
        src = [hi - lo - 1 for lo, hi in zip(bounds, bounds[1:])]
    return Table(kind_of(rows[0]), rows, shape, start + 1, src)


def parse_tables(text: str) -> tuple[list[Table], list[str]]:
    """Parse every table, collecting problems instead of aborting on the first."""
    lines = text.split("\n")
    try:
        spans = fence_spans(lines)
    except Bad as exc:
        return [], [str(exc)]
    tables, errors = [], []
    for start, end in table_blocks(lines):
        if not in_fence(spans, start):
            errors.append(f"line {start + 1}: table is not inside a ```text fence")
            continue
        try:
            tables.append(parse_block(lines, start, end))
        except Bad as exc:
            errors.append(str(exc))
    return tables, errors


# --------------------------------------------------------------------------
# firmware macro metadata and emitted events
# --------------------------------------------------------------------------


ANNOTATION_TARGETS = {"emacs", "niri", "system"}
SEND_KEY_ALIASES = {"COMM": "COMMA", "ENTER": "ENT", "SPACE": "SPC"}
SEND_MODIFIERS = {
    "SS_LCTL": "Ctrl",
    "SS_LALT": "Alt",
    "SS_LSFT": "Shift",
    "SS_LGUI": "Super",
    "SS_RCTL": "Ctrl",
    "SS_RALT": "Alt",
    "SS_RSFT": "Shift",
    "SS_RGUI": "Super",
}
ASCII_KEYS = {
    " ": ("Space", False),
    "!": ("1", True),
    '"': ("Apostrophe", True),
    "#": ("3", True),
    "$": ("4", True),
    "%": ("5", True),
    "&": ("7", True),
    "'": ("Apostrophe", False),
    "(": ("9", True),
    ")": ("0", True),
    "*": ("8", True),
    "+": ("Equal", True),
    ",": ("Comma", False),
    "-": ("Minus", False),
    ".": ("Period", False),
    "/": ("Slash", False),
    ":": ("Semicolon", True),
    ";": ("Semicolon", False),
    "<": ("Comma", True),
    "=": ("Equal", False),
    ">": ("Period", True),
    "?": ("Slash", True),
    "@": ("2", True),
    "[": ("Left Bracket", False),
    "\\": ("\\", False),
    "]": ("Right Bracket", False),
    "^": ("6", True),
    "_": ("Minus", True),
    "`": ("`", False),
    "{": ("Left Bracket", True),
    "|": ("\\", True),
    "}": ("Right Bracket", True),
    "~": ("`", True),
}


def ascii_event(char: str) -> KeyEvent:
    """Decode one SEND_STRING character using this checkout's US QMK LUT."""
    if "a" <= char <= "z":
        return KeyEvent((), char.upper())
    if "A" <= char <= "Z":
        return KeyEvent(("Shift",), char)
    if "0" <= char <= "9":
        return KeyEvent((), char)
    if char in ASCII_KEYS:
        key, shifted = ASCII_KEYS[char]
        return KeyEvent(("Shift",) if shifted else (), key)
    raise Bad(f"unsupported SEND_STRING character {char!r}")


def add_modifier(events: list[KeyEvent], modifier: str) -> list[KeyEvent]:
    return [KeyEvent((modifier, *event.modifiers) if modifier not in event.modifiers else event.modifiers, event.key) for event in events]


def balanced_argument(text: str, opening: int) -> tuple[str, int]:
    """Return text inside one parenthesised call and the offset after `)`."""
    depth, quote, escaped = 0, None, False
    for i in range(opening, len(text)):
        char = text[i]
        if quote:
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif char == quote:
                quote = None
            continue
        if char in "\"'":
            quote = char
        elif char == "(":
            depth += 1
        elif char == ")":
            depth -= 1
            if depth == 0:
                return text[opening + 1 : i], i + 1
    raise Bad("unclosed function call in macro expression")


def parse_send_expression(expression: str) -> list[KeyEvent]:
    """Parse the narrow SEND_STRING expression language used by this keymap."""
    out: list[KeyEvent] = []
    i = 0
    while i < len(expression):
        if expression[i].isspace():
            i += 1
            continue
        if expression[i] == '"':
            end, escaped = i + 1, False
            while end < len(expression):
                if escaped:
                    escaped = False
                elif expression[end] == "\\":
                    escaped = True
                elif expression[end] == '"':
                    break
                end += 1
            if end == len(expression):
                raise Bad("unclosed string literal in SEND_STRING")
            try:
                value = ast.literal_eval(expression[i : end + 1])
            except (SyntaxError, ValueError) as exc:
                raise Bad(f"invalid string literal in SEND_STRING: {exc}") from exc
            out.extend(ascii_event(char) for char in value)
            i = end + 1
            continue
        match = re.match(r"[A-Z][A-Z0-9_]*", expression[i:])
        if not match:
            raise Bad(f"unsupported SEND_STRING syntax near {expression[i:]!r}")
        name = match.group(0)
        opening = i + len(name)
        while opening < len(expression) and expression[opening].isspace():
            opening += 1
        if opening >= len(expression) or expression[opening] != "(":
            raise Bad(f"expected `(` after {name}")
        argument, i = balanced_argument(expression, opening)
        if name == "SS_TAP":
            raw = argument.strip()
            if not (match := re.fullmatch(r"X_(\w+)", raw)):
                raise Bad(f"unsupported SS_TAP argument {raw!r}")
            code = SEND_KEY_ALIASES.get(match.group(1), match.group(1))
            out.append(KeyEvent((), key_name(code)))
        elif name in SEND_MODIFIERS:
            out.extend(add_modifier(parse_send_expression(argument), SEND_MODIFIERS[name]))
        else:
            raise Bad(f"unsupported SEND_STRING helper {name}")
    return out


def call_argument(text: str, name: str) -> str | None:
    found = re.search(rf"\b{re.escape(name)}\s*\(", text)
    if not found:
        return None
    opening = text.find("(", found.start())
    argument, _end = balanced_argument(text, opening)
    return argument


def macro_events(body: str) -> tuple[KeyEvent, ...]:
    expression = call_argument(body, "SEND_STRING")
    taps = re.findall(r"\btap_code(?:16)?\s*\(\s*KC_(\w+)\s*\)\s*;", body)
    if expression is not None and taps:
        raise Bad("mixed SEND_STRING and tap_code calls are unsupported")
    if expression is not None:
        return tuple(parse_send_expression(expression))
    if taps:
        return tuple(KeyEvent((), key_name(code)) for code in taps)
    raise Bad("no supported SEND_STRING or tap_code output")


def parse_macros(text: str) -> tuple[dict[str, Macro], list[str]]:
    """Parse strict documentation annotations and output from every macro case."""
    case_names = re.findall(r"^\s*case\s+(QMK_M\d+)\s*:", text, re.M)
    pattern = re.compile(
        r"(?P<comment>/\*\*(?:(?!/\*\*).)*?\*/)\s*"
        r"case\s+(?P<name>QMK_M\d+)\s*:(?P<body>.*?^\s*break;\s*$)",
        re.S | re.M,
    )
    macros: dict[str, Macro] = {}
    errors: list[str] = []
    matched: set[str] = set()
    for found in pattern.finditer(text):
        name, comment, body = found.group("name", "comment", "body")
        matched.add(name)
        line = text.count("\n", 0, found.start("comment")) + 1
        annotations: dict[str, str] = {}
        annotation_problem = False
        comment_body = comment[3:-2]
        for raw in comment_body.splitlines():
            annotation = raw.strip()
            if annotation.startswith("*"):
                annotation = annotation[1:].lstrip()
            if not annotation.startswith("@"):
                continue
            found_annotation = re.fullmatch(r"@(\w+)(?:[ \t]+(.*))?", annotation)
            if not found_annotation:
                errors.append(f"{name} line {line}: malformed annotation {annotation!r}")
                annotation_problem = True
                continue
            target, payload = found_annotation.groups()
            target = target.lower()
            payload = (payload or "").strip()
            if target not in ANNOTATION_TARGETS:
                errors.append(f"{name} line {line}: unknown @{target} annotation")
                annotation_problem = True
            elif not payload:
                errors.append(f"{name} line {line}: empty @{target} annotation")
                annotation_problem = True
            elif target in annotations:
                errors.append(f"{name} line {line}: duplicate @{target} annotation")
                annotation_problem = True
            else:
                annotations[target] = payload
        if not annotations and not annotation_problem:
            errors.append(f"{name} line {line}: missing @emacs, @niri or @system annotation")
        try:
            events = macro_events(body)
        except Bad as exc:
            errors.append(f"{name} line {line}: {exc}")
            continue
        macros[name] = Macro(name, annotations, events, line)
    for name in case_names:
        if name not in matched:
            errors.append(f"{name}: missing adjacent documentation comment or terminating break")
    return macros, errors


# --------------------------------------------------------------------------
# rules
# --------------------------------------------------------------------------


def check_shape(t: Table) -> list[str]:
    norm = t.shape.replace("S", "B")  # a separator is accepted, but reported below
    want = r"BRBRRRBRB" if t.kind == "graph" else r"BRBR+B"
    expected_header = ["" if name == "gap" else name for name in COLUMNS[t.kind]]
    bad = []
    if t.rows[0] != expected_header:
        bad.append(f"{t.line}: header is {t.rows[0]!r}, expected {expected_header!r}")
    if t.src_widths is None:
        bad.append(f"{t.line}: table has no border lines; run format")
    elif not re.fullmatch(want, norm):
        expect = "BRBRRRBRB (border, header, border, L1-L3, border, THUMBS, border)" if t.kind == "graph" else "BRBR+B (border, header, border, rows, border)"
        bad.append(f"{t.line}: table shape is {t.shape}, expected {expect}")
    if "S" in t.shape:
        bad.append(f"{t.line}: a `| --- |` separator row must be an ASCII border instead")
    if t.kind == "graph":
        labels = [r[0] for r in t.rows]
        if labels != ["ROW", "L1", "L2", "L3", "THUMBS"]:
            bad.append(f"{t.line}: graph row labels are {labels}, expected ROW, L1, L2, L3, THUMBS")
    return bad


def check_widths(t: Table) -> list[str]:
    w, total = t.widths(), sum(t.widths()) + t.ncols + 1
    bad = []
    if t.kind == "graph" and t.ncols != len(COLUMNS["graph"]):
        return [f"{t.line}: graph has {t.ncols} columns, expected {len(COLUMNS['graph'])}"]
    if total > CAP:
        bad.append(f"{t.line}: table is {total} wide, the cap is {CAP}; shorten `Does` wording")
    if t.kind == "graph" and w[GAP_COLUMN] != GAP_WIDTH:
        bad.append(f"{t.line}: the gap column must be the constant width {GAP_WIDTH}")
    # Compare as written against canonical, so `check` passing means `format` is a no-op.
    if t.src_widths and len(t.src_widths) == t.ncols:
        for c, (got, want) in enumerate(zip(t.src_widths, w)):
            if got != want:
                name = "graph gap" if t.kind == "graph" and c == GAP_COLUMN else COLUMNS[t.kind][c]
                bad.append(f"{t.line}: {name} column is {got} wide, {want} is canonical; run format")
    if t.kind == "graph":
        for r, cells in enumerate(t.rows):
            if cells[GAP_COLUMN]:
                bad.append(f"{t.line + r}: the graph gap column must stay empty")
    return bad


def check_vocabulary(t: Table) -> list[str]:
    bad, names = [], COLUMNS[t.kind]
    for r, cells in enumerate(t.rows):
        for c, cell in enumerate(cells):
            col = names[c] if c < len(names) else f"column {c}"
            where = f"{t.line + r}: {col}"
            for pat, why in BANNED:
                if pat.search(cell):
                    bad.append(f"{where}: {why}, found {cell!r}")
            if "\\|" in cell:
                bad.append(f"{where}: escaped pipe in {cell!r}; inside a fence write it bare")
            if col == "Does" and re.search(r"Types [`\\|](\b|$)", cell):
                bad.append(f"{where}: {cell!r} shows a bare character in prose; write 'Types backtick', 'Types backslash' or 'Types pipe'")
            for word in CHAR_WORDS:
                if not re.search(rf"\b{word}\b", cell):
                    continue
                if col == "Does":
                    bad.append(f"{where}: capitalised {word!r} in prose; name the character lower case, e.g. 'Types {word.lower()}'")
                else:
                    bad.append(f"{where}: spelled-out character in {cell!r}; write the literal character outside `Does`")
    return bad


def check_semantics(t: Table) -> list[str]:
    """Rules that only a key table can violate.

    Layout and banned spellings are not enough: a model can produce a table that
    is perfectly aligned and still drop the HYPR/MEH form from the Key column.
    That duplication is part of the contract, so it is enforced here.
    """
    if t.kind != "key" or t.ncols != len(COLUMNS["key"]):
        return []
    bad = []
    for r, cells in enumerate(t.rows[1:], 1):
        pos, key, chord = cells[0], cells[1], cells[2]
        wrapped_command = re.match(r"^(HYPR|MEH)\+", chord) or (
            chord.startswith("Ctrl+") and ", then " not in chord and not re.fullmatch(r"M\d+", key)
        )
        if wrapped_command and key != chord:
            bad.append(f"{t.line + r}: {pos} Chord is {chord!r} so Key must repeat it, found {key!r}")
    return bad


def graph_positions(t: Table) -> dict[str, str]:
    """Position -> graph cell, so footnotes are recomputed rather than remembered."""
    out: dict[str, str] = {}
    for cells in t.rows[1:4]:
        tier = cells[0][1:]  # 'L1' -> '1'
        for i in range(1, 6):
            out[f"L{tier}-{i}"] = cells[i]
            out[f"R{tier}-{i}"] = cells[i + 6]
    thumbs = t.rows[4]
    for i in range(3):
        out[f"LT-{i + 1}"] = thumbs[1 + i]
        out[f"RT-{i + 1}"] = thumbs[7 + i]
    return out


def key_name(code: str) -> str:
    if code in KEY_NAMES:
        return KEY_NAMES[code]
    if re.fullmatch(r"[A-Z]|[0-9]|F(?:[1-9]|1[0-2])", code):
        return code
    raise Bad(f"unsupported KC_{code}; add its documentation name to KEY_NAMES")


def source_aliases(text: str) -> dict[str, tuple[str, str]]:
    """QMK alias -> (Key table value, graph value), derived from keycodes.h."""
    aliases: dict[str, tuple[str, str]] = {}
    modifiers = {"GUI": "Super", "ALT": "Alt", "CTL": "Ctrl", "SFT": "Shift"}
    home = re.compile(r"^#define\s+(HOME_\w+)\s+[LR](GUI|ALT|CTL|SFT)_T\(KC_(\w+)\)\s*$", re.M)
    for alias, modifier, tap in home.findall(text):
        value = f"{modifiers[modifier]} / {key_name(tap)}"
        aliases[alias] = (value, value)

    layer_tap = re.compile(r"^#define\s+(LAYER_(\w+))\s+LT\(\d+,\s*KC_(\w+)\)\s*$", re.M)
    for alias, layer, tap in layer_tap.findall(text):
        title = layer.title()
        aliases[alias] = (f"{key_name(tap)} / {title}", title)

    layer_hold = re.compile(r"^#define\s+(LAYER_(\w+))\s+MO\(\d+\)\s*$", re.M)
    for alias, layer in layer_hold.findall(text):
        title = layer.title()
        aliases[alias] = (title, title)
    return aliases


PURE_MODIFIERS = {
    "LGUI": ("Super", "Left Super"),
    "LALT": ("Alt", "Left Alt"),
    "LCTL": ("Ctrl", "Left Ctrl"),
    "LSFT": ("Shift", "Left Shift"),
    "RGUI": ("Super", "Right Super"),
    "RALT": ("Alt", "Right Alt"),
    "RCTL": ("Ctrl", "Right Ctrl"),
    "RSFT": ("Shift", "Right Shift"),
}
MEDIA_CHORDS = {
    "MNXT": "XF86AudioNext",
    "MPLY": "XF86AudioPlay",
    "MPRV": "XF86AudioPrev",
    "MUTE": "XF86AudioMute",
    "VOLD": "XF86AudioLowerVolume",
    "VOLU": "XF86AudioRaiseVolume",
}


def source_key(token: str, aliases: dict[str, tuple[str, str]]) -> tuple[str, str]:
    """Return the exact Key and graph labels required for one grid token."""
    if token in aliases:
        return aliases[token]
    if token == "XXXXXXX":
        return "-", "-"
    if token == "QK_BOOT":
        return "Boot", "Boot"
    if token == "QK_CAPS_WORD_TOGGLE":
        return "Caps Word", "Caps Word"
    if match := re.fullmatch(r"QMK_M(\d+)", token):
        value = f"M{match.group(1)}"
        return value, value
    if match := re.fullmatch(r"(HYPR|MEH)\(KC_(\w+)\)", token):
        value = f"{match.group(1)}+{key_name(match.group(2))}"
        return value, value
    if match := re.fullmatch(r"LCTL\(KC_(\w+)\)", token):
        value = key_name(match.group(1))
        graph = GRAPH_NAMES.get(value, value)
        return f"Ctrl+{value}", f"Ctrl+{graph}"
    if match := re.fullmatch(r"LSFT\(KC_(\w+)\)", token):
        code = match.group(1)
        if code not in SHIFTED_NAMES:
            raise Bad(f"unsupported shifted KC_{code}; add it to SHIFTED_NAMES")
        value = SHIFTED_NAMES[code]
        return value, value
    if match := re.fullmatch(r"KC_(\w+)", token):
        value = key_name(match.group(1))
        return value, GRAPH_NAMES.get(value, value)
    raise Bad(f"unsupported grid token {token!r}; add its documentation mapping")


def source_chord(token: str, aliases: dict[str, tuple[str, str]], macros: dict[str, Macro]) -> str:
    """Return the host-visible chord emitted by one grid token."""
    if token in aliases:
        key, _graph = aliases[token]
        return key if " / " in key else "-"
    if token in {"XXXXXXX", "QK_BOOT"}:
        return "-"
    if token == "QK_CAPS_WORD_TOGGLE":
        return "Caps Word"
    if token in macros:
        return macros[token].chord
    if match := re.fullmatch(r"(HYPR|MEH)\(KC_(\w+)\)", token):
        return f"{match.group(1)}+{key_name(match.group(2))}"
    if match := re.fullmatch(r"LCTL\(KC_(\w+)\)", token):
        return f"Ctrl+{key_name(match.group(1))}"
    if match := re.fullmatch(r"LSFT\(KC_(\w+)\)", token):
        return f"Shift+{key_name(match.group(1))}"
    if match := re.fullmatch(r"KC_(\w+)", token):
        code = match.group(1)
        if code in PURE_MODIFIERS:
            return PURE_MODIFIERS[code][1]
        if code in MEDIA_CHORDS:
            return MEDIA_CHORDS[code]
        return key_name(code)
    raise Bad(f"unsupported grid token {token!r}; cannot derive Chord")


def macro_does(macro: Macro, layer: str) -> str:
    """Select one source-owned annotation and apply mixed-layer attribution."""
    if layer in macro.annotations:
        target = layer
    elif "system" in macro.annotations:
        target = "system"
    elif len(macro.annotations) == 1:
        target = next(iter(macro.annotations))
    else:
        targets = ", ".join(sorted(macro.annotations)) or "none"
        raise Bad(f"{macro.name} has no unambiguous annotation for {layer}; found {targets}")
    value = macro.annotations[target]
    return f"{target.title()}: {value}" if layer == "apps" else value


def source_positions(text: str, layer: str) -> dict[str, str]:
    """Parse one layer's six 5-key rows and two 3-key thumb rows."""
    prefix = layer.upper()
    out: dict[str, str] = {}
    for half in ("L1", "L2", "L3", "R1", "R2", "R3"):
        pattern = rf"^#define\s+_+{prefix}_{half}_+\s+(.+?)\s*$"
        found = re.findall(pattern, text, re.M)
        if len(found) != 1:
            raise Bad(f"expected one {prefix}_{half} grid define, found {len(found)}")
        tokens = [token.strip() for token in found[0].split(",")]
        if len(tokens) != 5:
            raise Bad(f"{prefix}_{half} has {len(tokens)} entries, expected 5")
        out.update({f"{half}-{i}": token for i, token in enumerate(tokens, 1)})
    for side, label in (("LEFT", "LT"), ("RIGHT", "RT")):
        pattern = rf"^#define\s+_+{prefix}_{side}_+\s+(.+?)\s*$"
        found = re.findall(pattern, text, re.M)
        if len(found) != 1:
            raise Bad(f"expected one {prefix}_{side} grid define, found {len(found)}")
        tokens = [token.strip() for token in found[0].split(",")]
        if len(tokens) != 3:
            raise Bad(f"{prefix}_{side} has {len(tokens)} entries, expected 3")
        out.update({f"{label}-{i}": token for i, token in enumerate(tokens, 1)})
    return out


def check_source_file(path: str, text: str, keymap: str, keycodes: str, macros_text: str = "") -> list[str]:
    """Compare generated firmware-owned cells with the firmware sources."""
    layer = Path(path).stem.lower()
    if layer not in LAYERS:
        return []
    tables, errors = parse_tables(text)
    if errors:
        return []  # check_file reports parse errors; source comparison needs parsed tables
    keys = [table for table in tables if table.kind == "key"]
    graphs = [table for table in tables if table.kind == "graph"]
    if len(keys) != 1 or len(graphs) != 1:
        return [f"source: expected one key table and one graph table, found {len(keys)} and {len(graphs)}"]

    if keys[0].ncols != len(COLUMNS["key"]) or graphs[0].ncols != len(COLUMNS["graph"]):
        return []
    if [row[0] for row in graphs[0].rows] != ["ROW", "L1", "L2", "L3", "THUMBS"]:
        return []

    rows = keys[0].rows[1:]
    positions = [row[0] for row in rows]
    duplicates = sorted({position for position in positions if positions.count(position) > 1})
    if duplicates:
        return [f"source: duplicate Key-table positions: {', '.join(duplicates)}"]
    documented = {row[0]: row for row in rows}
    graphed = graph_positions(graphs[0])

    macros: dict[str, Macro] = {}
    macro_errors: list[str] = []
    if macros_text:
        macros, macro_errors = parse_macros(macros_text)
    try:
        aliases = source_aliases(keycodes)
        source = source_positions(keymap, layer)
    except Bad as exc:
        return [f"source: {exc}"]

    bad = [f"source: macros.c: {error}" for error in macro_errors]
    missing = sorted(set(source) - set(documented))
    extra = sorted(set(documented) - set(source))
    if missing:
        bad.append(f"source: Key table is missing positions: {', '.join(missing)}")
    if extra:
        bad.append(f"source: Key table has unknown positions: {', '.join(extra)}")
    for position, token in source.items():
        try:
            expected_key, expected_graph = source_key(token, aliases)
        except Bad as exc:
            bad.append(f"source: {position}: {exc}")
            continue
        if position in documented and documented[position][1] != expected_key:
            bad.append(f"source: {position} is {token}, Key is {documented[position][1]!r}, expected {expected_key!r}")
        if position in graphed and graphed[position] != expected_graph:
            bad.append(f"source: {position} is {token}, graph is {graphed[position]!r}, expected {expected_graph!r}")
        if macros_text:
            try:
                expected_chord = source_chord(token, aliases, macros)
            except Bad as exc:
                bad.append(f"source: {position}: {exc}")
                continue
            if position in documented and documented[position][2] != expected_chord:
                bad.append(f"source: {position} is {token}, Chord is {documented[position][2]!r}, expected {expected_chord!r}")
            if token in macros:
                try:
                    expected_does = macro_does(macros[token], layer)
                except Bad as exc:
                    bad.append(f"source: {position}: {exc}")
                    continue
                if position in documented and documented[position][3] != expected_does:
                    bad.append(f"source: {position} is {token}, Does is {documented[position][3]!r}, expected {expected_does!r}")
    return bad


def check_footnotes(tables: list[Table], text: str) -> list[str]:
    key = next((t for t in tables if t.kind == "key"), None)
    graph = next((t for t in tables if t.kind == "graph"), None)
    if not key or not graph or key.ncols != len(COLUMNS["key"]) or graph.ncols != len(COLUMNS["graph"]) or len(graph.rows) < 5:
        return []
    gvals = graph_positions(graph)
    main = [(p, k) for p, k, _, _ in key.rows[1:] if not p.startswith(("LT", "RT"))]
    thumb = [(p, k) for p, k, _, _ in key.rows[1:] if p.startswith(("LT", "RT"))]
    short = any(p in gvals and gvals[p] != k and len(gvals[p]) < len(k) for p, k in main if k != "-")
    hold = any(p in gvals and " / " in k and gvals[p] == k.split(" / ")[-1] for p, k in thumb)
    bad = []
    for note, want in ((FOOTNOTE_SHORT, short), (FOOTNOTE_THUMB, hold)):
        if want and note not in text:
            bad.append(f"file: missing footnote, a graph cell is shorter than the table: {note}")
        if not want and note in text:
            bad.append(f"file: stale footnote, no graph cell is short any more: {note}")
    return bad


def check_syntax(text: str) -> list[str]:
    """File-level hygiene.

    ASCII is enforced inside fences only: that is where a wide character would
    break column alignment. Prose outside a fence may legitimately use an em
    dash, as these file headings do. Box-drawing is rejected everywhere, because
    a pseudo-table rule anywhere signals that someone is drawing tables by hand.
    """
    bad = []
    lines = text.split("\n")
    try:
        spans = fence_spans(lines)
    except Bad:
        spans = []
    for n, line in enumerate(lines, 1):
        if line != line.rstrip():
            bad.append(f"{n}: trailing whitespace")
        if "\t" in line:
            bad.append(f"{n}: tab character")
        if any(0x2500 <= ord(ch) <= 0x259F for ch in line):
            bad.append(f"{n}: box-drawing character; borders must be ASCII `+` and `-`")
        elif in_fence(spans, n - 1) and any(ord(ch) > 126 for ch in line):
            bad.append(f"{n}: non-ASCII character inside a table fence")
    return bad


def check_file(path: str, text: str) -> list[str]:
    out = [f"{path}:{b}" for b in check_syntax(text)]
    tables, errors = parse_tables(text)
    out += [f"{path}:{e}" for e in errors]
    lines = text.split("\n")
    try:
        spans = fence_spans(lines)
    except Bad:
        spans = []
    for t in tables:
        body = lines[t.line - 1 : t.line - 1 + len(t.shape)]
        for n, line in enumerate(body):
            if len(line) != len(body[0]):
                out.append(f"{path}:{t.line + n}: line is {len(line)} wide, the table is {len(body[0])}")
                break
        for rule in (check_shape, check_widths, check_vocabulary, check_semantics):
            out += [f"{path}:{b}" for b in rule(t)]
    for start, end in table_blocks(lines):
        if in_fence(spans, start) and any(not is_table_line(l) for l in lines[start + 1 : end]):
            out.append(f"{path}:{start + 1}: prose mixed into a table fence")
    out += [f"{path}:{b}" for b in check_footnotes(tables, text)]
    if not text.endswith("\n"):
        out.append(f"{path}: file must end with a newline")
    if text.endswith("\n\n"):
        out.append(f"{path}: file must end with exactly one newline")
    def key(msg: str) -> tuple[str, int]:
        head, _, rest = msg.partition(":")
        line = rest.split(":", 1)[0]
        return (head, int(line) if line.isdigit() else 0)

    return sorted(set(out), key=key)


def format_text(text: str) -> str:
    """Rebuild every table: borders derived from content, gap fixed, fences added."""
    lines = text.split("\n")
    spans = fence_spans(lines)
    out, i = [], 0
    for start, end in table_blocks(lines):
        out += lines[i:start]
        rendered = parse_block(lines, start, end).render()
        if in_fence(spans, start):
            out += rendered
        else:
            if out and out[-1] != "":
                out.append("")
            out += ["```text", *rendered, "```"]
        i = end + 1
    out += lines[i:]
    return "\n".join(out)


def all_cells(text: str) -> list[tuple[int, int, str]]:
    """Every cell as (line, column, text), used to prove a run changed no content."""
    lines = text.split("\n")
    cells = []
    for start, end in table_blocks(lines):
        t = parse_block(lines, start, end)
        for r, row in enumerate(t.rows):
            for c, cell in enumerate(row):
                cells.append((t.line + r, c, cell))
    return cells


# --------------------------------------------------------------------------
# deterministic document generation
# --------------------------------------------------------------------------


PHYSICAL_ORDER = [
    f"{side}{row}-{column}"
    for side in ("L", "R")
    for column in range(1, 6)
    for row in range(1, 4)
] + [f"{side}T-{column}" for side in ("L", "R") for column in range(1, 4)]

PRINTABLE = {
    "COMMA": ",",
    "DOT": ".",
    "EQL": "=",
    "GRAVE": "backtick",
    "KP_PLUS": "+ (numpad plus)",
    "LBRC": "[",
    "MINS": "-",
    "QUOT": "'",
    "RBRC": "]",
    "SCLN": ";",
    "SLSH": "/",
    "BSLS": "backslash",
}
SPECIAL_DOES = {
    "CAPS": "Toggle Caps Lock",
    "DOWN": "Move cursor down",
    "END": "Move to line end",
    "HOME": "Move to line start",
    "LEFT": "Move cursor left",
    "MNXT": "Media: next track",
    "MPLY": "Media: play or pause",
    "MPRV": "Media: previous track",
    "MUTE": "System: mute toggle",
    "PGDN": "Page down",
    "PGUP": "Page up",
    "RIGHT": "Move cursor right",
    "UP": "Move cursor up",
    "VOLD": "System: volume down",
    "VOLU": "System: volume up",
}


def current_rows(text: str) -> dict[str, list[str]]:
    if not text:
        return {}
    tables, errors = parse_tables(text)
    if errors:
        raise Bad("cannot preserve application claims from invalid document: " + "; ".join(errors))
    keys = [table for table in tables if table.kind == "key"]
    if len(keys) != 1:
        raise Bad(f"expected one existing key table, found {len(keys)}")
    return {row[0]: row for row in keys[0].rows[1:]}


def deterministic_does(token: str, position: str, key: str) -> str | None:
    """Return source-derived prose, or None for an application-owned shortcut."""
    if token == "XXXXXXX":
        return "-"
    if token == "QK_BOOT":
        return "Reboots keyboard into bootloader (firmware)"
    if token == "QK_CAPS_WORD_TOGGLE":
        return "Toggle Caps Word"
    if token.startswith("HOME_"):
        modifier, tap = key.split(" / ")
        side = "left" if token in {"HOME_A", "HOME_R", "HOME_S", "HOME_T"} else "right"
        return f"{tap} on tap; {side} {modifier} on hold"
    if token.startswith("LAYER_"):
        if " / " in key:
            tap, layer = key.split(" / ")
            return f"{tap} on tap; {layer} layer on hold"
        return "Extra layer on hold (F-keys, media)" if token == "LAYER_EXTRA" else f"{key} layer on hold"
    if match := re.fullmatch(r"LSFT\(KC_(\w+)\)", token):
        value = SHIFTED_NAMES.get(match.group(1))
        if value is None:
            raise Bad(f"unsupported shifted KC_{match.group(1)}; cannot derive Does")
        return "Types pipe" if value == "|" else f"Types {value}"
    if re.match(r"^(?:HYPR|MEH|LCTL)\(", token):
        return None
    if not (match := re.fullmatch(r"KC_(\w+)", token)):
        return None
    code = match.group(1)
    if code in PURE_MODIFIERS:
        modifier, chord = PURE_MODIFIERS[code]
        side = "left" if chord.startswith("Left") else "right"
        return f"{modifier} modifier ({side} hand)"
    if code in SPECIAL_DOES:
        return SPECIAL_DOES[code]
    if re.fullmatch(r"F(?:[1-9]|1[0-2])", code):
        return f"Sends {code}"
    if re.fullmatch(r"[A-Z]", code):
        return f"Types {code.lower()}"
    if re.fullmatch(r"[0-9]", code):
        return f"Types {code}"
    if code in PRINTABLE:
        return f"Types {PRINTABLE[code]}"
    return None


def combo_rows(text: str) -> list[list[str]]:
    arrays = {
        name: [SEND_KEY_ALIASES.get(code, code) for code in re.findall(r"KC_(\w+)", values)]
        for name, values in re.findall(
            r"const\s+uint16_t\s+PROGMEM\s+(\w+)\[\]\s*=\s*\{(.*?)COMBO_END\s*\};",
            text,
            re.S,
        )
    }
    assignments = re.findall(r"\[(\w+)\]\s*=\s*COMBO_ACTION\((\w+)\)", text)
    cases = {
        name: body
        for name, body in re.findall(r"case\s+(\w+)\s*:(.*?^\s*break;\s*$)", text, re.S | re.M)
    }
    rows: list[list[str]] = [["Keys", "Chord", "Does"]]
    for event, array in assignments:
        if array not in arrays or event not in cases:
            raise Bad(f"combo {event} is missing its key array or action case")
        keys = "+".join(key_name(code) for code in arrays[array])
        body = cases[event]
        taps = re.findall(r"tap_code(?:16)?\s*\(\s*KC_(\w+)\s*\)", body)
        string_arg = call_argument(body, "send_string")
        if taps and string_arg is not None:
            raise Bad(f"combo {event} mixes tap_code and send_string")
        if taps:
            chord = ", then ".join(key_name(SEND_KEY_ALIASES.get(code, code)) for code in taps)
            does = f"Sends {chord}"
        elif string_arg is not None:
            try:
                chord = ast.literal_eval(string_arg.strip())
            except (SyntaxError, ValueError) as exc:
                raise Bad(f"combo {event} has an invalid string: {exc}") from exc
            if not isinstance(chord, str):
                raise Bad(f"combo {event} does not send a string literal")
            if event == "PERSONALMAIL":
                does = "Types personal email"
            elif event == "WORKMAIL":
                does = "Types work email"
            else:
                does = f"Types {chord}"
        else:
            raise Bad(f"combo {event} has no supported output")
        rows.append([keys, chord, does])
    return rows


def graph_rows(records: dict[str, tuple[str, str, str]]) -> list[list[str]]:
    rows = [["ROW", "1", "2", "3", "4", "5", "", "1", "2", "3", "4", "5"]]
    for row in range(1, 4):
        rows.append(
            [f"L{row}"]
            + [records[f"L{row}-{column}"][1] for column in range(1, 6)]
            + [""]
            + [records[f"R{row}-{column}"][1] for column in range(1, 6)]
        )
    rows.append(
        ["THUMBS"]
        + [records[f"LT-{column}"][1] for column in range(1, 4)]
        + ["", "", ""]
        + [records[f"RT-{column}"][1] for column in range(1, 4)]
        + ["", ""]
    )
    return rows


def render_document(layer: str, rows: list[list[str]], graph: list[list[str]], combos: list[list[str]] | None = None) -> str:
    key_table = Table("key", [["Position", "Key", "Chord", "Does"], *rows], "", 1)
    graph_table = Table("graph", graph, "", 1)
    parts = [f"# {layer.title()}", "", "```text", *key_table.render(), "```", "", "```text", *graph_table.render(), "```"]
    keyed = {row[0]: row[1] for row in rows}
    graphed = graph_positions(graph_table)
    main_short = any(
        position in graphed and graphed[position] != key and len(graphed[position]) < len(key)
        for position, key in keyed.items()
        if not position.startswith(("LT", "RT")) and key != "-"
    )
    thumb_hold = any(
        position in graphed and " / " in key and graphed[position] == key.split(" / ")[-1]
        for position, key in keyed.items()
        if position.startswith(("LT", "RT"))
    )
    if main_short:
        parts += ["", FOOTNOTE_SHORT]
    if thumb_hold:
        parts += ["", FOOTNOTE_THUMB]
    if layer == "base":
        parts += ["", "Home-row keys tap the letter, hold the mod."]
    if combos is not None:
        combo_table = Table("combos", combos, "", 1)
        parts += ["", "Combos (Base layer positions):", "", "```text", *combo_table.render(), "```"]
    return "\n".join(parts) + "\n"


def generate_layer(
    layer: str,
    current: str,
    keymap: str,
    keycodes: str,
    macros: dict[str, Macro],
    combos_text: str = "",
    macros_path: str = "macros.c",
) -> tuple[str, list[ReviewItem]]:
    """Generate one complete layer document and its manual-review items."""
    aliases = source_aliases(keycodes)
    source = source_positions(keymap, layer)
    old = current_rows(current)
    rows: list[list[str]] = []
    records: dict[str, tuple[str, str, str]] = {}
    reviews: list[ReviewItem] = []
    for position in PHYSICAL_ORDER:
        token = source[position]
        key, graph = source_key(token, aliases)
        chord = source_chord(token, aliases, macros)
        previous = old.get(position, [position, "-", "-", "-"])[3]
        if token in macros:
            does = macro_does(macros[token], layer)
            if previous != does:
                macro = macros[token]
                reviews.append(
                    ReviewItem(
                        layer,
                        position,
                        token.replace("QMK_", ""),
                        f"{macros_path}:{macro.line}",
                        chord,
                        previous,
                        does,
                        "source override",
                    )
                )
        else:
            does = deterministic_does(token, position, key)
            if does is None:
                if previous not in {"", "-", "Review required"}:
                    does = previous
                else:
                    does = "Review required"
                    reviews.append(
                        ReviewItem(layer, position, key, "keymap_colemakdh.c", chord, previous, does, "missing application claim")
                    )
        rows.append([position, key, chord, does])
        records[position] = (key, graph, does)
    combos = combo_rows(combos_text) if layer == "base" else None
    return render_document(layer, rows, graph_rows(records), combos), reviews


def render_review_report(items: list[ReviewItem]) -> str:
    noun = "item" if len(items) == 1 else "items"
    lines = [f"REVIEW REQUIRED ({len(items)} {noun})", "--- BEGIN REVIEW REPORT ---"]
    for index, item in enumerate(items):
        if index:
            lines.append("")
        lines += [
            f"{item.layer.upper()} {item.position} / {item.macro}",
            f"Source: {item.source}",
            f"QMK: {item.qmk}",
        ]
        if re.fullmatch(r"M\d+", item.macro):
            declared = item.generated.split(": ", 1)[-1] if item.layer == "apps" else item.generated
            lines.append(f"Declared action: {declared}")
        lines += [
            f"Previous Does: {item.previous}",
            f"New Does: {item.generated}",
            f"Class: {item.reason}",
        ]
    lines.append("--- END REVIEW REPORT ---")
    return "\n".join(lines)


def atomic_write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    mode = path.stat().st_mode if path.exists() else None
    with tempfile.NamedTemporaryFile("w", dir=path.parent, prefix=f".{path.name}.", delete=False) as handle:
        temporary = Path(handle.name)
        handle.write(text)
        handle.flush()
        os.fsync(handle.fileno())
    try:
        os.chmod(temporary, mode if mode is not None else 0o644)
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


# --------------------------------------------------------------------------
# entry point
# --------------------------------------------------------------------------


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description="Format and verify the layer tables.")
    sub = ap.add_subparsers(dest="cmd", required=True)
    root = Path(__file__).resolve().parents[2]
    s = sub.add_parser("check")
    s.add_argument("files", nargs="+")
    s.add_argument("--keymap", default=str(root / "keymap_colemakdh.c"))
    s.add_argument("--keycodes", default=str(root / "keycodes.h"))
    s.add_argument("--no-source", action="store_true", help="skip firmware comparison for isolated fixtures")
    s.add_argument("--macros", default=str(root / "macros.c"))
    s = sub.add_parser("format")
    s.add_argument("files", nargs="+")
    s = sub.add_parser("generate")
    mode = s.add_mutually_exclusive_group()
    mode.add_argument("--write", metavar="LAYER")
    mode.add_argument("--check", metavar="LAYER", nargs="?", const="all")
    s.add_argument("--keymap", default=str(root / "keymap_colemakdh.c"))
    s.add_argument("--keycodes", default=str(root / "keycodes.h"))
    s.add_argument("--macros", default=str(root / "macros.c"))
    s.add_argument("--combos", default=str(root / "combos.c"))
    s.add_argument("--docs-dir", default=str(root / "docs"))
    s = sub.add_parser("verify-cells")
    s.add_argument("file")
    s.add_argument("--against", required=True)
    a = ap.parse_args(argv)

    try:
        if a.cmd == "verify-cells":
            new, old = all_cells(open(a.file).read()), all_cells(open(a.against).read())
            changed = [(n, o) for n, o in zip(new, old) if n[2] != o[2]]
            for (l1, c1, x1), (l2, c2, x2) in changed:
                print(f"line {l1} column {c1}: {x2!r} -> {x1!r}")
            if len(new) != len(old):
                print(f"cell count differs: {len(old)} before, {len(new)} after")
            if changed or len(new) != len(old):
                print(f"verify-cells: FAILED, {len(changed)} of {len(new)} cells changed")
                return 1
            print(f"verify-cells: OK, all {len(new)} cells identical")
            return 0

        if a.cmd == "format":
            rendered: dict[Path, str] = {}
            for name in a.files:
                path = Path(name)
                before = path.read_text()
                after = format_text(before)
                if after != before:
                    rendered[path] = after
            for path, after in rendered.items():
                atomic_write(path, after)
                print(f"formatted {path}")
            print(f"format: {len(rendered)} of {len(a.files)} files rewritten")
            return 0

        if a.cmd == "generate":
            target = a.write or a.check
            if target is None:
                print("generate: choose --write LAYER or --check [LAYER]")
                return 1
            if target != "all" and target not in LAYERS:
                print(f"generate: unknown layer {target!r}; choose {', '.join(sorted(LAYERS))} or all")
                return 1
            inputs = {label: Path(path) for label, path in (("keymap", a.keymap), ("keycodes", a.keycodes), ("macros", a.macros), ("combos", a.combos))}
            missing = [f"{label} file not found: {path}" for label, path in inputs.items() if not path.is_file()]
            if missing:
                for error in missing:
                    print(f"generate: {error}")
                print("generate: FAILED; no documents written")
                return 1
            keymap, keycodes = inputs["keymap"].read_text(), inputs["keycodes"].read_text()
            macros_text, combos_text = inputs["macros"].read_text(), inputs["combos"].read_text()
            macros, macro_errors = parse_macros(macros_text)
            if macro_errors:
                for error in macro_errors:
                    print(f"generate: macros.c: {error}")
                print("generate: FAILED; no documents written")
                return 1
            layers = sorted(LAYERS) if target == "all" else [target]
            docs_dir = Path(a.docs_dir)
            generated: dict[Path, str] = {}
            reviews: list[ReviewItem] = []
            errors: list[str] = []
            for layer in layers:
                path = docs_dir / f"{layer}.md"
                current = path.read_text() if path.is_file() else ""
                try:
                    output, layer_reviews = generate_layer(
                        layer,
                        current,
                        keymap,
                        keycodes,
                        macros,
                        combos_text,
                        str(inputs["macros"]),
                    )
                    generated[path] = output
                    reviews.extend(layer_reviews)
                except Bad as exc:
                    errors.append(f"{layer}: {exc}")
            if errors:
                for error in errors:
                    print(f"generate: {error}")
                print("generate: FAILED; no documents written")
                return 1
            order = {layer: index for index, layer in enumerate(("base", "niri", "nav", "emacs", "sym", "num", "apps", "extra"))}
            position_order = {position: index for index, position in enumerate(PHYSICAL_ORDER)}
            reviews.sort(key=lambda item: (order[item.layer], position_order.get(item.position, 999)))
            changed = [path for path, output in generated.items() if not path.is_file() or path.read_text() != output]
            if a.write:
                for path in changed:
                    atomic_write(path, generated[path])
                    print(f"generated {path}")
                print(f"generate: {len(changed)} of {len(generated)} documents rewritten")
            elif changed:
                for path in changed:
                    print(f"generate: stale {path}")
            if reviews:
                print(render_review_report(reviews))
                return 2
            if a.check and changed:
                print("generate: FAILED; generated documents differ")
                return 1
            print("generate: PASS")
            return 0

        status = 0
        source_files = any(Path(path).stem.lower() in LAYERS for path in a.files)
        keymap = keycodes = macros_text = ""
        if source_files and not a.no_source:
            for label, path in (("keymap", a.keymap), ("keycodes", a.keycodes), ("macros", a.macros)):
                if not Path(path).is_file():
                    print(f"source: {label} file not found: {path}; use --no-source only for isolated fixtures")
                    status = 1
            if not status:
                keymap, keycodes, macros_text = Path(a.keymap).read_text(), Path(a.keycodes).read_text(), Path(a.macros).read_text()
        for path in a.files:
            text = Path(path).read_text()
            errors = check_file(path, text)
            if source_files and not a.no_source and keymap and keycodes:
                errors += [f"{path}:{bad}" for bad in check_source_file(path, text, keymap, keycodes, macros_text)]
            for bad in sorted(set(errors)):
                print(bad)
                status = 1
        print("check: OK" if not status else "check: FAILED")
        return status
    except (Bad, OSError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
