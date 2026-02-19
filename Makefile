CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison -y -d

TARGET = golem
LEXER = golem.l
PARSER = golem.y

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
	./$(TARGET) < test-case/spawn-and-move.golem
	@echo "Testing lexer with comments.golem..."
	./$(TARGET) < test-case/comments.golem

clean:
	rm -f $(TARGET) lex.yy.c y.tab.c y.tab.h

.PHONY: all clean test
