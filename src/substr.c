#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "substr.h"

/*
typedef struct substr_s {
	char   *begin;
	size_t 	length;
} 
substr_s;
*/

bool substr_cmp(substr_s *substr, const char *keyword) {
    size_t keyword_length = strlen(keyword);

    if (substr->length != keyword_length)
        return false;

    return memcmp(substr->begin, keyword, substr->length) == 0;
}

void substr_print(substr_s substr) {

    printf("%.*s", (int) substr.length, substr.begin);
}