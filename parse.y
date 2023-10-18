%{
#include <stdio.h>

int yylex();
int yyerror(const char *);
%}

%token IF ELSE ELIF WHILE BREAK CONTINUE RETURN FN AS LET
%token INT_T CHAR_T FLOAT_T STRING_T BOOL_T VOID_T
%token EQ NEQ GEQ LEQ RARROW EOL
%token ID INT FLOAT CHAR STRING

%left ','
%left '='
%left EQ NEQ
%left '>' '<' GEQ LEQ
%left '+' '-'
%left '*' '/' '%'
%left AS
%left '!'

%%

    /*  */
    global_statements: /* e */
                    | global_statement global_statements

    global_statement: EOL
                    | fn_def
                    | var_def

    /* function */
    fn_def: FN ID '(' args_def ')' RARROW fn_type '{' fn_statements '}'

    args_def: /* e */
           | arg_def_list

    arg_def_list: arg_def
               | arg_def ',' arg_def_list

    arg_def: ID ':' type
          | '&' ID ':' type

    fn_type: type
           | VOID_T
    
    fn_statements: /* e */
                | fn_statement fn_statements
                
    fn_statement: EOL
                | block
                | value EOL
                | var_def
                | if_else
                | while_loop
                | RETURN value EOL
                | RETURN EOL

    /* block */
    block: '{' fn_statements '}'

    /* var */
    var_def: LET ID '=' value EOL
           | LET ID ':' type EOL
           | LET ID ':' type '=' value EOL
           | LET '&' ID '=' l_value EOL
           | LET '&' ID ':' type '=' l_value EOL

    /* if-else */
    if_else: IF '(' value ')' '{' fn_statements '}' elif el

    elif: /* e */
         | ELIF '(' value ')' '{' fn_statements '}' elif
    
    el: /* e */
       | ELSE '{' fn_statements '}'

    /* while */

    while_loop: WHILE '(' value ')' '{' while_statements '}'

    while_statements: /* e */
                    | while_statement while_statements 

    while_statement: fn_statement
                   | BREAK EOL
                   | CONTINUE EOL

    /* general */
    type: INT_T | CHAR_T | FLOAT_T | STRING_T | BOOL_T

    value: l_value
         | r_value

    l_value: ID

    r_value: expr 
           | fn_call
           | INT
           | FLOAT
           | CHAR
           | STRING

    expr: '(' value ')'
        | '!' value
        | value AS type
        | value '*' value
        | value '/' value
        | value '%' value
        | value '+' value
        | value '-' value
        | value '>' value
        | value '<' value
        | value GEQ value
        | value LEQ value
        | value EQ value
        | value NEQ value
        | l_value '=' value

    /*  */

    fn_call: ID '(' fcall_args ')'

    fcall_args: /* e */
              | fcall_arg_list

    fcall_arg_list: value
                  | value ',' fcall_arg_list
%%