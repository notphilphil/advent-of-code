#include <errno.h>

#include "main.h"

int main() {
	int data_len;
	char **data_array = open_and_read_file("Welcome to day 2!", "input", &data_len);

	int x, y, aim;

	printf("Solving part 1...\n");
	find_x_and_y(data_array, data_len, &x, &y);
	printf("Found x and y to be (%d, %d) => x * y = %d\n", x, y, x * y);

	printf("Solving part 2...\n");
	find_aim_x_and_y(data_array, data_len, &aim, &x, &y);
	printf("Found aim, x, and y to be (%d, %d, %d) => x * y = %d\n", aim, x, y, x * y);

	free_data_array(data_array, data_len);
	return 0;
}

void find_x_and_y(char **data_array, int len, int *x, int *y) {
	*x = 0;
	*y = 0;

	char *move = (char*)malloc(sizeof(char) * 12);
	int dist;

	for (int i = 0; i < len; i++) {
		get_move_and_dist(data_array[i], move, &dist);
		// printf("Went %s with a distance of %d\n", move, dist);
		if (strcmp(move, "forward") == 0) {
			*x += dist;
		} else if (strcmp(move, "down") == 0) {
			*y += dist;
		} else if (strcmp(move, "up") == 0) {
			*y -= dist;
		} else {
			fprintf(stderr, "Oops, found an move we don't know how to deal with [%s] at line [%d}", move, i);
		}
	}
}

void find_aim_x_and_y(char **data_array, int len, int *aim, int *x, int *y) {
	*aim = 0;
	*x = 0;
	*y = 0;

	char *move = (char*)malloc(sizeof(char) * 12);
	int dist;

	for (int i = 0; i < len; i++) {
		get_move_and_dist(data_array[i], move, &dist);
		if (strcmp(move, "forward") == 0) {
			*x += dist;
			*y += (*aim) * dist;
		} else if (strcmp(move, "down") == 0) {
			*aim += dist;
		} else if (strcmp(move, "up") == 0) {
			*aim -= dist;
		} else {
			fprintf(stderr, "Oops, found an move we don't know how to deal with [%s] at line [%d}", move, i);
		}
	}
}

void get_move_and_dist(char *instruction, char *move, int *dist) {
	memset(move, 0, strlen(move));

	int idx = 0;
	while (instruction[idx] != ' ') {
		idx++;
	}
	strncpy(move, instruction, idx);
	 *dist = atoi(instruction + idx + 1);
}

void free_data_array(char **data_array, int data_len) {
	for (int i = 0; i < data_len; i++) {
		free(data_array[i]);
	}
	free(data_array);
}
