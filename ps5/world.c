#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include "room.h"
#include "item.h"

struct container* create_world(){

    //creating rooms
    /*struct room* home = create_room("a1", "a");
    struct container* created_world = create_container(NULL, ROOM, home);

    struct room* garden = create_room("a2", "b");
    struct room* akkala_tower = create_room("a3", "c");
    struct room* dah_hesho = create_room("a4", "d");
    struct room* south_akkala_stable = create_room("a5", "e");
    struct room* spring_of_power = create_room("a6", "f");
    struct room* ze_kasho_shrine = create_room("a7", "g");
    struct room* ancient_tech_lab = create_room("a8", "k");
    struct room* east_akkala_stable = create_room("a9", "l");
    struct room* katosa_aug_shrine = create_room("a10", "m");
    struct room* skull_lake = create_room("a11", "n");
    struct room* tutsuwa_nima_shrine = create_room("a12", "o");
    struct room* central_tower = create_room("a13", "r");
    struct room* dah_kaso_shrine = create_room("a14", "s");
    struct room* kaam_yatak_shrine = create_room("a15", "t");
    struct room* kaam1 = create_room("a16", "u");
    struct room* kaam2 = create_room("a17", "y");
    struct room* kaam3 = create_room("a18", "v");
    struct room* kaam4 = create_room("a19", "w");
    struct room* kaam5 = create_room("a20", "q");

    //creating items
    struct item* sword = create_item("Sword", "a1", MOVABLE);
    struct item* magical_sword = create_item("MagicalSword", "a2", MOVABLE);
    struct item* magical_shield = create_item("MagicalShield", "a3", MOVABLE);
    struct item* boomerang = create_item("Boomerang", "a4", MOVABLE);
    struct item* bomb = create_item("Bomb", "a5", MOVABLE);
    struct item* bow = create_item("Bow", "a6", MOVABLE);
    struct item* arrow = create_item("Arrow", "a7", MOVABLE);
    struct item* silver_arrow = create_item("SilverArrow", "a8", MOVABLE);
    struct item* candle = create_item("Candle", "a9", MOVABLE);
    struct item* recorder = create_item("Recorder", "a10", MOVABLE);

    //add items to some rooms
    add_item_to_room(kaam1, sword);
    add_item_to_room(akkala_tower, magical_sword);
    add_item_to_room(spring_of_power, magical_shield);
    add_item_to_room(east_akkala_stable, boomerang);
    add_item_to_room(tutsuwa_nima_shrine, bomb);
    add_item_to_room(dah_kaso_shrine, bow);
    add_item_to_room(ancient_tech_lab, arrow);
    add_item_to_room(central_tower, silver_arrow);
    add_item_to_room(kaam_yatak_shrine, candle);
    add_item_to_room(dah_hesho, recorder);

    //struct container* world = create_container(NULL, ROOM, home);

    //add all rooms to world
    add_room_to_world(created_world, home);
    add_room_to_world(created_world, garden);
    add_room_to_world(created_world, akkala_tower);
    add_room_to_world(created_world, dah_hesho);
    add_room_to_world(created_world, south_akkala_stable);
    add_room_to_world(created_world, spring_of_power);
    add_room_to_world(created_world, ze_kasho_shrine);
    add_room_to_world(created_world, ancient_tech_lab);
    add_room_to_world(created_world, east_akkala_stable);
    add_room_to_world(created_world, katosa_aug_shrine);
    add_room_to_world(created_world, skull_lake);
    add_room_to_world(created_world, tutsuwa_nima_shrine);
    add_room_to_world(created_world, central_tower);
    add_room_to_world(created_world, dah_kaso_shrine);
    add_room_to_world(created_world, kaam_yatak_shrine);
    add_room_to_world(created_world, kaam1);
    add_room_to_world(created_world, kaam2);
    add_room_to_world(created_world, kaam3);
    add_room_to_world(created_world, kaam4);
    add_room_to_world(created_world, kaam5);



    set_exits_from_room(room_1, NULL, NULL, room_2, NULL);
    set_exits_from_room(room_2, NULL, NULL, room_3, room_1);
    set_exits_from_room(room_3, NULL, NULL, room_4, room_2);
    set_exits_from_room(room_4, NULL, NULL, room_5, room_3);
    set_exits_from_room(room_5, NULL, NULL, room_6, room_4);
    set_exits_from_room(room_6, NULL, NULL, room_7, room_5);
    set_exits_from_room(room_7, NULL, NULL, room_8, room_6);
    set_exits_from_room(room_8, NULL, NULL, room_9, room_7);
    set_exits_from_room(room_9, NULL, NULL, room_10, room_8);
    set_exits_from_room(room_10, NULL, NULL, room_11, room_9);
    set_exits_from_room(room_11, NULL, NULL, room_12, room_10);
    set_exits_from_room(room_12, NULL, NULL, room_13, room_11);
    set_exits_from_room(room_13, NULL, NULL, room_14, room_12);
    set_exits_from_room(room_14, NULL, NULL, room_15, room_13);
    set_exits_from_room(room_15, NULL, NULL, room_16, room_14);
    set_exits_from_room(room_16, NULL, NULL, room_17, room_15);
    set_exits_from_room(room_17, NULL, NULL, room_18, room_16);
    set_exits_from_room(room_18, NULL, NULL, room_19, room_17);
    set_exits_from_room(room_19, NULL, NULL, room_20, room_18);
    set_exits_from_room(room_20, NULL, NULL, NULL, room_19);



    return created_world;*/



