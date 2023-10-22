%{
#include <stdio.h>
#include "y.tab.h"

#define RET(x) {output(#x, yytext) ; return x;}
#define TOKEN(x) {output(#x, yytext) ; return yy::parser::token::x;}
#define YY_DECL int yylex(yy::parser::value_type *value)

void output(const char *tname, const char *text);
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
bool                true|false

%%

{white}
{line_comment}
{block_comment}

"if"        TOKEN(IF)
"else"      TOKEN(ELSE)
"else if"   TOKEN(ELIF)
"while"     TOKEN(WHILE)
"return"    TOKEN(RETURN)
"break"     TOKEN(BREAK)
"continue"  TOKEN(CONTINUE)
"fn"        TOKEN(FN)
"as"        TOKEN(AS)
"let"       TOKEN(LET)

"int"       TOKEN(INT_T)
"char"      TOKEN(CHAR_T)
"float"     TOKEN(FLOAT_T)
"string"    TOKEN(STRING_T)
"bool"      TOKEN(BOOL_T)
"void"      TOKEN(VOID_T)

"=="    TOKEN(EQ)
"!="    TOKEN(NEQ)
">="    TOKEN(GEQ)
"<="    TOKEN(LEQ)
"->"    TOKEN(RARROW)
";"     TOKEN(EOL)

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

{bool}      TOKEN(BOOL)
{id}        {strcpy(value->s, yytext); TOKEN(ID)}
{intger}    TOKEN(INT)
{float}     TOKEN(FLOAT)
{char}      TOKEN(CHAR)
{string}    TOKEN(STRING)
.           {printf("lex error: line %d unknow '%s'\n", yylineno, yytext);}

%%
