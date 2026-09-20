#include <stdlib.h>

#include "token_array.h"

/* Initializes the dynamic array to an empty state */
void token_array_init(token_array_s *arr) {
	arr->data = NULL;
	arr->count = 0;
	arr->capacity = 0;
}

/*
 	Appends a token to the array.
 	Returns 1 on success, 0 on memory allocation failure 
 */
int token_array_push(token_array_s *arr, token_s token) {
	if (arr->count >= arr->capacity) {
		size_t new_capacity = (arr->capacity == 0) ? 8 : arr->capacity * 2;
		
		/* Safe realloc pattern: avoid overwriting arr->data on failure */
		token_s *new_data = realloc(arr->data, new_capacity * sizeof(token_s));
		if (new_data == NULL) {
			return 0; /* Allocation failed */
		}

		arr->data = new_data;
		arr->capacity = new_capacity;
	}

	arr->data[arr->count++] = token;
	return 1;
}

/*
 	Frees the memory allocated for the array data.
	If token_s contains heap-allocated string literals, 
	free those individually before calling this function.
*/
void token_array_free(token_array_s *arr) {
	free(arr->data);
	arr->data = NULL;
	arr->count = 0;
	arr->capacity = 0;
}