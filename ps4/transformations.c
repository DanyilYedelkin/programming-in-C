#include <stdlib.h>
#include <stdio.h>
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
	if(image == NULL) return NULL;

	struct bmp_image* new = malloc(sizeof(struct bmp_image));
    new->header = malloc(sizeof(struct bmp_header));
	memcpy(new->header, image->header, sizeof(*new->header));

	long size = image->header->width * image->header->height;
	new->data = (struct pixel*)calloc(size, sizeof(struct pixel));
	int half_width = new->header->width / 2;

	//flipping is like double(twice) rotate, but firstly we must find a half of BMP image
	int i = 0;
	for(long y = 0; y < image->header->height; y++){
		for(long x = 0; x < half_width; x++, i++){
			new->data[y * new->header->width + x] = image->data[y * image->header->width + image->header->width - x - 1];
			new->data[y * new->header->width + new->header->width - x - 1] = image->data[y * image->header->width + x];
		}
		if(new->header->width % 2 == 1){
			new->data[y * new->header->width + half_width] = image->data[y * image->header->width + half_width];
		}
	}

	return new;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
	if(image == NULL) return NULL;

	struct bmp_image* new = malloc(sizeof(struct bmp_image));
    new->header = malloc(sizeof(struct bmp_header));
	memcpy(new->header, image->header, sizeof(*new->header));

	long size = image->header->width * image->header->height;
	new->data = (struct pixel*)calloc(size, sizeof(struct pixel));
	int half_height = new->header->height / 2;
	
	//flipping is like double(twice) rotate, but firstly we must find a half of BMP image
	int i = 0;
	for(long y = 0; y < half_height; y++){
		for(long x = 0; x < image->header->width; x++, i++){
			new->data[i] = image->data[(image->header->height - y - 1) * image->header->width + x];
			new->data[(new->header->height - y - 1) * new->header->width + x] = image->data[i];
		}
	}
	if(new->header->height % 2 == 1){
		for(int x = 0; x < new->header->width; x++){
			new->data[half_height * new->header->width + x] = image->data[half_height * image->header->width + x];
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
	int new_bpp = new->header->bpp / 8;
	int value = 0;
	if((new_bpp * image->header->height) % 4 == 0){
		value = 0;
	} else{
		value = 4 - (new_bpp * image->header->height) % 4;
	}
	int new_image_size = (image->header->height * new_bpp + value) * image->header->width;
	new->header->image_size = new_image_size;
	new->header->size = new_image_size + new->header->offset;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));
	//and the another idea of rotating https://cboard.cprogramming.com/c-programming/175363-rotating-bmp-image-multiple-90-c.html
	int i = 0;
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++, i++){
			new->data[image->header->height - x - 1 + y * image->header->height] 
			    = image->data[x * image->header->width + y];
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
	int new_bpp = new->header->bpp / 8;
	int value = 0;
	if((new_bpp * image->header->height) % 4 == 0){
		value = 0;
	} else{
		value = 4 - (new_bpp * image->header->height) % 4;
	}
	int new_image_size = (image->header->height * new_bpp + value) * image->header->width;
	new->header->image_size = new_image_size;
	new->header->size = new_image_size + new->header->offset;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));
	//the idea of rotating http://www.cpp.re/forum/beginner/265541/
	int i = 0;
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++, i++){
			new->data[i] = image->data[x * image->header->width + image->header->width - y - 1];
		}
	}
	
	return new;	
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
	if((image == NULL) || (start_x < 0 || start_x > image->header->width) || (start_y < 0 || start_y > image->header->height) || (width <= 0 || start_x + width > image->header->width) || (height <= 0 || height + start_y > image->header->height)) return NULL;
	
    struct bmp_image * new = malloc(sizeof(struct bmp_image));
	new->header = malloc(sizeof(struct bmp_header));
	*new->header = *image->header;
	new->header->width = width;
	new->header->height = height;
	int new_bpp = image->header->bpp / 8;
	int padding = 0;
	if(((new_bpp * width) % 4) == 0){
		padding = 0;
	} else{
		padding = 4 - ((new_bpp * width) % 4);
	}
	new->header->image_size = height * (width * new_bpp + padding);
	new->header->size = new->header->offset + new->header->image_size;
	new->data = (struct pixel*)calloc(height * width, sizeof(struct pixel));
	struct pixel* datas = calloc(height * width, sizeof(struct pixel));

	int i = 0;
	//the cropped BMP image
	//the idea of rotating http://www.cpp.re/forum/beginner/265541/
	//and the another idea of rotating https://cboard.cprogramming.com/c-programming/175363-rotating-bmp-image-multiple-90-c.html
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x ++, i++) {
			datas[i] = image->data[x + start_x + (y * image->header->width + start_y)];
		}
	}
	i = 0;
	//inverted the cropped BMP image
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x ++, i++) {
			new->data[x + width * (height - y - 1)] = datas[i];
		}
	}
	free(datas);

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

	return NULL;
}
