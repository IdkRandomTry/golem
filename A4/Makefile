# A4 Makefile: Intermediate Code Generation (Quadruples)
# Simplified build for A4 IR work only

CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison -d -o y.tab.c

TARGET = golem
LEXER = golem.l
PARSER = golem.y

# ============================================================================
# A4 BUILD TARGETS
# ============================================================================

all: $(TARGET)

$(TARGET): y.tab.h
	$(LEX) $(LEXER)
	$(CC) $(CFLAGS) -o $(TARGET) lex.yy.c y.tab.c ir.c -ll

y.tab.c y.tab.h: $(PARSER)
	$(YACC) $(PARSER)

lex.yy.c: $(LEXER) y.tab.h
	$(LEX) $(LEXER)

# Run all 10 tests (Part 1 + Part 2 + Part 4)
test: test-part1 test-part2 test-part4
	@echo ""
	@echo "==== All 10 tests completed ===="

# Run all Part 1 tests (valid expression/codegen tests)
test-part1: $(TARGET)
	@echo "==== Part 1 Tests (3 files) ===="
	@status=0; \
	for f in \
		test-case/part1-simple.golem \
		test-case/part1-precedence-nested.golem \
		test-case/part1-modulo-unary.golem; do \
			echo ""; \
			echo "Input: $$f"; \
			./$(TARGET) < $$f || status=1; \
		done; \
	exit $$status

# Run all Part 2 tests (valid control-flow/codegen tests)
test-part2: $(TARGET)
	@echo "==== Part 2 Tests (3 files) ===="
	@status=0; \
	for f in \
		test-case/part2-control.golem \
		test-case/part2-nested-repeat-if.golem \
		test-case/part2-branch-with-repeat.golem; do \
			echo ""; \
			echo "Input: $$f"; \
			./$(TARGET) < $$f || status=1; \
		done; \
	exit $$status

# Run all Part 4 tests (error diagnostics, expected failures)
test-part4: $(TARGET)
	@echo "==== Part 4 Tests (4 files, expected parse failures) ===="
	@status=0; \
	for f in \
		test-case/part4-error-grid-negative.golem \
		test-case/part4-error-repeat-negative.golem \
		test-case/part4-error-div-zero.golem \
		test-case/part4-error-syntax-missing-semicolon.golem; do \
			echo ""; \
			echo "Input: $$f"; \
			./$(TARGET) < $$f; \
			ec=$$?; \
			echo "Exit code: $$ec"; \
			if [ $$ec -eq 0 ]; then \
				echo "[FAIL] Expected non-zero exit for diagnostic test"; \
				status=1; \
			fi; \
		done; \
	exit $$status

clean:
	rm -f $(TARGET) lex.yy.c y.tab.c y.tab.h

help:
	@echo ""
	@echo "A4 - Intermediate Code Generation (Quadruples)"
	@echo "======================================"
	@echo ""
	@echo "Targets:"
	@echo "  make        - Build A4 parser"
	@echo "  make test       - Run all 10 tests"
	@echo "  make test-part1 - Run all Part 1 tests (3)"
	@echo "  make test-part2 - Run all Part 2 tests (3)"
	@echo "  make test-part4 - Run all Part 4 tests (4, expected failures)"
	@echo "  make clean  - Remove build artifacts"
	@echo "  make help   - Show this message"
	@echo ""

.PHONY: all clean test test-part1 test-part2 test-part4 help
