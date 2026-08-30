#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

bool is_file_exists(char* fname)
{
    struct stat buffer;
    return (stat (fname, &buffer) == 0);
}

bool is_valid_format(char* f_format)
{
    char* formats[] = {"bmp"};
    size_t formats_len = sizeof(formats) / sizeof(formats[0]); 
   
    if (f_format == NULL) 
    {
        return false;
    }

    for (size_t i = 0; i < formats_len; i++)
    {
        if (strcmp(formats[i], f_format) == 0)
        {
            return true;
        }
    }
    return false;
}

char *get_file_format(char* fname)
{
    size_t fname_len = strlen(fname);
    char *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL)
    {
        return NULL;
    }
    size_t current_size = BUFFER_SIZE;
    size_t current_len = 0;
    for (size_t i = fname_len; i > 0 ; i--)
    {
        if (fname[i - 1] == '.')
        {
            break;
        }
        if (current_size - current_len <= 1)
        {
            current_size += BUFFER_SIZE;
            char *tmp = realloc(buffer, current_size);
            if (tmp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            current_size += BUFFER_SIZE;
        }
        buffer[current_len++] = fname[i - 1];
    }
    buffer[current_len] = '\0';

    rev_string(buffer);
    return buffer;
}

void rev_string(char* string)
{
    size_t left = 0;
    size_t right = strlen(string) -1;
    char tmp;
    while (left < right)
    {
        tmp = string[left];
        string[left] = string[right];
        string[right] = tmp;
        left++;
        right--;
    }
}

