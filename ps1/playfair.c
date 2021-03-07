#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playfair.h"

char* playfair_encrypt(const char* key, const char* text){
    if(text == NULL || key == NULL){
        return NULL;
    }
    for(int proverka=0; key[proverka]!='\0'; proverka++){
        if(key[proverka]!=' ' && !isalpha(key[proverka])){
            return NULL;
        }
    }
    int numberLine=-1;
    //char *playfair = (char*)calloc(2*strlen(text), sizeof(char));
    char *changed_key = (char*)calloc(strlen(key)+1, sizeof(char));
    strcpy(changed_key, key);
    //char *changed_text=(char*)calloc(2*strlen(text), sizeof(char));
    int length=0;
    //======================= problem 
    char alphabet[26];
    strcpy(alphabet, ALPHA);
    //alphabet[26]='\0';
    //=======================
    char cipher_table[5][5];
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cipher_table[i][j]='A';
        }
    }
    //printf("%s\n", alphabet);

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

    for(int i=0; i<strlen(key); i++){
        /*if(key[i]!=' ' && !isalpha(key[i])){
            free(changed_key);
            return NULL;
        }*/
        changed_key[i]=key[i];
        changed_key[i]=toupper(changed_key[i]);
        if(changed_key[i]=='W'){
            changed_key[i]='V';
        }
        if(key[i+1]=='\0'){
            changed_key[i+1]='\0';
        }
    }

    char *upgrade_key=(char*)calloc(2*strlen(text)+1, sizeof(char));
    int repeating3=0;

    for(int i=0; i<5; i++){
        upgrade_key[i+repeating3]=changed_key[i];
        repeating3++;
    }
    free(upgrade_key);

    //================================================================

    char *changed_text=(char*)calloc(2*strlen(text)+1, sizeof(char));

    for(int i=0, another=0; i<strlen(text); i++){
        //if(changed_text!=NULL){
            changed_text[i+another]=toupper(text[i]);
        //}
        if(length>-1){
            length++;
        }

        if(changed_text[i+another]=='W'){
            changed_text[i+another]='V';
        }else if(changed_text[i+another]==' '){
            if(length>-1){
                length--;
                another--;
            }
        }
        if(length>-1 && another>-1){
            if((another+i)%2==1){
                if(changed_text[i+another]!=' '){
                    if(changed_text[i+another]!='X'){
                        if(changed_text[i+another]==changed_text[i-1+another]){
                            changed_text[i+another+1]=changed_text[i+another];
                            changed_text[i+another]='X';
                            if(length>-1 && another>-1){
                                length++;
                                if(another>=0){
                                    another++;
                                }
                            }
                        }
                    }
                }
            }
        }
        if((another+i)%2==1){
            if(changed_text[i+another]!=' '){
                if(changed_text[i+another]!='X'){
                    if(changed_text[i+another]==changed_text[i-1+another]){
                        changed_text[i+another+1]=changed_text[i+another];
                        changed_text[i+another]='X';
                        if(length>-1 && another>-1){
                            length++;
                            if(another>=0){
                                another++;
                            }
                        }
                    }
                }
            }
        }
        if(length>=0){
            if(length%2==1){
                changed_text[length]='X';
            }
        }
    }
    char *down=(char*)calloc(2*strlen(text)+1, sizeof(char));
    changed_text[++length]='\0';
    int repeating5=0;

    for(int i=0; i<5; i++){
        down[i+repeating5]=changed_key[i];
        repeating5++;
    }
    free(down);
    //changed_text[++length]='\0';

    //===============================================================================

    /*char alphabet[26];
    strcpy(alphabet, ALPHA);
    alphabet[26]='\0';
    char cipher_table[5][5];*/
    //printf("%s\n", alphabet);

