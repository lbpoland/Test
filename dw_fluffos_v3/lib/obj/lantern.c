#include <fuel_handler.h>
inherit "/std/object";
#define BRIGHTNESS      60
#define FUEL_PER_TICK  FUEL_TIME
#define MAX_FUEL 3600
int  fuel_left;
int  is_lit;
void create(){
  ::create();
}
string short( int i ) {
  if ( is_lit )
    return ::short( 0 ) + " (lit)";
  return ::short( 0 );
}
int do_extinguish() {
   if ( !is_lit ) {
      this_player()->add_failed_mess(this_object(), "$D is not lit.\n", ({ }));
      return 0;
   }
   FUEL_HANDLER->remove_burner( this_object() );
   is_lit = 0;
   set_light( 0 );
   return 1;
}
int do_dowse() {
   return do_extinguish();
}
int do_light() {
   if ( is_lit ) {
      this_player()->add_failed_mess( this_object(), "$D is already lit.\n",
                                     ({ }) );
      return 0;
   }
   if ( fuel_left <= 0 ) {
      this_player()->add_failed_mess( this_object(), "$D is out of fuel.\n",
                                     ({ }) );
      return 0;
   }
   FUEL_HANDLER->add_burner( this_object() );
   is_lit = 1;
   set_light( BRIGHTNESS );
   return 1;
}
void init() {
   this_player()->add_command("light", this_object());
   this_player()->add_command("extinguish", this_object());
   this_player()->add_command("dowse", this_object());
}
void out_of_fuel() {
   object env;
   is_lit    = 0;
   fuel_left = 0;
   env = environment( this_object() );
   FUEL_HANDLER->remove_burner( this_object() );
   set_light( 0 );
   if ( interactive( env ) ) {
      write( poss_short() +" burns out.\n" );
      tell_room( environment(env), poss_short() +" burns out.\n", env );
   } else
      say( poss_short() +" burns out.\n" );
}
void consume_fuel() {
   fuel_left -= FUEL_PER_TICK;
   switch ( fuel_left ) {
    case -10000 .. 0:
      out_of_fuel();
      break;
    default:
   }
}
string pretty_plural( object thing) {
  if ( is_lit )
    return ::pretty_plural(thing) + " (lit)";
  return ::pretty_plural(thing);
}
void dest_me() {
   set_light( 0 );
   FUEL_HANDLER->remove_burner( this_object() );
   ::dest_me();
}
mixed *stats() {
  return ::stats() + ({
    ({ "fuel" , fuel_left, }),
    ({ "is lit", is_lit, }),
   });
}
mapping query_dynamic_auto_load() {
   return ([ "::" : ::query_dynamic_auto_load(),
             "fuel left" : fuel_left,
             "is lit" : is_lit,
          ]);
}
void init_dynamic_arg( mapping arg ) {
   fuel_left = arg["fuel left"];
   if ( arg[ "is lit" ] ) {
      FUEL_HANDLER->add_burner( this_object() );
      is_lit = 1;
      set_light(BRIGHTNESS);
   }
   ::init_dynamic_arg( arg["::"] );
}
int query_fuel_left() {
    return fuel_left;
}
void set_fuel_left( int i ) {
    if ( i > MAX_FUEL ) {
        i = MAX_FUEL;
    }
    fuel_left = i;
}
int query_max_fuel() {
    return MAX_FUEL;
}