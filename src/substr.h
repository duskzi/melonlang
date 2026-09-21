#ifndef HEADER_SUBSTRING
#define HEADER_SUBSTRING

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct substr_s {
	char   *begin;
	size_t 	length;
} 
substr_s;

void substr_print(substr_s substr);
bool substr_cmp(substr_s *substr, const char *keyword);

#endif