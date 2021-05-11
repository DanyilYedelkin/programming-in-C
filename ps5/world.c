#include <stdio.h>
#include <stdlib.h>
#include "world.h"

struct container* create_world(){

    //creating rooms
    struct room* home = create_room("start", "start");
    struct container* world = create_container(NULL, ROOM, home);
    struct room* garden = create_room("garden", "g");
    struct room* akkala_tower = create_room("Akkala_Tower", "a");
    struct room* dah_hesho = create_room("Dah_Hesho_Shrine", "d");
    struct room* south_akkala_stable = create_room("South_Akkala_Stable", "w");
    struct room* spring_of_power = create_room("Spring_of_Power", "t");
    struct room* ze_kasho_shrine = create_room("Ze_Kasho_Shrine", "Ze");
    struct room* ancient_tech_lab = create_room("Akkala_Ancient_Tech_Lab", "Th");
    struct room* east_akkala_stable = create_room("East_Akkala_Stable", "It");
    struct room* katosa_aug_shrine = create_room("Katosa_Aug_Shrine", "Ka");
    struct room* skull_lake = create_room("Skull_Lake", "Thsda");
    struct room* tutsuwa_nima_shrine = create_room("Tutsuwa_Nima_Shrine", "Tut");
    struct room* central_tower = create_room("Central_Tower", "Centra");
    struct room* dah_kaso_shrine = create_room("Dah_Kaso_Shrine", "Shrin");
    struct room* kaam_yatak_shrine = create_room("Kaam_Yatak_Shrine", "Kaam");

    //creating items
    struct item* sword = create_item("Sword", "It's", MOVABLE);
    struct item* magical_sword = create_item("MagicalSword", "TheWhite", MOVABLE);
    struct item* magical_shield = create_item("MagicalShield", "Itis", MOVABLE);
    struct item* boomerang = create_item("Boomerang", "Itcan", MOVABLE);
    struct item* bomb = create_item("Bomb", "Theycan", MOVABLE);
    struct item* bow = create_item("Bow", "OnceLink", MOVABLE);
    struct item* arrow = create_item("Arrow", "Thesedeadly", MOVABLE);
    struct item* silver_arrow = create_item("SilverArrow", "Itsprimary", MOVABLE);
    struct item* candle = create_item("Candle", "isusedtoeither", MOVABLE);
    struct item* recorder = create_item("Recorder", "TheRecorder", MOVABLE);

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
