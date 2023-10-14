%{
#include <stdio.h>
#include "y.tab.h"

#define RET(x) {output(x, #x, yytext) ; return x;}

void output(enum yytokentype type, const char *typename, const char *text);
%}

%option noyywrap

white               [ \t\r\f]|(\\\n)
line_comment        \/.*\n
block_comment       \/\*([^\*]|\*[^/])*\*\/
digit               [0-9]
letter              [a-zA-Z]
id                  ({letter}|_)({letter}|{digit}|_)*
number              {digit}+(\.{digit}*)?([eE][+-]?{digit}*)?
string              \"([^"]|\\\")*\"

%%

{white}
{line_comment}
{block_comment}

"if"    RET(IF)
"else"  RET(ELSE)
"while" RET(WHILE)
"do"    RET(DO)
"int"   RET(INT)
"char"  RET(CHAR)

"+"     RET(ADD)
"-"     RET(SUB)
"*"     RET(MUL)
"/"     RET(DIV)
"="     RET(ASSIGN)
"=="    RET(EQ)
"!="    RET(NEQ)
">"     RET(GT)
"<"     RET(LT)
">="    RET(GEQ)
"<="    RET(LEQ)

"\n"    RET(EOL)
";"     RET(EOL)
","     RET(COMMA)
"{"     RET(LBRACE)
"}"     RET(RBRACE)
"("     RET(LPAREN)
")"     RET(RPAREN)
"["     RET(LBRACKET)
"]"     RET(RBRACKET)

{id}        RET(ID)
{number}    {yylval = atoi(yytext); RET(NUM);}
{string}    RET(STR)
.           {printf("\nERROR unknow '%s'\n", yytext);}

%%
