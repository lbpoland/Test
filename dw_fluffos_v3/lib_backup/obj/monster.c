#include <config.h>
#include <living.h>
#include <map.h>
#include <monster.h>
#include <move_failures.h>
#include <player.h>
#include <skills.h>
#include <wander.h>
#include <route.h>
#include <combat.h>
#define SPELL_INCLUDE_CLASS
#include <top_ten_tables.h>
#define SOUL_OBJECT "/obj/handlers/soul"
inherit "/std/living/mon_actions";
inherit "/std/living/living";
inherit "/std/living/response_mon";
inherit "/global/events";
inherit "/global/guild-race";
nosave string cap_name;
nosave mixed *chat_string;
nosave mixed *achat_string;
private nosave mixed *_combat_actions;
nosave mixed _move_after;
nosave mixed *throw_out;
nosave int chat_chance;
nosave int achat_chance;
nosave int aggressive;
nosave int join_fight_type;
nosave int follow_speed;
nosave int virtual_move;
nosave int moves;
nosave string race;
nosave string guild;
nosave string join_fight_mess;
nosave string true_location;
nosave mixed *enter_commands;
nosave string *move_zones;
private nosave mixed *_queued_commands;
private nosave mixed *doing_story;
nosave object last_attacked;
private nosave string *following_route;
private nosave int added_language;
private nosave function cmd_func = 0;
private nosave int cannot_change_position;
private nosave int always_return_to_default_position;
private nosave mapping _spell_actions;
void do_move_after(int running_away);
void do_route_move();
private void _next_queued_command();
void start_attack( object who );
#if !efun_defined(add_action)
protected mixed _process_input(string);
protected mixed command(string);
void command_override(function func);
int drunk_check(string str);
#endif
void create() {
    do_setup++;
    events::create();
    living::create();
    mon_actions::create();
    response_mon::create();
    do_setup--;
    reset_get();
    follow_speed = 3;
    doing_story = ({ ({ }), ({ }) });
    chat_string = ({ 0, ({ }) });
    achat_string = ({ 0, ({ }) });
    move_zones = ({ });
    _spell_actions = ([ ]);
    _combat_actions = ({ });
    enter_commands = ({ });
    known_commands = ({ });
    _queued_commands = ({ });
    following_route = ({ });
    enable_commands();
    living_commands();
    parser_commands();
    communicate_commands();
    command_commands();
    add_property("npc",1);
    set_rows( 24 );
    set_cols( 200 );
    always_return_to_default_position = 5;
#ifdef OLD_SOUL
    add_action("*", "soul_commqz", -2);
#endif
    set_con( 13 );
    set_dex( 13 );
    set_int( 13 );
    set_str( 13 );
    set_wis( 13 );
    set_max_hp( 10000 );
    set_hp( 100000 );
    set_max_gp( 10000 );
    set_gp( 10000 );
    if ( !do_setup )
        this_object()->setup();
    if(clonep())
        call_out(function() {
              if(!environment()) {
                  move(find_object("/room/rubbish"));
              }
          }, 60);
}
void setup_nationality(string nationality, string region) {
   set_nationality(nationality);
   set_nationality_region(region);
   if (!load_object(nationality)) {
      debug_printf("Bad nationality, %O\n", nationality);
   } else {
      if (!nationality->query_region_description(region)) {
         debug_printf("Bad region %O in nationality, %O\n", region,
                      nationality);
      }
      add_language(nationality->query_language());
      set_language(nationality->query_language());
      set_default_language(nationality->query_language());
   }
}
void dest_me() {
    living::dest_me();
}
int soul_commqz(string str) {
    string verb, bit;
    if (sscanf(str, "%s %s", verb, bit) == 2)
        return (int)SOUL_OBJECT->soul_command(verb, bit);
    return (int)SOUL_OBJECT->soul_command(str, "");
}
int query_sp() { return 50; }
int adjust_sp( int number ) { return 50; }
string query_cap_name() {
    return cap_name;
}
void set_cap_name(string s) { cap_name = s; }
int soul_com_force(string str) {
    if (file_name(previous_object()) != SOUL_OBJECT)
        return 0;
    command(str);
    return 1;
}
void set_name(string n) {
    if (query_name() && query_name() != "object")
        return;
    ::set_name(n);
    cap_name = capitalize(query_name());
    add_plural(pluralize(query_name()));
    set_short( query_name() );
    set_long("You see nothing special.\n");
    set_living_name(n);
}
string long(string str, int dark) {
    string s;
    if (dark < -1) {
      s = "You can only make out a rough shape in the glare.\n";
    } else if (dark > 1) {
      s = "You can only make out a rough shape in the gloom.\n";
    } else {
       s = query_long();
    }
    if(!dark) {
        s += capitalize(query_pronoun())+" "+health_string()+".\n";
        s += capitalize(query_pronoun()) + " is " +
            this_object()->query_position_short() + ".\n";
        s += calc_extra_look();
        s += query_living_contents(0);
    }
    return s;
}
int set_race(string str) {
    race = str;
    return 1;
}
string query_race() { return race; }
string query_guild() { return guild; }
string query_class() { return guild; }
string query_profession() { return guild; }
int set_class(string str) {
    guild = str;
}
int set_guild(string str) {
    guild = str;
}
int set_profession(string str) {
    guild = str;
}
void init_equip() { command("equip"); }
int do_command( string words ) {
    if ( this_object()->query_property( PASSED_OUT_PROP ) ) {
        return -1;
    }
    if ( stringp( words ) ) {
        return command( words );
    }
    printf( "Invalid parameter to do_command: %O for monster %O in %O.\n",
      words, this_object(), environment() );
    return -1;
}
void delete_queued_commands() {
  _queued_commands = ({ });
}
mixed *query_queued_commands() {
  return _queued_commands;
}
private void _next_queued_command() {
  mixed next;
  if (!sizeof(_queued_commands)) return;
  if(this_object()->query_casting_spell()){
    call_out( (: _next_queued_command :), 2 );
    return;
  }
  next = _queued_commands[0];
  if (intp( next )) {
    _queued_commands = _queued_commands[1..];
    if (!sizeof(_queued_commands)) return;
    next = _queued_commands[0];
  }
  while (stringp( next )) {
    if (this_object()->queue_commands()) {
      call_out( (: _next_queued_command :), 2 );
      return;
    }
    do_command( next );
    _queued_commands = _queued_commands[1..];
    if (!sizeof(_queued_commands)) return;
    next = _queued_commands[0];
  }
  call_out( (: _next_queued_command :), next );
}
int delay_command( string words, int interval ) {
    if ( this_object()->query_property( PASSED_OUT_PROP ) ) {
        return -1;
    }
    if ( stringp( words ) ) {
      if (!sizeof(_queued_commands)) {
        call_out( (: _next_queued_command :), interval );
      }
      _queued_commands = _queued_commands + ({ interval, words });
      return 1;
    }
    printf( "Invalid parameter to delay_command: %O for monster %O in %O.\n",
      words, this_object(), environment() );
    return -1;
}
varargs int queue_command( string words, int interval ) {
    if ( this_object()->query_property( PASSED_OUT_PROP ) ) {
        return -1;
    }
    if ( stringp( words ) ) {
      if (undefinedp(interval)) interval=2;
      if (!sizeof(_queued_commands)) {
        _queued_commands = ({ words, interval });
        _next_queued_command();
        return 1;
      }
      _queued_commands = _queued_commands + ({ words, interval });
      return 1;
    }
    printf( "Invalid parameter to queue_command: %O for monster %O in %O.\n",
      words, this_object(), environment() );
    return -1;
}
varargs void init_command(string str, int tim) {
    call_out("do_command", tim, str);
}
void init() {
  set_heart_beat( 1 );
  if (environment() && aggressive && this_player() &&
      file_name( environment() )[1..4] != "room" &&
      !environment()->no_attack() &&
      this_player()->query_visible(this_object()))
    start_attack(this_player());
}
void start_attack( object who ) {
  if(!who || !aggressive ) {
    return;
  }
  if ( !who->query_visible( this_object() ) ||
       who->query_auto_loading() ||
       file_name(who) == DEATH ||
       who->query_property( "guest" ) ||
       ( userp( who ) && !interactive( who ) ) ||
       who->query_property( "no attack" ) ) {
    return;
  }
  if(((aggressive > 1) || interactive(who)) &&
     (!interactive(who) || !who->query_auto_loading()))
    this_object()->attack_ob( who );
}
varargs int adjust_hp( int number, object attacker, object weapon,
                         string attack ) {
    set_heart_beat( 1 );
    return ::adjust_hp( number, attacker, weapon, attack );
}
int adjust_gp( int number ) {
    set_heart_beat( 1 );
    return ::adjust_gp( number );
}
int check_anyone_here() {
    object thing;
    if ( !environment() ) {
        return 0;
    }
    if ( file_name( environment() )[1..4] == "room" ) {
        return 0;
    }
    if ( environment()->query_linked() ) {
        return 1;
    }
    foreach( thing in all_inventory( environment() ) ) {
        if ( interactive( thing ) || thing->query_slave() ) {
            return 1;
        }
    }
    return 0;
}
void set_throw_out( int hps, int chance, string their_mess,
  string everyone_mess ) {
    throw_out = ({ hps, chance, their_mess, everyone_mess });
}
mixed *query_throw_out() { return throw_out; }
int run_away() {
    if ( query_property( "run away" ) == -1 ) {
        return 0;
    }
    do_command("lose all");
    become_flummoxed();
    if ( sizeof( following_route ) ) {
        do_route_move();
        return 1;
    }
    if ( query_property( "run away" ) ) {
        this_object()->do_move_after( 1 );
        return 1;
    }
    return ::run_away();
}
string expand_string(string in_str, object on) {
    string *str, ret;
    int i, add_dollar;
    object liv, *obs, ob;
    in_str = "/global/events"->convert_message( in_str );
    str = explode(in_str, "$");
    ret = "";
    for ( i = 0; i < sizeof( str ); i++ ) {
        if ( i % 2 == 0 ) {
            if (add_dollar) {
                ret += "$";
            }
            ret += str[i];
            add_dollar = 1;
            ob = 0;
        } else switch (str[i][0]) {
        case 'm' :
            ob = this_object();
        case 'l' :
          if(!ob) {
            if(!liv) {
              obs = all_inventory(environment()) - ({ this_object() });
              obs = filter_array(obs, (: living($1) &&
                                       $1->query_visible(this_object()) :));
              if (sizeof(obs))
                liv = obs[random(sizeof(obs))];
            }
            if (!liv) {
              break;
            }
            ob = liv;
          }
        case 'a' :
            if ( !ob ) {
                obs = (object *)this_object()->query_attacker_list();
                if ( !sizeof( obs ) )
                    break;
                ob = obs[ random( sizeof( obs ) ) ];
            }
        case 'o' :
            if (!ob) {
                if (!on) {
                    obs = all_inventory(environment());
                    obs = filter_array( obs, (: !living( $1 ) :) );
                    if (sizeof(obs)) {
                        on = obs[random(sizeof(obs))];
                    }
                }
                ob = on;
            }
            switch (str[ i ][ 1 .. ]) {
            case "theshort" :
                ret += (string)ob->the_short();
                add_dollar = 0;
                break;
            case "ashort" :
                ret += (string)ob->a_short();
                add_dollar = 0;
                break;
            case "oneshort":
                ret += (string)ob->one_short();
                add_dollar = 0;
                break;
            case "possshort" :
                ret += (string)ob->poss_short();
                add_dollar = 0;
                break;
            case "name" :
                ret += (string)ob->query_name();
                add_dollar = 0;
                break;
            case "cname" :
                ret += (string)ob->query_cap_name();
                add_dollar = 0;
                break;
            case "gender" :
                ret += (string)ob->query_gender_string();
                add_dollar = 0;
                break;
            case "poss" :
                ret += (string)ob->query_possessive();
                add_dollar = 0;
                break;
            case "obj" :
                ret += (string)ob->query_objective();
                add_dollar = 0;
                break;
            case "gtitle" :
                ret += (string)ob->query_gender_title();
                add_dollar = 0;
                break;
            case "pronoun" :
                ret += (string)ob->query_pronoun();
                add_dollar = 0;
                break;
            default :
                if (add_dollar) {
                    ret += "$";
                }
                ret += str[i];
                add_dollar = 1;
                break;
            }
            ob = 0;
            break;
        default :
            if (add_dollar) {
                ret += "$";
            }
            ret += str[i];
            add_dollar = 1;
            ob = 0;
            break;
        }
    }
    if (strlen(ret) && ret[strlen(ret)-1] == '$') {
        return ret[0..strlen(ret)-2];
    }
    return ret;
}
void expand_mon_string( mixed str ) {
    string *args;
    if ( functionp( str ) ) {
        evaluate( str, this_object() );
    } else {
        if( !stringp( str ) && environment( this_object() ) ) {
            tell_room(environment(this_object()),
              "%^RED%^"+ this_object()->the_short()+
              " says: please bugreport me, I have a bad load_chat.%^RESET%^\n",
              ({ }) );
        }
        switch ( str[ 0 ] ) {
        case '#' :
            args = explode(str[ 1..], ":");
            switch (sizeof(args)) {
            case 1 :
                call_other( this_object(), args[0] );
                break;
            case 2 :
                call_other( this_object(), args[0], args[1] );
                break;
            case 3 :
                call_other( this_object(), args[0], args[1], args[2] );
                break;
            case 4 :
                call_other( this_object(), args[0], args[1], args[2],
                  args[3] );
                break;
            default :
                call_other( this_object(), args[0], args[1], args[2],
                  args[3], args[4] );
                break;
            }
            break;
        case ':' :
        case '\'' :
        case '"' :
            init_command( expand_string( str, 0 ), 1 );
            break;
        case '@' :
            init_command( expand_string( str[ 1 .. ], 0 ), 1 );
            break;
        default :
            tell_room( environment(), expand_string( str, 0 ) +"\n" );
        }
    }
}
int query_ok_turn_off_heart_beat() {
   return 1;
}
void heart_beat() {
  int i, j;
  if(base_name(environment()) == "/room/rubbish") {
    set_heart_beat(0);
    return;
  }
  ::heart_beat();
  RACE_OB->monster_heart_beat( race, guild, race_ob, guild_ob );
  if ( ( hp == max_hp ) && ( gp == max_gp ) ) {
    if (query_ok_turn_off_heart_beat()) {
      if ( !check_anyone_here() ||
           ( !sizeof( achat_string ) && !sizeof( chat_string ) ) ) {
        set_heart_beat( 0 );
        return;
      }
    }
  }
  remove_property( "done follow" );
  this_object()->do_spell_effects( 0 );
  if ( check_anyone_here() ) {
    if ( this_object()->query_fighting() ) {
      if ( sizeof( doing_story[ 1 ] ) ) {
        if( !intp(doing_story[ 1 ][ 0 ] ) ) {
          expand_mon_string( doing_story[ 1 ][ 0 ] );
          doing_story[ 1 ] = doing_story[ 1 ][ 1 .. ];
        } else if( random( 1000 ) < doing_story[ 1 ] [ 0 ]) {
          expand_mon_string( doing_story[ 1 ][ 1 ] );
          if ( sizeof( doing_story[ 1 ] ) == 2 ) {
            doing_story[ 1 ] = ({});
          } else {
            doing_story[ 1 ] = ({ doing_story[ 1 ] [ 0 ] }) +
              doing_story[ 1 ][ 2 .. ];
          }
        }
      } else if ( ( random( 1000 ) < achat_chance )
                  && sizeof( achat_string[ 1 ] ) ) {
        i = random( achat_string[ 0 ] + 1 );
        while ( ( i -= achat_string[ 1 ][ j ] ) > 0 )
          j += 2;
        if ( pointerp( achat_string[ 1 ][ j + 1 ] ) ) {
          if( intp(achat_string[ 1 ][ j + 1 ][ 0 ]) ) {
            if( random(1000) < achat_string[ 1 ][ j + 1 ][ 0 ] ) {
              expand_mon_string( achat_string[ 1 ][ j + 1 ][ 1 ] );
              doing_story[ 1 ] = ({ achat_string[ 1 ][ j + 1 ][ 0 ] })+
                achat_string[ 1 ][ j + 1 ][ 2 .. ];
            } else {
              doing_story[ 1 ] = achat_string[ 1 ][ j + 1 ];
            }
          } else {
            expand_mon_string( achat_string[ 1 ][ j + 1 ][ 0 ] );
            doing_story[ 1 ] = achat_string[ 1 ][ j + 1 ][ 1 .. ];
          }
        } else
          expand_mon_string( achat_string[ 1 ][ j + 1 ] );
      }
    } else {
      if ( sizeof( doing_story[ 0 ] ) ) {
        if( !intp( doing_story[ 0 ][ 0 ] ) ) {
          expand_mon_string( doing_story[ 0 ][ 0 ] );
          doing_story[ 0 ] = doing_story[ 0 ][ 1 .. ];
        } else if( random( 1000 ) < doing_story[ 0 ][ 0 ]) {
          expand_mon_string( doing_story[ 0 ][ 1 ] );
          if ( sizeof( doing_story[ 0 ] ) == 2 ) {
            doing_story[ 0 ] = ({});
          } else {
            doing_story[ 0 ] = ({ doing_story[ 0 ] [ 0 ] }) +
              doing_story[ 0 ][ 2 .. ];
          }
        }
      } else if ( ( random( 1000 ) < chat_chance )
                  && sizeof( chat_string[ 1 ] ) ) {
        i = random( chat_string[ 0 ] + 1 );
        while ( ( i -= chat_string[ 1 ][ j ] ) > 0 )
          j += 2;
        if ( pointerp( chat_string[ 1 ][ j + 1 ] ) ) {
          if( intp( chat_string[ 1 ][ j + 1 ][ 0 ]) ) {
            if(random( 1000) < chat_string[ 1 ][ j + 1 ][ 0 ]) {
              expand_mon_string( chat_string[ 1 ][ j + 1 ][ 1 ] );
              doing_story[ 0 ] = ({ chat_string[ 1 ][ j + 1 ][ 0 ] }) +
                chat_string[ 1 ][ j + 1 ][ 2 .. ];
            } else {
              doing_story[ 0 ] = chat_string[ 1 ][ j + 1 ];
            }
          } else {
            expand_mon_string( chat_string[ 1 ][ j + 1 ][ 0 ] );
            doing_story[ 0 ] = chat_string[ 1 ][ j + 1 ][ 1 .. ];
          }
        } else
          expand_mon_string( chat_string[ 1 ][ j + 1 ] );
      }
    }
  }
}
int clean_up( int parent ) {
  if(query_property("unique") || check_anyone_here())
    return 1;
  if(parent) {
    log_file("CLEANUP", "%s %s cleaned up.\n", ctime(time()),
             file_name(this_object()));
  }
  move( "/room/rubbish" );
  return 1;
}
int rand_num(int no, int type) {
    int i, val;
    for (i=0;i<no;i++)
        val = random(type)+1;
    return val;
}
void set_random_stats(int no, int type) {
    set_str(rand_num(no, type));
    set_dex(rand_num(no, type));
    set_int(rand_num(no, type));
    set_con(rand_num(no, type));
    set_wis(rand_num(no, type));
}
void basic_setup(string race, string guild, int level)
{
    this_object()->set_race(race);
    this_object()->set_guild(guild);
    this_object()->set_level(level);
}
void set_level( int i ) { RACE_OB->set_level( i, race, guild ); }
int give_money(int base, int rand, string type) {
    if (!type)
        type = "copper";
    return adjust_money(base+random(rand), type);
}
void load_chat(int chance, mixed *c_s) {
    int i;
    chat_string = ({ 0, ({ }) });
    for (i=0;i<sizeof(c_s);i+=2) {
        chat_string[1] += ({ c_s[i], c_s[i+1] });
        chat_string[0] += c_s[i];
    }
    chat_chance = chance;
}
void set_chat_chance(int i) { chat_chance = i; }
int query_chat_chance() { return chat_chance; }
void set_chat_string(string *chat) { chat_string = chat; }
string *query_chat_string() { return chat_string; }
void add_chat_string(mixed weight, mixed chat) {
    int i;
    if (pointerp(weight)) {
        for (i=0;i<sizeof(weight);i+=2) {
            add_chat_string(weight[i], weight[i+1]);
        }
    } else {
        if (member_array(chat, chat_string[1]) == -1) {
            chat_string[1] += ({ weight, chat });
            chat_string[0] += weight;
        }
    }
}
void remove_chat_string(mixed chat) {
    int i;
    if (pointerp(chat)) {
        for (i=0;i<sizeof(chat);i++) {
            remove_chat_string(chat[i]);
        }
    } else {
        if ((i = member_array(chat, chat_string[1])) != -1) {
            chat_string[0] -= chat_string[1][i-1];
            chat_string[1] = delete(chat_string[1], i-1, 2);
        }
    }
}
void load_a_chat(int chance, mixed *c_s) {
    int i;
    achat_string = ({ 0, ({ }) });
    for (i=0;i<sizeof(c_s);i+=2) {
        achat_string[1] += ({ c_s[i], c_s[i+1] });
        achat_string[0] += c_s[i];
    }
    achat_chance = chance;
}
void set_achat_chance(int i) { achat_chance = i; }
int query_achat_chance() { return achat_chance; }
void set_achat_string(string *chat) { achat_string = chat; }
string *query_achat_string() { return achat_string; }
void add_achat_string(mixed weight, mixed chat) {
    int i;
    if (pointerp(weight))
        for (i=0;i<sizeof(weight);i+=2)
            add_achat_string(weight[i], weight[i+1]);
    else
    if (member_array(chat, achat_string[1]) == -1) {
        achat_string[1] += ({ chat });
        achat_string[0] += weight;
    }
}
void remove_achat_string(mixed chat) {
    int i;
    if (pointerp(chat))
        for (i=0;i<sizeof(chat);i++)
            remove_achat_string(chat[i]);
    else
    if ((i = member_array(chat, achat_string[1])) != -1) {
        achat_string[0] -= achat_string[1][i-1];
        achat_string[1] = delete(achat_string[1], i-1, 1);
    }
}
void add_move_zone(mixed zone) {
    int i;
    if (pointerp(zone))
        for (i=0;i<sizeof(zone);i++)
            add_move_zone(zone[i]);
    else if (member_array(zone, move_zones) != -1)
        return;
    else
        move_zones += ({ zone });
}
void set_move_zones(string *zones) {
    int i;
    for (i=0;i<sizeof(zones);i++)
        add_move_zone(zones[i]);
}
void remove_move_zone(mixed zone) {
    int i;
    if (pointerp(zone))
        for (i=0;i<sizeof(zone);i++)
            remove_move_zone(zone[i]);
    else {
        if ((i=member_array(zone, move_zones)) == -1)
            return ;
        move_zones = delete(move_zones, i, 1);
    }
}
string *query_move_zones() { return move_zones; }
void set_move_after(int after, int rand) {
    _move_after = ({ after, rand });
    if (after != 0 && rand != 0) {
        do_move_after(0);
    }
}
mixed query_move_after() {
   return copy( _move_after );
}
int add_enter_commands(mixed str) {
    if (stringp(str)) {
        enter_commands += ({ str });
    } else if (pointerp(str)) {
        enter_commands += str;
    } else if (functionp(str)) {
        enter_commands += ({ str });
    }
    return 1;
}
string *query_enter_commands() { return enter_commands; }
void reset_enter_commands() { enter_commands = ({ }); }
varargs int move( mixed dest, string messin, string messout ) {
    int result;
    object before;
    before = environment();
    result = living::move( dest, messin, messout );
    if ( result == MOVE_OK ) {
        me_moveing( before );
        if ( virtual_move )
            true_location = file_name( environment() );
    }
    return result;
}
void room_look() {
    int i;
    ::room_look();
    for ( i = 0; i < sizeof( enter_commands ); i++ ) {
        if ( functionp( enter_commands[ i ] ) ) {
            call_out( enter_commands[ i ], 2 * i + 1, this_object() );
            continue;
        }
        if ( enter_commands[ i ][ 0 .. 0 ] == "#" )
            call_out( enter_commands[ i ][ 1 .. 99 ], 2 * i + 1 );
        else
            init_command( enter_commands[ i ], 2 * i + 1 );
    }
}
void do_move_after (int running_away ) {
    if (sizeof(following_route)) {
        do_route_move();
    } else {
        WANDER_HANDLER->move_after( running_away );
    }
}
void event_fight_in_progress(object me, object him) {
  mixed action;
  int i;
  if(sizeof(this_object()->query_attacker_list())) {
    for(i=0; i<sizeof(_combat_actions); i+= 3) {
      if(_combat_actions[i] > random(100)) {
        action = _combat_actions[i+2];
        if(stringp(action))
          this_object()->do_command(action);
        else if(functionp(action))
          evaluate(action, me, him);
        else if(pointerp(action) && sizeof(action) == 1 && stringp(action[0]))
          call_other(this_object(), action[0], me, him);
        else if(pointerp(action) && sizeof(action) == 2)
          call_other(action[0], action[1], this_object(), me, him);
      }
    }
  }
  if(him == this_object() && this_object()->query_property("see_caster") &&
     !userp(me) &&
     (random(him->query_property("see_caster"))) < (him->query_int()))
    this_object()->attack_ob(me->query_owner());
  if(!join_fight_mess || !me || !him)
    return;
  if(him == this_object())
    return;
  if(!join_fight_type && !interactive(him))
    return;
  if(member_array(him, (object *)this_object()->query_attacker_list()) == -1) {
    if(!him->query_property("no attack")) {
      if(join_fight_mess)
        expand_mon_string(join_fight_mess);
      this_object()->attack_ob(him);
    }
  }
}
void set_join_fights(string str) { join_fight_mess = str; }
string query_join_fights() { return join_fight_mess; }
void set_join_fight_type(int i) { join_fight_type = i; }
int query_fight_type() { return join_fight_type; }
void event_exit( object me, string mess, object to ) {
  mixed *bing;
  int i, j, k;
  string *zones, fname;
  object *attacker_list, ob;
  events::event_exit( me, mess, to );
  living::event_exit( me, mess, to );
  if (!_move_after || sizeof(following_route))
    return ;
  if ( !to || !me->query_visible(this_object()))
    return;
  attacker_list = this_object()->query_attacker_list();
  if(attacker_list && sizeof(attacker_list)) {
    if (member_array(me, attacker_list) == -1)
      return;
    attacker_list -= ({ me });
    foreach(ob in attacker_list) {
      if(ob && environment(ob) == environment())
        return;
    }
  } else {
    return;
  }
  bing = (mixed *)environment()->query_dest_dir( this_object() );
  if( !bing ) {
    return ;
  }
  fname = file_name( to );
  if ((i = member_array(fname, bing)) == -1) {
    return ;
  }
  if (!this_object()->query_property("unrestricted follow")) {
    zones = (string *)to->query_zones();
    if (move_zones && (j = sizeof(move_zones))) {
      while (j--) {
        if (member_array(move_zones[j], zones) != -1) {
          k = 1;
          break;
        }
      }
      if (!k)
        return;
    } else
      return;
  }
  remove_call_out("do_follow_move");
  call_out("do_follow_move", 4 + random(follow_speed), bing[i-1]);
}
void do_follow_move(string dir) {
  if (sizeof(following_route))
    return ;
  this_object()->adjust_action_defecit((ACTIONS_PER_HB / (COMBAT_SPEED + 1)));
  do_command(dir);
}
void add_combat_action( int chance, string name, mixed action ) {
    int i;
    i = member_array( name, _combat_actions );
    if ( i == -1 ) {
        _combat_actions += ({ chance, name, action });
    } else {
        _combat_actions[ i - 1 ] = chance;
        _combat_actions[ i + 1 ] = action;
    }
}
int remove_combat_action( string name ) {
    int i;
    i = member_array( name, _combat_actions );
    if ( i == -1 )
        return 0;
    _combat_actions = delete( _combat_actions, i - 1, 3 );
    return 1;
}
mixed *query_combat_actions() { return copy( _combat_actions ); }
void do_combat_action( object player,
                       object target,
                       mixed action ) {
   object place;
   if ( !target ) {
      return;
   }
   place = environment( target );
   if ( place != environment( player ) ) {
      return;
   }
   if ( stringp( action ) ) {
      do_command( action );
      return;
   }
   if (functionp(action)) {
      evaluate(action, player, target);
   }
   if ( pointerp(action) && sizeof(action) == 1 && stringp( action[ 0 ] ) ) {
      call_other( this_object(), action[ 0 ], player, target );
      return;
   }
   if (pointerp(action) && sizeof(action) == 2) {
      call_other( action[ 0 ], action[ 1 ], this_object(), player, target );
   }
}
void combat_actions_call_back( object player, object target ) {
  int i;
  object thing;
  object *things;
  mixed *actions;
  if ( !player || !target ) {
    return;
  }
  thing = environment( player );
  if ( thing != environment( target ) ) {
    return;
  }
  things = filter_array( all_inventory( thing ), (: living( $1 ) ==
                                                  !userp( $1 ) :) );
  foreach ( thing in things ) {
    actions = (mixed *)thing->query_combat_actions();
    for(i=0; i<sizeof(actions); i += 3) {
      if(actions[i] > random(100)) {
        call_out( "do_combat_action", 1, player, target, actions[ i + 2 ] );
      }
    }
  }
}
void add_spell_action(string spell_object, int chance,
                     string name, mixed action) {
   if (!_spell_actions[spell_object]) {
      _spell_actions[spell_object] = ([ ]);
   }
   _spell_actions[spell_object][name] = ({ chance, action });
}
int remove_spell_action(string name) {
   string spell;
   mapping bits;
   int ret;
   foreach (spell, bits in _spell_actions) {
      if (bits[name]) {
         map_delete(bits, name);
         ret = 1;
      }
   }
   return ret;
}
mapping query_spell_actions() {
   return _spell_actions;
}
void do_spell_action( object caster,
                      object* targets,
                      mixed action,
                      mixed args ) {
   if ( stringp( action ) ) {
      do_command( action );
      return;
   }
   if (functionp(action)) {
      evaluate(action, caster, targets);
   }
   if ( pointerp(action) && sizeof(action) == 1 && stringp( action[ 0 ] ) ) {
      call_other( this_object(), action[ 0 ], caster, targets, args );
      return;
   }
   if (pointerp(action) && sizeof(action) == 2) {
      call_other( action[ 0 ], action[ 1 ], this_object(), caster, targets,
                  args );
   }
}
mixed query_race_ob() { return race_ob; }
void set_race_ob(mixed r) { race_ob = r; }
mixed query_guild_ob() { return guild_ob; }
void set_guild_ob(mixed g) { guild_ob = g; }
int query_follow_speed() { return follow_speed; }
void set_follow_speed(int f) { follow_speed = f; }
int query_aggressive() { return aggressive; }
void set_aggressive(int a) {
    aggressive = a;
    if (a && !join_fight_mess) {
        join_fight_mess = this_object()->one_short()+" joins in the fight.\n";
    }
}
int query_level() {
    if (!guild_ob) return 1;
    return (int)guild_ob->query_level(this_object());
}
int query_death_xp() {
    int amount;
    if ( query_property( "dead" ) || query_property( "unique" ) ) {
        return 0;
    }
    amount = (int)TOP_TEN_HANDLER->calculate_rating( this_object() );
    return amount / 2;
}
mixed *stats() {
    mixed *bing;
    int i;
    bing = ({ });
    for (i=0;i<sizeof(move_zones);i++)
        bing += ({ ({ "move zone "+i, move_zones[i] }) });
    if (!query_move_after())
        return ::stats() + ({
          ({ "guild", query_guild() }),
          ({ "guild ob", query_guild_ob() }),
          ({ "race", query_race() }),
          ({ "race ob", query_race_ob() }),
          ({ "join_fights", query_join_fights() }),
          ({ "follow speed", query_follow_speed() }),
          ({ "level", query_level() }),
          ({ "chat chance", query_chat_chance() }),
          ({ "achat chance", query_achat_chance() }),
          ({ "aggressive", query_aggressive() }),
          ({ "route", (sizeof(following_route)?implode(following_route, ", "):
              "not going anywhere") }),
        }) + bing;
    return ::stats() + ({
      ({ "race", query_race() }),
      ({ "race ob", query_race_ob() }),
      ({ "guild", query_guild() }),
      ({ "guild ob", query_guild_ob() }),
      ({ "join fights", query_join_fights() }),
      ({ "follow_speed", query_follow_speed() }),
      ({ "level", query_level() }),
      ({ "chat chance", query_chat_chance() }),
      ({ "achat chance", query_achat_chance() }),
      ({ "aggressive", query_aggressive() }),
      ({ "move after-fix", query_move_after()[0] }),
      ({ "move after-rand", query_move_after()[1] }),
      ({ "route", (sizeof(following_route)?implode(following_route, ", "):
          "not following anyone") }),
    }) + bing;
}
string expand_nickname(string str) { return str; }
void event_enter( object dest, string mess, object from ) {
    if( environment( this_object() ) &&
      file_name( environment( this_object() ) )[ 1 .. 4 ] == "room" )
        return;
    if(check_anyone_here() && (moves > 2)){
        moves = 0;
        do_move_after(0);
    }
    living::event_enter( dest, mess, from );
    events::event_enter( dest, mess, from );
}
void event_person_say( object thing, string start, string mess, string lang,
                       string accent) {
    response_mon::event_person_say(thing, start, mess, lang);
}
void event_whisper( object thing, string start, string mess, object *obs,
  string lang, object me) {
    response_mon::event_whisper( thing, mess, obs, lang, me);
}
varargs void event_soul( object thing, string mess, mixed avoid, string verb,
  string last, mixed at ) {
    response_mon::event_soul( thing, mess, avoid, verb, last, at );
    events::event_soul( thing, mess, avoid );
}
void real_room( string check_room ) {
    if ( check_room == true_location ) {
        move_object( true_location );
    }
}
#if !efun_defined(add_action)
int query_virtual_move() { return virtual_move; }
#else
int query_virtual_move() { return 0; }
#endif
void set_virtual_move( int number ) {
    if(virtual_move && !number && file_name(environment()) == "/room/virtual"){
        object ob = load_object(true_location);
        if(ob)
            move(ob);
    }
    virtual_move = number;
    if ( virtual_move && environment() )
        true_location = file_name( environment() );
}
string query_true_location() { return true_location; }
void set_true_location( string word ) {
    if(word == "/room/virtual"){
        if(true_location)
            return;
        word = file_name(environment());
        if(word == "/room/virtual"){
            move("/room/rubbish");
            true_location = "/room/rubbish";
        }
    }
    true_location = word;
}
int cleaning_room() {
    if ( virtual_move ) {
        true_location = file_name( environment() );
        "/room/virtual"->force_load();
        move_object( "/room/virtual" );
        return 1;
    }
    return 0;
}
void do_move( string move ) {
    if (1 || check_anyone_here()) {
        moves = 0;
    }
    if (moves++ < 3) {
        string tmp;
        command(move);
        tmp = file_name(environment());
        if(tmp == "/room/virtual")
            tmp = true_location;
        true_location = tmp;
    } else {
        WANDER_HANDLER->delete_move_after(this_object());
    }
}
string get_next_route_direction() {
    string direc;
    if (!sizeof(following_route)) {
        return 0;
    }
    direc = following_route[0];
    following_route = following_route[1..];
    return direc;
}
int query_last_route_direction() { return ( sizeof(following_route) ? 1 : 0 ); }
string *query_following_route() { return following_route; }
void do_route_move() {
    if (!sizeof(following_route)) {
        return ;
    }
    do_command(get_next_route_direction());
}
protected void got_the_route(string *route, int delay, string dest) {
    following_route = route;
    if (sizeof(route)) {
        WANDER_HANDLER->move_me_please(delay, dest);
        do_route_move();
    } else {
        this_object()->stopped_route();
    }
}
varargs void move_me_to(string dest, int delay) {
    string *dest_dir, *start_dir;
    if (!environment() || !file_name(environment()))
        return ;
    if(!delay)
      delay = 10;
    if (!MAP->static_query_short( dest ) ||
      !MAP->static_query_short( file_name(environment()) ) ) {
       if (!sizeof( dest_dir = dest->query_dest_dir( this_object() ) ) ||
           !sizeof( start_dir =
               environment()->query_dest_dir( this_object() ) ) )
       {
            move( dest, "$N wanders in.\n", "$N wanders off.\n" );
        } else {
            move( dest,
              replace_string( query_msgin(), "$F",
                dest_dir[random(sizeof(dest_dir)/2)*2]),
              replace_string( query_msgout(), "$T",
                start_dir[random(sizeof(start_dir)/2)*2]));
        }
        call_out( "stopped_route", 1 );
        return;
    }
    ROUTE_HANDLER->get_route(dest, file_name(environment()),
      (: got_the_route($1, $(delay), $(dest)) :));
}
string identify( object thing, object *places ) {
    do_command( "'Please bug me!  I'm using identify()!" );
    return file_name( thing );
}
int query_time_left() { return 1; }
int ignore_identifier() { return 1; }
void add_language(string str) {
    ::add_language(str);
    added_language = 1;
}
void set_cannot_change_position(int flag) {
    cannot_change_position = flag;
}
int query_cannot_change_position() {
    return cannot_change_position;
}
void set_position(string new_pos) {
    if (always_return_to_default_position) {
        if (new_pos != query_position() &&
          this_player() != this_object()) {
            call_out("return_to_default_position",
              always_return_to_default_position, 0);
        }
    }
    ::set_position(new_pos);
}
void set_always_return_to_default_position(int tim) {
    always_return_to_default_position = tim;
}
int query_always_return_to_default_position() {
    return always_return_to_default_position;
}
mapping int_query_static_auto_load() {
    return ([
      "::" : ::int_query_static_auto_load(),
      "cap name" : cap_name,
      "race" : race,
      "guild" : guild,
    ]);
}
mixed query_static_auto_load() {
    if ( base_name(this_object()) + ".c" == __FILE__ )
        return int_query_static_auto_load();
    return ([ ]);
}
mapping query_dynamic_auto_load() {
    return ([
      "::" : ::query_dynamic_auto_load(),
      "chat string"                       : chat_string,
      "achat string"                      : achat_string,
      "combat actions"                    : _combat_actions,
      "move after"                        : _move_after,
      "throw out"                         : throw_out,
      "chat chance"                       : chat_chance,
      "achat chance"                      : achat_chance,
      "aggressive"                        : aggressive,
      "join fight type"                   : join_fight_type,
      "join fight mess"                   : join_fight_mess,
      "follow speed"                      : follow_speed,
      "virtual move"                      : virtual_move,
      "moves"                             : moves,
      "true location"                     : true_location,
      "enter commands"                    : enter_commands,
      "move zones"                        : move_zones,
      "doing story"                       : doing_story,
      "last attacked"                     : last_attacked,
      "following route"                   : following_route,
      "added language"                    : added_language,
      "cannot change position"            : cannot_change_position,
      "always return to default position" : always_return_to_default_position,
      "level"                             : query_level(),
    ]);
}
void init_static_arg(mapping args) {
    if (args["::"])
        ::init_static_arg(args["::"]);
    if (!undefinedp(args["cap name"]))
        cap_name = args["cap name"];
    if (!undefinedp(args["race"]))
        race = args["race"];
    if (!undefinedp(args["guild"]))
        guild = args["guild"];
}
void init_dynamic_arg( mapping args, object ob ) {
    if (args["::"])
        ::init_static_arg(args["::"]);
    if (!undefinedp(args["chat string"]))
        chat_string = args["chat string"];
    if (!undefinedp(args["achat string"]))
        achat_string = args["achat string"];
    if (!undefinedp(args["combat actions"]))
        _combat_actions = args["combat actions"];
    if (!undefinedp(args["move after"]))
        _move_after = args["move after"];
    if (!undefinedp(args["throw out"]))
        throw_out = args["throw out"];
    if (!undefinedp(args["chat chance"]))
        chat_chance = args["chat chance"];
    if (!undefinedp(args["achat chance"]))
        achat_chance = args["achat chance"];
    if (!undefinedp(args["aggressive"]))
        aggressive = args["aggressive"];
    if (!undefinedp(args["join fight type"]))
        join_fight_type = args["join fight type"];
    if (!undefinedp(args["join fight mess"]))
        join_fight_mess = args["join fight mess"];
    if (!undefinedp(args["follow speed"]))
        follow_speed = args["follow speed"];
    if (!undefinedp(args["virtual move"]))
        virtual_move = args["virtual move"];
    if (!undefinedp(args["moves"]))
        moves = args["moves"];
    if (!undefinedp(args["true location"]))
        true_location = args["true location"];
    if (!undefinedp(args["enter commands"]))
        enter_commands = args["enter commands"];
    if (!undefinedp(args["move zones"]))
        move_zones = args["move zones"];
    if (!undefinedp(args["doing story"]))
        doing_story = args["doing story"];
    if (!undefinedp(args["last attacked"]))
        last_attacked = args["last attacked"];
    if (!undefinedp(args["following route"]))
        following_route = args["following route"];
    if (!undefinedp(args["added language"]))
        added_language = args["added language"];
    if (!undefinedp(args["cannot change position"]))
        cannot_change_position = args["cannot change position"];
    if (!undefinedp(args["always return to default position"]))
        always_return_to_default_position =
        args["always return to default position"];
    if (!undefinedp(args["level"]))
        set_level(args["level"]);
}
int attack_permission( object ob1, object ob2, string stringy ) { return 0; }
#if !efun_defined(add_action)
protected mixed _process_input(string str) {
    object ob = this_player();
    if(str == "")
        return 0;
    _notify_fail(0);
    efun::set_this_player(this_object());
    if(!this_object()->drunk_check(str))
        if(!this_object()->exit_command(str))
            if(!this_object()->cmdAll(str))
                if(!this_object()->new_parser(str))
                    if(!this_object()->lower_check(str)){
                        efun::set_this_player(ob);
                        return 0;
                    }
    efun::set_this_player(ob);
    return "bing";
}
int drunk_check(string str) {
   if(cmd_func){
     object owner = function_owner(cmd_func);
     if(owner && owner == environment(this_player())){
       int res = evaluate(cmd_func, str);
       if(res)
         return res;
     } else cmd_func = 0;
   }
   return 0;
}
void command_override(function func) {
  if(!functionp(func))
    error("command_override needs a function!");
  cmd_func = func;
}
protected mixed command(string cmd){
  int time = eval_cost();
  if(_process_input(cmd))
    return eval_cost() - time + 1;
  return 0;
}
#endif
int _living(){return 1;}
void event_hide_invis( object hider, int adding, string type, int quiet ) {
   if ( aggressive &&
        !adding &&
        environment() &&
        file_name( environment() )[1..4] != "room" )
   {
      start_attack(hider);
   }
}