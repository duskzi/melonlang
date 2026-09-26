#ifndef HEADER_MELON_TOKEN
#define HEADER_MELON_TOKEN

#include <stddef.h> /* for size_t in substr_s */
#include "substr.h"

/* Macros Tables
 *
 *    USE( int Type, char *Strings )	
 */
#define KEYWORDS_TABLE \
	USE(IF,       	"if") \
	USE(FOR,          "for") \
	USE(OUT,          "out") \
	USE(ELSE,         "else") \
	USE(WHILE,        "while") \
	USE(RETURN,       "return") 

#define LITERALS_TABLE \
	USE(STRING,    	"string") \
	USE(NUMBER,		"number") 

#define SINGLE_CHAR_SYMBOLS_TABLE \
    USE(LEFT_PAREN,    '(') \
    USE(RIGHT_PAREN,   ')') \
    USE(LEFT_BRACE,    '{') \
    USE(RIGHT_BRACE,   '}') \
    USE(COMMA,         ',') \
    USE(DOT,           '.') \
    USE(MINUS,         '-') \
    USE(PLUS,          '+') \
    USE(SEMICOLON,     ';') \
    USE(SLASH,         '/') \
    USE(STAR,          '*') \
    USE(AT,            '@') \
    USE(BANG,          '!') \
    USE(EQUAL,         '=') \
    USE(GREATER,       '>') \
    USE(LESS,          '<') 

#define SYMBOLS_TABLE \
    USE(BANG_EQUAL,    "!=") \
    USE(EQUAL_EQUAL,   "==") \
    USE(GREATER_EQUAL, ">=") \
    USE(LESS_EQUAL,    "<=") \
    USE(AND,           "&&") \
    USE(OR,            "||")

typedef enum tokentype_e {

	/*  Expand xmacro to:
	 *	OUT,
	 *	ELSE,
	 *	...
	 */

	/* Keywords */
  	#define USE(Type, String) Type,
        KEYWORDS_TABLE
  	#undef USE

	/* Literals */
  	#define USE(Type, String) Type,
        LITERALS_TABLE
  	#undef USE

	/* Single Char Symbols */
  	#define USE(Type, String) Type,
        SINGLE_CHAR_SYMBOLS_TABLE
  	#undef USE

	/* Symbols */
  	#define USE(Type, String) Type,
        SYMBOLS_TABLE
  	#undef USE

	/* There's no related type */
	TOKEN_NULL
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
	substr_s 	      lexme;
	literal_u 		literal;
	unsigned int 	line;
} 
token_s;

/* Initializes *token, it may not use malloc for any atribute */
void init_token(token_s *token, tokentype_e type, substr_s lexme);

/* Prints token's lexme */
void print_token(token_s *token);

/* Return a token matching *keyword */
tokentype_e match_keyword(substr_s *keyword);

#endif
