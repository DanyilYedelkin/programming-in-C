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
    /*while(1){
        if(fscanf(fp, "%s %d", list[number].name, &list[number].score) != EOF){
            if(number > 10) break;
            number++;
        } else break;
    }*/
    for(number = 0; number < 10; number++){
        if(fscanf(fp, "%s %d", list[number].name, &list[number].score) != EOF) continue;
        else break;
    }
    if(number != 0) qsort(list, (size_t)number, (size_t)sizeof(struct player), cmp);
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
    
    int player_place = 10;
    for(int i = 0; i < *size; i++){
        if(list[i].score == player.score){
            player_place = i;
            break;
        }
    }
    if(player_place == 10){
        if(*size == 10){
            if(list[10 - 1].score > player.score) add = false;
            else if((list[10 - 1].score < player.score) || (list[10 - 1].score == player.score)){
                list[10 - 1] = player;
                qsort(list, (size_t)*size, sizeof(struct player), cmp);
                add = true;
            }
        } else{
            list[*size] = player;
            if(*size > -1 && *size < 10)(*size)++;
            qsort(list, (size_t) *size, sizeof(struct player), cmp);
            add = true;
        }
    } else{
        if (*size < 10) (*size)++;
        for(int i = (*size) - 1; i > player_place; i--){
            list[i] = list[i - 1];
        }
        list[player_place] = player;
        add = true;
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
