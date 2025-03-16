inherit "/std/races/fish_base";
void setup() {
   set_name( "guppy" );
   set_long( "Fish,  yes.  A fish.  Nice generic standard fish thing.\n" );
   set_height( 15 );
   set_weight( 40 );
   set_desc( "a beautiful looking guppy" );
   set_stats( ({ -2, 14, -4, -4, -6 }) );
}
void start_player( object thing ) {
   ::start_player( thing );
   thing->add_property( "gills", 1 );
   thing->tactics( "response dodge" );
}
int lives_in_water() { return 1; }