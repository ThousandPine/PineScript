%{
#include <stdio.h>

int yylex();
int yyerror(char *);
%}

%token IF ELSE WHILE DO INT CHAR
%token ADD SUB MUL DIV ASSIGN EQ NEQ GT LT GEQ LEQ
%token COMMA SEMI LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET
%token ID NUM STR

%left ADD
%left MUL

%%

    S: expr {printf("res:%d\n", $1);}

    expr: NUM       {$$ = $1; printf("NUM:%d\n", $1);}        
        | expr ADD expr {$$ = $1 + $3;}
        | expr MUL expr {$$ = $1 * $3;}

%%