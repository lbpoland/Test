# File: /lib/std/room/outside.c

#include <weather.h>
inherit "/std/room/basic_room";
#define FAST_CLEAN_UP 15
nosave int current_day;
nosave object sunlight;
nosave int day_light;
nosave string _climate;
nosave int next_weather_update;
nosave string weather_str;
private nosave string _weather_handler;
nosave int callout_handle;
nosave int room_stabilize;
private nosave int room_create_time;
private nosave int _fast_clean_up;
int clean_up_room( int flag );
int query_fast_clean_up();
void set_fast_clean_up(int fast_clean_up);
void set_weather_handler( string handler ) {
    _weather_handler = handler ;
}
string query_weather_handler() {
    return _weather_handler ;
}
int set_climate(string climate) {
  if(member_array(climate, CLIMATES) == -1)
    return 0;
  _climate = climate;
  return 1;
}
string query_climate() {
  if(!_climate)
    return DEFAULT_CLIMATE;
  return _climate;
}
void set_light_change(string s) {
    add_property("light change", s);
}
string query_light_change() {
    return query_property("light change");
}
string snow_look() {
   return _weather_handler->snow_string(this_object()) + ".";
}
string rain_look() {
   return _weather_handler->rain_string(this_object()) + ".";
}
string sleet_look() {
   return _weather_handler->sleet_string(this_object()) + ".";
}
string cloud_look() {
   return _weather_handler->cloud_string(this_object()) + ".";
}
void create() {
  set_fast_clean_up(1);
  do_setup++;
  ::create();
  do_setup--;
  set_room_size( 50 );
  add_property( "location", "outside" );
  add_property( "here", "on the ground" );
  _weather_handler = WEATHER ;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
  room_create_time = time();
  room_stabilize = 0;
}
int query_light() {
  int new_light;
  new_light = ( day_light * (int)_weather_handler->query_darkness
    ( this_object() ) ) / 100;
  if ( new_light != query_my_light() ) {
    ::set_light(new_light);
  }
  return ::query_light();
}
int query_visibility() {
   return _weather_handler->query_visibility(this_object());
}
int query_day_light() { return day_light; }
int set_light( int number ) {
  ::set_light(number);
  day_light = number;
}
string long( string word, int dark ) {
   int day_time;
   string ret;
   string obscure;
   mixed bit;
   ret = ::long( word, dark );
   day_time = (int)_weather_handler->query_day( this_object() );
   if ( day_time != current_day ) {
      if ( query_light_change() ) {
         call_other( this_object(), query_light_change(), current_day );
      }
   }
   obscure = this_object()->query_weather_obscured(day_time);
   if ( !day_time )
   {
      bit = query_night_long();
      if (functionp(bit)) {
         bit = evaluate(bit, word, dark);
      }
      ret = replace(ret, "$long$", bit);
      if (!obscure) {
         ret = (string)_weather_handler->query_moon_string() + ret;
      }
   } else {
      bit = query_long();
      if (functionp(bit)) {
         bit = evaluate(bit, word, dark);
      }
      ret = replace( ret, "$long$", bit);
   }
   if ( time() > next_weather_update ) {
      weather_str = _weather_handler->weather_string(this_object(), obscure) +".\n";
      next_weather_update = (int)_weather_handler->next_update();
   }
   return replace(ret, "$weather$",
                  this_player()->colour_event("weather", "%^ORANGE%^")+
                  weather_str+ "%^RESET%^");
}
mixed *stats() {
  return ::stats() + ({
    ({ "day light", day_light, }),
  });
}
object *find_inv_match( string word, object looker ) {
  int daylight;
  if((word == "sunlight") || (word == "daylight"))
  {
    daylight = this_object()->query_light();
    if(daylight == 0)
    {
      if(sunlight)
      {
        remove_hidden_object(sunlight);
        sunlight->dest_me();
        sunlight = 0;
      }
      return ::find_inv_match( word, looker );
    }
    if(!sunlight)
    {
      sunlight = clone_object("/std/object");
      sunlight->set_name("sunlight");
      sunlight->set_weight(0);
      sunlight->reset_get();
      sunlight->add_alias("daylight");
      add_hidden_object(sunlight);
    }
    if(daylight < 25)
    {
      sunlight->set_long("The light here is currently quite dim.\n");
    } else {
      sunlight->set_long("What do you want to look at the light for?  "+
        "It's... well, light really.\n");
    }
  }
  return ::find_inv_match( word, looker );
}
void dest_me() {
  if(sunlight) {
    sunlight->dest_me();
  }
  ::dest_me();
}
#ifdef FAST_CLEAN_UP
void event_exit(object ob, string message, object to) {
  if(!room_stabilize) {
    remove_call_out(callout_handle);
    callout_handle = call_out("clean_up_room", FAST_CLEAN_UP, 0);
  }
}
string *query_zones() {
  if(!room_stabilize)
    callout_handle = call_out("clean_up_room", FAST_CLEAN_UP, 0) ;
  return ::query_zones();
}
int clean_up_room(int flag) {
  object *obs, ob;
  int elapsed_time = time() - room_create_time;
  if(room_stabilize || !query_fast_clean_up() ||
     this_object()->query_keep_room_loaded())
    return 0;
  callout_handle = 0 ;
  obs = filter(all_inventory(this_object()),
               (: !living($1) || (userp($1)) ||
                !$1->query_property("transient") ||
                sizeof($1->query_attacker_list()) ||
                $1->cannot_walk() :));
  if(sizeof(all_inventory(this_object())) ||
     elapsed_time > (FAST_CLEAN_UP * 3)) {
    room_stabilize = 1;
    return 1;
  }
  obs = filter(all_inventory(this_object()),
               (: $1->query_property("transient") :));
  foreach(ob in obs)
    if(ob->query_property("hospital"))
      ob->move(ob->query_property("hospital"), "$N wander$s in.",
               "$N wander$s out.");
  dest_me();
  return 0;
}
void set_fast_clean_up(int number) {
   _fast_clean_up = number;
}
int query_fast_clean_up() {
   return _fast_clean_up;
}
#endif