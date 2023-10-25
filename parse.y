%code requires
{
    #include "statements/statements.h"
    #include "values/values.h"
    #include "expressions/expressions.h"
}

%code
{
    extern char *yytext;
    extern int yylineno;
    int yylex(yy::parser::value_type *value);
}

%require "3.2"
%language "c++"

%token IF ELSE ELIF WHILE BREAK CONTINUE RETURN FN AS LET INPUT OUTPUT
%token INT_T CHAR_T FLOAT_T STRING_T BOOL_T ARRAY_T VOID_T
%token EQ NEQ GEQ LEQ RARROW EOL
%token INT FLOAT CHAR STRING BOOL

%token <s> ID

%left ','
%right '='
%left EQ NEQ
%left '>' '<' GEQ LEQ
%left '+' '-'
%left '*' '/' '%'
%left AS
%right '!'
%right UMINUS
%left '[' ']'

%union
{
    int i;
    char s[99];
    args_def *args;
    expr_list *expr_l;
    statement *stmt;
    expression *expr;
}

%type <i> fn_type type
%type <expr> expr fn_call
%type <expr_l> expr_list expr_node
%type <args> args_def arg_def_list arg_def
%type <stmt> fn_statements fn_statement block var_def input output

%%

    /*  */
    global_statements: /* e */
                    | global_statement global_statements

    global_statement: EOL
                    | fn_def
                    | var_def       {$1->exec(); delete $1;}

    /* function */
    fn_def: FN ID '(' args_def ')' RARROW fn_type '{' fn_statements '}' {
        fndef_statement fn_def(new function($ID, $fn_type, $args_def, $fn_statements));
        fn_def.exec();
    }

    args_def: /* e */           {$$ = nullptr;}
           | arg_def_list       {$$ = $1;}

    arg_def_list: arg_def                   {$$ = $1;}
               | arg_def ',' arg_def_list   {$1->next = $3;}

    arg_def: ID ':' type        {$$ = new args_def($ID, $type, false);}
          | '&' ID ':' type     {$$ = new args_def($ID, $type, true);}

    fn_type: type       {$$ = $1;}
           | VOID_T     {$$ = value_t::VOID_T;}
    
    fn_statements: /* e */                      {$$ = nullptr;}
                | fn_statement fn_statements    {$$ = $1; $1->next = $2;}
                
    fn_statement: EOL               {$$ = new blank_statement();}
                | block             {$$ = $1;}
                | expr EOL          {$$ = new expr_statement($expr, yylineno);}
                | var_def           {$$ = $1;}
                // | if_else
                // | while_loop
                | input             {$$ = $1;}
                | output            {$$ = $1;}
                | RETURN expr EOL   {$$ = new return_statement($expr, yylineno);}
                | RETURN EOL        {$$ = new return_statement(nullptr, yylineno);}

    /* block */
    block: '{' fn_statements '}'    {$$ = new block_statement($fn_statements);}

    /* var */
    var_def: LET ID '=' expr EOL            {$$ = new vardef_statement($ID, NULL_T, $expr, yylineno);}
           | LET ID ':' type '=' expr EOL   {$$ = new vardef_statement($ID, $type, $expr, yylineno);}
           | LET '&' ID '=' ID EOL          {$$ = new varref_statement($3, NULL_T, $5, yylineno);}
           | LET '&' ID ':' type '=' ID EOL {$$ = new varref_statement($3, $5, $7, yylineno);}

    /* if-else */
    // if_else: IF '(' expr ')' '{' fn_statements '}' elif el

    // elif: /* e */
    //      | ELIF '(' expr ')' '{' fn_statements '}' elif
    
    // el: /* e */
    //    | ELSE '{' fn_statements '}'

    /* while */

    // while_loop: WHILE '(' expr ')' '{' while_statements '}'

    // while_statements: /* e */
    //                 | while_statement while_statements 

    // while_statement: fn_statement
    //                | BREAK EOL
    //                | CONTINUE EOL

    /* IO */
    input: INPUT '`' expr_list '`' EOL      {$$ = new input_statement($expr_list, yylineno);}

    output: OUTPUT '`' expr_list '`' EOL    {$$ = new output_statement($expr_list, yylineno);}

    /* general */
    type: INT_T     {$$ = value_t::INT_T;}
        | FLOAT_T   {$$ = value_t::FLOAT_T;}
        | CHAR_T    {$$ = value_t::CHAR_T;}
        | STRING_T  {$$ = value_t::STRING_T;}
        | BOOL_T    {$$ = value_t::BOOL_T;}
        | ARRAY_T   {$$ = value_t::ARRAY_T;}

    expr: ID        {$$ = new id_expression($ID);}
        | INT       {$$ = new literal(new int_value(yytext));}
        | FLOAT     {$$ = new literal(new float_value(yytext));}
        | CHAR      {$$ = new literal(new char_value(yytext));}
        | STRING    {$$ = new literal(new string_value(yytext));}
        | BOOL      {$$ = new literal(new bool_value(yytext));}
        | '[' expr EOL expr ']' {$$ = nullptr;}// TODO: 数组字面量
        | fn_call           {$$ = $1;}
        | '(' expr ')'      {$$ = $2;}
        | expr '[' expr ']' {$$ = nullptr;} // TODO: 下标访问
        | '-' expr %prec UMINUS {$$ = new minus_expression($2);}
        | '!' expr          {$$ = new not_expression($2);}
        | expr AS type      {$$ = new convert_expression($1, $3);}
        | expr '*' expr     {$$ = new mul_expression($1, $3);}
        | expr '/' expr     {$$ = new div_expression($1, $3);}
        | expr '%' expr     {$$ = new mod_expression($1, $3);}
        | expr '+' expr     {$$ = new add_expression($1, $3);}
        | expr '-' expr     {$$ = new sub_expression($1, $3);}
        | expr '>' expr     {$$ = new ge_expression($1, $3);}
        | expr '<' expr     {$$ = new le_expression($1, $3);}
        | expr GEQ expr     {$$ = new geq_expression($1, $3);}
        | expr LEQ expr     {$$ = new leq_expression($1, $3);}
        | expr EQ expr      {$$ = new eq_expression($1, $3);}
        | expr NEQ expr     {$$ = new neq_expression($1, $3);}
        | expr '=' expr     {$$ = new assign_expression($1, $3);}

    /*  */

    fn_call: ID '(' expr_list ')'     {$$ = new fncall_expression($ID, $expr_list);}

    expr_list: /* e */                {$$ = nullptr;}
             | expr_node              {$$ = $1;}

    expr_node: expr                   {$$ = new expr_list($1);}
             | expr ',' expr_node     {$$ = new expr_list($1); $$->next = $3;}
%%