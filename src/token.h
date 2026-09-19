#ifndef HEADER_MELON_TOKEN
#define HEADER_MELON_TOKEN

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
  AND, CLASS, ELSE, FALSE, FOR, IF, NLL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
}
tokentype_e;

#endif
