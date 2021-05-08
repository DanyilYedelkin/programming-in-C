#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "backpack.h"
#include "command.h"
#include "container.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"

int main() {
    /*// Item test 
    struct item* item = create_item("sword", "lox", 1);
    struct item* item2 = create_item("sword", "lox", 1);
    struct room* home = create_room("home", "Nachadzas sa v chyzi svarneho suhaja. Na vychode sa nachadzaju dvere veduce z chyze von.");
    struct room* garden = create_room("garden", "Stojis pred chyzou a rozoznavas zahradku, ktora je znacne neudrziavana. este ze husty lesik na severe v porovnani so zahradkou nicim nevynika.");
    struct room* bathroom = create_room("bathroom", "Stojis pred chyzou a rozoznavas zahradku, ktora je znacne neudrziavana. este ze husty lesik na severe v porovnani so zahradkou nicim nevynika.");
    struct backpack *backpack = create_backpack(5);
    add_item_to_room(home, item);
    add_item_to_room(garden, item2);
  
  

    add_item_to_backpack(backpack, item);
    printf("\n%d\n", backpack->size);
    get_item_from_backpack(backpack, "sword");
    printf("get_item_from_backpack - > %d\n", backpack->size);
    delete_item_from_backpack(backpack, item);
    printf("%d\n", backpack->size);
    // set exits
    set_exits_from_room(home, NULL, NULL, garden, bathroom);
    set_exits_from_room(bathroom, NULL, NULL, home, NULL);
  
    // show room
    show_room(home);
    
    //Nachadzas sa v chyzi svarneho suhaja. Na vychode sa nachadzaju dvere veduce z chyze von.
    // Mozne vychody z miesnosti:
       //vychod
    

    // destroy rooms
    home = destroy_room(home);
    garden = destroy_room(garden);
    bathroom = destroy_room(bathroom);
    item = destroy_item(item);
    item2 = destroy_item(item2);
    backpack = destroy_backpack(backpack);*/


    /*struct item *key = create_item("key", "just key", 1);
    struct backpack *backpack = create_backpack(5);
    add_item_to_backpack(backpack, key);
    printf("%d ", backpack->size);
    if(get_item_from_backpack(backpack, key->name) == NULL) 
        printf("yes ");
    delete_item_from_backpack(backpack, key);
    printf("%d\n", backpack->size);*/





    struct container* create_world();
    struct container* add_room_to_world(struct container* world, struct room* room);
    struct container* destroy_world(struct container* world);
    struct room* get_room(struct container* world, char* name);
    struct backpack* create_backpack(const int capacity);
    struct backpack* destroy_backpack(struct backpack* backpack);
    bool add_item_to_backpack(struct backpack* backpack, struct item* item);
    void delete_item_from_backpack(struct backpack* backpack, struct item* item);
    struct item* get_item_from_backpack(const struct backpack* backpack, char* name);
    struct container* create_container(struct container* first, enum container_type type, void* entry);
    struct container* destroy_containers(struct container* first);
    void* get_from_container_by_name(struct container *first, const char *name);
    struct container* remove_container(struct container *first, void *entry);
    struct command* create_command(char* name, char* description, char* pattern, size_t nmatch);
    struct command* destroy_command(struct command* command);
    void play_game(struct game* game);
    struct game* create_game();
    struct game* destroy_game(struct game* game);
    void execute_command(struct game* game, struct command* command);
    struct item* create_item(char* name, char* description, unsigned int properties);
    struct item* destroy_item(struct item* item);
    struct parser* create_parser();
    struct parser* destroy_parser(struct parser* parser);
    struct command* parse_input(struct parser* parser, char* input);
    struct room* create_room(char *name, char *description);
    struct room* destroy_room(struct room* room);
    void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west);
    void show_room(const struct room* room);
    void delete_item_from_room(struct room* room, struct item* item);
    void add_item_to_room(struct room* room, struct item* item);
    struct item* get_item_from_room(const struct room* room, const char* name);


    return 0;
}
