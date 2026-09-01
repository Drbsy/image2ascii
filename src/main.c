#include "file_utils.h"
#include "stb_impl.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libgen.h>


typedef struct 
{
    const char* name;
    const char* flag;
    int scale;
} SizeOption;

int get_size_index(const char *size_flag, const SizeOption *sizes, int sizes_len);

int main(int argc, char *argv[])
{
    char *executable_name = basename(argv[0]);

    //check if the arguments count is valid.
    if (argc > 3 && argc > 1)
    {
        printf( "Usage error : Invalid args.\n"
                "help        : %s -h or %s -help."
                ,  executable_name, executable_name);
        return 1;
    }
    
    //check if the user requested help flags.
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0)
    {
        printf( "Usage:\n"
                "       help        : %s -h or %s -help.\n"
                "       img2ascii   : %s \"Image_Path\" -(size).\n"
                "       sizes       : small             = -s    || 1/24.\n"
                "                     medium            = -m    || 1/12.\n"
                "                     large             = -l    || 1/6 .\n"
                "                     extra large       = -xl   || 1/3 .\n"
                "                     extra extra large = -xxl  || 1/1 .\n"
            , executable_name, executable_name, executable_name);
    }
    
    //create an array of sizes -s -m -l -xl -xxl.
    SizeOption sizes[5] = {
            {"small"            , "-s"  , 24 },   
            {"medium"           , "-m"  , 12 },
            {"large"            , "-l"  , 6  },
            {"extra large"      , "-xl" , 3  },
            {"extra extra large", "-xxl", 1  },
    };

    //calculate the number of sizes in sizes.
    int sizes_len = sizeof(sizes) / sizeof(sizes[0]);

    //get the file path.
    char* file_path = argv[1];
    //get the file format.
    char *file_format = get_file_format(file_path);

    //cheak if path exists.
    if (is_file_exists(file_path) == false)
    {
        printf("Path error : Invalid file pathd \"%s\" ." , file_path);
        return 2;
    }

    //cheak if the file format supported.
    if (is_valid_format(file_format) == false)
    {
        printf("Invalid file format");
        return 3;
    }
    
    //open image content.
    int width, height, num_channels;
    unsigned char *image = load_image(file_path, &width, &height, &num_channels);
    //cheak if the image loaded correctly.
    if (image == NULL)
    {
        printf("Error : Faild to load image.");
        return 4;
    }
    //cheak image dimensions.
    if (width <= 0 || height <= 0 || num_channels <= 0)
    {
        printf("Error : Invalid image dimensions or corrupted file.");
        image_free(image);
        return 5;
    }

    //check if the size flag is valid.
    char *size_flag = argv[2];
    int size_index = get_size_index(size_flag, sizes, sizes_len);

    /*
        Check if the index is valid.
        -1 means the user provided the size flag,but the value is invalid.
    */
    if (size_index == -1)
    {
        printf( "Input Error: Invalid size flag.\n"
                "help        : %s -h or %s -help."
                ,  executable_name, executable_name);
        image_free(image);
        return 6;
    }

    int final_width =   (int)((float)width  / (float)sizes[size_index].scale);
    //divide by 2 to account for the aspect ratio of characters in the terminal.
    int final_height =  (int)((float)height / (float)sizes[size_index].scale / 2.0);
    //resize image.
    unsigned char *resized_image = resize_image(image, width, height, 0,
                                                final_width, final_height, 0,
                                                num_channels, num_channels);

    //check if the image was resized successfully.
    if (resized_image == NULL)
    {
        printf("Error : Faild to resize image.");
        image_free(image);
        return 7;
    }

    //transform image into ascii.
    char *ascii_art = image_2_ascii(resized_image, final_width, final_height, num_channels);
    if (ascii_art == NULL) 
    {
        printf("Error : Faild to transform image into ascii.");
        image_free(image);
        return 8;
    }

    //print the output
    printf("%s", ascii_art);


    free(ascii_art);
    image_free(resized_image);
    image_free(image);
    free(file_format);
    return 0;
}

int get_size_index(const char *size_flag, const SizeOption *sizes, int sizes_len)
{
    //check if the size flag is NULL or empty
    if (size_flag == NULL || *size_flag == '\0')
    {
        return 1; //return 1 as a default size (medium) 
    }
    else
    {
        //loop through all available size options
        for (int i = 0; i < sizes_len ; i++)
        {
            if (strcasecmp(size_flag, sizes[i].flag) == 0)
            {
                return i;
                break;
            }
        }
    }
    return -1;   
}