#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"
#include <string.h>

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



int main(){
    FILE* stream = fopen("saboteur.bmp", "rb");
    struct bmp_image* image = read_bmp(stream);
    fclose(stream);
	char* rgb = "rb";
	struct bmp_image* image1 = flip_horizontally(image);
	struct bmp_image* image2 = flip_vertically(image);
	struct bmp_image* image3 = rotate_right(image);
	struct bmp_image* image4 = rotate_left(image);
	struct bmp_image* image5 = crop(image, 20, 10, 150, 150);
	struct bmp_image* image6 = scale(image, 0.66);
	struct bmp_image* image7 = extract(image, rgb);

	FILE *stream2 = fopen("output.bmp", "wb");
	write_bmp(stream2, image4);
	fclose(stream2);

	free_bmp_image(image);
	free_bmp_image(image1);
	free_bmp_image(image2);
	free_bmp_image(image3);
	free_bmp_image(image4);
	free_bmp_image(image5);
	free_bmp_image(image6);
    free_bmp_image(image7);

	return 0;
}
