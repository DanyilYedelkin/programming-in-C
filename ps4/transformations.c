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
	memcpy(new->header, image->header, sizeof(*new->header));

    //the idea of pixels https://stackoverflow.com/questions/56415441/flip-bmp-image-horizontal-in-c
	//the idea of rotating http://www.cpp.re/forum/beginner/265541/
	new->header->width = image->header->height;
	new->header->height = image->header->width;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++){
			new->data[y * image->header->height + image->header->height - x - 1].red 
			    = image->data[x * image->header->width + y].red;
			new->data[y * image->header->height + image->header->height - x - 1].blue
			    = image->data[x * image->header->width + y].blue;
			new->data[ y * image->header->height + image->header->height - x - 1].green
			    = image->data[x * image->header->width + y].green;
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

    //the idea of pixels https://stackoverflow.com/questions/56415441/flip-bmp-image-horizontal-in-c
	//the idea of rotating http://www.cpp.re/forum/beginner/265541/
	new->header->width = image->header->height;
	new->header->height = image->header->width;
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));
	for (int y = 0; y < image->header->width; y++){
		for(int x = 0; x < image->header->height; x++){
			new->data[y * image->header->height + x].red 
			    = image->data[x * image->header->width + image->header->width - y - 1].red; 
			new->data[y * image->header->height + x].blue 
			    = image->data[x * image->header->width + image->header->width - y - 1].blue;
			new->data[y * image->header->height + x].green 
			    = image->data[x * image->header->width + image->header->width - y - 1].green;
		}
	}
	
	return new;	
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
	if((image == NULL) || (start_x < 0 || start_x > image->header->width) || (start_y < 0 || start_y > image->header->height) || (width <= 0 || start_x + width > image->header->width) || (height <= 0 || height + start_y > image->header->height) || (image->data == NULL) || (image->header == NULL)) return NULL;
	
	struct bmp_image* new = malloc(sizeof(struct bmp_image));
	memcpy(new->header, image->header, sizeof(*new->header));
	new->header->height = height;
	new->header->width = width;
	new->data = (struct pixel*)calloc(height*width, sizeof(struct pixel));

	//the idea of pixels https://stackoverflow.com/questions/56415441/flip-bmp-image-horizontal-in-c
	//the idea of changed BMP http://www.cpp.re/forum/beginner/265541/
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			new->data[x+(width*(height-y-1))].red 
			    = image->data[x+start_y+(start_x + y*image->header->width)].red;
			new->data[x+(width*(height-y-1))].blue 
			    = image->data[x+start_y+(start_x + y*image->header->width)].blue;
			new->data[x+(width*(height-y-1))].green 
			    = image->data[x+start_y+(start_x + y*image->header->width)].green;
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
		}
	}
	struct bmp_image* new = malloc(sizeof(struct bmp_image));
	memcpy(new->header, image->header, sizeof(*new->header));
	new->data = (struct pixel*)calloc(image->header->width*image->header->height, sizeof(struct pixel));

	//the idea of pixels https://stackoverflow.com/questions/56415441/flip-bmp-image-horizontal-in-c
	//the idea of changed BMP http://www.cpp.re/forum/beginner/265541/
	for(int y = 0; y < image->header->height; y++){
		for(int x = 0; x < image->header->width; x++){
			if(red == true) new->data[y+x*image->header->height].red = image->data[y+x*image->header->height].red;
			else new->data[y+x*image->header->height].red = 0;
			if(blue == true) new->data[y+x*image->header->height].blue = image->data[y+x*image->header->height].blue;
			else new->data[y+x*image->header->height].blue = 0;
			if(green == true) new->data[y+x*image->header->height].green = image->data[y+x*image->header->height].green;
			else new->data[y+x*image->header->height].green = 0;
		}
	}

	return new;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
	//if((image == NULL) || (factor <= 0)) return NULL;

	return NULL;
}
