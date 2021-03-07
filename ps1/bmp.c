#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "bmp.h"

//=========================================================================

char* reverse(const char* text){
    if(text == NULL){
        return NULL;
    }

    int count=0;
    //int length=0;
    //char new_text[strlen(text)+1];
    char *new_text=(char*)calloc(2*strlen(text)+1, sizeof(char));

    for(int i = 0; i<strlen(text); i++){
        if((i+1) == strlen(text)){
            for(int j=0; j<strlen(text); j++, count--){
                new_text[j] = toupper(text[count]);
                if((j+1) == strlen(text)){
                    new_text[++j] = '\0';
                }
            }
        } 
        count++;
    }
    
    return new_text;
}

//======================================================================

char* vigenere_encrypt(const char* key, const char* text){
	if(key==NULL || text==NULL){
        return NULL; 
    }
    for(int proverka=0; key[proverka]!='\0'; proverka++){
        if(!isalpha(key[proverka])){
            return NULL;
        }
    }
    char alphabet[26];
    for(int i=0; i<26; i++){
        alphabet[i]=(char)(97 + i);
        if(i==25){
            alphabet[i+1] = '\0';
        }
        alphabet[i]=toupper(alphabet[i]);
    }         
    char *new_text=(char*)calloc(2*strlen(text)+41, sizeof(char));
    int counter=1, length=0, jump=0;
    /*for(int i=0, k=0, l=0; i<(strlen(text)+1); i++){
        for(int j=0; j<strlen(alphabet); j++){
            if(isalpha(text[i]) && text[i]==alphabet[j]){
                k = j;
            }
            if(isalpha(key[i]) && key[i]==alphabet[j]){
                l = j;
            }
            if(isalpha(text[i])){
                if((k+l)<strlen(alphabet)){
                    new_text[i]=alphabet[k+1];
                } else{
                    new_text[i]=alphabet[(k+l)-strlen(alphabet)];
                }
            } else{
                new_text[i]=text[i];
                break;
            }
        }
    }*/
    char changed_key[strlen(text)+2];
    /*for(int i=0; i<(strlen(key)+1); i++){
        new_key[i]=toupper(key[i]);
    }*/
    /*int counter=0;
    int length_key=0;
    for(int i=0; i<(strlen(text)+1); i++){
        if(text[i]!=' '){
            new_key[i]=toupper(key[length_key]);
            length_key++;
        }
        if(text[i]==' '){
            new_key[i]=' ';
        }
        if(key[length_key]=='\0' && i!=(length_key-1)){
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
        if(key[length_key]=='\0' && i==(length_key-1)){
            new_key[i]=' ';
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
    }*/

    
    changed_key[strlen(text)+1]='\0';

    counter=1;
    length=0;
    jump=0;
        
    for(int i=0; i<strlen(text)+1; i++){
        if(key!=NULL){
            if(toupper(text[i])!=' ' && i<strlen(key)){
                changed_key[i]=toupper(key[i]);
            } else if(i>(strlen(key)+counter-2) && toupper(text[i])!=' '){
                jump=i%(strlen(key)+counter+length-1);
                changed_key[i]=toupper(key[jump]);
                if(jump==(strlen(key)-1)){
                    length+=strlen(key);
                }
            } else if(toupper(text[i])==' ' && i<(strlen(key)+counter)){
                changed_key[i]=' ';
                i++;
                for(int j=0; j<strlen(text)+1; j++){
                    if(toupper(text[i])!=' ' && i<(strlen(key)+counter)){
                        changed_key[i]=toupper(key[i-counter]);
                        i++;
                    }
                } 
                if(toupper(text[counter+1])!='\0'){
                    counter++;
                }
                if(counter<i){
                    i--;
                }
            }else if(toupper(text[i])==' ' && i>strlen(key)+counter-2){
                changed_key[i]=' ';
                counter++;
            }
        }
    }
    changed_key[strlen(text)+1] = '\0';
    int position_text=0;
    int position_key=0;

    for(int i=0; i<(strlen(text)+1); i++){
        for(int j=0; j<strlen(alphabet); j++){
            if(key!=NULL && text!=NULL){
                if(isalpha(changed_key[i]) && changed_key[i]==alphabet[j]){
                    position_key=j;
                }
                if(isalpha(toupper(text[i])) && toupper(text[i])==alphabet[j]){
                    position_text=j;
                }
                if(isalpha(toupper(text[i]))){
                    int all_size=position_text+position_key;

                    if(all_size<strlen(alphabet)){
                        /*if(all_size!=0){
                            new_text[i]=alphabet[all_size];
                        }*/
                        new_text[i]=alphabet[all_size];
                    } else if(all_size>strlen(alphabet) || all_size!=0){
                        new_text[i]=alphabet[all_size-strlen(alphabet)];
                    }
                } else{
                    if(!isalpha(toupper(text[i]))){
                        new_text[i]=toupper(text[i]);
                    } else if(text[++i]=='\0' || changed_key[++i]=='\0'){
                        break;
                    }
                }
            }
        }
    }
    new_text[strlen(text)+1]='\0';


    return new_text;
}

