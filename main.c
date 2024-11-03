typedef enum TokenType{ TOKEN_PLUS, TOKEN_SUB, TOKEN_MUL, TOKEN_DIV, TOKEN_NUM, TOKEN_END} TokenType;

struct Token{
    TokenType type;
    int value;
};

