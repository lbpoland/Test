#include <money.h>
#include <room/room_rental.h>
private string _location;
private string _domain;
int do_rental( string room );
int add_room( string room, int cost );
int delete_room( string room );
int clear_rooms();
void set_domain( string dom ) {
  _domain = dom;
}
string query_domain() {
  return _domain;
}
void set_location( string loc ) {
  _location = loc;
}
string query_location() {
  return _location;
}
void create() {
  set_location( "default" );
  set_domain( "default" );
}
void init() {
  add_command( "list", "[rooms]" );
  add_command( "rent", "<string'room'>",
               (: do_rental( $4[0] ) :) );
  if ( this_player()->query_creator() ) {
    add_command( "add", "<string> for <number>",
                 (: add_room( $4[0], $4[1] ) :) );
    add_command( "remove", "<string>", (: delete_room( $4[0] ) :) );
  }
}
string query_list() {
   string room;
   string list = "";
   string tenant;
   object room_ob;
   object office_ob = this_object();
   tell_creator( "goldenthread", "getting list for %s ( %O )\n",
                 office_ob->short(), office_ob );
   foreach( room in ROOM_RENTAL_HANDLER->query_rooms_to_rent( office_ob ) ) {
      tenant = ROOM_RENTAL_HANDLER->query_who_rents( room, office_ob );
      tell_creator( "goldenthread", "found %s\n", room );
      if ( room_ob = load_object( room ) ) {
         list += room_ob->query_short();
         if ( tenant != "nobody" )
            list += " (rented by " + tenant + ")\n";
         else
            list += " (available for " + MONEY_HAND->money_value_string(
               to_int( ROOM_RENTAL_HANDLER->query_rental_value( room ) ),
               _domain ) + ")\n";
      }
   }
   if ( list != "")
      list = "/global/events"->convert_message(list) + "\n";
   else
      list = "There are no rooms available here.\n";
   return list;
}
int do_list() {
  string list = "Here are the rooms available to rent in " + _location
                + ":\n\n";
  this_player()->add_succeeded_mess( this_object(), "$N ask$s for a list "
                                     "of available rooms.\n", ({ }) );
  list += query_list();
  tell_object( this_player(), list );
  return 1;
}
int add_room( string room, int cost ) {
  if ( ROOM_RENTAL_HANDLER->add_room( room, cost, this_object() ) ) {
    this_player()->add_succeeded_mess( this_object(),
                   ({ "$N $V a room.\n", "" }), ({ }) );
    return 1;
  }
  this_player()->add_failed_mess( this_object(),
                                  "That room cannot be added.\n", ({ }) );
  return 0;
}
int delete_room( string room ) {
  if( ROOM_RENTAL_HANDLER->delete_room( room, this_object() ) ) {
    this_player()->add_succeeded_mess( this_object(),
                   ({ "$N $V a room.\n", "" }), ({ }) );
    return 1;
  }
  return 0;
}
int clear_rooms() {
  if( ROOM_RENTAL_HANDLER->clear_rooms( this_object() ) ) {
    this_player()->add_succeeded_mess( this_object(),
                   ({ "$N $V the list of rooms.\n", "" }), ({ }) );
    return 1;
  }
  return 0;
}
int do_rental( string room ) {
  object ob = this_player();
  int ret = ROOM_RENTAL_HANDLER->do_rental( ob, room, this_object() );
  switch( ret ) {
    case RENTAL_SUCCESS:
      ob->pay_money( MONEY_HAND->create_money_array(
          ROOM_RENTAL_HANDLER->query_rental_value( room ), query_domain() ),
          query_domain() );
      ob->add_succeeded_mess( this_object(), ({ "$N $V a room.\n", "" }),
                              ({ }) );
      return 1;
    case RENTAL_NO_SUCH_ROOM:
      ob->add_failed_mess( this_object(), "There is no such room here.\n",
                           ({ }) );
      return 0;
    case RENTAL_ALREADY_RENTED:
      ob->add_failed_mess( this_object(), "The room has already been rented.\n",
                           ({ }) );
      return 0;
    case RENTAL_NO_MONEY:
      ob->add_failed_mess( this_object(), "You don't have enough money for "
                           "that.\n", ({ }) );
      return 0;
    default:
      ob->add_failed_mess( this_object(), "Something has gone wrong.  Please "
                           "contact a creator.\n", ({ }) );
      return 0;
  }
}
void init_dynamic_arg( mapping map, object ob ) {
   _domain = map[ "domain" ];
   _location = map[ "location" ];
}
mapping query_dynamic_auto_load( void ) {
   return ([ "domain" : _domain,
           "location" : _location, ]);
}