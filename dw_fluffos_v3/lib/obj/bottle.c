#define PHIAL 150
#define BOTTLE 1000
#define QUIRM 2500
#define DEMIJOHN 50000
inherit "/obj/vessel";
nosave string glass;
void make_bottle( string word, int number ) {
   float mass;
   string adjective, noun;
   glass = word;
   set_max_volume(number*4);
   mass = number / 100.0;
   if ( !mass ) mass = 1;
   set_leak_rate( 0 );
   set_value( to_int(mass * 25 + random( mass * 10 )) );
   set_weight( to_int(mass + random( mass * 10 ) / 10 ));
   set_max_weight( to_int(mass * 2 ));
   add_property( "fragile", to_int(mass * 20 + random( mass * 5 )) );
   switch( number ) {
      case 0..PHIAL:
         adjective = "small";
         noun = "phial";
         set_length( 2 );
         set_width( 1 );
         break;
      case PHIAL+1..BOTTLE:
         adjective = "medium sized";
         noun = "bottle";
         set_length( 12 );
         set_width( 6 );
         break;
      case BOTTLE+1..QUIRM:
         adjective = "large";
         noun = "Quirm";
         set_length( 24 );
         set_width( 12 );
         break;
      case QUIRM+1..DEMIJOHN:
         adjective = "very large";
         noun = "demijohn";
         set_length( 48 );
         set_width( 24 );
         break;
      default:
         adjective = "huge";
         noun = "tank";
         set_length( 88 );
         set_width( 48 );
   }
   set_name( lower_case( noun ) );
   set_short( adjective +" "+ glass +" "+ noun );
   set_long( "This is a "+ adjective +" "+ glass +" glass "+ noun +".\n" );
   add_alias( "bottle" );
   add_adjective( ({ adjective, glass }) );
   set_main_plural( adjective +" "+ glass +" "+ noun +"s" );
   add_plural( lower_case( noun ) +"s" );
   set_material( ({ "glass" }) );
}
string query_glass() { return glass; }
int query_number() { return (int)query_property( "number" ); }
mixed *stats() {
   return ::stats() + ({
      ({ "glass", glass, }),
   });
}
mapping int_query_static_auto_load() {
   return ([
      "::" : ::int_query_static_auto_load(),
      "glass" : glass,
   ]);
}
void init_static_arg( mapping map ) {
   if ( map["::"] )
      ::init_static_arg( map["::"] );
   if ( !undefinedp( map["glass"] ) )
      glass = map["glass"];
}
mixed query_static_auto_load() {
   if ( explode( file_name( this_object() ), "#" )[ 0 ] == "/obj/bottle" )
      return int_query_static_auto_load();
   return ([ ]);
}