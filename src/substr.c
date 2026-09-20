#include <stdio.h>
#include "substr.h"

void substr_print(substr_s substr) {

    printf("%.*s", (int) substr.length, substr.begin);
}