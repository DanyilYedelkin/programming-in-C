#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bmp.h"

/*
         _nnnn_                      
        dGGGGMMb     ,"""""""""""""".
       @p~qp~~qMb    | Linux Rules! |
       M|@||@) M|   _;..............'
       @,----.JM| -'
      JS^\__/  qKL
     dZP        qKRb
    dZP          qKKb
   fZP            SMMb
   HZM            MMMM
   FqM            MMMM
 __| ".        |\dS"qML
 |    `.       | `' \Zq
_)      \.___.,|     .'
\____   )MMMMMM|   .'
     `-'       `--' hjm
*/



struct bmp_image* flip_horizontally(const struct bmp_image* image){
	if((image == NULL) || (image->data == NULL)) return NULL;

	struct bmp_image* new = malloc(sizeof(struct bmp_image));
    new->header = malloc(sizeof(struct bmp_header));
	memcpy(new->header, image->header, sizeof(*new->header));

	uint32_t size = image->header->width * image->header->height;
	new->data = (struct pixel*)calloc(size, sizeof(struct pixel));
	uint32_t half_width = new->header->width / 2;
	uint32_t old_width = image->header->width;
	uint32_t new_width = new->header->width;
	uint32_t old_height = image->header->height;

	//flipping is like double(twice) rotate, but firstly we must find a half of BMP image
	int i = 0;
	for(long y = 0; y < old_height; y++){
		for(long x = 0; x < half_width; x++, i++){
			new->data[x + y * new_width] = image->data[old_width - x - 1 + y * old_width];
			new->data[new_width - x - 1 + y * new_width] = image->data[x + y * old_width];
		}
		if((new_width % 2) == 1){
			new->data[half_width + y * new_width] = image->data[half_width + y * old_width];
		}
	}

	return new;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
	if((image == NULL) || (image->data == NULL)) return NULL;

	struct bmp_image* new = malloc(sizeof(struct bmp_image));
    new->header = malloc(sizeof(struct bmp_header));
	memcpy(new->header, image->header, sizeof(*new->header));

	uint32_t size = image->header->width * image->header->height;
	new->data = (struct pixel*)calloc(size, sizeof(struct pixel));
	uint32_t half_height = new->header->height / 2;
	uint32_t old_width = image->header->width;
	uint32_t old_height = image->header->height;
	uint32_t new_width = new->header->width;
	uint32_t new_height = new->header->height;
	
	//flipping is like double(twice) rotate, but firstly we must find a half of BMP image
	int i = 0;
	for(uint32_t y = 0; y < half_height; y++){
		for(uint32_t x = 0; x < old_width; x++, i++){
			new->data[i] = image->data[x + old_width * (old_height - y - 1)];
			new->data[x + new_width * (new_height - y - 1)] = image->data[i];
		}
	}
	if((new_height % 2) == 1){
		for(uint32_t x = 0; x < new_width; x++){
			new->data[x + new_width * half_height] = image->data[x + old_width * half_height];
		}
	}

	return new;
}

struct bmp_image* rotate_left(const struct bmp_image* image){
	if(image == NULL) return NULL;

	struct bmp_image* new = malloc(sizeof(struct bmp_image));
    new->header = malloc(sizeof(struct bmp_header));
	memcpy(new->header, image->header, sizeof(*image->header));

    
	//the idea of rotating http://www.cpp.re/forum/beginner/265541/
	new->header->width = image->header->height;
	new->header->height = image->header->width;
	int padding = 4 - ((new->header->bpp / 8) * image->header->height) % 4;
	if(((new->header->bpp / 8) * image->header->height) % 4 == 0){
		padding = 0;
	} else{
		padding = 4 - ((new->header->bpp / 8) * image->header->height) % 4;
	}
	int new_image_size = (image->header->height * (new->header->bpp / 8) + padding) * image->header->width;
	new->header->image_size = new_image_size;
	new->header->size = new_image_size + new->header->offset;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));
	//and the another idea of rotating https://cboard.cprogramming.com/c-programming/175363-rotating-bmp-image-multiple-90-c.html
	int i = 0;
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++, i++){
			new->data[image->header->height - x - 1 + y * image->header->height] = image->data[x * image->header->width + y];
		}
	}
	
	return new;		
}

struct bmp_image* rotate_right(const struct bmp_image* image){
	/*if(image == NULL) return NULL;

	struct bmp_image* new = malloc(sizeof(struct bmp_image));
	new = rotate_left(image);
	for(int i = 0; i < 2; i++){
		new = rotate_left(new);
	}

	return new;*/
	if(image == NULL) return NULL;
	struct bmp_image* new = malloc(sizeof(struct bmp_image));
    new->header = malloc(sizeof(struct bmp_header));
	memcpy(new->header, image->header, sizeof(*new->header));

