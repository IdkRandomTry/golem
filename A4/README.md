# A4: Intermediate Code Generation (Quadruples)

Akash Gupta (23110020)

Kaushal Bule (23110160)

Siddhesh Umarjee (23110347)

## Folder Structure

```
A4/
├── README.md                    # This file
├── todo-sidd.md                 # Detailed TODO checklist
├── Makefile                     # A4-specific build configuration
├── golem.y                       # Bison grammar (modified for IR)
├── golem.l                       # Flex lexer
├── tokens.h                      # Token definitions
├── a4.md                         # Assignment specification
├── Makefile.root                 # Backup of root Makefile (reference only)
├── test-case/                    # Test input files
│   └── *.golem                   # GOLEM programs for testing
└── output/                       # Generated outputs (you'll create this)
    ├── a4_demo_*.golem           # 10 demo programs
    ├── ir_output_*.txt           # IR quadruple outputs
    └── ...
```

## IR Output Format

```
Source Program:
===============
[Original GOLEM input]

Generated Intermediate Code (3AC Quadruples):
==============================================
# | op     | arg1  | arg2  | result
--|--------|-------|-------|--------
1 | assign | 5     | -     | t1
2 | add    | t1    | 3     | t2
...
```

## Suggested Steps for Verification

1. Build from a clean state:

```bash
make clean && make
```

2. Verify expression IR (Part 1):

```bash
make test-part1
```

3. Verify control-flow IR (Part 2):

```bash
make test-part2
```

4. Verify diagnostics with line numbers (Part 4):

```bash
make test-part4
```

5. Run all 10 test cases together:

```bash
make test
```

6. Output quality (Part 3):
- IR is printed row-by-row.
- Temporary names are readable (`t1`, `t2`, ...).
- Labels and jumps are visible for control flow.
- Errors are reported as `Parse error at line N: ...`.


## End to End Implementation Details

1. Lexing:
- `golem.l` tokenizes source code into keywords, operators, punctuation, literals, and identifiers.

2. Parsing + SDT:
- `golem.y` parses grammar rules and emits IR during reductions.
- Expression rules emit quadruples for `+`, `-`, `*`, `/`, `%`, unary minus, and assignment-like value moves.

3. IR core:
- Since we are attempting to build a compiler for specifying the behavior of autonomous agents operating within a discrete
two-dimensional grid world, we had to assume we had access to some non-conventional operations, specifically the following:
- create_canvas [arg1] [arg2] -> [-]        :creates a canvas of length arg1 and arg2. (empty result)
- load_golem  [arg1] [arg2] -> [result]     :loads a golem sprite at x=arg1 and y=arg2 on the canvas and sets and stores the id in result
- rot_golem [arg1] [arg2] -> [-]            :sets the rotation value of golem id arg1 to arg2. 0 is North, 90 is East and so on
- mov_x [arg1] [arg2] -> [-]                :moves sprite with id arg1 by arg2 in x direction
- mov_y [arg1] [arg2] -> [-]                :moves sprite with id arg1 by arg2 in x direction
- load_obstacle [arg1] [arg2] -> [-]        :loads an obstacle sprite at x=arg1 and y=arg2 on the canvas


- `ir.c` stores quadruples in insertion order.
- `new_temp()` and `new_label()` generate unique temporaries and labels.
- `emit_quad(op, arg1, arg2, result)` appends one 3AC row.

4. Control flow lowering:
- `if` and `if-else` generate condition checks, `if_false_goto`, `goto`, and `label` quads.
- `repeat` generates loop start/end labels, zero-check, decrement, and back-edge jump.

5. Diagnostics and safety:
- Semantic checks include negative dimensions/coordinates, negative repeat counts, divide-by-zero, and modulo-by-zero.
- Syntax and semantic diagnostics are printed with line numbers.
- On error, parser exits cleanly without crashing.

6. Output stage:
- On successful parse, quadruples are printed in tabular format.
- On failure, diagnostics are printed and allocated IR is cleaned up.

---
