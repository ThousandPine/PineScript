enum token_type {
    IF,
    ELSE,
    WHILE,
    DO,
    INT,
    ADD,
    SUB,
    MUL,
    DIV,
    ASSIGN,
    EQ,
    NEQ,
    GT,
    LT,
    GEQ,
    LEQ,
    COMMA,
    SEMI,
    LBRACE,
    RBRACE,
    LPAREN,
    RPAREN,
    ID,
    NUM
};

void output(enum token_type type, const char *val);