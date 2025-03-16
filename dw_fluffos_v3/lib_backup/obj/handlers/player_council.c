inherit "/obj/handlers/inherit/player_council";
#define NOMIC_SYSTEM_NO_CLASSES
#include <nomic_system.h>
void load_me();
void save_me();
void create() {
   player_council::create();
   load_me();
}
void save_me() {
   unguarded( (: save_object(NOMIC_SYSTEM_SAVE_FILE) :) );
}
void load_me() {
   unguarded( (: restore_object(NOMIC_SYSTEM_SAVE_FILE, 1) :) );
}
void dest_me() {
   destruct(this_object());
}