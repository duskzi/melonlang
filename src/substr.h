#ifndef HEADER_SUBSTRING
#define HEADER_SUBSTRING

#include <stdlib.h>
#include <stdio.h>

typedef struct substr_s {
	char   *begin;
	size_t 	length;
} 
substr_s;

void substr_print(substr_s substr);

#endif