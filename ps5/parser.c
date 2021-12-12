#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"


struct parser* create_parser(){
    struct parser* created_parser = calloc(1, sizeof(struct parser));

    created_parser->commands = create_container(NULL, COMMAND, create_command("KONIEC", "KONIEC", "^\\s{0,}((QU|EX)IT|KONIEC)\\s{0,}$", 3));
    create_container(created_parser->commands, COMMAND, create_command("SEVER", "SEVER", "^\\s{0,}(S|SEVER)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("JUH", "JUH", "^\\s{0,}(J|JUH)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("VYCHOD", "VYCHOD", "^\\s{0,}(V|VYCHOD)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("ZAPAD", "ZAPAD", "^\\s{0,}(Z|ZAPAD)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("ROZHLIADNI SA", "ROZHLIADNI SA", "^\\s{0,}ROZHLIADNI\\sSA\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("PRIKAZY", "PRIKAZY", "^\\s{0,}(PRIKAZY|HELP|POMOC)\\s{0,}$", 3));
    create_container(created_parser->commands, COMMAND, create_command("VERZIA", "VERZIA", "^\\s{0,}VERZIA\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("RESTART", "RESTART", "^\\s{0,}RESTART\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("O HRE", "O HRE", "^\\s{0,}(O HRE|ABOUT)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("VEZMI", "VEZMI", "^\\s{0,}VEZMI(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("POLOZ", "POLOZ", "^\\s{0,}POLOZ(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("INVENTAR", "INVENTAR", "^\\s{0,}(INVENTAR|I)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("POUZI", "POUZI", "^\\s{0,}POUZI(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("PRESKUMAJ", "PRESKUMAJ", "^\\s{0,}PRESKUMAJ(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("NAHRAJ", "NAHRAJ", "^\\s{0,}(NAHRAJ|LOAD)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("ULOZ", "ULOZ", "^\\s{0,}(ULOZ|SAVE)\\s{0,}$", 2));

    created_parser->history = create_container(NULL, COMMAND, create_command("O HRE", "O HRE", "^\\s{0,}(O HRE|ABOUT)\\s{0,}$", 2));

    if (created_parser->history == NULL){
        free(created_parser);
        return NULL;
    }
    return created_parser;
}

struct parser* destroy_parser(struct parser* parser) {
    if(parser == NULL) return NULL;

    parser->commands = destroy_containers(parser->commands);
    parser->history = destroy_containers(parser->history);
    free(parser);

    return NULL;
}

struct command* parse_input(struct parser* parser, char* input){
    if((input == NULL) || (parser == NULL) || (strlen(input) == 0)) return NULL;

    char input_buffer[strlen(input)]; 
    int ch_p = 1; 
    int word = 0; 
    int i_word = 0;

    if(input[i_word] == ' '){
        for(int i = 0; input[i_word] == ' '; i++, i_word++){}
    }

    while(i_word < strlen(input)){ 
        if(input[i_word] != ' ' && ch_p == 1){ 
            input_buffer[word] = (char)tolower(input[i_word]);
            word++;
            i_word++;
            continue; 
        } 
        if(input[i_word] == ' ' && ch_p == 1 && (((char)tolower(input[i_word - 1]) == 'o') || (((char)tolower(input[i_word - 1]) == 'i') && ((char)tolower(input[i_word - 2]) == 'n')))){ 
            ch_p = 2; 
        } 
        if(ch_p == 2 && input[i_word] != ' '){ 
            ch_p = 3; 
            input_buffer[word] = ' '; 
            word++; 
        } 
        if(ch_p == 3 && input[i_word] != ' '){ 
            input_buffer[word] = (char)tolower(input[i_word]); 
            word++;
        }
        i_word++;
    } 
    input_buffer[word] = '\0';

    return get_from_container_by_name(parser->commands, input_buffer); 
}

