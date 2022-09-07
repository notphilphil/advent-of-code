#include <errno.h>

#include "my_common_lib.h"

char** open_and_read_file(char *title, const char *_default_file_name, int *data_len) {
	char *file_name = get_file_name(title, _default_file_name);
       	if (file_name == NULL) {
	        fprintf(stderr, "Something went wrong when using get_file_name()\n");
		exit(errno);
	}

	FILE *data_file = open_file(file_name);
        if (data_file == NULL) {
		fprintf(stderr, "Something went wrong when using open_file()\n");
		exit(errno);
	}

        char **file_contents = read_file(data_file, data_len);
	if (file_contents == NULL) {
		fprintf(stderr, "Something went wrong when using read_file()\n");
		exit(errno);
	}

	free(file_name);
	fclose(data_file);

	return file_contents;
}

/*
 * Get file name using standard input.
 * 
 * title: preface (if any) when asking for input in std_out
 * _default_file_name: default file name if none gathered from std_in
 *
 * char* pointing to malloc'd file name is returned. make sure to free()!
 */
char* get_file_name(char *title, const char *_default_file_name) {
	size_t allocated_size = 0;
	ssize_t str_len;
	char *line_ptr;
	printf("%s\nPlease enter name of input file (or enter nothing for default: %s): ", title, _default_file_name);
	str_len = getline(&line_ptr, &allocated_size, stdin);
	if (str_len == -1) {
		fprintf(stderr, "Error getline()'ing...\n\terrno: %d", errno);
		exit(errno);
	}

	char *file_name;

	// TODO add error handling for malloc and strcpy/strncpy	
	if (str_len == 1) {
		file_name = (char *)malloc(sizeof(char) * strlen(_default_file_name));
		strcpy(file_name, _default_file_name);
	} else {
		// malloc and strncpy 1 less than str_len to remove \n character
		file_name = (char *)malloc(sizeof(char) * (str_len-1));
		strncpy(file_name, line_ptr, str_len-1);
	}

	free(line_ptr);

	return file_name;
}

FILE* open_file(char *file_name) {
	FILE *file = fopen(file_name, "r");
	if (file == NULL) {
		fprintf(stderr, "Something went wrong while opening file with name [%s]\n", file_name);
	}
	return file;
}

char** read_file(FILE *fp, int *file_len) {
	int current_arr_size = 128;
	*file_len = 0;
	char **file_contents = (char **)malloc(sizeof(char *) * current_arr_size);
	size_t allocated_size = 0;
	ssize_t line_len;
	char *line_ptr;
	while ((line_len = getline(&line_ptr, &allocated_size, fp)) > -1) {
		if (*file_len == current_arr_size) {
			current_arr_size *= 2;
			file_contents = (char **)realloc(file_contents, sizeof(char*) * current_arr_size);
		}
		file_contents[*file_len] = (char*)malloc(sizeof(char) * line_len);
		strcpy(file_contents[*file_len], line_ptr);
		*file_len = (*file_len) + 1;
	}
	return file_contents;
}
