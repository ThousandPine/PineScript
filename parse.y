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
%left ADD SUB
%left MUL DIV
%left LPAREN RPAREN

%%

    statement: statement expr EOL {printf("res:%d\n", $2);}
            | statement EOL
            | statement block
            | /* Epsilon */

    block: LBRACE statement RBRACE  {printf("block\n");}

    expr: NUM       {$$ = $1;}        
        | SUB expr  {$$ = -$2;}
        | ADD expr  {$$ = -$2;}
        | expr COMMA expr {$$ = $3;}
        | expr ADD expr {$$ = $1 + $3;}
        | expr SUB expr {$$ = $1 - $3;}
        | expr MUL expr {$$ = $1 * $3;}
        | expr DIV expr {$$ = $1 / $3;}
        | LPAREN expr RPAREN {$$ = $2;}

%%