enum token_type {
    IF,
    ELSE,
    WHILE,
    DO,
    INT,
    CHAR,

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
    LBRACKET,
    RBRACKET,

    ID,
    NUM,
    STR
};

void output(enum token_type type, const char *val);