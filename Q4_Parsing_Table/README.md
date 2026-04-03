# Part 4: Parsing Table Output (2.5 marks)

## Overview

This part outputs the LALR(1) parsing table in matrix (tabular) format, following the structure used in compiler course lecture slides.

## Features

1. **LALR(1) Parsing Table Extraction**: 
   - Parses the Bison `.output` file to extract parsing table information
   - Identifies all states, terminals, and nonterminals
   - Extracts ACTION and GOTO entries

2. **Matrix Format Display**:
   - Displays ACTION table (terminal columns)
   - Displays GOTO table (nonterminal columns)
   - Uses box-drawing characters for clear tabular format
   - Follows lecture slide format conventions

3. **Table Statistics**:
   - Total number of states
   - Number of terminals
   - Number of nonterminals

## Implementation

### Python Script: `parsing_table.py`

A Python script that:
- Reads the Bison `.output` file
- Parses state information using regular expressions
- Formats the parsing table in matrix form
- Displays ACTION and GOTO sections separately

### Usage

```bash
cd Q4_Parsing_Table

# Run with default file (../golem.output)
python3 parsing_table.py

# Run with specific file
python3 parsing_table.py path/to/file.output
```

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

## Sample Output

```
╔════════════════════════════════════════════════════════════════╗
║                    LALR(1) PARSING TABLE                       ║
╠════════════════════════════════════════════════════════════════╣
║ States: 128   Terminals: 40   Nonterminals: 24                ║
╚════════════════════════════════════════════════════════════════╝

┌──────┬───────────────────────────────────────────────────────┐
│STATE │                    ACTION                             │
├──────┼───────┬───────┬───────┬───────┬───────┬...            │
│      │ $end  │  AS   │  AT   │ BLUE  │ CONST │...            │
├──────┼───────┼───────┼───────┼───────┼───────┼...            │
│  0   │  acc  │       │       │       │       │...            │
│  1   │  acc  │       │       │  s4   │  s5   │...            │
│  2   │  acc  │       │       │       │       │...            │
...
└──────┴───────┴───────┴───────┴───────┴───────┴...            ┘

┌──────┬───────────────────────────────────────────────────────┐
│STATE │                    GOTO                               │
├──────┼────────┬──────┬──────┬──────┬──────┬...               │
│      │program │ stmt │ expr │ decl │ list │...               │
├──────┼────────┼──────┼──────┼──────┼──────┼...               │
│  0   │   1    │      │      │      │      │...               │
│  1   │        │  2   │      │      │      │...               │
...
└──────┴────────┴──────┴──────┴──────┴──────┴...               ┘

Legend:
  sN  = shift and go to state N
  rN  = reduce using rule N
  acc = accept
  N   = goto state N (in GOTO section)
```

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

3. **Format Output**:
   - Calculate column widths dynamically
   - Create box-drawing table structure
   - Align entries for readability

### Regex Patterns Used

- States: `State\s+(\d+)(.*?)(?=State\s+\d+|$)`
- Shifts: `(\w+|\$end)\s+shift.*?state\s+(\d+)`
- Reduces: `(\w+|\$end)\s+reduce using rule\s+(\d+)`
- Gotos: `(\w+)\s+go to state\s+(\d+)`

## Comparison with Lecture Slides

This implementation follows the standard format taught in compiler courses:

1. **Two-part table**: Separate ACTION and GOTO sections
2. **State-based rows**: Each row represents a parser state
3. **Symbol-based columns**: Terminals in ACTION, nonterminals in GOTO
4. **Standard notation**: `sN`, `rN`, `acc` for actions
5. **Clear visual structure**: Box characters for table borders

## Files

- `parsing_table.py`: Main script for table extraction and display
- `README.md`: This documentation
- `../golem.output`: Generated Bison output file (used as input)

## Dependencies

- Python 3.x
- Bison (to generate `.output` file)
