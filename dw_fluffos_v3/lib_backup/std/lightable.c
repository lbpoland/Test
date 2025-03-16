#include <fuel_handler.h>
#define HOLD_COMMAND "/cmds/living/ho_ld"
#define DEPARTURES "/room/departures"
inherit "/obj/weapon";
int max_fuel, fuel, lit, brightness, time, hold;
string empty_mess;
mixed fuel_messages;
int set_lit(int);
void create() {
   ::create();
   add_extra_look( this_object() );
}
void init() {
   this_player()->add_command( "light", this_object() );
   this_player()->add_command( "dowse", this_object() );
   this_player()->add_command( "extinguish", this_object() );
}
varargs string short( int dark ) {
   if( lit )
      return "lit "+ ::short( dark );
   else
      return ::short( dark );
}
void out_of_fuel() {
   object env;
   fuel = 0;
   lit = 0;
   set_lit( 0 );
   FUEL_HANDLER->remove_burner( this_object() );
   if( !environment() ) return;
   env = environment();
   if( living( env ) ) {
      tell_object( env, the_short() +" goes out.\n" );
      tell_room( environment( env ),
            env->the_short() +"'s "+ short() +" goes out.\n", env );
   } else {
      tell_room( env, the_short() +" goes out.\n" );
   }
}
void delayed_light() {
   lit = 1;
}
int hold_thing() {
   if( !query_wielded() )
      return HOLD_COMMAND->cmd( ({ this_object() }) );
   else
      return 1;
}
int set_lit( int i ) {
   if( !i ) {
      if( !query_property( "unextinguishable" ) ) {
         lit = 0;
         FUEL_HANDLER->remove_burner( this_object() );
         remove_adjective( "lit" );
         set_light( 0 );
         return 0;
      }
   } else {
      if( !query_property( "unlightable" ) && fuel > 0 ) {
         if( lit )
            return 1;
         if( hold && !hold_thing() )
            return 0;
         call_out( (: delayed_light :), 2 );
         FUEL_HANDLER->add_burner( this_object() );
         add_adjective( "lit" );
         set_light( brightness );
         return 1;
      }
   }
}
mixed set_holder( object ob, int pos ) {
   if( lit && hold && !ob && environment( this_player() )
       && file_name( environment( this_player() ) ) != DEPARTURES )
      if( !set_lit( 0 ) ) {
         tell_object( this_player(), "You extinguish "+ the_short() +".\n" );
         tell_room( environment( this_player() ), this_player()->the_short() +
               " extinguishes "+ the_short() +".\n", this_player() );
     }
   return ::set_holder( ob, pos );
}
int query_lit() {
   return lit;
}
int do_light() {
   if( lit )
      return notify_fail( the_short() +" is already lit.\n" );
   if( !fuel )
      return notify_fail( the_short() +" "+ empty_mess +"\n" );
   if( !set_lit( 1 ) )
      return notify_fail( "You cannot light "+ the_short() +".\n" );
   this_player()->add_succeeded_mess( this_object(), "$N $V $D.\n", ({ }) );
   return 1;
}
int do_dowse() {
   if( !lit )
      return notify_fail( the_short() +" is not lit.\n" );
   if( set_lit( 0 ) )
      return notify_fail( "You cannot extinguish "+ the_short() +".\n" );
   this_player()->add_succeeded_mess( this_object(), "$N $V $D.\n", ({ }) );
   return 1;
}
int do_extinguish() {
   return do_dowse();
}
void set_fuel_messages( mixed msgs ) {
   fuel_messages = msgs;
}
mixed query_fuel_messages() {
   return fuel_messages;
}
void set_max_fuel( int i ) {
   max_fuel = i;
}
int query_max_fuel() {
   return max_fuel;
}
void set_fuel( int i ) {
   fuel = i;
   if( fuel > max_fuel )
      fuel = max_fuel;
}
int query_fuel() {
   return fuel;
}
string current_fuel_message() {
   mixed messages;
   int fuel_percent, size, i;
   string fuel_string = "";
   if( fuel < 1 )
      return "It "+ empty_mess;
   messages = query_fuel_messages();
   size = sizeof( messages );
   if( !size )
      return "This item needs a creator.  It is broken and lonely.";
   if( size < 2 )
      return messages[0];
   fuel_percent = fuel * 99 / max_fuel;
   if( intp( messages[1] ) ) {
      for( i = 1; i < size; i += 2 ) {
         if( messages[i] > fuel_percent ) {
            fuel_string = messages[i-1];
            break;
         }
      }
      if( fuel_string == "" )
         fuel_string = messages[ size - 2 ];
   } else {
      fuel_string = messages[ fuel_percent * size / 100 ];
   }
   return fuel_string;
}
void set_empty_mess( string msg ) {
   empty_mess = msg;
}
string query_empty_mess() {
   return empty_mess;
}
void set_brightness( int i ) {
   brightness = i;
}
int query_brightness() {
   return brightness;
}
void set_hold_required( int hands ) {
   hold = hands;
}
int query_hold_required() {
   return hold;
}
string extra_look() {
   string lit_str;
   if( lit )
      lit_str = "It is lit.  ";
   else
      lit_str = "It is not currently lit.  ";
   return lit_str + current_fuel_message() +"\n";
}
mixed query_dynamic_auto_load() {
   return ([ "::" : ::query_dynamic_auto_load(),
             "fuel" : fuel,
             "lit" : lit,
           ]);
}
void init_dynamic_arg(mapping arg, object bing ) {
   fuel = arg["fuel"];
   ::init_dynamic_arg(arg["::"], bing);
   set_lit(arg["lit"]);
}
void consume_fuel() {
   fuel -= FUEL_TIME;
   if( fuel < 1 )
      out_of_fuel();
}
int query_value() {
   return (int)( ::query_value() * fuel / max_fuel );
}
varargs int move( mixed dest, string messin, string messout ) {
   object destination;
   if( objectp( dest ) ) {
      destination = dest;
   } else {
      destination = load_object( dest );
   }
   if( ( inherits( "/std/container", destination ) &&
         !living( destination ) ) ||
       inherits( "/std/uwater", destination ) ||
       inherits( "/std/water_inside", destination ) ||
       inherits( "/std/water_outside", destination ) ) {
      set_lit( 0 );
   }
   return ::move( dest, messin, messout );
}