#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<math.h>

#include "main.h"

int main() {
	solve_part_1();
	solve_part_2();
	return 0;
}

void solve_part_1() {
	char *file_name = NULL;
	FILE *fp = NULL;
	int *measurements = NULL;
	int count = 0, len = 0;

	get_file_name(&file_name, "Part 1", DEFAULT_INPUT_FILE_NAME);
	open_file(&fp, file_name);
	read_file(fp, &measurements, &len);
	count_measurements(measurements, &count, len);
	printf("Results for part 1: %d\n", count);
}

void solve_part_2() {
	char *file_name = NULL;
	FILE *fp = NULL;
	int *measurements = NULL;
	int count = 0, len = 0;

	get_file_name(&file_name, "Part 2", DEFAULT_INPUT_FILE_NAME);
	open_file(&fp, file_name);
	read_file(fp, &measurements, &len);
	group_and_count_measurements(measurements, &count, len);
	printf("Results for part 2: %d\n", count);
}

void get_file_name(char **file_name, char *title, const char *_default) {
	size_t alloc_len = 0;
	ssize_t len = 0;
	printf("%s:\nPlease enter input file name (or nothing for \"%s\"): ", title, _default);
	len = getline(file_name, &alloc_len, stdin);
	if (-1 == len) {
		printf("getline() failed with errno=%d\n", errno);
		exit(errno);
	}
	if (1 < len) {
		// Some file name was entered from std in
		// len includes null terminator so the length of what we really want is n + 1
		(*file_name)[len-1] = '\0';
	} else {
		// No file name from std in, use default
		strcpy(*file_name, DEFAULT_INPUT_FILE_NAME);
	}
	printf("Final file name: [%s]\n", *file_name);
}

void open_file(FILE **fp, char *file_name) {
	*fp = fopen(file_name, "r");
	if (NULL == fp) {
		perror("Error while opening file");
		exit(errno);
	}
}

void read_file(FILE *fp, int **measurements, int *data_len) {
	char *file_line = NULL;
	int curr_max_len = INIT_ARRAY_SIZE;
	ssize_t len = 0;
	*measurements = (int *)malloc(sizeof(int) * INIT_ARRAY_SIZE);
	while(getline(&file_line, &len, fp) >= 0) {
		if (*data_len == curr_max_len) {
			*measurements = (int *)realloc(*measurements, sizeof(int) * (curr_max_len * 2));
			curr_max_len *= 2;
			// Should probably do checks on this...
		}
		(*measurements)[*data_len] = atoi(file_line);
		*data_len = (*data_len) + 1;
	}
}

void group_and_count_measurements(int *measurements, int *count, int len) {
	int *grouped_measurements = (int *)malloc(sizeof(int) * (len/3));
	int grouped_len = 0;
	
	for (int i = 1; i < len - 1; i++) {
		grouped_measurements[grouped_len++] = measurements[i-1] + measurements[i] + measurements[i+1];
	}

	count_measurements(grouped_measurements, count, grouped_len);
}

void count_measurements(int *measurements, int *count, int len) {
	int curr, prev = -1;
	for (int i = 0; i < len; i++) {
		curr = measurements[i];
		if (prev != -1 && measurements[i-1] < measurements[i]) {
			*count = (*count) + 1;
		}
		prev = curr;
	}
}
