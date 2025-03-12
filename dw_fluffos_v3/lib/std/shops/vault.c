#include <vault.h>
inherit "/std/room/basic_room";
private object _container;
private string _vault_name;
private string _entry;
private string _there;
void set_vault_exit(string direc, mixed dest, string type) {
  _entry = dest;
  add_exit(direc, dest, type);
  modify_exit( direc, ({ "function", "check_done" }) );
  modify_exit( direc, ({ "closed", 1 }) );
}
void set_vault_name(string str) { _vault_name = str; }
object init_container(object person) {
  object container;
  string owner;
  owner = person->query_name();
  container = clone_object( "/obj/cont_save" );
  container->set_max_weight( 1000 );
  container->set_open();
  container->set_stuck( 1 );
  container->set_can_recurse(1);
  container->reset_get();
  container->set_save_file( VAULT_SAVE +_vault_name+ "/"+ owner,
                           person );
  if ( !master()->file_exists( VAULT_SAVE +_vault_name+"/"+ owner +".o" ) ) {
    container->add_property( "owner", owner );
    container->do_save();
  }
  container->move(this_object());
  container->add_property("there", "here");
  this_object()->setup_container(container);
  container->add_property( "owner", owner );
  _there = container->query_property("there");
  return container;
}
void event_enter(object thing, string mess, object from) {
  string owner;
  if( !userp( thing ) )
    return;
  owner = thing->query_name();
  if ( _container ) {
    if((string)_container->query_property( "owner" ) == owner)
      return;
    else if(thing->query_creator() &&
            find_player(_container->query_property( "owner" )) &&
            environment(find_player(_container->query_property( "owner" ))) ==
            this_object())
         return;
      else {
        _container->dest_me();
        _container = 0;
      }
  }
  _container = init_container(thing);
  call_out("fix_owner", 2, owner);
}
void fix_owner(string owner) {
  if (_container) {
     _container->add_property( "owner", owner );
     if(_there) {
       _container->add_property("there", _there);
     }
  }
}
int check_done( string verb, object thing, string special ) {
  if ( thing->query_auto_loading() ) {
    tell_room( this_object(), "The door swings shut.\n" );
    tell_object( thing, "Your vaults's inventory is still being generated.\n"
                "Please wait until it is completed.\n" );
      return notify_fail( "" );
   }
   return 1;
}
void event_exit( object thing, string message, object to ) {
  if(_container && _container->query_property("owner") == thing->query_name()) {
    _container->move("/room/void");
    call_out((: _container->dest_me() :), 1);
  }
  if(interactive(thing))
    thing->save_me();
}
string query_quit_handler() {
  return _entry;
}
void setup_container(object container) {
  container->set_name( "drawer" );
  container->set_short( "drawer" );
  container->add_alias( "drawer" );
  container->set_long("The single open drawer is sticking straight "
                      "out of the wall like...  well, like a drawer sticking "
                      "straight out of the wall.  " );
}
int trap_action( string str ) {
   string st1;
   if( sscanf( str,"%s %s", str, st1 ) );
      switch(str) {
      case "circle":
         tell_object( this_player(),
               "Something tells you that drawing a circle in this location "
               "would be a bad idea.\n");
         return 1;
      case "erect":
         tell_object( this_player(),
               "You can't seem to get the tent to unfold properly.  "
               "Perhaps you should try it somewhere else.\n");
         return 1;
      default:
         return 0;
    }
}
void event_net_dead(object ob) {
   ob->move_with_look(_entry);
}
void init() {
   ::init();
   this_player()->command_override( (: trap_action :) );
}
int query_vault_room() {
   return 1;
}