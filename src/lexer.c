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
	Scans the source buffer, appending a token for each character.
	Returns 1 on success, 0 on failure.
 */
int scan_tokens(char *source, token_array_s *tokens) {
	size_t index = 0;
	int    line  = 0;


	/* 
		'c' points to the address of the current letter in the loop 
	*/
	char *c = NULL;
	while (*(c = &source[index]) != '\0') {

		token_s token = {0};
		bool should_push = true;

		/* Try multi-char symbols first (max-munch: longest match wins) */
		bool matched = false;
		for (size_t i = 0; i < sizeof(multi_char_symbols)/sizeof(multi_char_symbols[0]); i++) {
			const symbol_entry_s *sym = &multi_char_symbols[i];
			if (strncmp(c, sym->str, sym->len) == 0) {
				init_token(&token, sym->type, (substr_s){c, sym->len});
				index += sym->len - 1;  /* Loop does index++ */
				matched = true;
				break;
			}
		}

		if (!matched) {
			/* Try single-char symbols */
			for (size_t i = 0; i < sizeof(single_char_symbols)/sizeof(single_char_symbols[0]); i++) {
				if (*c == single_char_symbols[i].str[0]) {
					init_token(&token, single_char_symbols[i].type, (substr_s){c, 1});
					matched = true;
					break;
				}
			}
		}

		if (!matched) {
			switch (*c) {
				case ' ':
				case '\t':
					should_push = false;
					break;

				case '\n':
					line++;
					should_push = false;
					break;
				
				case '"':

					/* Hops " char */
					char *begin = c;
					begin++;

					do {
						c++;
						index++;
					}
					while (*c != '"' && *c != '\0');
					
					if (*c == '\0') {
						ERROR_RETURN(0, "Unterminated string at line %d", line);
					}

					substr_s substr = {
						.begin = begin,
						.length = c - begin, /* c stops at the closing quote, so it's not counted */
					};
					
					init_token(&token, STRING, substr);

					break;

				default:
					
					/* Found a keyword or a type */
					if(isalpha(*c)) {

						char *begin = c;
						while(isalnum(*c) && *c != '\0') {
							c++;
							index++;
						}

						index--; /* Last word char */

						if (*c == '\0') {
							ERROR_RETURN(0, "Unterminated keyword at line %d", line);
						}
						
						substr_s keyword = {
							.begin = begin,
							.length = c - begin,
						};

						tokentype_e type = match_keyword(&keyword);
						
						if(type == TOKEN_NULL) {
							/* TODO: or this shit is a identifier or it is
							 * a type
							 */
						}

						/* Set the keyword */
						init_token(&token, type, keyword);

						break;
					}
					
					if(isdigit(*c)) {

                        char *begin = c;
                        
                        /* Group the digit and dot checks together */
                        while((isdigit(*c) || *c == '.') && *c != '\0') {
                            c++;
                            index++;
                        }

                        index--; /* Adjust so outer loop processes the non-digit char correctly */

                        substr_s number_str = {
                            .begin = begin,
                            .length = c - begin,
                        };

                        /* Assuming NUMBER is your token type for numerical values */
                        init_token(&token, NUMBER, number_str);

                        /* We DO want to push this token, so we don't set should_push = false */
                        break;
                    }
					
					ERROR_RETURN(0, "Unexpected character '%c' at line %d", *c, line);
					break;
			}
		}

		if (should_push && !token_array_push(tokens, token)) {
			ERROR_RETURN(0, "Failed to push token in line: %d", line);
		}

		index++;
	}

	return 1;
	
}