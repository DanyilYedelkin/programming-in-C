#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

struct parser* create_parser(){
    struct parser* created_parser = calloc(1, sizeof(struct parser));

    //creating all parser points form https://kurzy.kpi.fei.tuke.sk/pvjc/2021/problemset.05.adventure.html
    char* parser_name[] ={
        "KONIEC", 
        "SEVER", 
        "JUH", 
        "VYCHOD", 
        "ZAPAD", 
        "ROZHLIADNI SA", 
        "PRIKAZY", 
        "VERZIA", 
        "RESTART", 
        "O HRE", 
        "VEZMI", 
        "POLOZ", 
        "INVENTAR", 
        "POUZI", 
        "PRESKUMAJ", 
        "NAHRAJ", 
        "ULOZ"
    };

    char* parser_description[] ={
        "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", 
        "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.", 
        "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.", 
        "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", 
        "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", 
        "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.", 
        "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.", 
        "Príkaz zobrazí číslo verzie hry, ľubovolný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).", 
        "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.", 
        "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", 
        "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).", 
        "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", 
        "Zobrazí obsah hráčovho batohu.", 
        "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", 
        "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).", 
        "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", 
        "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru."
    };

    //https://ru.wikipedia.org/wiki/Регулярные_выражения
    //https://www.youtube.com/watch?v=bWu8IJ_DasE
    char* parser_patter[] ={
        "\\s*[kK][oO][nN][iI][eE][cC]\\s*", 
        "(\\s*[sS][eE][vV][eE][rR]\\s*)", 
        "\\s*[jJ][uU][hH]]\\s*", 
        "\\s*[vV][yY][cC][hH][oO][dD]\\s*", 
        "\\s*[zZ][aA][pP][aA][dD]\\s*", 
        "\\s*[rR][oO][zZ][hH][lL][iI][aA][dD][nN][iI][ ][sS][aA]\\s*", 
        "\\s*[pP][rR][iI][kK][aA][zZ][yY]\\s*", 
        "\\s*[vV][eE][rR][zZ][iI][aA]\\s*", 
        "\\s*[rR][eE][sS][tT][aA][rR][tT]\\s*", 
        "\\s*[oO][ ][hH][rR][eE]\\s*", 
        "\\s*[vV][eE][zZ][mM][iI]\\s*", 
        "\\s*[pP][oO][lL][oO][zZ]\\s*", 
        "\\s*[iI][nN][vV][eE][nN][tT][aA][rR]\\s*", 
        "\\s*[pP][oO][uU][zZ][iI]\\s*", 
        "\\s*[pP][rR][eE][sS][kK][uU][mM][aA][jJ]\\s*", 
        "\\s*[nN][aA][hH][rR][aA][jJ]\\s*", 
        "\\s*[uU][lL][oO][zZ]\\s*"
    };

    //struct command* new_command;
    int word = 0;
    int size_patter = 17;

    /*do{
        if(word < size_patter){
            new_command = create_command(parser_name[word], parser_description[word], parser_patter[word], 0);
            parser->commands = create_container(parser->commands, 2, new_command);
            word++;
        } else{
            break;
        }
    } while(word < size_patter);*/
    while(word < size_patter){
        //created_parser->commands = create_container(created_parser->commands, COMMAND, create_command(parser_name[word], parser_description[word], parser_patter[word], 1));
        create_container(created_parser->commands, COMMAND, create_command(parser_name[word], parser_description[word], parser_patter[word], 1));
        word++;
    }

    return created_parser;

    //parser->history = create_container(NULL, COMMAND, create_command("Start", "Start game", "(Start)", 0));
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

    //int input_word = 0;
    /*int word2 = 0;
    int word = 0;
    char* input_buffer = malloc(sizeof(char) * 20);

    for(int j = 0; input[word] == ' '; j++){
        word++;
    }*/

    //first changed: remove old method and add new method
    /*do{
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
    } while(input[input_word] == ' ');*/

    /*while(word < strlen(input)){
        if(input[word] == ' '){
            input_buffer[word2] = '\0';
            break;
        }
        if(input[word] != ' '){
            input_buffer[word2] = (char)tolower(input[word]);
            if(word2 <= word) word2++;
        }
        word++;
    }*/

    for(int i = 0; parser->commands->command != NULL && parser->commands != NULL; i++, parser->commands = parser->commands->next){
        if(regexec(&parser->commands->command->preg, input, 0, NULL, REG_ICASE) != REG_NOMATCH){
            return parser->commands->command;
        }
    }
    return NULL;
    //return get_from_container_by_name(parser->commands, input_buffer);
}
