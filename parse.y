%code
{
    extern char *yytext;
    int yylex(yy::parser::value_type *value);
}

%require "3.2"
%language "c++"

%token IF ELSE ELIF WHILE BREAK CONTINUE RETURN FN AS LET
%token INT_T CHAR_T FLOAT_T STRING_T BOOL_T VOID_T
%token EQ NEQ GEQ LEQ RARROW EOL
%token ID INT FLOAT CHAR STRING BOOL

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
                | expr EOL
                | var_def
                | if_else
                | while_loop
                | RETURN expr EOL
                | RETURN EOL

    /* block */
    block: '{' fn_statements '}'

    /* var */
    var_def: LET ID '=' expr EOL
           | LET ID ':' type EOL
           | LET ID ':' type '=' expr EOL
           | LET '&' ID '=' ID EOL
           | LET '&' ID ':' type '=' ID EOL

    /* if-else */
    if_else: IF '(' expr ')' '{' fn_statements '}' elif el

    elif: /* e */
         | ELIF '(' expr ')' '{' fn_statements '}' elif
    
    el: /* e */
       | ELSE '{' fn_statements '}'

    /* while */

    while_loop: WHILE '(' expr ')' '{' while_statements '}'

    while_statements: /* e */
                    | while_statement while_statements 

    while_statement: fn_statement
                   | BREAK EOL
                   | CONTINUE EOL

    /* general */
    type: INT_T | CHAR_T | FLOAT_T | STRING_T | BOOL_T

    expr: ID
        | INT
        | FLOAT
        | CHAR
        | STRING
        | BOOL
        | fn_call
        | '(' expr ')'
        | '!' expr
        | expr AS type
        | expr '*' expr
        | expr '/' expr
        | expr '%' expr
        | expr '+' expr
        | expr '-' expr
        | expr '>' expr
        | expr '<' expr
        | expr GEQ expr
        | expr LEQ expr
        | expr EQ expr
        | expr NEQ expr
        | ID '=' expr

    /*  */

    fn_call: ID '(' fcall_args ')'

    fcall_args: /* e */
              | fcall_arg_list

    fcall_arg_list: expr
                  | expr ',' fcall_arg_list
%%