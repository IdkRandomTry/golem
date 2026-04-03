# Q2: Conflict Resolution

This folder contains the resolved grammar with 0 conflicts and demonstrates how the conflicts were fixed.

## Part 2 (10 Marks): Conflict Identification and Resolution

### Resolution Achieved
- **All 10 conflicts eliminated** (10 → 0)
- Dangling else: Fixed with `%prec THEN/ELSE`
- Block ambiguity: Fixed with `compound_stmt` restructuring

### Files in this folder

#### Documentation
- `A3-ConflictResolution.pdf` - Complete Part 2 analysis 
  - Clear explanation of conflicts
  - Grammar modifications
  - Resolution mechanisms
  - Before/after examples

#### Resolved Grammar
- `golem.y` - **Final working grammar** (0 conflicts) ✓
- `golem.l` - **Lexer** (with ELSE, THEN tokens)
- `golem.output` - Bison output (clean, no conflicts)
- `golem.tab.c` - Generated C parser
- `golem.tab.h` - Generated header

#### Alternative Names (same files)
- `golem_fixed.y` - Same as golem.y
- `golem_fixed.output` - Same as golem.output
- `golem_fixed.tab.c` - Same as golem.tab.c
- `golem_fixed.tab.h` - Same as golem.tab.h

#### Test Cases
- `test-examples/test1_dangling_else.golem` - Nested if-else test
- `test-examples/test2_repeat_block.golem` - Repeat loop test

### Building

```bash
# Build the resolved grammar (no warnings!)
bison -v -d golem.y

# Compile with lexer
bison -d golem.y
flex golem.l
gcc -o golem golem.tab.c lex.yy.c -lfl

# Expected output: Clean build, 0 conflicts ✓
```

### Test the Parser

```bash
# Run test cases
./golem < test-examples/test1_dangling_else.golem
./golem < test-examples/test2_repeat_block.golem
```

### Comparison with Q1

| Metric | Q1 (With Conflicts) | Q2 (Resolved) |
|--------|---------------------|---------------|
| S/R Conflicts | 1 | 0 ✓ |
| R/R Conflicts | 9 | 0 ✓ |
| Total | 10 | 0 ✓ |
| Useless Rules | 1 | 0 ✓ |
| Repeat Loops | BROKEN | WORKS ✓ |
| IF-ELSE | Implicit | Explicit ✓ |

### Final Working Files

The files `golem.y` and `golem.l` in this folder are the **final working versions** of the parser and lexer. These same files are also copied to the root directory for easy access.
