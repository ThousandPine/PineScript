#include <stdio.h>
#include "y.tab.h"

FILE *out_file;

extern FILE *yyin;
extern int yyparse();

void output(enum yytokentype type, const char *typename, const char *text)
{
    
    switch (type)
    {
    case ID:
        fprintf(out_file, "%s(%d, \"%s\")\n", typename, type, text);
        break;
    default:
        fprintf(out_file, "%s(%d, %s)\n", typename, type, text);
        break;
    }
}

int main(int argc, char **argv)
{
    yyin = fopen("./test.txt", "r");
    out_file = fopen("./lex.out", "w");
    yyparse();

    puts("\ndone");
}

int yyerror(char *s)
{
    printf("yyerror: %s\n", s);
    return 1;
}
