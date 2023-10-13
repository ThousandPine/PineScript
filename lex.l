%{
#include <stdio.h>
#include "lex.h"

#define RET(x) {output(x, yytext);}
%}

white               [ \n\t\r\f]|(\\\n)
line_comment        \/.*\n
block_comment       \/\*([^\*]|\*[^/])*\*\/
digit               [0-9]
letter              [a-zA-Z]
id                  ({letter}|_)({letter}|{digit}|_)*
number              [+-]?{digit}+(\.{digit}*)?([eE][+-]?{digit}*)?
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

","     RET(COMMA)
";"     RET(SEMI)
"{"     RET(LBRACE)
"}"     RET(RBRACE)
"("     RET(LPAREN)
")"     RET(RPAREN)
"["     RET(LBRACKET)
"]"     RET(RBRACKET)

{id}        RET(ID)
{number}    RET(NUM)
{string}    RET(STR)
.           {printf("\nERROR unknow '%s'\n", yytext);}

%%
