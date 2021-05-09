#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

struct parser* create_parser(){
    struct parser* parser = (struct parser*)calloc(1, sizeof(struct parser));

    //creating all parser points form https://kurzy.kpi.fei.tuke.sk/pvjc/2021/problemset.05.adventure.html
    char* parser_name[] = {
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

    char* parser_description[] = {
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
    char* parser_patter[] = {
        "^\\s{0,}((QU|EX)IT|KONIEC)\\s{0,}$", 
        "^\\s{0,}(S|SEVER)\\s{0,}$", 
        "^\\s{0,}(J|JUH)\\s{0,}$", 
        "^\\s{0,}(V|VYCHOD)\\s{0,}$", 
        "^\\s{0,}(Z|ZAPAD)\\s{0,}$", 
        "^\\s{0,}ROZHLIADNI\\sSA\\s{0,}$", 
        "^\\s{0,}(PRIKAZY|HELP|POMOC)\\s{0,}$", 
        "^\\s{0,}VERZIA\\s{0,}$", 
        "^\\s{0,}RESTART\\s{0,}$", 
        "^\\s{0,}(O HRE|ABOUT)\\s{0,}$", 
        "^\\s{0,}VEZMI(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 
        "^\\s{0,}POLOZ(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 
        "^\\s{0,}(INVENTAR|I)\\s{0,}$", 
        "^\\s{0,}POUZI(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 
        "^\\s{0,}PRESKUMAJ(\\s{1,}[a-zA-Z]{1,}){1,}\\s{0,}$", 
        "^\\s{0,}(NAHRAJ|LOAD)\\s{0,}$", 
        "^\\s{0,}(ULOZ|SAVE)\\s{0,}$"
    };

    struct command* new_command;
    int word = 0;
    int size_patter = 17;

    do{
        if(word < size_patter){
            new_command = create_command(parser_name[word], parser_description[word], parser_patter[word], 0);
            parser->commands = create_container(parser->commands, 2, new_command);
            word++;
        } else{
            break;
        }
    } while(word < size_patter);

    return parser;
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
    int word2 = 0;
    int word = 0;
    char* input_buffer = malloc(sizeof(char) * 20);

    for(int j = 0; input[word] == ' '; j++){
        word++;
    }

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

    while(word < strlen(input)){
        if(input[word] == ' '){
            input_buffer[word2] = '\0';
            break;
        }
        if(input[word] != ' '){
            input_buffer[word2] = (char)tolower(input[word]);
            if(word2 <= word) word2++;
        }
        word++;
    }

    return get_from_container_by_name(parser->commands, input_buffer);
}
