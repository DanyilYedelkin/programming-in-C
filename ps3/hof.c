#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hof.h"

int cmp(const void *a, const void *b);

int load(struct player list[]){
    FILE *fp = fopen(HOF_FILE, "r");
    if(fp == NULL){
        fclose(fp); 
        return -1;
    }
    
    int number = 0;
    while(fscanf(fp, "%s %d", list[number].name, &list[number].score) != EOF){
        if(number > 10) break;
        number++;
    }
    qsort((void*)list, (size_t)number, (size_t)sizeof(struct player), cmp);
    fclose(fp);
    return number;
}

/*
manager 1000
manager 900
manager 800
manager 700
manager 600
manager 500
manager 400
manager 300
manager 200
manager 100
*/

bool save(const struct player list[], const int size){
    FILE *fp = fopen(HOF_FILE, "w");
    if(fp == NULL){
        fclose(fp);
        return false;
    }
    for(int i = 0; i < size; i++){
        fprintf(fp, "%s %d", list[i].name, list[i].score);
        if((i + 1) == size) break;
        fprintf(fp, "\n");
    }
    fclose (fp);
    return true;
}

bool add_player(struct player list[], int* size, const struct player player){
    if(*size < 0 || *size > 10) return false;
    bool add = false;
    
    if(*size == 0){
        list[*size] = player;
        (*size)++;
        add = true;
        return add;
    }

    for(int i = 0; i < *size; i++){
        if((i + 1) > *size){
            list[i].score = player.score;
            strcpy(list[i].name, player.name);
            add = true;
            break;
        }
        if(player.score > list[0].score){
            if (*size < 10) (*size)++;
            for(int j = (*size - 1); j > i; j--){
                list[j] = list[j - 1];
            }
            list[i] = player;
            add = true;
            break;
        }
        //if(player.score < list[*size].score) break;
        if(player.score == list[i].score){
            if(i + 1 == 10){
                list[i].score = player.score;
                strcpy(list[i].name, player.name);
                add = true;
                break;
            }
            if (*size < 10) (*size)++;
            for(int j = (*size - 1); j > i; j--){
                list[j] = list[j - 1];
            }
            list[i] = player;
            add = true;
            break;
        }
    }
    
    return add;
}
//https://ru.wikibooks.org/wiki/Язык_Си_в_примерах/Сортировка
int cmp(const void *a, const void *b){
    if(((struct player*)a)->score == ((struct player*)b)->score){
        return strcmp(((struct player*)a)->name, ((struct player*)b)->name);
    } else{
        return ((struct player*)b)->score - ((struct player*)a)->score;
    }
}
