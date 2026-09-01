#include "utils.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int get_pixel_brightness(int red, int green, int blue);
char pixel_to_ascii(int red, int green, int blue);

char pixel_to_ascii(int red, int green, int blue)
{
    const char *chars = " .:-=+#%@";
    char chars_num = strlen(chars);
    int pixel_brightness = get_pixel_brightness(red, green, blue);
    int index = pixel_brightness * (chars_num -1) / 255;
    return chars[index];
}

int get_pixel_brightness(int red, int green, int blue)
{
    return (int)floor((red + green + blue) / 3.0);
}

char *image_2_ascii(const unsigned char *image,const int width,const int height,const int num_channel)
{
    if (image == NULL)
    {
        return NULL;
    }

    size_t ascii_return_size = (size_t)(width + 1) * height + 1;
    char *ascii_return = malloc(ascii_return_size);
    if (ascii_return == NULL)
    {
        return NULL;
    }
    size_t j = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            size_t i = (size_t)(y * width + x) * num_channel;
            int red   = image[i + 0];
            int green = (num_channel >= 2) ? image[i + 1] : red;
            int blue  = (num_channel >= 3) ? image[i + 2] : red;
            ascii_return[j++] = pixel_to_ascii(red, green, blue);
        }
        ascii_return[j++] = '\n';
    }
    ascii_return[j] = '\0';

    return ascii_return;
}

