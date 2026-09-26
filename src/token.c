#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "substr.h"

void init_token(token_s *token, tokentype_e type, substr_s lexme) {
    
    token->type = type;
    token->lexme = lexme;
}

const char *tokentostr(tokentype_e type) {
    switch (type) {
        #define USE(Type, String) case Type: return #Type;
            KEYWORDS_TABLE
        #undef USE

        #define USE(Type, String) case Type: return #Type;
            LITERALS_TABLE
        #undef USE

        #define USE(Type, String) case Type: return #Type;
            SINGLE_CHAR_SYMBOLS_TABLE
        #undef USE

        #define USE(Type, String) case Type: return #Type;
            SYMBOLS_TABLE
        #undef USE

        default:
            return "TOKEN_NULL";
    }
}

void print_token(token_s *token) {

    printf("%s: ", tokentostr(token->type));
    substr_print(token->lexme);
    putchar('\n');
}

tokentype_e match_keyword(substr_s *keyword) {

    #define USE(Type, String) if(substr_cmp(keyword, String)) { return Type; }
        KEYWORDS_TABLE
    #undef USE

    return TOKEN_NULL;
}
