#include "bmp.h"
#include <stdio.h>
#include <math.h>

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

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = round((image[i][j].red + image[i][j].green + image[i][j].blue) / 3.0);
            image[i][j].blue = gray;
            image[i][j].green = gray;
            image[i][j].red = gray;
        }
    }
    return;
}