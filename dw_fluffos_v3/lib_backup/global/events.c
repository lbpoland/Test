#include <dirs.h>
#include <living.h>
#include <player.h>
#include <telnet.h>
#include <term.h>
#include <tune.h>
#include <language.h>
#include <broadcaster.h>
#include <cmds/options.h>
#include <newbiehelpers.h>
#include <playerinfo.h>
#define DEBUG
#define BROADCASTER "/obj/handlers/broadcaster"
#define SPACES "                                                              "
#define INFORM_COLOURS ([ "default":"WHITE", "logon":"GREEN", "death":"RED", \
                           "cheat":"RED", "multiplayer":"RED",  \
                           "bad-password" : "RED", "link-death":"GREEN", \
                           "new-player" : "BOLD%^%^MAGENTA", \
                           "gag" : "BOLD%^%^RED", "alert" : "GREEN" ])
#ifdef OLD_THINGY
inherit "/global/play_parse_com";
#else
inherit "/global/new_parse";
#endif
inherit "/global/communicate";
inherit "/global/friends";
inherit "/global/options_control";
class event_info {
  mapping colour_map;
  string cur_term;
  string last_term;
  object where;
  object *had_shorts;
  mixed *eemessages;
  mixed busy;
}
private nosave class event_info _event_info;
private int earmuffs;
private int cols;
private int rows;
private mapping my_colours;
private string term_name = "network";
private string *inform_types;
private mixed *tell_history;
void set_my_colours(string event_type, string colour);
mapping query_my_colours();
string find_rel(string word, int from);
private int set_our_rows(int num);
private int set_our_cols(int num, int test);
private int do_busy(string str);
private int do_busy_player(object *players);
protected varargs int do_tell_his(string, int);
mixed query_property(string name);
string query_nationality_accent_ob();
void create() {
  friends::create();
  _event_info = new(class event_info,
                    eemessages : ({ }));
  my_colours = ([ ]);
  inform_types = ({ });
#ifdef OLD_THINGY
  play_parse_com::create();
#else
  new_parse::create();
#endif
}
#if !efun_defined(has_mxp)
private int has_mxp(object ob) {
   return 0;
}
#endif
string query_term_name() { return term_name; }
string query_cur_term() { return _event_info->cur_term; }
int query_earmuffs() { return earmuffs; }
string *query_inform_types() {
  string *types;
  types = ({ "logon", "new-player", "birthday", "council", "friend" });
  if (this_object()->query_creator()) {
    types += ({ "link-death", "message", "death",
               "guild", "delete", "help", "combat-debug", "skill", "quest",
               "multiplayer", "bad-password", "club", "debug", "gag",
               "alert" });
    if (master()->query_lord((string)this_object()->query_name())) {
      types += ({ "force", "enter", "dest", "cheat", "xp", "calls",
                    "cpu", "ftp" });
    }
  } else if ( load_object(NEWBIEHELPERS_HANDLER)->query_helper_access(this_object())
                ) {
      types += ({ "guild" });
  }
  if( this_object()->query_guild_ob() == "/std/guilds/witch" ||
      this_object()->query_creator() ) {
    types += ({ "mockery" });
  }
  return types;
}
nomask protected int do_inform(string str) {
  string type, *types, *on, *frog, *off, *failed;
  int i;
  types = query_inform_types();
  foreach(type in inform_types) {
    if(member_array(type, types) == -1) {
      inform_types -= ({ type });
    }
  }
  on = inform_types;
  if (!on) {
    on = ({ });
  }
  if (!str) {
    str = "";
  }
  frog = explode(str, " ");
  if (!frog) {
    frog = ({ });
  } else {
    frog -= ({ "", 0 });
  }
  if (!sizeof(frog)) {
    if (this_object()->query_property("inform repressed")) {
      write("Your informs are currently being repressed.\n");
    }
    if (sizeof(on)) {
      write("$I$5=You will be informed of "+ query_multiple_short(on)+
            " events.\n");
    }
    types -= on;
    if (sizeof(types)) {
      write("$I$5=You are not being informed of "+ query_multiple_short(types)+
            " events.\n");
    }
    return 1;
  }
  if (sizeof(frog) == 1) {
    switch (frog[0]) {
    case "on" :
      this_object()->remove_property("inform repressed");
      write("You are now being informed.  This is true!\n");
      if (sizeof(on)) {
         write("$I$5=You will be informed of "+ query_multiple_short(on)+
               " events.\n");
      } else {
         write("$I$5=Although you are not currently being informed of "
               "any events.\n");
      }
      return 1;
    case "off":
      this_object()->add_property("inform repressed", 1);
      write("Informs are now repressed.\n");
      return 1;
    case "all":
      on = types;
      frog = frog[1..];
      break;
    case "none" :
      on = ({ });
      write("You will not be informed of anything.\n");
      frog = frog[1..];
      break;
    }
  }
  failed = off = ({ });
  for (i=0;i<sizeof(frog);i++) {
    if (member_array(frog[i], types) == -1) {
      failed += ({ frog[i] });
    } else {
      if (sizeof(frog) > i+1) {
        switch (frog[i+1]) {
        case "on" :
          if (member_array(frog[i], on) == -1)
            on += ({ frog[i] });
          i++;
          break;
        case "off" :
          off += ({ frog[i] });
          i++;
          break;
        default :
          if (member_array(frog[i], on) == -1) {
            on += ({ frog[i] });
          } else {
            off += ({ frog[i] });
          }
          break;
        }
      } else {
        if (member_array(frog[i], on) == -1) {
          on += ({ frog[i] });
        } else {
          off += ({ frog[i] });
        }
      }
    }
  }
  on -= off;
  if (sizeof(failed)) {
    write("$I$5=I don't know about "+ query_multiple_short(failed)+
          " events.\n");
  }
  if (sizeof(off)) {
    write("$I$5=You will now not be informed of "+ query_multiple_short(off)+
          " events.\n");
  }
  if (sizeof(on)) {
    write("$I$5=You will now be informed of "+ query_multiple_short(on)+
          " events.\n");
  }
  inform_types = on;
  return 1;
}
int query_see_octarine() {
  string guild;
  if ( this_object()->query_creator() )
    return 1;
  if(!(guild = (string)this_object()->query_guild_ob())) return 0;
  return (int)guild->query_see_octarine();
}
string octarine_message(string str) {
  if (query_see_octarine())
    return str;
  return "";
}
string colour_event(string event_type, string default_colour) {
  if (my_colours[event_type]) {
    return replace(my_colours[event_type], " ", "");
  }
  if (!default_colour) {
    return "";
  }
  return default_colour;
}
varargs string fix_string(string str, int width, int indent, int padding, mixed *args ...) {
  string octmess, *bits, bit;
  int i;
  if (!stringp(str) || str == "") {
    return str;
  }
  if(indent > width / 3) {
    indent = 4;
  }
  if (!_event_info->cur_term) {
    if (term_name != "network") {
      _event_info->cur_term = term_name;
    } else {
      _event_info->cur_term = "dumb";
    }
  }
  if (!_event_info->colour_map) {
    _event_info->colour_map = (mapping)TERM_HANDLER->set_term_type(_event_info->cur_term, query_property(PLAYER_ALLOW_COLOURED_SOULS));
  }
  if (sizeof(args)) {
    str = sprintf(str, args ...);
  }
  bits = explode(str, "%^OCTARINE:");
  foreach (bit in bits) {
    i = strsrch(bit, "%^");
    if (i == -1) {
      continue;
    }
    octmess = bit[0..i-1];
    if (query_see_octarine()) {
      str = replace_string(str, sprintf("%%^OCTARINE:%s%%^", octmess),
                           octmess);
    } else {
      str = replace_string(str, sprintf("%%^OCTARINE:%s%%^", octmess), "");
    }
  }
  if (is_mxp_enabled()) {
    str = terminal_colour(str, _event_info->colour_map);
  } else {
    str = terminal_colour(str, _event_info->colour_map, width, indent);
  }
  return str;
}
void player_connected() {
  _event_info->last_term = 0;
  printf("%c%c%c", IAC, DO, TELOPT_TTYPE);
  printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE);
  printf("%c%c%c", IAC, DO, TELOPT_NAWS);
}
int set_term_type(string str) {
  if (!str) {
    notify_fail(sprintf("%-=*s", cols,
                "Syntax: "+query_verb()+" <term_type>\n"+
                "Where term type is one of the following: "+
                implode((string *)TERM_HANDLER->query_term_types(), ", ")+
                ".\nOr set it to \"network\", and the mud will try to "
                "figure it out itself.\n"));
    return 0;
  }
  if(str != term_name) {
    if (member_array(str, (string *)TERM_HANDLER->query_term_types()) != -1 ||
        str == "network") {
      if (str != "network") {
        _event_info->colour_map = (mapping)TERM_HANDLER->set_term_type(str, query_property(PLAYER_ALLOW_COLOURED_SOULS));
      } else {
        player_connected();
      }
      term_name = str;
      _event_info->cur_term = 0;
      write("Ok, terminal type set to "+str+".\n");
      return 1;
    } else {
      notify_fail("No such terminal type as " + str  + ".\n");
      return 0;
    }
  } else {
    notify_fail("Terminal type unchanged as " + str + ".\n");
    return 0;
  }
}
void set_term(string name) {
  term_name = name;
  _event_info->cur_term = 0;
}
int set_network_terminal_type(string name) {
  if (term_name != "network") return 0;
  if (!name) {
    _event_info->cur_term = "dumb";
    _event_info->colour_map = 0;
  }
  if (_event_info->colour_map =
      (mapping)TERM_HANDLER->set_network_term_type(name, query_property(PLAYER_ALLOW_COLOURED_SOULS))) {
    _event_info->cur_term = name;
    return 1;
  }
}
void reset_colour_map() {
   _event_info->colour_map = 0;
}
void event_commands(){
  add_command("rows", this_object(), "", (: set_our_rows(0) :));
  add_command("cols", this_object(), "", (: set_our_cols(0, 0) :));
  add_command("rows", this_object(), "<number>", (: set_our_rows($4[0]) :));
  add_command("cols", this_object(), "<number>", (: set_our_cols($4[0], 0) :));
  add_command("cols", this_object(), "test <number>", (: set_our_cols($4[0], 1) :));
  add_command("term", this_object(), "{" +
                implode((string *)TERM_HANDLER->query_term_types() +
                ({ "network" }), "|")+"}", (: set_term_type($4[0]) :));
  add_command("term", this_object(), "", (: set_term_type(0) :));
  add_command("inform", this_object(), "", (: do_inform(0) :));
  add_command("inform", this_object(), "<string>", (: do_inform($4[0]) :));
  if (this_object()->query_creator()) {
    add_command("busy", this_object(), "{on|off}", (: do_busy($4[0]) :));
    add_command("busy", this_object(), "<indirect:player>",
                (: do_busy_player($1) :));
  }
}
function get_htell_func(){
  if(file_name(previous_object()) != "/cmds/player/ht_ell")
    return 0;
  return (:do_tell_his:);
}
protected varargs int do_tell_his(string str, int brief) {
  string ret;
  mixed bit, *filter_history;
  if (str != "")  {
    filter_history = filter(tell_history,
                            (: strsrch(lower_case($1[0]), $(str)) > -1 :));
  }
  else filter_history = tell_history;
  if (!pointerp(filter_history) || !sizeof(filter_history)) {
    return notify_fail("You have not been told anything.\n");
  }
  if (undefinedp(brief))  brief = 0;
  ret = "$P$Tell History$P$Your tell history is:\n";
  foreach (bit in filter_history) {
    if (!brief) {
      ret += "** "+ctime(bit[2])+" **\n";
    }
    ret += fix_string("%s%s\n", cols, strlen(bit[0]), 0, bit[0], bit[1]);
  }
  write(ret);
  return 1;
}
int do_busy(string str) {
   if (str == "on") {
      _event_info->busy = 1;
   } else {
      _event_info->busy = 0;
   }
   write("Busy set to " + str + ".\n");
   return 1;
}
int do_busy_player(object *obs) {
   write("Ok, setting you as busy with " + query_multiple_short(obs) + ".\n");
   _event_info->busy = obs;
   return 1;
}
mixed query_busy() {
   if (pointerp(_event_info->busy)) {
      _event_info->busy -= ({ 0 });
   }
   if (pointerp(_event_info->busy) && !sizeof(_event_info->busy)) {
      _event_info->busy = 0;
   }
   return _event_info->busy;
}
void toggle_earmuffs() {
  earmuffs = !earmuffs;
}
void set_allow_friends_earmuffs() {
  earmuffs = PLAYER_ALLOW_FRIENDS_EARMUFF;
}
int check_earmuffs(string type, object person) {
  string *on;
  if (!earmuffs) {
    return 0;
  }
  on = (string *)this_object()->query_property(PLAYER_EARMUFF_PROP);
  if (!on) {
     return 0;
  }
  if (member_array(type, on) == -1) {
    return 0;
  }
  if (!person) {
    person = this_player();
  }
  if (person && earmuffs == PLAYER_ALLOW_FRIENDS_EARMUFF) {
    if (is_friend(person->query_name())) {
      return 0;
    }
  }
  return 1;
}
void set_rows(int i) {
  if (i < 5) {
     return ;
  }
  rows = i;
}
int query_rows() { return rows; }
private int set_our_rows(int val) {
  if (!val) {
    notify_fail("Rows currently set to " + rows + ".\nrows <number> to set.\n");
    return 0;
  }
  if (val <= 10) {
    notify_fail("Invalid number of rows.\n");
    return 0;
  }
  write("Rows set to " + val + ".\n");
  rows = val;
  return 1;
}
int query_cols() { return cols; }
void set_cols(int i) {
  if (i <= 10 || i > 999)
     return ;
   cols = i;
}
private int set_our_cols(int val, int test) {
  int cur;
  if(!val) {
    notify_fail("Columns currently set to " + cols + ".\ncols <number> to set.\n");
    return 0;
  }
  if(val <= 35 || val > 999) {
    notify_fail("Invalid column size.\n");
    return 0;
  }
  if (test)  {
    cur = cols;
    cols = val;
    write(implode(allocate(val, (: sprintf("%d", ($1 + 1) % 10) :)), "") + "\n");
    call_out((: cols = $(cur) :), 3);
    return 1;
  }
  write("Columns set to " + val + ".\n");
  cols = val;
  return 1;
}
void set_my_colours(string event_type, string colour) {
  if(colour == "default") {
    map_delete(my_colours, event_type);
  } else if(colour == "none") {
    my_colours[event_type] = "";
  } else {
    my_colours[event_type] = colour;
  }
}
mapping query_my_colours() {
  return my_colours;
}
void set_looked( object thing ) { _event_info->where = thing; }
mixed *reform_message( string message, mixed *things ) {
   int last, number;
   string before, middle, after, info;
   last = -1;
   if ( !things ) {
      things = ({ });
   } else {
      last = sizeof(things) - 1;
   }
   if ( !_event_info->where ) {
      _event_info->where = environment();
   }
   if (strsrch(message, "$L$") != -1) {
      while ( sscanf( message, "%s$L$%s$L$%s", before, middle, after ) == 3 ) {
         if (sscanf( middle, "[%s]%s", info, middle) == 2) {
            if (info[0..4] == "read:") {
               middle = LANGUAGE_HAND->garble_text(info[5..], middle, 0, this_object());
            } else {
               middle = LANGUAGE_HAND->garble_text_say(middle, info, this_object());
            }
         }
         message = sprintf("%s%s%s", before, middle, after);
      }
   }
   if (strsrch(message, "$R$") != -1) {
      while ( sscanf( message, "%s$R$%s$R$%s", before, middle, after ) == 3 ) {
         if ( sscanf( middle, "[%s]%s", info, middle ) != 2 ) {
            info = "";
         }
         switch ( middle[ 0 ] ) {
            case '-' :
               number = 0;
               middle = middle[ 1 .. ];
               break;
            case '+' :
               number = 1;
               middle = middle[ 1 .. ];
               break;
            default :
               number = 2;
         }
         if ( ( number == 2 ) || _event_info->where->query_relative( middle ) ) {
            if ( this_object()->query_creator() ) {
               message = sprintf("%s%s (%s)%s", before, find_rel(middle, number),
                                 middle, after);
            } else {
               message = sprintf("%s%s%s", before, find_rel(middle, number),
                                 after);
            }
         } else {
            message = sprintf("%s%s%s%s", before, info, middle, after);
         }
      }
   }
   if (strsrch(message, "$r$") != -1) {
      while ( sscanf( message, "%s$r$%s$r$%s", before, middle, after ) == 3 ) {
         if ( sscanf( middle, "[%s]%s", info, middle ) != 2 ) {
            info = "";
         }
         switch ( middle[ 0 ] ) {
            case '-' :
               number = 0;
               middle = middle[ 1 .. ];
               break;
            case '+' :
               number = 1;
               middle = middle[ 1 .. ];
               break;
            default :
               number = 2;
         }
         if ( ( number == 2 ) || _event_info->where->query_relative( LENGTHEN[ middle ] ) ) {
            if ( this_object()->query_creator() ) {
               message = sprintf("%s%s (%s)%s", before,
                                 SHORTEN[find_rel(LENGTHEN[middle], number)],
                                 middle, after);
            } else {
               message = sprintf("%s%s%s", before,
                                 SHORTEN[find_rel(LENGTHEN[middle], number)],
                                 after);
            }
         } else {
            message = sprintf("%s%s%s%s", before, info, middle, after);
         }
      }
   }
#ifdef DEBUG
   if ( this_object()->query_property( "see eemessages" ) )
      efun::tell_object( this_object(), "Looking at "+ message +".\n" );
#endif
   if (strsrch(message, "$M$") != -1) {
      while ( sscanf( message, "%s$M$%s$M$%s", before, middle, after ) == 3 ) {
#ifdef DEBUG
         if ( this_object()->query_property( "see eemessages" ) )
            efun::tell_object( this_object(), "Expanding "+ middle +".\n" );
#endif
         last++;
         message = sprintf("%s$%d$%s", before, last, after);
         things += ({ ({ }) });
         if (strsrch(middle, "$") == -1) {
            things[ last ] += ({ middle });
            middle = 0;
         } else {
            while ( sscanf( middle, "$%s$%s", info, middle ) == 2 ) {
#ifdef DEBUG
               if ( this_object()->query_property( "see eemessages" ) ) {
                  efun::tell_object( this_object(), "Found "+ info +".\n" );
               }
#endif
               things[ last ] += ({ "my_"+ info });
            }
         }
      }
   }
   if (strsrch(message, "$") != -1) {
      after = message;
      message = "";
      while ( sscanf( after, "%s$%s$%s", before, middle, after ) == 3 ) {
#ifdef DEBUG
         if ( this_object()->query_property( "see eemessages" ) )
            efun::tell_object( this_object(), "Trying "+ middle +".\n" );
#endif
         if ( sscanf( middle, "%s_short:%s", middle, info ) != 2 ) {
            message = sprintf("%s%s$%s", message, before, middle);
            after = sprintf("$%s", after);
            continue;
         }
         last++;
         message = sprintf("%s%s$%d$", message, before, last);
         things += ({ ({ sprintf("my_%s_short:%s", middle, info) }) });
      }
      message += after;
   }
   return ({ message, things });
}
void add_message( string message, mixed *things ) {
   int last;
   mixed *stuff;
   if ( !interactive( this_object() ) ) {
      return;
   }
   if ( strsrch( message, "$" ) == -1 ) {
      stuff = ({ message, things });
   } else  {
      stuff = reform_message( message, things );
   }
   _event_info->where = 0;
   if ( !sizeof( _event_info->eemessages ) ) {
      _event_info->eemessages = stuff;
   } else {
      last = sizeof( _event_info->eemessages ) - 2;
      if ( ( stuff[ 0 ] == _event_info->eemessages[ last ] ) &&
            ( sizeof( stuff[ 1 ] ) == 1 ) ) {
         if ( sizeof( filter( stuff[ 1 ][ 0 ], (: member_array($1, $2) != -1 :),
               _event_info->eemessages[ last + 1 ][ 0 ] ) ) ) {
            _event_info->eemessages += stuff;
         } else {
            _event_info->eemessages[ last + 1 ][ 0 ] += stuff[ 1 ][ 0 ];
         }
      } else {
         _event_info->eemessages += stuff;
      }
   }
#ifdef DEBUG
   if ( this_object()->query_property( "see eemessages" ) )
      efun::tell_object( this_object(), sprintf( "%O\n", _event_info->eemessages ) );
#endif
}
string get_pretty_short( object thing, int dark ) {
  if (dark && environment(thing) != this_object()) {
    if (living(thing) && thing->query_race_ob() &&
        (thing->query_race_ob())->query_humanoid()) {
      return "someone";
    } else {
      return "something";
    }
  }
  if ( !thing->query_visible( this_object() ) ) {
    if (living(thing) && thing->query_race_ob() &&
        (thing->query_race_ob())->query_humanoid()) {
      return "someone";
    } else {
      return "something";
    }
  }
#ifdef USE_ROLE_PLAYING_SHORTS
   if(interactive(thing) &&
      this_object()->query_role_playing() &&
      !this_object()->is_friend(thing->query_name())) {
     return thing->query_short_desc();
   }
#endif
   return (string)thing->pretty_short( this_object() ) +
         (string)thing->hide_invis_string();
}
string get_pretty_plural( object thing, int dark ) {
   if (dark && environment(thing) != this_object()) {
      if (living(thing)) {
         return "people";
      } else {
         return "things";
      }
   }
   if ( !thing->query_visible( this_object() ) ) {
      return "things";
   }
#ifdef USE_ROLE_PLAYING_SHORTS
   if(interactive(thing) &&
      this_object()->query_role_playing() &&
      !this_object()->is_friend(thing->query_name())) {
     return thing->query_plural_desc();
   }
#endif
   return (string)thing->pretty_plural( this_object() ) +
         (string)thing->hide_invis_string();
}
string my_mirror_short( object thing, string arg) {
   if (objectp(thing)  &&  userp(thing))
      return thing->short(0, 0);
   return arg;
}
string my_a_short( object thing, string arg, int dark) {
   string article;
   if (!thing) {
      return "something";
   }
   if (dark && environment(thing) != this_object()) {
     if (living(thing) && thing->query_race_ob() &&
         (thing->query_race_ob())->query_humanoid()) {
       if (environment(thing) != environment()) {
         return "someone";
       }
     } else {
       return "something";
     }
   }
   if ( !objectp( thing ) ) {
     return "an unknown object";
   }
   article = (string)thing->query_determinate( this_object() );
   if ( !article ) {
      return add_a( (string)this_object()->get_pretty_short( thing, dark ) );
   }
   return article + (string)this_object()->get_pretty_short( thing, dark );
}
string my_the_short( object thing, string arg, int dark ) {
   string article;
   if (dark && environment(thing) != this_object()) {
     if (living(thing) && thing->query_race_ob() &&
         (thing->query_race_ob())->query_humanoid()) {
         if (environment(thing) == environment()) {
            return "someone";
         }
      } else {
         return "something";
      }
   }
   if ( !objectp( thing ) ) {
      return "the unknown object";
   }
   article = (string)thing->query_determinate( this_object() );
   if ( !article || ( article == "a " ) || ( article == "an " ) )
      return "the "+ (string)this_object()->get_pretty_short( thing, dark );
   return article + (string)this_object()->get_pretty_short( thing, dark );
}
int some_more( string word ) {
    return sizeof( filter( all_inventory( _event_info->where ),
        (: $1->query_plural() == $(word) &&
           $1->query_visible(this_object()) :))) > 1;
}
string my_one_short( object thing, string arg, int dark ) {
   string article, its_plural;
   if (dark && environment(thing) != this_object()) {
     if (living(thing) && thing->query_race_ob() &&
         (thing->query_race_ob())->query_humanoid()) {
         if (environment(thing) == environment()) {
            return "someone";
         }
      } else {
         return "something";
      }
   }
   if ( !objectp( thing ) ) {
      return "one of the unknown objects";
   }
   if ( environment( thing ) != environment() ) {
      _event_info->where = this_object();
   } else {
      _event_info->where = environment();
   }
   article = (string)thing->query_determinate( this_object() );
   if ( !article || ( article == "a " ) || ( article == "an " ) ) {
      its_plural = (string)this_object()->get_pretty_plural( thing, dark );
      if ( some_more( its_plural ) ) {
         return "one of the "+ its_plural;
      }
      return "the "+ (string)this_object()->get_pretty_short( thing, dark );
   }
   return article + (string)this_object()->get_pretty_short( thing, dark );
}
string my_poss_short(object thing, string arg, int dark) {
   string its_plural;
   string article;
   string of_whom;
   if (dark && environment(thing) != this_object()) {
     if (living(thing) && thing->query_race_ob() &&
         (thing->query_race_ob())->query_humanoid()) {
         if (environment(thing) == environment()) {
            return "someone";
         }
      } else {
         return "something";
      }
   }
   if ( !objectp( thing ) ) {
      return "an unknown object";
   }
   if(living(thing)) {
     if (thing == this_object()) {
       return "your";
     } else {
       of_whom = this_object()->get_pretty_short( thing, dark );
       if(of_whom[<1] == 's')
         of_whom = of_whom + "'";
       else
         of_whom = of_whom +"'s";
       return of_whom;
     }
   }
   _event_info->where = environment( thing );
   if ( !_event_info->where ) {
      return my_a_short( thing, arg, dark );
   }
   if ( !living( _event_info->where ) && !_event_info->where->query_corpse() ) {
      return my_a_short( thing, arg, dark );
   }
#ifdef DEBUG
   if ( this_object()->query_property( "see eemessages" ) )
      efun::tell_object( this_object(), sprintf( "%O\n", _event_info->had_shorts ) );
#endif
   if ( _event_info->where == this_object() ) {
      of_whom = "your ";
   } else {
      if ( member_array( _event_info->where, _event_info->had_shorts ) != -1 ) {
         of_whom = (string)_event_info->where->query_possessive() +" ";
      } else {
        of_whom = my_the_short( _event_info->where, arg, dark );
        if(of_whom[<1] == 's') {
          of_whom = of_whom + "' ";
        } else {
          of_whom = of_whom +"'s ";
        }
      }
   }
   if ( !article || ( article == "a " ) || ( article == "an " ) ) {
      its_plural = (string)this_object()->get_pretty_plural( thing, dark );
      if ( some_more( its_plural ) ) {
         return "one of "+ of_whom + its_plural;
      }
   }
   return of_whom + (string)this_object()->get_pretty_short( thing, dark );
}
string my_the_poss_short(object thing, string arg, int dark) {
   string its_plural;
   string article;
   string of_whom;
   if (dark && environment(thing) != this_object()) {
      if (living(thing)) {
         if (environment(thing) == environment()) {
            return "someone's";
         }
      } else {
         return "something's";
      }
   }
   if ( !objectp( thing ) ) {
      return "an unknown object's";
   }
   article = (string)thing->query_determinate(this_object());
   if(!article || (article == "a " || article == "an "))
     article = "the ";
   if(living(thing)) {
     if (thing == this_object()) {
       return "your";
     } else {
       of_whom = this_object()->get_pretty_short( thing, dark );
       if(of_whom[<1] == 's')
         of_whom = of_whom + "'";
       else
         of_whom = of_whom +"'s";
       return article + of_whom;
     }
   }
   _event_info->where = environment( thing );
   if ( !_event_info->where ) {
      return my_the_short( thing, arg, dark );
   }
   if ( !living( _event_info->where ) && !_event_info->where->query_corpse()) {
      return my_the_short(thing, arg, dark);
   }
#ifdef DEBUG
   if ( this_object()->query_property( "see eemessages" ) )
      efun::tell_object(this_object(), sprintf("%O\n",
                                               _event_info->had_shorts));
#endif
   if ( _event_info->where == this_object() ) {
     of_whom = "your ";
   } else {
     if(member_array( _event_info->where, _event_info->had_shorts ) != -1) {
       debug_printf("Had shorts");
       of_whom = (string)_event_info->where->query_possessive() +" ";
     } else {
       of_whom = my_the_short(_event_info->where, arg, dark);
       if(of_whom[<1] == 's') {
         of_whom = of_whom + "' ";
       } else {
         of_whom = of_whom +"'s ";
       }
     }
   }
   its_plural = (string)this_object()->get_pretty_plural( thing, dark );
   if(some_more(its_plural))
     return "one of "+ article + of_whom + its_plural;
   return of_whom + article + this_object()->get_pretty_short(thing, dark);
}
protected void clear_event_info_had_shorts() { _event_info->had_shorts = ({ }); }
varargs string calc_shorts( string *short_list, int exact ) {
   int i;
   int dark;
   string list;
   string str;
   string desc;
   object ob;
   object *things;
   string *descs_str;
   mixed *descs_ob;
   mixed *parts;
   function number;
   descs_str = ({ });
   descs_ob  = ({ });
   if (!_event_info->had_shorts)  clear_event_info_had_shorts();
   if (exact) {
      number = (: query_num($1) :);
   } else {
      number = (: query_num($1, 20) :);
   }
   if (environment()) {
      dark = this_object()->check_dark(environment()->query_light());
   }
   foreach (str in short_list) {
      parts = explode( str, ":" );
      if (sizeof(parts) == 2) {
         ob = find_object( parts[ 1 ] );
      } else if (sizeof(parts) > 2) {
         parts[1] = implode(parts[ 1.. ], ":");
         ob = find_object( parts[1] );
      } else {
         ob = 0;
         parts += ({ "" });
      }
#ifdef DEBUG
      if ( this_object()->query_property( "see eemessages" ) )
         efun::tell_object( this_object(), sprintf( "%O\n", ob ) );
#endif
      if (ob) {
         _event_info->had_shorts = ({ ob }) + _event_info->had_shorts;
      }
      if ( ob == this_object() ) {
         if (parts[0] == "my_poss_short" || parts[0] == "my_the_poss_short") {
            desc = "your";
         } else {
            desc = "you";
         }
      } else if (sizeof(parts) >= 2) {
#ifdef DISBALED
         desc = (string)call_other( this_object(), parts[0], ob, parts[1], dark);
#else
         switch(parts[0]) {
         case "my_mirror_short":
           desc = my_mirror_short(ob, parts[1]);
           break;
         case "my_a_short":
           desc = my_a_short(ob, parts[1], dark);
           break;
         case "my_the_short":
           desc = my_the_short(ob, parts[1], dark);
           break;
         case "my_one_short":
           desc = my_one_short(ob, parts[1], dark);
           break;
         case "my_poss_short":
           desc = my_poss_short(ob, parts[1], dark);
           break;
         case "my_the_poss_short":
           desc = my_the_poss_short(ob, parts[1], dark);
           break;
         }
#endif
      } else {
         if (sizeof(parts[0])) {
            desc = parts[0];
         } else {
            desc = "something";
         }
      }
      i = member_array(desc, descs_str);
      if (i == -1) {
         descs_str += ({ desc });
         descs_ob += ({ ({ ob }) });
      } else {
         descs_ob[i] += ({ ob });
      }
   }
   i = member_array( "you", descs_str );
   if ( i != -1 && i != sizeof(descs_str) - 1) {
      descs_str = descs_str[0..i-1] + descs_str[i+1..] + ({ "you" });
      descs_ob = descs_ob[0..i-1] +  descs_ob[i+1..] + descs_ob[i..i];
   }
   list = "";
 {
      for ( i = 0; i < sizeof( descs_str ); i++ ) {
         things = descs_ob[ i ];
         if ( sizeof( things ) == 1 ) {
            if (exact)  {
               if (things[0]) {
                  list += "one " + things[0]->short();
               } else {
                  list += descs_str[i];
               }
            } else {
               list += descs_str[ i ];
            }
         } else {
            things -= ({ 0 });
            if ( sizeof(things) ) {
               list += evaluate(number, sizeof(things)) + " " +
                     this_object()->get_pretty_plural( things[ 0 ], dark );
            } else {
               list += evaluate(number, sizeof(things)) + " unknown objects";
            }
         }
         if ( i == sizeof( descs_str ) - 1 ) {
            continue;
         }
         if ( i == sizeof( descs_str ) - 2 ) {
            list += " and ";
         } else {
            list += ", ";
         }
      }
   }
   return list;
}
string indent_column(string column, int width, int pad) {
   int left;
   int right;
   int space;
   string *parts;
   string part;
   mixed stuff;
   string ret;
   ret = "";
   if ( column[ 0 .. 2 ] != "$I$" ) {
      column = "$I$0=$C$"+ column;
   }
   parts = explode( column, "$C$" );
   parts = parts[0..0] + map(parts[1..], (: capitalize($1) :));
   parts = explode( implode(parts, ""), "$I$" );
   foreach ( part in parts) {
      sscanf( part, "%s=%s", stuff, part );
      if ( stuff[ 0 ] == ' ' ) {
         space = !space;
      }
      stuff = explode( stuff, "," );
      if ( stuff[ 0 ] != "" ) {
         switch ( stuff[ 0 ][ 0 ] ) {
            case '+' :
               if ( space && ( left > 0 ) && ( part != "" ) ) {
                  part = SPACES[ 0 .. left - 1 ] + part;
               }
               left += to_int( stuff[ 0 ][ 1 .. ] );
               break;
            case '-' :
               left -= to_int( stuff[ 0 ][ 1 .. ] );
               if ( left < 0 ) {
                  left = 0;
               }
               if ( space && ( left > 0 ) && ( part != "" ) ) {
                  part = SPACES[ 0 .. left - 1 ] + part;
               }
               break;
            default :
               left = to_int( stuff[ 0 ] );
         }
      } else {
         left = 0;
      }
      if ( sizeof( stuff ) > 1 ) {
         switch ( stuff[ 1 ][ 0 ] ) {
            case '+' :
               right += to_int( stuff[ 1 ][ 1 .. ] );
               break;
            case '-' :
               right -= to_int( stuff[ 1 ][ 1 .. ] );
               if ( right < 0 )
                  right = 0;
               break;
            default :
               right = to_int( stuff[ 1 ] );
         }
      } else {
         right = 0;
      }
#ifdef DEBUG
      if ( this_object()->query_property( "see eemessages" ) )
         efun::tell_object( this_object(), part +"\n"+
               left +", "+ right +", "+ cols +"\n" );
#endif
      if ( left > 0 ) {
         ret += fix_string( part, width - right, left, pad);
      } else {
         ret += fix_string( part, width - right, 0, pad );
      }
   }
   return ret;
}
string fit_message( string message ) {
   int i;
   int j;
   int size;
   int width;
   int ok;
   string* columns;
   string num;
   mixed* stuff;
   string ret;
   if ( strlen( message ) < 6 ) {
      return message;
   }
   columns = explode( message, "$COLUMN$" );
   if (sizeof(columns) > 1) {
      stuff = allocate(sizeof(columns), ({ }));
      width = cols;
      for (i = 0; i < sizeof(columns) - 1; i++) {
         if (sscanf(columns[i], "%s=%s", num, columns[i]) == 2) {
            size = to_int(num);
         } else {
            size = 10;
            columns[i] += "\nMust specify a column size.\n";
         }
         width -= size;
         stuff[i] = ({ size }) + explode(indent_column(columns[i], size, 1), "\n");
      }
      stuff[<1] = ({ width }) + explode(indent_column(columns[<1], width, 0), "\n");
      j = 1;
      ret = "";
      do {
         ok = 0;
         for (i = 0; i < sizeof(stuff); i++) {
            if (sizeof(stuff[i]) > j) {
               if (sizeof(stuff[i]) > j + 1) {
                  ok = 1;
               }
               ret += stuff[i][j];
            } else if (i < sizeof(stuff) -1) {
               ret += sprintf("%*s ", stuff[i][0] - 1, "");
            }
         }
         j++;
         ret += "\n";
         ret = fix_string(ret);
      } while (ok);
   } else {
      ret = indent_column(columns[0], cols, 0);
   }
   return ret;
}
string fix_for_mxp(string input) {
    return replace(input, ({
                          "&", "&amp;",
                          "<", "&lt;", ">", "&gt;",
                          "\n", mxp_next_secure(this_object()) + "<BR>",
                          "MXP&lt;", "<", "MXP&gt;", ">" }));
}
void show_message( string message ) {
   string bit;
   if ( sscanf( message, "$P$%s$P$%s", bit, message ) == 2 ) {
      this_object()->more_string( fit_message( message ), bit, 1 );
   } else {
      if (has_mxp(this_object())) {
         efun::tell_object( this_object(), fix_for_mxp( fit_message( message ) ));
      } else {
         efun::tell_object( this_object(), fit_message( message ) );
      }
   }
}
string evaluate_message( mixed *stuff ) {
   int i;
   string message, start, finish, verb_sing, verb_plur;
   message = stuff[ 0 ];
   clear_event_info_had_shorts();
   for ( i = 0; i < sizeof( stuff[ 1 ] ); i++ ) {
      message = replace_string( message, "$"+ i +"$",
            calc_shorts( stuff[ 1 ][ i ] ) );
      while ( sscanf( message, "%s$V$"+ i +"=%s,%s$V$%s", start, verb_sing,
            verb_plur, finish ) == 4 ) {
         if ( ( sizeof( stuff[ 1 ][ i ] ) == 1 ) &&
               sizeof(_event_info->had_shorts) &&
               objectp( _event_info->had_shorts[ 0 ] ) ) {
            if ( _event_info->had_shorts[ 0 ]->query_property( "group object" ) ||
                  _event_info->had_shorts[ 0 ]->group_object() ) {
               message = sprintf("%s%s%s", start, verb_plur, finish);
            } else {
               message = sprintf("%s%s%s", start, verb_sing, finish);
            }
         } else {
            message = sprintf("%s%s%s", start, verb_plur, finish);
         }
      }
   }
   return message;
}
void print_messages() {
   int i;
   string message;
   mixed *messages;
   messages = _event_info->eemessages;
   _event_info->eemessages = ({ });
   for ( i = 0; i < sizeof( messages ); i += 2 ) {
      message = messages[ i ];
      if ( sizeof( messages[ i + 1 ] ) ) {
         message = evaluate_message( ({ message, messages[ i + 1 ] }) );
      }
      show_message( message );
   }
   _event_info->where = 0;
}
string convert_message( string message ) {
  if(message)
    message = evaluate_message( reform_message( message, ({ }) ) );
  _event_info->where = 0;
  return message;
}
nomask varargs void event_inform( object, mixed mess, string which,
                           object thing ) {
  string *on, inform_col;
  int add_friend_later;
  on = inform_types;
  if (!on) {
     on = ({ });
  }
  if(this_object()->query_property( "inform repressed" ) || !sizeof( on))
      return;
  if(thing && thing->query_creator() && !thing->query_visible(this_object()))
    return;
  if (which == "logon" && is_friend(thing->query_name()) &&
      member_array("friend", on) != -1 ) {
    which = "friend";
  } else if ( ( which == "logon" || which == "link-death" ) &&
      PLAYERINFO_HANDLER->query_alerts_for(thing->query_name()) &&
      member_array("alert", on) != -1 ) {
    which = "alert";
  } else if(member_array(which, on) == -1 ) {
    return;
  }
  if(INFORM_COLOURS[which]) {
    inform_col = colour_event(which, INFORM_COLOURS[which]);
  } else {
    inform_col = colour_event(which, INFORM_COLOURS["default"]);
  }
  if(which == "friend") {
    add_friend_later = 0;
    if(!mess) {
      mess = " -- " + query_friend_tag(thing->query_name());
    } else if ( stringp( mess ) ) {
      mess += " -- " + query_friend_tag(thing->query_name());
    } else {
      add_friend_later = 1;
    }
    if (INFORM_COLOURS["friend"]) {
      inform_col = colour_event(which, INFORM_COLOURS["friend"]);
    }
  }
  if (functionp(mess)) {
    mess = evaluate(mess, this_object());
    if ( stringp( mess ) && add_friend_later ) {
      mess += "%^RESET%^%^" + inform_col + "%^ -- " +
        query_friend_tag(thing->query_name());
    }
  }
  if(which == "logon" && this_object()->query_lord() &&
     !check_earmuffs("verbose-logon", this_object()) &&
     strsrch(mess, "enters") != -1)
    mess +=  " %^RESET%^%^" + inform_col + "%^" + query_ip_name(thing);
  this_object()->add_message( "[%^"+ inform_col +"%^"+ mess +"%^RESET%^]\n",                              ({ }) );
}
protected void enter_exit_mess( string mess, object thing, int going ) {
   int i;
   string part, verb, *words;
   mess = replace_string( mess, "$N", "$0$" );
   words = explode( mess, " " );
   for ( i = sizeof( words ) - 1; i > -1; i-- ) {
      if ( ( sscanf( words[ i ], "%s$s%s", verb, part ) == 2 ) &&
            ( ( part[ 0 ] < 97 ) || ( part[ 0 ] > 122 ) ) ) {
         words[ i ] = "$V$0="+ pluralize( verb ) +","+ verb +"$V$"+ part;
      }
      if ( sscanf( words[ i ], "%%%s%%%s", verb, part ) == 3 ) {
         words[ i ] = "$V$0="+ pluralize( verb ) +","+ verb +"$V$"+ part;
      }
   }
   if ( going ) {
      this_object()->add_message( implode( words, " " ) +"\n",
            ({ ({ "my_the_short:"+ file_name( thing ) }) }) );
   } else {
      this_object()->add_message( implode( words, " " ) +"\n",
            ({ ({ "my_a_short:"+ file_name( thing ) }) }) );
   }
}
void event_enter( object thing, string mess, object ) {
  if ( !stringp( mess ) )
    return;
  thing->sneak_task(this_object());
  this_object()->perception_task(thing);
  if ( !thing->query_visible( this_object() ) ) {
    return;
  }
  enter_exit_mess( mess, thing, 0 );
}
void event_exit( object thing, string mess, object to ) {
   ::event_exit( thing, mess, to );
   if ( !stringp( mess ) )
      return;
   if ( !thing->query_visible( this_object() ) )
      return;
   enter_exit_mess( mess, thing, 1 );
}
void event_death( object thing, object *, object killer,
      string room_mess, string killer_mess ) {
   if ( this_object() == thing ) {
      return;
   }
   if ( ( this_object() == killer ) && stringp( killer_mess ) ) {
      this_object()->add_message( replace( killer_mess, "$D",
            (string)thing->the_short() ), ({ }) );
      print_messages();
      return;
   }
   if ( stringp( room_mess ) ) {
      if ( objectp( killer ) ) {
         this_object()->add_message( replace( room_mess,
               ({ "$D", (string)thing->the_short(),
               "$K", (string)killer->the_short() }) ), ({ }) );
      } else {
         this_object()->add_message( replace( room_mess, "$D",
               (string)thing->the_short() ), ({ }) );
      }
      print_messages();
   }
}
void event_say(object caller, string str, mixed avoid, string language) {
  if (pointerp(avoid)) {
    if (member_array(this_object(), avoid) != -1) {
      return ;
    }
  } else if (avoid == this_object()) {
    return ;
  }
  if (language) {
      this_object()->add_message( LANGUAGE_HAND->garble_text_say(str,
                                  language, this_object()), ({ }) );
   } else {
     this_object()->add_message( str, ({ }) );
   }
}
void event_see( object caller, string words, object thing, mixed avoid ) {
   if ( !thing->query_visible( this_object() ) )
      return;
   event_say( caller, words, avoid, 0 );
}
void event_write(object caller, string str, string language) {
   if (language) {
     this_object()->add_message( LANGUAGE_HAND->garble_text_say(str,
                                    language, this_object()), ({ }) );
   } else {
      this_object()->add_message( str, ({ }) );
   }
   print_messages();
}
void do_efun_write( string str, string language ) {
   event_write( 0, str, language );
}
varargs void event_soul(object ob, string str, mixed avoid) {
  if (ob != this_object()) {
    if (strsrch(str, "%^") != -1) {
      if (!query_property(PLAYER_ALLOW_COLOURED_SOULS)) {
         str = strip_colours(str);
      }
    }
    if (sizeof(avoid) > 1 && check_earmuffs("multiple-soul", ob)) {
      return ;
    }
    event_say(ob, colour_event("soul", "") + "$C$" + str + "%^RESET%^", avoid, 0);
  } else {
    event_write( ob, str + "%^RESET%^", 0 );
  }
}
void event_emote( object thing, string mess ) {
   if ( thing == this_object() )
      return;
   this_object()->add_message( colour_event("emote", "%^CYAN%^") + mess + "%^RESET%^", ({ }) );
}
void event_person_say(object ob, string start, string mess, string lang,
                      string accent) {
   string *args, astr, tstr;
   int mangle_accent;
   if(ob == this_object() )
      return;
   if (accent) {
      if (query_nationality_accent_ob() != accent) {
         if (query_mangle_accent()) {
            mangle_accent = 2;
         } else {
            mangle_accent = 1;
         }
      }
   }
   if((lang != query_default_language() && lang != "general") ||
       (accent && mangle_accent == 1)) {
     tstr = start[0..<3];
     if(lang != query_default_language() && lang != "general")
       tstr += " in " + cap_words(lang);
     if(accent && mangle_accent == 1) {
       astr = accent->query_accent_name();
       if(astr[0] == 'a' || astr[0] == 'e' || astr[0] == 'i' ||
          astr[0] == 'o' || astr[0] == 'u')
         astr = "an " + astr;
       else
         astr = "a " + astr;
       tstr += " with " + astr + " accent";
     }
     start = tstr + ": ";
   }
   if(this_object()->query_property(SHORTHAND_OUTPUT_PROP)) {
     mess = LANGUAGES->fix_shorthand(mess);
   }
   args = LANGUAGE_HAND->garble_say(lang, start, mess, this_object(),
                                    ob, SAY_TYPE);
   start = args[ 0 ];
   mess = args[ 1 ];
   if (accent && mangle_accent == 2) {
      mess = accent->garble_say(mess, this_object(), ob, SAY_TYPE,
                                query_default_language());
   }
   this_object()->add_message( "$I$5=" + colour_event("say", "%^CYAN%^") +
                               "$C$"+ start +
                               mess +"%^RESET%^\n",
             ({ }) );
}
void add_tell_history(string start, string mess, int remote) {
  if (!pointerp(tell_history)) {
    tell_history = ({ });
  }
  tell_history +=  ({ ({ start, mess, time(), remote }) });
  if (sizeof(tell_history) > MAX_TELL_HIS) {
    tell_history = tell_history[1..];
  }
}
 void event_person_tell( object ob, string start, string mess) {
   int id;
   string *args;
   string tmp;
   if ( this_object()->query_property( "ignoring" ) ) {
      if ( member_array( (string)ob->query_name(),
           (string *)this_object()->query_property( "ignoring" ) ) != -1 &&
           !ob->query_creator()) {
         tell_object(ob,this_object()->query_name()+" is ignoring you and "
                     "will not have heard what you said.\n");
         return;
      }
   }
   if(this_object()->query_property(SHORTHAND_OUTPUT_PROP))
     mess = LANGUAGES->fix_shorthand(mess);
   if (_event_info->busy && (!pointerp(_event_info->busy) ||
                             member_array(ob, _event_info->busy) == -1)) {
     tell_object(ob, this_object()->query_cap_name() +
                  " is currently busy with "
                  "someone else, " + this_object()->query_pronoun() +
                  " has heard this message and will get back to "
                  "you shortly.\n");
      start = "[BUSY] " + start;
   }
   add_tell_history(start, mess, 0);
   tmp = fix_string(replace(colour_event("tell", "%^YELLOW%^"),
                                         "%^", "%%^") +
                                 "%s%s%%^RESET%%^\n",
                                 cols, 5, 0, capitalize(start), mess);
   if (has_mxp(this_object())) {
      efun::tell_object(this_object(), fix_for_mxp(tmp));
   } else {
      efun::tell_object(this_object(), tmp);
   }
   if (userp(this_object()) &&  interactive( this_object() ) &&
      (id = query_idle(this_object())) > TELL_WARN_TIME) {
     args = ({ });
     if (id/(60*60))
        args += ({ (id/(60*60))+" hours" });
     if ((id/60)%60)
        args += ({ ((id/60)%60)+" minutes" });
     if (id%60)
        args += ({ (id%60)+" seconds" });
     write(this_object()->query_name()+" has been idle for "+
           query_multiple_short(args)+".\n");
   }
   if ( this_object()->query_property( PASSED_OUT ) ) {
      write( "Something tells you that $C$"+
            (string)this_object()->query_name() +
            " will be unable to reply to you just yet.\n" );
   }
}
void event_whisper(object ob, string start, string mess,
                   object *obs, string lang, object me) {
   string blue;
   string *args;
   blue = "";
   if (me == this_object())
      return;
   if (lang != query_default_language() && lang != "general")
     blue = " in " + cap_words(lang);
   if(this_object()->query_property(SHORTHAND_OUTPUT_PROP))
     mess = LANGUAGES->fix_shorthand(mess);
   if ( member_array( this_object(), obs ) == -1)  {
      if(ob->query_visible(this_object()))
         this_object()->add_message( "$I$5=" +
                                   colour_event("whisper", "%^CYAN%^") + "$C$"+
                                   start +
                                   query_multiple_short( obs ) +
                                   ".%^RESET%^\n", ({ }) );
   } else {
      args = LANGUAGE_HAND->garble_say(lang, start, mess, this_object(),
                                    ob, WHISPER_TYPE);
      start = args[ 0 ];
      mess = args[ 1 ];
      if ( sizeof( obs ) == 1 ) {
         this_object()->add_message( "$I$5=" +
                                     colour_event("whisper", "%^CYAN%^") +
                                     "$C$"+ start +"you"+
                                     blue +": "+ mess +"%^RESET%^\n", ({ }) );
      } else {
         this_object()->add_message( "$I$5=" +
                                     colour_event("whisper", "%^CYAN%^") +
                                     "$C$"+ start +
                                     query_multiple_short( obs ) + blue +": " +
                                     mess +"%^RESET%^\n",
                                     ({ }) );
      }
   }
}
void event_person_shout( object thing, string start, string mess, string lang,
      int *co_ord, int range ) {
   mixed *args;
   if ( this_object() == this_player() ) {
      return;
   }
   if ( check_earmuffs( "shout", thing ) ) {
      return;
   }
   if ( !environment() ) {
      return;
   }
   if ( environment()->query_property( "shout zone" ) !=
        environment( this_player() )->query_property( "shout zone" ) ) {
      return;
   }
   if (lang != query_default_language() && lang != "general") {
      start += " in " + capitalize(lang);
   }
   if (sizeof(query_ignoring(({ this_player() }))) ) {
      return ;
   }
   args = LANGUAGE_HAND->garble_say(lang, start, mess, this_object(),
                                    thing, SHOUT_TYPE);
   start = args[ 0 ];
   mess = args[ 1 ];
   if(this_object()->query_property(SHORTHAND_OUTPUT_PROP))
     mess = LANGUAGES->fix_shorthand(mess);
   if ( environment() == environment( this_player() ) ) {
      this_object()->add_message( "$I$5=" + colour_event("shout", "") + "$C$"+
                                  start +": "+ mess +"%^RESET%^\n", ({ }) );
      return;
   }
   if ( sizeof( co_ord ) != 3 ) {
      return;
   }
   BROADCASTER->broadcast_event( ({ this_object() }), co_ord, start +
      ": "+ mess, range, 1, 0 );
}
void event_newbie(object thing, string message) {
  string tmp;
  if((this_player() == this_object() ) ||
     check_earmuffs("newbie", this_player())) {
    return;
  }
  if (sizeof(query_ignoring(({ this_player() }))) ) {
    return ;
  }
  if(this_object()->query_property(SHORTHAND_OUTPUT_PROP))
    message = LANGUAGES->fix_shorthand(message);
  tmp = fix_string(replace(colour_event("newbie", "%^MAGENTA%^"),
                                       "%^", "%%^") +
                               "(newbie)%%^RESET%%^ %s\n",
                               cols, 5, 0, message);
  if (has_mxp(this_object())) {
     efun::tell_object(this_object(), fix_for_mxp(tmp));
  } else {
     efun::tell_object(this_object(), tmp);
  }
}
void event_newbiehelpers(object thing, string message) {
  string tmp;
  if((this_player() == this_object() ) ||
     check_earmuffs("newbiehelpers", this_player()) ||
     !NEWBIEHELPERS_HANDLER->query_helper_access(this_object())) {
    return 0;
  }
  if (sizeof(query_ignoring(({ this_player() }))) ) {
    return 0;
  }
  if(this_object()->query_property(SHORTHAND_OUTPUT_PROP))
    message = LANGUAGES->fix_shorthand(message);
  tmp = fix_string(replace(colour_event("newbiehelpers",
                                  "%^YELLOW%^"), "%^", "%%^") +
                               "(newbiehelpers)%%^RESET%%^ %s\n",
                               cols, 5, 0, message);
  if (has_mxp(this_object())) {
     efun::tell_object(this_object(), fix_for_mxp(tmp));
  } else {
     efun::tell_object(this_object(), tmp);
  }
}
void event_combat(object thing, string message, object *exclude, int verbose) {
  if(member_array(this_object(), exclude) != -1)
    return;
  if(verbose && !this_object()->query_verbose("combat"))
    return;
  this_object()->add_message(colour_event("combat", "%^WHITE%^") + "$C$" +
                             message + "%^RESET%^", ({ }));
  this_object()->print_messages();
}
nomask void event_creator_tell(object ob, string start, string mess,
                               int forced, string channel) {
  string tmp;
  if (!channel)
    channel = "cre";
  if (ob == this_object() ||
      ((sizeof(this_object()->query_ignoring( ({ ob }) ) ) ||
        check_earmuffs( channel, ob )) && !forced) ||
      !this_object()->query_creator()) {
    return;
  }
  if(member_array(channel, this_object()->channel_list()) == -1)
    return;
  if(this_object()->query_property(SHORTHAND_OUTPUT_PROP))
    mess = LANGUAGES->fix_shorthand(mess);
  tmp = fix_string(replace(colour_event(channel, "%^CYAN%^"),
                                       "%^", "%%^") +
                               "(" + channel + ") %s%s%%^RESET%%^\n",
                               cols, 5, 0, start, mess);
  if (has_mxp(this_object())) {
     efun::tell_object(this_object(), fix_for_mxp(tmp));
  } else {
     efun::tell_object(this_object(), tmp);
  }
}
nomask void event_lord_tell( object ob, string start, string mess,
      int forced ) {
  string tmp;
  if ( this_player() == this_object() ) {
      HIST_HANDLER->add_lord_history(start, mess);
      return;
   }
  if (ob == this_object()
     || (check_earmuffs("lord", ob) && !forced) ||
      !master()->query_lord((string)this_object()->query_name()))
    return;
  if(this_object()->query_property(SHORTHAND_OUTPUT_PROP))
     mess = LANGUAGES->fix_shorthand(mess);
  tmp = fix_string(replace(colour_event("lord", "%^YELLOW%^"),
                                       "%^", "%%^") +
                               "(lord) %s%s%%^RESET%%^\n",
                               cols, 5, 0, start, mess);
  if (has_mxp(this_object())) {
     efun::tell_object(this_object(), fix_for_mxp(tmp));
  } else {
     efun::tell_object(this_object(), tmp);
  }
}
void event_inter_creator_tell(object ob, string mname, string pname,
                              string mess, object ig, int emote) {
   string tmp;
  if (!this_object()->query_creator() || check_earmuffs("inter-creator-tell", 0)
      || this_object() == ig)
    return ;
   tmp = fix_string("%s@%s%s%s\n", cols, strlen(mname) + strlen(pname) + 3,
                      0, pname, mname, (emote?" ":": "), mess);
  if (has_mxp(this_object())) {
     efun::tell_object(this_object(), fix_for_mxp(tmp));
  } else {
     efun::tell_object(this_object(), tmp);
  }
}
void event_intermud_tell(object ob, string start, string mess,
                         string channel, object ig) {
  string tmp;
  if (!this_object()->query_creator() || check_earmuffs("intermud-all", 0)
      || check_earmuffs(channel, 0) || this_object() == ig) {
    return ;
  }
  tmp = fix_string("%%^MAGENTA%%^(%s)%%^RESET%%^ %s%s\n", cols,
                      strlen(start)+ strlen(channel)+ 3, 0, channel, start,
                      mess);
  if (has_mxp(this_object())) {
     efun::tell_object(this_object(), fix_for_mxp(tmp));
  } else {
     efun::tell_object(this_object(), tmp);
  }
}
void event_player_echo_to(object ob, string mess, object me) {
  if ( master()->query_lord( (string)this_object()->query_name() ) )
     this_object()->add_message( "$0$ echos to you:\n", ({ ({ "my_the_short:"+
            file_name( me ) }) }) );
   this_object()->add_message( colour_event("echo", "") + mess + "%^RESET%^",
                               ({ }) );
}
void event_player_emote_all(object ob, string mess) {
  if (ob == this_object()) {
    return;
  }
  if ( master()->query_lord( (string)this_object()->query_name() ) ) {
     this_object()->add_message( "$0$ emotes to all:\n", ({ ({ "my_the_short:"+
            file_name( ob ) }) }) );
  }
  mess = this_object()->colour_event( "emoteall" ) + mess + "%^RESET%^";
  this_object()->add_message( "$I$5=$C$"+ replace_string( mess, "$N", "$0$" ),
    ({ ({ "my_the_short:"+ file_name( ob ) }) }) );
}
void event_player_echo(object ob, string mess) {
   if (ob == this_object()) {
      return;
   }
   if ( master()->query_lord( (string)this_object()->query_name() ) ) {
      this_object()->add_message( "$0$ echos:\n", ({ ({ "my_the_short:"+
            file_name( ob ) }) }) );
   }
   this_object()->add_message( mess, ({ }) );
}
void receive_snoop(string mess) {
  tell_object(this_object(), "] "+mess);
}
void terminal_type(string type) {
  if (set_network_terminal_type(type)) {
    tell_object(this_object(), "Setting your network terminal type to \""+
                type+"\".\n");
  } else {
    if (term_name == "network") {
      if (!_event_info->last_term || _event_info->last_term != type) {
        _event_info->last_term = type;
        printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE);
      } else
        tell_object(this_object(), "Unknown terminal type \""+type+"\".\n");
    }
  }
}
void window_size(int width, int height) {
  if (term_name == "network") {
    if (width > 10 && width < 256) {
      set_cols(width);
   }
   if (height > 5 && height < 256) {
      set_rows(height);
   }
   tell_object(this_object(), "Your machine told our machine that your "
               "terminal has "+height+" rows and "+width+" columns.\n");
  }
}
void mxp_enable() {
   efun::tell_object(this_object(),
               sprintf("%c%c%c%c%c%c", IAC, SB, TELOPT_MXP, IAC, SE, 0) +
               sprintf("%c[1z", 27) +
               replace_string(read_file("/doc/login/mxp_setup"), "\n", "") + "\n");
}