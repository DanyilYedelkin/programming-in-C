#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "backpack.h"

struct backpack* create_backpack(const int capacity){
    //first changed: changed malloc -> calloc
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

bool add_item_to_backpack(struct backpack* backpack, struct item* item){   //=====================================================
    if((item == NULL) || (backpack == NULL)) return false;

    if(backpack->capacity > backpack->size){
        //first changed: remove old method, add new
        /*backpack->items = create_container(backpack->items, ITEM, item);
        backpack->size++;
        return true;*/
        if(item->properties && MOVABLE > 0){
        //struct container* items = backpack->items;
        if(backpack->items != NULL){
            backpack->items = create_container(backpack->items, ITEM, item);
            backpack->size++;
        } else if(backpack->items == NULL){
            create_container(backpack->items, ITEM, item);
            backpack->size++;
        }
        }
    } else return false;

    return true;
}





struct item* get_item_from_backpack(const struct backpack* backpack, char* name){  //=====================================================
    if((name == NULL) || (backpack == NULL)) return NULL;

    return get_from_container_by_name(backpack->items, name);
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if((backpack == NULL) || (item == NULL)) return;

    //first changed: remove old method, add new
    //second changed: remove back
    backpack->items = remove_container(backpack->items, item);
    backpack->size--;

    /*struct container* items = backpack->items;
    if(items->item == item){
        struct container* delete_first = backpack->items;
        backpack->items = backpack->items->next;
        free(delete_first);
        backpack->size--;

        return;
    }
    while((items->next->item != item) && (items->next != NULL)){
        items = items->next;
    }
    if((items->item != item) || (items->next == NULL)){
        return;
    }
    struct container* delete_first = items->next;
    items->next = items->next->next;
    free(delete_first);
    backpack->size--;*/
}
