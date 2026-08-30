#include "bmp.h"
#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


#define TARGET_HEIGHT 128
#define TARGET_WIDTH 128

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage error: Invalid args.");
        return 1;
    }
    
    char* fname = argv[1];
    char *f_format = get_file_format(fname);
    
    if (is_file_exists(fname) == false)
    {
        printf("Path error : Invalid file pathd \"%s\" ." , fname);
        return 2;
    }
    if (is_valid_format(f_format) == false)
    {
        printf("Invalid file format");
        return 3;
    }

    
    char *tmp = bmp2ascii(fname, TARGET_HEIGHT, TARGET_WIDTH);
    if (tmp == NULL)
    {
        printf("Error : faild to convert the bmp image.");
        return 4;
    }
    printf("%s", tmp);

    free(f_format);
    free(tmp);
    return 0;
}

