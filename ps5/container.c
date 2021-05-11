#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "container.h"

void creating_Wcont(struct container* new_container, enum container_type type, void* entry);
void creating_cont(struct container* new_container, enum container_type type, void* entry);
void free_memory_container(struct container* container);
int strcmpBIG(char const *first_name, char const *second_name);
int removing_first(struct container* first_container, struct container* first, void* entry);
int removing_second(struct container* first_container, struct container* next_container, struct container* first, void* entry);

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if((entry == NULL) || (first != NULL && first->type != type)) return NULL;

    if(first == NULL){
        //first changed: malloc -> calloc
        //struct container* new_container = malloc(sizeof(struct container));
        struct container* new_container = calloc(1, sizeof(struct container));
        new_container->type = type;

        creating_Wcont(new_container, type, entry);

        //first changed: add the new container to the first container
        return new_container;
        //first = new_container;
       // return first;
    } else{
        if(type != first->type) return NULL;

        //struct container* check = first;
        struct container* new_container = first;
        for(int i = 0; new_container->next != NULL; i++, new_container = new_container->next){}
        new_container->next = calloc(1, sizeof(struct container));
        new_container->next->type = type;
        creating_cont(new_container->next, type, entry);
        //creating_Wcont(new_container, type, entry);
        /*while(check->next != NULL){
            check = check->next;
        }
        check->next = new_container;
        new_container->next = NULL;*/

        return new_container->next;
    }
}

void creating_Wcont(struct container* new_container, enum container_type type, void* entry){
    if(type == ROOM){
        new_container->room = entry;
    }
    if(type == ITEM){
        new_container->item = entry;
    }
    if(type == COMMAND){
        new_container->command = entry;
    }
    if(type == TEXT){
        new_container->text = entry;
    }
}

void creating_cont(struct container* new_container, enum container_type type, void* entry){
    if(type == ROOM){
        new_container->room = entry;
    }
    if(type == ITEM){
        new_container->item = entry;
    }
    if(type == COMMAND){
        new_container->command = entry;
    }
    if(type == TEXT){
        new_container->text = entry;
    }
}

struct container* destroy_containers(struct container* first){
    if(first == NULL) return NULL;

    free_memory_container(first);

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
    if((name == NULL) || (first == NULL) || (strlen(name) == 0)) return NULL;

    //first changed: create a new container "item" and change first -> "item"
    //back to the first method
    /*struct container* item = first;
    for(; item != NULL; item = item->next){
        if(first->type == ROOM){
            if((strlen(item->room->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->room->name[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return item->room;
            }
            break;
        }
        if(first->type == ITEM){
            if((strlen(item->item->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->item->name[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return item->item;
            }
            break;
        }
        if(first->type == COMMAND){
            if((strlen(item->command->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->command->name[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return item->command;
            }
            break;
        }
        if(first->type == TEXT){
            if((strlen(item->text) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->text[i]) - tolower(name[i]);
                    if(difference != 0) break;
                }
                if(difference == 0) return item->text;
            }
            break;
        }
    }*/

    //second changed: try another method 
    /*if(first->type == ROOM){
        for(int i = 0; first != NULL || first->room != NULL; i++){
            if((strlen(first->room->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->room->name[i]) - tolower(name[i]);
                    if(difference != 0){
                        i = 100000000;
                    }
                }
                if(difference == 0) return first;
                else first = first->next;
            }
        }
    }
    if(first->type == ITEM){
        for(int i = 0; first != NULL || first->item != NULL; i++){
            if((strlen(first->item->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->item->name[i]) - tolower(name[i]);
                    if(difference != 0){
                        i = 10000000;
                    }
                }
                if(difference == 0) return first;
                else first = first->next;
            }
        }
    }
    if(first->type == COMMAND){
        for(int i = 0; first != NULL || first->command != NULL; i++){
            if((strlen(first->command->name) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->command->name[i]) - tolower(name[i]);
                    if(difference != 0){
                        i = 100000000;
                    }
                }
                if(difference == 0) return first;
                else first = first->next;
            }
        }
    }
    if(first->type == TEXT){
        for(int i = 0; first != NULL || first->text != NULL; i++){
            if((strlen(first->text) == strlen(name))){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(first->text[i]) - tolower(name[i]);
                    if(difference != 0){
                        i = 100000000;
                    }
                }
                if(difference == 0) return first;
                else first = first->next;
            }
        }
    }*/

