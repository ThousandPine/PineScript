#include <stdio.h>
#include <iostream>
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
    
    yy::parser parser;
    parser.parse();

    fclose(lex_out);
    puts("\ndone");
}

int yyerror(const char *s)
{
    printf("%s: line %d '%s'\n", s, yylineno, yytext);
    return 1;
}

void yy::parser::error(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const& e)
{
    yyerror(e.c_str());
    return;
}
