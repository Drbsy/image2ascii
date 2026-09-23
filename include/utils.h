#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

char *image_2_ascii(const unsigned char *image,const int width,const int height,const int num_channel, int use_saliency);
float get_llen_scale(size_t width, size_t llen);

#endif
