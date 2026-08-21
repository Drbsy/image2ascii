#include "utils.h"
#include <stdio.h>
#include "file_utils.h"

bool are_args_valid(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage error: Invalid args.");
        return false;
    }
    
    char* fname = argv[1];
    if (is_file_exists(fname) == false)
    {
        printf("Path error : Invalid file pathd \"%s\" ." , fname);
        return false;
    }

    char *f_format = get_file_format(fname);
    if (is_valid_format(f_format) == false)
    {
        printf("Invalid file format");
        return false;
    }

    return true;
}
