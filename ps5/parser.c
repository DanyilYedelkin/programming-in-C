#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

struct parser* create_parser(){
    
    return NULL;
}

struct parser* destroy_parser(struct parser* parser) {
    if(parser == NULL) return NULL;

    parser->commands = destroy_containers(parser->commands);
    parser->history = destroy_containers(parser->history);
    free(parser);

    return NULL;
}

struct command* parse_input(struct parser* parser, char* input){
    if((input == NULL) || (parser == NULL)) return NULL;

    int input_word = 0;
    int word = 0;
    char* input_buffer = malloc(sizeof(char) * 20);

    do{
        if(input[0] != ' '){
            while(input_word < strlen(input)){
                if(input[input_word] == ' '){
                    input_buffer[word] = '\0';
                    break;
                }
                input_buffer[word] = (char)tolower(input[input_word]);
                word++;
                input_word++;
            }
            break;
        }
        if(input[input_word] == ' '){
            input_word++;
        }
        if(input[input_word] != ' '){
            while(input_word < strlen(input)){
                if(input[input_word] == ' '){
                    input_buffer[word] = '\0';
                    break;
                }
                input_buffer[word] = (char)tolower(input[input_word]);
                word++;
                input_word++;
            }
            break;
        }
    } while(input[input_word] == ' ');

    return get_from_container_by_name(parser->commands, input_buffer);
}
