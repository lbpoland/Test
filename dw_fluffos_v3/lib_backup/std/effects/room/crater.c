#include <effect.h>
string query_classification() { return "room.crater.broom"; }
string *beginning( object room, string name ) {
  room->add_item( ({ name + " shaped crater", "crater" }),
      "There is a large crater in the ground, as if " +
      capitalize( name ) + " happened here recently, from a "
      "very great height indeed." );
  room->add_extra_look( this_object() );
  return ({ name });
}
string *merge_effect( object room, mixed old_names, string name ) {
  if( member_array( name, old_names ) != -1 ) {
    return old_names;
  }
  room->add_item( ({ name + " shaped crater", "crater" }),
      "There is a large crater in the ground, as if " +
      capitalize( name ) + " happened here recently, "
      "from a very great height indeed." );
  return old_names += ({ name });
}
void end( object room, mixed names ) {
  string name;
  foreach( name in names )  {
    room->remove_item( name + " shaped crater" );
  }
  room->remove_extra_look( this_object() );
}
int query_indefinite() { return 1; }
string extra_look( object room ) {
   int     *enums;
   string  *shapes;
   enums = room->effects_matching( query_classification() );
   if( !sizeof( enums ) )
     return "";
   shapes = room->arg_of( enums[0] );
   if( !sizeof( shapes ) )
     return "";
   if( sizeof( shapes ) == 1 )
     return "There is " + add_a( capitalize( shapes[0] ) ) +
         " shaped crater in the ground.\n";
   else {
     return "There are " + query_multiple_short( map( shapes, (: capitalize(
                $1 ) :) ) ) + " shaped craters in the ground.\n";
   }
}