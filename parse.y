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

    statement* statements_head = nullptr;
}

%require "3.2"
%language "c++"

%token IF ELSE WHILE BREAK CONTINUE RETURN FN AS LET INPUT OUTPUT
%token INT_T CHAR_T FLOAT_T STRING_T BOOL_T ARRAY_T VOID_T
%token EQ NEQ GEQ LEQ ADDEQ SUBEQ DIVEQ MULEQ MODEQ AND OR RARROW EOL
%token INT FLOAT CHAR STRING BOOL

%token <s> ID

%nonassoc LOWER_THAN_ELSE    
%nonassoc ELSE
%left ','
%right '=' ADDEQ SUBEQ DIVEQ MULEQ MODEQ
%left AND OR
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
%type <stmt> fn_def global_statements global_statement fn_statements fn_statement var_def input output condition while_loop loop_statement loop_statements

%%

    /*  */
    global_statements: /* e */                              {$$ = nullptr;}
                    | global_statement global_statements    {$$ = statements_head = $1; $1->next = $2;}

    global_statement: EOL           {$$ = new blank_statement();}
                    | fn_def        {$$ = $1;}
                    | var_def       {$$ = $1;}

    /* function */
    fn_def: FN ID '(' args_def ')' RARROW fn_type '{' fn_statements '}' {
        $$ = new fndef_statement(new function($ID, $fn_type, $args_def, $fn_statements));
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
                
    fn_statement: EOL                    {$$ = new blank_statement();}
                | expr EOL               {$$ = new expr_statement($expr, yylineno);}
                | '{' fn_statements '}'  {$$ = new block_statement($fn_statements);}
                | RETURN expr EOL        {$$ = new return_statement($expr, yylineno);}
                | RETURN EOL             {$$ = new return_statement(nullptr, yylineno);}
                | var_def                {$$ = $1;}
                | while_loop             {$$ = $1;}
                | input                  {$$ = $1;}
                | output                 {$$ = $1;}
                | IF '(' condition ')' fn_statement  %prec LOWER_THAN_ELSE   {$$ = new if_statement($condition, $5, nullptr);}
                | IF '(' condition ')' fn_statement ELSE fn_statement        {$$ = new if_statement($condition, $5, $7);}
    

    /* var */
    var_def: LET ID '=' expr EOL            {$$ = new vardef_statement($ID, false, NULL_T, $expr, yylineno);}
           | LET ID ':' type '=' expr EOL   {$$ = new vardef_statement($ID, false, $type, $expr, yylineno);}
           | LET '&' ID '=' expr EOL          {$$ = new vardef_statement($ID, true, NULL_T, $expr, yylineno);}
           | LET '&' ID ':' type '=' expr EOL {$$ = new vardef_statement($ID, true, $type, $expr, yylineno);}

    /* while */

    while_loop: WHILE '(' condition ')' loop_statement   {$$ = new while_statement($condition, $loop_statement);}

    loop_statements: /* e */                        {$$ = nullptr;}
                   | loop_statement loop_statements {$$ = $1; $1->next = $2;}

    loop_statement: EOL                      {$$ = new blank_statement();}
                  | expr EOL                 {$$ = new expr_statement($expr, yylineno);}
                  | '{' loop_statements '}'  {$$ = new block_statement($loop_statements);}
                  | RETURN expr EOL          {$$ = new return_statement($expr, yylineno);}
                  | RETURN EOL               {$$ = new return_statement(nullptr, yylineno);}
                  | BREAK EOL                {$$ = new break_statement();}
                  | CONTINUE EOL             {$$ = new continue_statement();}
                  | var_def                  {$$ = $1;}
                  | while_loop               {$$ = $1;}
                  | input                    {$$ = $1;}
                  | output                   {$$ = $1;}
                  | IF '(' condition ')' loop_statement  %prec LOWER_THAN_ELSE  {$$ = new if_statement($condition, $5, nullptr);}
                  | IF '(' condition ')' loop_statement ELSE loop_statement     {$$ = new if_statement($condition, $5, $7);}
    

    /* IO */
    input: INPUT '`' expr_list '`' EOL      {$$ = new input_statement($expr_list, yylineno);}

    output: OUTPUT '`' expr_list '`' EOL    {$$ = new output_statement($expr_list, yylineno);}

    /* general */
    condition: expr {$$ = new condition($expr, yylineno);}

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
        | '[' expr EOL expr ']' {$$ = new array_literal($2, $4);}
        | fn_call           {$$ = $1;}
        | '(' expr ')'      {$$ = $2;}
        | expr '[' expr ']' {$$ = new index_expression($1, $3);}
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
        | expr AND expr     {$$ = new and_expression($1, $3);}
        | expr OR expr      {$$ = new or_expression($1, $3);}
        | expr '=' expr     {$$ = new assign_expression($1, $3);}
        | expr ADDEQ expr   {gc_ptr expr1 = $1; $$ = new assign_expression(expr1, new add_expression(expr1, $3));}
        | expr SUBEQ expr   {gc_ptr expr1 = $1; $$ = new assign_expression(expr1, new sub_expression(expr1, $3));}
        | expr MULEQ expr   {gc_ptr expr1 = $1; $$ = new assign_expression(expr1, new mul_expression(expr1, $3));}
        | expr DIVEQ expr   {gc_ptr expr1 = $1; $$ = new assign_expression(expr1, new div_expression(expr1, $3));}
        | expr MODEQ expr   {gc_ptr expr1 = $1; $$ = new assign_expression(expr1, new mod_expression(expr1, $3));}

    /*  */
    fn_call: ID '(' expr_list ')'     {$$ = new fncall_expression($ID, $expr_list);}

    expr_list: /* e */                {$$ = nullptr;}
             | expr_node              {$$ = $1;}

    expr_node: expr                   {$$ = new expr_list($1);}
             | expr ',' expr_node     {$$ = new expr_list($1); $$->next = $3;}
%%