#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command.h"

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


struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    if((name == NULL) || (description == NULL) || (strlen(name) <= 0) || (strlen(description) <= 0)) return NULL;

    //first changed: change malloc -> calloc
    //struct command* new_command = malloc(sizeof(struct command));
    struct command* new_command = calloc(1, sizeof(struct command));

    new_command->name = malloc(strlen(name)+1);
    strcpy(new_command->name, name);
    new_command->description = malloc(strlen(description)+1);
    strcpy(new_command->description, description);

    new_command->nmatch = nmatch;

    //https://man7.org/linux/man-pages/man3/regex.3.html
    //first changed: delete function and create a new
    /*if(pattern != NULL){
        regcomp(&(new_command->preg), pattern, REG_ICASE | REG_EXTENDED);
    }*/
    //https://man7.org/linux/man-pages/man3/regex.3.html
    if(pattern != NULL){
        if(regcomp(&(new_command->preg), pattern, REG_ICASE | REG_EXTENDED) != 0){
            free(new_command);
            return NULL;
        }
    }

    return new_command;
}

struct command* destroy_command(struct command* command){
    if(command == NULL) return NULL;

    free(command->name);
    free(command->description);
    regfree(&(command->preg));
    free(command);

    return NULL;
}
