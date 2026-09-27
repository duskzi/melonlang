#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "lexer.h"
#include "substr.h"
#include "token.h"
#include "token_array.h"

int def_token(token_s *token, size_t *line, tokentype_e type, substr_s lexme) {
	token->lexme = lexme;
	token->line = *line;
	token->type = type;

	return 1;
}

#define advance_by(Offset) 		((*index)+=Offset)
#define advance() 				((*index)++)
#define match_next(Char) 		(source[*index + 1] == Char)

/* Variadic because the compound literal (substr_s){ptr, len} contains a
 * comma that the preprocessor would otherwise read as an argument separator 
 */
#define emit_token(Type, ...) 	def_token(token, line, Type, (__VA_ARGS__))

/* Returns true if ´c´ is valid Melon lang
 * symbol 
 */
static inline int is_melon_symbol(char c)
{
    unsigned char u = (unsigned char) c;

    return (u >= 33 && u <= 47) ||
           (u >= 58 && u <= 64) ||
           (u >= 91 && u <= 96) ||
           (u >= 123 && u <= 126);
}

/* 1 == true
 * 0 == false */
int scan_lexme(token_s *token, char *source, size_t *index, size_t *line) {
    
    if (source[*index] == '\0') return 0;

    char *letter = &source[*index];

    /* Numbers */
    if (isdigit(*letter)) {
        char *begin = letter;

        while (*begin != '\0' && isdigit(*begin)) begin++;

        size_t numberlen = begin - letter;
        advance_by(numberlen);

        return def_token(
			token, line, NUMBER,
			(substr_s){letter, numberlen});
    }

    /* Identifiers / keywords */
    if (isalnum(*letter) || *letter == '_') {
        char *begin = letter;

        while (*begin != '\0' && (isalnum(*begin) || *begin == '_')) begin++;

        size_t wordlen = begin - letter;
        advance_by(wordlen);

        return def_token(
			token, line, IDENTIFIER,
			(substr_s){letter, wordlen});
    }

    /* Comments */
    if (*letter == '|' && source[*index+1] != '|') {
        while (source[*index] != '\n' && source[*index] != '\0') advance();
        return scan_lexme(token, source, index, line);
    }

    /* Whitespace */
    if (isspace(*letter)) {
        if (*letter == '\n') (*line)++;
        advance();
        return scan_lexme(token, source, index, line);
    }

    /* Strings */
    if (*letter == '"') {
        char *begin = ++letter;
        
        while (*letter != '"' && *letter != '\0')
            letter++;
        
        if (*letter == '\0') {
			ERROR_RETURN(0, "Unterminated string at line: %d, index: %d", (int)*line, (int)*index);
        }
        
        size_t length = letter - begin;
        advance_by(length + 2); // Content + double quotes

		return def_token(
			token, line, STRING,
			(substr_s){begin, length});
    }

    /* Symbols */
    if (*letter == '<' && match_next('=')) {
        advance();
        return emit_token(LESS_EQUAL, (substr_s){letter, 2});
    }

    if (*letter == '>' && match_next('=')) {
        advance();
        return emit_token(GREATER_EQUAL, (substr_s){letter, 2});
    }

    if (*letter == '!' && match_next('=')) {
        advance();
        return emit_token(BANG_EQUAL, (substr_s){letter, 2});
    }

    if (*letter == '=' && match_next('=')) {
        advance();
        return emit_token(EQUAL_EQUAL, (substr_s){letter, 2});
    }

    tokentype_e type = *letter * (is_melon_symbol(*letter));
    advance();
	return def_token(
		token, line, type,
		(substr_s){letter, 1});
}

/*
	Scans the source buffer, appending a token for each character.
	Returns 1 on success, 0 on failure.
 */
int scan_tokens(char *source, token_array_s *tokens) {

	size_t index = 0;
	size_t line  = 0;

	token_s token;

	while(scan_lexme(&token, source, &index, &line)){
        
        token_array_push(tokens, token);
    }

    token_s eof = {TOKEN_EOF, NULL, line};
	token_array_push(tokens, eof);

    LOG_DEBUG("Lines scanned: %d", (int) line);
    LOG_DEBUG("Chars scanned: %d", (int) index);

	return 1;
}