#ifndef HEADER_MELON_TOKEN
#define HEADER_MELON_TOKEN

#include <stddef.h> /* for size_t in substr_s */
#include <ctype.h>
#include "substr.h"

/* Macros Tables
 *
 *    USE( int Type, char *Strings )
 *    USE( int Type, char Char )
 *    USE( char FirstCh, int OneType, char SecondCh, int TwoType )
 */
#define KEYWORDS_TABLE 				\
	USE(IF,			"if") 			\
	USE(FOR,		"for") 			\
	USE(OUT,		"out") 			\
	USE(LIB,		"lib") 			\
	USE(DEF,		"def") 			\
	USE(ELSE,		"else") 		\
	USE(WHILE,		"while") 		\
	USE(RETURN,		"return") 

typedef enum tokentype_e {

	/* There's no related type */
	TOKEN_NULL = 0,

	/* OUT = 1
	 * FOR = 2
	 * LIB = 3
	 * ...
	 */
  	#define USE(Type, String) Type,
        KEYWORDS_TABLE
  	#undef USE

	/* Literals */
  	STRING,
	NUMBER,
	IDENTIFIER,

	/* Double symbols */
	LESS_EQUAL,
    GREATER_EQUAL,
    BANG_EQUAL,
    EQUAL_EQUAL,

	/* Symbols */
    BANG        = 33,  /* ! */
    QUOTE       = 34,  /* " */
    HASH        = 35,  /* # */
    DOLLAR      = 36,  /* $ */
    PERCENT     = 37,  /* % */
    AMPERSAND   = 38,  /* & */
    APOSTROPHE  = 39,  /* ' */
    LEFT_PAREN  = 40,  /* ( */
    RIGHT_PAREN = 41,  /* ) */
    ASTERISK    = 42,  /* * */
    PLUS        = 43,  /* + */
    COMMA       = 44,  /* , */
    MINUS       = 45,  /* - */
    PERIOD      = 46,  /* . */
    SLASH       = 47,  /* / */

    COLON       = 58,  /* : */
    SEMICOLON   = 59,  /* ; */
    LESS        = 60,  /* < */
    EQUAL       = 61,  /* = */
    GREATER     = 62,  /* > */
    QUESTION    = 63,  /* ? */
    AT          = 64,  /* @ */

    LEFT_BRACK  = 91,  /* [ */
    BACKSLASH   = 92,  /* \ */
    RIGHT_BRACK = 93,  /* ] */
    CARET       = 94,  /* ^ */
    UNDERSCORE  = 95,  /* _ */
    GRAVE       = 96,  /* ` */

    LEFT_BRACE  = 123, /* { */
    PIPE        = 124, /* | */
    RIGHT_BRACE = 125, /* } */
    TILDE       = 126, /* ~ */

	/* To know exactly when the 
	 * token array ends 
	 */
	TOKEN_EOF
}
tokentype_e;

/* A single token produced by the lexer */
typedef struct token_s {
	tokentype_e	type;
	substr_s 	lexme;
	size_t 		line;
} 
token_s;

/* Initializes *token, it may not use malloc for any atribute */
void set_token(token_s *token, tokentype_e type, substr_s lexme);

/* Prints token's lexme */
void print_token(token_s *token);

/* Return a token matching *keyword */
tokentype_e match_keyword(substr_s *keyword);

#endif
