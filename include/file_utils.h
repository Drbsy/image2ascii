#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4
#endif

bool is_file_exists(char* fname);
bool is_valid_format(char* f_format);
char *get_file_format(char* fname);
void rev_string(char* string);

#endif 