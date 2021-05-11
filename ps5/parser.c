#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

struct parser* create_parser(){
    
    //https://ru.wikipedia.org/wiki/Регулярные_выражения
    //https://www.youtube.com/watch?v=bWu8IJ_DasE
    struct parser* created_parser = calloc(1, sizeof(struct parser));
    //created_parser->commands = calloc(17, sizeof(struct parser));

    created_parser->commands = create_container(NULL, COMMAND, create_command("KONIEC", "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", "^\\s{0,}((QU|EX)IT|KONIEC)\\s{0,}$", 3));
    create_container(created_parser->commands, COMMAND, create_command("SEVER", "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(S|SEVER)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("JUH", "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(J|JUH)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("VYCHOD", "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(V|VYCHOD)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("ZAPAD", "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(Z|ZAPAD)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("ROZHLIADNI SA", "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.", "^\\s{0,}ROZHLIADNI\\sSA\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("PRIKAZY", "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.", "^\\s{0,}(PRIKAZY|HELP|POMOC)\\s{0,}$", 3));
    create_container(created_parser->commands, COMMAND, create_command("VERZIA", "Príkaz zobrazí číslo verzie hry, ľubovolný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).", "^\\s{0,}VERZIA\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("RESTART", "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.", "^\\s{0,}RESTART\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "^\\s{0,}(O HRE|ABOUT)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("VEZMI", "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).", "^\\s{0,}VEZMI(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("POLOZ", "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", "^\\s{0,}POLOZ(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("INVENTAR", "Zobrazí obsah hráčovho batohu.", "^\\s{0,}(INVENTAR|I)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("POUZI", "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", "^\\s{0,}POUZI(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("PRESKUMAJ", "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).", "^\\s{0,}PRESKUMAJ(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 1));
    create_container(created_parser->commands, COMMAND, create_command("NAHRAJ", "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", "^\\s{0,}(NAHRAJ|LOAD)\\s{0,}$", 2));
    create_container(created_parser->commands, COMMAND, create_command("ULOZ", "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.", "^\\s{0,}(ULOZ|SAVE)\\s{0,}$", 2));

    created_parser->history = create_container(NULL, COMMAND, create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "^\\s{0,}(O HRE|ABOUT)\\s{0,}$", 2));

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
    if((input == NULL) || (parser == NULL) || (strlen(input) == 0) || (strlen(input) < 1)) return NULL;

    int input_word = 0;
    int word = 0;
    char input_buffer[strlen(input)];

    //first changed: remove old method and add new method
    /*do{
        if(input[0] != ' '){
            while(input_word < strlen(input)){  
                if(input[input_word] == ' ' ){
                    while(input[input_word] == ' '){
                        input_word++;
                    }
                    if(input[input_word] == '\0'){
                        input_buffer[word] = '\0';
                        break;
                    }
                    if(input[input_word] != ' '){
                        input_buffer[word] = ' ';
                        int next_word = word + 1;
                        while(input_word < strlen(input)){
                            if(input[input_word] == ' '){
                                input_buffer[next_word] = '\0';
                                break;
                            }
                            
                            input_buffer[next_word] = (char)tolower(input[input_word]);
                            next_word++;
                            input_word++;
                        }
                        break;
                    }
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
                if(input[input_word] == ' ' ){
                    while(input[input_word] == ' '){
                        input_word++;
                    }
                    if(input[input_word] == '\0'){
                        input_buffer[word] = '\0';
                        break;
                    }
                    if(input[input_word] != ' '){
                        input_buffer[word] = ' ';
                        int next_word = word + 1;
                        while(input_word < strlen(input)){
                            if(input[input_word] == ' '){
                                input_buffer[next_word] = '\0';
                                break;
                            }
                            
                            input_buffer[next_word] = (char)tolower(input[input_word]);
                            next_word++;
                            input_word++;
                        }
                        break;
                    }
                }
                input_buffer[word] = (char)tolower(input[input_word]);
                word++;
                input_word++;
            }
            break;
        }
    } while(input[input_word] == ' ');*/


    if(input[input_word] == ' '){
        for(int i = 0; input[input_word] == ' '; i++, input_word++){}
    }

    while(input_word < strlen(input)){
        if(input[input_word] == ' '){
            break;
        }
        input_buffer[word] = (char)toupper(input[input_word]);
        word++;
        input_word++;
    }
    if(input[input_word] == ' ' && (((char)toupper(input[input_word - 1]) == 'I' && (char)toupper(input[input_word - 2]) == 'N') || (char)toupper(input[input_word - 1]) == 'O')){
        while(input[input_word] == ' '){
            input_word++;
        }
        input_buffer[word] = ' ';
        word++;
        while(input[input_word] != ' '){
            if(input[input_word] == ' '){
                input_buffer[word] = '\0';
                break;
            }
            input_buffer[word] = (char)toupper(input[input_word]);
            word++;
            input_word++;
        }
    } else{
        input_buffer[word] = '\0';
    }
    input_buffer[word] = '\0';

    //return get_from_container_by_name(parser->commands, input_buffer);
    return create_command(input_buffer, " ", "(EXIT)", 1); 
}
