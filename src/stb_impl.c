#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

unsigned char *load_image(const char *filename, int *width, int *height, int *num_channel)
{
    unsigned char *data = stbi_load(filename, width, height, num_channel, 0);
    
    if (data == NULL)
    {
        printf("Error : Faild to load the file.");
        return NULL;
    }

    return data;
}

unsigned char *resize_image(
    const unsigned char *input_pixels, const int input_w, const int input_h, const int input_stride_in_bytes,
    const int output_w, const int output_h, const int output_stride_in_bytes,
    int channels, stbir_pixel_layout pixel_layout
)
{
    if (input_pixels == NULL)
    {
        return NULL;
    }

    unsigned char *output_pixels = (unsigned char *)malloc(output_w * output_h * channels);
    if (output_pixels == NULL)
    {
        return NULL;
    }
    stbir_resize_uint8_srgb(input_pixels,  input_w,  input_h,  input_stride_in_bytes,
                            output_pixels, output_w, output_h, output_stride_in_bytes,
                            pixel_layout);

    return output_pixels;
}   

void image_free(void *image)
{
    stbi_image_free(image);
}