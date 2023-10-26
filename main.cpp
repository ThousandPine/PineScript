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
    // fflush(lex_out);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        puts("No filename provided. Please provide a filename as an argument.");
        return 1;
    }
    if (argc > 2)
    {
        puts("Multiple filenames provided. This interpreter only supports one file at a time.");
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if(yyin == NULL)
    {
        puts("Unable to open the file path provided. Please check the file path and try again.");
        return 1;
    }

    lex_out = fopen(lex_out_path, "w");
    
    yy::parser parser;
    parser.parse();

    fclose(lex_out);

    fncall_expression main_fn("main", nullptr);
    main_fn.get_value();

    puts("\ndone");
}

int yyerror(const char *s)
{
    printf("%s: line %d '%s'\n", s, yylineno, yytext);
    exit(1);
    return 1;
}

void yy::parser::error(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const& e)
{
    yyerror(e.c_str());
    return;
}