char* vigenere_decrypt(const char* key, const char* text){
    if(key==NULL || text==NULL){
        return NULL; 
    }
    for(int proverka=0; key[proverka]!='\0'; proverka++){
        if(!isalpha(key[proverka])){
            return NULL;
        }
    }
    char alphabet[26];
    for(int i=0; i<26; i++){
        alphabet[i]=(char)(97 + i);
        if(i==25){
            alphabet[i+1] = '\0';
        }
        alphabet[i]=toupper(alphabet[i]);
    }         
    char *new_text=(char*)calloc(2*strlen(text)+41, sizeof(char));
    int counter=1, length=0, jump=0;
    /*for(int i=0, k=0, l=0; i<(strlen(text)+1); i++){
        for(int j=0; j<strlen(alphabet); j++){
            if(isalpha(text[i]) && text[i]==alphabet[j]){
                k = j;
            }
            if(isalpha(key[i]) && key[i]==alphabet[j]){
                l = j;
            }
            if(isalpha(text[i])){
                if((k+l)<strlen(alphabet)){
                    new_text[i]=alphabet[k+1];
                } else{
                    new_text[i]=alphabet[(k+l)-strlen(alphabet)];
                }
            } else{
                new_text[i]=text[i];
                break;
            }
        }
    }*/
    char changed_key[strlen(text)+2];
    /*for(int i=0; i<(strlen(key)+1); i++){
        new_key[i]=toupper(key[i]);
    }*/
    /*int counter=0;
    int length_key=0;
    for(int i=0; i<(strlen(text)+1); i++){
        if(text[i]!=' '){
            new_key[i]=toupper(key[length_key]);
            length_key++;
        }
        if(text[i]==' '){
            new_key[i]=' ';
        }
        if(key[length_key]=='\0' && i!=(length_key-1)){
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
        if(key[length_key]=='\0' && i==(length_key-1)){
            new_key[i]=' ';
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
    }*/

    
    changed_key[strlen(text)+2]='\0';

    counter=1;
    length=0;
    jump=0;
        
    for(int i=0; i<strlen(text)+1; i++){
        if(key!=NULL){
            if(toupper(text[i])!=' ' && i<strlen(key)){
                changed_key[i]=toupper(key[i]);
            } else if(i>(strlen(key)+counter-2) && toupper(text[i])!=' '){
                jump=i%(strlen(key)+counter+length-1);
                changed_key[i]=toupper(key[jump]);
                if(jump==(strlen(key)-1)){
                    length+=strlen(key);
                }
            } else if(toupper(text[i])==' ' && i<(strlen(key)+counter)){
                changed_key[i]=' ';
                i++;
                for(int j=0; j<strlen(text)+1; j++){
                    if(toupper(text[i])!=' ' && i<(strlen(key)+counter)){
                        changed_key[i]=toupper(key[i-counter]);
                        i++;
                    }
                } 
                if(toupper(text[counter+1])!='\0'){
                    counter++;
                }
                if(counter<i){
                    i--;
                }
            }else if(toupper(text[i])==' ' && i>strlen(key)+counter-2){
                changed_key[i]=' ';
                counter++;
            }
        }
    }
    int position_text=0;
    int position_key=0;

    for(int i=0; i<(strlen(text)+1); i++){
        for(int j=0; j<strlen(alphabet); j++){
            if(key!=NULL && text!=NULL){
                if(isalpha(changed_key[i]) && changed_key[i]==alphabet[j]){
                    position_key=j;
                }
                if(isalpha(toupper(text[i])) && toupper(text[i])==alphabet[j]){
                    position_text=j;
                }
                if(isalpha(toupper(text[i]))){
                    int all_size=position_text-position_key;

                    if(all_size<strlen(alphabet) && all_size>-1){
                        /*if(all_size!=0){
                            new_text[i]=alphabet[all_size];
                        }*/
                        new_text[i]=alphabet[all_size];
                    } else if(all_size>strlen(alphabet) || all_size!=0){
                        new_text[i]=alphabet[all_size+strlen(alphabet)];
                    }
                } else{
                    if(!isalpha(toupper(text[i]))){
                        new_text[i]=toupper(text[i]);
                    } else if(text[++i]=='\0' || changed_key[++i]=='\0'){
                        break;
                    }
                }
            }
        }
    }
    new_text[strlen(text)+1]='\0';

    return new_text;
}

