#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "room.h"

/*
         _nnnn_                      
        dGGGGMMb     ,"""""""""""""".
       @p~qp~~qMb    | Linux Rules! |
       M|@||@) M|   _;..............'
       @,----.JM| -'
      JS^\__/  qKL
     dZP        qKRb
    dZP          qKKb
   fZP            SMMb
   HZM            MMMM
   FqM            MMMM
 __| ".        |\dS"qML
 |    `.       | `' \Zq
_)      \.___.,|     .'
\____   )MMMMMM|   .'
     `-'       `--' hjm

*/


void creating_room(struct room* new_room, char* name, char* description);

struct room* create_room(char *name, char *description){
    if((name == NULL) || (description == NULL) || (strlen(name) == 0) || (strlen(description) == 0)) return NULL;

    //struct room* new_room = malloc(sizeof(struct room));
    struct room* new_room = calloc(1, sizeof(struct room));
    new_room->name = calloc(strlen(name)+1, sizeof(struct room));
    new_room->description = calloc(strlen(description)+1, sizeof(struct room));
    creating_room(new_room, name, description);

    return new_room;
}

void creating_room(struct room* new_room, char* name, char* description){
    strcpy(new_room->name, name);
    strcpy(new_room->description, description);

    new_room->items = NULL;
    new_room->south = NULL;
    new_room->north = NULL;
    new_room->east = NULL;
    new_room->west = NULL;
}


void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
    if(room == NULL) return;

    room->south = south;
    room->north = north;
    room->west = west;
    room->east = east;
    if(south != NULL) room->south->north = room;
    if(north != NULL) room->north->south = room;
    if(west != NULL) room->west->east = room;
    if(east != NULL) room->east->west = room;
}

void show_room(const struct room* room){
    if(room == NULL) return;

    printf("|Name|---> %s\n|DESCRIPTION|---> %s\n\nAvailable exists:\n", room->name, room->description);
    if (room->south != NULL) printf("South--->%s\n", room->south->name);
    if (room->north != NULL) printf("North--->%s\n", room->north->name);
    if (room->west != NULL) printf("West--->%s\n", room->west->name);
    if (room->east != NULL) printf("East--->%s\n", room->east->name);
    if (room->north == NULL && room->south == NULL && room->east == NULL && room->west == NULL) printf("Nothing\n");
    printf("\nYou see:\n"); 
    if(room->items != NULL){
        struct container* container = room->items;
        //container = room->items;
        while (container != NULL){
	        printf("%s\n", container->item->name);
	        container = container->next;
        }
        //free(container);
        //destroy_containers(container);
    } else printf("Nothing\n");
}


struct room* destroy_room(struct room* room){
    if(room == NULL) return NULL;

    destroy_containers(room->items);
    if(room->name != NULL) free(room->name);
    if(room->description != NULL) free(room->description);
    free(room);

    return NULL;
}

void add_item_to_room(struct room* room, struct item* item){
    if((room == NULL) || (item == NULL)) return;

    room->items = create_container(room->items, ITEM, item);
}

struct item* get_item_from_room(const struct room* room, const char* name){
    if((name == NULL) || (room == NULL)) return NULL;

    return get_from_container_by_name(room->items, name);
}

void delete_item_from_room(struct room* room, struct item* item) {
    if((item == NULL) || (room == NULL)) return;

    //new changing
    struct container* container = room->items;
    if(container->item == item){
        room->items = container->next;
        free(container);
        return;
    }
    while(container->next != NULL){
        if(container->next->item == item){
            container->next = container->next->next;
            free(container);
            return;
        }
        container = container->next;
    }
}
