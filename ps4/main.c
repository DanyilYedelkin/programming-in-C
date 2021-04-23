#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"
#include <string.h>

int main(){
    FILE* input = fopen("assets/lenna.bmp", "rb");
    struct bmp_image* image_bmp = read_bmp(input);
    fclose(input);
    image_bmp = flip_vertically(image_bmp);
    FILE* output = fopen("assets/new.bmp", "wb");
    write_bmp(output, image_bmp);
    fclose(output);
    flip_horizontally(NULL);
    rotate_left(NULL);
    rotate_right(NULL);
    scale(NULL, 0);
    crop(NULL, 0, 0, 0, 0);
    extract(NULL, NULL);
    free_bmp_image(image_bmp);
    return 0;
}