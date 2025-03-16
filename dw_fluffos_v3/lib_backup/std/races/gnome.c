inherit "/std/races/humanoid";
void setup() {
   set_name( "gnome" );
   set_long( "This is the race for gnomes.\n" );
   set_desc( "a short-looking gnome" );
   set_weight( 25 );
   set_height( 20 );
   set_sight( ({ 0, 5, 150, 200 }) );
   set_stats( ({ -2, 8, 0, 6, 0 }) );
}