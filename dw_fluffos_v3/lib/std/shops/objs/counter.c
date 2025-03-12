#include <position.h>
inherit "/std/surface";
void create() {
   ::create();
   set_name( "counter" );
   set_short( "counter" );
   set_long( "The counter seems to be where you should leave glasses and "
      "plates to be cleared away.\n" );
   reset_get();
   add_property(CAN_POSITION_PROPERTY, 1);
}
void clear_item( object item ) {
   if( environment( item ) == this_object()
       && !sizeof( all_inventory( item ) ) )
      item->move( "/room/rubbish" );
}
void event_enter( object ob, string mess, object from ) {
   if( ob->query_property( "pub item" )
       && !sizeof( all_inventory( ob ) ) )
      call_out( "clear_item", 3, ob );
}