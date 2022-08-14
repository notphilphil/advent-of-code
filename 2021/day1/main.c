#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#include "main.h"

int main() {
	// Variable declarations...
	char *fileName, *fileLine = NULL;
	size_t alloc_len = 0;
	ssize_t len = 0;
	FILE* fp = NULL;
	int curr, prev = -1;
	int count = 0;

	// Reading file name from standard in
	printf("Please enter input file name (or nothing for \"%s\"): ", DEFAULT_INPUT_FILE_NAME);
	len = getline(&fileName, &alloc_len, stdin);
	if (-1 == len) {
		printf("getline() failed with errno=%d\n", errno);
		exit(errno);
	}

	// Opening file...
	if (1 < len) {
		// Some file name was entered from std in
		// len includes null terminator so the length of what we really want is n + 1
		fileName[len-1] = '\0';
		fp = fopen(fileName, "r");
	} else {
		// No file name from std in, use default
		fp = fopen(DEFAULT_INPUT_FILE_NAME, "r");
	}

	if (NULL == fp) {
		perror("Error while opening file.\n");
		exit(errno);
	}

	// Reading file...
	printf("Reading file contents...\n");
	while(getline(&fileLine, &len, fp) >= 0) {
		curr = atoi(fileLine);
		if (-1 != curr && -1 != prev) {
			if (curr - prev > 0) {
				count++;
			}
		}
		prev = curr;
	}

	printf("\nFinal count of increasing sequences is: %d\n", count);

	// Clean up...
	if (-1 == fclose(fp)) {
		perror("Error while closing file.\n");
		exit(errno);
	}

	free(fileLine);
	return 0;
}