    //third changed: try another method
    //back to the first method

    /*if(first->type == ROOM){
        for(int i = 0; first != NULL; i++, first = first->next){
            if(strlen(name) == strlen(first->room->name)){
                if(strcmpBIG(name, first->room->name) == 0) return first->room;
            }
        }
    } else if(first->type == ITEM){
        for(int i = 0; first != NULL; i++, first = first->next){
            if(strlen(name) == strlen(first->item->name)){
                if(strcmpBIG(name, first->item->name) == 0) return first->item;
            }
        }
    } else if(first->type == COMMAND){
        for(int i = 0; first != NULL; i++, first = first->next){
            if(strlen(name) == strlen(first->command->name)){
                if(strcmpBIG(name, first->command->name) == 0) return first->command;
            }
        }
    } else if(first->type == TEXT){
        for(int i = 0; first != NULL; i++, first = first->next){
            if(strlen(name) == strlen(first->text)){
                if(strcmpBIG(name, first->text) == 0) return first->text;
            }
        }
    }*/

    //fourth method:
    /*struct container* item = first;
    for(; item != NULL; item = item->next){
        if(first->type == ROOM){
            if(item->room != NULL && item->room->name != NULL){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->room->name[i]) - tolower(name[i]);
                    if(difference != 0) i = 100000000;
                }
                if(difference == 0) return item->room;
            }
            break;
        }
        if(first->type == ITEM){
            if(item->item != NULL && item->item->name != NULL){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->item->name[i]) - tolower(name[i]);
                    if(difference != 0) i = 100000000;
                }
                if(difference == 0) return item->item;
            }
            break;
        }
        if(first->type == COMMAND){
            if(item->command != NULL && item->command->name != NULL){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->command->name[i]) - tolower(name[i]);
                    if(difference != 0) i = 100000000;
                }
                if(difference == 0) return item->command;
            }
            break;
        }
        if(first->type == TEXT){
            if(item->text != NULL){
                int difference = 0;
                for(int i = 0; i < strlen(name); i++){
                    difference = tolower(item->text[i]) - tolower(name[i]);
                    if(difference != 0) i = 100000000;
                }
                if(difference == 0) return item->text;
            }
            break;
        }
    }*/



    if(first->type == ROOM){
        for(int i = 0; first != NULL && first->room != NULL; i++, first = first->next){
            if(strcmpBIG(name, first->room->name) == 1) return first->room;
        }
    } else if(first->type == ITEM){
        for(int i = 0; first != NULL && first->item != NULL; i++, first = first->next){
            if(strcmpBIG(name, first->item->name) == 1) return first->item;
        }
    } else if(first->type == COMMAND){
        for(int i = 0; first != NULL && first->command != NULL; i++, first = first->next){
            if(strcmpBIG(name, first->command->name) == 1) return first->command;
        }
    } else if(first->type == TEXT){
        for(int i = 0; first != NULL && first->text != NULL; i++, first = first->next){
            if(strcmpBIG(name, first->text) == 1) return first->text;
        }
    }
    

    return NULL;
}

int strcmpBIG(char const *first_name, char const *second_name){
    if((first_name == NULL) || (second_name == NULL)) return 0;
    int difference = 0;
    for(int i = 0; i < strlen(first_name); i++){
        difference = tolower(first_name[i]) - tolower(second_name[i]);
        if(difference != 0) return 0;
    }
    return 1;
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
    if(strcmp(first_container->text, entry) == 0){
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
    if(strcmp(next_container->text, entry) == 0){
        first_container->next = next_container->next;
        free(next_container);
        return 1;
    }
    return 0;
}
