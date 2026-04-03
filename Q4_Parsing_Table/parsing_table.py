#!/usr/bin/env python3
import csv
import html
import os
import re
import sys
from typing import Dict, List, Set


def usage() -> None:
    print("Usage: python3 parsing_table.py <golem.output> <output_dir>")


def parse_symbol_section(lines: List[str], start_marker: str, end_marker: str) -> Set[str]:
    symbols: Set[str] = set()
    in_section = False
    symbol_re = re.compile(r"^\s+(\S+)\s+\(\d+\)")

    for line in lines:
        if not in_section and line.strip() == start_marker:
            in_section = True
            continue

        if in_section and line.strip().startswith(end_marker):
            break

        if in_section:
            match = symbol_re.match(line)
            if match:
                symbols.add(match.group(1))

    return symbols


def add_cell(row: Dict[str, str], symbol: str, value: str) -> None:
    existing = row.get(symbol)
    if existing is None:
        row[symbol] = value
    elif value not in existing.split(" / "):
        row[symbol] = f"{existing} / {value}"


def parse_tables(lines: List[str], terminals: Set[str], nonterminals: Set[str]):
    states: Dict[int, Dict[str, Dict[str, str]]] = {}
    current_state = None

    state_re = re.compile(r"^State\s+(\d+)\s*$")
    shift_re = re.compile(r"^\s+(\S+)\s+\[?shift, and go to state\s+(\d+)\]?")
    reduce_re = re.compile(r"^\s+(\S+)\s+\[?reduce using rule\s+(\d+)\s+\(([^)]+)\)\]?")
    goto_re = re.compile(r"^\s+(\S+)\s+go to state\s+(\d+)")
    default_reduce_re = re.compile(r"^\s+\$default\s+reduce using rule\s+(\d+)\s+\(([^)]+)\)")
    default_accept_re = re.compile(r"^\s+\$default\s+accept")
    accept_re = re.compile(r"^\s+(\S+)\s+accept")

    for line in lines:
        state_match = state_re.match(line)
        if state_match:
            current_state = int(state_match.group(1))
            states[current_state] = {"action": {}, "goto": {}}
            continue

        if current_state is None:
            continue

        row_action = states[current_state]["action"]
        row_goto = states[current_state]["goto"]

        default_reduce_match = default_reduce_re.match(line)
        if default_reduce_match:
            add_cell(row_action, "$default", f"r{default_reduce_match.group(1)}")
            continue

        if default_accept_re.match(line):
            add_cell(row_action, "$default", "acc")
            continue

        shift_match = shift_re.match(line)
        if shift_match:
            symbol = shift_match.group(1)
            value = f"s{shift_match.group(2)}"
            if symbol in nonterminals:
                add_cell(row_goto, symbol, shift_match.group(2))
            else:
                add_cell(row_action, symbol, value)
            continue

        reduce_match = reduce_re.match(line)
        if reduce_match:
            symbol = reduce_match.group(1)
            add_cell(row_action, symbol, f"r{reduce_match.group(2)}")
            continue

        accept_match = accept_re.match(line)
        if accept_match:
            add_cell(row_action, accept_match.group(1), "acc")
            continue

        goto_match = goto_re.match(line)
        if goto_match:
            symbol = goto_match.group(1)
            target = goto_match.group(2)
            if symbol in nonterminals or symbol not in terminals:
                add_cell(row_goto, symbol, target)
            else:
                add_cell(row_action, symbol, f"s{target}")

    return states


def expand_default_actions(states: Dict[int, Dict[str, Dict[str, str]]], action_symbols: List[str]) -> None:
    """Expand $default entries into concrete ACTION cells for readability.

    For states with "$default = rK", fill every missing terminal column with rK.
    For "$default = acc", only fill $end.
    """
    for state in states.values():
        row_action = state["action"]
        default_value = row_action.get("$default")
        if default_value is None:
            continue

        if default_value == "acc":
            if "$end" in action_symbols and "$end" not in row_action:
                row_action["$end"] = "acc"
            continue

        for symbol in action_symbols:
            if symbol not in row_action:
                row_action[symbol] = default_value


