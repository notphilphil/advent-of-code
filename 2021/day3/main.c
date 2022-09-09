#include <errno.h>
#include <math.h>
#include <stdbool.h>

#include "main.h"

int main() {
	int data_len;
	char **data_array = open_and_read_file("It's time for day 3!", "input_d3", &data_len);

	int num_of_bits = strlen(data_array[0]) - 1;
	int *bit_counts = count_bits(data_array, data_len, num_of_bits);

	int gamma, epsilon;
	get_gamma_and_epsilon(bit_counts, num_of_bits, &gamma, &epsilon);

	printf("Found gamma and epsilon to be (%d, %d) => gamma * epsilon = %d\n", gamma, epsilon, gamma * epsilon);

	return 0;
}

void get_gamma_and_epsilon(int *bit_counts, int num_of_bits, int *gamma, int *epsilon) {
	// bit_counts contains only counts of bits, not with a positive number representing more 1's and a negative number representing more 0's
	// gamma: most common bits
	// epsilon: least common bits (opposite of gamma)
	// NOTE: little-endian format
	bool is_one;
	*gamma = 0;
	*epsilon = 0;
	for (int i = 0; i < num_of_bits; i++) {
		is_one = bit_counts[num_of_bits - 1 - i] > 0;
		*gamma += ((int)pow(2, i)) * is_one;
		*epsilon += ((int)pow(2, i)) * !is_one;
	}
}

int* count_bits(char **data_array, int data_len, int num_of_bits) {
	int *bit_buckets = (int*)malloc(sizeof(int) * num_of_bits);
	memset(bit_buckets, 0, sizeof(int) * num_of_bits);

	char *curr;
	for (int i = 0; i < data_len; i++) {
		curr = data_array[i];
		for (int j = 0; j < num_of_bits; j++) {
			if (curr[j] == '0') {
				bit_buckets[j]--;
			} else if (curr[j] == '1') {
				bit_buckets[j]++;
			} else {
				fprintf(stderr, "Ran into a bit that's not 0 or 1! [%c]\n", curr[j]);
			}
		}
	}

	return bit_buckets;
}
