#include <room/room_rental.h>
string *query_exits();
int check_entry( object player_ob, object room_ob ) {
  return ROOM_RENTAL_HANDLER->check_tenant( player_ob, room_ob );
}
string query_costume_mess( object costume ) {
  return "The imp takes the " + costume->query_short() + ".\n";
}
void evict_tenant( object* tenants ) {
  string exit = query_exits()[0];
  foreach (object person in tenants) {
     tell_object( person, "You hear the soft tinkling of a bell.  As the "
               "sound resounds throughout the room it shatters your "
               "illusions.  A small imp hurries into the room and gently but "
               "firmly propels you outside the door.\n" );
  }
  tenants->move_with_look( exit, "$N appears from $F as though he's been "
                                "pushed in rather abruptly.\n" );
}
void event_exit( object ob, string message, object to ) {
  object *costumes;
  costumes = filter( deep_inventory( ob ),
                     (: $1->query_property( "costume" ) :) );
  foreach( object costume in costumes )
    costume->move( "/room/rubbish", query_costume_mess( costume ) );
}