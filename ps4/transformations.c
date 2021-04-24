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

	//flipping is like double(twice) rotate
	for(long y = 0; y < image->header->height; y++){
		for(long x = 0; x < half_width; x++){
			new->data[y * new->header->width + x]
			    = image->data[y * image->header->width + image->header->width - x - 1];
			new->data[y * new->header->width + new->header->width - x - 1] 
			    = image->data[y * image->header->width + x];
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
	
	//flipping is like double(twice) rotate
	for(long y = 0; y < half_height; y++){
		for(long x = 0; x < image->header->width; x++){
			new->data[y * new->header->width + x]
			    = image->data[(image->header->height - y - 1) * image->header->width + x];
			new->data[(new->header->height - y - 1) * new->header->width + x] 
			    = image->data[y * image->header->width + x];
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
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++){
			new->data[image->header->height - x - 1 + y * image->header->height] 
			    = image->data[x * image->header->width + y];
		}
	}
	
	return new;		
}

struct bmp_image* rotate_right(const struct bmp_image* image){
	/*struct bmp_image* new = malloc(sizeof(struct bmp_image));
	new = rotate_left(image);
	for(int i = 0; i < 2; i++){
		new = rotate_left(new);
	}

	return new;*/
	if(image == NULL) return NULL;
	struct bmp_image* new = malloc(sizeof(struct bmp_image));
    new->header = malloc(sizeof(struct bmp_header));
	memcpy(new->header, image->header, sizeof(*new->header));

    
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
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++){
			new->data[x + y * image->header->height] 
			    = image->data[x * image->header->width + image->header->width - y - 1];
		}
	}
	
	return new;	
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
	if((image == NULL) || (start_x < 0 || start_x > image->header->width) || (start_y < 0 || start_y > image->header->height) || (width <= 0 || start_x + width > image->header->width) || (height <= 0 || height + start_y > image->header->height)) return NULL;
	
	/*int h_coord = image->header->height - start_y - height;
	int w_coord = start_x;
	int nwidth = width * 3;

	int orig_width = image->header->image_size / image->header->height;

	int new_padding = 0;
	while((width * 3 + new_padding) % 4 != 0){
		new_padding++;
	}
	int new_width = width * 3 + new_padding;

	struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
	
	new_image->header = image->header;
	new_image->header->size = new_width * height + BMP_HEADER_SIZE;
	new_image->header->width = width;
	new_image->header->height = height;
	new_image->header->image_size = new_image->header->size - BMP_HEADER_SIZE;

	h_coord = h_coord * orig_width;
	w_coord = w_coord * 3;

	int total_offset = h_coord + w_coord;
	//unsigned char* new_data = malloc(sizeof(*new_data) * new_image->header->image_size);

	int i = 0;
	int h_count = 0;
	int w_count = 0;
	//unsigned char* orig_data = image->data;
	//struct bmp_image* orig_data = malloc(sizeof(struct bmp_image));
	
	//struct bmp_image* orig_data = calloc(height*width, sizeof(struct pixel));
	//new_image->data = (struct pixel*)malloc(new_image->header->image_size*sizeof(struct pixel));
	struct pixel* new_data = malloc(new_image->header->image_size*sizeof(struct pixel));
	struct pixel* orig_data = malloc(new_image->header->image_size*sizeof(struct pixel));
	*orig_data = *image->data;

	for(h_count = 0; h_count < height; h_count++){
		for(w_count = 0; w_count < nwidth + new_padding; w_count++){
			if(w_count < nwidth){
				new_data[i].red = orig_data[total_offset + i].red;
				new_data[i].blue = orig_data[total_offset + i].blue;
				new_data[i].green = orig_data[total_offset + i].green;
			} else{
				new_data[i].red = 0;
				new_data[i].blue = 0;
				new_data[i].green = 0;
			}
			i++;
		}
		for(w_count = 0; w_count < orig_width - w_coord - nwidth - new_padding; w_count++){
			total_offset++;
		}
		total_offset += w_coord;
	}

	new_image->data = new_data;

	return new_image;*/
	return NULL;	
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
		}
	}
	struct bmp_image* new = malloc(sizeof(struct bmp_image));
	new->header = malloc(sizeof(struct bmp_header));
	*new->header = *image->header;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));

	//the idea of pixels https://stackoverflow.com/questions/56415441/flip-bmp-image-horizontal-in-c
	//the idea of changed BMP http://www.cpp.re/forum/beginner/265541/
	for(int y = 0; y < image->header->height; y++){
		for(int x = 0; x < image->header->width; x++){
			if(red == true) new->data[y*image->header->width+x].red = image->data[y*image->header->width+x].red;
			else new->data[y*image->header->width+x].red = 0;
			if(blue == true) new->data[y*image->header->width+x].blue = image->data[y*image->header->width+x].blue;
			else new->data[y*image->header->width+x].blue = 0;
			if(green == true) new->data[y*image->header->width+x].green = image->data[y*image->header->width+x].green;
			else new->data[y*image->header->width+x].green = 0;
			/*if(red == true) new->data[y*100+x].red = image->data[y*100+x].red;
			else new->data[y*100+x].red = 0;
			if(blue == true) new->data[y*100+x].blue = image->data[y*100+x].blue;
			else new->data[y*100+x].blue = 0;
			if(green == true) new->data[y+x].green = image->data[y+x].green;
			else new->data[y*100+x].green = 0;*/
		}
	}

	return new;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
	if((image == NULL) || (factor <= 0)) return NULL;

	return NULL;
}
