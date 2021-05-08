#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "container.h"

void creating_Wcont(struct container* new_container, enum container_type type, void* entry);
void creating_cont(struct container* new_container, struct container* first, enum container_type type, void* entry);
void free_memory_container(struct container* container);
int removing_first(struct container* first_container, struct container* first, void* entry);
int removing_second(struct container* first_container, struct container* next_container, struct container* first, void* entry);

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if((entry == NULL) || (first != NULL && first->type != type)) return NULL;

    if(first == NULL){
        struct container* new_container = malloc(sizeof(struct container));
        new_container->type = type;

        creating_Wcont(new_container, type, entry);
        new_container->next = NULL;

        //first = new_container;
        return new_container; //return first; ?????
    } else{
        if(type != first->type) return NULL;

        struct container* new_container = malloc(sizeof(struct container));
        new_container->type = type;
        creating_cont(new_container, first, type, entry);

        return new_container;
    }
}

void creating_Wcont(struct container* new_container, enum container_type type, void* entry){
    if(type == ROOM){
        new_container->room = (struct room*)entry;
    }
    if(type == ITEM){
        new_container->item = (struct item*)entry;
    }
    if(type == COMMAND){
        new_container->command = (struct command*)entry;
    }
    if(type == TEXT){
        new_container->text = entry;
    }
}

void creating_cont(struct container* new_container, struct container* first, enum container_type type, void* entry){
    if(type == ROOM){
        new_container->room = (struct room*)entry;
    }
    if(type == ITEM){
        new_container->item = (struct item*)entry;
    }
    if(type == COMMAND){
        new_container->command = (struct command*)entry;
    }
    if(type == TEXT){
        //char* new_text = malloc(strlen(entry) + 1);
        //strcpy(new_text, entry);
        //new_container->text = new_text;

        strcpy(new_container->text, entry);
    }
    while(first->next != NULL){
        first = first->next;
    }
    first->next = new_container;
}

struct container* destroy_containers(struct container* first){
    if(first == NULL) return NULL;

    struct container* first_container = first;
    struct container* next_container;

    do{
        next_container = first->next;
        if(first_container != NULL){
            //free_memory_container(first_container);
            free(first_container);
        }
        first_container = next_container;
    } while(next_container);

    //free_memory_container(first_container);
    free(first_container);

    return NULL;
}

void free_memory_container(struct container* container){
    if(container->type == ROOM){
        container->room = destroy_room(container->room);
    }
    if(container->type == ITEM){
        container->item = destroy_item(container->item);
    }
    if(container->type == COMMAND){
        container->command = destroy_command(container->command);
    }
    if(container->type == TEXT){
        free(container->text);
    }
    free(container);
}

void* get_from_container_by_name(struct container *first, const char *name){
    if((name == NULL) || (first == NULL)) return NULL;

    for(; first != NULL; first = first->next){
        if(first->type == ROOM){
            if((strlen(first->room->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->room->name[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return first->room;
            }
            break;
        }
        if(first->type == ITEM){
            if((strlen(first->item->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->item->name[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return first->item;
            }
            break;
        }
        if(first->type == COMMAND){
            if((strlen(first->command->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->command->name[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return first->command;
            }
            break;
        }
        if(first->type == TEXT){
            if((strlen(first->text) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->text[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return first->text;
            }
            break;
        }
    }

    return NULL;
}

struct container* remove_container(struct container *first, void *entry){
    if(first == NULL) return NULL;
    if(entry == NULL) return first;

    struct container* first_container = first;
    struct container* next_container = first->next;

    int first_checking = removing_first(first_container, first, entry);
    if(first_checking == 1) return next_container;

    for(; next_container != NULL; first_container = next_container, next_container = first_container->next){
        int second_checking = removing_second(first_container, next_container, first, entry);
        if(second_checking == 1) return first;
    }

    return first;
}

int removing_first(struct container* first_container, struct container* first, void* entry){
    if(first_container->room == entry){
        free(first_container);
        return 1;
    }
    if(first_container->item == entry){
        free(first_container);
        return 1;
    }
    if(first_container->command == entry){
        free(first_container);
        return 1;
    }
    if((strcmp(first_container->text, entry) == 0) && (first->type == 3)){
        free(first_container);
        return 1;
    }
    return 0;
}

int removing_second(struct container* first_container, struct container* next_container, struct container* first, void* entry){
    if(next_container->room == entry){
        first_container->next = next_container->next;
        free(next_container);
        return 1;
    }
    if(next_container->item == entry){
        first_container->next = next_container->next;
        free(next_container);
        return 1;
    }
    if(next_container->command == entry){
        first_container->next = next_container->next;
        free(next_container);
        return 1;
    }
    if((strcmp(next_container->text, entry) == 0) && (first->type == 3)){
        first_container->next = next_container->next;
        free(next_container);
        return 1;
    }
    return 0;
}
