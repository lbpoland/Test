# File: /lib/std/room/furniture/inherit/furniture_base.c

#include <move_failures.h>
#include <position.h>
#include <housing.h>
#include <room/placement.h>
void add_property(string name, mixed type);
mixed query_property(string name);
string one_short();
int query_light_needs_inform();
void inform_of_light_level_change(object ob);
private nosave mapping _allowed_room_verbs;
private nosave string *_allowed_positions;
private nosave string _bonded;
void create() {
  _allowed_positions = ({ });
  if (base_name(this_object()) + ".c" != __FILE__) {
    if ( !query_property( "shop type" ) ) {
      add_property( "shop type", "furniture" );
    }
    this_object()->set_max_cond(100000);
    this_object()->set_cond(100000);
  }
  if(clonep(this_object()) &&
     base_name(this_object())[0..14] != "/obj/furnitures" &&
     base_name(this_object())[0..2] != "/w/" &&
     strsrch (base_name(this_object()), "_dev") == -1 &&
     strsrch (base_name(this_object()), "_pt") == -1) {
    call_out("move", 2, "/room/void");
  }
}
int query_furniture() {
   return 1;
}
void set_allowed_positions(string *positions) {
   _allowed_positions = positions;
}
void remove_allowed_positions( string *positions ){
  _allowed_positions -= positions;
}
string* query_allowed_positions() {
   return _allowed_positions;
}
void set_allowed_room_verbs( mapping allowed ) {
  _allowed_room_verbs = allowed;
}
mapping query_allowed_room_verbs() {
   return _allowed_room_verbs;
}
string query_position_string(string position_type) {
  if(member_array(position_type, _allowed_positions) != -1) {
    return one_short();
  }
  return 0;
}
void set_bonded(string person) {
   _bonded = person;
}
string query_bonded() {
   return _bonded;
}
string query_owner() {
   return _bonded;
}
int is_allowed_to_mess(object player) {
  mixed *stuff;
  string occupier;
  if(environment() && !function_exists("query_owner", environment()))
    return 1;
  if(player->query_creator())
    return 1;
  if(player->query_caster())
    player = find_player(player->query_caster());
  if(player->query_owner())
    player = player->query_owner();
  if (player && player->query_name() == _bonded)
    return 1;
  stuff = this_object()->query_property("dropped");
  if(player && sizeof(stuff) && stuff[0] == player->query_name())
    return 1;
  if(player && environment()) {
    if(environment()->test_occupier(player->query_name()))
      return 1;
    if(environment()->query_owner() == "For Sale" ||
       environment()->query_owner() == "Under Offer")
      return 1;
    occupier = HOUSING->query_owner(base_name(environment()));
    if(pk_check(player, occupier, 1))
      return 0;
  }
  return (!_bonded);
}
int move_check(object dest) {
  if (living(dest)) {
    if (!is_allowed_to_mess(dest)) {
       return 0;
    }
  } else if (this_player() && environment()) {
    if (!(living(environment()) && dest == environment(environment()))) {
       if (!is_allowed_to_mess(this_player())) {
          return 0;
       }
    }
  }
  return 1;
}
string query_placement_verb() {
   return query_property(PLACEMENT_CURRENT_ROOM_VERB);
}
string query_placement_other() {
   return query_property(PLACEMENT_CURRENT_ROOM_OTHER);
}
string query_placement_position() {
   return query_property(PLACEMENT_CURRENT_ROOM_POSITION);
}
int query_placement_immovable() {
   return query_property(PLACEMENT_IMMOVABLE);
}
int is_placed() {
   return query_placement_position() &&
     stringp(query_placement_verb()) &&
     stringp(query_placement_other());
}
void set_placement_verb(string verb) {
   add_property(PLACEMENT_CURRENT_ROOM_VERB, verb);
}
void set_placement_other(string other) {
   add_property(PLACEMENT_CURRENT_ROOM_OTHER, other);
}
void set_placement_position(string position) {
   add_property(PLACEMENT_CURRENT_ROOM_POSITION, position);
}
int set_placement_immovable() {
   return query_property(PLACEMENT_IMMOVABLE);
}