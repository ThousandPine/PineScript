#include <stdio.h>
#include "y.tab.h"

FILE *lex_out;
const char *lex_out_path = "./lex.out";

extern FILE *yyin;
extern int yyparse();

void output(enum yytokentype type, const char *typename, const char *text)
{
    switch (type)
    {
    case ID:
        fprintf(lex_out, "%s(%d, \"%s\")\n", typename, type, text);
        break;
    default:
        fprintf(lex_out, "%s(%d, %s)\n", typename, type, text);
        break;
    }
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

int yyerror(char *s)
{
    printf("yyerror: %s\n", s);
    return 1;
}
