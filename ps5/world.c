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

    return created_world;*/



    //creating rooms
    struct room* room_1 = create_room("A", "a"); 

    struct container* world = create_container(NULL, ROOM, room_1);

    struct room* room_2 = create_room("B", "b"); 
    struct room* room_3 = create_room("C", "c"); 
    struct room* room_4 = create_room("D", "d"); 
    struct room* room_5 = create_room("E", "e"); 
    struct room* room_6 = create_room("F", "f"); 
    struct room* room_7 = create_room("G", "g"); 
    struct room* room_8 = create_room("H", "h"); 
    struct room* room_9 = create_room("I", "i"); 
    struct room* room_10 = create_room("J", "j"); 
    struct room* room_11 = create_room("K", "k"); 
    struct room* room_12 = create_room("L", "l"); 
    struct room* room_13 = create_room("M", "m"); 
    struct room* room_14 = create_room("N", "n");
    struct room* room_15 = create_room("O", "o");
    struct room* room_16 = create_room("P", "p");
    struct room* room_17 = create_room("Q", "q");
    struct room* room_18 = create_room("R", "r");
    struct room* room_19 = create_room("S", "s");
    struct room* room_20 = create_room("T", "t");

    //creating items
    struct item* item_1 = create_item("shield", "u", MOVABLE);
    struct item* item_2 = create_item("sword", "v", MOVABLE);
    struct item* item_3 = create_item("magical shield", "w", MOVABLE);
    struct item* item_4 = create_item("spellbook", "x", MOVABLE);
    struct item* item_5 = create_item("bone", "y", MOVABLE);
    struct item* item_6 = create_item("armory", "z", MOVABLE);

    //add items to some rooms
    add_item_to_room(room_1, item_1); 
    add_item_to_room(room_3, item_2); 
    add_item_to_room(room_6, item_3); 
    add_item_to_room(room_9, item_4);
    add_item_to_room(room_12 , item_5); 
    add_item_to_room(room_14, item_6); 

    /*set_exits_from_room(room_1, NULL, NULL, room_2, NULL);
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
    set_exits_from_room(room_20, NULL, NULL, NULL, room_19);*/

    //add all rooms to world
    //add_room_to_world(world, room_1); 
    add_room_to_world(world, room_2); 
    add_room_to_world(world, room_3);
    add_room_to_world(world, room_4); 
    add_room_to_world(world, room_5); 
    add_room_to_world(world, room_6); 
    add_room_to_world(world, room_7); 
    add_room_to_world(world, room_8);
    add_room_to_world(world, room_9); 
    add_room_to_world(world, room_10); 
    add_room_to_world(world, room_11); 
    add_room_to_world(world, room_12);
    add_room_to_world(world, room_13); 
    add_room_to_world(world, room_14); 
    add_room_to_world(world, room_15); 
    add_room_to_world(world, room_16); 
    add_room_to_world(world, room_17); 
    add_room_to_world(world, room_18); 
    add_room_to_world(world, room_19); 
    add_room_to_world(world, room_20); 

    return world;
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
