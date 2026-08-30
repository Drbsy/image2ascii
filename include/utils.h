#ifndef UTILS_H
#define UTILS_H

#include "bmp.h"

char pixel_to_ascii(RGBTRIPLE *pixel);
int get_pixel_brightness(RGBTRIPLE *pixel);

#endif
