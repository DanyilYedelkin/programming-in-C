#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main()
{
    struct player *list = malloc(sizeof(struct player) * 10);
    int hof_size = load(list);

    struct player *player1 = malloc(sizeof(player1));
    player1->score = 300;
    char *name = "John3";
    strcpy(player1->name, name);

    add_player(list, &hof_size, *player1);
    save(list, hof_size);

    /*struct player list[10];

    struct player *list = malloc(sizeof(struct player) * 10);
    int size = load(list);
    struct player player = {
        .name = "John",
        .score = 100
    };

    add_player(list, &size, player);
    save(list, size);*/

    for(int i = 0; i < hof_size; i++){
        printf("%s\t%d\n", list[i].name, list[i].score);
    }

    return 0;
}
