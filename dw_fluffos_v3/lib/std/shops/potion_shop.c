#define CONVERT "/global/events"->convert_message
#define MIN_VOLUME 1000
inherit "/std/shops/craft_shop_category";
void shopkeeper_say( string message );
int is_potion_or_salve( object ob );
void set_message_function( function wossname );
private nosave function _message_function;
private nosave string _shopkeeper;
void create() {
   set_message_function( (: shopkeeper_say :) );
   ::create();
   set_allowed_to_sell( (: is_potion_or_salve :) );
}
void set_message_function( function wossname ) {
   _message_function = wossname;
}
function query_message_function() {
   return _message_function;
}
void set_shopkeeper( string name ) {
   _shopkeeper = name;
}
string query_shopkeeper() {
   return _shopkeeper;
}
void shopkeeper_say( string message ) {
   object *frog;
   if( !message || message == "" )
      message = "Tuppence a bucket, well stamped down!";
   if( _shopkeeper ) {
      frog = match_objects_for_existence( _shopkeeper, this_object() );
      if( sizeof( frog ) == 1 ) {
         frog[0]->init_command( "' "+ message );
         return;
      }
   }
   write( message );
   return;
}
int is_potion_or_salve( object ob ) {
   object thing, *contents;
   int found_something;
   string contents_string;
   if( !ob->query_volume() ) {
      tell_creator( this_player(), "ob has 0 volume.\n" );
      if( _message_function )
         evaluate( _message_function,
               CONVERT( "There's nothing in "+ ob->the_short() +" that "
               "can be described as either potion or salve, "+
               this_player()->the_short() +".\n" ) );
      return 0;
   } else if( ob->query_volume() < MIN_VOLUME ||
              ob->query_volume() < ( 7 * ob->query_max_volume() / 10 ) ) {
      tell_creator( this_player(), "ob does not contain enough stuff.\n" );
      if( _message_function )
         evaluate( _message_function,
               CONVERT( "We don't deal in quantities smaller than a cup, "+
               this_player()->the_short() +".\n" ) );
      return 0;
   }
   contents = all_inventory( ob );
   if( !sizeof( contents ) ) {
      tell_creator( this_player(), "No contents.\n" );
      if( _message_function )
         evaluate( _message_function,
               CONVERT( ob->the_short() +" is empty, "+
               this_player()->the_short() +"!\n" ) );
      return 0;
   }
   foreach( thing in contents )
      if( !( sizeof( thing->query_apply_effects() ) +
             sizeof( thing->query_eat_effects() ) ) ) {
         found_something = 1;
      } else {
         tell_creator( this_player(), "thing %s, effect %O.\n",
                       thing->query_short(), thing->query_eat_effects()  );
      }
   contents_string = ( sizeof( contents ) > 1 ) ?
         query_multiple_short( contents, "the" ) +" are neither potions nor "
            "salves, or they are " :
         contents[0]->the_short() +" is neither potion nor salve, or it is ";
   if( found_something ) {
      if( _message_function )
         evaluate( _message_function,
               CONVERT( "Either "+ contents_string +"impure, or so weak as "
               "to make no difference, "+ this_player()->the_short() +"." ) );
      return 0;
   }
   return 1;
}