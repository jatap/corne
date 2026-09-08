#!/usr/bin/env python3
"""Regression tests for layer_tables.py's firmware correspondence checks."""

import io
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path

import layer_tables as tables

ROOT = Path(__file__).resolve().parents[2]
LAYERS = ("base", "niri", "nav", "emacs", "sym", "num", "apps", "extra")
HALVES = ("L1", "L2", "L3", "R1", "R2", "R3")


def positions() -> list[str]:
    return [f"{half}-{column}" for half in HALVES for column in range(1, 6)] + [
        f"{side}-{column}" for side in ("LT", "RT") for column in range(1, 4)
    ]


def source(layer: str, tokens: dict[str, str]) -> str:
    lines = []
    for half in HALVES:
        row = ", ".join(tokens[f"{half}-{column}"] for column in range(1, 6))
        lines.append(f"#define _____{layer.upper()}_{half}_____ {row}")
    for side, label in (("LEFT", "LT"), ("RIGHT", "RT")):
        row = ", ".join(tokens[f"{label}-{column}"] for column in range(1, 4))
        lines.append(f"#define _____{layer.upper()}_{side}_____ {row}")
    return "\n".join(lines) + "\n"


def document(layer: str, values: dict[str, str]) -> str:
    key_rows = [["Position", "Key", "Chord", "Does"]]
    physical_order = [
        f"{side}{row}-{column}"
        for side in ("L", "R")
        for column in range(1, 6)
        for row in range(1, 4)
    ] + [f"{side}T-{column}" for side in ("L", "R") for column in range(1, 4)]
    key_rows += [[position, values[position], "-", "-"] for position in physical_order]

    graph_rows = [["ROW", "1", "2", "3", "4", "5", "", "1", "2", "3", "4", "5"]]
    for row in range(1, 4):
        graph_rows.append(
            [f"L{row}"]
            + [values[f"L{row}-{column}"] for column in range(1, 6)]
            + [""]
            + [values[f"R{row}-{column}"] for column in range(1, 6)]
        )
    graph_rows.append(
        ["THUMBS"]
        + [values[f"LT-{column}"] for column in range(1, 4)]
        + ["", "", ""]
        + [values[f"RT-{column}"] for column in range(1, 4)]
        + ["", ""]
    )

    key = tables.Table("key", key_rows, "", 1)
    graph = tables.Table("graph", graph_rows, "", 1)
    return "\n".join(
        [
            f"# {layer.title()}",
            "",
            "```text",
            *key.render(),
            "```",
            "",
            "```text",
            *graph.render(),
            "```",
            "",
        ]
    )


class MacroTests(unittest.TestCase):
    def test_m20_emits_the_direct_emacs_sequence(self) -> None:
        macros, errors = tables.parse_macros((ROOT / "macros.c").read_text())
        self.assertEqual([], errors)
        self.assertEqual("Alt+G, then G", macros["QMK_M20"].chord)

    def test_annotation_and_uppercase_send_string_are_derived(self) -> None:
        source_text = '''
        /** @emacs example action */
        case QMK_M99:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("G") SS_TAP(X_G));
            }
            break;
        '''
        macros, errors = tables.parse_macros(source_text)
        self.assertEqual([], errors)
        self.assertEqual("Alt+Shift+G, then G", macros["QMK_M99"].chord)
        self.assertEqual({"emacs": "example action"}, macros["QMK_M99"].annotations)

    def test_system_annotation_and_tap_code_sequence_are_derived(self) -> None:
        source_text = '''
        /** @system Types the pound sign via Linux text input */
        case QMK_M26:
            if (record->event.pressed) {
                tap_code(KC_CAPS);
                tap_code(KC_MINS);
                tap_code(KC_L);
            }
            break;
        '''
        macros, errors = tables.parse_macros(source_text)
        self.assertEqual([], errors)
        self.assertEqual("Caps Lock, then Minus, then L", macros["QMK_M26"].chord)
        self.assertEqual("Types the pound sign via Linux text input", macros["QMK_M26"].annotations["system"])

    def test_nested_modifiers_are_derived_in_source_order(self) -> None:
        source_text = '''
        /** @niri Sets column width */
        case QMK_M28:
            SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_2))));
            break;
        '''
        macros, errors = tables.parse_macros(source_text)
        self.assertEqual([], errors)
        self.assertEqual("Super+Ctrl+2", macros["QMK_M28"].chord)

    def test_annotation_payload_can_contain_an_asterisk(self) -> None:
        source_text = '''
        /** @emacs Searches for * literally */
        case QMK_M0:
            SEND_STRING("x");
            break;
        '''
        macros, errors = tables.parse_macros(source_text)
        self.assertEqual([], errors)
        self.assertEqual("Searches for * literally", macros["QMK_M0"].annotations["emacs"])

    def test_missing_annotation_is_not_hidden_by_macro_name_prefix(self) -> None:
        source_text = '''
        /** @unknown value */
        case QMK_M20:
            SEND_STRING("x");
            break;

        /** ordinary comment */
        case QMK_M2:
            SEND_STRING("y");
            break;
        '''
        _macros, errors = tables.parse_macros(source_text)
        self.assertTrue(any("QMK_M20" in error and "unknown @unknown" in error for error in errors))
        self.assertTrue(any("QMK_M2 line" in error and "missing @emacs" in error for error in errors))

    def test_annotation_errors_accumulate(self) -> None:
        source_text = '''
        /** @emacs */
        case QMK_M0:
            SEND_STRING("x");
            break;

        /**
         * @emacs first line
         * continuation
         * @emacs duplicate
         * @unknown value
         */
        case QMK_M1:
            SEND_STRING("y");
            break;
        '''
        _macros, errors = tables.parse_macros(source_text)
        self.assertEqual(3, len(errors))
        self.assertTrue(any("QMK_M0" in error and "empty @emacs" in error for error in errors))
        self.assertTrue(any("QMK_M1" in error and "duplicate @emacs" in error for error in errors))
        self.assertTrue(any("QMK_M1" in error and "unknown @unknown" in error for error in errors))


