#include <twilight.h>
#include <climate.h>
int last_updated;
mixed roomitems;
string *roomlong;
mixed roomchats;
object shadowed_obj;
void set_current_long();
string return_long( mixed desc );
void do_change();
void change( int time_now );
void create() {
  seteuid( (string)"/secure/master"->creator_file( file_name(
    this_object() ) ) );
}
void destruct_shadow( object thing ) {
  if( thing == this_object() )
    destruct( thing );
  else
    thing->destruct_shadow( thing );
}
void setup_shadow( object this_room ) {
  shadow( this_room, 1 );
  shadowed_obj = this_room;
  if( WEATHER_HANDLER->query_day() ) {
    call_out( "changing_to_day", 0, 1 );
    last_updated = DAY;
  } else {
    call_out( "changing_to_night", 0, 1 );
    last_updated = NIGHT;
  }
  roomitems = ({ ({ }), ({ }) });
  roomlong = allocate( 2 );
  roomlong = ({ 0, 0 });
  roomchats = allocate( 2 );
  WEATHER_HANDLER->weather_notify( this_room, NOTIFY_DAY );
}
void event_weather(int whats_changed) {
  if (WEATHER_HANDLER->query_day()) {
    if (last_updated == NIGHT)
      change( DAY );
  } else if (last_updated == DAY)
    change( NIGHT );
  shadowed_obj->event_weather( whats_changed );
}
void change( int time_now ) {
  int i;
  last_updated = time_now;
  set_current_long();
  for ( i = 0; i < sizeof( roomitems[ last_updated ] ); i += 2 )  {
    shadowed_obj->modify_item( roomitems[ last_updated ][ i ],
                               roomitems[ last_updated ][ i + 1 ] );
  }
  for ( i = 0; i < sizeof( roomitems[ 1 - last_updated ] ); i += 2 )  {
    if ( member_array( roomitems[ 1 - last_updated ][ i ],
                       roomitems[ last_updated ] ) == -1 )  {
      shadowed_obj->modify_item( roomitems[ 1 - last_updated ][ i ],
                                 "You can't see that now.\n" );
    }
  }
  shadowed_obj->stop_room_chats();
  if( sizeof(roomchats[last_updated]) )
    shadowed_obj->room_chat( roomchats[last_updated] );
  if( last_updated == DAY )
    shadowed_obj->changing_to_day( 0 );
  else
    shadowed_obj->changing_to_night( 0 );
}
void set_day_long( string str ) {
  roomlong[DAY] = str;
  set_current_long();
}
void set_night_long( string str ) {
  roomlong[NIGHT] = str;
  set_current_long();
}
void set_current_long() {
  if (roomlong[last_updated] != 0 && roomlong[last_updated] != "")
    shadowed_obj->set_long( roomlong[last_updated] );
}
varargs int add_day_item( mixed shorts, mixed desc, mixed no_plural ) {
  string the_item;
  if( pointerp( shorts ) )
    the_item = shorts[0];
  else
    the_item = shorts;
  roomitems[DAY] += ({ the_item, return_long( desc ) });
  if( last_updated == DAY )
    return this_object()->add_item( shorts, desc, no_plural );
  return 1;
}
varargs int add_night_item( mixed shorts, mixed desc, mixed no_plural ) {
  string the_item;
  if( pointerp( shorts ) )
    the_item = shorts[0];
  else
    the_item = shorts;
  roomitems[NIGHT] += ({ the_item, return_long( desc ) });
  if( last_updated == NIGHT )
    return shadowed_obj->add_item( shorts, desc, no_plural );
  return 1;
}
void room_day_chat( mixed *args ) {
  roomchats[DAY] = args;
  if( last_updated == DAY )
    shadowed_obj->room_chat( args );
}
void room_night_chat( mixed *args ) {
  roomchats[NIGHT] = args;
  if( last_updated == NIGHT )
    shadowed_obj->room_chat( args );
}
string return_long( mixed desc ) {
  int ma;
  if( !pointerp( desc ) )
    return (string)desc;
  ma = member_array( "long", desc );
  if( ma < 0 )
    return "Error: No long found.";
  return (string)desc[ma+1];
}
int query_time() { return last_updated; }
mixed query_roomitems() { return roomitems; }
string *query_roomlong() { return roomlong; }
mixed query_roomchats() { return roomchats; }