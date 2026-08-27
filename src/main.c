#include "bmp.h"
#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

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

    
    char *tmp = bmp2ascii( fname);
    if (tmp == NULL)
    {
        //TODO ERROR message
        printf("Error : TODO");
        return 4;
    }
    printf("%s", tmp);

    return 0;
}

