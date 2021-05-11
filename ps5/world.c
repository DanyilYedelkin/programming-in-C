#include <stdio.h>
#include <stdlib.h>
#include "world.h"

struct container* create_world(){

    //creating rooms
    struct room* home = create_room("start", "s");
    struct container* world = create_container(NULL, ROOM, home);
    struct room* garden = create_room("garden", "g");
    struct room* akkala_tower = create_room("Akkala", "a");
    struct room* dah_hesho = create_room("Dah", "d");
    struct room* south_akkala_stable = create_room("Southd", "w");
    struct room* spring_of_power = create_room("Spring", "t");
    struct room* ze_kasho_shrine = create_room("Ze", "Ze");
    struct room* ancient_tech_lab = create_room("Ancient", "Th");
    struct room* east_akkala_stable = create_room("Easta", "It");
    struct room* katosa_aug_shrine = create_room("Katosa", "Ka");
    struct room* skull_lake = create_room("Skul", "Thsda");
    struct room* tutsuwa_nima_shrine = create_room("Tutsuwa", "Tut");
    struct room* central_tower = create_room("Centra", "Centra");
    struct room* dah_kaso_shrine = create_room("Dahaaso", "Shrin");
    struct room* kaam_yatak_shrine = create_room("Kaamyat", "Kaam");
    struct room* kaam1 = create_room("Kat1", "Kaam1");
    struct room* kaam2 = create_room("Kat2", "Kaam2");
    struct room* kaam3 = create_room("Kat3", "Kaam3");
    struct room* kaam4 = create_room("Kat4", "Kaam4");
    struct room* kaam5 = create_room("Kat5", "Kaam5");

    //creating items
    struct item* sword = create_item("Sword", "Its", MOVABLE);
    struct item* magical_sword = create_item("MagicalSword", "Thehite", MOVABLE);
    struct item* magical_shield = create_item("MagicalShield", "Itis", MOVABLE);
    struct item* boomerang = create_item("Boomerang", "Ican", MOVABLE);
    struct item* bomb = create_item("Bomb", "eycan", MOVABLE);
    struct item* bow = create_item("Bow", "ceLink", MOVABLE);
    struct item* arrow = create_item("Arrow", "esedeadly", MOVABLE);
    struct item* silver_arrow = create_item("SilverArrow", "rimary", MOVABLE);
    struct item* candle = create_item("Candle", "edther", MOVABLE);
    struct item* recorder = create_item("Recorder", "corder", MOVABLE);

    //add items to some rooms
    add_item_to_room(home, sword);
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
    add_room_to_world(world, home);
    add_room_to_world(world, garden);
    add_room_to_world(world, akkala_tower);
    add_room_to_world(world, dah_hesho);
    add_room_to_world(world, south_akkala_stable);
    add_room_to_world(world, spring_of_power);
    add_room_to_world(world, ze_kasho_shrine);
    add_room_to_world(world, ancient_tech_lab);
    add_room_to_world(world, east_akkala_stable);
    add_room_to_world(world, katosa_aug_shrine);
    add_room_to_world(world, skull_lake);
    add_room_to_world(world, tutsuwa_nima_shrine);
    add_room_to_world(world, central_tower);
    add_room_to_world(world, dah_kaso_shrine);
    add_room_to_world(world, kaam_yatak_shrine);
    add_room_to_world(world, kaam1);
    add_room_to_world(world, kaam2);
    add_room_to_world(world, kaam3);
    add_room_to_world(world, kaam4);
    add_room_to_world(world, kaam5);

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
    if((world == NULL) || (name == NULL)) return NULL;

    return get_from_container_by_name(world, name);
}
