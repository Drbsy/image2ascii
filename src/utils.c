#include "utils.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

char pixel_to_ascii(RGBTRIPLE *pixel)
{
    char *chars = " .:-=+#%@";
    char chars_num = strlen(chars);
    int pixel_brightness = get_pixel_brightness(pixel);
    int index = pixel_brightness * (chars_num -1) / 255;
    return chars[index];
}


int get_pixel_brightness(RGBTRIPLE *pixel)
{
    return round((pixel->red + pixel->green + pixel->blue) / 3.0);
}
