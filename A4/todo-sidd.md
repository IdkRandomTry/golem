# TODO for A4 (Intermediate Code Generation)

Project stage used for this TODO:
- Q1 to Q5 already implemented (conflict analysis, conflict resolution, reverse derivation, parsing table, diagnostics).
- A4 now requires IR generation in quadruple format on top of the current parser pipeline.

## 1) Baseline Check Before IR Work

- [ ] Run a clean baseline build.
- [ ] Confirm existing parser tests pass before adding IR logic.
- [ ] Save baseline outputs for comparison.

Testing tips:
- Use WSL workflow used in this project.
- Run:
  - `make clean && make`
  - `make test`
- If anything fails here, fix baseline first. Do not start IR changes yet.

Pass criteria:
- Root build succeeds.
- Existing sample tests run without new errors.

---

## 2) Add IR Core Data Structures

- [ ] Add quadruple struct: `op, arg1, arg2, result`.
- [ ] Add `emit_quad(...)` helper.
- [ ] Add temporary generator: `t1, t2, t3...`.
- [ ] Add label generator placeholder: `L1, L2, L3...`.

Testing tips:
- Before grammar integration, emit a few dummy quads from a controlled path.
- Verify temp names increase strictly and never repeat.

Pass criteria:
- Quad list stores rows in insertion order.
- Temp and label counters are deterministic.

---

## 3) Expression IR (A4 Part 1)

- [ ] Generate quads for literals and identifiers.
- [ ] Add unary minus codegen.
- [ ] Add binary ops: `+ - * / %`.
- [ ] Ensure precedence follows grammar declarations.

Testing tips:
- Add one focused test per operator before mixing operators.
- Use expressions that force precedence validation.

Suggested test inputs:
1. `go 1 + 2;`
2. `go 8 - 3;`
3. `go 2 * 5;`
4. `go 9 / 3;`
5. `go 10 % 3;`
6. `go -5;`
7. `go 2 + 3 * 4;` (precedence check)
8. `go (2 + 3) * 4;` (parentheses check)

Pass criteria:
- Output quads reflect grammar precedence/associativity.
- Unary minus creates expected intermediate value/temp.
- Division/modulo by zero handled via diagnostics path.

---

## 4) Statement-Level IR Hooks

- [ ] Attach expression IR to statement actions that need numeric evaluation.
- [ ] Keep parse actions clean (avoid mixing too much printing logic in grammar rules).
- [ ] Ensure no quads emitted for invalid/recovered fragments.

Testing tips:
- Start with small statements and gradually combine into blocks.
- Verify generated IR count roughly matches expected operation count.

Pass criteria:
- Valid statements emit quads.
- Broken statements do not crash parser or codegen.

---

## 5) Control Flow IR (A4 Part 2)

- [ ] Implement labels and jumps for `if`.
- [ ] Implement labels and jumps for `if-else`.
- [ ] Implement loop control flow for `repeat` (or loop construct present in grammar).
- [ ] Support nesting (if inside repeat, repeat inside if-else).

Testing tips:
- Test each control construct alone first.
- Then test nested combinations to catch wrong jump targets.

Suggested tests:
1. Simple `if` with one statement.
2. `if-else` where both branches emit code.
3. `repeat 3 { go 1; }`
4. Nested `if` inside `repeat`.

Pass criteria:
- Every jump target label exists exactly once.
- Control-flow order is correct (no dead/missing branch due to wrong label placement).

---

## 6) Output Formatting (A4 Part 3)

- [ ] Print source program section clearly.
- [ ] Print IR in strict tabular row-by-row order.
- [ ] Use readable temp naming (`t1`, `t2`, ...).
- [ ] Keep column headers consistent.

Recommended table columns:
- `# | op | arg1 | arg2 | result`

Testing tips:
- Try long identifiers and nested expressions to ensure alignment/readability.
- Verify no row is skipped or duplicated.

Pass criteria:
- Evaluator can visually map source to generated quads.
- Quad table is stable and readable across all test files.

---

## 7) Diagnostics During Codegen (A4 Part 4)

- [ ] Detect unsupported constructs in codegen phase.
- [ ] Detect invalid expression trees reaching codegen.
- [ ] Print meaningful messages and continue safely when possible.
- [ ] Avoid crash on malformed input.

Testing tips:
- Use malformed arithmetic and incomplete statements.
- Confirm parser recovery + codegen skip strategy works.

Pass criteria:
- Errors are explicit and actionable.
- Process does not terminate abruptly on first bad construct.

---

## 8) Build the Required 10 A4 Demo Programs

- [ ] Prepare 10 small GOLEM programs for codegen demonstration.
- [ ] Cover all required categories (simple expressions, assignments if supported, control flow, errors).
- [ ] Keep each file focused on one feature.

Coverage checklist for 10 files:
- [ ] arithmetic add/sub
- [ ] mul/div/mod
- [ ] unary minus
- [ ] precedence + parentheses
- [ ] conditional (`if`)
- [ ] conditional (`if-else`)
- [ ] loop (`repeat`)
- [ ] nested control flow
- [ ] one semantic error case
- [ ] one syntax/unsupported case

Testing tips:
- Maintain expected-output notes for each file.
- Name files by feature to simplify demo.

Pass criteria:
- Exactly 10 examples shown with source + IR output.
- All A4 mandatory points are visibly covered.

---

## 9) Regression Against Existing Stages

- [ ] Re-run previous milestone checks after IR integration.
- [ ] Confirm Q2 conflict-free grammar behavior remains unchanged.
- [ ] Confirm Q5 diagnostics are still working.

Testing tips:
- Re-run:
  - `make clean && make test`
  - Q2 sample tests
  - Q5 `test_errors.golem`
- Compare against baseline outputs where relevant.

Pass criteria:
- No regressions in previously completed parts.

---

## 10) Final Submission Packaging

- [ ] Document end-to-end flow: lex -> parse -> IR emit -> print table.
- [ ] Add command list for evaluator reproduction.
- [ ] Add one worked example with explanation of generated quads.
- [ ] Confirm team contribution notes are included.

Testing tips:
- Do a dry run exactly as evaluator would.
- Time the full run so demo stays smooth.

Pass criteria:
- Repo is self-explanatory and reproducible.
- A4 rubric points can be checked quickly by reading docs + outputs.

---

## Suggested Execution Order (Fast Path)

1. Baseline verify
2. IR core (quad/temp/label)
3. Expression IR
4. Control-flow IR
5. Output formatting
6. Diagnostics hardening
7. 10 demo programs + expected outputs
8. Full regression + final docs

---

## Quick Tracker

- [ ] Part 1: IR core + basic expressions
- [ ] Part 2: control flow + formatting
- [ ] Part 3: diagnostics + 10 demos
- [ ] Part 4: regression + submission polish
