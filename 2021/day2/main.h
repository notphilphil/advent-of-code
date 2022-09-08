#include "../my_common_lib.h"

void free_data_array(char **data_array, int data_len);
void find_x_and_y(char **data_array, int len, int *x, int *y);
void find_aim_x_and_y(char **data_array, int len, int *aim, int *x, int *y);
void get_move_and_dist(char *instruction, char *move, int *dist);
