#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "playfair.h"

int main () {
    char *sssencrypted, *sssdecrypted;
    // even length of string
    sssencrypted = playfair_encrypt("SeCReT", "Hello world");
    printf("%s \n", sssencrypted);
    // "Hello world" --> "HELXLOVORLDX"
    // IS JZ JQ XN TK JC
    sssdecrypted = playfair_decrypt("SeCReT", sssencrypted);
    printf("%s \n" , sssdecrypted);
    // HELXLOVORLDX
    free(sssencrypted);
    free(sssdecrypted);

    //============================================

    char* ssreversed = reverse("Hello World!");
    printf("%s\n", ssreversed);
    // "!DLROW OLLEH"
    free(ssreversed);

    char* sencrypted;

    // basic test with long text
    sencrypted = vigenere_encrypt("ComPuTer", "Hello WoRlD!");
    printf("%s\n", sencrypted);
    // "JSXAI PSINR!"
    //HIOZ GR EJU RQPL USJU CR IBBW XAA
    free(sencrypted);

    printf("\n\n");

    char* sdecrypted;

    // basic test with long text
    sdecrypted = vigenere_decrypt("ComPuTer", "JSXAI PSINR!");
    printf("%s\n", sdecrypted);
    // "Hello world!"
    free(sdecrypted);

    //================================================

    unsigned char* encrypted;

   // basic test with long text
   encrypted = bit_encrypt("Hello world!");
   for(int i=0; i < 12;i++) {
        printf("%x ", encrypted[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    char* decrypted = bit_decrypt(encrypted);
    printf("\n\n\n");
    for(int i=0; i<12;i++){
        printf("%c", decrypted[i]);
    }
    free(encrypted);
    free(decrypted);
    printf("\n\n"); 

    //===============================================

    unsigned char* cipher;
    cipher=bmp_encrypt("ComPuTer", "Hello WoRld!");
    for(int i=0; i<12; i++){
        printf("%x ", cipher[i]);
    }

    printf("\n\n");

    unsigned char* decipher;
    decipher=(unsigned char*)bmp_decrypt("ComPuTer", cipher);
    for(int i=0; i<12; i++){
        printf("%c", decipher[i]);
    }
    printf("\n");
    
    free(cipher);
    free(decipher);

    return 0;
}
