#include <stdio.h>
#include "y.tab.h"

FILE *lex_out;
const char *lex_out_path = "./lex.out";

extern int yylineno;
extern char *yytext;
extern FILE *yyin;
extern int yyparse();

void output(const char *tname, const char *text)
{
    fprintf(lex_out, "%s, %s\n", tname, text);
    fflush(lex_out);
}

int main(int argc, char **argv)
{
    yyin = fopen("./test.txt", "r");
    lex_out = fopen(lex_out_path, "w");
    yyparse();

    fclose(lex_out);
    puts("\ndone");
}

int yyerror(const char *s)
{
    printf("%s: line %d '%s'\n", s, yylineno, yytext);
    return 1;
}
