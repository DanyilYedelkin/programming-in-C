#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "world.h"

struct game* create_game(){
    struct game* created_game = calloc(1, sizeof(struct game));

    created_game->state = PLAYING;
    created_game->parser = create_parser();
    created_game->world = create_world();
    created_game->current_room = created_game->world->room;
    created_game->backpack = create_backpack(12);

    return created_game;
}

struct game* destroy_game(struct game* game){
    if(game == NULL) return NULL;

    if (game->backpack != NULL) destroy_backpack(game->backpack);
    if (game->parser != NULL) destroy_parser(game->parser);
    game->current_room = NULL;
    if (game->world != NULL) destroy_containers(game->world);
    free(game);
    
    return NULL;
}

void play_game(struct game* game){
    if(game == NULL) return;

    struct command* input_command;
    char* input_buffer = malloc(sizeof(char) * INPUT_BUFFER_SIZE);

    do{
        if((game->state != SOLVED) && (game->state != GAMEOVER)){
            fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
            input_command = parse_input(game->parser, input_buffer);
            execute_command(game, input_command);
            if(game->state == RESTART){
                printf("Restarted the game :D\n");
                game = destroy_game(game);
                game = create_game();
            }
        }
        if(game->state == RESTART){
            printf("Restarted the game :D\n");
            game = destroy_game(game);
            game = create_game();
        }
        if(game->state == SOLVED){
            printf("Congratulations! You're win :D\n");
        } else if(game->state == GAMEOVER){
            printf("Gameover! Try in another :D\n");
        }
    } while((game->state != SOLVED) || (game->state != GAMEOVER));
}

void execute_command(struct game* game, struct command* command){
    if((command == NULL) || (game == NULL)) return;

    if(strcmp(command->name, "KONIEC") == 0){
        game->state = GAMEOVER;  
        printf("Gameover\n");
    } else if(strcmp(command->name, "SEVER") == 0){
        if(game->current_room->north == NULL){
            printf("Sorry, but you can't find the north\n");
        } else{
            game->current_room = game->current_room->north;
            printf("Okey, now you are in the north\n");
        }
    } else if(strcmp(command->name, "JUH") == 0){
        if(game->current_room->south == NULL){
            printf("Sorry, but you can't find the south\n");
        } else{
            game->current_room = game->current_room->south;
            printf("Okey, now you are in the south\n");

        }
    } else if(strcmp(command->name, "VYCHOD") == 0){
        if(game->current_room->east == NULL){
            printf("Sorry, but you can't find the east\n");
        } else{
            game->current_room = game->current_room->east;
            printf("Okey, now you are in the east\n");
        }
    } else if(strcmp(command->name, "ZAPAD") == 0){
        if(game->current_room->west == NULL){
            printf("Sorry, but you can't find the west\n");
        } else{
            game->current_room = game->current_room->west;
            printf("Okey, now you are in the west\n");
        }
    } else if(strcmp(command->name, "ROZHLIADNI SA") == 0){
        show_room(game->current_room);
    } else if(strcmp(command->name, "PRIKAZY") == 0){
        struct container* commands = game->parser->commands;
        for(int i = 0; commands != NULL; i++){
            printf("%s  -->  %s\n", commands->command->name, commands->command->description);
        }
        destroy_containers(commands);
    } else if(strcmp(command->name, "VERZIA") == 0){
        printf("|=====================|\n");
        printf("|      build 0.1      |\n");
        printf("|     Demo Verzia     |\n");
        printf("|                     |\n");
        printf("|   Zelda: Breath of  |\n");
        printf("|      the Wild       |\n");
        printf("|=====================|\n");

    } else */if(strcmp(command->name, "RESTART") == 0){
        printf("Restart the game :D\n");
        game->state = RESTART;
    } else if(strcmp(command->name, "O HRE") == 0){
        printf("STEP INTO A WORLD OF ADVENTURE\n\n");
        printf("Forget everything you know about The Legend of Zelda games.\n");
        printf("Step into a world of discovery, exploration, and adventure in The\n");
        printf("Legend of Zelda: Breath of the Wild, a boundary-breaking new\n");
        printf("game in the acclaimed series. Travel across vast fields, through\n");
        printf("forests, and to mountain peaks as you discover what has become\n");
        printf("of the kingdom of Hyrule in this stunning Open-Air Adventure. Now\n");
        printf("on Nintendo Switch, your journey is freer and more open than ever.\n");
        printf("Take your system anywhere, and adventure as Link any way you like.\n");
    } else if(strcmp(command->name, "VEZMI") == 0){
        add_item_to_backpack(game->backpack, NULL);
    } else if(strcmp(command->name, "POLOZ") == 0){
        add_item_to_room(game->current_room, NULL);
        delete_item_from_backpack(game->backpack, NULL);
    } else if(strcmp(command->name, "INVENTAR") == 0){
        if(game->backpack->items != NULL){
            struct container* inventark = game->backpack->items;
            for(int i = 0; game->backpack->items != NULL; i++, game->backpack->items = game->backpack->items->next){
                printf(" %s\n", game->backpack->items->item->name);
            }
        } else{
            printf("Your backpack is empty :D\n");
        }
    } else if(strcmp(command->name, "PRESKUMAJ") == 0){
        printf("%s\n", game->backpack->items->item->description);
    } else if(strcmp(command->name, "NAHRAJ") == 0){
        FILE *fp = fopen("game_saves.txt", "r");
        if(fp == NULL){
            printf("You haven't any saves\n");
        } else{
            char input_buffer[INPUT_BUFFER_SIZE];
            if(fp != NULL){
                while(1){
                    if(fscanf(fp, "%s", input_buffer) != EOF){
                        struct command* input_command = parse_input(game->parser, input_buffer);
                        execute_command(game, input_command);
                    } else{
                        break;
                    }
                }
            }
        }
       fclose(fp);
    } else if(strcmp(command->name, "ULOZ") == 0){
        if(game->parser->history != NULL){
            FILE *fp = fopen("game_saves.txt", "w");
            printf("Saving... Wait for a while, please\n");
            struct container* history = game->parser->history;
            for(int i = 0; history != NULL; i++, history = history->next){
                fprintf(fp, "%s\n", history->text);
            }
            printf("Saving is completed! :D\n");
            fclose(fp);
        } else{
            printf("Sorry, but nothing to save\n");
        }
        
    }
}
