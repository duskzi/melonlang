#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "error.h"
#include "lexer.h"
#include "substr.h"
#include "token.h"


/*
 	Scans the source buffer, appending a token for each character.
 	Currently only single-character tokens are recognized.
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

		switch (*c) {
			case '(':
				init_token(&token, LEFT_PAREN, (substr_s){c, 1});
				break;
			case ')':
				init_token(&token, RIGHT_PAREN, (substr_s){c, 1});
				break;
			case '{':
				init_token(&token, LEFT_BRACE, (substr_s){c, 1});
				break;
			case '}':
				init_token(&token, RIGHT_BRACE, (substr_s){c, 1});
				break;
			case ',':
				init_token(&token, COMMA, (substr_s){c, 1});
				break;
			case '.':
				init_token(&token, DOT, (substr_s){c, 1});
				break;
			case '-':
				init_token(&token, MINUS, (substr_s){c, 1});
				break;
			case '+':
				init_token(&token, PLUS, (substr_s){c, 1});
				break;
			case ';':
				init_token(&token, SEMICOLON, (substr_s){c, 1});
				break;
			case '/':
				init_token(&token, SLASH, (substr_s){c, 1});
				break;
			case '*':
				init_token(&token, STAR, (substr_s){c, 1});
				break;
			case '@':
				init_token(&token, AT, (substr_s){c, 1});
				break;
			
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
					/* TODO: Parse number */
					should_push = false;
					break;
				}
				
				ERROR_RETURN(0, "Unexpected character '%c' at line %d", *c, line);
				break;
		}

		if (should_push && !token_array_push(tokens, token)) {
			ERROR_RETURN(0, "Failed to push token in line: %d", line);
		}

		index++;
	}

	return 1;

	
}