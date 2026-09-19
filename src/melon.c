#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "error.h"

typedef struct substr_s {
	char *begin;
	size_t length;
} 
substr_s;

typedef union literal_u {
	float fnum;
	int inum;
	char *str;
} 
literal_u;

typedef struct token_s {
	tokentype_e type;
	substr_s lexme;
	literal_u literal;
	unsigned int line;
} 
token_s;

/* Dynamic array structure */
typedef struct {
	token_s *data;
	size_t count;
	size_t capacity;
} token_array_s;

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

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		ERROR_RETURN(1, "Usage: %s <filename>", argv[0]);
	}

	LOG_DEBUG("Opening source file: %s", argv[1]);

	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		ERROR_RETURN(1, "Failed to open file '%s'", argv[1]);
	}

	/* Get file size */
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if (length < 0) {
		fclose(fp);
		ERROR_RETURN(1, "Failed to determine file size for '%s'", argv[1]);
	}

	LOG_DEBUG("File size: %ld bytes", length);

	/* Allocate memory for file content + null terminator */
	char *file = malloc((size_t)length + 1);
	if (file == NULL) {
		fclose(fp);
		ERROR_RETURN(1, "Memory allocation failed for file buffer");
	}

	/* Read file content */
	size_t bytes_read = fread(file, sizeof(char), (size_t)length, fp);
	fclose(fp);

	if (bytes_read != (size_t)length) {
		free(file);
		ERROR_RETURN(1, "Failed to read entire file (read %zu of %ld bytes)", bytes_read, length);
	}

	file[length] = '\0'; /* Correct null terminator placement */
	LOG_DEBUG("Loaded file buffer into memory");
	

	token_array_s tokens;
	token_array_init(&tokens);

	size_t 	index = 0;
	int 	line = 0;
	char   	*c;
	
	while(*(c = &file[index]) != '\0') {

		/* TODO: Find tokens */

		token_s token = {};
		
		if (!token_array_push(&tokens, token)) {
		
			token_array_free(&tokens);
			free(file);
			
			ERROR_RETURN(1, "Failed to push token in line: %d", line);
		}
		
		index++;
	}

	token_array_free(&tokens);
	free(file);

	return 0;
}
