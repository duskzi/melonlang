#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "lexer.h"
#include "token.h"
#include "token_array.h"

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

	/* TODO: Actual tokenization is not implemented yet */
	if (!scan_tokens(file, &tokens)) {
		token_array_free(&tokens);
		free(file);
		return 1;
	}

	for (size_t i = 0; i < tokens.count; i++) {
		print_token(&tokens.data[i]);
	}

	token_array_free(&tokens);
	free(file);

	return 0;
}