	new->header->width = image->header->height;
	new->header->height = image->header->width;
	int padding = 4 - ((new->header->bpp / 8) * image->header->height) % 4;
	if(((new->header->bpp / 8) * image->header->height) % 4 == 0){
		padding = 0;
	} else{
		padding = 4 - ((new->header->bpp / 8) * image->header->height) % 4;
	}
	int new_image_size = (image->header->height * (new->header->bpp / 8) + padding) * image->header->width;
	new->header->image_size = new_image_size;
	new->header->size = new_image_size + new->header->offset;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));
	//the idea of rotating http://www.cpp.re/forum/beginner/265541/
	//and the another idea of rotating https://cboard.cprogramming.com/c-programming/175363-rotating-bmp-image-multiple-90-c.html
	int i = 0;
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++, i++){
			new->data[i] = image->data[x * image->header->width + image->header->width - y - 1];
		}
	}
	
	return new;	
}



struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
	if((image == NULL) || (colors_to_keep == NULL) || (image->data == NULL) || (image->header == NULL)) return NULL;
	bool red = false, blue = false, green = false;

	for(int i = 0; i < strlen(colors_to_keep); i++){
		if(colors_to_keep[i] == 'r'){
			red = true;
		} else if(colors_to_keep[i] == 'b'){
			blue = true;
		} else if(colors_to_keep[i] == 'g'){
			green = true;
		} else return NULL;
	}
	struct bmp_image* new = malloc(sizeof(struct bmp_image));
	new->header = malloc(sizeof(struct bmp_header));
	*new->header = *image->header;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));

	int i = 0;
	for(int y = 0; y < image->header->height; y++){
		for(int x = 0; x < image->header->width; x++, i++){
			if(red == true) new->data[i].red = image->data[i].red;
			else new->data[i].red = 0;
			if(blue == true) new->data[i].blue = image->data[i].blue;
			else new->data[i].blue = 0;
			if(green == true) new->data[i].green = image->data[i].green;
			else new->data[i].green = 0;
		}
	}

	return new;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
	if((image == NULL) || (factor <= 0)) return NULL;

	struct bmp_image * new = malloc(sizeof(struct bmp_image));
	new->header = malloc(sizeof(struct bmp_header));
	*new->header = *image->header;
	uint32_t new_height = round((float)image->header->height * factor);
	uint32_t new_width = round((float)image->header->width * factor);
	new->header->width = (uint32_t)new_width;
	new->header->height = (uint32_t)new_height;

	uint32_t padding = 0;
	if(((image->header->bpp / 8) * new_width) % 4 == 0){
		padding = 0;
	} else{
		padding = 4 - (((image->header->bpp / 8) * new_width) % 4);
	}

	new->header->size = ((padding + (uint32_t)new_width * (image->header->bpp / 8)) * (uint32_t)new_height) + image->header->offset;
	new->header->image_size = ((padding + (uint32_t)new_width * (image->header->bpp / 8)) * (uint32_t)new_height);
	new->data = (struct pixel*)calloc((uint32_t)(new_height * new_width), sizeof(struct pixel));

	//int one = 0;
	//int two = 0;
	int i = 0;
	
	for(int y = 0; y < new_height; y++){
		for(int x = 0; x < new_width; x++, i++){
			//add (int), because have an error: array subscript is not an integer
			//new->data[i] = image->data[(int)(floor(x/factor) + floor(y/factor) * image->header->width)];
            new->data[i] = image->data[(((int)(y * image->header->height) / new->header->height) * image->header->width) + ((int)(x * image->header->width) / new->header->width)];
		}
	}



	return new;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
	if((image == NULL) || (start_x < 0 || start_x > image->header->width) || (start_y < 0 || start_y > image->header->height) || (width <= 0 || start_x + width > image->header->width) || (height <= 0 || height + start_y > image->header->height)) return NULL;

	struct bmp_image* new_bmp =  malloc(sizeof(struct bmp_image));
	new_bmp->header = malloc(sizeof(struct bmp_header));
	*new_bmp->header = *image->header;
	int old_width = image->header->width;

	new_bmp->data = calloc(new_bmp->header->width * new_bmp->header->height, sizeof(struct pixel));
	struct pixel* datas = calloc(new_bmp->header->width * new_bmp->header->height, sizeof(struct pixel));
	for(int y = 0; y < image->header->height; y++){
        for(int x = 0, i = 0; x < image->header->width; x++, i++){
            new_bmp->data[x + y * image->header->width] = image->data[x + (image->header->height - 1 - y) * image->header->width];
			datas[x + y * image->header->width ] = image->data[x + (image->header->height - 1 - y) * image->header->width];
        }
    }
	
    new_bmp->header->width = (uint32_t)width;
    new_bmp->header->height = (uint32_t)height;
    int i = 0;
    for(int y = start_y; y < start_y + height; y++){
        for(int x = start_x; x < start_x + width; x++, i++){
            new_bmp->data[i] = new_bmp->data[x + (y * old_width)];
			datas[i] = datas[x + (y * old_width)];
        }
    }
	i = 0;
	
	for(int y = 0; y < height; y++){
	    for(int x = 0; x < width; x ++, i++){
			new_bmp->data[x + width * (height - y - 1)] = datas[i];
		}
	}
	uint32_t padding = 4 - (((image->header->bpp / 8) * width) % 4);
	new_bmp->header->image_size = (uint32_t)height * ((uint32_t)width * sizeof(struct pixel) + padding);
	new_bmp->header->size = new_bmp->header->offset + new_bmp->header->image_size;

	free(datas);

    return new_bmp;
}
