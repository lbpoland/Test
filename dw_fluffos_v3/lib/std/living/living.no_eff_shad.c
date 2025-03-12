#include <dirs.h>
#include <drinks.h>
#include <living.h>
#include <move_failures.h>
#include <player.h>
#include <tune.h>
#include <position.h>
#include <obj_parser.h>
inherit "/std/container";
inherit "/std/living/armour";
inherit "/std/living/carrying";
inherit "/std/living/combat";
inherit "/std/living/force";
inherit "/std/living/gender";
inherit "/std/living/health";
inherit "/std/living/holding";
inherit "/std/living/money";
inherit "/std/living/skills";
inherit "/std/living/spells";
inherit "/std/living/crafts";
inherit "/std/living/stats";
inherit "/std/living/respond_cmd";
inherit "/std/living/nationality";
#define VERBOSE_TYPES ({"combat", "look", "score", "names", "htell", "finger"})
#define MAX_FAVOUR 100
class living_data {
  int handicap;
  int burden;
  object* followers;
  class obj_match_context it_them;
  object* to_drop;
  int burden_call;
}
class messages {
   string msgout;
   string msgin;
   string mmsgout;
   string mmsgin;
}
private int alignment;
private class messages _messages;
private mixed *facing;
private mapping verbose;
private mapping abs_facing = ABS_FACING;
private mapping lengthen = LENGTHEN;
private string deity;
private mapping deity_favour;
private nosave class living_data _liv_data;
void return_to_default_position(int leaving);
void set_position(string name);
void set_position_on(mixed ob);
void set_position_multiple(int mult);
void set_position_type(string type);
object query_position_on();
protected mixed command(string);
private nosave string position;
private nosave mixed default_position;
private
nosave int always_use_default_position;
private nosave mixed position_on;
void create() {
   string t;
   _liv_data = new(class living_data);
   _messages = new(class messages);
   crafts::create();
   container::create();
   armour::create();
   combat::create();
   health::create();
   holding::create();
   skills::create();
   spells::create();
   respond_cmd::create();
   enable_commands();
   reset_can_export_inventory();
   reset_effects();
   _messages->msgin = "$N arrive$s from $F.";
   _messages->msgout = "$N leave$s $T.";
   _messages->mmsgin = "$N appear$s out of the ground.";
   _messages->mmsgout = "$N disappear$s in a puff of smoke.";
   _liv_data->followers = ({ });
   verbose = ([ ]);
   set_max_items(50);
   _liv_data->to_drop = ({ });
   foreach(t in VERBOSE_TYPES) {
      verbose[t] = 1;
   }
   facing = ({ 0, ({ "north", "northeast", "east", "southeast", "south",
         "southwest", "west", "northwest" }), ({ "up", "down" }) });
   position = STANDING;
   add_adjective("living");
}
void heart_beat() {
  stats::heart_beat();
  combat::heart_beat();
}
string query_pronoun() {
   return gender::query_pronoun();
}
string query_possessive() {
   return gender::query_possessive();
}
string query_objective() {
   return gender::query_objective();
}
varargs int query_weight(int actual) {
  if(!actual && this_object()->query_property("dead"))
    return 0;
  return stats::query_weight();
}
int query_burden() {
  return _liv_data->burden;
}
int query_handicap() { return _liv_data->handicap; }
void calc_burden() {
  int new_handicap;
  int burden;
  object thing;
  mapping hands;
  _liv_data->burden_call = 0;
  update_loc_weight();
  burden = query_loc_weight();
  foreach(thing in query_wearing())
    burden -= (int)thing->query_complete_weight() / 2;
  hands = ([ ]);
  foreach(thing in query_holding())
    if(objectp(thing))
      hands[thing]++;
  foreach(thing in keys(hands))
    burden += (int)thing->query_complete_weight() / hands[thing];
  if(!query_max_weight()) {
    this_object()->reset_carry_cap();
    _liv_data->burden = 50;
  } else
    _liv_data->burden = (100 * burden) / query_max_weight();
  new_handicap = (_liv_data->burden / 25) - 1;
  if(new_handicap < 0)
    new_handicap = 0;
  if ( _liv_data->handicap != new_handicap ) {
    adjust_bonus_dex( _liv_data->handicap - new_handicap );
    _liv_data->handicap = new_handicap;
  }
}
string burden_string() {
  switch (_liv_data->handicap) {
  case 0 :
    return "unburdened";
  case 1 :
    return "burdened";
  case 2 :
    return "heavily burdened";
  case 3 :
    return "very heavily burdened";
  default :
    return "incredibly heavily burdened";
  }
}
void living_commands() {
#if efun_defined(add_action)
   add_action( "exit_command", "*", 1 );
#endif
}
void eat_this( object food ) {
  this_object()->bypass_queue();
  command( "eat " + file_name( food ) );
}
int test_add(object ob, int flag) {
  if(sizeof(all_inventory(this_object())) > query_max_items())
    return 0;
  return !flag;
}
int test_remove( object ob, int flag, mixed dest ) {
   object thing;
   if ( flag ) {
      return 0;
   }
   if ( !this_player() || ( this_player() == this_object() ) ) {
      return !flag;
   }
   if ( stringp( dest ) ) {
      thing = find_object( dest );
   }
   if ( objectp( dest ) ) {
      thing = dest;
      dest = file_name( dest );
   }
   if ( thing->query_corpse() || ( dest == "/room/rubbish" ) ) {
      return !flag;
   }
   if ( sizeof( filter_array( previous_object( -1 ),
         (: $1->query_theft_command() :) ) ) ) {
      return !flag;
   }
   if ( !query_property( PASSED_OUT ) ) {
      return 0;
   }
   if ( !pk_check( this_player(), this_object() ) ) {
      event( environment( this_player() ), "theft", this_player(),
            this_object(), ob );
      return !flag;
   }
   write( "An unseen force stays your hand.\n" );
   return 0;
}
int query_al() { return alignment; }
void set_al( int number ) { alignment = number; }
int adjust_al( int number ) {
   alignment += number;
   if ( alignment < -MAX_AL ) {
      alignment = -MAX_AL;
   }
   if ( alignment > MAX_AL ) {
      alignment = MAX_AL;
   }
   return alignment;
}
int adjust_alignment( int number ) {
  int change;
  change = - (number + alignment/5);
  change /= 20;
  return adjust_al( change );
}
string align_string() {
   switch ( alignment ) {
      case -MAX_AL .. -5001 : return "extremely good"; break;
      case -5000 .. -2501 : return "very good"; break;
      case -2500 .. -1251 : return "quite good"; break;
      case -1250 .. -601 : return "good"; break;
      case -600 .. -301 : return "barely good"; break;
      case -300 .. 300 : return "neutral"; break;
      case 301 .. 600 : return "barely evil"; break;
      case 601 .. 1250 : return "evil"; break;
      case 1251 .. 2500 : return "quite evil"; break;
      case 2501 .. 5000 : return "very evil"; break;
      default : return "extremely evil"; break;
   }
}
string query_deity() { return deity; }
void set_deity( string word ) { deity = word; }
string query_msgin() { return _messages->msgin; }
string query_msgout() { return _messages->msgout; }
int set_msgin(string str) {
   if (strsrch(str, "$N") == -1 || strsrch(str, "$F") == -1) {
      return 0;
   }
   _messages->msgin = str;
   return 1;
}
int set_msgout(string str) {
   if (strsrch(str, "$N") == -1 || strsrch(str, "$T") == -1) {
      return 0;
   }
   _messages->msgout = str;
   return 1;
}
string query_mmsgin() { return _messages->mmsgin; }
string query_mmsgout() { return _messages->mmsgout; }
int set_mmsgin(string str) {
   if (strsrch(str, "$N") == -1) {
      return 0;
   }
   _messages->mmsgin = str;
   return 1;
}
int set_mmsgout(string str) {
   if (strsrch(str, "$N") == -1) {
      return 0;
   }
   _messages->mmsgout = str;
   return 1;
}
mixed *query_facing() { return copy( facing ); }
void set_facing( mixed *args ) { facing = args; }
string find_rel( string word, int from ) {
  int i;
  i = member_array( word, facing[ 1 ] );
  if ( i != -1 ) {
    i = ( i + 8 - facing[ 0 ] ) % 8;
    return REL_DIRS[ 3 * i + from ];
  }
  i = member_array( word, facing[ 2 ] );
  if ( i != -1 ) {
    return ({ "up", "down" })[ i ];
  }
  return word;
}
string find_abs( string word ) {
  int i;
  i = member_array( word, REL_DIRS );
  if ( i != -1 ) {
    i = ( i / 3 + facing[ 0 ]) % 8;
    return facing[ 1 ][ i ];
  }
  i = member_array( word, ({ "up", "down" }) );
  if ( i != -1 ) {
    return facing[ 2 ][ i ];
  }
  return word;
}
string reorient_rel( string word ) {
  int i;
  i = member_array( word, REL_DIRS );
  if ( i != -1 ) {
    i = ( i / 3 + facing[ 0 ] ) % 8;
    facing[ 0 ] = i;
    return facing[ 1 ][ i ];
  }
  i = member_array( word, ({ "up", "down" }) );
  if ( i != -1 ) {
    return facing[ 2 ][ i ];
  }
  return word;
}
void reorient_abs( string verb ) {
  if ((ABS_FACING)[verb]) {
    facing[0] = (ABS_FACING)[verb] % 8;
  }
}
void set_dragging( object thing ) { add_property("dragging", thing); }
object query_dragging() { return query_property("dragging"); }
void reset_dragging() { add_property("dragging", 0); }
int room_look() {
   if ( query_property( UNKNOWN_MOVE ) || !( interactive( this_object() ) ||
         this_object()->query_slave() ) )
      return 0;
   if(!mapp(verbose))
     verbose = ([ ]);
   if(verbose && verbose["look"]) {
      this_object()->ignore_from_history( "look" );
      this_object()->bypass_queue();
      command( "look" );
   } else {
      this_object()->ignore_from_history( "glance" );
      this_object()->bypass_queue();
      command( "glance" );
   }
   return 1;
}
int query_verbose(string type) {
  if(!verbose || !mapp(verbose)) {
    verbose = ([ ]);
  }
  return verbose[type];
}
void set_verbose(string type, int val) {
  if(!verbose || !mapp(verbose)) {
    verbose = ([ ]);
  }
  if(member_array(type, VERBOSE_TYPES) != -1) {
    verbose[type] = val;
  }
}
string *query_verbose_types() {
  return VERBOSE_TYPES;
}
varargs int move_with_look( mixed dest, string messin, string messout ) {
   return_to_default_position(1);
   if ( (int)this_object()->move( dest, messin, messout ) != MOVE_OK )
      return 0;
   room_look();
   return_to_default_position(1);
   return 1;
}
varargs int exit_command( string word, mixed verb, object thing, int redirection ) {
   string special_mess, *bits, *exits, redirect;
   int temp;
   if ( !environment() ) {
      return 0;
   }
   if ( !verb ) {
      verb = word;
      bits = explode( word, " " );
      if ( sizeof( bits ) > 1 ) {
         word = implode( bits[ 1 .. ], " " );
      } else {
         word = "";
      }
   } else {
      if ( pointerp( verb ) ) {
         special_mess = verb[ 1 ];
         verb = verb[ 0 ];
      }
      bits = explode( verb, " " );
      if ( sizeof( bits ) > 1 ) {
         word = implode( bits[ 1 .. ], " " );
      } else {
         word = "";
      }
   }
   if ( lengthen[ verb ] ) {
      verb = lengthen[ verb ];
   }
   exits = (string *)environment()->query_exits();
   if ( !exits ) {
      return 0;
   }
   if ( member_array( verb, exits ) != -1 ) {
     if ( environment()->query_relative( verb ) ) {
       return 0;
     }
     if ((abs_facing)[verb]) {
       facing[0] = (abs_facing)[verb] % 8;
     }
   } else {
     if (member_array(find_abs(verb), exits ) == -1 ) {
       return 0;
     }
     verb = reorient_rel(verb);
   }
   if ( !thing ) {
      thing = this_object();
   }
    if ( !redirection ) {
        if ( stringp( redirect = thing->query_exit_redirection( word ) ) ) {
            if ( temp = this_object()->exit_command( verb, redirect, thing, 1 ) )
                return temp;
        }
    }
   return (int)"/obj/handlers/room_handler"->exit_move( verb, word,
         special_mess, thing );
}
void become_flummoxed() {
   int will;
   will = query_int() * query_wis();
   if ( will < random( WILL_POWER ) )
      this_object()->interrupt_ritual();
   if ( will < random( WILL_POWER ) )
      this_object()->interrupt_spell();
   if ( will < random( WILL_POWER ) )
      this_object()->stop_all_fight();
}
int run_away() {
   int i;
   object old_env;
   mixed *direcs;
   direcs = (mixed *)environment()->query_dest_dir(this_object());
   old_env = environment();
   while ( sizeof( direcs ) ) {
      i = random( sizeof( direcs ) / 2 ) * 2;
      if ( exit_command( direcs[i] ) ) {
          event( old_env, "run_away", direcs[ i ], direcs[ i + 1 ] );
          return 1;
      }
      direcs = delete( direcs, i, 2 );
   }
   return 0;
}
mixed *stats() {
   return container::stats() + stats::stats() + ({
           ({ "max_hp", max_hp }),
           ({ "hp",  hp }),
           ({ "max_gp", max_gp }),
           ({ "gp", gp }),
           ({ "alcohol", drink_info[ D_ALCOHOL ] }),
           ({ "food", drink_info[ D_FOOD ] }),
           ({ "drink", drink_info[ D_DRINK ] }),
           ({ "gender", query_gender_string() }),
           ({ "alignment", this_object()->query_al() }),
           ({ "deity", deity }),
           ({ "total money", query_value() }),
           ({ "xp", query_xp() }),
   }) + armour::stats() + combat::stats();
}
class obj_match_context query_it_them() { return _liv_data->it_them; }
void set_it_them( class obj_match_context args) { _liv_data->it_them = args; }
int add_follower(object ob) {
  if (ob == this_object()) {
    return 0;
  }
  if (member_array(ob, _liv_data->followers) == -1) {
    _liv_data->followers += ({ ob });
  }
  return 1;
}
int remove_follower(object ob) {
  int i;
  i = member_array(ob, _liv_data->followers);
  if (i != -1) {
    _liv_data->followers = delete(_liv_data->followers, i, 1);
    return 1;
  }
  return 0;
}
int check_doing_follow(object thing, string verb, string special) {
   return 1;
}
object query_current_room() { return environment(); }
mixed *query_followers() { return copy(_liv_data->followers - ({ 0 })); }
varargs void adjust_money(mixed amt, string type) {
  return money::adjust_money(amt, type);
}
mixed *query_money_array() {
  return money::query_money_array();
}
int query_money(string type) {
  return money::query_money(type);
}
int query_value() { return money::query_value(); }
void do_burden_call() {
  if(_liv_data->burden_call)
    remove_call_out(_liv_data->burden_call);
  _liv_data->burden_call = call_out("calc_burden", 1);
}
int query_burden_limit() {
  if (this_object()->query_creator()) {
    return MAX_CREATOR_INVEN;
  } else {
    return MAX_INVEN;
  }
}
void event_enter( object thing, string mess, object from ) {
  if(environment( thing ) == this_object()) {
    do_burden_call();
    if(sizeof(all_inventory()) > query_burden_limit() ) {
      _liv_data->to_drop += ({ thing });
      remove_call_out("test_number_of_items");
      call_out("test_number_of_items", 5 + random(5));
    }
  }
}
void event_exit( object thing, string mess, object to ) {
  if(environment(thing) == this_object()) {
    do_burden_call();
  }
}
void test_number_of_items() {
   int how_many;
   object thing, *things, *dropped;
   things = all_inventory() - query_armours() - query_holding();
   how_many = sizeof(things) - query_burden_limit();
   if ( how_many < 1 ) {
      return;
   }
   _liv_data->to_drop -= ({ 0 });
   dropped = ({ });
   while(how_many > 0 && sizeof(things)) {
      if (sizeof(_liv_data->to_drop)) {
         thing = _liv_data->to_drop[random(sizeof(_liv_data->to_drop))];
      } else {
         thing = things[random(sizeof(things))];
      }
      things -= ({ thing });
      _liv_data->to_drop -= ({ thing });
      if(!thing || !thing->short() || thing->drop() ||
         thing->query_property("cannot fumble") ||
         thing->id("coin") ||
         environment(thing) != this_object()) {
        continue;
      }
      if((int)thing->move(environment()) == MOVE_OK) {
        how_many--;
        dropped += ({ thing });
      }
   }
   _liv_data->to_drop = ({ });
   if(sizeof(dropped)) {
     tell_object( this_object(), "Whoops!  You tried to carry too many "
                  "things and fumbled "+
                  query_multiple_short( dropped ) +".\n" );
     this_object()->dest_hide_shadow();
     tell_room( environment(), capitalize( the_short() ) +" juggles "+
                "around "+ query_possessive() +" stuff and fumbles "+
                query_multiple_short( dropped ) +".\n", this_object() );
   }
}
void force_burden_recalculate() {
   do_burden_call();
   remove_call_out("test_number_of_items");
   call_out("test_number_of_items", 5 + random(5));
}
object *find_inv_match( string words, object looker ) {
   return sort_array( container::find_inv_match( words, looker ),
         (: ( member_array( $1, query_holding() ) != -1 ? -1 : 0 ) :) );
}
int attack_by(object ob) {
   return_to_default_position(0);
   return ::attack_by(ob);
}
int attack_ob(object ob) {
   return_to_default_position(0);
   return ::attack_ob(ob);
}
void set_always_use_default_position(int flag) {
   always_use_default_position = flag;
}
int query_always_use_default_position() {
   return always_use_default_position;
}
string query_default_position() {
   mixed pos;
   if (stringp(default_position) &&
              default_position->query_position_command()) {
      pos = default_position;
   } else if (pointerp(default_position) &&
              (sizeof(default_position) == POSITION_MESS_SIZE ||
               sizeof(default_position) == POSITION_ONLY_TYPE_SIZE)) {
      pos = default_position;
   } else if (functionp(default_position)) {
      pos = default_position;
   }
   if (!pos) {
      pos = STANDING_CMD;
   }
   return pos;
}
void set_default_position(mixed str) {
   if (stringp(str) && str->query_position_command() && str != STANDING_CMD) {
      default_position = str;
   } else if (!str || str == STANDING_CMD) {
      default_position = 0;
   } else if (pointerp(str) && (sizeof(str) == POSITION_ONLY_TYPE_SIZE ||
                                sizeof(str) == POSITION_MESS_SIZE)) {
      default_position = str;
   } else if (functionp(str)) {
      default_position = str;
   }
}
void return_to_default_position(int leaving) {
   mixed pos;
   if (query_always_use_default_position()) {
      pos = query_default_position();
   } else {
      pos = 0;
      if (environment()) {
         pos = environment()->query_default_position(this_object());
      }
      if (!pos) {
         pos = query_default_position();
      }
   }
   if (functionp(pos)) {
      if (!evaluate(pos, this_object(), leaving)) {
         pos = 0;
         if (environment()) {
            pos = environment()->query_default_position(this_object());
         }
         if (!pos) {
            pos = STANDING_CMD;
         }
      }
   }
   if (stringp(pos)) {
      if (position != pos->query_position_type() ||
          (leaving && query_position_on())) {
         if (leaving) {
            catch(pos->position_floor(this_object()));
         } else {
            catch(pos->position(this_object()));
         }
      }
   } else if (pointerp(pos) && position != pos[POSITION_TYPE_INDEX]) {
      if (sizeof(pos) > 1) {
         if (pos[POSITION_ME_MESS_INDEX]) {
            tell_object(this_object(), pos[POSITION_ME_MESS_INDEX]);
         }
         if (pos[POSITION_REST_MESS]) {
            tell_room(environment(), pos[POSITION_REST_MESS], this_object());
         }
      }
      set_position(pos[POSITION_TYPE_INDEX]);
      set_position_on(0);
      set_position_type(0);
      set_position_multiple(0);
   }
}
void set_position(string name) {
   position = name;
}
string query_position() {
   return position;
}
void set_position_on(mixed ob) {
   if (!position_on) {
      position_on = allocate(POSITION_ARRAY_SIZE);
   }
   position_on[POS_ON_OBJECT] = ob;
}
void set_position_multiple(int mult) {
   if (!position_on) {
      position_on = allocate(POSITION_ARRAY_SIZE);
   }
   position_on[POS_MULTIPLE] = mult;
}
int query_position_multiple() {
   if (!position_on) {
      return 0;
   }
   return position_on[POS_MULTIPLE];
}
void set_position_type(string type) {
   if (!position_on) {
      position_on = allocate(POSITION_ARRAY_SIZE);
   }
   position_on[POS_TYPE] = type;
}
string query_position_type() {
   if (!position_on ||
       !position_on[POS_TYPE]) {
      return "on";
   }
   return position_on[POS_TYPE];
}
object query_position_on() {
   if (!position_on) {
      return 0;
   }
   return position_on[POS_ON_OBJECT];
}
string query_position_on_short() {
   if (!position_on || !position_on[POS_ON_OBJECT]) {
      return "";
   }
   if (stringp(position_on[POS_ON_OBJECT])) {
      return position_on[POS_ON_OBJECT];
   }
   return position_on[POS_ON_OBJECT]->the_short();
}
string query_position_long() {
   if (position != STANDING || position_on) {
      if (position_on) {
         return query_pronoun() + " is " + query_position_type() + " "+
                query_position_on_short()+".\n";
      }
      return query_pronoun()+" is "+position+" on the floor.\n";
   }
   return "";
}
string query_position_short() {
   if (!position_on ||
       !position_on[POS_ON_OBJECT]) {
      return position;
   }
   return position + " " + query_position_type() + " " +
          query_position_on_short();
}
varargs int cannot_walk( string verb, mixed *dest_other) {
   return 0;
}
string *query_arcane_shields() { return ({ }); }
int can_find_match_reference_inside_object(object thing, object looker) {
   if (member_array(thing, query_wearing_hidden(looker, 0)) != -1) {
      return 0;
   }
   return 1;
}
int query_deity_favour( string god ) {
  if ( !mapp( deity_favour ) )
    return 0;
  if ( !undefinedp( deity_favour[ god ] ) )
    return 0;
  return deity_favour[ god ];
}
void adjust_deity_favour( string god, int amount ) {
  if ( !mapp( deity_favour ) )
    deity_favour = ([ ]);
  if ( !undefinedp( deity_favour[ god ] ) )
    deity_favour[ god ] = amount;
  deity_favour[ god ] += amount;
  if ( deity_favour[ god ] > MAX_FAVOUR )
    deity_favour[ god ] = MAX_FAVOUR;
  if ( deity_favour[ god ] < -MAX_FAVOUR )
    deity_favour[ god ] = -MAX_FAVOUR;
  return;
}
mapping query_all_deity_favour() { return deity_favour; }