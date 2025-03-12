#ifndef __STD_HOSPITAL_H
#define __STD_HOSPITAL_H
#define HOSPITAL_ALIGNMENT_INHERIT "/std/hospital/alignment"
#define REGEN_TIME (1 * 60 * 60)
#define DEFAULT_MAX_CACHE 10
#define DEFAULT_LOG_DIRECTORY "/log"
#define DEFAULT_POPULATION 3
#define MINIMUM_DEATH_REGEN 3
#define POPULATION_UPDATE_TIME 15 * 60
class regenerated_npc {
    string type;
    string load_position;
}
class zone_info {
   int wealth;
   int busy;
   int npc_chance;
   mapping npcs;
   int group_chance;
   mapping groups;
   int zone_chance;
   mapping zones;
}
class unique_npc {
   int next_regen_time;
}
class npc_info {
   string path;
   int unique;
   int delay;
   int transient;
   int nocturnal;
   int diurnal;
   string* seasonal;
   int max_population;
   string* move_zones;
   string* commands;
   object* population;
   int no_deaths;
   int no_created;
   int no_reused;
   int next_update;
}
class group_info {
   string* move_zones;
   mapping npcs;
   mapping npc_commands;
   int protect;
   int defend;
   int transient;
   int max_population;
   mixed* storage;
   int no_creates;
   int next_update;
}
#define MONSTER "/obj/monster"
#define MAX_NAMED_LIVING 600
#define MAX_AM_LIVING 450
#define MAX_DJEL_LIVING 100
#endif