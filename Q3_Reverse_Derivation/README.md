# Part 3: Reverse Derivation Tree (2.5 marks)

## Overview

This implementation stores and displays the derivation tree generated during parsing in **reverse order** (bottom-up).

## Features

1. **Derivation Tree Storage**: 
   - Each grammar production reduction is recorded during parsing
   - Productions are stored in a linked list with rule numbers
   - Total of 57 unique production rules tracked

2. **Reverse Display**:
   - After successful parsing, the derivation tree is displayed in reverse order
   - Shows bottom-up construction (how parser builds the parse tree)
   - Each step is numbered and labeled with the production rule

3. **Data Structure**:
   ```c
   typedef struct DerivationNode {
       char *production;    // Production rule description
       int rule_num;        // Rule number
       struct DerivationNode *next;
   } DerivationNode;
   ```

## Implementation Details

### Functions

- `add_derivation(rule_desc, rule_num)`: Records a derivation step
- `display_reverse_derivation()`: Displays the tree in reverse order
- `free_derivations()`: Cleans up allocated memory

### Production Rules Tracked

All 57 grammar productions are tracked, including:
- Program structure (rules 1-2)
- Statements (rules 3-6)
- Grid declarations (rules 7-10)
- Blueprint definitions (rule 11)
- Spawn statements (rules 15-16)
- Control flow (if-else, repeat)
- Expressions (arithmetic operations)
- And more...

## Building and Running

### Compile:
```bash
cd Q3_Reverse_Derivation
bison -d golem.y
flex golem.l
gcc -o golem y.tab.c lex.yy.c -lfl
```

### Run:
```bash
./golem < ../test-case/example.golem
```

Or using the Makefile:
```bash
make Q3
./Q3_Reverse_Derivation/golem < test-case/example.golem
```

## Sample Output

```
╔════════════════════════════════════════════════════════════════╗
║             GOLEM Parser - Part 3: Derivation Tree            ║
╚════════════════════════════════════════════════════════════════╝

  Grid: 10 x 10

╔════════════════════════════════════════════════════════════════╗
║                     Parsing Successful!                        ║
╚════════════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════════════╗
║           REVERSE DERIVATION TREE (Bottom-Up)                 ║
╠════════════════════════════════════════════════════════════════╣
║ Total Derivation Steps: 15                                    ║
╚════════════════════════════════════════════════════════════════╝

[Step   1/15] Rule 50: expr → INTEGER
[Step   2/15] Rule 50: expr → INTEGER
[Step   3/15] Rule  8: obstacle_list → ε
[Step   4/15] Rule  7: grid_decl → GRID '(' expr ',' expr ')' '{' obstacle_list '}'
[Step   5/15] Rule  3: statement → grid_decl
...
```

## Key Points

- **Reverse order**: Shows how the parser reduces (bottom-up parsing)
- **Complete trace**: Every production application is recorded
- **Rule numbering**: Helps identify which grammar rule was applied
- **Memory management**: Proper allocation and deallocation
