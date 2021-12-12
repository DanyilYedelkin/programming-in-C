#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"


struct bmp_header* read_bmp_header(FILE* stream){
    if(stream == NULL) return NULL;
    fseek(stream, 0, 2);
    int length_file = ftell(stream);
    if(length_file == -1L) return NULL;

    fseek(stream, 0, 0);
    char *string_of_steam = calloc(length_file, sizeof(char));
    fread(string_of_steam, length_file, 1, stream);
    char *long_of_string = calloc(strlen(string_of_steam), sizeof(char));

    for(int i = 0, number = 0; i < length_file; i++){
        if(string_of_steam[i] != '\0'){
            number++;
            long_of_string[number] = string_of_steam[i];
        }
        if(string_of_steam[i+1] == 77 && string_of_steam[i] == 66){
            fseek(stream, i, 0);
            break;
        } else if(string_of_steam[i+1] == '\0'){
            free(string_of_steam);
            free(long_of_string);
            return NULL;
        }
    }
    free(long_of_string);
    free(string_of_steam);

    struct bmp_header* header = malloc(sizeof(struct bmp_header));
    fread(header, sizeof(struct bmp_header), 1, stream);
    if((header->bpp != 24) || (header->dib_size != 40) || (header->offset != 54) || (header->type != 0x4D42) || (header->width <= 0) || (header->height <= 0)){
        free(header);
        return NULL;
    }

    return header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){
    if((stream == NULL) || (header == NULL)) return NULL;

    //creating new variables for simple codding 
    uint32_t size = header->height * header->width;
    uint32_t width = header->width;
    uint32_t height = header->height;
    struct pixel* data = calloc(size, sizeof(struct pixel));
    fseek(stream, header->offset, 0);

    //function for reading data memory
    for(uint32_t i = 0; i < height; i++){
        for(uint32_t j = 0; j < width; j++){
            fread(&data[i * width + j], sizeof(struct pixel), 1, stream);
        }
        if((width % 4) != 0) fseek(stream, width, 1);
    }

    return data;
}

struct bmp_image* read_bmp(FILE* stream){
    if(stream == NULL) return NULL;

    //creating and checking a header bmp (for elements)
    struct bmp_header* header = read_bmp_header(stream);
    if(header == NULL){
        fprintf(stderr, "Error: This is not a BMP file.\n");
        free(header);
        return NULL;
    }

    //creating and checking a data bmp (for elements)
    struct pixel* data = read_data(stream, header);
    if(data == NULL){
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        free(header);
        free(data);
        return NULL;
    }

    //creating a new bmp image, and fill it with data & header
    struct bmp_image* image = malloc(sizeof(struct bmp_image));
    if(header != NULL && data != NULL){
        image->data = data;
        image->header = header;
    }

    return image;
}

bool write_bmp(FILE* stream, const struct bmp_image* image){
    if((stream == NULL) || (image == NULL) || (image->data == NULL) || (image->header == NULL)) return false;

    //creating new variables for simple codding 
    uint32_t height = image->header->height;
    uint32_t width = image->header->width;

    //function for writing data
    fwrite(image->header, sizeof(struct bmp_header), 1, stream);
    for(uint32_t i = 0; i < height; i++){
        for(uint32_t j = 0; j < width; j++){
            fwrite(&image->data[(i * width) + j], sizeof(struct pixel), 1, stream);
        }
        fwrite(&PADDING_CHAR, sizeof(unsigned char), ((width) % 4), stream);
    }

    return true;
}

void free_bmp_image(struct bmp_image* image){
    if(image != NULL){
        free(image->header);
        free(image->data);
        free(image);
    }
}
