%{
#include <stdio.h>
#include "y.tab.h"

#define RET(x) {output(x, #x, yytext) ; return x;}

void output(enum yytokentype type, const char *typename, const char *text);
%}

%option noyywrap yylineno

white               [ \n\t\r\f]|(\\\n)
line_comment        \/.*\n
block_comment       \/\*([^\*]|\*[^/])*\*\/
digit               [0-9]
letter              [a-zA-Z]
id                  ({letter}|_)({letter}|{digit}|_)*
intger              {digit}+
float               {digit}+(\.{digit}*)?([eE][+-]?{digit}*)?
char                \'([^'\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3})\'
string              \"([^"\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3})*\"

%%

{white}
{line_comment}
{block_comment}

"if"        RET(IF)
"else"      RET(ELSE)
"else if"   RET(ELIF)
"while"     RET(WHILE)
"return"    RET(RETURN)
"break"     RET(BREAK)
"continue"  RET(CONTINUE)
"fn"        RET(FN)
"as"        RET(AS)
"let"       RET(LET)

"int"       RET(INT_T)
"char"      RET(CHAR_T)
"float"     RET(FLOAT_T)
"string"    RET(STRING_T)
"bool"      RET(BOOL_T)
"void"      RET(VOID_T)

"=="    RET(EQ)
"!="    RET(NEQ)
">="    RET(GEQ)
"<="    RET(LEQ)
"->"    RET(RARROW)
";"     RET(EOL)

"!" |
"+" |
"-" |
"*" |
"/" |
"%" |
"=" |
">" |
"<" |
"," |
"{" |
"}" |
"(" |
")" |
"[" |
"]" |
"&" |
":"     RET(yytext[0])

{id}        RET(ID)
{intger}    {yylval = atoi(yytext); RET(INT);}
{float}     {yylval = atof(yytext); RET(FLOAT);}
{char}      RET(CHAR)
{string}    RET(STRING)
.           {printf("lex error: line %d unknow '%s'\n", yylineno, yytext);}

%%
