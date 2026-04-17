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

# Run basic test suite
test: $(TARGET)
	@echo "==== A4 Testing: Expression IR ===="
	@echo "Test 1: Simple addition"
	@echo 'grid(5,5) {} blueprint t1 { go 1 + 2; } construct { spawn t1 at (0,0); }' | ./$(TARGET)
	@echo ""
	@echo "Test 2: Precedence (mult before add)"
	@echo 'grid(5,5) {} blueprint t2 { go 2 + 3 * 4; } construct { spawn t2 at (0,0); }' | ./$(TARGET)
	@echo ""
	@echo "Test 3: Unary minus"
	@echo 'grid(5,5) {} blueprint t3 { go -5; } construct { spawn t3 at (0,0); }' | ./$(TARGET)
	@echo ""

# Focused Stage 3 test (expressions only)
part1-test: $(TARGET)
	@echo "==== Stage 3 Simple Test ===="
	@echo "Input: test-case/part1-simple.golem"
	./$(TARGET) < test-case/part1-simple.golem

# Focused Stage 4 test (control flow)
part2-test: $(TARGET)
	@echo "==== Stage 4 Control-Flow Test ===="
	@echo "Input: test-case/part2-control.golem"
	./$(TARGET) < test-case/part2-control.golem

# Focused Part 4 tests (error diagnostics)
part4-test: $(TARGET)
	@echo "==== Part 4 Error Diagnostics Tests ===="
	@set +e; \
	for f in \
		test-case/part4-error-grid-negative.golem \
		test-case/part4-error-repeat-negative.golem \
		test-case/part4-error-div-zero.golem \
		test-case/part4-error-syntax-missing-semicolon.golem; do \
			echo ""; \
			echo "Input: $$f"; \
			./$(TARGET) < $$f; \
			echo "Exit code: $$?"; \
		done

clean:
	rm -f $(TARGET) lex.yy.c y.tab.c y.tab.h

help:
	@echo ""
	@echo "A4 - Intermediate Code Generation (Quadruples)"
	@echo "======================================"
	@echo ""
	@echo "Targets:"
	@echo "  make        - Build A4 parser"
	@echo "  make test   - Run test suite"
	@echo "  make part1-test - Run focused Stage 3 expression test"
	@echo "  make part2-test - Run focused Stage 4 control-flow test"
	@echo "  make part4-test - Run focused Part 4 diagnostics tests"
	@echo "  make clean  - Remove build artifacts"
	@echo "  make help   - Show this message"
	@echo ""

.PHONY: all clean test stage3-test part1-test part2-test part4-test help
