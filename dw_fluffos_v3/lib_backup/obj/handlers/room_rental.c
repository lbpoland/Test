#include <money.h>
#include <room/room_rental.h>
protected void do_load();
protected void do_save();
protected void evict_tenant( object room_ob );
private nosave int loaded = 0;
private mapping rented_rooms = ([]);
private mapping rental = ([]);
private mapping eviction_times = ([]);
private mapping locations = ([]);
private mapping paths = ([]);
void create() {
  do_load();
}
void reset() {
   string room;
   int now = time();
   foreach( room in keys( rented_rooms ) ) {
      if ( stringp( rented_rooms[ room ] ) ) {
         if ( ( eviction_times[ room ] < now ) &&
              ( eviction_times[ room ] > -1 ) ) {
            evict_tenant( find_object( room ) );
            tell_creator( "goldenthread", "RENTAL: %s no longer rents %s\n",
                          rented_rooms[ room ], room );
            rented_rooms[ room ] = 0;
            eviction_times[ room ] = -1;
         }
      }
   }
   do_save();
}
protected void do_load() {
   if ( !loaded )
      unguarded( (: restore_object( ROOM_RENTAL_SAVE_FILE, 1 ) :) );
   loaded = 1;
}
protected void do_save() {
   unguarded( (: save_object( ROOM_RENTAL_SAVE_FILE , 0 ) :) );
}
void evict_tenant( object room_ob ) {
   object *occupants;
   occupants = filter( all_inventory( room_ob ), (: living :) );
   room_ob->evict_tenant( occupants );
}
int add_room( string room, int cost, object office ) {
   object room_ob;
   if( !room_ob = load_object( room ) )
      return 0;
   rented_rooms[ room ] = 0;
   rental[ room ] = cost;
   eviction_times[ room ] = -1;
   locations[ room ] = office->query_location();
   paths[ room_ob->short() ] = room;
   do_save();
   return 1;
}
string query_who_rents( string room, object office ) {
   if ( locations[room] == office->query_location() ) {
      if ( stringp( rented_rooms[room] ) )
         return rented_rooms[room];
      else
         return "nobody";
   } else
      return "no such room in this location";
}
int check_tenant( object player_ob, object room_ob, object office ) {
   string player = player_ob->short();
   string room = room_ob->short();
   if ( player == query_who_rents( room, office ) )
      return RENTAL_SUCCESS;
   else if ( player == "nobody" )
      return RENTAL_AVAILABLE;
   else if ( player == "no such room!" )
      return RENTAL_NO_SUCH_ROOM;
   else
      return RENTAL_ALREADY_RENTED;
}
int delete_room( string room, object office ) {
  string room_short = load_object( room )->short();
  if ( locations[room] == office->query_location() ) {
    map_delete( rented_rooms, room );
    map_delete( rental, room );
    map_delete( eviction_times, room );
    map_delete( locations, room );
    map_delete( paths, room_short );
    do_save();
    return 1;
  } else
    return 0;
}
int clear_rooms( object office ) {
   object room_ob;
   foreach( string room in keys( filter( locations,
            (: $2 == $( office->query_location() ) :) ) ) ) {
      room_ob = load_object( room );
    map_delete( rented_rooms, room );
    map_delete( rental, room );
    map_delete( eviction_times, room );
    map_delete( locations, room );
    map_delete( paths, room_ob->query_short() );
  }
  do_save();
  return 1;
}
string *query_rooms_to_rent( object office ) {
  return keys( filter( locations,
               (: $2 == $( office->query_location() ) :) ) );
}
int do_rental( object player_ob, string room_short, object office ) {
   int result;
   string domain = office->query_domain();
   string room = paths[ room_short ];
   if ( locations[room] == office->query_location() ) {
      if ( !rented_rooms[room] ||
           ( rented_rooms[room] == player_ob->short()) ) {
         if ( (int)player_ob->query_value_in( domain ) < rental[room] )
            return RENTAL_NO_MONEY;
         rented_rooms[room] = player_ob->short();
         eviction_times[room] = time() + ONE_DAY;
         result = RENTAL_SUCCESS;
      } else
         result = RENTAL_ALREADY_RENTED;
   } else
      result = RENTAL_NO_SUCH_ROOM;
   do_save();
   return result;
}
int query_rental_value( string room ) {
   return rental[ room ];
}
int remove_rental( object room_ob ) {
   int result;
   string room_short = room_ob->short();
   string room = paths[ room_short ];
   if ( !undefinedp( rented_rooms[room] ) ) {
      rented_rooms[room] = 0;
      result = RENTAL_SUCCESS;
   } else
      result = RENTAL_NO_SUCH_ROOM;
   do_save();
   return result;
}