class GenerationTests(unittest.TestCase):
    def test_macro_annotation_overrides_does_and_reports_review(self) -> None:
        tokens = dict.fromkeys(positions(), "XXXXXXX")
        values = dict.fromkeys(positions(), "-")
        tokens["R1-1"] = "QMK_M0"
        values["R1-1"] = "M0"
        macro_text = '''
        /** @emacs goto-line */
        case QMK_M0:
            SEND_STRING(SS_LALT("g") SS_TAP(X_G));
            break;
        '''
        macros, errors = tables.parse_macros(macro_text)
        self.assertEqual([], errors)
        output, reviews = tables.generate_layer("emacs", document("emacs", values), source("emacs", tokens), "", macros)
        key_table = next(table for table in tables.parse_tables(output)[0] if table.kind == "key")
        row = next(row for row in key_table.rows if row[0] == "R1-1")
        self.assertEqual(["R1-1", "M0", "Alt+G, then G", "goto-line"], row)
        self.assertEqual(1, len(reviews))
        report = tables.render_review_report(reviews)
        self.assertIn("Declared action: goto-line", report)
        self.assertIn("Previous Does: -", report)
        self.assertIn("New Does: goto-line", report)

    def test_missing_application_claim_is_visible_and_reviewed(self) -> None:
        tokens = dict.fromkeys(positions(), "XXXXXXX")
        values = dict.fromkeys(positions(), "-")
        tokens["L1-1"] = "HYPR(KC_Q)"
        values["L1-1"] = "HYPR+Q"
        output, reviews = tables.generate_layer("niri", document("niri", values), source("niri", tokens), "", {})
        key_table = next(table for table in tables.parse_tables(output)[0] if table.kind == "key")
        row = next(row for row in key_table.rows if row[0] == "L1-1")
        self.assertEqual("Review required", row[3])
        self.assertEqual("missing application claim", reviews[0].reason)

    def test_repository_generation_is_byte_identical(self) -> None:
        keymap = (ROOT / "keymap_colemakdh.c").read_text()
        keycodes = (ROOT / "keycodes.h").read_text()
        macro_text = (ROOT / "macros.c").read_text()
        macros, errors = tables.parse_macros(macro_text)
        self.assertEqual([], errors)
        combos = (ROOT / "combos.c").read_text()
        for layer in LAYERS:
            path = ROOT / "docs" / f"{layer}.md"
            with self.subTest(layer=layer):
                output, reviews = tables.generate_layer(layer, path.read_text(), keymap, keycodes, macros, combos)
                self.assertEqual([], reviews)
                self.assertEqual(path.read_text(), output)

    def test_new_atomic_file_is_world_readable(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "layer.md"
            tables.atomic_write(path, "content\n")
            self.assertEqual(0o644, path.stat().st_mode & 0o777)

    def test_generate_write_reports_review_then_becomes_idempotent(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            docs = root / "docs"
            docs.mkdir()
            tokens = dict.fromkeys(positions(), "XXXXXXX")
            values = dict.fromkeys(positions(), "-")
            tokens["R1-1"] = "QMK_M0"
            values["R1-1"] = "M0"
            (docs / "emacs.md").write_text(document("emacs", values))
            (root / "keymap.c").write_text(source("emacs", tokens))
            (root / "keycodes.h").write_text("")
            (root / "combos.c").write_text("")
            (root / "macros.c").write_text(
                '/** @emacs goto-line */\ncase QMK_M0:\nSEND_STRING("g");\nbreak;\n'
            )
            command = [
                "generate",
                "--write",
                "emacs",
                "--keymap",
                str(root / "keymap.c"),
                "--keycodes",
                str(root / "keycodes.h"),
                "--macros",
                str(root / "macros.c"),
                "--combos",
                str(root / "combos.c"),
                "--docs-dir",
                str(docs),
            ]
            first_output = io.StringIO()
            with redirect_stdout(first_output):
                first_status = tables.main(command)
            self.assertEqual(2, first_status)
            self.assertIn("REVIEW REQUIRED (1 item)", first_output.getvalue())
            second_output = io.StringIO()
            with redirect_stdout(second_output):
                second_status = tables.main(command)
            self.assertEqual(0, second_status)
            self.assertIn("generate: PASS", second_output.getvalue())

    def test_generate_without_mode_is_a_failure_not_review(self) -> None:
        output = io.StringIO()
        with redirect_stdout(output):
            status = tables.main(["generate"])
        self.assertEqual(1, status)
        self.assertIn("choose --write LAYER or --check", output.getvalue())

    def test_format_validates_all_files_before_writing(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            good = Path(directory) / "good.md"
            bad = Path(directory) / "bad.md"
            original = "# Test\n\n| Position | Key | Chord | Does |\n| --- | --- | --- | --- |\n| L1-1 | - | - | - |\n"
            good.write_text(original)
            bad.write_text("```text\n| broken |\n")
            with redirect_stdout(io.StringIO()), redirect_stderr(io.StringIO()):
                status = tables.main(["format", str(good), str(bad)])
            self.assertEqual(1, status)
            self.assertEqual(original, good.read_text())

    def test_format_repairs_an_expanded_does_cell(self) -> None:
        original = document("base", dict.fromkeys(positions(), "-"))
        changed = original.replace("| L1-1     | -   | -     | -    |", "| L1-1     | -   | -     | A longer value |")
        formatted = tables.format_text(changed)
        parsed, errors = tables.parse_tables(formatted)
        self.assertEqual([], errors)
        self.assertEqual("A longer value", parsed[0].rows[1][3])


class SourceCheckTests(unittest.TestCase):
    def test_control_wrapped_key_without_modifier_is_semantically_rejected(self) -> None:
        table = tables.Table(
            "key",
            [["Position", "Key", "Chord", "Does"], ["L1-1", "0", "Ctrl+0", "Reset font size"]],
            "",
            1,
        )
        self.assertEqual(
            ["2: L1-1 Chord is 'Ctrl+0' so Key must repeat it, found '0'"],
            tables.check_semantics(table),
        )

    def test_control_wrapped_keys_keep_the_modifier(self) -> None:
        aliases: dict[str, tuple[str, str]] = {}
        self.assertEqual(("Ctrl+0", "Ctrl+0"), tables.source_key("LCTL(KC_0)", aliases))
        self.assertEqual(
            ("Ctrl+Numpad Minus", "Ctrl+Minus"),
            tables.source_key("LCTL(KC_KP_MINUS)", aliases),
        )
        self.assertEqual(
            ("Ctrl+Numpad Plus", "Ctrl+Plus"),
            tables.source_key("LCTL(KC_KP_PLUS)", aliases),
        )

    def test_all_repository_layers_match_firmware(self) -> None:
        keymap = (ROOT / "keymap_colemakdh.c").read_text()
        keycodes = (ROOT / "keycodes.h").read_text()
        for layer in LAYERS:
            path = ROOT / "docs" / f"{layer}.md"
            with self.subTest(layer=layer):
                self.assertEqual(
                    [],
                    tables.check_source_file(
                        str(path),
                        path.read_text(),
                        keymap,
                        keycodes,
                        (ROOT / "macros.c").read_text(),
                    ),
                )

    def test_stale_macro_chord_and_does_are_rejected(self) -> None:
        tokens = dict.fromkeys(positions(), "XXXXXXX")
        values = dict.fromkeys(positions(), "-")
        tokens["R1-1"] = "QMK_M0"
        values["R1-1"] = "M0"
        macro_text = '''
        /** @emacs goto-line */
        case QMK_M0:
            SEND_STRING(SS_LALT("G") SS_TAP(X_G));
            break;
        '''
        errors = tables.check_source_file(
            "emacs.md",
            document("emacs", values),
            source("emacs", tokens),
            "",
            macro_text,
        )
        self.assertEqual(
            [
                "source: R1-1 is QMK_M0, Chord is '-', expected 'Alt+Shift+G, then G'",
                "source: R1-1 is QMK_M0, Does is '-', expected 'goto-line'",
            ],
            errors,
        )

    def test_stale_macro_position_is_rejected_in_both_tables(self) -> None:
        tokens = dict.fromkeys(positions(), "XXXXXXX")
        values = dict.fromkeys(positions(), "-")
        values["R1-2"] = "M24"
        errors = tables.check_source_file("apps.md", document("apps", values), source("apps", tokens), "")
        self.assertEqual(
            [
                "source: R1-2 is XXXXXXX, Key is 'M24', expected '-'",
                "source: R1-2 is XXXXXXX, graph is 'M24', expected '-'",
            ],
            errors,
        )

    def test_literal_pipe_maps_without_splitting_the_cell(self) -> None:
        tokens = dict.fromkeys(positions(), "XXXXXXX")
        values = dict.fromkeys(positions(), "-")
        tokens["L3-5"] = "LSFT(KC_BSLS)"
        values["L3-5"] = "|"
        self.assertEqual([], tables.check_source_file("sym.md", document("sym", values), source("sym", tokens), ""))


if __name__ == "__main__":
    unittest.main()
