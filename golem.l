D   [0-9]
L   [a-z]
A   [a-zA-Z_0-9]
ID  {L}{A}*
WS  [ \t\v\n\f]

%{
#include <stdio.h>
#include "y.tab.h"
#include "tokens.h"

static void comment(void);
%}

%%
"/*"					{ comment(); }
"//".*                    		{ /* consume //-comment */ }

"grid"					{ return(GRID); }
"obstacle"				{ return(OBSTACLE); }
"blueprint"				{ return(BLUEPRINT); }
"construct"				{ return(CONSTRUCT); }
"spawn"					{ return(SPAWN); }
"at"					{ return(AT); }
"as"					{ return(AS); }
"go"					{ return(GO); }
"turn"					{ return(TURN); }
"scan"					{ return(SCAN); }
"pick"					{ return(PICK); }
"drop"					{ return(DROP); }
"if"					{ return(IF); }
"repeat"				{ return(REPEAT); }
"north"					{ return(NORTH); }
"south"					{ return(SOUTH); }
"east"					{ return(EAST); }
"west"					{ return(WEST); }
"true"					{ return(TRUE); }
"false"					{ return(FALSE); }

{ID}					{ return(IDENTIFIER); }

{D}+					{ return(INTEGER); }

\"[^\"]*\"				{ return(STRING_LITERAL); }

">>"					{ return(EAST_SCAN); }
"<<"					{ return(WEST_SCAN); }
"^^"					{ return(NORTH_SCAN); }
"vv"					{ return(SOUTH_SCAN); }

"=="					{ return(EQ_OP); }
"!="					{ return(NE_OP); }
";"					{ return ';'; }
"{"					{ return '{'; }
"}"					{ return '}'; }
","					{ return ','; }
"("					{ return '('; }
")"					{ return ')'; }
"?"					{ return '?'; }

{WS}+					{ /* whitespace separates tokens */ }
.					{ /* discard bad characters */ }

%%

int yywrap(void)
{
    return 1;
}

static void comment(void)
{
    int c;

    while ((c = input()) != 0)
        if (c == '*')
        {
            while ((c = input()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
    yyerror("unterminated comment");
}

void yyerror(const char *s) {
    fprintf(stderr, "Lexer error: %s\n", s);
}

int main(int argc, char **argv) {
    int token;
    int token_count = 0;
    FILE *input_file;
    
    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
        yyin = input_file;
    } else {
        printf("Reading from stdin (Ctrl+D to end):\n");
        yyin = stdin;
    }
    
    printf("GOLEM Lexical Analyzer - Token Stream:\n");
    printf("======================================\n\n");
    
    while ((token = yylex()) != 0) {
        token_count++;
        printf("%-3d: %-20s", token_count, token2string(token));
        if (token == IDENTIFIER || token == INTEGER || token == STRING_LITERAL) {
            printf(" (%s)", yytext);
        }
        printf("\n");
    }
    
    printf("\n======================================\n");
    printf("Total tokens: %d\n", token_count);
    
    if (argc > 1) {
        fclose(input_file);
    }
    
    return 0;
}
