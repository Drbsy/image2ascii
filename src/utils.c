#include "utils.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int get_pixel_brightness(int red, int green, int blue);
char pixel_to_ascii(int red, int green, int blue);
int saliency_dedector(unsigned char *saliency_image , const unsigned char *gray_image,const int width,const int height, int threshold);
unsigned char *image_2_gray(const unsigned char *image,const int width,const int height,const int num_channel);

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
    //return (int)floor((red + green + blue) / 3.0);
    return (int)floor(0.299 * red + 0.587 * green + 0.114 * blue);
}

char *image_2_ascii(const unsigned char *image,const int width,const int height,const int num_channel, int saliency_threshold)
{
    if (image == NULL || width <= 0 || height <= 0 || num_channel <= 0)
    {
        return NULL;
    }

    size_t ascii_return_size = (size_t)(width + 1) * height + 1;
    char *ascii_return = malloc(ascii_return_size);
    unsigned char *gray_image = image_2_gray(image, width, height, num_channel);
    unsigned char *saliency_image = malloc((size_t)width * height);
    if (ascii_return == NULL || gray_image == NULL || saliency_image == NULL)
    {
        free(ascii_return);
        free(gray_image);
        free(saliency_image);
        return NULL;
    }

    if (saliency_threshold >= 0)
    {
        if (saliency_dedector(saliency_image, gray_image, width, height, saliency_threshold) != 0)
        {
            free(ascii_return);
            free(gray_image);
            free(saliency_image);
            return NULL;
        }
    }
    else
    {
        memcpy(saliency_image, gray_image, (size_t)width * height);
    }

    size_t j = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char saliency = saliency_image[(size_t)y * width + x];
            ascii_return[j++] = pixel_to_ascii(saliency, saliency, saliency);
        }
        ascii_return[j++] = '\n';
    }
    ascii_return[j] = '\0';

    free(gray_image);
    free(saliency_image);
    return ascii_return;
}

float get_llen_scale(size_t width, size_t llen)
{
    if (llen == 0)
    {
        return 0;
    }
    float scale = (float)(width)/(float)(llen);
    return scale;
}

int saliency_dedector(unsigned char *saliency_image , const unsigned char *gray_image,const int width,const int height, int threshold)
{
    if (!saliency_image || !gray_image || width <= 0 || height <= 0)
    {
        return -1;
    }

    size_t total_pixels = height * width;

    int hist[256] = {0};
    int sal_table[256] = {0};

    for (size_t i = 0; i < total_pixels; i++)
    {
        hist[gray_image[i]]++;
    }
    
    int max_score = 0;
    for (int i = 0; i < 256; i++)
    {
        long long score = 0;
        for (int j = 0; j < 256; j++)
        {
            score += hist[j] * abs(i - j);
        }
        sal_table[i] = (int)(score / total_pixels);
        if (sal_table[i] > max_score)
        {
            max_score = sal_table[i];
        }
    }

    for (size_t i = 0; i <total_pixels; i++)
    {
        unsigned char gray_val = gray_image[i];

        if (max_score > 0)
        {
            int val = (sal_table[gray_val] * 255) / max_score;

            if (val < threshold) 
            {
                saliency_image[i] = 0;
            } 
            else 
            {
                saliency_image[i] = (unsigned char)val;
            }
        }
        else
        {
            saliency_image[i] = 0;
        }
    }

    return 0; 
}

unsigned char *image_2_gray(const unsigned char *image,const int width,const int height,const int num_channel)
{
    if (!image || width <= 0 || height <= 0 || num_channel <= 0)
    {
        return NULL;
    }

    size_t total_pixels = height * width;

    unsigned char *gray_image = (unsigned char *)malloc(total_pixels);
    if (!gray_image)
    {
        return NULL;
    }

    for (size_t i = 0; i < total_pixels; i++)
    {
        size_t index = i * num_channel;
        int red   = image[index + 0];
        int green = (num_channel >= 2) ? image[index + 1] : red;
        int blue  = (num_channel >= 3) ? image[index + 2] : red;

        gray_image[i] = get_pixel_brightness(red , green, blue);
    }

    return gray_image;
}