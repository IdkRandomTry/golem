# A4 Makefile: Intermediate Code Generation (Quadruples)
# Simplified build for A4 IR work only

CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison -y -d

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
	@echo "Input: test-case/stage3-simple.golem"
	./$(TARGET) < test-case/stage3-simple.golem

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
	@echo "  make clean  - Remove build artifacts"
	@echo "  make help   - Show this message"
	@echo ""

.PHONY: all clean test stage3-test help
