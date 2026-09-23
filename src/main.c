#include "file_utils.h"
#include "stb_impl.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
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

    int saliency_threshold = -1;
    int new_argc = 1;
    char **new_argv = malloc((argc + 1) * sizeof(char *));
    new_argv[0] = argv[0];

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-salience") == 0 || strcmp(argv[i], "-sal") == 0)
        {
            if (i + 1 < argc && argv[i + 1][0] != '-')
            {
                saliency_threshold = atoi(argv[i + 1]);
                i++;
            }
            else
            {
                saliency_threshold = 128;
            }
        }
        else
        {
            new_argv[new_argc++] = argv[i];
        }
    }
    new_argv[new_argc] = NULL;

    if (new_argc < 2 || new_argc > 4)
    {
        printf( "Usage error : Invalid args.\n"
                "help        : %s -h or %s -help.\n"
                ,  executable_name, executable_name);
        free(new_argv);
        return 1;
    }
    
    if (strcmp(new_argv[1], "-h") == 0 || strcmp(new_argv[1], "-help") == 0)
    {
       printf( "Usage:\n"
                "       help        : %s -h or %s -help.\n"
                "       img2ascii   : %s \"Image_Path\" -(size) [options]\n"
                "       sizes       : small             = -s    || 1/24.\n"
                "                     medium            = -m    || 1/12.\n"
                "                     large             = -l    || 1/6 .\n"
                "                     extra large       = -xl   || 1/3 .\n"
                "                     extra extra large = -xxl  || 1/1 .\n"
                "                     custom line lengh = -llen || custom line length.\n"
                "       options     : -salience [val]   = -sal  || Apply saliency threshold (e.g., -sal 140).\n"
            , executable_name, executable_name, executable_name);
        free(new_argv);
        return 0;
    }
    
    SizeOption sizes[6] = {
            {"small"             , "-s"   , 24   },   
            {"medium"            , "-m"   , 12   },
            {"large"             , "-l"   , 6    },
            {"extra large"       , "-xl"  , 3    },
            {"extra extra large ", "-xxl" , 1    },
            {"costom line lenght", "-llen", -2   }
    };

    int sizes_len = sizeof(sizes) / sizeof(sizes[0]);

    char* file_path = new_argv[1];
    char *file_format = get_file_format(file_path);

    if (is_file_exists(file_path) == false)
    {
        printf("Path error : Invalid file pathd \"%s\" ." , file_path);
        free(new_argv);
        return 2;
    }

    if (is_valid_format(file_format) == false)
    {
        printf("Invalid file format");
        free(new_argv);
        return 3;
    }
    
    int width, height, num_channels;
    unsigned char *image = load_image(file_path, &width, &height, &num_channels);
    if (image == NULL)
    {
        printf("Error : Faild to load image.");
        free(new_argv);
        return 4;
    }
    if (width <= 0 || height <= 0 || num_channels <= 0)
    {
        printf("Error : Invalid image dimensions or corrupted file.");
        image_free(image);
        free(new_argv);
        return 5;
    }

    char *size_flag = new_argv[2];
    int size_index = get_size_index(size_flag, sizes, sizes_len);

    float scale = 0;
    if (size_index == -1)
    {
        printf( "Input Error: Invalid size flag.\n"
                "help        : %s -h or %s -help.\n"
                ,  executable_name, executable_name);
        image_free(image);
        free(new_argv);
        return 6;
    }
    else if (sizes[size_index].scale == -2)
    {
        size_t line_len = abs(atoi(new_argv[3]));
        scale =  get_llen_scale(width, line_len); 
    }
    else
    {
        scale = sizes[size_index].scale;
    }
    
    int final_width =   (int)((float)width  / scale);
    int final_height =  (int)(((float)height / scale)/ 2.0);
    
    unsigned char *resized_image = resize_image(image, width, height, 0,
                                                final_width, final_height, 0,
                                                num_channels, num_channels);

    if (resized_image == NULL)
    {
        printf("Error : Faild to resize image.");
        image_free(image);
        free(new_argv);
        return 8;
    }

    char *ascii_art = image_2_ascii(resized_image, final_width, final_height, num_channels, saliency_threshold);
    if (ascii_art == NULL) 
    {
        printf("Error : Faild to transform image into ascii.");
        image_free(image);
        free(new_argv);
        return 9;
    }

    printf("%s", ascii_art);

    free(ascii_art);
    image_free(resized_image);
    image_free(image);
    free(file_format);
    free(new_argv);
    return 0;
}

int get_size_index(const char *size_flag, const SizeOption *sizes, int sizes_len)
{
    if (size_flag == NULL || *size_flag == '\0')
    {
        return 1; 
    }
    else
    {
        for (int i = 0; i < sizes_len ; i++)
        {
            if (strcasecmp(size_flag, sizes[i].flag) == 0)
            {
                return i;
            }
        }
    }
    return -1;   
}