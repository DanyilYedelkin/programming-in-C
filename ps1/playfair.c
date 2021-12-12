#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playfair.h"
#include <stdbool.h>

char* playfair_encrypt(const char* key, const char* text){
    if(text == NULL || key == NULL){
        return NULL;
    }
    for(int i = 0; i < 2; i++){
        if(key[i] == ' ' && key[++i] == '\0'){
            return NULL;
        }
    }
    for(int proverka=0; key[proverka]!='\0'; proverka++){
        if(key[proverka]!=' ' && !isalpha(key[proverka])){
            return NULL;
        }
    }
    int numberLine=-1;
    char *changed_key = (char*)calloc(strlen(key)+1, sizeof(char));
    strcpy(changed_key, key);

    int length = 0;
    bool ifTrue = true;
    char alphabet[26];
    strcpy(alphabet, ALPHA);
    char cipher_table[5][5];

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cipher_table[i][j]='A';
        }
    }

    for(int i = 0; i < strlen(key); i++){
        if(isalpha(key[i])){
            ifTrue = false;
        }
        changed_key[i] = key[i];
        changed_key[i] = toupper(changed_key[i]);
        if(changed_key[i] == 'W'){
            changed_key[i] = 'V';
        }
        if(key[i+1] == '\0'){
            changed_key[i+1] = '\0';
        }
    }
    if(ifTrue == true){
        free(changed_key);
        return NULL;
    }

    char *changed_text = (char*)calloc(2*strlen(text)+1, sizeof(char));

    for(int i = 0, another = 0; i < strlen(text); i++){
        if(changed_text != NULL){
            changed_text[i+another] = toupper(text[i]);
        }
        if(length > -100){
            length++;
        }
        if(changed_text[i+another] == ' '){
            if(length > -100){
                length--;
                another--;
            }
        } else{
            if(changed_text[i+another] == 'W'){
                changed_text[i+another] = 'V';
            }
            if(length > -100 && another > -100){
                if(((another + i) % 2 == 1) && (changed_text[i+another] != ' ') && (changed_text[i+another] != 'X') && (changed_text[i+another] == changed_text[i - 1 + another])){
                    changed_text[i + another + 1] = changed_text[i + another];
                	changed_text[i + another] = 'X';
                    if(length > -100 && another > -100){
                        length++;
                        if(another > -100){
                            another++;
                        }
					}   
                }
            }
        }
    }

    if(length % 2 == 1){
        changed_text[length] = 'X';
        length++;
    }

    changed_text[length] = '\0';


    for(int i = 0 ; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(numberLine > -10){
                numberLine++;
            }

            if(numberLine < strlen(key)){
                if(numberLine > -10){
                    cipher_table[i][j] = '.';
                }

                for(int alph = 0; alph < 25 ; alph++){
                    if(alphabet[alph] == changed_key[numberLine]){
                        if(alphabet[alph] != 26){
                            alphabet[alph] = '.';
                        }
                        if(cipher_table != NULL){
                            cipher_table[i][j] = changed_key[numberLine];
                        }
                    }
                }
                if(cipher_table[i][j] == '.'){
                    if(j > -1){
                        if(j != 0){
                            j--;
                        } else if(j == 0){
                            if(j != '.'){
                                i--;
                            }
                            j = 4;
                        }
                    }
                }
            }else if(cipher_table[i][j] != 'W'){
                for(int alph = 0; alph < 25 ; alph++){
                    if(alphabet[alph] != '.'){
						if(cipher_table != NULL){
							cipher_table[i][j] = alphabet[alph];
						}
                        if(alphabet[alph] != 25){
                            alphabet[alph] = '.';
                        }
                        break;
                    }
                }
            }
        }
    }

    char* playfair = (char*)calloc(length + length/2, sizeof(char));
    int counter = 0;

    for(int i = 0, g = 1; i < length; i += 2, g += 2){
        for(int first_pos_x = 0; first_pos_x < 5; first_pos_x++){
            counter++;
            for(int first_pos_y = 0; first_pos_y < 5; first_pos_y++){
                if(changed_text[i] == cipher_table[first_pos_x][first_pos_y]){
                    counter++;
                    for(int second_pos_x = 0; second_pos_x < 5; second_pos_x++){
                        for(int second_pos_y = 0; second_pos_y < 5; second_pos_y++){
                            if(changed_text[i+1] == cipher_table[second_pos_x][second_pos_y]){
                                counter++;
                                if(first_pos_x == second_pos_x || first_pos_y == second_pos_y){
                                    if(first_pos_x == second_pos_x){
                                        counter++;
                                        if(first_pos_y == 4){
                                            playfair[i] = cipher_table[first_pos_x][0];
                                        } else if(first_pos_y >= 0 && first_pos_y < 4){
                                            playfair[i] = cipher_table[first_pos_x][first_pos_y+1];
                                        }
                                        counter++;
                                        if(second_pos_y == 4){
                                            playfair[g] = cipher_table[second_pos_x][0];
                                        } else if(second_pos_y >= 0 && second_pos_y < 4){
                                            playfair[g] = cipher_table[second_pos_x][second_pos_y+1];
                                        }
                                        counter++;
                                    }
                                    if(first_pos_y == second_pos_y){
                                        if(first_pos_x == 4){
                                            playfair[i] = cipher_table[0][first_pos_y];
                                        } else if(first_pos_x >= 0 && first_pos_x < 4){
                                            playfair[i] = cipher_table[first_pos_x+1][first_pos_y];
                                        }
                                        counter++;
                                        if(second_pos_x == 4){
                                            playfair[g] = cipher_table[0][second_pos_y];
                                        } else if(second_pos_x >= 0 && second_pos_x < 4){
                                            playfair[g] = cipher_table[second_pos_x+1][second_pos_y];
                                        }
                                        counter++;
                                    }
                                } else if(first_pos_x != second_pos_x && first_pos_y != second_pos_y){
                                    playfair[g] = cipher_table[second_pos_x][first_pos_y];
                                    playfair[i] = cipher_table[first_pos_x][second_pos_y];
                                }
                                counter = 0;

                            }
                        }
                    }
                }
            }
        }
    }

    free(changed_text);
    free(changed_key);
    changed_key = NULL;
    changed_text = NULL;

    int finally_length = length + (length)/2-1;

    playfair[finally_length] = '\0';

    for(int i = 0; i < finally_length; i++){
        if(finally_length >= 0){
            if(i % 3 == 2){
                for(int j = finally_length; j > i; j--){
                    playfair[j] = playfair[j-1];
                }
                playfair[i] = ' ';
            }
        }
    }
    for(int i = 0; playfair[i] != '\0'; i++){
        if(playfair[i+1] == '\0' && playfair[i] == ' '){
            playfair[i] = '\0';
            break;
        }
    }

    return playfair;
}


