#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

struct parser* create_parser(){
    //first changed: add all functions and methods for create_parser()
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
        "^\\s*((QU|EX)IT|KONIEC)\\s*$", 
        "^\\s*(S|SEVER)\\s*$", 
        "^\\s*(J|JUH)\\s*$", 
        "^\\s*(V|VYCHOD)\\s*$", 
        "^\\s*(Z|ZAPAD)\\s*$", 
        "^\\s*ROZHLIADNI\\sSA\\s*$", 
        "^\\s*(PRIKAZY|HELP|POMOC)\\s*$", 
        "^\\s*VERZIA\\s*$", 
        "^\\s*RESTART\\s*$", 
        "^\\s*(O HRE|ABOUT)\\s*$", 
        "^\\s*VEZMI(\\s+[a-zA-Z]+)+\\s*$", 
        "^\\s*POLOZ(\\s+[a-zA-Z]+)+\\s*$", 
        "^\\s*(INVENTAR|I)\\s*$", 
        "^\\s*POUZI(\\s+[a-zA-Z]+)+\\s*$", 
        "^\\s*PRESKUMAJ(\\s+[a-zA-Z]+)+\\s*$", 
        "^\\s*(NAHRAJ|LOAD)\\s*$", 
        "^\\s*(ULOZ|SAVE)\\s*$"
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
