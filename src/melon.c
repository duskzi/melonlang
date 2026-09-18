#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {

	/* 
		Try open file passed as argument:
			argv[0]: Program's name
			argv[1]: File to run  
	*/
	if(argc < 1) {
		printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}

	
	FILE *fp = fopen(argv[1], "rb");

	if(fp == NULL) {
		printf("Failed to open %s\n", argv[1]);
		return 1;
	}

	/* Set stream pointer to end of file*/
	fseek(fp, 0, SEEK_END);

	/* Get length in bytes */
	long length = ftell(fp);

	printf("%li\n", length);

	return 0;
}
