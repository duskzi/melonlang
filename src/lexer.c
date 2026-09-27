#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "lexer.h"
#include "substr.h"
#include "token.h"


/* Symbol table entry for lexing */
typedef struct {
    const char 	   *str;
    tokentype_e 	type;
    size_t 			len;
} symbol_entry_s;

/* Multi-char symbols from SYMBOLS_TABLE */
#define USE(Type, Str) { Str, Type, sizeof(Str) - 1 },
static const symbol_entry_s multi_char_symbols[] = {
    SYMBOLS_TABLE
};
#undef USE

/* Single-char symbols from SINGLE_CHAR_SYMBOLS_TABLE */
#define USE(Type, Ch) { (const char[]){Ch, '\0'}, Type, 1 },
static const symbol_entry_s single_char_symbols[] = {
    SINGLE_CHAR_SYMBOLS_TABLE
};
#undef USE

/*
 * 1 == true
 * 0 == false
 */
int scan_lexme(substr_s *substr, char *source, size_t *index, size_t *line) {
    
    if (source[*index] == '\0')
        return 0;

    char *letter = &source[*index];

    /* Numbers */
    if (isdigit(*letter)) {
        char *begin = letter;

        while (*begin != '\0' && isdigit(*begin)) begin++;

        size_t numberlen = begin - letter;

        *substr = (substr_s){letter, numberlen};
        *index += numberlen;

        return 1;
    }

    /* Identifiers / keywords */
    if (isalnum(*letter) || *letter == '_') {
        char *begin = letter;

        while (*begin != '\0' && (isalnum(*begin) || *begin == '_')) begin++;

        size_t wordlen = begin - letter;

        *substr = (substr_s){letter, wordlen};
        *index += wordlen;

        return 1;
    }

    /* Comments */
    if (*letter == '|') {
        while (source[*index] != '\n' && source[*index] != '\0') (*index)++;
        return scan_lexme(substr, source, index, line);
    }

    /* Whitespace */
    if (isspace(*letter)) {
        if (*letter == '\n') (*line)++;

        (*index)++;

        return scan_lexme(substr, source, index, line);
    }

    /* Strings */
    if (*letter == '"') {
        char *begin = ++letter;
        
        while (*letter != '"' && *letter != '\0')
            letter++;
        
        if (*letter == '\0') {
            /* unterminated string */
            return 0;
        }
        
        size_t length = letter - begin;
        
        *substr = (substr_s){begin, length};
        
        *index += length + 2; // opening + contents + closing
        
        return 1;
    }

    /* Symbols */
    if (ispunct(*letter)) {
        *substr = (substr_s){letter, 1};
        (*index)++;

        return 1;
    }

    return 0;
}
/*
	Scans the source buffer, appending a token for each character.
	Returns 1 on success, 0 on failure.
 */
int scan_tokens(char *source, token_array_s *tokens) {

	size_t index = 0;
	size_t line  = 0;

	substr_s token;

	while(scan_lexme(&token, source, &index, &line)){
        
        substr_print(token);
        putchar('\n');
    }

	return 0;
}