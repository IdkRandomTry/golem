# Part 4: Parsing Table Output (2.5 marks)

## Overview

This part generates the LALR(1) parsing table in matrix (tabular) form from a Bison `.output` file and exports it to CSV, Markdown summary, and HTML.

## Features

1. **LALR(1) Parsing Table Extraction**: 
   - Parses the Bison `.output` file to extract parsing table information
   - Identifies all states, terminals, and nonterminals
   - Extracts ACTION and GOTO entries

2. **Matrix Format Display**:
   - Produces separate ACTION and GOTO matrices as CSV
   - Produces a combined matrix as an HTML table (single view)
   - Uses standard parser-table notation (`sN`, `rN`, `acc`)
   - Follows lecture slide conventions for ACTION/GOTO separation

3. **Table Statistics**:
   - Total number of states
   - Number of terminals
   - Number of nonterminals

## Implementation

### Python Script: `parsing_table.py`

A Python script that:
- Reads the Bison `.output` file
- Parses state information using regular expressions
- Expands `$default` actions for readability
- Writes ACTION/GOTO tables and a combined HTML matrix

### Usage

```bash
cd Q4_Parsing_Table

# Run with explicit input and output directory
python3 parsing_table.py ../golem.output .

# Alternative: from repository root
python3 Q4_Parsing_Table/parsing_table.py golem.output Q4_Parsing_Table/
```

Expected generated files:
- `action_table.csv`
- `goto_table.csv`
- `parsing_table_summary.md`
- `parsing_table_matrix.html`

## Table Format

### ACTION Section
- Rows: Parser states (0, 1, 2, ...)
- Columns: Terminal symbols
- Entries:
  - `sN`: Shift and go to state N
  - `rN`: Reduce using rule N
  - `acc`: Accept
  - Empty: Error

### GOTO Section
- Rows: Parser states (0, 1, 2, ...)
- Columns: Nonterminal symbols
- Entries:
  - `N`: Go to state N
  - Empty: Not applicable

## Sample Summary Output

```
# Parsing Table Summary

- Number of states: 128
- ACTION columns: 47
- GOTO columns: 23
```

Console output from the script prints generated file paths rather than rendering the full table directly in terminal.

## Technical Details

### Parsing Algorithm

1. **Extract Grammar Information**:
   - Find Grammar section to identify nonterminals
   - Find Terminals section for terminal list

2. **Parse State Information**:
   - Use regex to find all state blocks
   - Extract shift actions: `token shift ... state N`
   - Extract reduce actions: `token reduce using rule N`
   - Extract accept actions
   - Extract goto transitions

3. **Generate Outputs**:
   - Write ACTION matrix to `action_table.csv`
   - Write GOTO matrix to `goto_table.csv`
   - Write column/state statistics to `parsing_table_summary.md`
   - Write combined matrix view to `parsing_table_matrix.html`

### Regex Patterns Used

- States: `State\s+(\d+)(.*?)(?=State\s+\d+|$)`
- Shifts: `\s+(\S+)\s+\[?shift, and go to state\s+(\d+)\]?`
- Reduces: `\s+(\S+)\s+\[?reduce using rule\s+(\d+)\s+\(([^)]+)\)\]?`
- Gotos: `(\w+)\s+go to state\s+(\d+)`
- Defaults: `$default reduce using rule ...` and `$default accept`

## Comparison with Lecture Slides

This implementation follows the standard format taught in compiler courses:

1. **Two-part table**: Separate ACTION and GOTO data exports
2. **State-based rows**: Each row represents a parser state
3. **Symbol-based columns**: Terminals in ACTION, nonterminals in GOTO
4. **Standard notation**: `sN`, `rN`, `acc` for actions
5. **Clear visual structure**: Combined matrix available as HTML

## Files

- `parsing_table.py`: Main script for table extraction and display
- `README.md`: This documentation
- `action_table.csv`: ACTION matrix export
- `goto_table.csv`: GOTO matrix export
- `parsing_table_summary.md`: Summary statistics and column lists
- `parsing_table_matrix.html`: Combined ACTION+GOTO matrix (single view)
- `../golem.output`: Generated Bison output file (used as input)

## Dependencies

- Python 3.x
- Bison (to generate `.output` file)
