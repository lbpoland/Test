#include <artifacts.h>
#include <tasks.h>
inherit "/obj/weapon";
inherit "/std/basic/artifact";
int query_magic_wand() { return 1; }
void create() {
  weapon::create();
  set_artifact_type( "wand" );
}
void set_weight( int number ) {
  weapon::set_weight( number );
  new_weapon( 80 * number );
   add_attack( "prod", 90, ({ 0, 5, weight }), "blunt", "blunt", 0 );
}
string long( int word, int dark ) {
  return artifact::long( word, dark ) + weapon::long( word, dark );
}
void init() {
  this_player()->add_command( "zap", this_object(), "<direct:object> at <indirect:object>" );
  this_player()->add_command( "zap", this_object(), "<indirect:object> with <direct:object>" );
}
int do_zap( object *things ) {
  int outcome;
  if ( query_wielded() != this_player() ) {
    this_player()->add_failed_mess( this_object(), "You must be holding "+
        "$D to $V it.\n", ({ }) );
    return 0;
  }
  if( ( sizeof( things ) > 1 ) ||
      ( sizeof( filter( things, (: $1->query_amount() > 1 :)) ) )
    ){
    this_player()->add_failed_mess( this_object(), "You can only zap $D "+
        "at one object at a time.\n", ({ }) );
    return 0;
  }
  if ( things[ 0 ] == this_object() ) {
    this_player()->add_failed_mess( this_object(), "You cannot zap $D at "+
        "itself!\n", ({ }) );
    return 0;
  }
  outcome = (int)TASKER->perform_task(this_player(), WAND_SKILL, level,
                                      TM_FREE);
  if ( outcome == FAIL ) {
    this_player()->add_failed_mess( this_object(), "You failed "+
        "to $V $D.\n", ({ }) );
    return 0;
  }
  if ( !charges ) {
    this_player()->add_failed_mess( this_object(), "It appears that there "+
        "are no charges in $D.\n", ({ }) );
    return 0;
  }
   if ( outcome == AWARD ) {
      write( "%^YELLOW%^"+ ({ "A piece of lore concerning wands becomes "
            "clearer for you", "You manage to grasp one of the principles "
            "of magic wands more firmly", "A sudden flash of insight allows "
            "you to understand the wand a little better" })[ random( 3 ) ] +
            ".%^RESET%^\n" );
   }
  charges--;
  if ( random( 100 ) < level / 10 ) {
    if ( !zapper->failed_zap( things[ 0 ], this_player(), this_object() ) )
      this_player()->add_succeeded_mess( this_object(), "$N $V $D at $I but "+
          "nothing happens!\n", things );
    return 1;
  }
  zapper->zap( things[ 0 ], this_player(), this_object() );
  this_player()->add_succeeded( things[ 0 ] );
  return 1;
}
mixed *stats() {
  return weapon::stats() + artifact::stats();
}
mapping query_dynamic_auto_load() {
  return ([
    "::" : weapon::query_dynamic_auto_load(),
    "artifact" : artifact::query_dynamic_auto_load(),
  ]);
}
mapping query_static_auto_load() {
  if ( explode( file_name( this_object() ), "#" )[ 0 ] != "/obj/wand" )
    return ([ ]);
  return ([
    "::" : int_query_static_auto_load(),
    "artifact" : artifact::query_static_auto_load(),
  ]);
}
void init_dynamic_arg( mapping map ) {
  if ( map[ "::" ] )
    weapon::init_dynamic_arg( map[ "::" ] );
  if ( map[ "artifact" ] )
    artifact::init_dynamic_arg( map[ "artifact" ] );
}
void init_static_arg( mapping map ) {
  if ( map[ "::" ] )
    weapon::init_static_arg( map[ "::" ] );
  if ( map[ "artifact" ] )
    artifact::init_static_arg( map[ "artifact" ] );
}