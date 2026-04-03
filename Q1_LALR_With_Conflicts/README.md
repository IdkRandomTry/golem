# Q1: LALR(1) Automaton with Conflicts

## Part 1 (10 Marks): Construction of LALR(1) Automaton

### Conflicts
- **State 102**: 1 Shift/Reduce conflict (Dangling Else)
- **State 107**: 9 Reduce/Reduce conflicts (Block Ambiguity)
- **Total**: 10 conflicts

### Files in this folder

#### Documentation

The Documentation folder is just for testing purposes. The main documentation is in the root directory as `A3-ConflictSummary.pdf`.

#### Report
- `A3-ConflictSummary.pdf` - Complete Part 1 analysis
  - LALR(1) item sets
  - Complete automaton structure
  - Detailed conflict identification
  - Exact productions involved

#### Grammar with Conflicts
- `golem_with_conflicts.y` - Bison grammar file (WITH conflicts)
- `golem_with_conflicts.output` - Bison verbose output showing conflicts
- `golem_with_conflicts.tab.c` - Generated C parser
- `golem_with_conflicts.tab.h` - Generated header

#### Analysis Files
- `state_table.txt` - State transition table (14K)

#### Visualizations
- `automaton.dot` - Graphviz DOT file for full automaton
- `automaton.png` - Visual representation (8.4MB, 132 states)

### Building
```bash
# Build the grammar (will show conflict warnings)
bison -v -d golem_with_conflicts.y

# Expected output:
#   warning: 1 shift/reduce conflict
#   warning: 9 reduce/reduce conflicts
```

### View Visualizations

```bash
# View automaton diagram
xdg-open automaton.png  # or your image viewer

# Regenerate from DOT
dot -Tpng automaton.dot -o automaton.png
```

### Next Steps

See `../Q2_Conflict_Resolution/` for the resolved grammar with 0 conflicts.
