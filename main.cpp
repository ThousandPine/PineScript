#include <stdio.h>
#include <iostream>
#include "y.tab.h"

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

extern statement *statements_head;

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
    if (yyin == NULL)
    {
        puts("Unable to open the file path provided. Please check the file path and try again.");
        return 1;
    }

    // 语法分析
    yy::parser parser;
    parser.parse();

    gc_ptr<statement> statements = statements_head; // 使用gc_ptr接管指针

    // 执行全局语句
    for (auto stmt = statements; stmt != nullptr; stmt = stmt->next)
    {
        switch (stmt->exec())
        {
        case DONE:
            break;

        // ERROR
        default:
            return -1;
        }
    }

    // 执行main函数
    fncall_expression main_fn("main", nullptr);
    main_fn.get_value();
}

int yyerror(const char *s)
{
    printf("%s: line %d '%s'\n", s, yylineno, yytext);
    exit(1);
    return 1;
}

void yy::parser::error(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const &e)
{
    yyerror(e.c_str());
    return;
}
