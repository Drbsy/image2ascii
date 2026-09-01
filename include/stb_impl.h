#ifndef STB_IMPL_H
#define STB_IMPL_H

#include "stb_image_resize2.h"

unsigned char *load_image(const char *filename, int *width, int *height, int *num_channel);
unsigned char *resize_image(
    const unsigned char *input_pixels, const int input_w, const int input_h, const int input_stride_in_bytes,
    const int output_w, const int output_h, const int output_stride_in_bytes,
    int channels, stbir_pixel_layout pixel_layout
);
void image_free(void *image);

#endif