//===========================================================

    for(int i=0 ; i<5; i++){
        for(int j=0; j<5; j++){
            if(numberLine>-10){
                numberLine++;
            }

                if(numberLine<strlen(key)){
                    if(numberLine>-10){
                        cipher_table[i][j]='.'; 
                    }
                    
                    for(int alph=0; alph<25 ; alph++){
                        if(alphabet[alph]==changed_key[numberLine]){
                            if(alphabet[alph]!=25){
                                alphabet[alph]='.';
                            }
                            if(cipher_table!=NULL){
                                cipher_table[i][j]=changed_key[numberLine];
                            }
                        }
                    }
                    if(cipher_table[i][j]=='.'){
                        if(j>-1){
                            if(j!=0){
                                j--;
                            } else if(j==0){
                                if(j!='.'){
                                    j--;
                                }
                                j=4;
                            }
                        }
                    }
                }else if(cipher_table[i][j]!='.'){
                    for(int alph=0; alph<25 ; alph++){
                        //if(isalpha(alphabet)==0){
                            if(alphabet[alph]!='.'){
                                if(cipher_table!=NULL){
                                    cipher_table[i][j]=alphabet[alph];
                                }
                                if(alphabet[alph]!=25){
                                    alphabet[alph]='.';
                                }
                                break;
                            }
                        //}
                }
            }
        }
    }
    //printf("%s\n\n", changed_text);

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            //printf("%c", table[i][j]);
        } 
        //printf("\n");
    }
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(cipher_table[i][j]=='H'){
                //printf("\n%d, %d\n", i, j);
            }
        } 
        //printf("\n");
    }
    //printf("\n\n%d\n\n", length);
    //int first_pos_x=0, first_pos_y=0, second_pos_x=0, second_pos_y=0;
    int* numbers=(int*)calloc(2*strlen(text)+1, sizeof(int));
    char *playfair = (char*)calloc(2*strlen(text)+1, sizeof(char));
    int counter=0;

    for(int i=0, g=1; i<length; i+=2, g+=2){
        for(int first_pos_x=0 ; first_pos_x<5; first_pos_x++){
            counter++;
            for(int first_pos_y=0; first_pos_y<5; first_pos_y++){
                if(changed_text[i]==cipher_table[first_pos_x][first_pos_y]){
                    counter++;
                    for(int second_pos_x=0; second_pos_x<5; second_pos_x++){
                        for(int second_pos_y=0; second_pos_y<5; second_pos_y++){
                            if(changed_text[i+1]==cipher_table[second_pos_x][second_pos_y]){
                                counter++;
                                if(first_pos_x==second_pos_x || first_pos_y==second_pos_y){
                                    if(first_pos_x==second_pos_x){
                                        numbers[i]=first_pos_x;
                                        //printf("%ls", numbers);
                                        numbers[i]=first_pos_y;
                                        //printf("%ls", numbers);
                                        counter++;
                                        if(first_pos_y==4){
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                            playfair[i]=cipher_table[first_pos_x][0];
                                        } else if(first_pos_y>=0 && first_pos_y<4){
                                            playfair[i]=cipher_table[first_pos_x][first_pos_y+1];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        }
                                        counter++;
                                        numbers[i]=first_pos_x;
                                        //printf("%ls", numbers);
                                        numbers[i]=first_pos_y;
                                        //printf("%ls", numbers);
                                        if(second_pos_y==4){
                                            playfair[g]=cipher_table[second_pos_x][0];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        } else if(second_pos_y>=0 && second_pos_y<4){
                                            playfair[g]=cipher_table[second_pos_x][second_pos_y+1];
                                        }
                                        counter++;
                                        numbers[i]=first_pos_x;
                                        //printf("%ls", numbers);
                                        numbers[i]=first_pos_y;
                                        //printf("%ls", numbers);
                                    }
                                    if(first_pos_y==second_pos_y){
                                        if(first_pos_x==4){
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                            playfair[i]=cipher_table[0][first_pos_y];
                                        } else if(first_pos_x>=0 && first_pos_x<4){
                                            playfair[i]=cipher_table[first_pos_x+1][first_pos_y];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        }
                                        counter++;
                                        if(second_pos_x==4){
                                            playfair[g]=cipher_table[0][second_pos_y];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        } else if(second_pos_x>=0 && second_pos_x<4){
                                            playfair[g]=cipher_table[second_pos_x+1][second_pos_y];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        }       
                                        counter++;                            
                                    }
                                } else if(first_pos_x!=second_pos_x && first_pos_y!=second_pos_y){
                                    playfair[g]=cipher_table[second_pos_x][first_pos_y];
                                    numbers[i]=first_pos_x;
                                    //printf("%ls", numbers);
                                    numbers[i]=first_pos_y;
                                    //printf("%ls", numbers);
                                    playfair[i]=cipher_table[first_pos_x][second_pos_y];
                                    numbers[i]=first_pos_x;
                                    //printf("%ls", numbers);
                                    numbers[i]=first_pos_y;
                                    //printf("%ls", numbers);
                                }
                                counter=0;
            
                            }
                        }
                    }
                }
            }
        }
    }
    free(numbers);
    free(changed_text);
    free(changed_key);
    changed_key=NULL;
    changed_text=NULL;
    numbers=NULL;
    int finally_length=length+(length)/2;
    //printf("\n%d, %d, %d, %d\n\n", first_pos_x, first_pos_y, second_pos_x, second_pos_y);
    
    playfair[finally_length]='\0';

    for(int i=0; i<finally_length; i++){
        if(finally_length>=0){
            if(i%3==2){
                for(int j=finally_length; j>i; j--){
                    playfair[j]=playfair[j-1];
                }
                playfair[i]=' ';
            }
        }
    }

    return playfair;
}

