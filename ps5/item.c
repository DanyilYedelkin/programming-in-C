#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

void creating(struct item* new_item, char* name, char* description, unsigned int properties);
void free_memory_item(struct item* item);

struct item* create_item(char* name, char* description, unsigned int properties){
    if((name == NULL) || (description == NULL)) return NULL;

    struct item* new_item = malloc(sizeof(struct item));
    new_item->name = calloc(strlen(name)+1, sizeof(struct item));
    new_item->description = calloc(strlen(description)+1, sizeof(struct item));
    creating(new_item, name, description, properties);

    return new_item;
}

void creating(struct item* new_item, char* name, char* description, unsigned int properties){
    strcpy(new_item->name, name);
    strcpy(new_item->description, description);
    new_item->properties = properties;
}

struct item* destroy_item(struct item* item){
    if(item == NULL) return NULL;

    free_memory_item(item);

    return NULL;
}

void free_memory_item(struct item* item){
    free(item->name);
    free(item->description);
    free(item);
}
