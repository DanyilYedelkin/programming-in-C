#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "backpack.h"

struct backpack* create_backpack(const int capacity){
    //struct backpack* new_backpack = malloc(sizeof(struct backpack));
    struct backpack* new_backpack = calloc(1, sizeof(struct backpack));
    new_backpack->capacity = capacity;
    new_backpack->items = NULL;
    new_backpack->size = 0;
    
    return new_backpack;
}

struct backpack* destroy_backpack(struct backpack* backpack){
    if(backpack == NULL) return NULL;
    free(backpack);

    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item){
    if((item == NULL) || (backpack == NULL)) return false;

    if(backpack->capacity > backpack->size){
        backpack->items = create_container(backpack->items, ITEM, item);
        backpack->size++;
        return true;
    } else return false;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
    if((name == NULL) || (backpack == NULL)) return NULL;

    return get_from_container_by_name(backpack->items, name);
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if((backpack == NULL) || (item == NULL)) return;

    backpack->items = remove_container(backpack->items, item);
    backpack->size--;
}
