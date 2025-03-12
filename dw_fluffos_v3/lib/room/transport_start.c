inherit "/std/room/basic_room";
inherit "/std/basic/virtual_quit_control";
#define TRANSPORT_LOCATION "transport start"
void setup() {
   set_long("A room with bunches of horses and camels milling around in "
            "chunks.  You think you have never seen quite so many "
            "transport animals ever before.\n");
   set_short("transport start");
}
void player_quitting( object player, object place ) {
   tell_creator( "goldenthread", "adding property with player %O and place "
                 "%O with environment %O\n", player, place,
                 environment( place ) );
   player->add_property( TRANSPORT_LOCATION,
                         find_start_pos( player, environment( place ) ), 180 );
}
void event_enter( object ob ) {
   string location;
   location = ob->query_property( TRANSPORT_LOCATION );
   tell_creator("goldenthread", "location: %s\n", location );
   if ( !location ) {
      location = ob->query_start_pos();
   }
   tell_creator( "goldenthread", "final location: %s\n", location );
   ob->move( location );
}