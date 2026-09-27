#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "substr.h"

void set_token(token_s *token, tokentype_e type, substr_s lexme) {
    
    token->type = type;
    token->lexme = lexme;
}

void print_token(token_s *token) {

    substr_print(token->lexme);
    putchar('\n');
}

tokentype_e match_keyword(substr_s *keyword) {

    #define USE(Type, String) if(substr_cmp(keyword, String)) { return Type; }
        KEYWORDS_TABLE
    #undef USE

    return TOKEN_NULL;
}
