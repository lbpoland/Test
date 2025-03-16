#include "path.h"
inherit "/std/room";
object npc;
void setup() {
    set_light(70);
    set_short( "cloned NPC room" );
    add_property( "determinate", "the " );
    set_long( "This room holds a very simple NPC.  He is a fighter.  His "
    "code is within the room code.  If he's not here, type update, and"
    ", like magic, he should appear.  If he doesn't, panic.\n");
    add_exit("onwards", PATH +"room2", "door");
    }
void reset(){
        if (!npc){
    npc = clone_object( "/obj/monster" );
    npc -> set_name("pugh");
    npc -> set_short("Pugh");
    npc -> add_property("determinate", "");
    npc -> add_alias( ({"npc", "warrior", "man"}) );
    npc -> set_long("This is Pugh.  He was cloned here, and "
    "this is his world.  Welcome to it.\n");
    npc -> basic_setup("human", "warrior", 10);
    npc -> set_gender( 1 );
    npc->move( this_object() );
    }
    }