def write_matrix_csv(path: str, states: Dict[int, Dict[str, Dict[str, str]]], key: str, columns: List[str]) -> None:
    with open(path, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["state", *columns])
        for state in sorted(states.keys()):
            row = states[state][key]
            writer.writerow([state, *[row.get(col, "") for col in columns]])


def write_summary(path: str, num_states: int, action_cols: List[str], goto_cols: List[str]) -> None:
    with open(path, "w", encoding="utf-8") as f:
        f.write("# Parsing Table Summary\n\n")
        f.write(f"- Number of states: {num_states}\n")
        f.write(f"- ACTION columns: {len(action_cols)}\n")
        f.write(f"- GOTO columns: {len(goto_cols)}\n\n")

        f.write("## ACTION Columns\n\n")
        for col in action_cols:
            f.write(f"- {col}\n")

        f.write("\n## GOTO Columns\n\n")
        for col in goto_cols:
            f.write(f"- {col}\n")


def write_single_matrix_html(path: str, states: Dict[int, Dict[str, Dict[str, str]]], action_cols: List[str], goto_cols: List[str]) -> None:
    def td(text: str, cls: str = "") -> str:
        class_attr = f' class="{cls}"' if cls else ""
        return f"<td{class_attr}>{html.escape(text)}</td>"

    rows: List[str] = []

    rows.append(
        "<tr>"
        "<th class=\"state-head\"></th>"
        f"<th class=\"section-head action\" colspan=\"{len(action_cols)}\">ACTION</th>"
        f"<th class=\"section-head goto\" colspan=\"{len(goto_cols)}\">GOTO</th>"
        "</tr>"
    )

    header_cells = ["<th class=\"state-head\">State</th>"]
    header_cells.extend([f"<th class=\"col-head action\">{html.escape(col)}</th>" for col in action_cols])
    header_cells.extend([f"<th class=\"col-head goto\">{html.escape(col)}</th>" for col in goto_cols])
    rows.append("<tr>" + "".join(header_cells) + "</tr>")

    for state in sorted(states.keys()):
        action_row = states[state]["action"]
        goto_row = states[state]["goto"]
        cells = [f"<th class=\"state-cell\">{state}</th>"]
        cells.extend([td(action_row.get(col, ""), "action") for col in action_cols])
        cells.extend([td(goto_row.get(col, ""), "goto") for col in goto_cols])
        rows.append("<tr>" + "".join(cells) + "</tr>")

    html_out = f"""<!DOCTYPE html>
<html lang=\"en\">
<head>
    <meta charset=\"utf-8\" />
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />
    <title>Golem LALR(1) Parsing Matrix</title>
    <style>
        :root {{
            --bg: #f7f8f5;
            --paper: #ffffff;
            --ink: #1f2937;
            --muted: #5b6470;
            --line: #d8dee8;
            --action: #0f766e;
            --goto: #7c2d12;
            --accent-soft: #eef7f6;
            --goto-soft: #fff5ef;
        }}
        * {{ box-sizing: border-box; }}
        body {{
            margin: 0;
            font-family: \"IBM Plex Sans\", \"Segoe UI\", sans-serif;
            color: var(--ink);
            background:
                radial-gradient(circle at 20% 0%, #f3f5ea 0%, transparent 40%),
                radial-gradient(circle at 90% 10%, #eef3ff 0%, transparent 35%),
                var(--bg);
        }}
        .wrap {{ max-width: 100%; padding: 20px; }}
        .card {{
            background: var(--paper);
            border: 1px solid var(--line);
            border-radius: 14px;
            box-shadow: 0 8px 28px rgba(15, 23, 42, 0.08);
            overflow: hidden;
        }}
        .head {{ padding: 16px 18px 10px 18px; border-bottom: 1px solid var(--line); }}
        .head h1 {{ margin: 0; font-size: 20px; letter-spacing: 0.2px; }}
        .head p {{ margin: 6px 0 0 0; color: var(--muted); font-size: 13px; }}
        .table-wrap {{ overflow: auto; max-height: calc(100vh - 170px); }}
        table {{ border-collapse: collapse; width: max-content; min-width: 100%; font-size: 12px; }}
        th, td {{ border: 1px solid var(--line); padding: 6px 8px; white-space: nowrap; text-align: center; }}
        .section-head {{ position: sticky; top: 0; z-index: 3; font-size: 13px; letter-spacing: 0.3px; }}
        .section-head.action {{ background: var(--accent-soft); color: var(--action); }}
        .section-head.goto {{ background: var(--goto-soft); color: var(--goto); }}
        .state-head {{ position: sticky; left: 0; top: 0; z-index: 4; background: #f3f4f6; min-width: 72px; }}
        .col-head {{ position: sticky; top: 37px; z-index: 2; font-weight: 600; }}
        .col-head.action {{ background: #f8fcfc; color: #115e59; }}
        .col-head.goto {{ background: #fff9f5; color: #9a3412; }}
        .state-cell {{ position: sticky; left: 0; z-index: 1; background: #f8fafc; }}
        td.action {{ background: #fcfffe; }}
        td.goto {{ background: #fffdfb; }}
        tr:nth-child(odd) td.action {{ background: #f9fdfd; }}
        tr:nth-child(odd) td.goto {{ background: #fffaf7; }}
        .legend {{ padding: 10px 18px 14px 18px; color: var(--muted); font-size: 12px; border-top: 1px solid var(--line); }}
        .legend strong {{ color: var(--ink); }}
    </style>
</head>
<body>
    <div class=\"wrap\">
        <div class=\"card\">
            <div class=\"head\">
                <h1>LALR(1) Parsing Matrix</h1>
                <p>Single matrix view: State | ACTION terminals | GOTO non-terminals</p>
            </div>
            <div class=\"table-wrap\">
                <table>
                    <colgroup>
                        <col style=\"width:72px\" />
                        <col span=\"{len(action_cols)}\" />
                        <col span=\"{len(goto_cols)}\" />
                    </colgroup>
                    <thead>
                        {rows[0]}
                        {rows[1]}
                    </thead>
                    <tbody>
                        {''.join(rows[2:])}
                    </tbody>
                </table>
            </div>
            <div class=\"legend\">
                <strong>States:</strong> {len(states)} &nbsp;|&nbsp;
                <strong>ACTION columns:</strong> {len(action_cols)} &nbsp;|&nbsp;
                <strong>GOTO columns:</strong> {len(goto_cols)}
            </div>
        </div>
    </div>
</body>
</html>
"""

    with open(path, "w", encoding="utf-8") as f:
        f.write(html_out)


