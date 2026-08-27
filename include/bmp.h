#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)

typedef struct  
{
    uint16_t  bfType;
    int32_t bfSize;
    int16_t bfReserved1;
    int16_t bfReserved2;
    int32_t bfOffBits;
} BMPFILEHEADER;

typedef struct  
{
    int32_t biSize;
    int32_t biWidth;       
    int32_t biHeight;
    int16_t biPlanes;
    int16_t biBitCount;
    int32_t biCompression;
    int32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    int32_t biClrUsed;
    int32_t biClrImportant;
} BMPIMAGEHEADER;

typedef struct 
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGBTRIPLE;

#pragma pack(pop)

void print_bmp_info(BMPFILEHEADER *file_header, BMPIMAGEHEADER *image_header);
char *bmp2ascii( char *fname);

#endif