char* playfair_decrypt(const char* key, const char* text){
    if(key == NULL || text == NULL){
        return NULL;
    }
    for(int proverka = 0; key[proverka] != '\0'; proverka++){
        if(key[proverka] != ' ' && !isalpha(key[proverka])){
            return NULL;
        }
    }
    for(int i = 0; i < strlen(text); i++){
        if(text[i] == 'W'){
            return NULL;
        }
    }
    bool ifTrue = true;

    int numberLine = -1;
    char changed_plafair[strlen(text)];
    strcpy(changed_plafair, text);

    int last_position = 4;
    int finally_length = strlen(text) - (strlen(text) + 1)/3 + 1;

    char *changed_key = (char*)calloc(2*strlen(key) + 1, sizeof(char));


    for(int i = 0; i < strlen(key); i++){
        if(isalpha(key[i])){
            ifTrue = false;
        }
        if(key[i] != ' ' && !isalpha(key[i])){
            free(changed_key);
            return NULL;
        }
        changed_key[i] = key[i];
        changed_key[i] = toupper(changed_key[i]);
        if(changed_key[i] == 'W'){
            changed_key[i] = 'V';
        }
    }
    if(ifTrue){
        free(changed_key);
        return NULL;
    }

    char *changed_text = (char*)calloc(2*strlen(text) + 1, sizeof(char));

    char texts[strlen(text)];
    strcpy(texts, text);
    for(int i = 0; i < strlen(text); i++){
        if(texts[i] == ' '){
            for(int j = i; j < strlen(text); j++){
                texts[j] = texts[j+1];
            }
        }
    }


    char alphabet[27];
    strcpy(alphabet, ALPHA);
    alphabet[26] = '\0';

    char cipher_table[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cipher_table[i][j] = 'A';
        }
    }


    for(int i = 0 ; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(numberLine > -10){
                numberLine++;
            }
            if(numberLine < strlen(key)){
                if(numberLine > -10){
                    cipher_table[i][j] = '.';
                }

                for(int alph = 0; alph < 25; alph++){
                    if(alphabet[alph] == changed_key[numberLine]){
                        if(alphabet[alph] != 25){
                            alphabet[alph] = '.';
                        }
                        if(cipher_table != NULL){
                            cipher_table[i][j] = changed_key[numberLine];
                        }
                    }
                }
                if(cipher_table[i][j] == '.'){
                    if(j > -1){
                        if(j != 0){
                            j--;
                        } else if(j == 0){
                            if(j != '.'){
                                i--;
                            }
                            j = 4;
                        }
                    }
                }
            }else if(cipher_table[i][j] != 'W'){
                for(int alph = 0; alph < 25 ; alph++){
                    if(alphabet[alph] != '.'){
                        if(cipher_table != NULL){
                            cipher_table[i][j] = alphabet[alph];
                        }
                        if(alphabet[alph] != 25){
                            alphabet[alph] = '.';
                        }
                        break;
                    }
                }
            }
        }
    }

    char *playfair = (char*)calloc(2*strlen(text)+1, sizeof(char));
    playfair[finally_length] = '\0';

    strcpy(changed_plafair, text);

    for(int i = 0; i < strlen(text); i++){
        if(changed_plafair[i] == ' '){
            for(int j = i; j < strlen(text); j++){
                if(j >= 0 && i >= 0){
                    changed_plafair[j] = changed_plafair[j+1];
                }
            }
        }
    }


    for(int i = 0; i < finally_length + 1; i++){
        if(finally_length != 0){
            changed_text[i] = changed_plafair[i];
        }
    }

    int counter = 0;

    for(int i = 0, g = 1; i < finally_length; i += 2, g += 2){
        for(int first_pos_x = 0; first_pos_x < 5; first_pos_x++){
            counter++;
            for(int first_pos_y = 0; first_pos_y < 5; first_pos_y++){
                if(changed_text[i] == cipher_table[first_pos_x][first_pos_y]){
                    counter++;
                    for(int second_pos_x = 0; second_pos_x < 5; second_pos_x++){
                        for(int second_pos_y = 0; second_pos_y < 5; second_pos_y++){
                            if (changed_text[g] == cipher_table[second_pos_x][second_pos_y]){
                                counter++;
                                if(first_pos_x == second_pos_x || first_pos_y == second_pos_y){
                                    if(first_pos_x == second_pos_x){
                                        if(first_pos_y == 0){
                                            counter++;
                                            playfair[i] = cipher_table[first_pos_x][last_position];
                                        } else if(first_pos_y > 0 && first_pos_y < 5){
                                            playfair[i] = cipher_table[first_pos_x][first_pos_y-1];
                                        }
                                        if(second_pos_y == 0){
                                            playfair[g] = cipher_table[second_pos_x][last_position];
                                        } else if(second_pos_y > 0 && second_pos_y < 5){
                                            playfair[g] = cipher_table[second_pos_x][second_pos_y-1];
                                        }
                                        counter++;
                                    }
                                    if(first_pos_y == second_pos_y){
                                        if(first_pos_x == 0){
                                            playfair[i] = cipher_table[last_position][first_pos_y];
                                        } else if(first_pos_x > 0 && first_pos_x < 5){
                                            playfair[i] = cipher_table[first_pos_x - 1][first_pos_y];
                                        }
                                        if(second_pos_x == 0){
                                            playfair[g] = cipher_table[last_position][second_pos_y];
                                        } else if(second_pos_x > 0 && second_pos_x < 5){
                                            playfair[g] = cipher_table[second_pos_x-1][second_pos_y];
                                        }
                                        counter++;
                                    }
                                    counter = 0;
                                } else if(first_pos_x != second_pos_x && first_pos_y != second_pos_y){
                                    playfair[g] = cipher_table[second_pos_x][first_pos_y];
                                    playfair[i] = cipher_table[first_pos_x][second_pos_y];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    free(changed_key);
    free(changed_text);
    changed_key = NULL;
    changed_text = NULL;
    playfair[finally_length] = '\0';

    return playfair;
}
