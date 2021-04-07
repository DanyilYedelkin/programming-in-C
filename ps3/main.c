#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k.h"
#include "ui.h"
#include "hof.h"


int main()
{
    struct player *list = malloc(sizeof(struct player) * 10);
    struct player *player1 = malloc(sizeof(player1)*30);
    player1->score = 0;
    char *name = "John";
    strcpy(player1->name, name);
    int size_fp = load(list);

    for (int i = 0; i < size_fp; i++){
        printf("%s%s%d\n", list[i].name, DELIMITER, list[i].score);
    }

    struct game game = {
            .board = {
                    {'A', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' '},
                    {'A', ' ', ' ', 'A'}
            },
            .score = 0
    };

    render(game);
    while(1){
        int step = getchar();
        switch(step){
            case 'w':{
                if (update(&game, -1, 0)) add_random_tile(&game);
                render(game);
                break;
            }
            case 'd':{
                if (update(&game, 0, 1)) add_random_tile(&game);
                render(game);
                break;
            }
            case 's':{
                if (update(&game, 1, 0)) add_random_tile(&game);
                render(game);
                break;
            }
            case 'a':{
                if (update(&game, 0, -1)) add_random_tile(&game);
                render(game);
                break;
            }
            case 'q':{
                add_player(list, &size_fp, *player1);
                save(list, size_fp);
                free(list);
                free(player1);
                return 0;
            }
            default:
                break;
        }
    }

    return 0;
}
