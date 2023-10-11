%{
#include <stdio.h>
#include "lex.h"

#define OUTPUT(x) {output(x, yytext);}
%}

white               [\n\t ]
line_comment        \/.*\n
block_comment       \/\*([^\*]|\*[^/])*\*\/
digit               [0-9]
letter              [a-zA-Z]
id                  ({letter}|_)({letter}|{digit}|_)*
number              [+-]?{digit}+(\.{digit}*)?([eE]{digit}*)?
string              "[^\n]*"

%%

{white}
{line_comment}
{block_comment}

"if"    OUTPUT(IF)
"else"  OUTPUT(ELSE)
"while" OUTPUT(WHILE)
"do"    OUTPUT(DO)
"int"   OUTPUT(INT)

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

{id}        OUTPUT(ID)
{number}    OUTPUT(NUM)
.           {printf("\nERROR unknow '%s'\n", yytext);}

%%
