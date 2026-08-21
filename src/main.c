#include <stdio.h>
#include "file_utils.h"
#include "utils.h"
#include "bmp.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "img_to_ascii.h"


int main(int argc, char *argv[])
{
    if (are_args_valid(argc,argv) == false)
    {
        return 1;
    }

    char* fname = argv[1];
    char *f_format = get_file_format(fname);

    FILE *image;
    BMPFILEHEADER file_header;
    BMPIMAGEHEADER image_header;

    image = fopen(fname, "rb");

    if(!image) {
        printf("Error: could'nt open the file %s.", fname);
        return 1;
    }
    
    fread(&file_header, sizeof(file_header), 1, image);
    fread(&image_header, sizeof(image_header), 1, image);

    if (file_header.bfType != 0x4d42 || file_header.bfOffBits != 54 || image_header.biSize != 40 || image_header.biBitCount != 24 || image_header.biCompression != 0)
    {
        printf("Error: unsupported \"%s\" file.\n", f_format); 
        fclose(image);
        return 1;
    }

    
    int height = (image_header.biHeight);
    int width = image_header.biWidth;

    print_bmp_info(&file_header, &image_header);
    
    fseek(image, file_header.bfOffBits, SEEK_SET);

    RGBTRIPLE(*tmp_image)[width] = malloc(abs(height) * sizeof(*tmp_image));
    if (tmp_image == NULL)
    {
        printf("Error : not enough memory to store image.");
        fclose(image);
        return 1;
    }

    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0; i < abs(height); i++)
    {
        fread(tmp_image[i], sizeof(RGBTRIPLE), width, image);
        fseek(image, padding, SEEK_CUR); 
    }

    print_ascci_art(height, width, tmp_image);

    free(tmp_image);
    fclose(image); 
    return 0;
}