def main() -> int:
    if len(sys.argv) != 3:
        usage()
        return 1

    input_path = sys.argv[1]
    output_dir = sys.argv[2]

    if not os.path.exists(input_path):
        print(f"Input file not found: {input_path}")
        return 1

    os.makedirs(output_dir, exist_ok=True)

    with open(input_path, "r", encoding="utf-8", errors="replace") as f:
        lines = f.readlines()

    terminals = parse_symbol_section(lines, "Terminals, with rules where they appear", "Nonterminals, with rules where they appear")
    nonterminals = parse_symbol_section(lines, "Nonterminals, with rules where they appear", "State")

    states = parse_tables(lines, terminals, nonterminals)

    action_cols = sorted(terminals)
    expand_default_actions(states, action_cols)
    action_cols = sorted({symbol for st in states.values() for symbol in st["action"].keys()})
    goto_cols = sorted({symbol for st in states.values() for symbol in st["goto"].keys()})

    write_matrix_csv(os.path.join(output_dir, "action_table.csv"), states, "action", action_cols)
    write_matrix_csv(os.path.join(output_dir, "goto_table.csv"), states, "goto", goto_cols)
    write_summary(os.path.join(output_dir, "parsing_table_summary.md"), len(states), action_cols, goto_cols)
    write_single_matrix_html(os.path.join(output_dir, "parsing_table_matrix.html"), states, action_cols, goto_cols)

    print(f"Generated ACTION table: {os.path.join(output_dir, 'action_table.csv')}")
    print(f"Generated GOTO table: {os.path.join(output_dir, 'goto_table.csv')}")
    print(f"Generated summary: {os.path.join(output_dir, 'parsing_table_summary.md')}")
    print(f"Generated HTML matrix: {os.path.join(output_dir, 'parsing_table_matrix.html')}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
