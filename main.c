#include <stdio.h>
#include "y.tab.h"

FILE *out_file;

extern FILE *yyin;
extern int yyparse();

int main(int argc, char **argv)
{
    yyin = fopen("./test.txt", "r");
    // out_file = fopen("./output.txt", "w");
    yyparse();

    puts("\ndone");
}

int yyerror(char *s)
{
    puts(s);
    return 1;
}
