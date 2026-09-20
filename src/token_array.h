#ifndef HEADER_MELON_TOKEN_ARRAY
#define HEADER_MELON_TOKEN_ARRAY

#include <stddef.h>

#include "token.h"

/* Dynamic array structure */
typedef struct {
	token_s    *data;
	size_t 		count;
	size_t 		capacity;
} 
token_array_s;

/* Initializes the dynamic array to an empty state */
void token_array_init(token_array_s *arr);

/*
 	Appends a token to the array.
 	Returns 1 on success, 0 on memory allocation failure 
*/
int token_array_push(token_array_s *arr, token_s token);

/*
 	Frees the memory allocated for the array data.
	If token_s contains heap-allocated string literals, 
	free those individually before calling this function.
*/
void token_array_free(token_array_s *arr);

#endif