//================================================================================================

unsigned char* bit_encrypt(const char* text){
	if(text==NULL){
        return NULL;
    }
    /*for(int i=0; i<(strlen(key)+1); i++){
        new_key[i]=toupper(key[i]);
    }*/
    /*int counter=0;
    int length_key=0;
    for(int i=0; i<(strlen(text)+1); i++){
        if(text[i]!=' '){
            new_key[i]=toupper(key[length_key]);
            length_key++;
        }
        if(text[i]==' '){
            new_key[i]=' ';
        }
        if(key[length_key]=='\0' && i!=(length_key-1)){
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
        if(key[length_key]=='\0' && i==(length_key-1)){
            new_key[i]=' ';
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
    }*/
    unsigned char* new_text=(unsigned char*)calloc(2*strlen(text)+41, sizeof(char));
    memcpy(new_text, (unsigned char*)text, strlen(text)+1);
    unsigned int* new_bits=(unsigned int*)calloc(2*strlen(text)+41, sizeof(int));
    char back_bits[8];
    //char bits[8];
    //int count=9;
    //==============================problem
    char bits_word[9];
    bits_word[8] = '\0';
    char first_pair[5];
    first_pair[4] = '\0';
    char second_pair[5];
    second_pair[4] = '\0';
    //===============================


    for(int i=0; i<(strlen(text)+1); i++){
        int value = text[i];
        for(int j=0; j<8; j++){
            if(value%2==0){
                back_bits[j]=0;
            } else{
                back_bits[j]=1;
            }
            value/=2;
        }
        int m=7;
        for(int j=0; j<8; j++){
            if(j>=0){
                if(++j==8){
                    new_bits[++j]=' ';
                }
                new_bits[j]=back_bits[m];
                m--;
            }
        }
        //printf("%ls", new_bits);      
    }
    //printf("\n\n");
    free(new_bits);
    new_bits=NULL;


    for(int i=0; i<(strlen(text)+1); i++){
        //if(new_text!=NULL){
            unsigned char word=new_text[i];
        //}
        for(int j=0; j<8; j++, word/=2){
            bits_word[7-j]=(word%2)+'0';
        }
        for(int j=4; j<8; j++){
            second_pair[j-4]=bits_word[j];
        }
        for(int j=0; j<4; j+=2){
            first_pair[j]=bits_word[j+1];
            first_pair[j+1]=bits_word[j];
        }
        for(int j=0; j<4; j++){
            if(first_pair[j]=='1' && first_pair[j]==second_pair[j]){
                second_pair[j]='0';
            } else if(first_pair[j]=='0' && first_pair[j]==second_pair[j]){
                second_pair[j]='0';
            } else if(first_pair[j]=='1' && first_pair[j]!=second_pair[j]){
                second_pair[j]='1';
            } else if(first_pair[j]=='0' && first_pair[j]!=second_pair[j]){
                second_pair[j]='1';
            }
        }
        for(int j=0; j<8; j++){
            if(j>3){
                bits_word[j]=first_pair[j];
                if(bits_word[j]!=2){
                    bits_word[j]=second_pair[j-4];
                }
            } else if(j<4){
                if(bits_word[j]!=-1){
                    bits_word[j]=first_pair[j];
                }
            }
        }
        if(bits_word!=NULL){
            new_text[i]=strtoul(bits_word,'\0',2);
        }
    }

    return new_text;
}
char* bit_decrypt(const unsigned char* text){
    if(text==NULL){
        return NULL;
    }
    /*for(int i=0; i<(strlen(key)+1); i++){
        new_key[i]=toupper(key[i]);
    }*/
    /*int counter=0;
    int length_key=0;
    for(int i=0; i<(strlen(text)+1); i++){
        if(text[i]!=' '){
            new_key[i]=toupper(key[length_key]);
            length_key++;
        }
        if(text[i]==' '){
            new_key[i]=' ';
        }
        if(key[length_key]=='\0' && i!=(length_key-1)){
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
        if(key[length_key]=='\0' && i==(length_key-1)){
            new_key[i]=' ';
            counter=i+1;
            for(int j=0; j<(strlen(text)+1-i); j++){
                new_key[counter]=toupper(key[j]);
                counter++;
            }
            break;
        }
    }*/
    char* new_text=(char*)calloc(strlen((char*)text)+41, sizeof(char));
    memcpy(new_text, text, strlen((char*)text));

    unsigned int* new_bits=(unsigned int*)calloc(2*strlen((char*)text)+41, sizeof(int));
    char back_bits[8];
    //char bits[8];
    //int count=9;

    for(int i=0; i<(strlen((char*)text)+1); i++){
        int value = text[i];
        for(int j=0; j<8; j++){
            if(value%2==0){
                back_bits[j]=0;
            } else{
                back_bits[j]=1;
            }
            value/=2;
        }
        int m=7;
        for(int j=0; j<8; j++){
            if(j>=0){
                if(++j==8){
                    new_bits[++j]=' ';
                }
                new_bits[j]=back_bits[m];
                m--;
            }
        }
        //printf("%ls", new_bits);      
    }
    //printf("\n\n");
    free(new_bits);
    new_bits=NULL;

    //========================problem
    char bits_word[9];
    bits_word[8] = '\0';
    char first_pair[5];
    first_pair[4] = '\0';
    char second_pair[5];
    second_pair[4] = '\0';
    //========================


    for(int i=0; i<strlen((char*)text)+1; i++){
        //if(new_text!=NULL){
            unsigned char word=new_text[i];
        //}
        for(int j=0; j<8; j++, word/=2){
            bits_word[7-j]=(word%2)+'0';
        }
        for(int j=4; j<8; j++){
            second_pair[j-4]=bits_word[j];
        }
        for(int j=0; j<4; j++){
            first_pair[j]=bits_word[j];
        }
        for(int j=0; j<4; j++){
            if(first_pair[j]=='0' && first_pair[j]==second_pair[j]){
                second_pair[j]='0';
            } else if(first_pair[j]=='1' && first_pair[j]==second_pair[j]){
                second_pair[j]='0';
            } else if(first_pair[j]=='0' && first_pair[j]!=second_pair[j]){
                second_pair[j]='1';
            } else if(first_pair[j]=='1' && first_pair[j]!=second_pair[j]){
                second_pair[j]='1';
            }
        }
        for(int j=0; j<4; j+=2){
            first_pair[j]=bits_word[j+1];
            first_pair[j+1]=bits_word[j];
        }
        for(int j=0; j<8; j++){
            if(j>3){
                bits_word[j]=first_pair[j];
                if(bits_word[j]!=2){
                    bits_word[j]=second_pair[j-4];
                }
            } else if(j<4){
                if(bits_word[j]!=-1){
                    bits_word[j]=first_pair[j];
                }
            }
        }
        if(bits_word!=NULL){
            new_text[i]=strtoul(bits_word,'\0', 2);
        }
	}

    return new_text;
}

