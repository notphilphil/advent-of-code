#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef MY_COMMON_HEADER
#define MY_COMMON_HEADER

char** open_and_read_file(char *title, const char *_default_file_name, int *data_len);
char* get_file_name(char *title, const char *_default_file_name);
FILE* open_file(char *file_name);
char** read_file(FILE *fp, int *file_len);


#endif
