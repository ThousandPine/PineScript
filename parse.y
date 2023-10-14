%{
#include <stdio.h>

int yylex();
int yyerror(char *);
%}

%token IF ELSE WHILE DO INT CHAR
%token ADD SUB MUL DIV ASSIGN EQ NEQ GT LT GEQ LEQ
%token EOL COMMA LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET
%token ID NUM STR

%left COMMA
%left ADD
%left MUL

%%

    S: S expr EOL {printf("res:%d\n", $2);}
        | S EOL
        | /* Epsilon */

    expr: NUM       {$$ = $1; printf("NUM:%d\n", $1);}        
        | expr ADD expr {$$ = $1 + $3;}
        | expr MUL expr {$$ = $1 * $3;}

%%