    //creating rooms
    struct room* home = create_room("A", "a"); 

    //struct container* world = create_container(NULL, ROOM, room_1);

    struct room* garden = create_room("B", "b"); 
    struct room* town = create_room("C", "c"); 
    struct room* castle = create_room("D", "d"); 
    struct room* roomuk = create_room("E", "e"); 
    struct room* coridor = create_room("F", "f"); 
    struct room* zal = create_room("G", "g"); 
    struct room* ad = create_room("H", "h"); 
    struct room* pechera = create_room("I", "i"); 
    struct room* dira = create_room("J", "j"); 
    struct room* pol = create_room("K", "k"); 
    struct room* okno = create_room("L", "l"); 
    struct room* lake = create_room("M", "m"); 
    struct room* more = create_room("N", "n");
    struct room* okean = create_room("O", "o");
    struct room* sad = create_room("P", "p");
    struct room* karcer = create_room("Q", "q");
    struct room* turma = create_room("R", "r");
    struct room* dilfo = create_room("S", "s");
    struct room* dragon = create_room("T", "t");

    //creating items
    struct item* posoch = create_item("posoch", "u", MOVABLE);
    struct item* sword = create_item("sword", "v", MOVABLE);
    struct item* shield = create_item("magical shield", "w", MOVABLE);
    struct item* book = create_item("spell book", "x", MOVABLE);
    struct item* bone = create_item("bone", "y", MOVABLE);
    struct item* armory = create_item("armory", "z", MOVABLE);

    //add items to some rooms
    add_item_to_room(home, posoch); 
    add_item_to_room(town, sword); 
    add_item_to_room(coridor, shield); 
    add_item_to_room(pechera, book);
    add_item_to_room(okno , bone); 
    add_item_to_room(more, armory); 

    //add all rooms to world

    struct container* worldmir = create_container(NULL, ROOM, home);

    //add_room_to_world(world, room_1); 
    add_room_to_world(worldmir, garden); 
    add_room_to_world(worldmir, town);
    add_room_to_world(worldmir, castle); 
    add_room_to_world(worldmir, roomuk); 
    add_room_to_world(worldmir, coridor); 
    add_room_to_world(worldmir, zal); 
    add_room_to_world(worldmir, ad);
    add_room_to_world(worldmir, pechera); 
    add_room_to_world(worldmir, dira); 
    add_room_to_world(worldmir, pol); 
    add_room_to_world(worldmir, okno);
    add_room_to_world(worldmir, lake); 
    add_room_to_world(worldmir, more); 
    add_room_to_world(worldmir, okean); 
    add_room_to_world(worldmir, sad); 
    add_room_to_world(worldmir, karcer); 
    add_room_to_world(worldmir, turma); 
    add_room_to_world(worldmir, dilfo); 
    add_room_to_world(worldmir, dragon); 

    return worldmir;
}

struct container* destroy_world(struct container* world){
    if(world == NULL) return NULL;

    destroy_containers(world);

    return NULL;
}

struct container* add_room_to_world(struct container* world, struct room* room){
    if(room == NULL) return NULL;

    if(world != NULL){
        if(get_room(world, room->name) != NULL) return NULL;
    }
    return create_container(world, ROOM, room);
}

struct room* get_room(struct container* world, char* name){
    //if((world == NULL) || (name == NULL)) return NULL;

    return get_from_container_by_name(world, name);
}
