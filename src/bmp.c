#include "bmp.h"
#include "file_utils.h"
#include "utils.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

RGBTRIPLE** image_scaling(size_t original_width, size_t original_height, size_t target_width, size_t target_height, RGBTRIPLE image[original_height][original_width])
{
    // allocate ram for scaled image
    RGBTRIPLE **scaled_image = malloc(target_height * sizeof(RGBTRIPLE *));
    if (scaled_image == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < target_height; i++)
    {
        scaled_image[i] = malloc(target_width * sizeof(RGBTRIPLE));
        if (scaled_image[i] == NULL)
        {
            return NULL;
            for (size_t j = 0; j < i; j++)
            {
                free(scaled_image[j]);
            }
            free(scaled_image);
        }
    }

    //Nearst neighbor scaling algo
    for (size_t x = 0; x < target_height; x++) 
    {
        for (size_t y = 0; y < target_width; y++)
        {
            size_t src_y = y * original_height / target_height;
            size_t src_x = x * original_width / target_width;

            scaled_image[y][x] = image[src_y][src_x];
        }
    }

    return scaled_image;
}


void print_bmp_info(BMPFILEHEADER *file_header, BMPIMAGEHEADER *image_header)
{
    char *type_ptr = (char *)&(file_header->bfType);
    printf("Type : %c%c .\n", type_ptr[0], type_ptr[1]);
    printf("File Size : %d.\n", file_header->bfSize);
    printf("Reserved 1 : %d.\n", file_header->bfReserved1);
    printf("Reserved 2 : %d.\n", file_header->bfReserved2);
    printf("Offset to start of pixel data: %d.\n", file_header->bfOffBits);
    printf("Header Size : %d.\n", image_header->biSize);
    printf("Image Width : %d  || Image Height : %d  .\n", image_header->biWidth, image_header->biHeight);
    printf("Planes : %d.\n", image_header->biPlanes);
    printf("Bits Per Pixel : %d.\n", image_header->biBitCount);
    printf("Compression : %d.\n", image_header->biCompression);
    printf("Image Size : %d.\n", image_header->biSizeImage);
    printf("X Pixels Per Meter : %d.\n", image_header->biXPelsPerMeter);
    printf("Y Pixels Per Meter : %d.\n", image_header->biYPelsPerMeter);
    printf("Colors Used : %d.\n", image_header->biClrUsed);
    printf("Important Colors : %d.\n", image_header->biClrImportant);
    return;
}

char *bmp2ascii(char *fname, size_t target_height, size_t target_width)
{   
    FILE *bmp_file = fopen(fname, "rb");
    
    if (bmp_file == NULL)
    {
        printf("Error : Cant read file");
        return NULL;
    }

    BMPFILEHEADER file_header;
    BMPIMAGEHEADER image_header;
    
    //reads bmp file header 
    fread(&file_header, sizeof(file_header), 1, bmp_file);
    //reads bmp image header
    fread(&image_header, sizeof(image_header), 1, bmp_file);

    //DEBUG : print bmp file headers info
    //print_bmp_info(&file_header, &image_header);

    /*  cheak next BMP parametes:
        bftype == "BM"
        colorbit map == 24bit
        bfOffBits == 54 (offset to start of pixel data)
        biSize == 40 (header size)
        biCompression == 0 (not compressed)
    */
    if (file_header.bfType != 0x4d42 || file_header.bfOffBits != 54 || image_header.biSize != 40 || image_header.biBitCount != 24 || image_header.biCompression != 0)
    {
        printf("Error: unsupported \"bmp\" file.\n"); 
        return NULL;
    }
    
    //export height/width from BMP image header
    int height = (image_header.biHeight);
    int width = image_header.biWidth;

    //jump to pixel_data statrting position
    fseek(bmp_file, file_header.bfOffBits, SEEK_SET);

    //allocate ram for pixel data
    RGBTRIPLE(*tmp_image)[width] = malloc(abs(height) * sizeof(*tmp_image));
    if (tmp_image == NULL)
    {
        printf("Error : not enough memory to store image.");
        return NULL;
    }

    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;    

    //extract pixel data into tmp_image
    for (int i = 0; i < abs(height); i++)
    {
        fread(tmp_image[i], sizeof(RGBTRIPLE), width, bmp_file);
        fseek(bmp_file, padding, SEEK_CUR); 
    }

    //scale image to target width and height
    RGBTRIPLE **scaled_image = image_scaling(width, abs(height), target_width, target_height, tmp_image);
    
    if (scaled_image == NULL)
    {
        free(tmp_image);
        fclose(bmp_file);
        return NULL;
    }

    //allocate ram for the return 
    char *ascii_return = malloc(target_height * (target_width + 1) + 1);

    if (ascii_return == NULL) 
    {
        for (size_t i = 0; i < target_height; i++)
        {
            free(scaled_image[i]);
        }

        free(scaled_image);
        free(tmp_image);
        fclose(bmp_file);
        return NULL;
    }

    //transfrom pixel val into ascii char
    for (size_t i = 0; i < target_height; i++)
    {
        size_t src_row = (target_height - 1) - i;

        for (size_t j = 0; j < target_width; j++)
        {
            size_t index = j + (i * (target_width + 1));
            ascii_return[index] = pixel_to_ascii(&scaled_image[src_row][j]);
        }
        size_t new_line_index = target_width + (i * (target_width + 1));
        ascii_return[new_line_index] = '\n';
    }
    
    ascii_return[target_height * (target_width + 1)] = '\0';

    for (size_t i = 0; i < target_height; i++)
    {
        free(scaled_image[i]);
    }
    
    free(scaled_image);
    free(tmp_image);

    fclose(bmp_file);
    
    return  ascii_return;
}
 
