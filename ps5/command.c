#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command.h"

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    if((name == NULL) || (description == NULL)) return NULL;

    struct command* new_command = malloc(sizeof(struct command));
    //new_command->groups = (char**)malloc(sizeof(char*) * nmatch);
    new_command->name = malloc(strlen(name)+1);
    strcpy(new_command->name, name);
    new_command->description = malloc(strlen(description)+1);
    strcpy(new_command->description, description);

    new_command->nmatch = nmatch;

    //https://man7.org/linux/man-pages/man3/regex.3.html
    if(pattern != NULL){
        regcomp(&(new_command->preg), pattern, REG_ICASE | REG_EXTENDED);
    }

    return new_command;
}

struct command* destroy_command(struct command* command){
    if(command == NULL) return NULL;

    //for(int i = 0; i < command->nmatch; i++){
        //free(command->groups[i]);
        //command->groups[i] = NULL;
    //}      // LOOK AT THIS!!!!!!!!!!!!!!!!!!!
    
    free(command->groups);
    free(command->name);
    free(command->description);
    regfree(&(command->preg));
    free(command);

    return NULL;
}
