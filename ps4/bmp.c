#include <stdio.h>
#include <stdlib.h>
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



struct bmp_header* read_bmp_header(FILE* stream){
    //https://web.cs.ucdavis.edu/~amenta/s12/readBMP.cpp
    //https://elcharolin.wordpress.com/2018/11/28/read-and-write-bmp-files-in-c-c/
    if(stream == NULL) return NULL;
    //http://www.c-cpp.ru/content/ftell
    int length_file = ftell(stream);
    if(length_file == -1L) return NULL;

    char *string_of_steam = calloc(length_file, sizeof(char));
    fread(string_of_steam, length_file, 1, stream);
    char *long_of_string = calloc(strlen(string_of_steam), sizeof(char));

    for(int i = 0, number = 0; i < length_file; i++){
        if(string_of_steam[i] != '\0'){
            number++;
            long_of_string[number] = string_of_steam[i];
        }
        if(string_of_steam[i+1] == 77 && string_of_steam[i] == 66){
            fseek(stream, i, SEEK_SET);
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

    int size = header->height * header->width;
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
        fprintf(stderr, "Error: This is not a BMP file.\n");
        free(header);
        return NULL;
    }

    struct pixel* data = read_data(stream, header);
    if(data == NULL){
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        free(header);
        free(data);
        return NULL;
    }
    
    struct bmp_image* image = malloc(sizeof(struct bmp_image));
    if(header != NULL && data != NULL){
        image->data = data;
        image->header = header;
    } else{
        free_bmp_image(image);
        return NULL;
    }

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

