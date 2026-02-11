CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison -y -d

TARGET = golem
LEXER = golem.l
PARSER = golem.y
TESTCASE_DIR = "test case"

all: $(TARGET)

$(TARGET): y.tab.h
	$(LEX) $(LEXER)
	$(CC) $(CFLAGS) -o $(TARGET) lex.yy.c -ll

y.tab.c y.tab.h: $(PARSER)
	$(YACC) $(PARSER)

lex.yy.c: $(LEXER) y.tab.h
	$(LEX) $(LEXER)

test: $(TARGET)
	@echo "Testing lexer with spawn-and-move.golem..."
	./$(TARGET) $(TESTCASE_DIR)/spawn-and-move.golem

clean:
	rm -f $(TARGET) lex.yy.c y.tab.c y.tab.h

.PHONY: all clean test