//============================================================================================

char* playfair_decrypt(const char* key, const char* text){
    if(key==NULL || text==NULL){
        return NULL;
    } 
    for(int proverka=0; key[proverka]!='\0'; proverka++){
        if(key[proverka]!=' ' && !isalpha(key[proverka])){
            return NULL;
        }
    }

    int numberLine=-1;
    char changed_plafair[strlen(text)];
    strcpy(changed_plafair,text);
    //memcpy(changed_plafair, text, strlen(text));
    int last_position=4;
    int finally_length=strlen(text)-(strlen(text)+1)/3+1;
    //char *playfair = (char*)calloc(2*strlen(text)+1, sizeof(char));
    char *changed_key = (char*)calloc(2*strlen(key)+1, sizeof(char));
    //char *changed_text=(char*)calloc(2*strlen(text)+1, sizeof(char));
    //char mytext[finally_length];
    //playfair[finally_length]='\0';
    //mytext[finally_length]='\0';
    int length=0;

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

    for(int i=0; i<strlen(key); i++){
        /*if(key[i]!=' ' && !isalpha(key[i])){
            free(changed_key);
            return NULL;
        }*/
        changed_key[i]=key[i];
        changed_key[i]=toupper(changed_key[i]);
        if(changed_key[i]=='W'){
            changed_key[i]='V';
        }
        if(key[i+1]=='\0'){
            changed_key[i+1]='\0';
        }
    }

    char *upgrade_key=(char*)calloc(2*strlen(text)+1, sizeof(char));
    char *changed_text=(char*)calloc(2*strlen(text)+1, sizeof(char));
    int repeating8=0;

    for(int i=0; i<5; i++){
        upgrade_key[i+repeating8]=changed_key[i];
        repeating8++;
    }
    free(upgrade_key);   

    for(int i=0, another=0; i<strlen(text); i++){
        //if(changed_text!=NULL){
            changed_text[i+another]=toupper(text[i]);
        //}
        if(length>-1){
            length++;
        }

        if(changed_text[i+another]=='W'){
            changed_text[i+another]='V';
        }else if(changed_text[i+another]==' '){
            if(length>-1){
                length--;
                another--;
            }
        }
        if(length>-1 && another>-1){
            /*for(int i=0; i<(strlen(key)+1); i++){
        new_key[i]=toupper(key[i]);
    }*/
    /*int counter=0;
    int length_key=0;
    */
            if((another+i)%2==1){
                if(changed_text[i+another]!=' '){
                    if(changed_text[i+another]!='X'){
                        if(changed_text[i+another]==changed_text[i-1+another]){
                            changed_text[i+another+1]=changed_text[i+another];
                            if(changed_text[i]>-1){
                                changed_text[i+another]='X';
                            }
                            if(length>-1 && another>-1){
                                length++;
                                if(another>=0){
                                    another++;
                                }
                            }
                        }
                    }
                }
            }
        }
        if((another+i)%2==1){
            if(changed_text[i+another]!=' '){
                if(changed_text[i+another]!='X'){
                    if(changed_text[i+another]==changed_text[i-1+another]){
                        changed_text[i+another+1]=changed_text[i+another];
                        changed_text[i+another]='X';
                        if(length>-1 && another>-1){
                            length++;
                            if(another>=0){
                                another++;
                            }
                        }
                    }
                }
            }
        }
        if(length>=0){
            if(length%2==1){
                changed_text[length]='X';
            }
        }
    }
    //=======================================================
    char *down2=(char*)calloc(2*strlen(text)+1, sizeof(char));
    int repeating1=0;

    for(int i=0; i<5; i++){
        down2[i+repeating1]=down2[i];
        repeating1++;
    }
    free(down2);
    changed_text[++length]='\0';

    char *upgrade_key1=(char*)calloc(2*strlen(text)+1, sizeof(char));
    int repeating2=0;

    for(int i=0; i<5; i++){
        upgrade_key1[i+repeating2]=upgrade_key1[i];
        repeating2++;
    }
    free(upgrade_key1);
    //=============================problem
    char alphabet[27];
    strcpy(alphabet, ALPHA);
    alphabet[26]='\0';
    //=============================
    char cipher_table[5][5];
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cipher_table[i][j]='A';
        }
    }
    //printf("%s\n", alphabet);

    char *down1=(char*)calloc(2*strlen(text)+1, sizeof(char));
    int repeating=0;

    for(int i=0; i<5; i++){
        down1[i+repeating]=down1[i];
        repeating++;
    }
    free(down1);

    for(int i=0 ; i<5; i++){
        for(int j=0; j<5; j++){
            if(numberLine>-10){
                numberLine++;
            }

                if(numberLine<strlen(key)){
                    if(numberLine>-10){
                        cipher_table[i][j]='.'; 
                    }
                    
                    for(int alph=0; alph<25 ; alph++){
                        if(alphabet[alph]==changed_key[numberLine]){
                            if(alphabet[alph]!=25){
                                alphabet[alph]='.';
                            }
                            if(cipher_table!=NULL){
                                cipher_table[i][j]=changed_key[numberLine];
                            }
                        }
                    }
                    if(cipher_table[i][j]=='.'){
                        if(j>-1){
                            if(j!=0){
                                j--;
                            } else if(j==0){
                                if(j!='.'){
                                    j--;
                                }
                                j=4;
                            }
                        }
                    }
                }else if(cipher_table[i][j]!='.'){
                    for(int alph=0; alph<25 ; alph++){
                        //if(isalpha(alphabet)==0){
                            if(alphabet[alph]!='.'){
                                if(cipher_table!=NULL){
                                    cipher_table[i][j]=alphabet[alph];
                                }
                                if(alphabet[alph]!=25){
                                    alphabet[alph]='.';
                                }
                                break;
                            }
                        //}
                }
            }
        }
    }
    //printf("%s\n\n", changed_text);

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            //printf("%c", cipher_table[i][j]);
        } 
        //printf("\n");
    }
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(cipher_table[i][j]=='H'){
                //printf("\n%d, %d\n", i, j);
            }
        } 
        //printf("\n");
    }
    //printf("\n\n%d\n\n", length);
    char *playfair = (char*)calloc(2*strlen(text)+1, sizeof(char));
    playfair[finally_length]='\0';

    //=====================================================

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            //printf("%c", cipher_table[i][j]);
        }
    }

    for(int i=0; i<strlen(text); i++){
        //printf("%c", changed_text[i]);
    }

    for(int i=0; i<strlen(text); i++){
        if(changed_plafair[i]==' '){
            for(int j=i; j<strlen(text); j++){
                if(j>=0 && i>=0){
                    changed_plafair[j]=changed_plafair[j+1];
                }
            }
        }
    }
    //int* numbers=(int*)calloc(strlen(text), sizeof(int));
    int numbers[1000];
    for(int i=0; i<1000; i++){
        numbers[i]=0;
    }
    numbers[999]='\0';
    for(int i=0;i<finally_length+1;i++){
        if(finally_length!=0){
            changed_text[i]=changed_plafair[i];//===
        }
    }
    int counter=0;

    for(int i=0, g=1; i<finally_length; i+=2, g+=2){
        for(int first_pos_x=0 ; first_pos_x<5; first_pos_x++){
            counter++;
            for(int first_pos_y=0; first_pos_y<5; first_pos_y++){
                if(changed_text[i]==cipher_table[first_pos_x][first_pos_y]){
                    counter++;
                    for(int second_pos_x=0 ; second_pos_x<5; second_pos_x++){
                        for(int second_pos_y=0; second_pos_y<5; second_pos_y++){
                            if (changed_text[g]==cipher_table[second_pos_x][second_pos_y]){
                                numbers[i]=first_pos_x;
                                //printf("%ls", numbers);
                                numbers[i]=first_pos_y;
                                //printf("%ls", numbers);
                                counter++;
                                if(first_pos_x==second_pos_x || first_pos_y==second_pos_y){
                                    if(first_pos_x==second_pos_x){
                                        if(first_pos_y==0){
                                            counter++;
                                            playfair[i]=cipher_table[first_pos_x][last_position]; 
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);                                          
                                        } else if(first_pos_y>0 && first_pos_y<5){
                                            playfair[i]=cipher_table[first_pos_x][first_pos_y-1];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        }
                                        if(second_pos_y==0){
                                            playfair[g]=cipher_table[second_pos_x][last_position];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        } else if(second_pos_y>0 && second_pos_y<5){
                                            playfair[g]=cipher_table[second_pos_x][second_pos_y-1];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        }
                                        counter++;
                                    }
                                    if(first_pos_y==second_pos_y){
                                        if(first_pos_x==0){
                                            playfair[i]=cipher_table[last_position][first_pos_y];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        } else if(first_pos_x>0 && first_pos_x<5){
                                            playfair[i]=cipher_table[first_pos_x-1][first_pos_y];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        }
                                        if(second_pos_x==0){
                                            playfair[g]=cipher_table[last_position][second_pos_y];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        } else if(second_pos_x>0 && second_pos_x<5){
                                            playfair[g]=cipher_table[second_pos_x-1][second_pos_y];
                                            numbers[i]=first_pos_x;
                                            //printf("%ls", numbers);
                                            numbers[i]=first_pos_y;
                                            //printf("%ls", numbers);
                                        }
                                        counter++;
                                    }
                                    counter=0;
                                } else if(first_pos_x!=second_pos_x && first_pos_y!=second_pos_y){
                                    numbers[i]=first_pos_x;
                                    //printf("%ls", numbers);
                                    numbers[i]=first_pos_y;
                                    //printf("%ls", numbers);
                                    playfair[g]=cipher_table[second_pos_x][first_pos_y];
                                    numbers[i]=first_pos_x;
                                    //printf("%ls", numbers);
                                    numbers[i]=first_pos_y;
                                    //printf("%d", numbers[i]);
                                    playfair[i]=cipher_table[first_pos_x][second_pos_y];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<1000; i++){
        counter=numbers[i];
    }
    counter=0;
    //free(numbers);
    free(changed_key);
    free(changed_text);
    changed_key=NULL;
    changed_text=NULL;
    playfair[finally_length]='\0';

    return playfair;
}
