#include "img_to_ascii.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

char pixel_to_ascii(RGBTRIPLE *pixel)
{
    char *chars = " .:-=+#%@";
    char chars_num = strlen(chars);
    int pixel_brightness = round((pixel->blue + pixel->red + pixel->green) / 3);
    int index = pixel_brightness * (chars_num -1) / 255;
    return chars[index];
}

void print_ascci_art(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%c",pixel_to_ascii(&image[i][j]));
        }
        printf("\n");
    }
    printf("\n");
    return;
}