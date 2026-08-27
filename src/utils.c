#include "utils.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

char pixel_to_ascii(RGBTRIPLE *pixel)
{
    char *chars = " .:-=+#%@";
    char chars_num = strlen(chars);
    int pixel_brightness = round((pixel->red + pixel->green + pixel->blue) / 3.0);
    int index = pixel_brightness * (chars_num -1) / 255;
    return chars[index];
}
