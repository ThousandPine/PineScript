#include <stdio.h>
#include "lex.h"

FILE *out_file;

extern FILE *yyin;
extern int yylex();
extern int yywrap();

void output(enum token_type type, const char *val)
{
    switch (type)
    {
    case ID:
        fprintf(out_file, "(%d, \"%s\")\n", type, val);
        break;
    case NUM:
        fprintf(out_file, "(%d, %s)\n", type, val);
        break;
    case STR:
        fprintf(out_file, "(%d, %s)\n", type, val);
        break;
    default:
        fprintf(out_file, "(%d, \t)\n", type);
        break;
    }
}

int main(int argc, char **argv)
{
    yyin = fopen("./test.txt", "r");
    out_file = fopen("./lex.txt", "w");
    yylex();
    yywrap();

    puts("\ndone");
}

int yywrap()
{
    return 1;
}