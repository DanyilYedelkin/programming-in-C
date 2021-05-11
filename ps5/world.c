#include <stdio.h>
#include <stdlib.h>
#include "world.h"

struct container* create_world(){

    //creating rooms
    struct room* home = create_room("start", "Nachadzas sa v chyzi svarneho suhaja. Na vychode sa nachadzaju dvere veduce z chyze von.");
    struct room* garden = create_room("garden", "Stojis pred chyzou a rozoznavas zahradku, ktora je znacne neudrziavana. este ze husty lesik na severe v porovnani so zahradkou nicim nevynika.");
    struct room* akkala_tower = create_room("Akkala Tower", "Akkala Tower is in the northeast portion of Hyrule, due north of Zora's Domain.");
    struct room* dah_hesho = create_room("Dah Hesho Shrine", "The Dah Hesho Shrine is one of the Shrines in the Akkala Region of The Legend of Zelda: Breath of the Wild. Location: Dah Hesho Shrine is located: From Akkala Tower, it is east of Tarrey Town or Lake Akkala.");
    struct room* south_akkala_stable = create_room("South Akkala Stable", "The South Akkala Stable is located near the main entrance to Akkala on the border of Eldin, just along the main road past Akkala Tower in the Akkala Region.");
    struct room* spring_of_power = create_room("Spring of Power", "The Spring of Power is a special area in the West side of Akkala near East Akkala Stable. It is guarded by several Guardian Skywatchers patrolling the entrance via the Ordorac Quarry.");
    struct room* ze_kasho_shrine = create_room("Ze Kasho Shrine", "Ze Kasho Shrine is across the road from the South Akkala Stables, heading West-Northwest from a T intersection.");
    struct room* ancient_tech_lab = create_room("Akkala Ancient Tech Lab", "The Akkala Ancient Tech Lab is an odd modified lighthouse on the Eastern tip of Akkala. It is operated by Robbie, one of the Sheikah researcher's and assistant to Purah in Hateno Village.");
    struct room* east_akkala_stable = create_room("East Akkala Stable", "It is located on the road to the Akkala Ancient Tech Lab far in the Northeast area of the Akkala region. Katosa Aug Shrine is immediately East of the stable.");
    struct room* katosa_aug_shrine = create_room("Katosa Aug Shrine", "Katosa Aug Shrine is located outside East Akkala Stable, where the roads from East Akkala Beach and Ordorac Quarry meet.");
    struct room* skull_lake = create_room("Skull Lake", "The imposing Skull Lake can be seen in the far North of Akkala, and the main valley entrance is guarded by Lynels.");
    struct room* tutsuwa_nima_shrine = create_room("Tutsuwa Nima Shrine", "Tutsuwa Nima Shrine is located behind the Spring of Power, east of East Akkala Stable. To reveal it, you have to finish The Spring of Power Shrine Quest.");
    struct room* central_tower = create_room("Central Tower", "Central Tower is in the, you guessed it, central portion of Hyrule.");
    struct room* dah_kaso_shrine = create_room("Dah Kaso Shrine", "Shrine Dah Kaso is located below the Digdogg Suspension Bridge on the Southwestern side of the Central Hyrule region.");
    struct room* kaam_yatak_shrine = create_room("Kaam Ya'tak Shrine", "Kaam Ya'tak Shrine is located South of the Central Hyrule Tower, just South of Mount Daphnes.");

    //connecting rooms in the world
    /*set_exits_from_room(home, NULL, garden, NULL, NULL);
    set_exits_from_room(garden, home, akkala_tower, NULL, NULL);
    set_exits_from_room(akkala_tower, garden, dah_hesho, NULL, NULL);
    set_exits_from_room(dah_hesho, akkala_tower, south_akkala_stable, NULL, NULL);
    set_exits_from_room(south_akkala_stable, dah_hesho, spring_of_power, NULL, NULL);
    set_exits_from_room(spring_of_power, south_akkala_stable, ze_kasho_shrine, NULL, NULL);
    set_exits_from_room(ze_kasho_shrine, spring_of_power, ancient_tech_lab, NULL, NULL);
    set_exits_from_room(ancient_tech_lab, ze_kasho_shrine, east_akkala_stable, NULL, NULL);
    set_exits_from_room(east_akkala_stable, ancient_tech_lab, katosa_aug_shrine, NULL, NULL);
    set_exits_from_room(katosa_aug_shrine, east_akkala_stable, skull_lake, NULL, NULL);
    set_exits_from_room(skull_lake, katosa_aug_shrine, tutsuwa_nima_shrine, NULL, NULL);
    set_exits_from_room(tutsuwa_nima_shrine, skull_lake, central_tower, NULL, NULL);
    set_exits_from_room(central_tower, tutsuwa_nima_shrine, dah_kaso_shrine, NULL, NULL);
    set_exits_from_room(dah_kaso_shrine, central_tower, kaam_yatak_shrine, NULL, NULL);
    set_exits_from_room(kaam_yatak_shrine, dah_kaso_shrine, NULL, NULL, NULL);*/


    //creating items
    struct item* sword = create_item("Sword", "It's dangerous to go alone! Take this.", MOVABLE);
    struct item* magical_sword = create_item("Magical Sword", "The White Sword is slightly stronger than the Wooden Sword.", MOVABLE);
    struct item* magical_shield = create_item("Magical Shield", "It is the only shield upgrade of the game, and replaces the Wooden Shield.", MOVABLE);
    struct item* boomerang = create_item("Boomerang", "It can be used to stun larger enemies, e.g. Moblins, or kill smaller ones, e.g. ", MOVABLE);
    struct item* bomb = create_item("Bomb", "They can be obtained by either buying them in shops or collecting them from killed enemies. They can be used to blow up walls, kill enemies, etc.", MOVABLE);
    struct item* bow = create_item("Bow", "Once Link has purchased them, he can use the Bow. There is no arrow inventory - instead, Link will lose a Rupee every time he shoots an arrow.", MOVABLE);
    struct item* arrow = create_item("Arrow", "These deadly projectiles are capable of killing Pols Voices in one shot, and are needed to defeat Gohma. ", MOVABLE);
    struct item* silver_arrow = create_item("Silver Arrow", "Its primary use is to defeat Ganon, as it is the only weapon capable of doing so.", MOVABLE);
    struct item* candle = create_item("Candle", "It is used to either light dark rooms inside a dungeon, burn bushes hiding secret staircases, or even to kill enemies. ", MOVABLE);
    struct item* recorder = create_item("Recorder", "The Recorder is the only musical instrument found in The Legend of Zelda. ", MOVABLE);


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

    struct container* world = create_container(NULL, ROOM, home);

    //create containers for all rooms
    //add_room_to_world(world, ROOM, home);
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
