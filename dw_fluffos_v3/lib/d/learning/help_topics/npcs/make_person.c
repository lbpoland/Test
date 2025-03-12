#include "path.h";
inherit "/std/room";
object red_demon;
void setup() {
   set_short( "room telling about adding NPC's" );
   add_property( "determinate", "the " );
   set_long( "This is a room showing how to add a stationary NPC to a room.  "
            "If you try to \"update here\" you will see that it waits a few "
            "seconds after loading the room before adding the NPC and, that "
            "when it appears there are a message notifying the player about "
            "it.\n" );
   set_light( 60 );
   add_exit( "exit", ENTRANCE, "path" );
   add_property( "commented functions",
                ({ "set_long", "set_short", "add_property",
                   "set_light", "reset" }) );
   add_property( "keywords", ({ "npc", "clone", "permanent", "make" }) );
}
void reset() {
   if ( !red_demon ) {
      call_out( "make_demon", 5 );
   }
}
void make_demon() {
   red_demon = clone_object( "/obj/monster" );
   red_demon->set_name( "imp" );
   red_demon->set_short( "small red imp" );
   red_demon->add_adjective( ({ "small", "red" }) );
   red_demon->set_long( "This is a small red imp who has agreed to be used "
                       "as an example.\n" );
   red_demon->set_base_weight( 10 );
   red_demon->set_height( 17 );
   red_demon->set_race( "imp" );
   red_demon->set_level( 1 );
   red_demon->move( this_object(), "$N materialize$s with a small *POP*." );
}