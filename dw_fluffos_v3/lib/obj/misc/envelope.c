#define SMALL   3
#define MEDIUM  5
#define LARGE   8
#define UNSEALED  1
#define SEALED    2
#define OPENED    3
inherit "/obj/baggage";
nosave int status;
void make_envelope( string description, int size ) {
   string adjective, noun;
   if( size < 2 )
      size = 2;
   switch( size ) {
      case 0..SMALL:
         adjective = "small";
         noun = "envelope";
         break;
      case SMALL + 1..MEDIUM:
         adjective = "medium sized";
         noun = "envelope";
         break;
      case MEDIUM + 1..LARGE:
         adjective = "large";
         noun = "envelope";
         break;
      default:
         adjective = "large";
         noun = "packet";
         add_alias("packet");
   }
   set_name( "envelope" );
   set_short( adjective + " " + description + " " + noun );
   add_adjective( adjective );
   add_adjective( explode( description, " " ) );
   set_long( "This is a " + adjective + " " + description + " envelope.  " );
   set_weight( 1 );
   set_value( 300 + size * 20 );
   set_max_weight( size );
   set_material( "paper" );
   add_property( "writeable", 1 );
   add_extra_look( this_object() );
   status = UNSEALED;
}
void init() {
   ::init();
   this_player()->add_command( "seal", this_object(),
      "<direct:object:me>" );
   this_player()->add_command( "unseal", this_object(),
      "<direct:object:me>" );
}
string long( string str, int dark ) {
   string desc;
   switch( status ) {
   case UNSEALED :
      desc = "It has a sticky flap at one end with which you could "
         "probably seal it if you wanted to, though it might be wise to put "
         "something into it first or you're going to feel rather silly.\n";
      break;
   case SEALED :
      desc = "The sticky flap seems to have been sealed down.\n";
      break;
   case OPENED :
      desc = "It looks like it has been sealed and then opened up.\n";
      break;
   default :
      desc = "It is completely broken - you'd better tell a liaison.\n";
   }
   return ::long( str, dark ) + desc;
}
int do_seal() {
   if( status != UNSEALED ) {
      return notify_fail( this_object()->the_short() + " has already been "
         "sealed.\n" );
   }
   do_close();
   set_stuck( 1 );
   status = SEALED;
   this_player()->add_succeeded_mess( this_object(), "$N lick$s the flap on "
      "$D and seal$s it down.\n", ({ }) );
   return 1;
}
int do_unseal() {
   if( status != SEALED ) {
      return notify_fail( this_object()->the_short() + " has not been "
         "sealed.\n" );
   }
   set_stuck( 0 );
   do_open();
   status = OPENED;
   this_player()->add_succeeded_mess( this_object(), "$N tear$s back the "
      "flap on $D and open$s it.\n", ({ }) );
   return 1;
}
int query_envelope_status() {
   return status;
}
mixed *stats() {
   return ::stats() + ({
      ({ "status", status, }),
   });
}
mapping int_query_static_auto_load() {
   return ([
      "::" : ::int_query_static_auto_load(),
      "status" : status,
   ]);
}
void init_static_arg( mapping map ) {
   if( map["::"] )
      ::init_static_arg( map["::"] );
   if( !undefinedp( map["status"] ) )
      status = map["status"];
}
mixed query_static_auto_load() {
   if( base_name( this_object() ) + ".c" == __FILE__ )
      return int_query_static_auto_load();
   return ([ ]);
}