//==================================================================================

unsigned char* bmp_encrypt(const char* key, const char* text){
    if(key==NULL || text==NULL){
        return NULL;
    }
    for(int proverka=0; key[proverka]!='\0'; proverka++){
        if(!isalpha(key[proverka])){
            return NULL;
        }
    }
    char* reverse_cipher=reverse(text);
    char* vigenere_cipher=vigenere_encrypt(key, reverse_cipher);
    unsigned char* bit_cipher=bit_encrypt(vigenere_cipher);
    unsigned char* cipher=(unsigned char*)calloc(2*strlen((char*)text)+1, sizeof(char));
    memcpy(cipher, bit_cipher, strlen((char*)text));
    
    free(reverse_cipher);
    free(vigenere_cipher);
    free(bit_cipher);

    return cipher;
}
char* bmp_decrypt(const char* key, const unsigned char* text){
    if(key==NULL || text==NULL){
        return NULL;
    }
    for(int proverka=0; key[proverka]!='\0'; proverka++){
        if(!isalpha(key[proverka])){
            return NULL;
        }
    }
    char* bit_cipher=bit_decrypt(text);
    char* vigenere_cipher=vigenere_decrypt(key, bit_cipher);
    char* reverse_cipher=reverse(vigenere_cipher);
    char* cipher=(char*)calloc(2*strlen((char*)text)+1, sizeof(char));
    strcpy(cipher, reverse_cipher);

    free(reverse_cipher);
    free(vigenere_cipher);
    free(bit_cipher);

    return cipher;
}
