#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

struct bmp_header* read_bmp_header(FILE* stream){
    if(stream == NULL) return NULL;
    fseek(stream, 0, SEEK_END);
    //http://www.c-cpp.ru/content/ftell
    long length_file = ftell(stream);
    if(length_file == -1L) return NULL;

    fseek(stream, 0, SEEK_SET);
    char *string_of_steam = calloc(length_file, sizeof(char));
    fread(string_of_steam, length_file, 1, stream);

    for(int i = 0; i < length_file; i++){
        if(string_of_steam[i+1] == 77 && string_of_steam[i] == 66){
            fseek(stream, i, SEEK_SET);
            break;
        } else if(string_of_steam[i+1] == '\0'){
            free(string_of_steam);
            return NULL;
        }
    }
    free(string_of_steam);

    struct bmp_header* header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    fread(header, sizeof(struct bmp_header), 1, stream);
    if(header->bpp != 24){
        free(header);
        return NULL;
    }
    if(header->compression != 0){
        free(header);
        return NULL;
    }
    if(header->dib_size != 40){
        free(header);
        return NULL;
    }
    if(header->offset != 54){
        free(header);
        return NULL;
    }
    if(header->type != 0x4D42){
        free(header);
        return NULL;
    }
    if(header->width <= 0){
        free(header);
        return NULL;
    }
    if(header->height <= 0){
        free(header);
        return NULL;
    }

    return header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){
    if((stream == NULL) || (header == NULL)) return NULL;

    long size = header->height * header->width;
    struct pixel* data = calloc(size, sizeof(struct pixel));
    fseek(stream, header->offset, SEEK_SET);

    for(int i = 0; i < header->height; i++){
        for(int j = 0; j < header->width; j++){
            fread(&data[i * header->width + j], sizeof(struct pixel), 1, stream);
        }
        if((header->width % 4) != 0) fseek(stream, header->width, SEEK_CUR);
    }

    return data;
}

struct bmp_image* read_bmp(FILE* stream){
    if(stream == NULL) return NULL;

    struct bmp_header* header = read_bmp_header(stream);
    if(header == NULL){
        fprintf(stdout, "Error: This is not a BMP file.\n");
        free(header);
        return NULL;
    }

    struct pixel* data = read_data(stream, header);
    if(data == NULL){
        fprintf(stdout, "Error: Corrupted BMP file.\n");
        free(header);
        free(data);
        return NULL;
    }
    
    struct bmp_image* image = malloc(sizeof(struct bmp_image));
    image->data = data;
    image->header = header;

    return image;
}

bool write_bmp(FILE* stream, const struct bmp_image* image){
    if((stream == NULL) || (stream == NULL)) return false;

    fwrite(image->header, sizeof(struct bmp_header), 1, stream);
    for(int i = 0; i < image->header->height; i++){
        for(int j = 0; j < image->header->width; j++){
            fwrite(&image->data[(i*image->header->width) + j], sizeof(struct pixel), 1, stream);
        }
        fwrite(&PADDING_CHAR, sizeof(unsigned char), (image->header->width)%4, stream);
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
