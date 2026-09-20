#ifndef HEADER_MELON_LEXER
#define HEADER_MELON_LEXER

#include "token_array.h"

/*
 	Scans the source buffer and appends the found tokens
 	to the given array.
 	Returns 1 on success, 0 on failure.
 */
int scan_tokens(char *source, token_array_s *tokens);

#endif