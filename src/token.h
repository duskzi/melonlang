#ifndef HEADER_MELON_TOKEN
#define HEADER_MELON_TOKEN

#include <stddef.h> /* for size_t in substr_s */
#include "substr.h"

typedef enum tokentype_e {

  /* Single-character tokens */
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
  AT,

  /* One or two character tokens */
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,
  
  /* Literals */
  IDENTIFIER, STRING, NUMBER,
  
  /* Keywords */
  AND, ELSE, FALSE, FOR, IF, NLL, OR,
  OUT, RETURN, TRUE, VAR, WHILE,

  /* Types */
  INT_T, STRING_T, FLOAT_T,
}
tokentype_e;

/* Literal value attached to a token */
typedef union literal_u {
	float 	number;
	char   *string;
} 
literal_u;

/* A single token produced by the lexer */
typedef struct token_s {
	tokentype_e 	type;
	substr_s 		  lexme;
	literal_u 		literal;
	unsigned int 	line;
} 
token_s;

void init_token(token_s *token, tokentype_e type, substr_s lexme);
void print_token(token_s *token);

#endif
