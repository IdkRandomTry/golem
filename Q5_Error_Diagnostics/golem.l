D   [0-9]
L   [a-z]
A   [a-zA-Z_0-9]
ID  {L}{A}*
WS  [ \t\v\n\f]

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "golem.tab.h"
#include "tokens.h"

static void comment(void);
extern void yyerror(const char *s);
extern int error_count;
extern int warning_count;
%}

%option nounput
%option yylineno

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
"else"					{ return(ELSE); }
"then"					{ return(THEN); }
"repeat"				{ return(REPEAT); }
"north"					{ return(NORTH); }
"south"					{ return(SOUTH); }
"east"					{ return(EAST); }
"west"					{ return(WEST); }
"true"					{ return(TRUE); }
"false"					{ return(FALSE); }
"empty"					{ return(EMPTY); } /* [FLAG: Add keyword] Add keyword token here as needed */

{ID}					{ yylval.sval = strdup(yytext); return(IDENTIFIER); }

{D}+					{ yylval.ival = atoi(yytext); return(INTEGER); }

\"[^\"]*\"				{ yylval.sval = strdup(yytext); return(STRING_LITERAL); }

">>"					{ return(EAST_SCAN); }
[<][<]					{ return(WEST_SCAN); }
"^^"					{ return(NORTH_SCAN); }
"vv"					{ return(SOUTH_SCAN); }

"=="					{ return(EQ_OP); }
"!="					{ return(NE_OP); }
"+"					{ return(PLUS); }
"-"					{ return(MINUS); }
"*"					{ return(MULTIPLY); }
"/"					{ return(DIVIDE); }
"%"					{ return(MODULO); }
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
                break; // EOF reached but comment not closed
        }
    yyerror("unterminated comment");
}

int main(int argc, char **argv) {
    FILE *input_file = NULL;

    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            fprintf(stderr, "╔════════════════════════════════════════════════════════════════╗\n");
            fprintf(stderr, "║                         FILE ERROR                             ║\n");
            fprintf(stderr, "╚════════════════════════════════════════════════════════════════╝\n");
            fprintf(stderr, "\nError: Cannot open file '%s'\n", argv[1]);
            fprintf(stderr, "Please check:\n");
            fprintf(stderr, "  • File exists\n");
            fprintf(stderr, "  • File path is correct\n");
            fprintf(stderr, "  • You have read permissions\n\n");
            return 1;
        }
        yyin = input_file;
    } else {
        yyin = stdin;
    }

    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║          GOLEM Parser - Part 5: Error Diagnostics             ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");

    int result = yyparse();

    if (input_file) {
        fclose(input_file);
    }

    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                       PARSING SUMMARY                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");

    if (result == 0 && error_count == 0) {
        printf("✓ Parsing successful!\n");
        printf("  • No errors detected\n");
        if (warning_count > 0) {
            printf("  • %d warning(s) issued\n", warning_count);
        }
        printf("\n");
        return 0;
    } else {
        printf("✗ Parsing failed!\n");
        printf("  • %d error(s) detected\n", error_count);
        if (warning_count > 0) {
            printf("  • %d warning(s) issued\n", warning_count);
        }
        printf("\nPlease fix the errors and try again.\n\n");
        return 1;
    }
}
