# Q6: Additional Information

This document consolidates execution instructions and implementation/parser-analysis notes for all assignment parts (Q1-Q5).

## Prerequisites

Install required tools:

```bash
sudo apt-get update
sudo apt-get install -y bison flex gcc make python3 graphviz
```

Run commands from repository root unless specified:

```bash
cd /mnt/d/Academics/Sem6/Compilers/golem-A3
```

## Added Language Constructs (Operators and Else)

This section highlights grammar support that should be called out explicitly in reports.

### Integer-Modification Operators

The grammar supports integer arithmetic in `expr`, enabling value modification through:

- Addition: `expr PLUS expr`
- Subtraction: `expr MINUS expr`
- Multiplication: `expr MULTIPLY expr`
- Division: `expr DIVIDE expr`
- Modulo: `expr MODULO expr`
- Unary minus: `MINUS expr %prec UMINUS`

Implementation notes:

- Operator precedence is defined as:
  - `%left PLUS MINUS`
  - `%left MULTIPLY DIVIDE MODULO`
  - `%right UMINUS`
- Runtime semantic checks are included for division/modulo by zero.
- These operators are used in numeric contexts such as movement steps, coordinates, and repeat counts.

### Else Statements

`if`/`else` handling is explicitly supported and disambiguated in the grammar:

- `IF '(' condition ')' stmt %prec THEN`
- `IF '(' condition ')' stmt ELSE stmt`

Implementation notes:

- Lexer recognizes `else` and `then` keywords and returns `ELSE`/`THEN` tokens.
- Parser resolves dangling-else ambiguity with:
  - `%nonassoc THEN`
  - `%nonassoc ELSE`
  - `%prec THEN` on the `if-without-else` production
- Effect: `ELSE` binds to the nearest unmatched `IF`, and Q2 has 0 conflicts.

## Q1: LALR(1) With Conflicts

### Execute

```bash
# Build conflicting grammar using Makefile target
make Q1

# Regenerate Bison report directly (shows warnings)
cd Q1_LALR_With_Conflicts
bison -v -d golem_with_conflicts.y
flex golem.l
gcc -Wall -g -o golem_with_conflicts lex.yy.c y.tab.c -ll

# Optional: visualize automaton from DOT
dot -Tpng automaton.dot -o automaton.png
```

### Implementation Notes

- Grammar file: `Q1_LALR_With_Conflicts/golem_with_conflicts.y`
- This version intentionally keeps ambiguity to demonstrate conflict analysis.
- Outputs include state transitions (`state_table.txt`) and automaton graph (`automaton.dot`).

### Parser Analysis

- States: 132 (from `golem_with_conflicts.output`)
- Conflicts:
  - State 102: 1 shift/reduce (dangling else)
  - State 107: 9 reduce/reduce (block ambiguity)
- Total conflicts: 10

## Q2: Conflict Resolution

### Execute

```bash
# Build resolved grammar using Makefile target
make Q2

# Direct build inside Q2
cd Q2_Conflict_Resolution
bison -v -d golem.y
flex golem.l
gcc -Wall -g -o golem golem.tab.c lex.yy.c -lfl

# Run provided tests
./golem < test-examples/test1_dangling_else.golem
./golem < test-examples/test2_repeat_block.golem
```

### Implementation Notes

- Grammar file: `Q2_Conflict_Resolution/golem.y`
- Dangling else resolved via precedence/associativity strategy (`THEN`/`ELSE`).
- Block ambiguity resolved by restructuring repeated-block productions.

### Parser Analysis

- States: 128 (from `Q2_Conflict_Resolution/golem.output`)
- Conflicts: 0
- Compared to Q1: conflicts removed and parser simplified by 4 states.

## Q3: Reverse Derivation

### Execute

```bash
cd Q3_Reverse_Derivation
bison -y -d golem.y
flex golem.l
gcc -Wall -g -o golem y.tab.c lex.yy.c -ll

# Run on any test
./golem < ../test-case/simple_test.golem
```

### Implementation Notes

- Parser actions record every reduction in a derivation list.
- After successful parse, reductions are printed as reverse derivation steps.
- Includes memory cleanup for derivation nodes.

### Parser Analysis

- Demonstrates bottom-up parsing behavior explicitly.
- Helps map reductions back to grammar rule numbers and parsing sequence.
- Useful for debugging shift/reduce behavior and validating grammar actions.

## Q4: Parsing Table Output

### Execute

```bash
# From repository root
python3 Q4_Parsing_Table/parsing_table.py golem.output Q4_Parsing_Table/

# Or from inside Q4 folder
cd Q4_Parsing_Table
python3 parsing_table.py ../golem.output .
```

### Generated Files

- `action_table.csv`
- `goto_table.csv`
- `parsing_table_summary.md`
- `parsing_table_matrix.html`

### Implementation Notes

- Script parses terminal/nonterminal sections from Bison `.output`.
- Extracts ACTION and GOTO entries state-wise.
- Handles default actions (`$default`) and expands them for readability.
- Produces both machine-readable (CSV) and human-readable (Markdown/HTML) outputs.

### Parser Analysis

- Uses resolved grammar output (`golem.output`) with 128 states and no conflicts.
- Final matrix view makes ACTION and GOTO transitions explicit for each state.

## Q5: Error Diagnostics

### Execute

```bash
cd Q5_Error_Diagnostics
bison -d golem.y
flex golem.l
gcc -Wall -g -o golem golem.tab.c lex.yy.c -lfl

# Run diagnostics test
./golem < test_errors.golem
```

### Implementation Notes

- Enhanced diagnostic functions categorize syntax errors, semantic errors, and warnings.
- Lexer tracks line numbers to report exact locations.
- Error recovery productions allow continued parsing after failures.

### Parser Analysis

- Improves parser usability by reporting multiple errors in one run.
- Diagnostic flow separates parse-phase and semantic-phase issues.
- Recovery strategy reduces cascading failures and improves debugging quality.

## Quick Comparison Summary

| Question | States | Conflicts | Focus |
|---|---:|---:|---|
| Q1 | 132 | 10 | Demonstrate ambiguity and conflict states |
| Q2 | 128 | 0 | Conflict elimination and stable grammar |
| Q3 | Based on selected grammar | Depends on grammar | Reverse derivation tracking |
| Q4 | 128 (using root output) | 0 | ACTION/GOTO matrix extraction/export |
| Q5 | Based on selected grammar | Depends on grammar | Error reporting and recovery |

## Suggested Verification Workflow

```bash
# 1) Confirm Q1 conflicts exist
cd Q1_LALR_With_Conflicts
bison -v -d golem_with_conflicts.y

# 2) Confirm Q2 conflicts are resolved
cd ../Q2_Conflict_Resolution
bison -v -d golem.y

# 3) Generate parsing-table artifacts from resolved output
cd ..
python3 Q4_Parsing_Table/parsing_table.py golem.output Q4_Parsing_Table/

# 4) Run diagnostics tests
cd Q5_Error_Diagnostics
./golem < test_errors.golem
```
