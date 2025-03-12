#include <login_handler.h>
#include <command.h>
#include <player.h>
#define PROTECTION_LOG "/log/secure/playtesters/protection_log"
#define MAX_COUNTER 2
class playtester_data {
   int protect;
   int hp;
   string log_file;
   int log_death;
   int log_damage;
   int turn_off;
   int protection_counter;
   int room_protection;
}
inherit "/global/player";
int query_in_pt_arena();
private nosave class playtester_data _pt_data;
int query_pt_area (object ob) {
  string *file;
  if (strsrch (base_name (ob), "_pt") != -1) {
    return 1;
  }
  if (strsrch (base_name (ob), "_dev") != -1) {
    return 1;
  }
  file = explode (base_name (ob), "/");
  if (file[1] == "playtesters") {
    return 1;
  }
  return 0;
}
void create() {
   ::create();
   _pt_data = new(class playtester_data);
}
void move_player_to_start(string bong, int new_pl, string c_name, string ident, int go_invis) {
  if(!sscanf(file_name(previous_object()), "/secure/login#%*s") &&
     !sscanf(file_name(previous_object()), "/secure/nlogin#%*s"))
    return 0;
#ifndef NEW_DRIVER
#endif
  ::move_player_to_start(bong, new_pl, c_name, ident, go_invis);
  AddSearchPath(({ DIR_PLAYTESTER_CMDS }));
  if (PLAYTESTER_HAND->query_senior_playtester(query_name())) {
     AddSearchPath(({ DIR_SENIOR_PLAYTESTER_CMDS }));
  }
  if (PLAYTESTER_HAND->query_exec_access (query_name())) {
     AddSearchPath(({ DIR_EXEC_PLAYTESTER_CMDS }));
  }
}
int query_playtester() { return 1; }
string query_object_type(object) {
  if (PLAYTESTER_HAND->query_pt_exec(query_name())) {
    return "E";
  }
  if (PLAYTESTER_HAND->query_senior_playtester(query_name())) {
    return "P";
  }
  return "p";
}
int query_pt_protection() {
  if (_pt_data->room_protection) {
    return 2;
  }
  return _pt_data->protect;
}
int enable_pt_protection() {
  if (_pt_data->room_protection != 1) {
   log_file (PROTECTION_LOG, "%s: %s had room PT "
    "protection enabled by %s.\n", ctime(time()), this_player()->query_name(),
    base_name (environment (this_player())));
    tell_object (this_player(), "%^BOLD%^You have had your playtester "
      "protection enabled by an external source.  It will last until switched "
      "off by another external source.\n%^RESET%^");
    _pt_data->room_protection = 1;
    return 1;
  }
  return 0;
}
int disable_pt_protection() {
  if (_pt_data->room_protection == 1) {
   log_file (PROTECTION_LOG, "%s: %s had room PT "
    "protection disabled by %s.\n", ctime(time()), this_player()->query_name(),
    base_name (environment (this_player())));
    tell_object (this_player(), "%^BOLD%^The playtester protection enabled "
      "by an external source has been switched off.\n%^RESET%^");
    _pt_data->room_protection = 0;
    return 1;
  }
  return 0;
}
int enable_personal_pt_protection() {
  if (query_pt_protection()) {
    return 0;
  }
   _pt_data = new(class playtester_data);
   _pt_data->hp = ::query_hp();
   _pt_data->protect = 1;
   _pt_data->log_file = "/d/playtesters/log/pain";
   tell_room (environment (this_player()), this_player()->one_short()
      + " looks as if " + this_player()->query_pronoun() + " no longer has "
      "any fear of the risks of the real world.\n", this_player());
   log_file (PROTECTION_LOG, "%s: %s enabled PT "
    "protection (%s).\n", ctime(time()), this_player()->query_name(),
    base_name (environment (this_player())));
   if (_pt_data->turn_off) {
      remove_call_out(_pt_data->turn_off);
   }
   if (!query_pt_area (environment (this_player()))) {
      tell_object (this_player(), "%^BOLD%^You feel somewhat more secure, as if "
        "you can no longer be harmed by conventional weapons (This will "
        "only last a maximum of fifteen minutes).%^RESET%^\n");
     _pt_data->protection_counter = 0;
     _pt_data->turn_off = call_out("disable_personal_pt_protection", 5 * 60);
   }
   else {
      tell_object (this_player(), "%^BOLD%^You feel somewhat more secure, as if "
        "you can no longer be harmed by conventional weapons (This will "
        "last until you switch it off or leave a PT area).%^RESET%^\n");
  }
   return 1;
}
int disable_personal_pt_protection() {
  if (query_pt_protection() != 1) {
    return 0;
  }
  if (this_player()) {
    _pt_data->protection_counter = MAX_COUNTER;
  }
  if (_pt_data->protection_counter < MAX_COUNTER) {
    tell_object (this_player(), "%^BOLD%^You still have your PT protection "
      "enabled.\n%^RESET%^");
    log_file (PROTECTION_LOG, "%s: %s warned about still enabled PT "
      "protection (%s).\n", ctime(time()), this_player()->query_name(),
      base_name (environment (this_player())));
    _pt_data->turn_off = call_out("disable_personal_pt_protection", 5 * 60);
    _pt_data->protection_counter = _pt_data->protection_counter + 1;
    return 0;
  }
   _pt_data->turn_off = 0;
   _pt_data->protect = 0;
   _pt_data->protection_counter = 0;
   log_file (PROTECTION_LOG, "%s: %s disabled PT "
    "protection (%s).\n", ctime(time()), this_player()->query_name(),
    base_name (environment (this_player())));
   tell_object (this_player(), "%^BOLD%^You feel less secure in your "
    "indestructability.%^RESET%^\n");
   tell_room (environment (this_player()), this_player()->one_short()
      + " looks as if the risks of the real world are once again "
      "relevant.\n", this_player());
   return 1;
}
void pt_set_hp( int hp ) {
   _pt_data->hp = hp;
}
int pt_query_hp() {
   return _pt_data->hp;
}
object pt_make_corpse() {
   object corpse;
   corpse = clone_object( "/obj/corpse" );
   corpse->set_owner( 0, this_object() );
   corpse->set_ownership( query_name() );
   corpse->set_race_name( query_race() );
   if ( !query_race_ob() ) {
      corpse->set_race_ob( "/std/races/unknown" );
   } else {
      corpse->set_race_ob( query_race_ob() );
   }
   corpse->add_adjective( query_adjectives() );
   corpse->start_decay();
   return corpse;
}
object pt_do_death() {
   object corpse, flowers;
   DEATH->death_informer( this_object(), 0, _pt_data->log_file, 1 );
   tell_object( this_object(),
         "The Death of Playtesters sneaks up behind you and taps "
         "you on the shoulder.\n"
         "%^CYAN%^The Death of Playtesters says: MY, WE'VE BEEN A BIT "
         "CARELESS, HAVEN'T WE?%^RESET%^\n"
         "The Death of Playtesters coughs.\n"
         "%^CYAN%^The Death of Playtesters says: Sorry about the Voice.  "
         "We have to do that, you know.  Well, you should really be dead "
         "now, but the Playtesters' Union renegotiated the whole death deal "
         "with the powers that be.%^RESET%^\n" );
   call_out ("pt_set_hp", 0, query_max_hp());
   corpse = pt_make_corpse();
   corpse->move( environment( ) );
   flowers = clone_object( "/std/object" );
   flowers->set_name( "flowers" );
   flowers->set_short( "bunch of flowers" );
   flowers->add_alias( "bunch" );
   flowers->add_adjective( ({ "bunch", "of" }) );
   flowers->set_main_plural( "bunches of flowers" );
   flowers->add_plural( ({ "bunches", "bunches of flowers" }) );
   flowers->set_long( "This is a small bunch of nice flowers.\n" );
   flowers->set_weight( 5 + random( 10 ) );
   flowers->set_value( 0 );
   flowers->set_read_mess( "Rest In Peas", "common" );
   flowers->move( corpse );
   return corpse;
}
varargs int pt_adjust_hp( int hp, object attacker ) {
   _pt_data->hp += hp;
   if( ( hp < 0 || hp > 10 ) && _pt_data->log_damage && stringp( _pt_data->log_file ) )
      log_file( _pt_data->log_file, ctime( time() ) +": "+
                query_name() +" - "+ hp +" hitpoints.\n" );
   if( _pt_data->hp <= 0 && hp < 0) {
      pt_do_death();
   } else if( _pt_data->hp > ::query_max_hp() ) {
      _pt_data->hp = ::query_max_hp();
   }
   if( hp < 0 && _pt_data->hp > 0 && attacker && attacker != this_object() ) {
      if( 100 * _pt_data->hp < query_wimpy() * ::query_max_hp() ) {
         run_away();
      }
   }
   return _pt_data->hp;
}
void set_pt_log_file( string str ) {
   _pt_data->log_file = str;
}
string query_pt_log_file() {
   return _pt_data->log_file;
}
void enable_death_log() {
   _pt_data->log_death = 1;
}
void disable_death_log() {
   _pt_data->log_death = 0;
}
int query_log_death() {
   return _pt_data->log_death;
}
void enable_damage_log() {
   _pt_data->log_damage = 1;
}
void disable_damage_log() {
   _pt_data->log_damage = 0;
}
int query_log_damage() {
   return _pt_data->log_damage;
}
object do_death( object thing ) {
   if( query_pt_protection() || query_in_pt_arena())
      return pt_do_death();
   else
      return ::do_death( thing );
}
varargs int adjust_hp( int hp, object attacker ) {
   if( query_pt_protection() ) {
     return pt_adjust_hp( hp, attacker );
   } else {
      return ::adjust_hp( hp, attacker );
   }
}
int query_hp() {
   if( query_pt_protection() )
      return pt_query_hp();
   else
      return ::query_hp();
}
mixed *stats() {
   return ::stats() + ({
      ({ "PT hitpoints", _pt_data->hp }),
      ({ "PT protection", ( query_pt_protection() ? "On" : "Off" ) })
   });
}
string extra_score() {
   return ::extra_score() +
         "Your playtester protection is "+
         ( query_pt_protection() ? "on" : "off" ) +".\n";
}
int query_in_pt_arena() {
  if (!environment(this_object())) {
    return 0;
  }
  if (environment (this_object())->query_pt_arena()) {
    return 1;
  }
  return 0;
}
int advancement_restriction() {
  if (query_pt_protection()) {
    return 1;
  }
  if (query_in_pt_arena()) {
    return 1;
  }
  return 0;
}
varargs int adjust_xp(int number, int shared) {
  if ( advancement_restriction() && number > 0) {
    return 0;
  }
  return ::adjust_xp(number, shared);
}
void event_move_object(mixed from, mixed to) {
  ::event_move_object (from, to);
  if (query_pt_protection()) {
    if (query_pt_area(from) && !query_pt_area (to)) {
       _pt_data->protection_counter = MAX_COUNTER;
      if (_pt_data->turn_off) {
        remove_call_out(_pt_data->turn_off);
      }
      tell_object (this_player(), "%^BOLD%^You are now leaving a PT area.  "
        "Your protection is still on.\n%^RESET%^");
      log_file (PROTECTION_LOG, "%s: %s left a playtester area with protection "
        "still active (%s).\n", ctime(time()), this_player()->query_name(),
        base_name (environment (this_player())));
      _pt_data->turn_off = call_out("disable_pt_protection", 5 * 60);
    }
    else if (!query_pt_area (from) && query_pt_area (to)) {
      tell_object (this_player(), "%^BOLD%^You are now entering a PT area.  "
        "Your protection will not wear off until you leave or switch it "
        "off.\n%^RESET%^");
      if (_pt_data->turn_off) {
        remove_call_out(_pt_data->turn_off);
        _pt_data->protection_counter = 0;
      }
    }
  }
}
int query_player_killer() {
  if (query_in_pt_arena()) {
    return 1;
  }
  return ::query_player_killer();
}
int query_contractable() {
  return ::query_player_killer();
}