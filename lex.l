%{
#include <stdio.h>
#include "lex.h"

#define OUTPUT(x) {output(x, yytext);}
%}

white               [ \n\t\r\f]
line_comment        \/.*\n
block_comment       \/\*([^\*]|\*[^/])*\*\/
digit               [0-9]
letter              [a-zA-Z]
id                  ({letter}|_)({letter}|{digit}|_)*
number              [+-]?{digit}+(\.{digit}*)?([eE][+-]?{digit}*)?
string              \"[^"]*\"

%%

{white}
{line_comment}
{block_comment}

"if"    OUTPUT(IF)
"else"  OUTPUT(ELSE)
"while" OUTPUT(WHILE)
"do"    OUTPUT(DO)
"int"   OUTPUT(INT)
"char"  OUTPUT(CHAR)

"+"     OUTPUT(ADD)
"-"     OUTPUT(SUB)
"*"     OUTPUT(MUL)
"/"     OUTPUT(DIV)
"="     OUTPUT(ASSIGN)
"=="    OUTPUT(EQ)
"!="    OUTPUT(NEQ)
">"     OUTPUT(GT)
"<"     OUTPUT(LT)
">="    OUTPUT(GEQ)
"<="    OUTPUT(LEQ)

","     OUTPUT(COMMA)
";"     OUTPUT(SEMI)
"{"     OUTPUT(LBRACE)
"}"     OUTPUT(RBRACE)
"("     OUTPUT(LPAREN)
")"     OUTPUT(RPAREN)
"["     OUTPUT(LBRACKET)
"]"     OUTPUT(RBRACKET)

{id}        OUTPUT(ID)
{number}    OUTPUT(NUM)
{string}    OUTPUT(STR)
.           {printf("\nERROR unknow '%s'\n", yytext);}

%%
