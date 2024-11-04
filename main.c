#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum TokenType{ TOKEN_ADD, TOKEN_SUB, TOKEN_MUL, TOKEN_DIV, TOKEN_NUM, TOKEN_END} TokenType;

typedef struct Token{
    TokenType type;
    int value;
} Token;

  typedef struct Result{
        TokenType type;
        int isOperator;
    } Result;

void checkChar(char c, struct Result* result) {
    switch (c) {
        case '+':
            result->type = TOKEN_ADD; 
            result->isOperator = 1; 
            break;
        case '-':
            result->type = TOKEN_SUB; 
            result->isOperator = 1; 
            break;
        case '*':
            result->type = TOKEN_MUL; 
            result->isOperator = 1; 
            break;
        case '/':
            result->type = TOKEN_DIV; 
            result->isOperator = 1; 
            break;
        default: 
            result->isOperator = 0; 
            break;
    }
}

// Tokenization
Token* tokenize(char* expression){
    Token* tokens = malloc(256 * sizeof(Token));
    if (!tokens) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    int i = 0;
    struct Result checkResult;

    while (*expression) {
        checkChar(*expression, &checkResult);

        if (checkResult.isOperator) {
            tokens[i].type = checkResult.type;
            tokens[i].value = -1; 
            i++;
            expression++;
        } else if (isdigit(*expression)) {
            tokens[i].type = TOKEN_NUM;
            tokens[i].value = strtol(expression, &expression, 10);
            i++;
        } else expression++;
        
    }

    tokens[i].type = TOKEN_END;
    tokens[i].value = -1;
    return tokens;
}

// Parsing
int parse(Token* tokens, int* ans) {
    if (tokens->type != TOKEN_NUM && tokens->type != TOKEN_SUB && tokens->type != TOKEN_ADD) {
        return -1; 
    }

    int sign = 1; 
    while (tokens->type == TOKEN_SUB) {
        sign *= -1;
        tokens++;
    }

    if(tokens->type==TOKEN_ADD) tokens++;

    if (tokens->type != TOKEN_NUM) return -1; 
    *ans = sign * tokens->value; 
    tokens++;

    while (tokens->type != TOKEN_END) {
        TokenType op = tokens->type; 
        tokens++;

        if (tokens->type != TOKEN_NUM) return -1; 
        int num = tokens->value;
        tokens++;

        switch (op) {
            case TOKEN_ADD:
                *ans += num;
                break;
            case TOKEN_SUB:
                *ans -= num;
                break;
            case TOKEN_MUL:
                *ans *= num;
                break;
            case TOKEN_DIV:
                if (num == 0) return -1; 
                *ans /= num;
                break;
            default:
                return -1; 
        }
    }
    return 1; 
}

// Code gen

