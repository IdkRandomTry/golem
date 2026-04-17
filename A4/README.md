# A4: Intermediate Code Generation (Quadruples)

This folder is your complete working directory for A4 - Intermediate Code Generation.

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

## Quick Start

1. **Build the parser:**
   ```bash
   cd A4
   make clean && make
   ```

2. **Run tests:**
   ```bash
   make test
   ```

3. **Test a specific input:**
   ```bash
   ./golem < test-case/spawn-and-move.golem
   ```

## Work Plan (from todo-sidd.md)

You're implementing IR generation in 10 stages:

1. ✓ Baseline Check (verify current parser works)
2. → Add IR Core Data Structures (quad struct, temp/label gen)
3. → Expression IR (operators, precedence)
4. → Statement-Level IR
5. → Control Flow IR (if, repeat, labels)
6. → Output Formatting (tabular quadruples)
7. → Diagnostics (error handling during codegen)
8. → 10 Demo Programs (required test suite)
9. → Regression Testing
10. → Final Submission

See `todo-sidd.md` for detailed step-by-step instructions and testing tips.

## Key Files You'll Modify

- **golem.y** - Add IR emission actions to parser rules
- **golem.l** - Keep minimal changes (lexer is complete)
- **tokens.h** - May add IR/quad related tokens if needed

## Expected IR Output Format

Per assignment spec (A4.md), your output should be:

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

## Assignment Requirements (from a4.md)

- **Part 1 (7 marks):** Arithmetic expressions in quadruple format
- **Part 2 (7 marks):** Control flow (if, if-else, repeat, labels)
- **Part 3 (3 marks):** Tabular output format
- **Part 4 (3 marks):** Error diagnostics
- **Bonus:** 10 demo programs showing all features

## Testing Your Work

As you implement each stage:

1. **Unit test** - Test one feature at a time (one operator, one control struct)
2. **Integration test** - Combine features (nested if in repeat)
3. **End-to-end** - Run all 10 demo programs
4. **Regression** - Verify Q1-Q5 still work (use root directory for this)

## Debugging Tips

- Compile with `-g` (already in Makefile)
- Use `gdb` to step through parser actions
- Print intermediate quads as they're emitted
- Validate quad numbering is sequential
- Check temp/label counter uniqueness

## File References

- Assignment spec: `a4.md`
- Previous work spec: `Makefile.root` (Q1-Q5 targets still available in root)
- Language spec: `../README.md`
- Grammar status: `../Q6_Additional_Info/README.md`

## Submission Checklist

Before submitting from A4/:

- [ ] All 10 demo programs present
- [ ] Each demo has corresponding IR output
- [ ] Quadruple format is consistent and readable
- [ ] Error handling works on malformed input
- [ ] Documentation in `a4.md` is complete
- [ ] Team member contributions are documented

---

**Start working:** Read `todo-sidd.md`, then implement stage 2 (IR Core Data Structures) in `golem.y`.
