#include <stdio.h>
#include "token.h"
#include "substr.h"

void init_token(token_s *token, tokentype_e type, substr_s lexme) {
    
    token->type = type;
    token->lexme = lexme;
}

void print_token(token_s *token) {

    substr_print(token->lexme);
    putchar('\n');
}
