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
    int position_text=0;
    int position_key=0;
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
    char* testKey=(char*)calloc(2*strlen(text)+1, sizeof(char));
        
    for(int i=0; i<strlen(text)+1; i++){
        testKey[i]=changed_key[i];
        //printf("\n%s\n", testKey[i]);
        if(key!=NULL){
            if(toupper(text[i])!=' ' && i<strlen(key)){
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                changed_key[i]=toupper(key[i]);
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
            } else if(i>(strlen(key)+counter-2) && toupper(text[i])!=' '){
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                jump=i%(strlen(key)+counter+length-1);
                changed_key[i]=toupper(key[jump]);
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                if(jump==(strlen(key)-1)){
                    length+=strlen(key);
                }
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
            } else if(toupper(text[i])==' ' && i<(strlen(key)+counter)){
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                changed_key[i]=' ';
                i++;
                for(int j=0; j<strlen(text)+1; j++){
                    if(toupper(text[i])!=' ' && i<(strlen(key)+counter)){
                        changed_key[i]=toupper(key[i-counter]);
                        i++;
                    }
                } 
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                if(toupper(text[counter+1])!='\0'){
                    counter++;
                }
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                if(counter<i){
                    i--;
                }
            }else if(toupper(text[i])==' ' && i>strlen(key)+counter-2){
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                changed_key[i]=' ';
                testKey[i]=changed_key[i];
                //printf("\n%s\n", testKey[i]);
                counter++;
            }
        }
    }
    free(testKey);
    changed_key[strlen(text)+1] = '\0';
    char* testText=(char*)calloc(2*strlen(text)+1, sizeof(char));

    for(int i=0; i<(strlen(text)+1); i++){
        for(int j=0; j<strlen(alphabet); j++){
            if(key!=NULL && text!=NULL){
                if(isalpha(changed_key[i]) && changed_key[i]==alphabet[j]){
                    testText[i]=new_text[i];
                    //printf("\n%s\n", testText[i]);
                    position_key=j;
                }
                if(isalpha(toupper(text[i])) && toupper(text[i])==alphabet[j]){
                    testText[i]=new_text[i];
                    //printf("\n%s\n", testText[i]);
                    position_text=j;
                }
                if(isalpha(toupper(text[i]))){
                    int all_size=position_text+position_key;

                    if(all_size<strlen(alphabet)){
                        /*if(all_size!=0){
                            new_text[i]=alphabet[all_size];
                        }*/
                        testText[i]=new_text[i];
                        //printf("\n%s\n", testText[i]);
                        new_text[i]=alphabet[all_size];
                        testText[i]=new_text[i];
                        //printf("\n%s\n", testText[i]);
                    } else if(all_size>strlen(alphabet) || all_size!=0){
                        testText[i]=new_text[i];
                        //printf("\n%s\n", testText[i]);
                        new_text[i]=alphabet[all_size-strlen(alphabet)];
                    }
                } else{
                    if(!isalpha(toupper(text[i]))){
                        testText[i]=new_text[i];
                        //printf("\n%s\n", testText[i]);
                        new_text[i]=toupper(text[i]);
                        testText[i]=new_text[i];
                        //printf("\n%s\n", testText[i]);
                    } else if(text[++i]=='\0' || changed_key[++i]=='\0'){
                        testText[i]=new_text[i];
                        //printf("\n%s\n", testText[i]);
                        break;
                    }
                }
            }
        }
    }
    free(testText);
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
    int position_text=0;
    int position_key=0;
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
    char* checkKey=(char*)calloc(2*strlen(text)+1, sizeof(char));
        
    for(int i=0; i<strlen(text)+1; i++){
        if(key!=NULL){
            if(toupper(text[i])!=' ' && i<strlen(key)){
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
                changed_key[i]=toupper(key[i]);
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
            } else if(i>(strlen(key)+counter-2) && toupper(text[i])!=' '){
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
                jump=i%(strlen(key)+counter+length-1);
                changed_key[i]=toupper(key[jump]);
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
                if(jump==(strlen(key)-1)){
                    length+=strlen(key);
                }
            } else if(toupper(text[i])==' ' && i<(strlen(key)+counter)){
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
                changed_key[i]=' ';
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
                i++;
                for(int j=0; j<strlen(text)+1; j++){
                    if(toupper(text[i])!=' ' && i<(strlen(key)+counter)){
                        checkKey[i]=changed_key[i];
                        //printf("\n%s\n", checkKey[i]);
                        changed_key[i]=toupper(key[i-counter]);
                        checkKey[i]=changed_key[i];
                        //printf("\n%s\n", checkKey[i]);
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
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
                changed_key[i]=' ';
                checkKey[i]=changed_key[i];
                //printf("\n%s\n", checkKey[i]);
                counter++;
            }
        }
    }
    free(checkKey);

    char* checkText=(char*)calloc(2*strlen(text)+1, sizeof(char));


    for(int i=0; i<(strlen(text)+1); i++){
        for(int j=0; j<strlen(alphabet); j++){
            checkText[i]=new_text[i];
            //printf("\n%s\n", checkText[i]);
            if(key!=NULL && text!=NULL){
                checkText[i]=new_text[i];
                //printf("\n%s\n", checkText[i]);
                if(isalpha(changed_key[i]) && changed_key[i]==alphabet[j]){
                    position_key=j;
                }
                checkText[i]=new_text[i];
                //printf("\n%s\n", checkText[i]);
                if(isalpha(toupper(text[i])) && toupper(text[i])==alphabet[j]){
                    position_text=j;
                }
                if(isalpha(toupper(text[i]))){
                    checkText[i]=new_text[i];
                    //printf("\n%s\n", checkText[i]);
                    int all_size=position_text-position_key;

                    if(all_size<strlen(alphabet) && all_size>-1){
                        checkText[i]=new_text[i];
                        //printf("\n%s\n", checkText[i]);
                        /*if(all_size!=0){
                            new_text[i]=alphabet[all_size];
                        }*/
                        new_text[i]=alphabet[all_size];
                        checkText[i]=new_text[i];
                        //printf("\n%s\n", checkText[i]);
                    } else if(all_size>strlen(alphabet) || all_size!=0){
                        checkText[i]=new_text[i];
                        //printf("\n%s\n", checkText[i]);
                        new_text[i]=alphabet[all_size+strlen(alphabet)];
                        checkText[i]=new_text[i];
                        //printf("\n%s\n", checkText[i]);
                    }
                } else{
                    checkText[i]=new_text[i];
                    //printf("\n%s\n", checkText[i]);
                    if(!isalpha(toupper(text[i]))){
                        new_text[i]=toupper(text[i]);
                        checkText[i]=new_text[i];
                        //printf("\n%s\n", checkText[i]);
                    } else if(text[++i]=='\0' || changed_key[++i]=='\0'){
                        checkText[i]=new_text[i];
                        //printf("\n%s\n", checkText[i]);
                        break;
                    }
                }
            }
        }
    }
    free(checkText);
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

    char* checkBits=(char*)calloc(2*strlen(text)+1, sizeof(char));

    for(int i=0; i<(strlen(text)+1); i++){
        int value = text[i];
        for(int j=0; j<8; j++){
            checkBits[i]=back_bits[j];
            //printf("\n%s\n", checkBits[i]);
            if(value%2==0){
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                back_bits[j]=0;
            } else{
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                back_bits[j]=1;
            }
            checkBits[i]=back_bits[j];
            //printf("\n%s\n", checkBits[i]);
            value/=2;
        }
        int m=7;
        for(int j=0; j<8; j++){
            if(j>=0){
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                if(++j==8){
                    new_bits[++j]=' ';
                }
                new_bits[j]=back_bits[m];
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                m--;
            }
        }
        //printf("%ls", new_bits);      
    }
    //printf("\n\n");
    free(checkBits);
    free(new_bits);
    new_bits=NULL;

    char* checkWord=(char*)calloc(2*strlen(text)+1, sizeof(char));

    for(int i=0; i<(strlen(text)+1); i++){
        //if(new_text!=NULL){
            checkWord[i]=bits_word[i];
            //printf("\n%s\n", checkWord[i]);
            unsigned char word=new_text[i];
        //}
        for(int j=0; j<8; j++, word/=2){
            checkWord[i]=bits_word[j];
            //printf("\n%s\n", checkWord[i]);
            bits_word[7-j]=(word%2)+'0';
        }
        for(int j=4; j<8; j++){
            checkWord[i]=bits_word[j];
            //printf("\n%s\n", checkWord[i]);
            second_pair[j-4]=bits_word[j];
        }
        for(int j=0; j<4; j+=2){
            checkWord[i]=bits_word[j];
            //printf("\n%s\n", checkWord[i]);
            first_pair[j]=bits_word[j+1];
            checkWord[i]=bits_word[j];
            //printf("\n%s\n", checkWord[i]);
            first_pair[j+1]=bits_word[j];
        }
        for(int j=0; j<4; j++){
            checkWord[i]=bits_word[j];
            //printf("\n%s\n", checkWord[i]);
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
                checkWord[i]=bits_word[j];
                //printf("\n%s\n", checkWord[i]);
                bits_word[j]=first_pair[j];
                if(bits_word[j]!=2){
                    checkWord[i]=bits_word[j];
                    //printf("\n%s\n", checkWord[i]);
                    bits_word[j]=second_pair[j-4];
                }
            } else if(j<4){
                checkWord[i]=bits_word[j];
                //printf("\n%s\n", checkWord[i]);
                if(bits_word[j]!=-1){
                    bits_word[j]=first_pair[j];
                }
                checkWord[i]=bits_word[j];
                //printf("\n%s\n", checkWord[i]);
            }
        }
        if(bits_word!=NULL){
            checkWord[i]=bits_word[i];
            //printf("\n%s\n", checkWord[i]);
            new_text[i]=strtoul(bits_word,'\0',2);
            checkWord[i]=bits_word[i];
            //printf("\n%s\n", checkWord[i]);
        }
    }
    free(checkWord);

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
    char* checkBits=(char*)calloc(2*strlen((char*)text)+1, sizeof(char));
    //char bits[8];
    //int count=9;

    for(int i=0; i<(strlen((char*)text)+1); i++){
        checkBits[i]=back_bits[i];
        //printf("\n%s\n", checkBits[i]);
        int value = text[i];
        for(int j=0; j<8; j++){
            checkBits[i]=back_bits[j];
            //printf("\n%s\n", checkBits[i]);
            if(value%2==0){
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                back_bits[j]=0;
            } else{
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                back_bits[j]=1;
            }
            checkBits[i]=back_bits[j];
            //printf("\n%s\n", checkBits[i]);
            value/=2;
        }
        int m=7;
        for(int j=0; j<8; j++){
            if(j>=0){
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                if(++j==8){
                    checkBits[i]=back_bits[j];
                    //printf("\n%s\n", checkBits[i]);
                    new_bits[++j]=' ';
                }
                new_bits[j]=back_bits[m];
                checkBits[i]=back_bits[j];
                //printf("\n%s\n", checkBits[i]);
                m--;
            }
        }
        //printf("%ls", new_bits);      
    }
    free(checkBits);
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

    char* checkText=(char*)calloc(2*strlen((char*)text)+1, sizeof(char));

    for(int i=0; i<strlen((char*)text)+1; i++){
        checkText[i]=bits_word[i];
        //printf("\n%s\n", checkText[i]);
        //if(new_text!=NULL){
            unsigned char word=new_text[i];
        //}
        for(int j=0; j<8; j++, word/=2){
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
            bits_word[7-j]=(word%2)+'0';
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
        }
        for(int j=4; j<8; j++){
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
            second_pair[j-4]=bits_word[j];
        }
        for(int j=0; j<4; j++){
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
            first_pair[j]=bits_word[j];
        }
        for(int j=0; j<4; j++){
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
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
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
            first_pair[j]=bits_word[j+1];
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
            first_pair[j+1]=bits_word[j];
            checkText[i]=bits_word[j];
            //printf("\n%s\n", checkText[i]);
        }
        for(int j=0; j<8; j++){
            if(j>3){
                checkText[i]=bits_word[j];
                //printf("\n%s\n", checkText[i]);
                bits_word[j]=first_pair[j];
                if(bits_word[j]!=2){
                    checkText[i]=bits_word[j];
                    //printf("\n%s\n", checkText[i]);
                    bits_word[j]=second_pair[j-4];
                }
            } else if(j<4){
                if(bits_word[j]!=-1){
                    checkText[i]=bits_word[j];
                    //printf("\n%s\n", checkText[i]);
                    bits_word[j]=first_pair[j];
                }
            }
        }
        if(bits_word!=NULL){
            checkText[i]=bits_word[i];
            //printf("\n%s\n", checkText[i]);
            new_text[i]=strtoul(bits_word,'\0', 2);
        }
	}
    free(checkText);

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
