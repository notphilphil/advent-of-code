#ifndef HEADER_FILE
#define HEADER_FILE

const char* DEFAULT_INPUT_FILE_NAME = "input";
const int INIT_ARRAY_SIZE = 128;

void solve_part_1(void);
void solve_part_2(void);
void get_file_name(char **file_name, char *title, const char *_default);
void open_file(FILE **fp, char *file_name);
void read_file(FILE *fp, int **measurements, int *len);
void group_and_count_measurements(int *measurements, int *count, int len);
void count_measurements(int *measurements, int *count, int len);

#endif
