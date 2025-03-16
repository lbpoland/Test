#include <bits_controller.h>
#include <weather.h>
inherit "/obj/food";
#define CHILL -5
#define CHILL_TIME 10
#define MELT_RATE_DEFAULT 6
#define WATER "/obj/food/beverages/water.food"
#define _LOOKUP_RATE ({ 60, 57, 54, 51, 48, 42, 36, 30, 27, 24, \
                        20, 18, 16, 14, 12, 10,  9,  8,  7,  6, \
                         6,  6,  6,  5,  5,  5,  4,  4,  4,  3, \
                         3,  3,  3,  3,  3,  3,  3,  3,  3,  2, \
                         2,  2,  2,  2,  2,  2,  2,  2,  2,  1  })
private int _melt_level;
private int _original_melt_level;
private int _melt_rate;
private int _melt_counter;
private int _callout_id;
private string _melt_result;
void create();
void set_melt_result( string result );
string query_melt_result();
void set_melt_rate( int rate );
int query_melt_rate();
int query_melt_level();
private void setup_callout();
protected void do_melt();
void create() {
   do_setup++;
   ::create();
   do_setup--;
   _melt_rate = MELT_RATE_DEFAULT;
   _melt_counter = 0;
   set_melt_result( WATER );
   set_decay_speed( 1 );
   setup_callout();
   if ( !do_setup ) {
      this_object()->setup();
   }
   _melt_level = ( this_object()->query_weight() ) * 10;
   _original_melt_level = _melt_level;
}
void set_melt_result( string result ) {
   _melt_result = result;
}
string query_melt_result() {
   return _melt_result;
}
void set_melt_rate( int rate ) {
   _melt_rate = rate;
}
int query_melt_rate() {
   return _melt_rate;
}
int query_melt_level() {
   return _melt_level;
}
private void setup_callout() {
   if( _callout_id ) {
      remove_call_out( _callout_id );
   }
   _callout_id = call_out( "do_melt", _melt_rate );
}
protected void do_melt() {
   object liquid;
   object room, ob;
   int environment_temp, current_weight;
   ob = environment( this_object() );
   if( !ob ) {
      return;
   }
   room = ob;
   while( ob = environment( ob ) ) {
      room = ob;
   }
   if( room->query_property( "location" ) == "outside" ) {
      environment_temp = WEATHER->query_temperature( room );
   }
   else if( room->query_name() == "clone_on_demand-store" ) {
      environment_temp = 0;
   }
   else {
      environment_temp = 20 + room->query_property( "warmth" );
   }
   if( environment_temp > 1 ) {
      if( environment_temp > 50 ) {
         _melt_rate = 1;
      }
      else {
         _melt_rate = _LOOKUP_RATE[ environment_temp ];
      }
      _melt_level = _melt_level - 1;
      _melt_counter = _melt_counter + 1;
      if ( _melt_counter >= 10 ) {
         liquid = clone_object( _melt_result );
         liquid->set_amount( 20 );
         liquid->move( environment( this_object() ) );
         current_weight = this_object()->query_weight();
         if( current_weight <= 1 ) {
            this_object()->move( "/room/rubbish" );
         }
         else {
            this_object()->set_weight( current_weight - 1 );
         }
         _melt_counter = 0;
      }
   }
   _callout_id = call_out( "do_melt", _melt_rate );
}
string query_short_rotten_adjective() {
   string ret;
   int bing;
   bing = 100 - ( ( 100 * _melt_level ) / _original_melt_level );
   ret = "";
   switch ( bing ) {
   case 0..1:
      break;
   case 2..20:
      ret = "slightly melted " + ret;
      break;
   case 21..45:
      ret = "partially melted " + ret;
      break;
   case 46..55:
      ret = "half melted " + ret;
      break;
   case 56..80:
      ret = "mostly melted " + ret;
      break;
   case 81..100:
      ret = "almost completely melted " + ret;
      break;
   }
   return ret;
}
string query_long_decay_level() {
   string ret;
   int bing;
   bing = 100 - ( ( 100 * _melt_level ) / _original_melt_level );
   ret = "";
   switch ( bing ) {
   case 0..1:
     if( query_collective() && query_amount() > 1 )
        ret += "They have not yet begun to melt.\n";
     else
        ret += "It has not yet begun to melt.\n";
     break;
   case 2..20:
      if( query_collective() && query_amount() > 1 )
         ret += "They have melted slightly.\n";
      else
         ret += "It has melted slightly.\n";
      break;
   case 21..45:
      if( query_collective() && query_amount() > 1 )
         ret += "They have partially melted away.\n";
      else
         ret += "It has partially melted away.\n";
      break;
   case 46..55:
      if( query_collective() && query_amount() > 1 )
         ret += "They are half melted away.\n";
      else
         ret += "It is half melted away.\n";
      break;
   case 56..80:
      if( query_collective() && query_amount() > 1 )
         ret += "They have mostly melted away.\n";
      else
         ret += "It has mostly melted away.\n";
      break;
   case 81..100:
      if( query_collective() && query_amount() > 1 )
         ret += "They have almost complete melted away.\n";
      else
         ret += "It has almost completely melted away.\n";
      break;
   }
    return ret;
}
varargs int do_eat( int no_mess ) {
   this_player()->add_property( "warmth", CHILL, CHILL_TIME );
   return( ::do_eat( no_mess ) );
}
int do_apply( object * things ) {
   int i;
   if( i = ::do_apply( things ) ) {
      things[ 0 ]->add_property( "warmth", CHILL, CHILL_TIME );
   }
   return i;
}
int do_rub( object * things ) {
   int i;
   if( i = ::do_rub( things ) ) {
      things[ 0 ]->add_property( "warmth", CHILL, CHILL_TIME );
   }
   return i;
}
mixed *stats()
{
   mixed *args;
   args =::stats() + ({ ({ "melt level", _melt_level }),
                        ({ "melt result", _melt_result }),
                        ({ "original melt level", _original_melt_level }),
                        ({ "melt rate", _melt_rate }),
                        ({ "melt counter", _melt_counter }),
                        ({ "callout id", _callout_id }) });
   return args;
}
mapping int_query_static_auto_load() {
   return ([ "::" : ::int_query_static_auto_load(),
             "melt_level" : _melt_level,
             "melt_result" : _melt_result,
             "original melt level" : _original_melt_level,
             "melt rate" : _melt_rate,
             "melt counter" : _melt_counter,
             "callout id" : _callout_id ]);
}
mapping query_static_auto_load()
{
   if ( ( base_name( this_object() ) != "/obj/food" )
       && !query_continuous() ) {
      return 0;
   }
   return int_query_static_auto_load();
}
void init_static_arg( mapping map )
{
   if ( !mapp( map ) ) {
      return;
   }
   if ( map[ "::" ] ) {
      ::init_static_arg( map[ "::" ] );
   }
   _melt_level = map[ "melt_level" ];
   _melt_result = map[ "melt_result" ];
   _original_melt_level = map[ "original melt level" ];
   _melt_rate = map[ "melt rate" ];
   _melt_counter = map[ "melt counter" ];
   _callout_id = map[ "callout id" ];
}
mapping query_dynamic_auto_load()
{
   return ([ "::" : ::query_dynamic_auto_load(),
             "melt_level" : _melt_level,
             "melt_result" : _melt_result,
             "original melt level" : _original_melt_level,
             "melt rate" : _melt_rate,
             "melt counter" : _melt_counter,
             "callout id" : _callout_id ]);
}
void init_dynamic_arg( mapping map, object )
{
   if ( !mapp( map ) ) {
      return;
   }
   if ( map[ "::" ] ) {
      ::init_dynamic_arg( map[ "::" ] );
   }
   _melt_level = map[ "melt_level" ];
   _melt_result = map[ "melt_result" ];
   _original_melt_level = map[ "original melt level" ];
   _melt_rate = map[ "melt rate" ];
   _melt_counter = map[ "melt counter" ];
   _callout_id = map[ "callout id" ];
}
int query_liquid() {
   return 0;
}
void set_liquid() {
}
void do_decay() {
   return;
}
int query_decays() {
   return 0;
}
int query_decay_speed() {
   return 0;
}
int query_decay_level() {
   return 0;
}
void set_decay_speed( int decay ) {
  return( ::set_decay_speed( 1 ) );
}
int do_cure() {
   return 0;
}
int query_cured() {
   return 0;
}
int do_dry() {
   return 0;
}
int query_dried() {
   return 0;
}
int query_rotten() {
   return 0;
}
void set_splashable() {
   return;
}