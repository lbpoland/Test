
==================================================
FILE: alias.c
==================================================

#include <alias.h>
#include <player.h>
inherit "/global/history";
mapping aliases;
nosave mapping doing_alias;
protected void exec_alias(string verb, string args);
protected string *expand_alias(string verb, string args);
protected void set_doing_alias(string verb);
protected int is_doing_alias(string verb);
protected string *run_alias(string verb, string args);
int remove_alias_thing(string);
protected int alias(string);
protected int edit_alias(string);
int add_player_alias(string name, mixed *value) {
   if (file_name(previous_object()) != ALIAS_CMD &&
       file_name(previous_object()) != EDIT_ALIAS_CMD) {
      return 0;
   }
   if(name == "unalias" || name == "alias" || name == "ealias")
     return 0;
   aliases[name] = value[0..1023];
   return 1;
}
mixed *query_player_alias(string name) {
  if(!mapp(aliases))  {
    aliases = ([ ]);
    return 0;
  }
   return copy(aliases[name]);
}
int remove_player_alias(string name) {
   if ((file_name(previous_object()) != UNALIAS_CMD) &&
       name != "" &&
       !this_player(1)->query_lord()) {
      printf("%O\n", file_name(previous_object()));
      return 0;
   }
   map_delete(aliases, name);
   return 1;
}
void alias_commands() {
   add_command("END_ALIAS", "<string>", (:remove_alias_thing($4[0]):));
}
int remove_all_aliases() {
   if (!this_player(1)->query_lord()) {
      write("You can't do that :)\n");
      return 0;
   }
   aliases = ([ ]);
   return 1;
}
mapping query_aliases() {
   return copy(aliases);
}
int is_alias(string verb) {
   return aliases[verb] != 0;
}
protected void exec_alias(string verb, string args) {
   string *bing;
   string comm;
   bing = run_alias(verb, args);
   if (bing) {
      set_doing_alias(verb);
      foreach (comm in bing) {
         command(comm);
      }
   }
}
protected string *run_alias(string verb, string args) {
   if (!mapp(aliases)) {
      aliases = ([ ]);
   }
   if (!aliases[verb] || is_doing_alias(verb)) {
      return 0;
   }
   return expand_alias(verb, args);
}
protected int is_doing_alias(string verb) {
   if (!doing_alias) {
      doing_alias = ([ ]);
   }
   if (doing_alias[verb]) {
      return 1;
   }
   return 0;
}
protected void set_doing_alias(string verb) {
  doing_alias[verb] = 1;
  in_alias_command++;
}
protected string *expand_alias(string verb, string args) {
   int i;
   int num;
   string *bits;
   string line;
   mixed stuff;
   string *ret;
   if (!aliases[verb]) {
      return ({ verb + " " + args });
   }
   ret = ({ });
   stuff = aliases[verb];
   line = "";
   if (!args) {
      args = "";
   }
   bits = explode(verb + " " + args, " ");
   for (i = 0; i < sizeof(stuff); i++) {
      if (stringp(stuff[i])) {
         line += stuff[i];
      } else {
         num = stuff[i] & ALIAS_MASK;
         switch (stuff[i] - num) {
         case NEW_LINE :
            ret += ({ line });
            line = "";
            break;
         case ALL_ARGS :
            line += args;
            break;
         case ONE_ARG  :
            if (num < sizeof(bits)) {
               line += bits[num];
            }
            break;
         case TO_ARG   :
            line += implode(bits[1..num], " ");
            break;
         case FROM_ARG :
            line += implode(bits[num..100], " ");
            break;
         case ALL_ARG  :
            i++;
            if (args == "") {
               line += stuff[i];
            } else {
               line += args;
            }
            break;
         case ARG_THING :
            i++;
            if (num < sizeof(bits)) {
               line += bits[num];
            } else {
               line += stuff[i];
            }
            break;
         case ALL_IFARG :
            i++;
            if (args == "") {
               i += stuff[i];
            }
            break;
         case IFARG_THING :
            i++;
            if (num >= sizeof(bits)) {
               i += stuff[i];
            }
            break;
         case ELSE_THING :
            i++;
            i += stuff[i];
            break;
         case CURR_LOC :
            i++;
            line += file_name(environment())+".c";
            break;
         case END_IF :
            break;
         }
      }
   }
   if (line != "") {
      ret += ({ line });
   }
   ret += ({ "END_ALIAS " + verb });
   return ret[0..1023];
}
int remove_alias_thing(string verb) {
   in_alias_command--;
   map_delete(doing_alias, verb);
   this_player()->adjust_time_left(-DEFAULT_TIME);
   return 1;
}

==================================================
FILE: auto_load.c
==================================================

#include <move_failures.h>
#include <virtual.h>
#include <player.h>
#define AUTO_STR_LENGTH 3
#define AUTO_LOAD_TYPE 0
#define AUTO_LOAD_NAME 1
#define AUTO_LOAD_DATA 2
#define AUTO_LOAD_STATIC_ARG  0
#define AUTO_LOAD_DYNAMIC_ARG 1
private mixed auto_load;
private nosave int _no_calls;
private nosave function _finished;
private void auto_clone_alt( object thing, mixed *load_info,
                     object dest, object tell_pl, function move_f, string name);
private object *int_auto_load(int type, string name, mixed *load_info,
                              object dest, object tell_pl, int now,
                              function move_f);
private void move_to_destination(object thing, object dest, object tell_pl,
                                 function move_f);
string *fragile_auto_str_ob(object ob) {
   mixed static_arg;
   mixed dynamic_arg;
   string fname;
   static_arg = ob->query_static_auto_load();
   dynamic_arg = ob->query_dynamic_auto_load();
   if (!static_arg && !dynamic_arg) {
      return ({ });
   }
   if ( sscanf( file_name( ob ), "%s#%*d", fname) == 2 ) {
      return  ({ 1, fname, ({ static_arg, dynamic_arg }) });
   } else {
      return ({ 0, file_name(ob), ({ static_arg, dynamic_arg }) });
   }
}
private string *auto_str_ob(object ob) {
   string static_arg;
   string dynamic_arg;
   string catch_static;
   string catch_dynamic;
   string fname;
   int value;
   string ob_name;
   mixed* tmp;
   catch_static = catch(static_arg = (string)ob->query_static_auto_load());
   catch_dynamic = catch(dynamic_arg = (string)ob->query_dynamic_auto_load());
   if (!static_arg && !dynamic_arg) {
      if (catch_static || catch_dynamic) {
         catch(value = ob->query_value());
         ob_name = "unknown object";
         catch(ob_name = ob->short(1));
         catch(PLAYER_RECEIPT->set_object(file_name(ob)));
         PLAYER_RECEIPT->set_obname(ob_name);
         PLAYER_RECEIPT->set_value(value);
         catch(PLAYER_RECEIPT->set_static_data(({ static_arg, dynamic_arg })));
         tmp = fragile_auto_str_ob(find_object("/obj/misc/al_receipt"));
         tmp[0] = 1;
         if (!undefinedp(tmp[2][1]["::"]["cloned by"])) {
           tmp[2][1]["::"]["cloned by"] = "greco";
         }
      } else {
         tmp = ({ });
      }
      return tmp;
   }
   if ( sscanf( file_name( ob ), "%s#%*d", fname ) == 2 ) {
      return  ({ 1, fname, ({ static_arg, dynamic_arg }) });
   } else {
      return ({ 0, file_name( ob ), ({ static_arg, dynamic_arg }) });
   }
}
string *create_auto_load(object *obs, int into_array) {
  int i;
  string *tmp;
  string *al_tmp;
  if (into_array) {
    auto_load = ({ });
  } else {
    tmp = ({ });
  }
  for (i = sizeof(obs) - 1; i >= 0; i--) {
    reset_eval_cost();
    if (!objectp(obs[i])) {
       continue;
    }
    if (!catch(al_tmp = auto_str_ob(obs[i]))) {
      if (into_array) {
         auto_load += al_tmp;
      } else {
         tmp += al_tmp;
      }
    }
  }
  return tmp;
}
void load_auto_load_alt( mixed *auto_string, object dest,
                                   object tell_pl, function finished) {
   int i;
   reset_eval_cost();
   if ( !auto_string || !sizeof( auto_string ) ) {
      return;
   }
   if ( !pointerp( auto_string ) ) {
      return;
   }
   if ( ( dest == this_object() ) &&
        ( tell_pl == this_object() ) &&
        !this_object()->query_no_check() ) {
      this_object()->set_no_check( 1 );
      this_object()->set_max_weight( 100 + this_object()->query_max_weight() );
   }
   _finished = finished;
   reset_eval_cost();
   for ( i = 0; i < sizeof( auto_string ); i += AUTO_STR_LENGTH) {
      _no_calls++;
      call_out( (: int_auto_load :), i / 6,
                                     auto_string[ i + AUTO_LOAD_TYPE ],
                                     auto_string[ i + AUTO_LOAD_NAME ],
                                     auto_string[ i + AUTO_LOAD_DATA ],
                                     dest, tell_pl, 0, (: $1->move($2) :));
   }
}
object *load_auto_load_to_array( mixed *auto_string, object tell_pl ) {
   object *obs;
   int i;
   obs = ({ });
   if (!tell_pl) {
      tell_pl = this_player();
   }
   if (!tell_pl) {
      tell_pl = this_object();
   }
   for ( i = 0; i < sizeof( auto_string ); i += AUTO_STR_LENGTH) {
      _no_calls++;
      obs += int_auto_load(auto_string[ i + AUTO_LOAD_TYPE ],
                           auto_string[ i + AUTO_LOAD_NAME ],
                           auto_string[ i + AUTO_LOAD_DATA ],
                           0, tell_pl, 1, (: MOVE_OK :));
   }
   return obs - ({ 0 });
}
void load_auto_load_to_inventory(mixed *auto_string, object dest,
                                 object tell_pl, function move_f) {
   int i;
   if (!tell_pl) {
      tell_pl = this_player();
   }
   if (!tell_pl) {
      tell_pl = this_object();
   }
   for ( i = 0; i < sizeof( auto_string ); i += AUTO_STR_LENGTH) {
      _no_calls++;
      int_auto_load(auto_string[ i + AUTO_LOAD_TYPE ],
                    auto_string[ i + AUTO_LOAD_NAME ],
                    auto_string[ i + AUTO_LOAD_DATA ],
                    dest, tell_pl, 0, move_f);
   }
}
private object create_auto_load_object( string name,
                                        mixed *load_info,  object dest,
                                        object tell_pl, function move_f) {
   object thing;
   catch(name = (string)CLONER->other_file( name ));
   if ( !catch( thing = (object)CLONER->clone( name ) ) ) {
      if ( thing ) {
         if ( base_name( thing ) == name ) {
            auto_clone_alt(thing, load_info, dest, tell_pl, move_f, name);
         } else {
            move_to_destination(thing, dest, tell_pl, move_f);
         }
      } else {
  tell_object( tell_pl, "%^RED%^Could not clone "+ name +
         ".%^RESET%^\n" );
  thing = clone_object( PLAYER_RECEIPT );
  thing->set_object( name );
  thing->set_static_save( load_info );
  move_to_destination(thing, dest, tell_pl, move_f);
      }
   } else {
      tell_object( tell_pl, "%^RED%^Error in loading "+ name +
       ".%^RESET%^\n" );
      thing = clone_object( PLAYER_RECEIPT );
      thing->set_object( name );
      thing->set_static_save( load_info );
      move_to_destination(thing, dest, tell_pl, move_f);
   }
   return thing;
}
private object *int_auto_load(int type, string name, mixed *load_info,
                              object dest, object tell_pl, int now,
                              function move_f) {
   object thing;
   object new_thing;
   mixed *stuff;
   int reduce;
   _no_calls--;
   if ( type ) {
      thing = create_auto_load_object(name, load_info, dest, tell_pl, move_f);
      if ( name == PLAYER_RECEIPT) {
         stuff = thing->query_static_save();
         if (stuff) {
            new_thing = create_auto_load_object(name, load_info, dest,
                                         tell_pl, move_f);
            if (new_thing) {
               thing->dest_me();
               thing = new_thing;
            }
         }
      }
   } else {
      if ( !find_object( name ) ) {
         if ( !catch( load_object( name ) ) ) {
            thing = find_object( name );
            if ( thing ) {
               auto_clone_alt(thing, load_info, dest, tell_pl, move_f, name);
            } else {
               tell_object( tell_pl, "%^RED%^Could not load "+ name +
          ".%^RESET%^\n" );
            }
         } else {
            tell_object( tell_pl, "%^RED%^Error in loading "+ name +
       ".%^RESET%^\n" );
         }
      } else {
         tell_object( tell_pl, "%^RED%^Object "+ name +
          " exists.%^RESET%^\n" );
      }
   }
   if (_no_calls == 0 && _finished) {
      evaluate(_finished, this_object());
      _finished = 0;
      this_object()->set_no_check( 0 );
      reduce = (int)this_object()->query_max_weight() -
             (int)this_object()->query_loc_weight();
      if ( reduce > 1 ) {
         if ( reduce > 100 ) {
            reduce = 100;
         }
         this_object()->set_max_weight( (int)this_object()->query_max_weight() -
                                 reduce );
      }
      this_object()->calc_burden();
   }
   if (thing) {
      return ({ thing });
   }
   return ({ });
}
private string ident( object thing ) {
   mixed word;
   catch(word = (string)thing->query_short());
   if ( stringp( word ) ) {
      return "\""+ word +"\"";
   }
   return file_name( thing );
}
private void auto_clone_alt( object thing, mixed *load_info,
                     object dest, object tell_pl, function move_f, string name) {
   string ob_path;
   reset_eval_cost();
   if ( load_info[ AUTO_LOAD_STATIC_ARG ] ) {
      catch( thing->init_static_arg( load_info[ AUTO_LOAD_STATIC_ARG ],
                                     tell_pl ) );
   }
   catch( thing->set_player( tell_pl ) );
   if ( load_info[ AUTO_LOAD_DYNAMIC_ARG ] ) {
      catch( thing->init_dynamic_arg( load_info[ AUTO_LOAD_DYNAMIC_ARG ],
                                      tell_pl ));
   }
   ob_path = thing->query_property(VIRTUAL_NAME_PROP);
   if (ob_path) {
      ob_path = CLONER->other_file( ob_path );
      if (file_size(ob_path) < 0) {
         thing->dest_me();
         thing = clone_object( PLAYER_RECEIPT );
         thing->set_object( name );
         thing->set_static_save( load_info );
         thing->set_virtobname( ob_path );
      } else {
         thing->add_property(VIRTUAL_NAME_PROP, ob_path);
      }
   }
   ob_path = CLONER->illegal_thing(base_name(thing), thing->query_short());
   if(ob_path) {
     thing->dest_me();
     thing = clone_object( ob_path );
   }
   move_to_destination(thing, dest, tell_pl, move_f);
}
private void move_to_destination(object thing, object dest, object tell_pl,
                                 function move_f) {
   object place;
   int ret_val;
   string catch_str;
   place = dest;
   ret_val = MOVE_OK - 1;
   while ( place && ret_val != MOVE_OK) {
      catch_str = catch( ret_val =  evaluate(move_f, thing, place ) );
      if(catch_str) {
        tell_object(tell_pl, "%^RED%^Error moving object: " + catch_str +
        ".%^RESET%^\n");
        ret_val = MOVE_OK - 1;
      }
      if (ret_val != MOVE_OK) {
         if ( environment( place ) ) {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       ident( place ) +" (move returned " +
                         catch_str + "); attempting to move it into "+
                  ident( environment( place ) ) +".%^RESET%^\n" );
            place = environment( place );
         } else if ( ( place != environment(tell_pl) ) &&
                     environment( tell_pl ) ) {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       ident( place ) +" (move returned " +
                         ret_val + "); attempting to move it into "
       "environment of " + tell_pl->query_name() +
       ".%^RESET%^\n" );
            place = environment( tell_pl );
         } else  if (place != find_object("/room/broken")) {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       ident( place ) +" (move returned " + ret_val +
                         "); moving it to the room for broken objects "+
                         "--- please ask a creator for help.%^RESET%^\n" );
            load_object("/room/broken");
            place = find_object( "/room/broken" );
         } else {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       " the room for broken objects "+
       "--- This is a serious errror!  Please tell a "
       "creator immediately.%^RESET%^\n");
            place = 0;
         }
         move_f = (: $1->move($2) :);
      }
   }
}
int query_auto_loading() {
   return _no_calls > 0;
}
protected mixed query_auto_load_string() {
   return auto_load;
}
protected void set_auto_load_string(mixed str) {
   auto_load = str;
}

==================================================
FILE: auto_mailer.c
==================================================

#include <mail.h>
#include <player_handler.h>
int auto_mail(string to,
              string from,
              string sub,
              string cc,
              string body,
              int send_inter,
              string only_to,
              int flag)
{
  if (PLAYER_HANDLER->test_player(from) &&
      this_player() &&
      from != this_player()->query_name()) {
    write("AUTO_MAILER: Illegal access!\n");
    unguarded((: write_file, "/log/CHEAT",
           "Illegal access to AUTO_MAILER.\n" "Backtrace: " +
           back_trace() :));
    return 0;
  }
  return MAILER->do_mail_message(to, from, sub, cc, body,
                 send_inter, only_to, flag);
}

==================================================
FILE: cloner.c
==================================================

#define SAVE_FILE "/save/cloner"
#define SAVE_FILE_DELAY 15
#define LIFE_TIME 7257600
inherit "/std/object";
mapping changes;
mapping illegal;
private nosave int _save_file_call_out;
mapping query_changes() {
   return changes;
}
void save_file() {
   _save_file_call_out = 0;
   unguarded((: save_object, SAVE_FILE:));
}
void load_file() {
   if (file_size(SAVE_FILE + ".o") > 0)
      unguarded((: restore_object, SAVE_FILE:));
}
void setup() {
   changes = ([]);
   illegal = ([]);
   load_file();
   _save_file_call_out = 0;
}
object clone( string word ) {
   string new_file;
   object thing;
   if ( changes[ word ] && new_file = changes[ word ][ 0 ] )
      word = new_file;
   catch( thing = clone_object( word ) );
   return thing;
}
string other_file( string word ) {
   if ( changes[ word ] )
      return changes[ word ][ 0 ];
   return word;
}
int add_mapping( string from, string to ) {
  string obj_name;
  if(from[<2..] == ".c")
    from = from[0..<3];
  if(to[<2..] == ".c")
    to = to[0..<3];
  if((file_size(to) < 1) && (file_size(to+".c") < 1)) {
    write("Destination file does not exist\n");
    return 0;
  }
  changes[from] = ({to, time()});
  if ( !_save_file_call_out ) {
        _save_file_call_out = call_out( (: save_file :), SAVE_FILE_DELAY );
  }
  if ( !this_player() ) {
      obj_name = file_name( previous_object() );
  }
  else {
      obj_name = this_player()->query_cap_name();
  }
  write("Mapping of "+from+" to "+to+" added.\n");
  log_file("CLONER", "Mapping of "+from+" to "+to+" added by "+
           obj_name +" at "+ctime(time())+".\n");
  remove_call_out("clean_up");
  call_out("clean_up", 120 + random(500));
  return 1;
}
int remove_mapping( string from ) {
   string obj_name;
   if ( changes && changes[ from ] ) {
      map_delete( changes, from );
      save_file();
      write( "Mapping of " + from + " removed.\n" );
      if ( !this_player() ) {
          obj_name = file_name( previous_object() );
      }
      else {
          obj_name = this_player()->query_cap_name();
      }
      log_file( "CLONER", "Mapping of " + from + " removed by " +
          obj_name + " at " + ctime( time() ) + ".\n" );
      return 1;
   }
   write("No mapping found for " + from + ".\n");
   return 0;
}
string list_mappings( string str ) {
   string from, retval;
   retval = "";
   foreach(from in keys(changes)) {
      if (!str ||
          strsrch(from, str) != -1 ||
          strsrch(changes[from][0], str) != -1)
         retval += from + " -> " + changes[from][0] + "\n";
   }
   return retval;
}
int add_illegal(string basename, string short, string replacement) {
  if(!illegal)
    illegal = ([ ]);
  if(illegal[basename + ":" + short])
    return 0;
  if((file_size(replacement) < 1) && (file_size(replacement+".c") < 1))
    return 0;
  illegal[basename + ":" + short] = replacement;
  save_file();
  return 1;
}
int remove_illegal(string basename, string short) {
  if(!illegal)
    return 0;
  if(!illegal[basename+":"+short])
    return 0;
  map_delete(illegal, basename+":"+short);
  save_file();
  return 1;
}
mapping query_illegal() {
  return illegal;
}
string illegal_thing(string basename, string short) {
  if(!illegal)
    return 0;
  return illegal[basename + ":" + short];
}
void clean_up() {
   string from;
   mixed  *to;
   foreach(from, to in changes)
      if ((to[1] < time() - LIFE_TIME) ||
          ((file_size(to[0]) < 1) && (file_size(to[0] + ".c") < 1)))
         map_delete(changes, from);
   save_file();
}

==================================================
FILE: command.c
==================================================

#include <command.h>
nosave string current_verb, current_cmd;
private nosave int Forced;
private nosave string *SearchPath;
protected void create() {
   current_verb = "";
  SearchPath = ({ DIR_LIVING_CMDS });
}
string query_current_verb() { return current_verb; }
string query_current_cmd() { return current_cmd; }
protected int cmdAll(string args) {
  class command verb;
  mixed tmp;
  verb = new(class command);
  verb->args = args;
  current_cmd = args;
  if( !((int)CMD_D->GetCommand(verb, SearchPath)) ) {
    return 0;
  }
   current_verb = verb->verb;
  if (CMD_D->IsGRCommand(verb->filepart) &&
      !this_object()->query_known_command(verb->verb))
    return 0;
  if (this_object()->command_shadowed(verb->verb, verb->args))
    return 1;
  if( !(tmp = (mixed)call_other(verb->file, "cmd", verb->args, verb->verb)) )
    return 0;
  else if( stringp(tmp) ) {
    write("Error: "+tmp+"\n");
    return 1;
  }
  else return 1;
}
protected mixed *cmdPatterns(string verb) {
  if (CMD_D->IsGRCommand(verb) &&
      !this_object()->query_known_command(verb))
    return 0;
  return CMD_D->GetCommandPatterns(verb, SearchPath);
}
protected void command_commands() {
#if efun_defined(add_action)
  add_action( "cmdAll", "*", -1 );
#endif
}
int eventForce(string cmd) {
  string err;
  int res;
  if(member_array(call_stack(0)[1],
                  ({  "/cmds/creator/show_help.c",
                      "/d/am/broad_way/cryer_order.c",
                      "/obj/handlers/new_soul.c",
                      "/std/living/force.c"
                        })) == -1)
    error("illegal force");
  Forced = 1;
  err = catch(res = command(cmd));
  Forced = 0;
  if(err) error(err);
  return res;
}
string *AddSearchPath(mixed val) {
  if (stringp(val)) {
     val = ({ val });
  } else if(!pointerp(val)) {
     error("Bad argument 1 to AddSearchPath()\n");
  }
  SearchPath = uniq_array(SearchPath + val);
  return SearchPath;
}
string *RemoveSearchPath(mixed val) {
  if(stringp(val)) {
    val = ({ val });
  } else if(!pointerp(val)) {
    error("Bad argument 1 to RemoveSearchPath()\n");
  }
  SearchPath -= val;
  return SearchPath;
}
string *GetSearchPath() { return SearchPath; }
int GetForced() { return Forced; }
string GetClient() { return 0; }

==================================================
FILE: communicate.c
==================================================

#include <drinks.h>
#include <library.h>
#include <player.h>
#include <language.h>
#define TELL_CMD "/cmds/player/t_ell"
#define REMOTE_CMD "/cmds/player/rem_ote"
class language_info {
   string cur_lang;
   int mangle_accent;
   string default_lang;
}
private int *_sp = ({0, 0});
private class language_info cur_lang;
private mixed *tell_reply_list = ({ 0, 0 });
private nosave object converse_ob;
string drunk_speech(string str);
string expand_nickname(string str);
private int converse(string);
private int do_write(string);
private int do_repeat(string);
string query_current_language();
void communicate_commands() {
  add_command("converse", "", (: converse(0) :));
  add_command("converse", "<string'person'>", (: converse($4[0]) :));
  add_command("frimble", "<string>", (: do_write($4[0]) :));
  add_command("repeat", "<string'command'>", (: do_repeat($4[0]) :));
}
int query_real_max_sp() {
  int ret;
  ret = sqrt(this_object()->query_time_on() / -15);
  if(ret < 50)
    return 50;
  if(ret > 500)
    return 500;
  return ret;
}
int query_max_sp() { return _sp[1]; }
int adjust_max_sp( int number ) {
   _sp[1] += number;
   if ( _sp[1] < 0 )
      _sp[1] = 0;
   number = query_real_max_sp();
   if ( _sp[1] > number )
      _sp[1] = number;
   return _sp[1];
}
int set_max_sp( int number ) { return adjust_max_sp( number - _sp[1] ); }
int query_sp() { return _sp[0]; }
int adjust_sp( int number ) {
  if (_sp[0] + number < 0)
    return -1;
  if (number < 0)
    adjust_max_sp(1);
  _sp[0] += number;
  if ( _sp[0] > _sp[1] )
    _sp[0] = _sp[1];
  return _sp[0];
}
int set_sp( int number ) {
   return adjust_sp( number - _sp[0] );
}
void comm_event( mixed thing, string type, string start, string rest,
      string lang, string accent ) {
   if ( !objectp( thing ) && !pointerp( thing ) ) {
      return;
   }
   event( thing, type, start, rest, lang, accent );
   call_other(all_inventory(), "event_" + type, this_object(),
              start, rest, lang, accent);
}
void comm_event_to(object ob, string event_type, string start, string type,
                   string words, object *others, string lang, object me,
                   string accent) {
  event(ob, event_type, start, type, words, others, lang, me, accent);
}
void do_whisper(object ob, string event_type, string start, string type,
                string words, object *others, string lang, object me,
                string accent) {
  event(ob, event_type, start, type, words, others, lang, me, accent);
}
private int do_write(string arg) {
  if (!arg || arg == "") {
    notify_fail("Syntax: "+query_verb()+" <string>\n");
    return 0;
  }
  write(sprintf("$I$0=%s\n", arg));
  this_player()->adjust_time_left(-DEFAULT_TIME);
  return 1;
}
private int converse(string str) {
  if (!LANGUAGE_HAND->query_language_spoken(query_current_language())) {
    notify_fail(capitalize(query_current_language())+" is not a spoken language.\n");
    return 0;
  }
  if (str) {
    if (!LANGUAGE_HAND->query_language_distance(query_current_language())) {
      notify_fail(capitalize(query_current_language())+" is not able to spoken at a "+
                  "distance.\n");
      return 0;
    }
    str = lower_case(str);
    str = (string)this_object()->expand_nickname(str);
    converse_ob = find_player(str);
    if (!converse_ob)
      converse_ob = find_living(str);
    if (!converse_ob) {
      notify_fail("Syntax: converse [player]\n");
      return 0;
    }
    if (converse_ob == this_object()) {
      notify_fail("You have a nice conversation with yourself. Gee, what fun.\n");
      return 0;
    }
  }
  write("Give '**' to stop.\n");
  write("] ");
  input_to("do_converse");
  return 1;
}
void do_converse(string str) {
  if(str == "**") {
    write("Ok.\n");
    converse_ob = 0;
    return;
  }
  if(str)
    if (!converse_ob)
      "/cmds/living/sa_y"->cmd( str );
    else
      if ( function_exists( "trap_tell", environment() ) )
        environment()->trap_tell( str, converse_ob, 1 );
      else
        TELL_CMD->cmd( str, converse_ob, 1 );
  write("] ");
  input_to("do_converse");
}
void add_language(string lang) {
  int lvl;
  string skill;
  if (!LANGUAGE_HAND->test_language(lang))
    return ;
  if (LANGUAGE_HAND->query_language_spoken(lang)) {
    skill = LANGUAGE_HAND->query_language_spoken_skill(lang);
    lvl = this_object()->query_skill(skill);
    this_object()->add_skill_level(skill, 100 - lvl);
  }
  if (LANGUAGE_HAND->query_language_written(lang) ||
      LANGUAGE_HAND->query_language_magic(lang)) {
    skill = LANGUAGE_HAND->query_language_written_skill(lang);
    lvl = this_object()->query_skill(skill);
    this_object()->add_skill_level(skill, 100 - lvl);
  }
}
private void fixup_lang_class() {
   mixed tmp;
   if (!classp(cur_lang)) {
      tmp = cur_lang;
      if (!tmp) {
         tmp = "common";
      }
      cur_lang = new(class language_info);
      cur_lang->cur_lang = tmp;
      cur_lang->default_lang = "common";
      cur_lang->mangle_accent = 1;
   }
}
int set_language(string str) {
  if (!LANGUAGE_HAND->test_language(str))
    return 0;
  fixup_lang_class();
  cur_lang->cur_lang = str;
  return 1;
}
string query_current_language() {
  fixup_lang_class();
  return cur_lang->cur_lang;
}
void set_default_language(string def) {
  fixup_lang_class();
  cur_lang->default_lang = def;
}
string query_default_language() {
  fixup_lang_class();
  return cur_lang->default_lang;
}
void set_mangle_accent(int flag) {
   fixup_lang_class();
   cur_lang->mangle_accent = flag;
}
int query_mangle_accent() {
   fixup_lang_class();
   return cur_lang->mangle_accent;
}
private int do_repeat(string str) {
  if (!str) {
    notify_fail("Syntax: repeat <cmd>\n");
    return 0;
  }
  input_to("do_wombat_repeat", 0, str);
  write("Enter the commands you wish to pass to "+str+".  '**' on a line "+
        "by itself to exit.\n");
  write("] ");
  return 1;
}
protected int do_wombat_repeat(string str, string com) {
  if (str == "**") {
    return 0;
  }
  write("Doing '"+com+" "+str+"\n");
  command(com+" "+str);
  write("] ");
  input_to("do_wombat_repeat", 0, com);
  return 0;
}
object *query_ignoring(object *people)  {
   string *ignore;
   object *fail = ({ });
   ignore = this_object()->query_property( "ignoring" );
   if ( ignore )  {
      fail = filter_array( people,
                (: member_array( $1 && $1->query_name(), $(ignore) ) > -1 :) );
   }
   return fail;
}
object *query_ignored_by(object *people) {
   return filter(people, (: sizeof($1->query_ignoring( ({ this_player() }) )) :));
}
int set_tell_reply_list(mixed list) {
  if (base_name(previous_object())[0 .. strlen(TELL_CMD) - 1] != TELL_CMD &&
      base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
     !previous_object()->query_lord())
    return 0;
  tell_reply_list = ({time() + (60 * 15), list });
  return 1;
}
mixed query_tell_reply_list() {
  if(base_name(previous_object())[0..strlen(TELL_CMD) - 1] != TELL_CMD &&
     base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
     !previous_object()->query_lord())
    return 0;
  if(tell_reply_list[0] < time())
    return 0;
  return tell_reply_list[1];
}

==================================================
FILE: creator.c
==================================================

#include <login_handler.h>
inherit "/global/wiz_file_comm";
#define ECHO_ALLOWED
void move_player_to_start(string bong, int new_pl, string c_name, string ident, int go_invis) {
  if(!sscanf(file_name(previous_object()), "/secure/login#%*s") &&
     !sscanf(file_name(previous_object()), "/secure/nlogin#%*s"))
    return 0;
#ifndef NEW_DRIVER
#endif
  ::move_player_to_start(bong, new_pl, c_name, ident, go_invis);
  write(LOGIN_HANDLER->get_message("/doc/CREATORNEWS"));
  if(query_invis()) {
    tell_object(this_object(), "===> You are currently INVISIBLE! <===\n");
  }
}
int query_creator() { return 1; }
string query_object_type(object) {
   if ( master()->query_senior( query_name() ) )
      return "S";
   return "C";
}
void receive_snoop(string bing) {
  tell_object(this_object(), "] "+bing);
}

==================================================
FILE: events.c
==================================================

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

==================================================
FILE: family.c
==================================================

#include <clubs.h>
#include <player.h>
class family_information {
   string name;
   string* adjectives;
   string id;
   string* titles;
   string cur_title;
   string* clubs;
   string force_title;
   int force_timeout;
}
#define FAMILY_CLASS_SIZE 8
private class family_information _family_name;
string query_name();
int set_family_name(string name);
int add_player_title(string title);
void remove_player_title(string title);
private class family_information create_family_info() {
   class family_information bing;
   bing = new(class family_information);
   bing->adjectives = ({ });
   bing->titles = ({ "mr", "miss", "mrs", "ms" });
   bing->clubs = ({ });
   return bing;
}
protected void setup_default_titles() {
   if (!_family_name) {
       return;
   }
   _family_name->titles = ({ "mr", "miss", "mrs", "ms" });
}
private void update_adjectives() {
   if (!_family_name) {
      return ;
   }
   _family_name->adjectives = ({ });
   _family_name->id = 0;
   if (_family_name &&
       _family_name->name) {
      _family_name->adjectives = explode(lower_case(_family_name->name), " ")[0..<2];
      _family_name->id = explode(lower_case(_family_name->name), " ")[<1];
   }
   if (_family_name &&
       _family_name->cur_title) {
      _family_name->adjectives += explode(_family_name->cur_title, " ");
   }
}
void check_family_name() {
   class family_information frog;
   string bing;
   if (!classp(_family_name) &&
       _family_name) {
      bing = (string)_family_name;
      _family_name = create_family_info();
      set_family_name(bing);
   }
   if (classp(_family_name) &&
       sizeof(_family_name) == 5) {
      frog = new(class family_information);
      frog->adjectives = _family_name->adjectives;
      frog->id = _family_name->id;
      frog->cur_title = _family_name->cur_title;
      frog->name = _family_name->name;
      frog->titles = _family_name->titles;
      frog->clubs = ({ });
      _family_name = frog;
   }
   if (classp(_family_name) &&
       sizeof(_family_name) == 6) {
      frog = new(class family_information);
      frog->adjectives = _family_name->adjectives;
      frog->id = _family_name->id;
      frog->cur_title = _family_name->cur_title;
      frog->name = _family_name->name;
      frog->titles = _family_name->titles;
      frog->clubs = _family_name->clubs;
      _family_name = frog;
   }
   if (_family_name &&
       _family_name->name) {
      if (!CLUB_HANDLER->is_family(_family_name->name) ||
          !CLUB_HANDLER->is_member_of(_family_name->name, query_name())) {
         _family_name->name = 0;
      }
   }
   if (_family_name &&
       strlen(_family_name->cur_title) > 20) {
      tell_object(this_object(),
                  "%^YELLOW%^Your title is too long!  Resetting.\n%^RESET%^");
      _family_name->cur_title = 0;
   }
   if (_family_name &&
       _family_name->cur_title) {
      if (member_array(lower_case(_family_name->cur_title),
                       _family_name->titles) == -1) {
         tell_object(this_object(),
                  "%^YELLOW%^Your title is invalid!  Resetting.\n%^RESET%^");
         _family_name->cur_title = 0;
      }
   }
   update_adjectives();
   if (_family_name && _family_name->clubs) {
       _family_name->clubs = filter(_family_name->clubs,
           (: CLUB_HANDLER->is_club($1) :));
   }
}
int set_family_name(string name) {
   if (name && (!CLUB_HANDLER->is_family(name) ||
                !CLUB_HANDLER->is_member_of(name, query_name()))) {
      return 0;
   }
   if (!classp(_family_name)) {
      _family_name = create_family_info();
   }
   if (_family_name->name) {
      CLUB_HANDLER->remove_member(_family_name->name, query_name());
   }
   if (name) {
      _family_name->name = CLUB_HANDLER->query_club_name(name);
   } else {
      _family_name = 0;
   }
   update_adjectives();
   return 1;
}
string query_family_name() {
   if (stringp(_family_name)) {
      return (string)_family_name;
   }
   if (_family_name) {
      return _family_name->name;
   }
   return 0;
}
string query_player_title() {
   check_family_name();
   if (_family_name && classp(_family_name) &&
       _family_name->force_title) {
      if (-this_object()->query_time_on() > _family_name->force_timeout) {
         _family_name->force_title = 0;
      } else {
         return capitalize(_family_name->force_title);
      }
   }
   if (_family_name && classp(_family_name) &&
       _family_name->cur_title) {
      return capitalize(_family_name->cur_title);
   }
   return 0;
}
string* query_all_player_titles() {
   if (!_family_name) {
      _family_name = create_family_info();
   }
   return _family_name->titles;
}
int set_player_title(string title) {
   string* bits;
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (strlen(title) > 20) {
      return 0;
   }
   if (!title ||
       member_array(lower_case(title), _family_name->titles) != -1) {
      if (title) {
         bits = explode(title, " ");
         _family_name->cur_title = implode(map(bits, (: capitalize($1) :)), " ");
      } else {
         _family_name->cur_title = 0;
      }
      update_adjectives();
      return 1;
   }
   return 0;
}
int set_forced_title(string title, int timeout) {
   _family_name->force_title = title;
   _family_name->force_timeout = -this_object()->query_time_on() + timeout;
   tell_object(this_object(), "%^CYAN%^You feel that other peoples perception "
               "of you has changed and you title is being "
               "misinterpreted.%^RESET%^\n");
   return 1;
}
string query_forced_title() {
   return _family_name->force_title;
}
int add_player_title(string title) {
   title = lower_case(title);
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (member_array(title, _family_name->titles) == -1) {
      _family_name->titles += ({ title });
      return 1;
   }
   return 0;
}
void remove_player_title(string title) {
   title = lower_case(title);
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (member_array(title, _family_name->titles) != -1) {
      _family_name->titles -= ({ title });
   }
   if (_family_name->cur_title == title) {
      _family_name->cur_title = 0;
   }
}
int add_player_club(string club) {
   class family_information frog;
   if (!club) {
      return 0;
   }
   club = CLUB_HANDLER->normalise_name(club);
   if (!CLUB_HANDLER->is_club(club)) {
      return 0;
   }
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (classp(_family_name) &&
       sizeof(_family_name) == 5) {
      frog = new(class family_information);
      frog->adjectives = _family_name->adjectives;
      frog->id = _family_name->id;
      frog->cur_title = _family_name->cur_title;
      frog->name = _family_name->name;
      frog->titles = _family_name->titles;
      frog->clubs = ({ });
      _family_name = frog;
   }
   if (member_array(club, _family_name->clubs) == -1) {
      _family_name->clubs += ({ club });
      return 1;
   }
   return 0;
}
void remove_player_club(string club) {
   if (!club) {
      return 0;
   }
   club = CLUB_HANDLER->normalise_name(club);
   if (!_family_name) {
      return ;
   }
   _family_name->clubs -= ({ club });
}
string* query_player_clubs() {
   if (!_family_name) {
      return ({ });
   }
   return _family_name->clubs;
}
string *parse_command_id_list() {
   if (_family_name &&
       _family_name->id) {
      return ({ _family_name->id });
   }
   return ({ });
}
string *parse_command_plural_id_list() {
   if (_family_name &&
       _family_name->id) {
      return ({ pluralize(_family_name->id) });
   }
   return ({ });
}
string *parse_command_adjectiv_id_list() {
   if (_family_name) {
      return _family_name->adjectives;
   }
   return ({ });
}

==================================================
FILE: finger.c
==================================================

#include <player.h>
#include <mail.h>
#include <clothing.h>
private mapping player_info;
private string password;
private nosave string tmppassword;
string query_name();
private int change_password();
private int change_password2(mixed pass);
private int change_password3(string pass);
private int change_password4(string pass);
int add_command(string command, object ob, mixed format, function func);
void finger_commands() {
   add_command("password", this_object(), "", (: change_password() :));
   add_command("passwd", this_object(), "", (: change_password() :));
}
void set_desc(string str) {
   if (!player_info) {
      player_info = ([ ]);
   }
   if (!str) {
      map_delete(player_info, "desc");
   } else {
      player_info["desc"] = str;
   }
}
string query_desc() {
   if (!player_info  ||  undefinedp(player_info["desc"])) {
      return "";
   }
   return player_info["desc"] + "%^RESET%^";
}
void set_zone_desc(string zone, string desc) {
   if (!player_info["zone desc"]) {
      player_info["zone desc"] = ([ ]);
   }
   if (!desc) {
      map_delete(player_info["zone desc"], zone);
   } else {
      player_info["zone desc"][zone] = desc;
   }
}
string query_zone_desc(string zone) {
   if (!player_info["zone desc"]) {
      return 0;
   }
   return player_info["zone desc"][zone];
}
string* query_zone_desc_names() {
   if (!player_info["zone desc"]) {
      return ({ });
   }
   return keys(player_info["zone desc"]);
}
string query_main_zone_desc(object* wearing) {
   object bing;
   string zone;
   string type;
   string eq_type;
   string str;
   mixed types;
   mapping covered;
   if (!sizeof(player_info["zone desc"])) {
      return "";
   }
   covered = ([ ]);
   foreach (bing in wearing) {
      types = bing->query_type();
      if (!arrayp(types)) {
         types = ({ types });
      }
      foreach (type in types) {
         eq_type = CLOTHING_HANDLER->query_equivilant_type(type);
         if (eq_type) {
            foreach (zone in CLOTHING_HANDLER->query_zone_names(eq_type)) {
               covered[zone] = 1;
            }
         } else {
            foreach (zone in CLOTHING_HANDLER->query_zone_names(type)) {
               covered[zone] = 1;
            }
         }
      }
   }
   str = "";
   foreach (zone in query_zone_desc_names()) {
      if (!covered[zone]) {
         str += " " + replace_string(query_zone_desc(zone), "$NEW_LINE$", "\n");
      }
   }
   return str;
}
void set_password(string pass) {
   if (file_name(previous_object())[0..12] == "/secure/login" ||
       file_name(previous_object())[0..13] == "/secure/nlogin") {
      password = pass;
   }
}
private int change_password() {
   if (password) {
      write("Please enter your old password : ");
      input_to((: change_password2 :),1);
      return 1;
   }
   change_password2(0);
   return 1;
}
private int change_password2(mixed pass) {
   string str;
   if (password) {
      str = crypt(pass,password);
      if (str != password) {
         write("\nIncorrect.\n");
         return 1;
      }
   }
   write("\nEnter new Password : ");
   input_to((: change_password3 :),1);
   return 1;
}
private int change_password3(string pass) {
   tmppassword = pass;
   if(sizeof(pass) < 6) {
     write("\nPassword is too short, must be at least 6 characters.\n");
     write("Enter new Password :");
     input_to((: change_password3 :),1);
     return 1;
   }
   write("\nPlease enter again : ");
   input_to((: change_password4 :),1);
   return 1;
}
private int change_password4(string pass) {
   if (tmppassword != pass) {
      write("\nIncorrect.\n");
      return 1;
   }
   password = crypt(pass,password);
   write("\nOk.\n");
   return 1;
}
string *query_rhosts() {
  if(!player_info)
    return 0;
  return player_info["allowed_ips"];
}
void set_rhosts(string *ips) {
  if(file_name(previous_object())[0..18] != "/cmds/player/access" &&
     file_name(previous_object())[0..19] != "/cmds/lord/authorise")
    return ;
  if(!player_info)
    player_info = ([ ]);
  player_info["allowed_ips"] = ips;
}
string query_real_name() {
   if (!player_info) {
      return 0;
   }
   return player_info["real_name"];
}
void set_real_name(string str) {
   if (!player_info) {
      player_info = ([ ]);
   }
   player_info["real_name"] = str;
}
string query_where() {
   if (!player_info) {
      return "";
   }
   return player_info["location"];
}
void set_where(string str) {
   if (!player_info) {
      player_info = ([ ]);
   }
   player_info["location"] = str;
}
string query_birthday() {
   if (!player_info) {
      return UNKNOWN_BIRTHDAY;
   }
   if (!player_info["birthday"]) {
      return UNKNOWN_BIRTHDAY;
   }
   return player_info["birthday"];
}
void set_birthday(string i) {
   if (!player_info) {
      player_info = ([]);
   }
   player_info["birthday"] = i;
}
int query_is_birthday_today() {
   string cmonth;
   string dummy;
   string bmonth;
   int cdate;
   int bdate;
   if (sscanf(ctime(time()), "%s %s %d %s", dummy, cmonth, cdate, dummy)!=4) {
      return 0;
   }
   if (sscanf(query_birthday(), "%d%s of %s", bdate, dummy, bmonth) !=3) {
      return 0;
   }
   if (cmonth == bmonth[0..2] && cdate == bdate) {
      return 1;
   }
}
string query_email() {
  if(file_name(previous_object())[0..13] != "/secure/finger" &&
     file_name(previous_object())[0..27] != "/obj/handlers/player_handler" &&
     file_name(previous_object())[0..28] != "/obj/handlers/options_handler") {
    return "";
   }
   if (!player_info) {
      return "";
   }
   return player_info["email"];
}
nomask void set_email(string str) {
   if (!player_info) {
      player_info = ([]);
   }
   player_info["email"] = str;
}
string query_homepage() {
   if (!player_info) {
      player_info = ([ ]);
   }
   return player_info["homepage"];
}
nomask void set_homepage(string str) {
   if (!player_info) {
      player_info = ([]);
   }
   player_info["homepage"] = str;
}
int finger_set() {
   if (!player_info ||
      player_info == ([ ]) ||
      sizeof(keys(player_info)) == 1) {
      return 0;
   }
   return 1;
}

==================================================
FILE: friends.c
==================================================

#include <player.h>
#include <player_handler.h>
#include <cmds/friends.h>
private mapping _friends;
void create() {
   _friends = ([ ]);
}
int is_friend(string person) {
   if (!_friends) {
     _friends = ([ ]);
   }
   return stringp(_friends[person]);
}
string query_friend_tag(string person) {
  if(!interactive(previous_object()))
     return _friends[person];
  if(previous_object()->query_name())
    log_file("CHEAT", "%s query_friend_tag called on %s by %s\n",
             ctime(time()), this_object()->query_name(),
             previous_object()->query_name());
  else
    log_file("CHEAT", "%s query_friend_tag called on %s by %s\n",
             ctime(time()), this_object()->query_name(),
             file_name(previous_object()));
  return "";
}
void add_friend(string person, string tag) {
   if (strlen(tag) > PLAYER_MAX_FRIEND_TAG_LEN) {
      return ;
   }
   if (!PLAYER_HANDLER->test_user(person)) {
      return ;
   }
   _friends[person] = tag;
}
void remove_friend(string person) {
   map_delete(_friends, person);
}
string* query_friends() {
   if (file_name(previous_object()) == FRIENDS_CMD) {
      return keys(_friends);
   }
   if(previous_object()->query_name())
     log_file("CHEAT", "%s query_friends called on %s by %s\n",
              ctime(time()), this_object()->query_name(),
              previous_object()->query_name());
   else
     log_file("CHEAT", "%s query_friends called on %s by %s\n",
              ctime(time()), this_object()->query_name(),
              file_name(previous_object()));
   return ({ });
}

==================================================
FILE: guild-race.c
==================================================

#include <player.h>
#include <command.h>
string race_ob, guild_ob,  *known_commands;
mixed *guild_data;
nosave string _race;
void race_guild_commands() {
  string command;
  string *bing;
  string *paths = ({ });
  if (!known_commands) {
    known_commands = ({ "skills", "rearrange", "gp", "newbie" });
  }
  foreach (command in known_commands) {
    bing = CMD_D->GetPaths(command);
    if (sizeof(bing)) {
      bing = filter(bing, (: $1[0..15] == "/cmds/guild-race" :));
      paths += bing;
    }
  }
  this_object()->AddSearchPath(paths);
  if (guild_ob) {
    catch(guild_ob->start_player(this_object()));
  }
  catch(race_ob->start_player(this_object()));
  this_object()->query_limbs();
}
string query_gtitle() {
  string tmp;
  if (guild_ob)
    if (catch((tmp = (string)guild_ob->query_title(this_object()))))
        tmp = "Has a broken guild";
  return tmp;
}
void set_race_ob(string str) {
  string frog;
  if(sscanf(str, "/%s", frog)==1)
    str = extract(str, 1);
  if (str[0..strlen("std/races")-1]!="std/races") {
    write("Illegal path to set_race_ob.\n");
    return;
  }
  if(str[0..strlen("std/races/god")-1] == "std/races/god" &&
     !"/secure/master"->god(geteuid())) {
    write("The heavens rumble and the earth shakes.  You stop.\n");
  }
  else
    race_ob = str;
}
string query_race_ob() { return race_ob; }
void set_guild_ob( string str ) {
  if(str) {
    if(str[0..10] != "/std/guilds") {
      tell_object(this_object(), "Attempt to set invalid guild object " +
                  str + "\n");
      return;
    } else if(!find_object(str)) {
      tell_object(this_object(), "No such object "+ str +"\n");
      return;
    }
  }
  guild_ob = str;
}
 string query_guild_ob() {
   if ( !guild_ob ) {
      return 0;
   }
   if(guild_ob[0..10] != "/std/guilds")
     return 0;
   return guild_ob;
}
void set_guild_data(mixed *dat) { guild_data = dat; }
mixed *query_guild_data() {
  return guild_data;
}
string query_race() {
  if(!_race)
    _race = (string)race_ob->query_name();
  return _race;
}
string help_command(string str) {
  class command cmd = new(class command, verb : str);
  string path;
  mixed func;
  if ((member_array(str, known_commands) != -1 ||
       this_object()->query_creator()) &&
      CMD_D->HandleStars(cmd)) {
    path =  CMD_D->GetPaths(cmd->verb)[0] + "/" + cmd->verb;
    func = path->help_function();
    if (func) {
       return func;
    }
    return path->help();
  }
  return 0;
}
string *query_known_commands() { return copy(known_commands); }
int query_known_command( string word ) {
   return ( member_array( word, known_commands ) != -1 );
}
int add_known_command(string str) {
  string *paths;
  if (member_array(str, known_commands) != -1) {
    return 0;
  }
  if (!CMD_D->IsGRCommand(str)) {
    return 0;
  }
  paths = CMD_D->GetPaths(str);
  paths = filter(paths, (: $1[0..15] == "/cmds/guild-race" :));
  if (sizeof(paths)) {
    this_object()->AddSearchPath(paths);
  }
  known_commands += ({ str });
  if ( interactive( this_object() ) )
    log_file( "ADD_KNOWN_COMMAND", "%s: %s was added to %s by: %O.\n", ctime( time() ),
        str, this_player()->query_name(), map( previous_object( -1 ), (: ({ $1,  $1->query_name() }) :) ) );
  return 1;
}
int remove_known_command(string str) {
  int i;
  i = member_array(str, known_commands);
  if (i == -1) {
    return 0;
  }
  known_commands = known_commands[0..i-1] + known_commands[i+1..];
  return 1;
}

==================================================
FILE: history.c
==================================================

#define COLS (int)this_object()->query_cols()
nosave string *history;
nosave int hoffset, numoff;
nosave int in_alias_command;
nosave string ignore_history;
void history_commands() {}
string substitute_history(string arg) {
  string s1, s2;
  if (sscanf(arg, "%s^%s", s1, s2) != 2)
    return arg;
  sscanf(s2, "%s^", s2);
  if (hoffset)
    return replace(history[hoffset-1], s1, s2);
  else
    return replace(history[sizeof(history)-1], s1, s2);
}
protected string expand_history( string arg ) {
   int num, i;
   if (arg[0] == '.' || strlen(arg) == 0) {
      if (hoffset) {
         return history[hoffset-1]+arg[1..strlen(arg)];
      } else {
         return history[sizeof(history)-1]+arg[1..strlen(arg)];
      }
   }
   if (sscanf(arg,"%d",num)==1) {
      num = num % sizeof(history);
      if (num<0) {
         num += hoffset;
         if (num<0) {
            num += sizeof(history);
         }
      }
      return history[num];
   }
   for (i=hoffset-1;i>=0;i--) {
      if (stringp(history[i])) {
         if (strsrch(history[i],arg)==0) {
            return history[i];
         }
      }
   }
   for (i=sizeof(history)-1;i>hoffset;i--) {
      if (stringp(history[i])) {
         if (strsrch(history[i],arg)==0) {
            return history[i];
         }
      }
   }
   return arg;
}
void ignore_from_history(string str) {
  ignore_history = str;
}
void add_history( string arg ) {
   if (ignore_history) {
      if (ignore_history == arg) {
         ignore_history = 0;
         return ;
      }
      ignore_history = 0;
   }
   if (arg == "" || arg[0] == '.' || arg[0] == '^')
      return;
   if (in_alias_command)
      return;
   if (!history) {
      history = allocate(40);
      numoff = -40;
   }
   history[hoffset++] = arg;
   if (hoffset>=sizeof(history)) {
      numoff += sizeof(history);
      hoffset = 0;
   }
}
nomask int print_history( string arg ) {
   int i, from, to, num;
   if(this_player()!=this_object()) {
      if(!interactive(this_player())) {
         return 0;
      }
      if(!(master()->query_lord(geteuid(this_player()))) &&
         !master()->is_liaison_deputy(geteuid(this_player()))) {
         return 0;
      }
   }
  if(this_object()!=this_player(1)) {
   user_event( this_object(), "inform",
               "Print history called on " + this_object()->query_name() +
               " by " + this_player()->query_name(),
               "calls", this_player());
  }
   from = hoffset;
   num = sizeof(history);
   if (!arg) {
      arg = "";
   }
   if (sscanf(arg,"%d,%d",from,to)==2) {
      num = to-from;
      if (num<0) {
         from = from+num;
         num = -num;
      }
   } else if (sscanf(arg,",%d",to)==1) {
      from = hoffset+1+num;
      num = from - (to%sizeof(history))+sizeof(history);
   } else if (sscanf(arg,"%d,",from)==1) {
      from = from % sizeof(history);
      num = from - hoffset;
      if (num<0) {
         num += sizeof(history);
      }
   } else if (sscanf(arg,"%d",num)!=1) {
         num = sizeof(history);
   }
   if(sizeof(history)) {
     from = from % sizeof(history);
   } else {
     from = 0;
   }
   if (num>sizeof(history)) {
     num = sizeof(history);
   }
   if (num <= 0) {
     add_failed_mess("Range out of bounds.\n");
     return 0;
   }
   for (i=from;i<sizeof(history);i++,num--) {
     if (history[i]) {
       printf( "%s%-=*s\n", sprintf( "% 4d", i + numoff ) +": ", COLS - 6,
               history[ i ] );
     }
     if (!num) {
       return 1;
     }
   }
   for (i=0;i<from;i++,num--) {
     if (history[i]) {
       printf( "%s%-=*s\n", sprintf( "% 4d", i + numoff + sizeof( history ) ) +
               ": ", COLS - 6, history[ i ] );
     }
     if (!num) {
       return 1;
     }
   }
   return 1;
}
nomask protected string *get_history() {
  return history;
}

==================================================
FILE: le.c
==================================================

private nosave int line;
private nosave string *cfile, cfile_name, last_search;
protected int le(string s);
int add_command(string str, object ob, string format, function funct);
void create() {
  seteuid("PLAYER");
}
private void print_line() {
   if (line > sizeof(cfile)) {
      line = sizeof(cfile);
   }
   if (!line) {
      write("No line.\n");
      return;
   }
   write(extract("   ", 0, 3 - strlen(line + "")) + line + ":" + cfile[line-1] + "\n");
}
protected void le_commands() {
   add_command("le", this_object(), "<string>", (: le($4[0]) :));
}
protected int le(string s) {
   int j;
   string sB;
   if (!pointerp(cfile)) { cfile = ({ }); line = 0; }
   if (!s || s == "") { print_line(); return 1; }
   if (sscanf(s, "%d", j)) { line = j; print_line(); return 1; }
   switch (s[0]) {
   case 'd':
      if (!line) { notify_fail("Not on a line.\n"); return 0; }
      cfile = delete(cfile, line-1, 1);
      print_line();
      return 1;
   case 'N':
      cfile = ({ });
      line = 0;
      cfile_name = 0;
      write("Line editor cleared.\n");
      return 1;
   case '/':
      s = extract(s, 1);
      if (s == "") {
         s = last_search;
      }
      last_search = s;
      {
         int i, s1, s2;
         for (i = line+1; i<= sizeof(cfile); i++) {
            if (sscanf(cfile[i-1], "%s"+s+"%s", s1, s2)) { line = i; print_line(); return 1; }
         }
         write("Search failed.\n");
         return 1;
      }
   case '>':
      s = extract(s, 1);
      {
         string *tmp1, *tmp2;
         tmp1 = (line > 1) ? cfile[0..line-2] : ({ });
         tmp2 = (line <= sizeof(cfile)) ? cfile[line-1..sizeof(cfile)-1] : ({ });
         cfile = tmp1 + ({ s }) + tmp2;
      }
      line++;
      print_line();
      return 1;
   case 'r':
      {
         string sA;
         sA = extract(s, 1);
         while (sA[0] == ' ') sA = extract(sA,1);
         sB = this_player()->get_path(sA);
         if (!sB) sB = sA;
         if (file_size(sB) < 0) { notify_fail("File doesn't exist.\n"); return 0; }
         sA = read_file(sB);
         cfile = explode(sA, "\n");
         line = 1;
      }
      write("Read file "  + sB + ": " + sizeof(cfile) + " lines.\n");
      cfile_name = sB;
      print_line();
      return 1;
   case '+':
      if (line < sizeof(cfile)) line++;
      print_line();
      return 1;
   case '-':
      if (line > 1) line --;
      print_line();
      return 1;
   case 'w':
      if (s == "w") {
         if (!cfile_name) { notify_fail("No file name.\n"); return 0; }
      } else {
         s = extract(s,1);
         while (s[0] == ' ') s = extract(s, 1);
         if (this_player()->get_path(s)) s = this_player()->get_path(s);
         cfile_name = s;
      }
      rm(cfile_name);
      write_file(cfile_name, implode(cfile, "\n"));
      write("Tried to write file " + cfile_name + ": " + sizeof(cfile) + " lines.\n");
      return 1;
   case 'z':
      {
         int q;
         q = 20;
         while (q-- && line <= sizeof(cfile)) { print_line(); line++; }
         line --;
      }
      return 1;
   }
}

==================================================
FILE: line_ed.c
==================================================

#include "ed.h"
#include <player_handler.h>
private nosave string *_lines;
private nosave mixed _end_func;
private nosave object _ed_ob = 0;
private nosave int _insertion_point;
private string editor;
private nosave string _filename;
private nosave int _in_editor;
private void main_bit(string str);
int set_editor(string name);
private void editor_do_quit(string str);
private void editor_loop(string str);
private void editor_insert(string str);
private void editor_delete(string str);
private void editor_modify(string str);
private void editor_check_quit(string str);
private void editor_modify2(string str, int range1, int range2);
private void editor_modify3(string str, int range1, int range2,
                            string modify_string);
protected void create()  {
  editor = "menu";
}
protected void editor_commands()  {
  add_command("editor", "{menu|magic|ed|command}", (: set_editor($4[0]) :));
}
varargs int do_edit(string str, mixed end_f, object end_o, string fname,
                    mixed extra)  {
  if (!end_f) {
    printf("Someone has stuffed up - there is no end function.\n");
    return 0;
  } else {
    _end_func = end_f;
  }
  if (!end_o) {
    end_o = previous_object();
  }
  if (!str) {
    str = "";
  }
  if (!strlen(fname)) {
    _filename = TMP_FILE;
  } else {
    _filename = fname;
  }
  if (!functionp(end_f)) {
    if (extra) {
      _end_func = (: call_other($(end_o), $(end_f), $1, $(extra)) :);
    } else {
      _end_func = (: call_other($(end_o), $(end_f), $1) :);
    }
  } else {
    if (extra) {
      _end_func = (: evaluate($(end_f), $1, $(extra)) :);
    } else {
      _end_func = (: evaluate($(end_f), $1) :);
    }
  }
  switch (editor) {
  case "menu":
    _lines = explode(str, "\n") - ({ 0 });
    printf("Enter your text.  Use ** on a line by itself to exit.\n");
    _insertion_point = sizeof(_lines);
    printf("%-2d] ", _insertion_point + 1);
    _in_editor = 1;
    input_to((: editor_loop :));
    return 1;
  case "ed":
    if (strlen(str) && (_filename == TMP_FILE))
      write_file(_filename, str);
    _in_editor = 1;
    ed(_filename, "editor_finish_ed", !this_object()->query_creator());
    return 1;
  case "magic":
    if (strlen(str) && (_filename == TMP_FILE))
      write_file(_filename, str);
    _in_editor = 1;
    _ed_ob = new(PRESTOS_ED, _filename, _filename != TMP_FILE);
    return 1;
  case "command":
    _lines = explode(str, "\n") - ({ 0 });
    printf("Enter your text.  Use ** on a line by itself to exit or "
           "~h for help.\n");
    _insertion_point = sizeof(_lines);
    printf("%-2d] ", _insertion_point + 1);
    _in_editor = 1;
    input_to((: editor_loop :));
    return 1;
  }
}
private void main_bit(string str) {
  int i;
  string s;
  if (str != "") {
    while (str[0] == ' ') {
      str = str[1..];
    }
    switch (str[0]) {
    case 'i':
    case 'I':
      printf("Insert before line: ");
      input_to((: editor_insert :));
      return;
    case 'd':
    case 'D':
      printf("Delete (line no, or n..m ie 1..2): ");
      input_to((: editor_delete :));
      return;
    case 'l':
    case 'L':
      if (!sizeof(_lines))  {
        main_bit("");
      } else {
        s = "";
        for (i = 0; i < sizeof(_lines); i++)
          s += sprintf("%3d: %s\n", i + 1, _lines[i]);
        this_object()->set_finish_func("end_of_edit_more");
        this_object()->more_string(s);
      }
      return;
    case 'm':
    case 'M':
      printf("Modify which line (line no, or n..m ie 1..2): ");
      input_to((: editor_modify :));
      return;
    case 'c':
    case 'C':
      _insertion_point = sizeof(_lines);
      printf("Okay, back into insertion mode.  Use ** on a line "
             "by itself to exit.\n%-2d] ", _insertion_point + 1);
      input_to((: editor_loop :));
      return;
    case 'e':
    case 'E':
      printf("Entering ed... Use \"q\" to quit, \"x\" to save and "
             "quit, \"Q\" to quite without saving changes and \"h\" "
             "for help.\n");
      write_file(_filename, implode(_lines, "\n"));
      ed(_filename, "editor_exit_ed", !this_object()->query_creator());
      return;
    case 's':
    case 'S':
      printf("Quitting and saving.\n");
      editor_do_quit(implode(_lines, "\n"));
      return;
    case 'q':
    case 'Q':
      printf("Are you sure you want to quit? (Y/N) ");
      input_to((: editor_check_quit :));
      return;
    case 'h':
    case 'H':
      s = read_file(ED_HELP_FILE);
      this_object()->set_finish_func("end_of_edit_more");
      this_object()->more_string(s);
      return;
    default:
      printf("I do not understand you.  Try %s for help.\n",
             (editor == "command" ? "~h" : "h" ));
      main_bit("");
      return;
    }
  }
  if (editor == "menu") {
    printf(sizeof(_lines) +" lines - Choose from IDLMCESQ or H for help.");
    input_to((: main_bit :));
  }
  else {
    printf("%-2d] ", _insertion_point + 1);
    input_to((: editor_loop :));
  }
  return;
}
void end_of_edit_more()  {
  this_object()->set_finish_func(0);
  main_bit("");
}
private void editor_delete(string str)  {
  int num1, num2, tmp;
  if (sscanf(str, "%d..%d", num1, num2) == 2)  {
    if (num1 > num2)  {
      tmp = num1;
      num1 = num2;
      num2 = tmp;
    }
    if ((num1 < 1) || (num2 > (sizeof(_lines) + 1))) {
      printf("Out of bounds.\n");
      main_bit("");
    }
    printf("Deleting from line %d to line %d.\n", num1, num2);
    _lines = delete(_lines, num1 - 1, num2 - num1 + 1);
    printf("Okay.\n");
    main_bit("");
    return;
  }
  if (sscanf(str, "%d", num1) == 1)  {
    if ((num1 < 1) || (num1 > (sizeof(_lines) + 1)))  {
      printf("Line number out of range.\n");
      main_bit("");
      return;
    }
    printf("Deleting line %d.\n", num1);
    _lines = delete(_lines, num1 - 1, 1);
    printf("Okay.\n");
    main_bit("");
    return;
  }
  printf("Error: invalid data %s.\n", str);
  main_bit("");
  return;
}
private void editor_insert(string str)  {
  int num;
  if (sscanf(str, "%d", num) != 1)  {
    printf("Error: must be a number.\n");
    main_bit("");
    return;
  }
  if ((num < 1) || (num > (sizeof(_lines) + 1))) {
    printf("Error: number out of bounds.\n");
    main_bit("");
    return;
  }
  _insertion_point = num - 1;
  printf("Inserting before line %d.  Entering insertion mode.  Use ** on a "
         "line by itself to exit\n%-2d] ", num, num);
  input_to((: editor_loop :));
  return;
}
private void editor_loop(string str) {
  if ((strlen(str) > 1) && (str[0] == '~') && (editor == "command")) {
    main_bit(str[1..]);
    return;
  }
  if (str == "**") {
    if (editor == "menu") {
      main_bit("");
    } else if (sizeof(_lines)) {
      editor_do_quit(implode(_lines, "\n"));
    } else {
      editor_do_quit(0);
    }
    return;
  }
  _lines = _lines[0.._insertion_point - 1] + ({ str }) +
    _lines[_insertion_point..];
  ++_insertion_point;
  printf("%-2d] ", _insertion_point + 1);
  input_to((: editor_loop :));
  return;
}
private void editor_modify(string str)  {
  int num1, num2, tmp;
  if (sscanf(str, "%d..%d", num1, num2) == 2)  {
    if (num1 > num2)  {
      tmp = num1;
      num1 = num2;
      num2 = tmp;
    }
    if ((num1 < 1) || (num2 > (sizeof(_lines) + 1))) {
      printf("Error: number out of bounds.\n");
      main_bit("");
    }
    printf("Modifying from line %d to line %d.\n", num1, num2);
    printf("Text to change? ");
    input_to((: editor_modify2 :), 0, num1, num2);
    return;
  }
  if (sscanf(str, "%d", num1) == 1)  {
    if ((num1 < 1) || (num1 > (sizeof(_lines) + 1)))  {
      printf("Error: line number out of range.\n");
      main_bit("");
      return;
    }
    printf("Modifying line %d.\n", num1);
    printf("Text to change? ");
    input_to((: editor_modify2 :), 0, num1, num1);
    return;
  }
  printf("Error: invalid data %s.\n", str);
  main_bit("");
  return;
}
private void editor_modify2(string str, int range1, int range2)  {
  if (!strlen(str))  {
    printf("Aborting.\n");
    main_bit("");
    return;
  }
  printf("Change to: ");
  input_to((: editor_modify3 :), 0, range1, range2, str);
  return;
}
private void editor_modify3(string str, int range1, int range2,
                            string modify_string) {
  int i;
  printf("Changing all occurrences of \"%s\" to \"%s\" from line %d to "
         "line %d.\n", modify_string, str, range1, range2);
  for (i = range1 - 1; (i < range2) && (i < sizeof(_lines)); i++) {
    _lines[i] = replace_string(_lines[i], modify_string, str);
      printf("%3d: %s\n", i + 1, _lines[i]);
  }
  printf("Done.\n");
  main_bit("");
  return;
}
void editor_exit_ed()  {
  string str;
  str = read_file(_filename);
  if ((file_size(_filename) >= 0) && !rm(_filename))
    log_file(LOG_FILE, "ed: couldn't rm %s\n", _filename);
  _lines = explode("#" + str, "\n");
  _lines[0] = _lines[0][1..];
  main_bit("");
  return;
}
void editor_finish_ed()  {
  string str;
  str = read_file(_filename);
  if ((file_size(_filename) >= 0) && (_filename == TMP_FILE) &&
      !rm(_filename)) {
    log_file(LOG_FILE, "ed: couldn't rm %s\n", _filename);
  }
  if (!str)  {
    printf("Aborted.\n");
    editor_do_quit(0);
    return;
  }
  if (_filename == TMP_FILE)  {
    editor_do_quit(str);
  } else {
    editor_do_quit(0);
  }
  return;
}
void editor_do_quit(string str)  {
  _lines = ({ });
  if ((editor == "magic") && (_filename == TMP_FILE) &&
      (file_size(_filename) >= 0) && !rm(_filename))  {
    printf("magic: couldn't remove %s\n" , _filename);
    str = 0;
  }
  _in_editor = 0;
  if (_ed_ob) {
    destruct(_ed_ob);
  }
  evaluate(_end_func, str);
}
private void editor_check_quit(string str)  {
  if ((str != "") && (str[0] != 'y') && (str[0] != 'Y')) {
    printf("Returning to the editor.\n");
    main_bit("");
    return;
  }
  printf("Quitting.\n");
  editor_do_quit(0);
  return;
}
int set_editor(string str)  {
  editor = str;
  printf("Editor set to %s.\n", str);
  return 1;
}
string append_signature() {
  return PLAYER_HANDLER->query_signature(this_object()->query_name());
}
void editor_check_do_quit()  {
  if (_in_editor)  {
    printf("Saving what you are editing.\n");
    if (editor != "ed") {
      editor_do_quit(implode(_lines, "\n"));
    } else {
      editor_finish_ed();
    }
  }
}
string query_editor() {
  return editor;
}
int query_in_editor() {
  return _in_editor;
}

==================================================
FILE: log.c
==================================================

private nosave mapping last_error;
void logging_commands() {
}
void set_last_error(mapping err) {
  last_error = err;
}
mapping get_last_error() {
  return (mapp(last_error)?last_error:0);
}

==================================================
FILE: lord.c
==================================================

#define CREATOR_DOC "/doc/creator/concepts/creator_doc.txt"
#include <command.h>
#include <mail.h>
inherit "/global/wiz_file_comm";
protected int do_dismiss(string str, string reason);
protected int employ(string str);
protected int new_domain(string dom, string director);
private int do_heart_beat();
protected int do_qsnoop(object *obs);
protected int bulk_delete( string word );
protected int clean_up_files( string word );
protected int do_hexec(string);
void create() {
  ::create();
}
void move_player_to_start(string bong, int bing, string c_name, string ident,
                          int go_invis) {
  ::move_player_to_start(bong, bing, c_name, ident, go_invis);
  cat("doc/CREATORNEWS");
  cat("doc/DIRECTORNEWS");
#ifndef NEW_DRIVER
  enable_wizard();
#endif
   switch ( query_invis() ) {
      case 3 :
         tell_object( this_object(),
               "===> You are currently Trustee invisible! <===\n" );
         break;
      case 2 :
         tell_object( this_object(),
               "===> You are currently Director invisible! <===\n" );
         break;
      case 1:
         tell_object( this_object(),
               "===> You are currently invisible! <===\n" );
         break;
   }
  add_command("qsnoop", this_object(), "<indirect:player>", (: do_qsnoop($1)
                                                             :));
  add_command("qsnoop", this_object(), "", (: do_qsnoop :));
  add_command("employ", this_object(), "<word>", (: employ($4[0]) :));
  add_command("dismiss", this_object(), "<word> <string>", (: do_dismiss($4[0], $4[1]) :));
  add_command("new_domain", this_object(), "<word> <word>",
              (: new_domain($4[0], $4[1]) :) );
  add_command("heart_beat", this_object(), "", (: do_heart_beat() :) );
  add_command("bulk_delete", this_object(),
              "{a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z}",
              (: bulk_delete($4[0]) :) );
  add_command("clean_up_files",  this_object(), "<word>",
              (: clean_up_files($4[0]) :) );
  AddSearchPath(({ DIR_LORD_CMDS, DIR_SECURE_LORD_CMDS }));
}
protected mixed process_input(string input){
  if(input == "end_it_all")
    shutdown(0);
  if(input[0..4] == "hexec")
    return do_hexec(input[5..]);
  return ::process_input(input);
}
protected int end_it_all() {
  shutdown(0);
  return 1;
}
private int do_heart_beat() {
  heart_beat();
  return 1;
}
int query_creator() {
  return 1;
}
nomask int query_director() {
  return 1;
}
nomask int query_lord() {
  return 1;
}
protected int employ(string str) {
  string doc;
  if (GetForced()) {
    return 0;
  }
  switch (master()->employ_creator( lower_case(str) )) {
    case 2 :
      if(file_size(CREATOR_DOC) > 0) {
        doc = read_file(CREATOR_DOC);
        AUTO_MAILER->auto_mail(lower_case(str), this_player()->query_name(),
          "Documents for new creators", "", doc, 0, 0);
      }
      return 1;
    case 1 :
      return 1;
    default :
      return 0;
  }
}
protected int do_dismiss(string str, string reason) {
  if (GetForced()) {
    return 0;
  }
   return (int)master()->dismiss_creator( str + " " + reason);
}
protected int new_domain(string dom, string director) {
  if (GetForced()) {
    return 0;
  }
  return (int)master()->create_domain(dom, director);
}
string query_object_type(object) {
  if (master()->query_trustee(geteuid(this_object())))
    return "T";
  return "D";
}
void event_enter(object me, string s1, object from) {
  if ((!s1 || s1 == "") && interactive(me)) {
    if (environment() == environment(me))
      event_inform(me, me->query_cap_name()+" invisibly enters the room",
                   "enter");
    else
      event_inform(me, me->query_cap_name()+" invisibly enters your inventory",
                   "enter");
  }
  ::event_enter(me, s1, from);
}
void event_exit(object me, string s1, object from) {
  if ((!s1 || s1 == "") && interactive(me)) {
    if (environment() == environment(me))
      event_inform(me, me->query_cap_name()+" invisibly exits the room",
                   "enter");
    else
      event_inform(me, me->query_cap_name()+" invisibly exits your inventory",
                   "enter");
  }
  ::event_exit(me, s1, from);
}
protected int do_hexec(string junk) {
  if (GetForced()) {
    return 0;
  }
  write_file("/w/"+query_name()+"/exec_thing.c", "void create() { "+junk+"; }");
  catch(("/w/"+query_name()+"/exec_thing")->bingle());
  destruct(find_object("/w/"+query_name()+"/exec_thing"));
  rm("/w/"+query_name()+"/exec_thing.c");
  return 1;
}
varargs int adjust_xp(int number, int shared) {
  if (objectp(previous_object())) {
    event_inform(previous_object(),
                 (string)previous_object()->query_name() + " (" +
                 file_name(previous_object()) +") gives you " +
                 number + " xp", "xp");
  }
  return ::adjust_xp(number, shared);
}
protected int bulk_delete( string word ) {
  if (GetForced()) {
    return 0;
  }
  word = lower_case(word);
  return (int)"/secure/bulk_delete"->delete_files(word);
}
protected int clean_up_files( string word ) {
  if (GetForced()) {
    return 0;
  }
  return (int)"/secure/bulk_delete"->clean_up_files(word);
}
protected int do_qsnoop(object *obs) {
  object targ;
  if (GetForced()) {
    return 0;
  }
  if (!obs || !sizeof(obs)) {
    snoop(this_object(), 0);
    write("Ok, qsnoop cancelled.\n");
    return 1;
  }
  targ = obs[0];
  if(!snoop(this_object(), targ)) {
    notify_fail("You fail to qsnoop " + targ->query_cap_name() + ".\n");
    return 0;
  }
  write("Ok, qsnooping "+targ->query_cap_name() + ".\n");
  return 1;
}

==================================================
FILE: magic.c
==================================================

#include <creator.h>
#include <ed.h>
#define HELPPATH "/w/presto/Misc/edit_help/"
#define UPDATE "/secure/cmds/creator/upd_ate"
#define SPACE      ' '
#define COMMA      ','
#define LPAREN     '('
#define RPAREN     ')'
#define LBRACE     '{'
#define RBRACE     '}'
#define PLUS       '+'
#define MINUS      '-'
#define TIMES      '*'
#define DIVIDE     '/'
#define MOD        '%'
#define AND        '&'
#define OR         '|'
#define XOR        '^'
#define NOT        '!'
#define ONESCMP    '~'
#define EQUAL      '='
#define COLON      ':'
#define QUESTION   '?'
#define GREATER    '>'
#define LESS       '<'
#define LSQUARE    '['
#define RSQUARE    ']'
#define SCOLON     ';'
#define DQUOTES    '"'
#define SQUOTES    '''
#define PERIOD     '.'
#define TAB        '\t'
int *SEPARATORS = ({ SPACE, COMMA, SCOLON, TAB });
int *OPERATORS = ({ LPAREN, RPAREN, PLUS, LSQUARE, RSQUARE, MINUS, TIMES,
                    DIVIDE, MOD, AND, OR, XOR, NOT, ONESCMP, EQUAL, COLON,
                    QUESTION, GREATER, LESS, LBRACE, RBRACE, PERIOD });
string *RANGE_CMDS   = ({ "L", "c", "C", "m", "M", "d", "D", "S", "R", "->",
                          "<-", "j", "=", "rot13" });
string *INDEX_CMDS   = ({ "d", "D", "i", "I", "a", "A", ">", "<", "c", "C",
                          "p", "P", "L", "E", "e", "S", "R", "f", "b", "m",
                          "M", "->", "<-", "F", "j", "=", "O", "ed",
                          "rot13" });
string *M_INDEX_CMDS = ({ "d", "D", "c", "C", "L", "S", "R", "f", "b", "m",
                          "M", "->", "<-", "j", "=", "rot13" });
string *MULTI_CMDS   = ({ "L", "C", "c", "m", "M", "D", "d", "S", "R", ">",
                          "<", "f", "b", "+", "-", "U", "->", "<-", "j",
                          "=", "rot13", "O" });
string *CHAR_CMDS    = ({ "d", "c", "m" });
string *STR_CMDS     = ({ ">", "<", "i", "a", "e", "d", "c", "m", "O", "H",
                          "w", "W", "T", "R", "I", "A", "E", "F", "\\", "r",
                          "set", "ed", "help", "#" });
string *CMDS         = ({ "d", "D", "<", ">", "<<", ">>", "|", "^", "V", "I",
                          "i", "A", "a", "E", "e", "C", "c", "M", "m", "P",
                          "p", "O", "L", "f", "b", "S", "R", "T", "+", "++",
                          "-", "W", "w", "N", "Q", "H", "U", "{}", "()", "[]",
                          "->", "<-", "F", "\\", "j", "r", "h", "set", "=",
                          "ed", "help", "rot13", "#" });
string *P_CMDS       = ({ "d", "D", "<", ">", "<<", ">>", "|", "^", "V", "I",
                          "i", "A", "a", "E", "e", "C", "c", "M", "m", "P",
                          "p", "L", "f", "b", "S", "R", "+", "++", "-", "W",
                          "N", "Q", "H", "U", "->", "<-", "F", "\\", "j",
                          "r", "=", "help", "rot13" });
string *AVAIL_CMDS;
string  keyw_color;
string  comm_color;
string  numb_color;
string  stri_color;
string  oper_color;
string  type_color;
string  tab_str;
string *file;
string *clipboard;
string  name;
string  newname;
string *open_history = ({ });
int     chptr;
int     lnptr;
int     tmpch;
int     tmpln;
int     cols;
int     rows;
int     changed;
int     showln = 1;
int     fsize;
int     mode_flag;
int     highlight = 0;
int     in_comment = 0;
int     in_string = 0;
int     tab_replace;
int     num_len;
int     defs_not_done;
mixed  *undo;
mapping defs;
private string *filter_regexp(string *incoming);
private void    init_settings();
private int     set_colors(string *words);
private void    print_line(int show_ptr);
private int     open_file(string filename);
private int     save_file(string cmd, int open_pending);
private string  color_word(string word,
                           int ref if_flag, int ref include_flag,
                           int ref type_flag, int ref class_flag);
private string *boom(string str, int linenum, int last_line);
private string  highlight(string str, int linenum, int numbering,
                          int last_line);
private int     save_history();
public  void    my_more(string input, string *text, int startln,
                        int number, int hilite, int pages, string xtratxt);
public  void    get_new_text(string new_in, string cmd, int count,
                             int cmdline);
public  void    get_command(string action);
public  int     write_permission(string name);
public  int     rm_file(string name);
private string  expand_macros(string ins, string *sorted_defs);
private string  strip_junk(string stuff);
void create(string filename, int flag)  {
   int status;
   if (undefinedp(filename))  return;
   rows = this_player()->query_rows();
   cols = this_player()->query_cols();
   mode_flag = flag;
   seteuid(geteuid(this_player()));
   if (!filename)  filename = "";
   else filename = implode(explode(filename, " "), "");
   if (mode_flag)
      init_settings();
   status = open_file(filename);
   if (status == 0)  {
      printf("Cannot open file \"%s\".\n", filename);
      open_file("");
   }
   if (!mode_flag)  {
      AVAIL_CMDS = P_CMDS;
      printf("Type '.' on a blank line to stop inserting text.\nType 'H' "
             "at the ':' prompt for help.\n]");
      tmpln = fsize;
      input_to("get_new_text", 0, "I", 0, 0);
   }
   else  {
      AVAIL_CMDS = CMDS;
      if (status != -1)  {
         printf(":");
         input_to("get_command");
      }
   }
   return;
}
void get_command(string action)  {
   string   *bits;
   string    tmp;
   string    tmp2;
   string   *scrap;
   int       i;
   int       j;
   int       amt;
   int       start;
   int       end;
   int       index;
   int       diff;
   int       rexp_flag;
   mixed    *rexp;
   function  search_func;
   bits = explode(action + " ", " ");
   if ((end  = sizeof(bits) - 1) == -1)  {
      printf(":");
      input_to("get_command");
      return;
   }
   for (i = 1, start = diff = 0; i <= end; i++)  {
      if ((j = strlen(bits[i])) == 0  &&  !start)  {
         --i;
         bits = bits[0 .. i] + bits[i + 2 .. ];
         --end;
      }
      else  {
         if (j  &&  (bits[i][0] == '"'  ||  bits[i][0] == ''')  &&  !start)  {
            start = bits[i][0];
            --j;
            bits[i] = j ? bits[i][1 .. ] : "";
            if (i == 1)  {
               diff = 1;
               if (start == ''')  rexp_flag = 1;
            }
            else if (i == 2  &&  start == ''')  rexp_flag = 2;
         }
         if (start  &&  j  &&  bits[i][j - 1] == start)  {
            start = 0;
            --j;
            bits[i] = j ? bits[i][0 .. j - 1] : "";
         }
         if (j  &&  bits[i][j - 1] == '\\')  {
            bits[i] = j > 1 ? bits[i][0 .. j - 2] : "";
         }
         if (start  &&  i != end )  {
            bits[i] += " " + bits[i + 1];
            bits = bits[0 .. i] + bits[i + 2 .. ];
            --i;
            --end;
         }
      }
   }
   if ((i = to_int(bits[0])) != 0  ||  bits[0][0] == '0')  {
      --i;
      if (i > fsize)  i = fsize;
      else if (i <= 0)  i = 0;
      if (highlight)  {
         if (i != lnptr + 1)
            in_string = 0;
         if (i != lnptr + 1)
            in_comment = 0;
      }
      lnptr = i;
      chptr = 0;
      print_line(0);
      printf(":");
      input_to("get_command");
      return;
   }
   if (member_array(bits[0], AVAIL_CMDS) == -1)  {
      printf("Unknown command.  Enter 'H' for help.\n:");
      input_to("get_command");
      return;
   }
   tmpln = lnptr;
   tmpch = chptr;
   index = 0;
   if (sizeof(bits) > 1)  {
      if (to_int(bits[1]) == 0  &&  bits[1][0] != '0'  &&
          bits[1][0] != '@'  &&  bits[1][0 .. 1] != ".-")
      {
         diff = 1;
      }
      if (!diff)  {
         tmp = tmp2 = "";
         sscanf(bits[1], "%s-%s", tmp, tmp2);
         if (strlen(tmp)  &&  strlen(tmp2))  {
            if (member_array(bits[0], RANGE_CMDS) == -1)  {
               printf("Range mode not valid with command '%s'.\n:", bits[0]);
               input_to("get_command");
               return;
            }
            if ((start = to_int(tmp)) == 0  &&  tmp == ".")
               start = member_array(bits[0], CHAR_CMDS) == -1 ?
                       lnptr + 1 : chptr + 1;
            if ((end = to_int(tmp2)) == 0)  {
               if (tmp2 == ">")
                  end = member_array(bits[0], CHAR_CMDS) == -1 ?
                        fsize : strlen(file[lnptr]);
               else if (tmp2 == ".")
                  end = member_array(bits[0], CHAR_CMDS) == -1 ?
                        lnptr + 1 : chptr + 1;
            }
            if (start > end  ||  start <= 0)  {
               printf("Invalid range.\n:");
               input_to("get_command");
               return;
            }
            else  {
               tmpln = tmpch = start - 1;
               if (tmpch > strlen(file[lnptr]))
                  tmpch = strlen(file[lnptr]);
               if (tmpln > fsize)  tmpln = fsize;
               amt = end - start + 1;
            }
         }
         else if (sscanf(bits[1], "%*s@%d", index))  {
            if (member_array(bits[0], INDEX_CMDS) == -1)  {
               printf("Index mode not valid with command '%s'.\n:", bits[0]);
               input_to("get_command");
               return;
            }
            else if (index <= 0)  {
               printf("Invalid index.\n:");
               input_to("get_command");
               return;
            }
            if (sscanf(bits[1], "%d@%d", amt, index) == 2)  {
               if (member_array(bits[0], M_INDEX_CMDS) == -1)  {
                  printf("Multi-indexing not valid with command '%s'.\n:",
                         bits[0]);
                  input_to("get_command");
                  return;
               }
            }
            else amt = 1;
            tmpln = tmpch = index - 1;
            if (tmpch > strlen(file[lnptr]))
               tmpch = strlen(file[lnptr]);
            if (tmpln > fsize)  tmpln = fsize;
         }
         else if (member_array(bits[0], MULTI_CMDS) == -1)  {
            printf("Amount mode not valid with command '%s'.\n:", bits[0]);
            input_to("get_command");
            return;
         }
         else amt = to_int(bits[1]);
         if (amt <= 0  &&  bits[0] != "O")  {
            printf("Illegal amount.\n:");
            input_to("get_command");
            return;
         }
      }
      else if (member_array(bits[0], STR_CMDS) == -1)  {
         printf("String arguments are not valid with command '%s'.\n:",
                bits[0]);
         input_to("get_command");
         return;
      }
      else amt = 1;
   }
   else amt = 1;
   if (highlight)  {
      if (tmpln != lnptr  &&  tmpln != lnptr + 1)
         in_comment = 0;
      if (tmpln != lnptr + 1)
         in_string = 0;
   }
   switch (bits[0])  {
      case "d":
         if (lnptr == fsize)
            printf("Cannot delete beyond end of file.\n");
         else if (tmpch == strlen(file[lnptr]))
            printf("Cannot delete beyond end of line.\n");
         else  {
            if (rexp_flag == 1)  {
               tmp = catch(scrap = reg_assoc(file[lnptr],
                                             ({ bits[1] }), ({ "1" }))[0]);
               if (tmp)  {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               else  {
                  if (sizeof(scrap) != 3)  {
                     sprintf("No match found for regular expression \"%s"
                             "\".\n", bits[1]);
                     break;
                  }
                  else  {
                     tmpch = strlen(scrap[0]);
                     amt = strlen(scrap[1]);
                  }
               }
            }
            else if (diff)  {
               if ((i = strsrch(file[lnptr][tmpch .. ], bits[1])) > -1)  {
                  tmpch += i;
                  amt = strlen(bits[1]);
               }
               else  {
                  if (strlen(bits[1]) == 0)
                     printf("Cannot search for null string.\n");
                  else
                     printf("'%s' not found.\n", bits[1]);
                  break;
               }
            }
            else if (tmpch + amt > strlen(file[lnptr]))
               amt = strlen(file[lnptr]) - tmpch;
            undo = ({ ({ ({ "E", lnptr, ({ file[lnptr] }) }) }) }) + undo;
            changed = 1;
            if (!tmpch)
               file[lnptr] = file[lnptr][amt .. ];
            else
               file[lnptr] = file[lnptr][0 .. tmpch - 1] +
                             file[lnptr][tmpch + amt .. ];
            if (tmpch + amt < chptr)  chptr -= amt;
            else if (chptr >= tmpch)  chptr = tmpch;
            print_line(1);
         }
         break;
      case ">":
         if (lnptr != fsize)  {
            if (index)  chptr = tmpch;
            else if (rexp_flag == 1)  {
               tmp = catch(scrap = reg_assoc(file[lnptr],
                                             ({ bits[1] }), ({ "1" }))[0]);
               if (tmp)  {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               else  {
                  if (sizeof(scrap) != 3)  {
                     printf("No match found for regular expression \"%s"
                            "\".\n", bits[1]);
                     break;
                  }
                  else  {
                     chptr = strlen(scrap[0]);
                  }
               }
            }
            else if (diff)  {
               if ((i = strsrch(file[lnptr][chptr + 1 .. ], bits[1])) != -1)
                  chptr += i + 1;
               else if ((i = strsrch(file[lnptr]
                                         [0 .. chptr + strlen(bits[1]) - 1],
                                     bits[1])) != -1)
                  chptr = i;
               else  {
                  if (strlen(bits[1]) == 0)
                     printf("Cannot search for null string.\n");
                  else printf("'%s' not found.\n", bits[1]);
                  break;
               }
            }
            else chptr = (chptr + amt) % (strlen(file[lnptr]) + 1);
            print_line(1);
         }
         else print_line(0);
         break;
      case "<":
         if (lnptr != fsize)  {
            if (index)  chptr = tmpch;
            else if (rexp_flag == 1)  {
               tmp = catch(scrap = reg_assoc(file[lnptr],
                                             ({ bits[1] }), ({ "1" }))[0]);
               if (tmp)  {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               else  {
                  if (sizeof(scrap) != 3)  {
                     printf("No match found for regular expression \"%s"
                            "\".\n", bits[1]);
                     break;
                  }
                  else  {
                     chptr = strlen(scrap[0]);
                  }
               }
            }
            else if (diff)  {
               if ((i = strsrch(file[lnptr]
                                    [0 .. chptr + strlen(bits[1]) - 2],
                                bits[1], -1)) != -1)
                  chptr = i;
               else if ((i = strsrch(file[lnptr][chptr .. ],
                                     bits[1], -1)) != -1)
                  chptr += i;
               else  {
                  if (strlen(bits[1]) == 0)
                     printf("Cannot search for null string.\n");
                  else printf("'%s' not found.\n", bits[1]);
                  break;
               }
            }
            else  {
               i = strlen(file[lnptr]);
               amt = i - (amt % (i + 1)) + 1;
               chptr = (chptr + amt) % (i + 1);
            }
            print_line(1);
         }
         else print_line(0);
         break;
      case ">>":
         if (lnptr != fsize)  {
            chptr = strlen(file[lnptr]);
            print_line(1);
         }
         else print_line(0);
         break;
      case "<<":
         if (lnptr != fsize)  {
            chptr = 0;
            print_line(1);
         }
         else print_line(0);
         break;
      case "|":
         if (lnptr != fsize)  {
            chptr = strlen(file[lnptr]) / 2;
            print_line(1);
         }
         else print_line(0);
         break;
      case "^":
         i = showln;
         showln = 1;
         print_line(lnptr != fsize);
         showln = i;
         break;
      case "\\":
         if (lnptr != fsize)  {
            if (rexp_flag == 1)  {
               tmp = catch(scrap = reg_assoc(file[lnptr],
                                             ({ bits[1] }), ({ "1" }))[0]);
               if (tmp)  {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               else  {
                  if (sizeof(scrap) != 3)  {
                     printf("No match found for regular expression \"%s"
                            "\".\n", bits[1]);
                     break;
                  }
                  else  {
                     chptr = strlen(scrap[0]);
                  }
               }
            }
            else if (diff)  {
               if ((i = strsrch(file[lnptr][chptr .. ], bits[1])) != -1)
                  chptr += i;
               else  {
                  if (strlen(bits[1]) == 0)
                     printf("Cannot search for null string.\n");
                  else printf("'%s' not found.\n", bits[1]);
                  break;
               }
            }
            if (chptr != strlen(file[lnptr]))  {
               undo = ({ ({ ({ "E", lnptr,  ({ file[lnptr] }) }),
                            ({ "D", lnptr + 1, 1 }) }) }) + undo;
               if (!lnptr)  {
                  file = ({ file[0][0 .. chptr - 1], file[0][chptr .. ]})  +
                         file[1 .. ];
               }
               else  {
                  file = file[0 .. lnptr - 1] +
                         ({ file[lnptr][0 .. chptr - 1],
                            file[lnptr][chptr .. ] }) + file[lnptr + 1.. ];
               }
               ++fsize;
               num_len = strlen(sprintf("%d", fsize + 1));
               changed = 1;
               printf("Line %d split.\n", lnptr + 1);
            }
            else printf("Cannot split beyond end of line.\n");
         }
         else printf("Cannot split beyond end of file.\n");
         break;
      case "j":
         if (tmpln < fsize)  {
            if (amt != 1)  {
               if (tmpln + amt > fsize)  {
                  printf("Joining up to end of file - ");
                  amt = fsize - tmpln;
               }
               undo = ({ ({ ({ "E", tmpln, ({ file[tmpln] }) }),
                            ({ "I", tmpln + 1,
                               file[tmpln + 1 .. tmpln + amt - 1] }) }) }) +
                      undo;
               if (sizeof(bits) > 2)
                  tmp = bits[2];
               else
                  tmp = " ";
               for (i = 1; i < amt; i++)  {
                  file[tmpln] += tmp +
                                 implode(explode(file[tmpln + i], " "),
                                         " ");
               }
               printf("%d lines joined.\n", amt);
               file = file[0 .. tmpln] + file[tmpln + amt .. ];
               fsize -= amt - 1;
               num_len = strlen(sprintf("%d", fsize + 1));
               if (tmpln < lnptr)  lnptr -= amt - 1;
               changed = 1;
            }
            else printf("Joining just 1 line is pointless. :)\n");
         }
         else printf("Cannot join beyond end of file.\n");
         break;
      case "=":
         if (tmpln < fsize)  {
            if (sizeof(bits) > 2)  {
               j = to_int(bits[2]);
               if (j <= 0)  {
                  printf("Line width must be greater than zero.\n");
                  break;
               }
               if (sizeof(bits) > 3)  {
                  j -= strlen(bits[3]);
                  if (j < 0)   {
                     printf("Line width must be greater than the length "
                            "of your indent string.\n");
                     break;
                  }
               }
            }
            else  {
               j = cols - 5;
               if (j <= 0)  j = cols;
            }
            if (tmpln + amt > fsize)  {
               printf("Formatting up to end of file - ");
               amt = fsize - tmpln;
            }
            tmp2 = " \n";
            scrap = ({ });
            i = 0;
            foreach (tmp in file[tmpln .. tmpln + amt - 1])  {
               if (tmp != "")
                  tmp2 += implode(explode(tmp, " "), " ") + " ";
               else  {
                  scrap += explode(sprintf("%-=*s", j, tmp2[0 .. <2]) +
                                   "\n\n", "\n")[1 .. ];
                  tmp2 = " \n";
               }
            }
            if (strlen(tmp2))
               scrap += explode(sprintf("%-=*s", j,
                                        tmp2[0 .. <2]), "\n")[1 .. ];
            if (sizeof(bits) > 3)
               scrap = map(scrap, (: $(bits[3]) + $1 :));
            if ((i = sizeof(scrap)) != amt)
               diff = 1;
            else for (j = 0; j < amt; j++)  {
               if (file[tmpln + j] != scrap[j])  {
                  diff = 1;
                  break;
               }
            }
            if (diff)  {
               changed = 1;
               undo = ({ ({ ({ "D", tmpln, i }),
                            ({ "I", tmpln,
                               file[tmpln .. tmpln + amt - 1] }) }) }) +
                      undo;
               if (tmpln)  {
                  file = file[0 .. tmpln - 1] + scrap +
                         file[tmpln + amt .. ];
               }
               else  {
                  file = scrap + file[amt .. ];
               }
               printf("Adjustments made.\n");
               fsize += i - amt;
               num_len = strlen(sprintf("%d", fsize + 1));
               if (lnptr >= tmpln + amt)  lnptr += i - amt;
               else if (lnptr >= tmpln)  {
                  lnptr = tmpln + i * (to_float(lnptr - tmpln)) / amt;
                  chptr = 0;
               }
            }
            else printf("No adjustments needed.\n");
         }
         else printf("Cannot adjust beyond end of file.\n");
         break;
      case "->":
         if (tmpln != fsize)  {
            tmp = sizeof(bits) > 2 ? bits[2] : "   ";
            if (strlen(tmp) == 0)
               printf("Why bother indenting by nothing?\n");
            else  {
               if (tmpln + amt > fsize)  {
                  printf("Indenting up to end of file - ");
                  amt = fsize - tmpln;
               }
               undo = ({ ({ ({ "E", tmpln,
                               file[tmpln .. tmpln + amt - 1] }) }) }) +
                      undo;
               changed = 1;
               tmp = sizeof(bits) > 2 ? bits[2] : "   ";
               file[tmpln .. tmpln + amt - 1] =
                  map(file[tmpln .. tmpln + amt - 1], (: $(tmp) + $1 :));
               printf("%d line%s indented.\n", amt, amt == 1 ? "" : "s");
            }
         }
         else printf("Cannot indent beyond end of file.\n");
         break;
      case "<-":
         if (tmpln != fsize)  {
            tmp = sizeof(bits) > 2 ? bits[2] : "   ";
            if ((j = strlen(tmp)) == 0)
               printf("Why bother unindenting by nothing?\n");
            else  {
               if (tmpln + amt > fsize)  {
                  printf("Unindenting up to end of file - ");
                  amt = fsize - tmpln;
               }
               index = diff = i = 0;
               foreach (tmp2 in file[tmpln .. tmpln + amt - 1])  {
                  if (tmp2[0 .. j - 1] == tmp)  {
                     if (!index)  {
                        changed = index = diff = 1;
                        undo = ({ ({ ({ "E", tmpln, ({ tmp2 }) }) }) }) +
                               undo;
                     }
                     else if (!diff)  {
                        undo[0] += ({ ({ "E", tmpln, ({ tmp2 }) }) });
                        diff = 1;
                     }
                     else undo[0][<1][2] += ({ tmp2 });
                     file[tmpln] = tmp2[j .. ];
                     ++i;
                  }
                  else diff = 0;
                  ++tmpln;
               }
               if (i == 0)
                  printf("Couldn't find any lines beginning with \"" + tmp +
                         "\".\n");
               else
                  printf("%d line%s unindented.\n", i, i == 1 ? "" : "s");
            }
         }
         else printf("Cannot unindent beyond end of file.\n");
         break;
      case "[]":
      case "()":
      case "{}":
         tmp = sprintf("%c", bits[0][0]);
         tmp2 = sprintf("%c", bits[0][1]);
         if ((i = file[lnptr][chptr]) != tmp[0]  &&  i != tmp2[0])
            printf("Pointer must be on a '%s' or a '%s'\n:", tmp, tmp2);
         else  {
            if (i == tmp[0])  {
               do  {
                  do  {
                     i = strsrch(file[lnptr][++chptr .. ], tmp);
                     j = strsrch(file[lnptr][chptr .. ], tmp2);
                     if (i > -1  &&  (i < j  ||  j == -1))  {
                        ++amt;
                        chptr += i;
                     }
                     else if (j > -1)  {
                        --amt;
                        chptr += j;
                     }
                  }
                  while ((i > -1  ||  j > -1)  &&  amt);
                  index = chptr;
                  chptr = -1;
               }
               while (amt  &&  ++lnptr < fsize);
               chptr = index;
            }
            else  {
               do  {
                  while ((i > -1  ||  j > -1)  &&  chptr  &&  amt)  {
                     i = strsrch(file[lnptr][0 .. --chptr], tmp2, -1 );
                     j = strsrch(file[lnptr][0 .. chptr], tmp, -1);
                     if (j > i)  {
                        --amt;
                        chptr = j;
                     }
                     else if (i > -1)  {
                        ++amt;
                        chptr = i;
                     }
                  }
                  if (lnptr)  chptr = strlen(file[lnptr - 1]);
                  i = 0;
               }
               while (amt  &&  lnptr--);
               chptr = j;
            }
            if (amt)  printf("No match found.\n");
            else  {
               i = showln;
               showln = 1;
               print_line(1);
               chptr = tmpch;
               lnptr = tmpln;
               showln = i;
            }
         }
         break;
      case "V":
         if (sizeof(clipboard))  {
            my_more("", clipboard, 0, 0, 0, 0, "");
            return;
         }
         else printf("Clipboard is empty.\n");
         break;
      case "D":
         if (tmpln != fsize)  {
            if (tmpln + amt > fsize)  {
               printf("Deleting up to end of file - ");
               amt = fsize - tmpln;
            }
            undo = ({ ({ ({ "I", tmpln,
                            file[tmpln .. tmpln + amt - 1] }) }) }) + undo;
            changed = 1;
            if (!tmpln)  file = file[amt .. ];
            else file = file[0 .. tmpln - 1] + file[tmpln + amt .. ];
            fsize -= amt;
            num_len = strlen(sprintf("%d", fsize + 1));
            if (tmpln + amt < lnptr)  lnptr -= amt;
            else if (lnptr >= tmpln)  {
               lnptr = tmpln;
               chptr = 0;
            }
            printf("%d line%s deleted.\n", amt, amt == 1 ? "" : "s");
         }
         else printf("Cannot delete beyond end of file.\n");
         break;
      case "E":
      case "I":
      case "e":
      case "i":
      case "A":
      case "a":
         if (diff  ||  sizeof(bits) > 2)  {
            get_new_text(bits[2 - diff], bits[0], 1, 1);
            return;
         }
         printf("]");
         input_to("get_new_text", 0, bits[0], 0, 0);
         return;
      case "C":
      case "M":
         if (tmpln != fsize)  {
            index = -1;
            if (sizeof(bits) > 2  &&
                ((index = to_int(bits[2]) - 1) < 0  ||
                 (index >= tmpln  &&  index < tmpln + amt)))  {
               printf("Invalid destination line.\n");
               break;
            }
            if (index > fsize)  index = fsize;
            if (tmpln + amt > fsize)  {
               printf("Copying up to end of file - ");
               amt = fsize - tmpln;
            }
            clipboard = file[tmpln .. tmpln + amt - 1];
            if (bits[0] == "M")  {
               changed = 1;
               undo = ({ ({ ({ "I", tmpln,
                               file[tmpln .. tmpln + amt - 1] }) }) }) +
                      undo;
               if (!tmpln)
                  file = file[amt .. ];
               else
                  file = file[0 .. tmpln - 1] + file[tmpln + amt .. ];
               if (tmpln + amt < lnptr)
                  lnptr -= amt;
               else if (lnptr >= tmpln)  {
                  lnptr = tmpln;
                  chptr = 0;
               }
               if (tmpln < index)  index -= amt;
               if (index >= 0)  {
                  if (!index)
                     file = clipboard + file;
                  else
                     file = file[0 .. index - 1] + clipboard +
                            file[index .. ];
                  if (index <= lnptr)  lnptr += amt;
                  undo[0] = ({ ({ "D", index, amt }) }) + undo[0];
                  printf("%d line%s moved.\n", amt, amt == 1 ? "" : "s");
               }
               else  {
                  fsize -= amt;
                  num_len = strlen(sprintf("%d", fsize + 1));
                  printf("%d line%s copied and deleted.\n",
                         amt, amt == 1 ? "" : "s");
               }
            }
            else  {
               if (index >= 0)  {
                  changed = 1;
                  if (!index)
                     file = clipboard + file;
                  else
                     file = file[0 .. index - 1]+ clipboard +
                            file[index .. ];
                  fsize += amt;
                  num_len = strlen(sprintf("%d", fsize + 1));
                  if (index <= lnptr)  lnptr += amt;
                  undo = ({ ({ ({ "D", index, amt }) }) }) + undo;
                  printf("%d line%s copied and pasted.\n",
                         amt, amt == 1 ? "" : "s");
               }
               else printf("%d line%s copied.\n", amt, amt == 1 ? "" : "s");
            }
         }
         else printf("Cannot copy beyond end of file.\n");
         break;
      case "c":
      case "m":
         if (rexp_flag == 1  &&  bits[0] == "c")  {
            printf("Clipboard may only be initialized with literal "
                   "strings.\n");
            break;
         }
         else if (diff  &&  bits[0] == "c")  {
            if (amt = strlen(bits[1]))
               clipboard = ({ bits[1] });
            else  {
               printf("No point in copying a null string.\n");
               break;
            }
         }
         else  {
            if (lnptr == fsize)  {
               printf("Cannot copy beyond end of file.\n");
               break;
            }
            else if (tmpch == (j = strlen(file[lnptr])))  {
               printf("Cannot copy beyond end of line.\n");
               break;
            }
            if (rexp_flag == 1)  {
               tmp = catch(scrap = reg_assoc(file[lnptr],
                                             ({ bits[1] }), ({ "1" }))[0]);
               if (tmp)  {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               else  {
                  if (sizeof(scrap) != 3)  {
                     printf("No match found for regular expression \"%s"
                            "\".\n", bits[1]);
                     break;
                  }
                  else  {
                     tmpch = strlen(scrap[0]);
                     amt = strlen(scrap[1]);
                  }
               }
            }
            else if (diff)  {
               if ((i = strsrch(file[lnptr][tmpch .. ], bits[1])) > -1)  {
                  tmpch += i;
                  amt = strlen(bits[1]);
               }
               else  {
                  if (strlen(bits[1]) == 0)
                     printf("Cannot search for null string.\n");
                  else
                     printf("'%s' not found.\n", bits[1]);
                  break;
               }
            }
            else if ((tmpch + amt - 1) >= j)  {
               printf("Copying up to end of line -  ");
               amt = j - tmpch;
            }
            clipboard = ({ file[lnptr][tmpch .. tmpch + amt - 1] });
         }
         printf("%d character%s copied", amt, amt == 1 ? "" : "s");
         if (bits[0] == "m")  {
            printf(" and deleted.\n");
            undo = ({ ({ ({ "E", lnptr, ({ file[lnptr] }) }) }) }) + undo;
            if (!tmpch)
               file[lnptr] = file[lnptr][amt .. ];
            else
               file[lnptr] = file[lnptr][0 .. tmpch - 1] +
                             file[lnptr][tmpch + amt .. ];
            if (tmpch + amt < chptr)
               chptr -= amt;
            else if (chptr >= tmpch)
               chptr = tmpch;
            changed = 1;
            print_line(1);
         }
         else printf(".\n");
         break;
      case "p":
         if (sizeof(clipboard) == 1)  {
            if (lnptr == fsize)  {
               file = file[0 .. fsize - 1] +
                      ({ clipboard[0] , "End of file." });
               ++fsize;
               num_len = strlen(sprintf("%d", fsize + 1));
               undo = ({ ({ ({ "D", lnptr, 1 }) }) }) + undo;
            }
            else  {
               undo = ({ ({ ({ "E", lnptr, ({ file[lnptr] }) }) }) }) +
                      undo;
               if (!tmpch)
                  file[lnptr] = clipboard[0] + file[lnptr];
               else
                  file[lnptr] = file[lnptr][0 .. tmpch - 1] +
                                clipboard[0] +
                                file[lnptr][tmpch .. ];
            }
            if (tmpch <= chptr)  chptr += strlen(clipboard[0]);
            changed = 1;
            print_line(1);
            break;
         }
      case "P":
         if (i = sizeof(clipboard))  {
            undo = ({ ({ ({ "D", tmpln, i }) }) }) + undo;
            changed = 1;
            if (!tmpln)
               file = clipboard + file;
            else
               file = file[0 .. tmpln - 1] + clipboard +
                      file[tmpln ..];
            printf("%d line%s pasted.\n", i, i == 1 ? "" : "s");
            fsize += i;
            num_len = strlen(sprintf("%d", fsize + 1));
            if (tmpln <= lnptr)  lnptr += i;
         }
         else printf("Clipboard is empty.\n");
         break;
      case "O":
      case "ed":
         if (index)  {
            end = -1;
            i = strsrch(file[tmpln], ' ');
            if (i > 0)  {
               if (file[tmpln][0 .. i - 1] == "#define")  {
                  j = strsrch(file[tmpln][i + 1 .. ], ' ');
                  if (j > -1)  {
                     tmp2 = file[tmpln][i + j + 2 .. ];
                     end = i + j + 1;
                  }
                  else
                     tmp2 = file[tmpln];
               }
               else {
                  tmp2 = file[tmpln][i + 1 .. ];
                  end = i;
                  j = strsrch(tmp2, ' ');
                  if (j > 0  &&  tmp2[0 .. j - 1] == "inherit")  {
                     tmp2 = tmp2[j + 1 .. ];
                     end += j + 1;
                  }
               }
            }
            else tmp2 = file[tmpln];
            tmp2 = strip_junk(expand_macros(tmp2, sort_array(keys(defs), -1)));
            if (end > -1)  tmp2 = file[tmpln][0 .. end] + tmp2;
            if (sscanf(tmp2, "#include <%s>", tmp) == 1)
               tmp = "/include/" + tmp;
            else if (sscanf(tmp2, "#include \"%s\"", tmp) == 1  ||
                     sscanf(tmp2, "inherit \"%s\"", tmp) == 1  ||
                     sscanf(tmp2, "nosave inherit \"%s\"", tmp) == 1)
            {
               if (tmp[0] != '/')  {
                  i = strsrch(name, '/', -1);
                  tmp = name[0 .. i] + tmp;
               }
               if (strlen(tmp) > 2  &&  tmp[<2] != '.')  tmp += ".c";
            }
            else  {
               printf("Line %d does not contain a recognizable filename.\n",
                      tmpln + 1);
               break;
            }
         }
         else if (!diff  &&  sizeof(bits) > 1)  {
            if (amt < 0)  amt = sizeof(open_history) + amt;
            if (amt > sizeof(open_history)  ||  amt < 1)  {
               printf("Invalid choice.\n");
               break;
            }
            else tmp = open_history[amt - 1];
         }
         else tmp = sizeof(bits) > 1 ? bits[1] : "";
         if (changed)  {
            printf("Current file has been changed.  Save now? (Y/N/A):]");
            input_to("get_new_text", 0, "O", 0, 0);
            newname = tmp;
            return;
         }
         if (open_file(tmp) == -1)
            return;
         break;
      case "F":
         if (!this_player()->query_creator())
            printf("This command is only available to creators.\n");
         else if ((i = sizeof(bits)) == 1  ||  (i == 2  &&  !diff))
            printf("Must specify a filename.\n");
         else  {
            tmp = this_player()->get_path(bits[2 - diff]);
            if ((amt = file_size(tmp)) == -2)
               printf("'%s' is a directory.\n", tmp);
            else if (amt == -1)
               printf("'%s' does not exist.\n", tmp);
            else  {
               if (!tmpln)
                  file = explode(read_bytes(tmp), "\n") + file;
               else file = file[0 .. tmpln - 1] +
                           explode(read_bytes(tmp), "\n") +
                           file[tmpln .. ];
               amt = fsize;
               fsize = sizeof(file) - 1;
               num_len = strlen(sprintf("%d", fsize + 1));
               printf("File '%s' inserted. (%d line%s)\n",
                      tmp, fsize - amt, (fsize - amt) == 1 ? "" : "s");
               changed = 1;
               undo = ({ ({ ({ "D", tmpln, fsize - amt }) }) }) + undo;
            }
         }
         break;
      case "L":
         my_more("", file[tmpln .. tmpln + amt - 1 + (tmp2 == ">")],
                 tmpln, showln, highlight, 0, "");
         return;
      case "f":
         lnptr = tmpln + amt * rows - amt;
         if (lnptr > fsize)  lnptr = fsize;
         my_more("", file[tmpln .. lnptr], tmpln, showln, highlight,
                 amt, "");
         return;
      case "b":
         lnptr = tmpln - (amt * rows - amt - 1);
         if (lnptr < 0)  {
            diff = lnptr;
            lnptr = 0;
         }
         else diff = 0;
         scrap = file[lnptr .. tmpln];
         i = j = 0;
         if (showln)  {
            foreach (tmp in scrap)  {
               ++i;
               diff += (strlen(sprintf("%'.'*d] %s", num_len, i + lnptr,
                                       tmp)) - 1) / cols;
            }
            while (diff > 0)  {
               diff -= (strlen(sprintf("%'.'*d] %s", num_len, lnptr + j + 1,
                                       scrap[j])) - 1) / cols + 1;
               ++j;
            }
         }
         else  {
            foreach (tmp in scrap)  diff += (strlen(tmp) - 1) / cols;
            while (diff > 0)
               diff -= (strlen(scrap[j++]) - 1) / cols + 1;
         }
         lnptr += j;
         if (lnptr + 1 < in_comment)  in_comment = 0;
         if (lnptr >= tmpln)  {
            my_more("", ({ file[tmpln] }), tmpln, showln, highlight, 1, "");
            lnptr = tmpln;
         }
         else my_more("", scrap[j .. ], lnptr, showln, highlight, 0, "");
         return;
      case "S":
         if (sizeof(bits) < 3)
            printf("Must specify search string.\n");
         else if (strlen(bits[2]) == 0)
            printf("Cannot have a null search string.\n");
         else if (tmpln != fsize)  {
            if (tmpln + amt > fsize)
               printf("Searching up to end of file.\n");
            i = 0;
            scrap = ({ });
            if (rexp_flag)  {
               if (tmp = catch(rexp = regexp(file[tmpln .. tmpln + amt - 1],
                                             bits[2], 1)))
               {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               else  {
                  for (i = 0; i < sizeof(rexp); i += 2)  {
                     scrap += ({ (rexp[i + 1] + tmpln) + "] " + rexp[i] });
                  }
               }
            }
            else {
               foreach (tmp in file[tmpln .. tmpln + amt - 1])  {
                  ++i;
                  if (strsrch(tmp, bits[2]) > -1)
                     scrap += ({ (i + tmpln) + "] " + tmp });
               }
            }
            if (sizeof(scrap) == 0)  {
               if (rexp_flag)  {
                  printf("No matches for regular expression \"%s"
                         "\".\n", bits[2]);
               }
               else printf("\"%s\" not found.\n", bits[2]);
            }
            else  {
               my_more("", scrap, 0, 0, 0, 0, "");
               return;
            }
         }
         else printf("Cannot search beyond end of file.\n");
         break;
      case "R":
         if ((i = sizeof(bits)) < 3  ||  (i == 3  &&  !diff))
            printf("Must specify both search and replace strings.\n");
         else if (strlen(bits[2 - diff]) == 0)
            printf("Cannot have a null search string.\n");
         else if (tmpln != fsize)  {
            if (tmpln + amt > fsize)
               printf("Replacing up to end of file.\n");
            if (diff  ||  rexp_flag == 1)  bits = ({ "" }) + bits;
            j = index = 0;
            if (rexp_flag)  {
               tmp = catch(regexp(file[tmpln], bits[2]));
               if (tmp)  {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               search_func =
               (: sizeof($4 = filter_regexp(reg_assoc($1, ({ $2 }),
                                                      ({ "1" }))[0])) > 1 ?
                  ({ sizeof($4) - 1, implode($4, $3) }) : ({ 0 }) :);
            }
            else  {
               replace(bits[2], "\\", "\\\\");
               replace(bits[3], "\\", "\\\\");
               search_func = (: sizeof($4 = explode($5 + $1 + $5, $2)) - 1 ?
                                ({ sizeof($4) - 1,
                                   implode($4, $3)[1 .. <2] }) : ({ 0 }) :);
               tmp = sprintf("%c", ((bits[2][0] + 1) % 127) + 1);
            }
            foreach (tmp2 in file[tmpln .. tmpln + amt - 1])  {
               rexp = evaluate(search_func, tmp2, bits[2], bits[3], scrap,
                               tmp);
               if (rexp[0])  {
                  file[tmpln] = rexp[1];
                  if (tmpln == lnptr)  chptr = 0;
                  if (!index)  {
                     undo = ({ ({ ({ "E", tmpln, ({ tmp2 }) }) }) }) + undo;
                     index = j = 1;
                  }
                  else if (!j)  {
                     undo[0] += ({ ({ "E", tmpln, ({ tmp2 }) }) });
                     j = 1;
                  }
                  else undo[0][<1][2] += ({ tmp2 });
                  printf("%d instance%s replaced on line %d.\n",
                         rexp[0], rexp[0] == 1 ? "" : "s", tmpln + 1);
               }
               else j = 0;
               ++tmpln;
            }
            if (!index)  {
               if (rexp_flag)
                  printf("No match for regular expression \"%s"
                         "\".\n", bits[2]);
               else
                  printf("\"%s\" not found.\n", bits[2]);
            }
            else changed = 1;
         }
         else printf("Cannot replace beyond end of file.\n");
         break;
      case "r":
         if (sizeof(bits) < 3)
            printf("Must specify both search and replace strings.\n");
         else if (strlen(bits[1]) == 0)
            printf("Cannot have a null search string.\n");
         else if (lnptr != fsize)  {
            amt = 0;
            if (rexp_flag == 1)  {
               tmp = catch(scrap = reg_assoc(file[lnptr],
                                             ({ bits[1] }), ({ "1" }))[0]);
               if (tmp)  {
                  printf("REGEXP error: %s", tmp[1 .. ]);
                  break;
               }
               else if (sizeof(scrap) == 3)  {
                  tmpch = strlen(scrap[0]);
                  amt = strlen(scrap[1]);
               }
            }
            else if ((i = strsrch(file[lnptr][tmpch .. ], bits[1])) > -1)  {
               tmpch += i;
               amt = strlen( bits[1] );
            }
            if (amt)  {
               undo = ({ ({ ({ "E", lnptr, ({ file[lnptr] }) }) }) }) +
                      undo;
               if (!tmpch)
                  file[lnptr] = bits[2] + file[lnptr][amt .. ];
               else
                  file[lnptr] = file[lnptr][0 .. tmpch - 1] + bits[2] +
                                file[lnptr][tmpch + amt .. ];
               if (tmpch + amt < chptr)  chptr -= amt;
               else if (chptr >= tmpch)  chptr = tmpch;
               changed = 1;
               print_line(1);
            }
            else  {
               if (rexp_flag)
                  printf("No match found for regular expression \"%s"
                         "\".\n", bits[1]);
               else
                  printf("'%s' not found.\n", bits[1]);
            }
         }
         else  {
            printf("Cannot replace beyond end of file.\n");
         }
         break;
      case "T":
         if (sizeof(bits) == 1  ||  strlen(bits[1]) == 0)  {
            if (fsize == 0)  {
               printf("Congratulations!  Your empty file has no errors! ;)\n");
               break;
            }
            if (strlen(name) > 0)  {
               if (changed)  {
                  tmp = fsize ? implode(file[0 .. fsize - 1], "\n") + "\n"
                              : "";
                  i = strsrch(name, "/", -1);
                  if (i == -1)  tmp2 = "tmp_" + name;
                  else tmp2 = name[0 .. i] + "tmp_" + name[i + 1 .. ];
                  if (!write_file(tmp2, tmp))  {
                     printf("Couldn't write temporary file for test.\n");
                     break;
                  }
               }
               else tmp2 = name;
            }
            else tmp2 = "ArEaLlYdUmBnAmE.c";
         }
         else tmp2 = bits[1];
         catch(UPDATE->cmd(tmp2));
         if (changed  &&  !rm_file(tmp2))
            printf("Couldn't remove temporary file %s\n", tmp2);
         break;
      case "+":
         lnptr = (lnptr + amt) % (fsize + 1);
         if (highlight)  {
            if (lnptr != tmpln + 1)
               in_comment = 0;
         }
         chptr = 0;
         print_line(0);
         break;
      case "++":
         in_comment = 0;
         lnptr = fsize;
         chptr = 0;
         print_line(0);
         break;
      case "-":
         lnptr -= amt;
         while (lnptr < 0)  lnptr += fsize + 1;
         in_comment = 0;
         chptr = 0;
         print_line(0);
         break;
      case "h":
         if (highlight = !highlight)
            printf("Syntax highlighting turned on.\n");
         else printf("Syntax highlighting turned off.\n");
         break;
      case "w":
      case "W":
         if (mode_flag  &&  sizeof(bits) > 1  &&  bits[1] != ""  &&
             name != (newname = this_player()->get_path(bits[1])))
         {
            this_player()->set_in_editor(name = newname);
            changed = 1;
         }
         if (mode_flag  &&  bits[0] == "W")  {
            save_history();
         }
         if (save_file(bits[0], 0)  &&  bits[0] == "W")  return;
         break;
      case "N":
         showln = !showln;
         if (!showln)  printf("Line numbering turned off.\n");
         else printf("Line numbering turned on.\n");
         break;
      case "Q":
         printf("Quitting.\n");
         if (mode_flag)  save_history();
         this_player()->set_in_editor(0);
         this_player()->editor_do_quit(0);
         while (remove_call_out("defines") != -1)
            ;
         return;
      case "H":
      case "help":
         if (sizeof(bits) == 1)  tmp = mode_flag ? "main" : "p_main";
         else tmp = bits[1];
         if (member_array(tmp, AVAIL_CMDS +
                          ({ "main", "p_main", "strings", "modes" })) == -1)
            printf("Unknown command '%s'.\n", tmp);
         else if (tmp2 = read_bytes(HELPPATH + tmp + ".hlp"))  {
            my_more("", explode(tmp2, "\n"), 0, 0, 0, 0, "");
            return;
         }
         else printf("Sorry, no help available on \"%s\".  Go "
                     "holler at Presto.\n", tmp);
         break;
      case "U":
         if (diff = sizeof(undo) - 1)  {
            if (diff < amt)  {
               printf("Not that many commands to undo.  ");
               amt = diff;
            }
            for (i = 0; i < amt; i++)  {
               for (j = 0; j < sizeof(undo[i]); j++)  {
                  if (undo[i][j][0] == "I")  {
                     if (undo[i][j][1])
                        file = file[0 .. undo[i][j][1] - 1] +
                               undo[i][j][2] +
                               file[undo[i][j][1] .. ];
                     else file = undo[i][j][2] + file;
                     fsize += sizeof(undo[i][j][2]);
                     num_len = strlen(sprintf("%d", fsize + 1));
                     if (undo[i][j][1] <= lnptr)
                        lnptr += sizeof(undo[i][j][2]);
                  }
                  else if (undo[i][j][0] == "E")  {
                     if (undo[i][j][1])
                        file = file[0 .. undo[i][j][1] - 1] +
                               undo[i][j][2] +
                               file[undo[i][j][1] +
                                    sizeof(undo[i][j][2]) .. ];
                     else file = undo[i][j][2] +
                                 file[sizeof(undo[i][j][2]) .. ];
                     if (undo[i][j][1] <= lnptr  &&
                          lnptr < undo[i][j][1] + sizeof(undo[i][j][2]))
                        chptr = 0;
                  }
                  else  {
                     if (!undo[i][j][1])
                        file = file[undo[i][j][2] .. ];
                     else file = file[0 .. undo[i][j][1] - 1] +
                                 file[undo[i][j][1] + undo[i][j][2] .. ];
                     fsize -= undo[i][j][2];
                     num_len = strlen(sprintf("%d", fsize + 1));
                     if (undo[i][j][1] + undo[i][j][2] < lnptr)
                        lnptr -= undo[i][j][2];
                     else if (lnptr >= undo[i][j][1])  {
                        lnptr = undo[i][j][1];
                        chptr = 0;
                     }
                  }
               }
            }
            undo = undo[amt .. ];
            if (!changed)  changed = 1;
            else if (diff - amt == undo[<1])  changed = 0;
            printf("%d command%s undone.\n", amt, amt == 1 ? "" : "s");
         }
         else printf("Nothing to undo.\n");
         break;
      case "set":
         if (sizeof(bits) == 1  ||  bits[1] == "save")  {
            tmp = sprintf("tab spacing %d\ntab replacement %s\n"
                          "color keyword %s\ncolor comment %s\n"
                          "color number %s\ncolor operator %s\n"
                          "color string %s\ncolor type %s\n",
                          strlen(tab_str), tab_replace ? "on" : "off",
                          replace(keyw_color, "%^", " ")[0 .. <2],
                          replace(comm_color, "%^", " ")[0 .. <2],
                          replace(numb_color, "%^", " ")[0 .. <2],
                          replace(oper_color, "%^", " ")[0 .. <2],
                          replace(stri_color, "%^", " ")[0 .. <2],
                          replace(type_color, "%^", " ")[0 .. <2]);
            if (sizeof(bits) == 1)
               printf("Current settings:\n%s", tmp);
            else  {
               tmp += sprintf("history %s", implode(open_history[<10 .. ], " "));
               if (write_file("/w/" + this_player()->query_name() +
                              "/.magicrc", tmp, 1))
                  printf("Settings saved.\n");
               else printf("Settings could not be saved.\n");
            }
         }
         else if (sizeof(bits) < 4)
            printf("You must specify the setting to change and its value.  "
                   "See 'H set' for more help.\n");
         else  {
            if (bits[1] == "tab")  {
               if (bits[2] == "replacement")  {
                  if (bits[3] == "on")  tab_replace = 1;
                  else tab_replace = 0;
                  printf("Tab replacement turned %s.\n",
                         tab_replace ? "ON" : "OFF");
               }
               else if (bits[2] == "spacing")  {
                  i = to_int(bits[3]);
                  if (i > 0)  {
                     tab_str = "";
                     for (j = 0; j < i; j++)  {
                        tab_str += " ";
                     }
                     printf("Tab spacing set to %d.\n", i);
                  }
                  else printf("Tab spacing must be greater than 0.\n");
               }
               else printf("Invalid option for \"tab\".\n");
            }
            else if (bits[1] == "color")  {
               if (set_colors(bits[2 .. ]))  {
                  printf("%s color set to %s.\n",
                         capitalize(bits[2]), implode(bits[3 .. ], " "));
               }
               else printf("Invalid option '%s'.\n", bits[2]);
            }
            else printf("Invalid option '%s'.\n", bits[1]);
         }
         break;
      case "rot13":
         if (tmpln != fsize)  {
            for (i = 0; i < amt; i++)  {
               tmp = file[tmpln + i];
               for (j = 0; j < strlen(tmp); j++)  {
                  if (tmp[j] >= 'A'  &&  tmp[j] <= 'Z')
                     tmp[j] = ((13 + tmp[j] - 'A') % 26) + 'A';
                  else if (tmp[j] >= 'a' && tmp[j] <= 'z')
                     tmp[j] = ((13 + tmp[j] - 'a') % 26) + 'a';
                  else if (tmp[j] >= '0' && tmp[j] <= '9')
                     tmp[j] = ((5 + tmp[j] - '0') % 10) + '0';
               }
               file[tmpln + i] = tmp;
            }
            printf("%d line%s rot13ified.\n", amt, amt == 1 ? "" : "s");
         }
         else printf("Cannot rot13 beyond end of file.\n");
         break;
      case "#":
         if (defs_not_done)
            printf("Warning: Macros have not yet been fully processed.\n");
         if (sizeof(bits) > 1)  {
if (bits[1] == "ALL")  printf("%O\n", defs);
            if (undefinedp(defs[bits[1]]))
               printf("No definition for \"%s\".\n", bits[1]);
            else
               printf("%s\n", defs[bits[1]]);
         }
         else printf("Which macro do you want to look up?\n");
         break;
      default:
         printf("Something odd has happened.  Tell Presto.\n");
         break;
   }
   printf(":");
   input_to( "get_command" );
   return;
}
void get_new_text(string new_in, string cmd, int count, int cmdline)  {
   string new_in2;
   int len;
   if ((len = strlen(new_in) - 1) > -1  &&  new_in[0] == '\\'  &&  !cmdline)  {
      new_in2 = new_in[1 .. ];
      --len;
   }
   else new_in2 = new_in;
   if (tab_replace)  new_in2 = replace(new_in2, "\t", tab_str);
   switch (cmd)  {
      case "i":
         if (len > -1)  {
            changed = 1;
            if (lnptr < fsize)  {
               undo = ({ ({ ({ "E", lnptr, ({ file[lnptr] }) }) }) }) +
                      undo;
               if (!tmpch)  file[lnptr] = new_in2 + file[lnptr];
               else file[lnptr] = file[lnptr][0 .. tmpch - 1] + new_in2 +
                                  file[lnptr][tmpch .. ];
            }
            else  {
               undo = ({ ({ ({ "D", fsize, 1 }) }) }) + undo;
               if (!fsize)  file = ({ new_in2, "End of file." });
               else file = file[0 .. fsize - 1] +
                           ({ new_in2, "End of file." });
               ++fsize;
            }
            if (tmpch <= chptr)  chptr += len + 1;
            print_line(1);
         }
         break;
      case "I":
         if (new_in != "."  ||  cmdline)  {
            if (new_in == "W"  &&  !mode_flag)  {
               if (this_player()->query_name() == "dogbolter")
                  printf("No more secret message!\n");
               get_new_text("", "W", count, 0);
               return;
            }
            if (new_in == ".;W"  &&  this_player()->query_name() == "warrax")  {
               write("You did that on purpose, didn't you?\n");
               get_new_text("", "W", count, 0);
               return;
            }
            changed = 1;
            if (!tmpln)  file = ({ new_in2 }) + file;
            else file = file[0 .. tmpln - 1] + ({ new_in2 }) +
                        file[tmpln .. ];
            ++tmpln;
            if (!cmdline)  {
               printf("]");
               input_to("get_new_text", 0, "I", count + 1, 0);
               return;
            }
         }
         if (count)  {
            if (tmpln - count <= lnptr)  lnptr += count;
            printf("%d line%s added.\n", count, count == 1 ? "" : "s");
            fsize += count;
            undo = ({ ({ ({ "D", tmpln - count, count }) }) }) + undo;
         }
         break;
      case "a":
         if (len > -1)  {
            changed = 1;
            if (lnptr < fsize)  {
               undo = ({ ({ ({ "E", lnptr, ({ file[lnptr] }) }) }) }) +
                      undo;
               file[lnptr] = file[lnptr][0 .. tmpch] + new_in2 +
                             file[lnptr][tmpch + 1 .. ];
            }
            else  {
               undo = ({ ({ ({ "D", fsize, 1 }) }) }) + undo;
               if (!fsize)  file = ({ new_in2, "End of file." });
               else file = file[0 .. fsize - 1] +
                           ({ new_in2, "End of file." });
               ++fsize;
            }
            print_line(1);
         }
         break;
      case "A":
         if (new_in != "."  ||  cmdline)  {
            changed = 1;
            if (tmpln == fsize)  --tmpln;
            file = file[0 .. tmpln] + ({ new_in2 }) +
                   file[tmpln + 1 .. ];
            ++tmpln;
            ++fsize;
            if (!cmdline)  {
               printf("]");
               input_to("get_new_text", 0, "A", count + 1, 0);
               return;
            }
         }
         if (count)  {
            printf("%d line%s added.\n", count, count == 1 ? "" : "s");
            undo = ({ ({ ({ "D", tmpln - count + 1, count }) }) }) + undo;
         }
         break;
      case "E":
         if (new_in != "."  ||  cmdline)  {
            changed = 1;
            if (tmpln < fsize)  {
               if (!count  ||  cmdline)
                  undo = ({ ({ ({ "E", tmpln, ({ file[tmpln] }) }) }) }) +
                         undo;
               else undo[0][0][2] += ({ file[tmpln] });
            }
            else  {
               if (!count  ||  cmdline)
                  undo = ({ ({ ({ "D", tmpln, 1 }) }) }) + undo;
               else if (undo[0][0][0] == "E")
                  undo[0] = ({ ({ "D", tmpln, 1 }) }) + undo[0];
               else ++undo[0][0][2];
               file += ({ "End of file." });
               ++fsize;
            }
            file[tmpln] = new_in2;
            if (tmpln == lnptr)  chptr = 0;
            ++tmpln;
            if (!cmdline)  {
               printf("]");
               input_to("get_new_text", 0, "E", count + 1, 0);
               return;
            }
         }
         if (count)
            printf("%d line%s changed.\n", count, count == 1 ? "" : "s");
         break;
      case "e":
         if (len > -1)  {
            changed = 1;
            if (lnptr < fsize)  {
               undo = ({ ({ ({ "E", lnptr, ({ file[lnptr] }) }) }) }) +
                      undo;
               if (!tmpch)
                  file[lnptr] = new_in2 + file[lnptr][len + 1 .. ];
               else file[lnptr] = file[lnptr][0 .. tmpch - 1] +
                                  new_in2 +
                                  file[lnptr][tmpch + len + 1 .. ];
            }
            else  {
               if (!fsize)  file = ({ new_in2, "End of file." });
               else file = file[0 .. fsize - 1] +
                           ({ new_in2, "End of file." });
               undo = ({ ({ ({ "D", fsize, 1 }) }) }) + undo;
               ++fsize;
            }
            print_line(1);
         }
         break;
      case "w":
      case "W":
         if (len > -1)  {
            new_in2 = replace(new_in2, ({ " ", "", "\t", "" }));
            name = this_player()->get_path(new_in2);
            this_player()->set_in_editor(name);
            if (save_file(cmd, 0))  {
               if (count)  {
                  if (!open_file(newname)  &&  newname == "...")
                     return;
                  if (member_array(name, open_history) == -1)
                     open_history += ({ name });
               }
               else if (cmd == "W")  return;
            }
         }
         else printf("Save canceled.\n");
         break;
      case "O":
         if (cmdline)  {
            len = to_int(new_in2);
            new_in2 = "";
            if (len == 0)  {
               printf("Cancelled.\n");
               if (file == 0)  {
                  this_player()->editor_do_quit(0);
                  return;
               }
            }
            else if (len > sizeof(open_history) - count)  {
               printf("Invalid choice.\n");
               if (file == 0)  {
                  this_player()->editor_do_quit(0);
                  return ;
               }
            }
            else new_in2 = open_history[len - 1];
            open_history = open_history[count .. ];
            if (new_in2 != "")  open_file(new_in2);
         }
         else  {
            if (new_in2 == "y"  ||  new_in2 == "Y")  {
               if (save_file("w", 1))  {
                  if (!changed)  {
                     if (!open_file(newname)  &&  newname == "...")
                        return;
                  }
                  else return;
               }
            }
            else if (new_in2 == "a"  ||  new_in2 == "A")
               printf("Open aborted.\n");
            else if (new_in2 == "n"  ||  new_in2 == "N") {
               printf("OK, you're the boss.\n");
               open_file(newname);
            }
            else  {
               printf("(Y)es, (N)o, or (A)bort?:]");
               input_to("get_new_text", 0, "O", count, 0);
               return;
            }
         }
         break;
      default:
         printf("How in the hell did you get here?\n");
         break;
   }
   printf(":");
   input_to("get_command");
   num_len = strlen(sprintf("%d", fsize + 1));
   return;
}
private int open_file(string filename)  {
   object *things;
   string  oldname;
   string  tmp;
   string *file_list;
   int     i;
   int     len;
   if (strlen(filename))  {
      if (mode_flag)  {
         if (filename == "...")  {
            if (!sizeof(open_history))  {
               printf("No files in your history.\n:");
               input_to("get_command");
               return -1;
            }
            else  {
               len = strlen(sprintf("%d", sizeof(open_history)));
               for (i = 0; i < sizeof(open_history); i++)  {
                  if (open_history[i] == name)
                     printf("%*d: %s (current file)\n", len, i + 1,
                            open_history[i]);
                  else
                     printf("%*d: %s\n", len, i + 1, open_history[i]);
               }
               printf("Choose file (enter nothing to cancel):] ");
               input_to("get_new_text", 0, "O", 0, 1);
               return -1;
            }
         }
         else if (sizeof(file_list =
                         get_dir(this_player()->get_path(filename))) > 1)  {
            i = strsrch(filename, '/', -1);
            if (i > -1)  filename = filename[0 .. i];
            else filename = "./";
            len = strlen(sprintf("%d", sizeof(file_list)));
            for (i = 0; i < sizeof(file_list); i++)  {
               if (file_list[i] == name)
                  printf("%*d: %s (current file)\n", len, i + 1, file_list[i]);
               else
                  printf("%*d: %s\n", len, i + 1, file_list[i]);
               file_list[i] = filename + file_list[i];
            }
            open_history = file_list + open_history;
            printf("Choose file (enter nothing to cancel):] ");
            input_to("get_new_text", 0, "O", i, 1);
            return -1;
         }
         else if (sizeof(things = WIZ_PRESENT->
                         wiz_present(filename, this_player())) == 1)  {
            oldname = this_player()->get_path(filename);
            filename = file_name(things[0]);
            sscanf(filename, "%s#%*s", filename);
            if (file_size(filename) == -2  ||  filename + ".c" == oldname)
               filename = oldname;
            else if (file_size(filename) == -1)  filename += ".c";
         }
         filename = this_player()->get_path(filename);
         if (file_size(filename) == -2)  {
            printf("\"%s\" is a directory.\n", filename);
            return 0;
         }
      }
      if (file_size(filename) == -1)  {
         if (mode_flag)  {
            if (filename != TMP_FILE)
               printf("Opening new file '%s'.\n", filename);
            else
               printf("Opening new file.\n");
         }
         file = ({ "End of file." });
         fsize = 0;
         this_player()->set_in_editor(filename);
      }
      else  {
         tmp = read_bytes(filename);
         if (stringp(tmp)) {
            file = explode(tmp, "\n") + ({ "End of file." });
            fsize = sizeof(file) - 1;
         }
         else {
            file = ({ "End of file." });
            fsize = 0;
         }
         this_player()->set_in_editor(filename);
         if (mode_flag)  {
            printf("%s opened", filename);
            if (!this_object()->write_permission(filename))
               printf(" (read only)");
            printf(".  (%d line%s, %d character%s)\n",
                   fsize, fsize == 1 ? "" : "s",
                   file_size(filename), file_size(filename) == 1 ? "" : "s");
         }
      }
      if (mode_flag)  {
         i = member_array(filename, open_history);
         if (i == -1)
            open_history += ({ filename });
         else if (i == 0)
            open_history = open_history[1 .. ] + ({ filename });
         else
            open_history = open_history[0 .. i - 1] +
                           open_history[i + 1 .. ] + ({ filename });
      }
   }
   else  {
      printf("Opening new file.\n");
      file = ({ "End of file." });
      fsize = 0;
      this_player()->set_in_editor("New file");
   }
   if (filename == ""  || (strlen(filename) > 2  &&
       (filename[<2 .. ] == ".h"  ||  filename[<2 .. ] == ".c")))
      highlight = 1;
   else
      highlight = 0;
   name = filename;
   lnptr = chptr = tmpln = tmpch = changed = 0;
   undo = ({ 0 });
   num_len = strlen(sprintf("%d", fsize + 1));
   in_string = 0;
   in_comment = 0;
   if (mode_flag)  {
      defs = ([ ]);
      defs_not_done = 1;
      while (remove_call_out("defines") != -1)
         ;
      call_out("defines", 1, name);
   }
   return 1;
}
private int save_file(string cmd, int open_pending)  {
   string tmp;
   string ftext;
   if (changed)  {
      if (strlen(name) == 0)  {
         printf("Enter a name for this file (enter nothing to cancel):]");
         input_to("get_new_text", 0, cmd, open_pending, 0);
         return 1;
      }
      ftext = fsize ? implode(file[0 .. fsize - 1], "\n") + "\n" : "";
      if (mode_flag)  {
         tmp = read_bytes(name);
         if (tmp  &&  !this_object()->rm_file(name))  {
            printf("Could not overwrite old file.\n");
            return 0;
         }
         else if (!write_file(name, ftext))  {
            printf("Could not write file '%s'.\n", name);
            if (tmp  &&  !write_file(name, tmp))
               printf("Could not restore the old version either.  Uh-oh.\n");
            return 0;
         }
         else  {
            changed = 0;
            printf("File '%s' saved.\n", name);
            undo[<1] = sizeof(undo) - 1;
         }
      }
   }
   else  {
      printf("No changes made; nothing saved.\n");
      ftext = "";
   }
   if (cmd == "W")  {
      this_player()->set_in_editor(0);
      this_player()->editor_do_quit(mode_flag || strlen(ftext) == 0 ? 0 :
                                    ftext);
   }
   return 1;
}
void my_more(string input, string *text, int startln, int number, int hilite,
             int pages, string xtratxt)
{
   int    i;
   int    j;
   int    k;
   int    len;
   int    limit;
   int    lines;
   int    oldlines;
   string junk;
   if (input == "q"  ||  input == "Q")  {
      printf(":");
      input_to("get_command");
      return;
   }
   i = lines = limit = 0;
   j = sizeof(text);
   do  {
      oldlines = lines;
      k = cols;
      if ((len = strlen(xtratxt)) == 0)  {
         junk = replace((number ? sprintf("%'.'*d] %s", num_len, 1 + startln++,
                                          text[i++])
                                : text[i++]), "\t", "\\TAB\\", "%", "%%");
         len = strlen(junk);
         ++lines;
         while (k < len)  {
            junk = junk[0 .. k - 1] + "\n" + junk[k .. ];
            ++lines;
            ++len;
            k += cols + 1;
         }
         if (hilite)
            junk = highlight(junk, startln - 1, number, lines >= rows);
      }
      else  {
         junk = xtratxt;
         ++lines;
         limit = 0;
         while ((k = strsrch(junk[limit .. ], "\n")) > -1)  {
            limit += k + 1;
            ++lines;
         }
         xtratxt = "";
      }
      if (lines < rows)  {
         if (len == 0)  printf("\n");
         else printf("%s\n", junk);
         len = 0;
      }
      else  {
         limit = 0;
         for (k = 0; k < rows - oldlines - 1; k++)  {
            limit += strsrch(junk[limit .. ], "\n") + 1;
         }
         xtratxt = junk[limit .. ];
         printf("%s", junk[0 .. limit - 1]);
      }
   }
   while (i < j  &&  lines < rows - 1);
   if ((i < j  ||  len)  &&  --pages)  {
      write("%^RESET%^MORE... enter 'q' to stop, anything else to continue:");
      input_to("my_more", 0, text[i .. ], startln, number, hilite, pages,
               xtratxt);
   }
   else  {
      if (i < j  &&  !pages)  lnptr -= j - i;
      write("%^RESET%^:");
      input_to("get_command");
   }
   return;
}
private void print_line(int show_ptr)  {
   string tmp;
   int    i;
   int    j;
   int    chr;
   int    tchr;
   int    len;
   chr = chptr;
   if (showln)  {
      tmp = sprintf("%'.'*d] %s", num_len, lnptr + 1, file[lnptr]);
      chr += num_len + 2;
   }
   else tmp = file[lnptr];
   tchr = chr;
   if (chr)  {
      chr += 4 * (chr - strlen(replace(tmp[0 .. chr - 1], "\t", "")));
   }
   if (tchr < strlen(tmp)  &&  tmp[tchr] == '\t')  chr += 2;
   tmp = replace(tmp, "\t", "\\TAB\\", "%", "%%");
   len = strlen(tmp);
   j = cols;
   while (j < len)  {
      tmp = tmp[0 .. j - 1] + "\n" + tmp[j .. ];
      ++len;
      j += cols + 1;
   }
   tmp += "\n";
   if (in_comment == lnptr + 1)
      in_comment = 0;
   if (!show_ptr)  {
      if (highlight)  {
         printf("%s", highlight(tmp, lnptr, showln, 0));
      }
      else  {
         printf("%s", tmp);
      }
   }
   else  {
      if (highlight)  tmp = highlight(tmp, lnptr, showln, 1);
      i = chr / cols + 1;
      tchr = 0;
      for (j = 0; j < i; j++)
         tchr += strsrch(tmp[tchr .. ], "\n") + 1;
      printf("%s", tmp[0 .. tchr - 1]);
      if (chr % cols)  {
          write("                                                           "
                "                                                           "
                "                                          "
                [0 .. chr % cols - 1] + "%^RESET%^^\n");
      }
      else write("%^RESET%^^\n");
      printf("%s", tmp[tchr .. ]);
   }
   return;
}
private string color_word(string word,
                          int ref if_flag, int ref include_flag,
                          int ref type_flag, int ref class_flag)  {
   string newword;
   int    i;
   include_flag = 0;
   type_flag = 0;
   if (strlen(newword = replace(word, "\n", "")) != 0)  {
      if (newword[0] >= '0'  &&  newword[0] <= '9')  {
         word = numb_color + word + "%^RESET%^";
      }
      else switch (newword)  {
         case "#include" :
            include_flag = 1;
         case "#define"  :
         case "#ifdef"   :
         case "#ifndef"  :
         case "#undef"   :
         case "#else"    :
         case "#elif"    :
         case "#endif"   :
         case "#pragma"  :
         case "#echo"    :
         case "varargs"  :
         case "protected":
         case "private"  :
         case "public"   :
         case "nosave"   :
         case "nomask"   :
         case "if"       :
         case "while"    :
         case "for"      :
         case "foreach"  :
         case "in"       :
         case "switch"   :
         case "return"   :
         case "do"       :
         case "else"     :
         case "case"     :
         case "break"    :
         case "default"  :
         case "continue" :
         case "inherit"  :
         case "new"      :
         case "efun"     :
            word = keyw_color + word + "%^RESET%^";
            if (strlen(word) != strlen(newword))  {
               i = strsrch(word, "\n");
               word = word[0 .. i] + keyw_color + word[i + 1 .. ];
            }
            if_flag = 0;
            break;
         case "#if"      :
            if_flag = 1;
            word = keyw_color + word + "%^RESET%^";
            if (strlen(word) != strlen(newword))  {
               i = strsrch(word, "\n");
               word = word[0 .. i] + keyw_color + word[i + 1 .. ];
            }
            if_flag = 1;
            break;
         case "defined"  :
            if (if_flag)  {
               word = keyw_color + word + "%^RESET%^";
            }
            if_flag = 0;
            break;
         case "class"    :
            class_flag = 1;
            word = type_color + word + "%^RESET%^";
            if (strlen(word) != strlen(newword))  {
               i = strsrch(word, "\n");
               word = word[0 .. i] + type_color + word[i + 1 .. ];
            }
            break;
         case "int"      :
         case "string"   :
         case "mixed"    :
         case "object"   :
         case "float"    :
         case "mapping"  :
         case "function" :
         case "buffer"   :
         case "ref"      :
            type_flag = 1;
         case "void"     :
            word = type_color + word + "%^RESET%^";
            if (strlen(word) != strlen(newword))  {
               i = strsrch(word, "\n");
               word = word[0 .. i] + type_color + word[i + 1 .. ];
            }
         default         :
            if (class_flag)  {
               word = type_color + word + "%^RESET%^";
               if (strlen(word) != strlen(newword))  {
                  i = strsrch(word, "\n");
                  word = word[0 .. i] + type_color + word[i + 1 .. ];
               }
               type_flag = 1;
               class_flag = 0;
            }
            break;
      }
   }
   return word;
}
private string *boom(string str, int linenum, int last_line)  {
   int     i;
   int     j;
   int     k;
   int     last;
   int     count;
   int     sep_flag = 0;
   int     op_flag = 0;
   int     split;
   int     if_flag;
   int     include_flag;
   int     type_flag;
   int     class_flag;
   string *shrapnel = ({ });
   last = 0;
   if_flag = 0;
   include_flag = 0;
   for (i = 0; i < strlen(str); i++)  {
      if (in_comment)  {
         split = 0;
         j = strsrch(str[i .. ], "*/");
         if (j == -1)  {
            split = 1;
            j = strsrch(str[i .. ], "*\n/");
         }
         if (j == -1)  {
            shrapnel += ({ comm_color + str[last .. ] + "%^RESET%^" });
            i = strlen(str) - 1;
         }
         else  {
            in_comment = 0;
            shrapnel += ({ comm_color + str[last .. i + j + 1 + split] +
                           "%^RESET%^" });
            i += j + 1 + split;
         }
         if (last_line)  {
            shrapnel[<1] = replace(shrapnel[<1], "\n", "\n" + comm_color);
         }
         sep_flag = op_flag = 0;
         last = i + 1;
      }
      else if (in_string  ||  str[i] == DQUOTES)  {
         if (i != last)  {
            shrapnel += ({ str[last .. i - 1] });
         }
         last = i;
         while (1)  {
            j = strsrch(str[i + 1 .. ], DQUOTES);
            if (j == -1)  {
               shrapnel += ({ stri_color + str[last .. ] + "%^RESET%^" });
               i = strlen(str) - 1;
               in_string = 1;
               break;
            }
            else  {
               k = i + j;
               count = split = 0;
               while (k > -1  &&  !split)  {
                  if (str[k] == '\\')  {
                     --k;
                     ++count;
                  }
                  else if (str[k] == '\n')  {
                     --k;
                  }
                  else split = 1;
               }
               i += j + 1;
               if (count % 2 == 0)  {
                  shrapnel += ({ stri_color + str[last .. i] +
                                 "%^RESET%^" });
                  in_string = 0;
                  break;
               }
            }
         }
         if (last_line)  {
            shrapnel[<1] = replace(shrapnel[<1], "\n", "\n" + stri_color);
         }
         sep_flag = op_flag = 0;
         last = i + 1;
      }
      else if (str[i] == SQUOTES)  {
         if (i != last)  {
            shrapnel += ({ str[last .. i - 1] });
         }
         last = i;
         while (1)  {
            j = strsrch(str[i + 1 .. ], SQUOTES);
            if (j == -1)  {
               shrapnel += ({ stri_color + str[last .. ] + "%^RESET%^" });
               i = strlen(str) - 1;
               break;
            }
            else  {
               k = i + j;
               count = split = 0;
               while (k > -1  &&  !split)  {
                  if (str[k] == '\\')  {
                     --k;
                     ++count;
                  }
                  else if (str[k] == '\n')  {
                     --k;
                  }
                  else split = 1;
               }
               i += j + 1;
               if (count % 2 == 0)  {
                  if (i == last + 1  &&  last + 2 < strlen(str)  &&
                      str[last + 2] == SQUOTES)
                  {
                     shrapnel += ({ stri_color + str[last .. last + 2] +
                                    "%^RESET%^" });
                     ++i;
                  }
                  else  {
                     shrapnel += ({ stri_color + str[last .. i] +
                                    "%^RESET%^" });
                  }
                  break;
               }
            }
         }
         if (last_line)  {
            shrapnel[<1] = replace(shrapnel[<1], "\n", "\n" + stri_color);
         }
         sep_flag = op_flag = 0;
         last = i + 1;
      }
      else if (str[i] == LESS  &&  include_flag)  {
         if (i != last)  {
            shrapnel += ({ str[last .. i - 1] });
         }
         j = strsrch(str[i + 1 .. ], GREATER);
         if (j == -1)  {
            shrapnel += ({ stri_color + str[i .. ] + "%^RESET%^" });
            i = strlen(str) - 1;
         }
         else  {
            shrapnel += ({ stri_color + str[i .. i + j + 1] + "%^RESET%^" });
            i += j + 1;
         }
         if (last_line)  {
            shrapnel[<1] = replace(shrapnel[<1], "\n", "\n" + stri_color);
         }
         sep_flag = op_flag = 0;
         last = i + 1;
      }
      else if (str[i .. i + 1] == "");
         if (j == -1)  {
            j = strsrch(str[i + 2 + split .. ], "*\n/");
            ++split;
         }
         if (j == -1)  {
            in_comment = linenum + 1;
            shrapnel += ({ comm_color + str[i .. ] + "%^RESET%^" });
            i = strlen(str) - 1;
         }
         else  {
            shrapnel += ({ comm_color + str[i .. i + j + 3 + split] +
                           "%^RESET%^" });
            i += j + 3 + split;
         }
         if (last_line)  {
            shrapnel[<1] = replace(shrapnel[<1], "\n", "\n" + comm_color);
         }
         sep_flag = op_flag = 0;
         last = i + 1;
      }
      else if (str[i .. i + 1] == "
         if (i != last)  {
            shrapnel += ({ str[last .. i - 1] });
         }
         shrapnel += ({ comm_color + str[i .. ] + "%^RESET%^" });
         i = strlen(str) - 1;
         if (last_line)  {
            shrapnel[<1] = replace(shrapnel[<1], "\n", "\n" + comm_color);
         }
         sep_flag = op_flag = 0;
         last = i + 1;
      }
      else if (member_array(str[i], SEPARATORS) != -1)  {
         if (last <= i - 1)  {
            shrapnel += ({ color_word(str[last .. i - 1],
                                      ref if_flag, ref include_flag,
                                      ref type_flag, ref class_flag) });
         }
         if (sep_flag)  {
            shrapnel[<1] += str[i .. i];
         }
         else  {
            shrapnel += ({ str[i .. i] });
            sep_flag = 1;
         }
         op_flag = 0;
         if (str[i] == SCOLON)
            type_flag = 0;
         last = i + 1;
      }
      else if (member_array(str[i], OPERATORS) != -1)  {
         if (last <= i - 1)  {
            shrapnel += ({ color_word(str[last .. i - 1],
                                      ref if_flag, ref include_flag,
                                      ref type_flag, ref class_flag) });
            class_flag = 0;
         }
         if (str[i] == TIMES  &&  type_flag)  {
            shrapnel += ({ type_color + str[i .. i] + "%^RESET%^" });
            type_flag = 0;
         }
         else if (op_flag)  {
             shrapnel[<1] = shrapnel[<1][0 .. <10] + str[i .. i] +
                            "%^RESET%^";
         }
         else  {
             shrapnel += ({ oper_color + str[i .. i] + "%^RESET%^" });
             op_flag = 1;
         }
         sep_flag = 0;
         last = i + 1;
      }
      else sep_flag = op_flag = 0;
   }
   if (last < i)  {
      shrapnel += ({ color_word(str[last .. ],
                                ref if_flag, ref include_flag,
                                ref type_flag, ref class_flag) });
   }
   return shrapnel;
}
private string highlight(string str, int linenum, int numbering,
                         int last_line)
{
   string *words;
   string  num = "";
   if (linenum == fsize)  return str;
   if (numbering)  {
      num = str[0 .. num_len + 1];
      str = str[num_len + 2 .. ];
   }
   words = boom(replace(str, "%^", "%%%^^^"), linenum, last_line);
   words = map(words, "fix_string", this_player());
   return this_player()->fix_string(num + implode(words, ""));
}
private void init_settings()  {
   string  rc;
   string  line;
   string *sets;
   string *bits;
   int     spaces;
   int     i;
   tab_str = "   ";
   tab_replace = 0;
   keyw_color = "%^CYAN%^";
   comm_color = "%^GREEN%^";
   numb_color = "%^MAGENTA%^";
   oper_color = "%^BLUE%^";
   stri_color = "%^YELLOW%^";
   type_color = "%^BOLD%^%^CYAN%^";
   rc = read_bytes("/w/" + this_player()->query_name() + "/.magicrc");
   if (strlen(rc) == 0)  return;
   sets = explode(rc, "\n");
   foreach (line in sets)  {
      bits = explode(line, " ") - ({ "" });
      if (sizeof(bits) > 2)  {
         if (bits[0] == "tab")  {
            if (bits[1] == "spacing")  {
               if ((spaces = to_int(bits[2])) > 0)  {
                  tab_str = "";
                  for (i = 0; i < spaces; i++)  {
                     tab_str += " ";
                  }
               }
            }
            else if (bits[1] == "replacement")  {
               if (bits[2] == "on")  tab_replace = 1;
               else tab_replace = 0;
            }
         }
         else if (bits[0] == "color")  {
            set_colors(bits[1 .. ]);
         }
         else if (bits[0] == "history")  {
            open_history = bits[1 .. ];
         }
      }
   }
   return;
}
private int set_colors(string *words)  {
   string tmp_color;
   tmp_color = implode(map(words[1 .. ],
                           (: "%^" + upper_case($1) + "%^" :)), "");
   switch (words[0])  {
      case "keyword":
         keyw_color = tmp_color;
         return 1;
      case "comment":
         comm_color = tmp_color;
         return 1;
      case "number":
         numb_color = tmp_color;
         return 1;
      case "string":
         stri_color = tmp_color;
         return 1;
      case "operator":
         oper_color = tmp_color;
         return 1;
      case "type":
         type_color = tmp_color;
         return 1;
      default:
         return 0;
   }
}
int write_permission(string name)  {
   return write_file(name, "");
}
int rm_file(string name)  {  return rm(name);  }
string *filter_regexp(string *incoming)  {
   string *result;
   int     i;
   result = allocate((sizeof(incoming) + 1) / 2);
   for (i = sizeof(incoming) - 1; i >= 0; i -= 2)
      result[i / 2] = incoming[i];
   return result;
}
int save_history()  {
   string tmp;
   string *junk;
   int i;
   int res;
   tmp = read_bytes("/w/" + this_player()->query_name() + "/.magicrc");
   if (tmp)  {
      junk = explode(tmp, "\n");
      for (i = 0; i < sizeof(junk); i++)  {
         if (junk[i][0 .. 6] == "history")  {
            junk[i] = sprintf("history %s",
                              implode(open_history[<10 .. ], " "));
            break;
         }
      }
   }
   else junk = ({ sprintf("history %s",
                          implode(open_history[<10 .. ], " ")) });
   res = write_file("/w/" + this_player()->query_name() + "/.magicrc",
                    implode(junk, "\n"), 1);
   return res;
}
string get_inc_path(string fname, string last_file)  {
   string  ret;
   string  tmp;
   string *bits;
   int     count;
   while (fname[0] == ' ')
      fname = fname[1 .. ];
   if (sscanf(fname, "<%s>", tmp) == 1)  {
      ret = "/include/";
      fname = tmp;
   }
   else if (sscanf(fname, "\"%s\"", tmp) == 1)  {
      if (tmp[0] == '/')
         ret = "";
      else  {
         bits = explode(last_file, "/");
         count = 2;
         while (tmp[0 .. 2] == "../")  {
           ++count;
           tmp = tmp[3 .. ];
         }
         ret = "/" + implode(bits[0 .. <count], "/") + "/";
      }
      fname = tmp;
   }
   else return "";
   if (file_size(ret + fname) < 0)
      return "";
   return ret + fname;
}
string expand_macros(string ins, string *sorted_defs)  {
   int     changed;
   int    *allowed = ({' ', '\t', '+', '-', ',', '(', '\"', '[' });
   int     off;
   string  def;
   do {
      changed = 0;
      foreach (def in sorted_defs)  {
         if ((off = strsrch(ins, def)) != -1)  {
            if (off == 0  ||  member_array(ins[off - 1], allowed) >= 0)  {
               ins = replace_string(ins, def, defs[def]);
               changed = 1;
            }
         }
      }
   }
   while(changed);
   return ins;
}
string strip_junk(string stuff){
   stuff = replace(stuff, ({ " ", "", "+", "", "(", "", ")", "" }));
   return replace_string(stuff, "\"\"", "");
}
void defines(string fname)  {
   string *lines;
   string  line;
   string  tmp;
   string  tmp2;
   int     off;
   string *sorted_defs;
   int     i;
   int     j;
   int     nest;
   if (fname != name)  {
      tmp = read_file(fname);
      if (tmp)
         lines = regexp(explode(tmp, "\n"), "^#[ ]*(include|define)[ \t]+");
      else
         lines = ({ });
   }
   else lines = regexp(file, "^#[ ]*(include|define)[ \t]+");
   foreach (line in lines)  {
      if ((off = strsrch(line, "include")) != -1)  {
         tmp = line[off + 8 .. ];
         tmp2 = get_inc_path(tmp, fname);
         call_out("defines", defs_not_done, tmp2);
         ++defs_not_done;
      }
      else {
         i = 0;
         nest = 0;
         off = strsrch(line, "define");
         tmp = line[off + 7 .. ];
         while (tmp[i] == ' ')
            ++i;
         tmp = tmp[i .. ];
         i = 0;
         while (i < strlen(tmp)  &&  (tmp[i] != ' '  ||  nest))  {
            if (tmp[i] == '(')  {
               ++nest;
            }
            else if (tmp[i] == ')')
               --nest;
            ++i;
         }
         j = i;
         while (j < strlen(tmp)  &&  tmp[j] != ' ')
            ++j;
         tmp2 = tmp[j .. ];
         tmp = tmp[0 .. i - 1];
         defs[tmp] = tmp2;
      }
   }
   --defs_not_done;
   if (!defs_not_done)  {
      sorted_defs = sort_array(keys(defs), -1);
      foreach (tmp, tmp2 in copy(defs))  {
         if (strsrch(tmp, '(') == -1)
            defs[tmp] = strip_junk(expand_macros(tmp2, sorted_defs));
      }
   }
}

==================================================
FILE: more_file.c
==================================================

#include <nroff.h>
#include <cmds/options.h>
#define ROWS (this_player()->query_rows() - 1)
#define COLS this_player()->query_cols()
private nosave int fsize, topl, botl, charl, real_rows, search_flag;
private nosave mixed mark_data;
private nosave string _more_file_fname,
              *mark_name,
              *filenames,
              finish_func,
              stat_line,
              last_search;
private int display_file() {
   int i;
   int ncols;
   int nrows;
   string file;
   string *bits;
   string *lines;
   string tstop;
   int tab;
   ncols = COLS;
   nrows = ROWS;
   file = read_file(_more_file_fname, topl, nrows);
   if (file == 0)
      return 0;
   tab = this_player()->query_property(TABSTOP_PROP);
   if (tab)
      tstop = sprintf("%" + tab + "' 's", "");
   else
      tstop = "<TAB>";
   file = replace(file, ({ "\t", tstop,
                           "\r", "^M",
                           sprintf("%c", 13), "^M" }));
   bits = explode("x\n" + file, "\n")[1 .. ];
   if (charl)
      bits[0] = bits[0][charl .. ];
   real_rows = 0;
   lines = ({ });
   for (i = 0; i < sizeof(bits); i++)  {
      if (strlen(bits[i]) > ncols)  {
         lines = ({ lines..., bits[i][0 .. ncols - 1] });
         bits[i] = bits[i][ncols .. ];
         charl += ncols;
         --i;
      } else {
         lines  = ({ lines..., bits[i] });
         charl = 0;
         ++real_rows;
      }
      if (sizeof(lines) == nrows)
         break;
   }
   printf("%s\n", implode(lines, "\n"));
   botl = topl + real_rows - 1;
   if (botl > fsize)
      botl = fsize;
  return 1;
}
private int get_next_filename() {
  string str;
  _more_file_fname = filenames[0];
  filenames = filenames[1 .. ];
  fsize = file_length(_more_file_fname);
  if (fsize == 0) {
    printf("Empty file.\n");
    if (sizeof(filenames) > 1)
      return get_next_filename();
    else
      return 0;
  }
  if (fsize == -1) {
    printf("File does not exist.\n");
    if (sizeof(filenames) > 1)
      return get_next_filename();
    else
      return 0;
  }
  if (fsize == -2) {
    printf("You cannot more a directory.\n");
    if (sizeof(filenames) > 1)
      return get_next_filename();
    else
      return 0;
  }
  topl = 1;
  charl = 0;
  printf( "\n" );
  str = read_file(_more_file_fname, 1, 1);
  if (str == 0)
    return 0;
  if (str[0] == '.')  {
    string s2;
    str = "/tmp/nroffed_file";
    if (NROFF_HAND->create_nroff(_more_file_fname, "/tmp/nroffed_file")) {
      s2 = NROFF_HAND->cat_file("/tmp/nroffed_file");
      rm("/tmp/nroffed_file.o");
      if (s2 != 0) {
        this_player()->more_string(s2, _more_file_fname);
        fsize = ROWS - 3;
        return 1;
      }
    }
  }
  return display_file();
}
private string *expand_path(string s) {
  string *s1;
  s1 = this_player()->get_files(s);
  if (s1 == 0)
    return ({ s });
  return s1;
}
int set_mark(string s) {
   int i;
   if (!mark_name) {
      mark_name = ({ });
      mark_data = ({ });
   }
   if ((i = member_array(s, mark_name)) != -1)
      mark_data[i] = ({ _more_file_fname, topl });
   else {
      mark_name += ({ s });
      mark_data += ({ ({ _more_file_fname, topl }) });
   }
   return 1;
}
private void status_line() {
   string *frog;
   string s;
   int i, percentage;
   if (!stat_line)
      stat_line = "$N From $T to $B of $S ($%%) - h for help. ";
   s = "";
   frog = explode(stat_line, "$");
   for (i = 0; i < sizeof(frog); i++) {
      if (frog[i] == "") {
         s += "$";
         ++i;
      }
      else switch (frog[i][0]) {
         case 'N':
            s += _more_file_fname + frog[i][1 .. ];
            break;
         case 'T':
            s += topl + frog[i][1 .. ];
            break;
         case 'B':
            if (botl > fsize)
               s += fsize + frog[i][1 .. ];
            else
               s += botl + frog[i][1 .. ];
            break;
         case '%':
            percentage = (botl * 100) / fsize;
            if (percentage > 100) percentage = 100;
            s += percentage + frog[i][1 .. ];
            break;
         case 'S':
            s += fsize + frog[i][1 .. ];
            break;
         default:
            printf("Bad tag (%s) found in format string.\n", frog[i]);
            break;
      }
   }
   printf("%s", s);
   return;
}
void next_page(string str) {
   int num, noargs, i, j, k, redraw;
   string s1, *s3;
   if (str == 0)
      str = "";
   if (sscanf(str, "%d%s", num, str) != 2)
      noargs = 1;
   s1 = extract(str, 1);
   switch (str[0 .. 0]) {
      case "":
      case " ":
         topl += real_rows;
         redraw = 1;
         break;
      case "f":
         if (noargs)
            num = 1;
         topl += ROWS * num;
         redraw = 1;
         break;
      case "q" :
         printf("OK.\n");
         return;
      case "/":
         search_flag = 0;
         j = topl + 4;
         if (s1[0] == '!') {
            search_flag = 1;
            s1 = extract(s1, 1);
         }
         set_mark("'");
         if (s1=="" || !s1)
            s1 = last_search;
         if (s1 == "") {
            printf("No previous search string.\n");
            break;
         }
         do {
            i = j;
            j = i + 900;
            if (j > fsize)
               j = fsize;
            s3 = explode(read_file(_more_file_fname, i, j), "\n");
            for (k = 0; k < sizeof(s3); k++)
               if (!search_flag) {
                  if (sscanf(s3[k], "%*s" + s1 + "%*s") == 2)
                     if (num-- <= 0)
                        break;
               } else
                  if (sscanf(s3[k], "%*s" + s1 + "%*s") != 2)
                     if (num-- <= 0)
                     break;
         } while (j < fsize && k == sizeof(s3));
         if (k == sizeof(s3))
            printf("Sorry " + s1 + " not found.\n");
         else {
            topl = i + k - 3;
            redraw = 1;
         }
         last_search = s1;
         break;
      case "?":
         i = topl;
         if (s1[0] == '!') {
            s1 = extract(s1, 1);
            search_flag = 3;
         } else
            search_flag = 2;
         set_mark("'");
         if (s1=="" || !s1)
            s1 = last_search;
         if (s1 == "") {
            printf("No previous search string.\n");
            break;
         }
         do {
            j = i - 900;
            if (j < 0)
               j = 0;
            s3 = explode(read_file(_more_file_fname, j, i), "\n");
            for (k = 0; k < sizeof(s3); k++)
               if (search_flag == 2) {
                  if (sscanf(s3[k], "%*s" + s1 + "%*s") == 2)
                     if (num-- <= 0)
                        break;
               } else
                  if (sscanf(s3[k], "%*s" + s1 + "%*s") != 2)
                     if (num-- <= 0)
                        break;
            i = j;
         } while (j > 0 && k == sizeof(s3));
         if (k == sizeof(s3))
            printf("Sorry "+ s1 +" not found.\n");
         else {
            topl = k + i - 2;
            redraw = 1;
         }
         last_search = s1;
         break;
      case "n":
         switch (search_flag) {
            case 0:
               next_page(num + "/");
               break;
            case 1:
               next_page(num + "/!");
               break;
            case 2:
               next_page(num + "?");
               break;
            case 3:
               next_page(num + "?!");
               break;
         }
         return;
      case "b":
         if (noargs)
            num = 1;
         if (topl > 0) {
            topl -= ROWS * num;
            redraw = 1;
            if (topl < 0)
               topl = 0;
         }
         break;
      case "G":
         if (noargs)
            num = fsize - ROWS + 1;
      case "g":
         set_mark("'");
         topl = num;
         if (topl >= fsize)
         topl = fsize - 2;
         redraw = 1;
         break;
      case "P":
         if (noargs)
            num = 100;
      case "p":
      case "%":
         redraw = 1;
         set_mark("'");
         topl = (num * fsize) / 100;
         if (topl + ROWS - 1 > fsize)
            topl -= ROWS - 1;
         break;
      case "d":
         if (noargs)
            num = ROWS / 2;
         topl += num;
         redraw = 1;
         break;
      case "u":
         if (noargs)
            num = ROWS / 2;
         topl -= num;
         redraw = 1;
         break;
      case "r":
         redraw = 1;
         break;
      case "m":
         if (s1 == "") {
            printf("Sorry, you must specify a name.\n");
            break;
         }
         set_mark(s1);
         printf("OK, mark " + s1 + " set.\n");
         break;
      case "'":
         if (!mark_name) {
            printf("Sorry, must go to a mark.\n");
            break;
         }
         if ((i = member_array(s1, mark_name)) != -1) {
            if (_more_file_fname != mark_data[i][0]) {
               _more_file_fname = mark_data[i][0];
               redraw = 1;
            }
            if (topl != mark_data[i][1]) {
               topl = mark_data[i][1];
               redraw = 1;
            }
         } else
            printf("Mark " + s1 + " not set.\n");
         break;
      case "F":
         filenames = expand_path(str);
         if (sizeof(filenames) == 0) {
            printf("No matching files.\n");
            break;
         }
         last_search = "";
         redraw = get_next_filename();
         break;
      case "h":
         cat("/doc/helpdir/more");
         break;
   }
   if (redraw)
      display_file();
   if (botl < fsize || charl) {
      status_line();
      input_to("next_page");
   } else
      if (sizeof(filenames) > 0) {
         if (get_next_filename())
            input_to("next_page");
         else if (finish_func)
            call_other(this_player(), finish_func);
      } else {
         if (finish_func)
            call_other(this_player(), finish_func);
      }
}
int more_file(string str) {
   filenames = expand_path(str);
   if (!sizeof(filenames)) {
      notify_fail("No matching files.\n");
      return 0;
   }
   last_search = "";
   if (!get_next_filename())  {
      notify_fail("Could not read " + _more_file_fname + ".\n");
      return 0;
   }
   if (botl < fsize || charl) {
      status_line();
      input_to("next_page");
   } else
      if (finish_func)
         call_other(this_player(), finish_func);
   return 1;
}

==================================================
FILE: more_string.c
==================================================

#define COLS (int)this_object()->query_cols()
#define ROWS ( (int)this_object()->query_rows() - 1 )
class more_string_info {
   int fsize;
   int topl;
   int botl;
   string last_search;
   string *the_bit;
   string finish_func;
   string more_bit;
   string stat_line;
   object finish_ob;
}
private nosave mixed *_pending_more;
private class more_string_info _current_info;
int internal_more_string();
void create() {
   add_command("Internal_More_String", "<string>", (:internal_more_string:));
}
private void string_display_file(class more_string_info info) {
  int i;
  string stuff;
  info->botl = info->topl + ROWS;
  stuff = "";
  for ( i = info->topl; ( i < info->botl ) && ( i < info->fsize ); i++ ) {
    stuff += info->the_bit[ i ] +"\n";
  }
  efun::tell_object( this_object(), stuff );
}
private void more_string_status_line(class more_string_info info) {
   string *frog;
   string s;
   int i;
   int percentage;
   if (!info->stat_line) {
      info->stat_line = "$N From $T to $B of $S ($%%) - h for help. ";
   }
   s = "";
   frog = explode(info->stat_line, "$");
   for (i=0;i<sizeof(frog);i++) {
      if (frog[i] == "") {
         s += "$";
         i ++;
      } else switch (frog[i][0]) {
         case 'N' :
            s += info->more_bit+frog[i][1..];
            break;
         case 'T' :
            s += ( info->topl + 1 ) + frog[ i ][ 1 .. ];
            break;
         case 'B' :
            if (info->botl > info->fsize)
               s += info->fsize+frog[i][1..];
            else
               s += info->botl+frog[i][1..];
            break;
         case '%' :
            percentage = (info->botl*100)/info->fsize;
            if (percentage > 100) {
               percentage = 100;
            }
            s += percentage + frog[i][1..];
            break;
         case 'S' :
            s += info->fsize + frog[i][1..];
            break;
      }
   }
   efun::tell_object( this_object(), (string)this_object()->fix_string( s ) );
   return;
}
private void string_next_page(string str, class more_string_info info) {
   int num;
   int noargs;
   int i;
   int redraw;
   string s1;
   if (!str) {
     str = "";
   }
   if (sscanf(str,"%d%s", num, str) != 2) {
     noargs = 1;
   }
   s1 = str[1..];
   if (str == "") {
      str = "f";
   }
   switch(str[0]) {
      case 'h' :
         cat("/doc/helpdir/more");
         break;
      case 'q' :
         if (info->finish_func) {
            if (functionp(info->finish_func)) {
               evaluate(info->finish_func);
            } else {
               call_other(info->finish_ob, info->finish_func);
            }
         }
         info->finish_func = 0;
         _current_info = 0;
         return;
      case 'f' :
      case 'F' :
         info->topl += ROWS;
         redraw = 1;
         break;
      case 'b' :
      case 'B' :
         info->topl -= ROWS;
         redraw = 1;
         break;
      case '/' :
         i = info->topl + 4;
         if (!s1 || s1 == "") {
            s1 = info->last_search;
         }
         if (!s1 || s1 == "") {
            s1 = "bing!";
         }
         for (i = info->topl + 4; i < info->fsize; i++) {
            if (strsrch(info->the_bit[i], s1) != -1) {
               if (num-- <= 0) {
                  break;
               }
            }
         }
         if (i == info->fsize) {
            tell_object( this_object(), "Sorry "+ s1 +" not found.\n" );
         } else {
            tell_object( this_object(), "Found " + s1 + " on line "+ i +".\n");
            info->topl = i - 3;
         }
         redraw = 1;
         break;
      case '?' :
         if (!s1 || s1 == "") {
            s1 = info->last_search;
         }
         if (!s1 || s1 == "") {
            s1 = "bing!";
         }
         for (i = info->topl + 2; i > 0; i--) {
            if (strsrch(info->the_bit[i], s1) != -1) {
               if (num-- <= 0) {
                  break;
               }
            }
         }
         if (i == 0) {
            tell_object(this_object(), "Sorry " + s1 + " not found.\n");
         } else {
            info->topl = i - 3;
         }
         redraw = 1;
         break;
      case 'b' :
         if (info->topl > 0) {
            info->topl -= ROWS;
            redraw = 1;
            if (info->topl < 0) {
               info->topl = 0;
            }
         }
         break;
      case 'g' :
         info->topl = num;
         if (info->topl >= info->fsize)
            info->topl = info->fsize - 2;
         redraw = 1;
         break;
      case 'G' :
         redraw = 1;
         if (noargs)
            info->topl = info->fsize - ROWS;
         else
            info->topl = num;
         if (info->topl > info->fsize)
            info->topl = info->fsize - 2;
         break;
   }
   if (info->topl < 0) {
      info->topl = 0;
   }
   if (redraw) {
      string_display_file(info);
      if ( info->botl < info->fsize ) {
         more_string_status_line(info);
         input_to((: string_next_page :), 0, info);
      } else {
         if (info->finish_func) {
            if ( info->finish_ob ) {
               call_other(info->finish_ob, info->finish_func);
            }
            info->finish_func = 0;
         }
         _current_info = 0;
      }
   } else {
      more_string_status_line(info);
      input_to((: string_next_page :), 0, info);
   }
}
varargs int more_string( string text, string bity, int noreline ) {
  int i, ncols;
  string *bits;
  class more_string_info info;
  mixed func;
  if ( this_player() != this_object() ){
     if ( !_pending_more ) {
        _pending_more = ({ ({ text, bity, noreline }) });
     } else {
        _pending_more += ({ ({ text, bity, noreline }) });
     }
     this_object()->ignore_from_history("Internal_More_String something");
     command( "Internal_More_String something" );
     return 1;
  }
  if (!_current_info) {
     _current_info = new(class more_string_info);
  }
  info = _current_info;
  if ( bity ) {
    info->more_bit = bity;
  } else {
    info->more_bit = "--- MORE";
  }
  info->last_search = "";
  if ( !stringp( text ) || !strlen( text ) ) {
    return notify_fail( "Empty string.\n" );
  }
  if ( noreline ) {
    info->the_bit = explode( this_object()->fix_string( text ), "\n" );
  } else {
    text = this_object()->convert_message( text );
    text = this_object()->fit_message( text );
    text = this_object()->fix_string( text );
    info->the_bit = ({ });
    ncols = COLS;
    bits = explode( text, "\n" );
    for ( i = 0; i < sizeof( bits ); i++ ) {
      reset_eval_cost();
      if ( bits[ i ] == "" ) {
        info->the_bit += ({ "" });
      } else {
        info->the_bit +=
          explode( this_object()->fix_string( bits[ i ], ncols ), "\n" );
      }
    }
  }
  info->fsize = sizeof( info->the_bit );
  info->topl = 0;
  string_display_file(info);
  if ( info->botl < info->fsize ) {
    more_string_status_line(info);
    input_to( (: string_next_page :), 0, info );
  } else {
      if ( info->finish_func ) {
         if ( !info->finish_ob ) {
            info->finish_func = 0;
            return 1;
         }
         func = info->finish_func;
         info->finish_func = 0;
         call_other( info->finish_ob, func );
      }
      _current_info = 0;
  }
  return 1;
}
varargs void set_finish_func(string str, object ob) {
  if (!_current_info) {
     _current_info = new(class more_string_info);
  }
  _current_info->finish_func = str;
  if (!ob) {
    _current_info->finish_ob = previous_object();
  } else {
    _current_info->finish_ob = ob;
  }
}
private int internal_more_string() {
   string text, bity;
   int noreline;
   if ( sizeof( _pending_more ) ) {
      text = _pending_more[ 0 ][ 0 ];
      bity = _pending_more[ 0 ][ 1 ];
      noreline = _pending_more[ 0 ][ 2 ];
      _pending_more = _pending_more[ 1 .. <1 ];
      more_string( text, bity, noreline );
   }
   return 1;
}

==================================================
FILE: new_parse.c
==================================================

#include <soul.h>
#include <creator.h>
#include <user_parser.h>
#include <command.h>
#include <obj_parser.h>
#include <function.h>
inherit "/global/command";
#define NEW_SOUL
#define MY_MESS_HEADER "#!"
#define OTHER_MESS_HEADER "!#"
class fail_mess_data {
    object* direct;
    object* indirect;
    int weight;
}
private nosave mapping _succ_mess;
private nosave mapping _fail_mess;
private nosave mapping _cur_objects;
private nosave object *_succ_indir;
private nosave object *_succ_mess_dir;
private nosave object *_succ_mess_indir;
private nosave mapping _commands;
private nosave string *_failed_mess;
private nosave string _curpat;
int *pattern_match(string *bits, mixed *pattern);
private int handle_command(string *bits, int *matches, mixed *pattern,
                            mixed *command, string pattern_str);
string get_fail_messages(string verb, object *fail_obs);
void print_special_messages(string verb);
string *query_word_list(string bing);
private void remove_object2(object ob, int flag);
private void remove_object_force(object ob);
varargs string create_message(string *bits, int *matches, mixed *pattern,
                                             object *dir_obs, int flag);
int syntax_messages(string str);
string query_name();
void create() {
   _commands = ([ ]);
   _fail_mess = ([ ]);
   _succ_mess = ([ ]);
   _cur_objects = ([ ]);
   _succ_indir = _succ_mess_dir = _succ_mess_indir = ({ });
   command::create();
}
mapping query_p_commands() { return copy( _commands ); }
mapping query_p_objects() { return copy( _cur_objects ); }
mixed *query_parse_command(string name) { return _commands[name]; }
object* query_parse_command_objects(string name) {
   class command_class command;
   class command_data command_data;
   string pattern;
   object* obs;
   command = _commands[name];
   obs = ({ });
   if (command) {
      foreach (pattern, command_data in command->patterns) {
         obs += filter(command_data->calls, (: objectp($1) :));
      }
   }
   return obs;
}
object* query_succ_mess_indir() {
    return _succ_mess_indir;
}
void parser_commands() {
#if efun_defined(add_action)
   add_action("new_parser", "*", -2);
#endif
   add_command("syntax", "<word'verb'>", (:syntax_messages($4[0]):));
}
int add_succeeded(mixed ob) {
   int i;
   if (!pointerp(_succ_indir)) _succ_indir = ({ });
   if (objectp(ob)) {
      if (member_array(ob, _succ_indir) == -1) {
         _succ_indir += ({ ob });
      } else {
         return 1;
      }
   } else if (!pointerp(ob)) {
      return 0;
   } else for (i=0;i<sizeof(ob);i++) {
      if (member_array(ob[i], _succ_indir) == -1) {
         _succ_indir += ({ ob[i] });
      }
   }
   return 1;
}
int add_succeeded_mess(object dir, mixed incoming_mess, object *in_dir) {
   string my_mess, other_mess;
   if (!pointerp(incoming_mess)) {
      if (stringp(incoming_mess)) {
         my_mess = MY_MESS_HEADER+incoming_mess;
         other_mess = OTHER_MESS_HEADER+incoming_mess;
      } else {
         write("Parameter to add_succeeded_mess() must be a string or "
                  "array.\n");
         return 0;
      }
   } else if (sizeof(incoming_mess) == 2) {
      my_mess = MY_MESS_HEADER+incoming_mess[0];
      other_mess = OTHER_MESS_HEADER+incoming_mess[1];
   } else {
      write("Message array to add_succeeded_mess() must be two long.\n");
      return 0;
   }
   if ( undefinedp( in_dir ) ) {
       in_dir = ({ });
   }
   if (!_succ_mess[my_mess]) {
      _succ_mess[my_mess] = ({ ({ dir }), in_dir });
   } else {
      if (member_array(dir, _succ_mess[my_mess][0]) == -1) {
         _succ_mess[my_mess][0] += ({ dir });
      }
      in_dir = in_dir - _succ_mess[my_mess][1];
      _succ_mess[my_mess][1] += in_dir;
   }
   if (!_succ_mess[other_mess]) {
      _succ_mess[other_mess] = ({ ({ dir }), in_dir });
   } else {
      if (member_array(dir, _succ_mess[other_mess][0]) == -1) {
         _succ_mess[other_mess][0] += ({ dir });
      }
      in_dir = in_dir - _succ_mess[other_mess][1];
      _succ_mess[other_mess][1] += in_dir;
   }
   if (member_array(dir, _succ_mess_dir) == -1) {
      _succ_mess_dir += ({ dir });
   }
   return 1;
}
void add_failed_mess( object dir, string mess, mixed *in_dir ) {
   int i;
   class fail_mess_data fail;
   if (!stringp(mess)) {
      write("Parameter to add_failed_mess() must be a string.\n");
      return;
   }
   if ( undefinedp( in_dir ) ) {
      in_dir = ({ });
   }
   if (!_fail_mess[mess]) {
      fail = new(class fail_mess_data);
      fail->direct = ({ dir });
      fail->indirect = in_dir;
      _fail_mess[mess] = fail;
   } else {
      if (member_array(dir, _fail_mess[mess]->direct) == -1) {
         _fail_mess[mess]->direct += ({ dir });
      }
      for (i=0;i<sizeof(in_dir);i++) {
         if (member_array(in_dir[i], _fail_mess[mess]->indirect) == -1) {
            _fail_mess[mess]->indirect += in_dir[i..i];
         }
      }
   }
   if (member_array(dir, _succ_mess_indir) == -1) {
      _succ_mess_indir += ({ dir });
   }
}
object *query_succ_mess_dir() {
    return _succ_mess_dir;
}
int query_failed_message_exists(object dir) {
    string mess;
    class fail_mess_data stuff;
    foreach (mess, stuff in _fail_mess) {
         if (member_array(dir, stuff->direct) != -1) {
             return 1;
         }
    }
    return 0;
}
varargs int add_command(string cmd, object ob, mixed format, function funct) {
   int i;
   int idx;
   class command_class command;
   class command_data command_data;
   if ((funct && !functionp(funct)) || !objectp(ob)) {
      return 0;
   }
   if (!format) {
      format = "<direct:object>";
   } else if (pointerp(format)) {
      for (i = 0; i < sizeof(format); i++) {
         add_command(cmd, ob, format[i], funct);
      }
      return 1;
   } else if (!stringp(format)) {
      return 0;
   }
   command = _commands[cmd];
   if (!command) {
      command = new(class command_class);
      command->patterns = ([ ]);
      command->order = 0;
      _commands[cmd] = command;
   }
   command_data = command->patterns[format];
   if (command_data) {
      idx = member_array(ob, command_data->calls);
      if (idx != -1) {
         command_data->calls[idx + 1] = funct;
      } else {
         command_data->calls += ({ ob, funct });
      }
   } else {
      command_data = new(class command_data);
      command_data->calls = ({ ob, funct });
      command->order = 0;
      command->patterns[format] = command_data;
   }
   if (_cur_objects[ob]) {
      _cur_objects[ob] |= ({ cmd });
   } else {
      _cur_objects[ob] = ({ cmd });
   }
   return 1;
}
int remove_object(mixed ob, int was_env) {
   if (objectp(ob) && !_cur_objects[ob] && !was_env) {
      return 0;
   }
   remove_object2(ob, was_env);
   return 1;
}
private void remove_object2(object ob, int was_env) {
   object womble;
   object *inv_match;
   if (!ob ||
       (!was_env && (environment() == ob ||
                     environment(ob) == this_object() ||
                     environment(ob) == environment()))) {
      return ;
   }
   if (was_env == 1) {
      remove_object_force(ob);
      inv_match = ob->find_inv_match();
      if ( arrayp( inv_match ) ) {
        foreach (womble in inv_match) {
           if (objectp(womble) && womble != this_object() &&
               _cur_objects[womble]) {
              remove_object_force(womble);
           }
        }
      }
      return ;
   }
   return ;
}
private void remove_from_command(string cmd, object ob) {
   int k;
   string format;
   class command_data command_data;
   if (!_commands[cmd]) {
      return ;
   }
   foreach (format, command_data in _commands[cmd]->patterns) {
      for (k = 0; k < sizeof(command_data->calls); k += 2) {
         if (!command_data->calls[k] || command_data->calls[k] == ob) {
            command_data->calls = command_data->calls[0..k - 1] + command_data->calls[k + 2..];
         }
      }
      if (!sizeof(command_data->calls)) {
         map_delete(_commands[cmd]->patterns, format);
         if (_commands[cmd]->order) {
            _commands[cmd]->order -= ({ format });
         }
      }
   }
   if (!sizeof(_commands[cmd]->patterns)) {
      map_delete(_commands, cmd);
   }
}
private void remove_object_force(object ob) {
   string ind;
   if (!_cur_objects[ob]) {
      return 0;
   }
   foreach (ind in _cur_objects[ob]) {
      remove_from_command(ind, ob);
   }
   map_delete(_cur_objects, ob);
}
void event_dest_me(object ob) {
   remove_object_force(ob);
}
void event_exit(object ob, string mess, object dest) {
   if (dest == this_object() || dest == environment()) {
      return ;
   }
   remove_object_force(ob);
}
void me_moveing(object from) {
   if (from) {
      remove_object(from, 1);
   }
}
nomask int new_parser(string str) {
   string *bits;
   string pattern_str;
   string format;
   mixed *wombat;
   mixed *soul_stuff;
   mixed *pattern;
   mixed *command_stuff;
   mixed *stuff;
   int i;
   int j;
   int ret;
   int flag;
   class command_class command;
   class command_data command_data;
   bits = explode(str, " ") - ({ "", 0 });
   command_stuff = cmdPatterns(bits[0]);
   if (this_object()->command_shadowed(bits[0], implode(bits[1..], " "))) {
      return 1;
   }
   command = _commands[bits[0]];
#ifdef NEW_SOUL
   if (!command && !sizeof(command_stuff)) {
      soul_stuff = SOUL_OBJECT->query_soul_command(bits[0]);
      if (!soul_stuff) {
         return 0;
      }
   }
#else
   if (!_commands[bits[0]] && !sizeof(command_stuff)) {
      return 0;
   }
#endif
   _failed_mess = ({ "", "" });
    current_verb = bits[ 0 ];
   if (!soul_stuff) {
      if (command) {
         if (!command->order) {
            foreach (pattern_str, command_data in command->patterns) {
               if (!command_data->weight) {
                  pattern =  PATTERN_OB->query_pattern(pattern_str);
                  if (pattern) {
                     command_data->weight = pattern[0];
                  } else {
                     map_delete(command->patterns, pattern_str);
                  }
               }
            }
            command->order = sort_array(keys(command->patterns),
                                   (: ((class command_data)$3[$2])->weight -
                                      ((class command_data)$3[$1])->weight :),
                                   command->patterns);
         }
         format = command->order[0];
         command_data = command->patterns[format];
      } else {
         command = new(class command_class);
         command->order = ({ });
         command->patterns = ([ ]);
      }
      for (i = 0, j = 0; i < sizeof(command->order) ||
                         j < sizeof(command_stuff); ) {
         if (i < sizeof(command->order)) {
            format = command->order[i];
            command_data = command->patterns[format];
         } else {
            command_data = 0;
         }
         if (j < sizeof(command_stuff) &&
             (!command_data ||
              command_data->weight < command_stuff[j][PATTERN_WEIGHT])) {
            pattern_str = command_stuff[j][PATTERN_STRING];
            stuff = command_stuff[j++][OBJS..];
            flag = 1;
         } else {
            pattern_str = format;
            flag = 0;
            stuff = command_data->calls;
            i++;
         }
         pattern = PATTERN_OB->query_pattern(pattern_str);
         if (!pattern) {
            continue;
         }
         wombat = pattern_match(bits, pattern);
         if (wombat && (ret = handle_command(bits, wombat, pattern, stuff,
                                             pattern_str))) {
            if (ret == -1) {
               if (flag) {
                  j = 100;
               } else {
                  i = 100;
               }
            } else {
               return 1;
            }
         }
         if (wombat && !sizeof(wombat)) {
            int cont;
            string pat;
            mixed *junk;
            if (_curpat[<2] == '}' || _curpat[<2] == ']') {
               if (_curpat[<2] == '}') {
                  _curpat = _curpat[0..strsrch(_curpat, '{', -1)-2];
               } else {
                  _curpat = _curpat[0..strsrch(_curpat, '[', -1)-2];
               }
            } else {
               _curpat = implode((explode(_curpat, " ") - ({0,""}))[0..<2], " ");
            }
            if (flag) {
               foreach (junk in command_stuff[j..]) {
                  pat = junk[PATTERN_STRING];
                  pat = replace(pat, ({":object", "", ":living", "",
                                                 ":any-living", "", ":distant-living", "",
                                                 ":here", "", ":me>", ">", ":here-me", "",
                                                 ":me-here", "" }));
                  if (_curpat == pat) {
                     cont = 1;
                     break;
                  }
               }
               if (!cont) {
                  j = 100;
               }
            } else {
               foreach (pat in command->order[i..]) {
                  pat = junk[PATTERN_STRING];
                  pat = replace(pat, ({":object", "", ":living", "",
                                                 ":any-living", "", ":distant-living", "",
                                                 ":here", "", ":me>", ">", ":here-me", "",
                                                 ":me-here", "" }));
                  if (_curpat == pat) {
                     cont = 1;
                     break;
                  }
               }
               if (!cont) {
                  i = 100;
               }
            }
         }
      }
   }
#ifdef NEW_SOUL
   if ( !ret ) {
      if (!soul_stuff) {
         soul_stuff = SOUL_OBJECT->query_soul_command(bits[0]);
      }
      for (i=0;i<sizeof(soul_stuff);i++) {
         pattern = PATTERN_OB->query_pattern(soul_stuff[i][PATTERN_STRING]);
         wombat = pattern_match(bits, pattern);
         if (wombat && handle_command(bits, wombat, pattern, soul_stuff[i][OBJS..],
                                      soul_stuff[i][PATTERN_STRING])) {
            return 1;
         }
      }
   }
#endif
   if (_failed_mess[1] == "") {
      if (!query_notify_fail()) {
         if (_failed_mess[0] == "") {
            notify_fail( "See \"syntax "+ bits[ 0 ] +
                  "\" for the input patterns.\n");
         } else {
            notify_fail( _failed_mess[0] );
         }
      }
   } else {
      notify_fail(_failed_mess[1]);
   }
   _fail_mess = ([ ]);
   return 0;
}
int syntax_messages(string str) {
   string the_mess;
   int i;
   string tmp;
   class command_data fluff;
   mixed *soul_stuff;
   mixed *command_stuff;
   if (!str) {
      notify_fail("Syntax: syntax <verb>\n");
      return 0;
   }
   command_stuff = cmdPatterns(str);
#ifdef NEW_SOUL
   soul_stuff = SOUL_OBJECT->query_soul_command(str);
   if (!_commands[str] && !soul_stuff && !sizeof(command_stuff)) {
      notify_fail("Could not find the verb '"+str+"'.\n");
      return 0;
   }
#else
   if (!_commands[str] && !sizeof(command_stuff)) {
      notify_fail("Could not find the verb '"+str+"'.\n");
      return 0;
   }
#endif
   the_mess = "Forms of syntax available for the command \""+ str +"\":\n";
   if (_commands[str]) {
      foreach (tmp, fluff in _commands[str]->patterns) {
         the_mess += str+" "+PATTERN_OB->query_short_pattern(tmp) + "\n";
      }
   }
   for (i=0;i<sizeof(command_stuff);i++) {
       the_mess += str+" "+PATTERN_OB->query_short_pattern(
                                        command_stuff[i][PATTERN_STRING]) + "\n";
   }
   for (i=0;i<sizeof(soul_stuff);i++) {
       the_mess += str+" "+PATTERN_OB->query_short_pattern(
                                        soul_stuff[i][PATTERN_STRING]) + "\n";
   }
   write(the_mess);
   return 1;
}
int *pattern_match(string *bits, mixed *pattern) {
   string *elms;
   int pos, *delayed, last, failed, j, opt, i, word_offset, spaces, wcount,
      *matches;
   mixed tmp;
   pos = wcount = 1;
   _curpat = "";
   matches = ({ 0 });
   delayed = ({ });
   for (i = 1; i < sizeof(pattern) && !failed; i++) {
      if (pos >= sizeof(bits))
         failed = 1;
      _curpat += PATTERN[pattern[i]];
      switch (pattern[i]) {
         case DIRECT_OBJECT :
         case INDIRECT_OBJECT :
            i++;
            if (pattern[i] == TARGET_PLAYER) {
               if (last) {
                  delayed += ({ SINGLE_WORD });
                  word_offset++;
                  pos++;
               } else {
                  pos++;
                  matches += ({ pos - 1 });
               }
               failed |= pos > sizeof(bits);
            } else {
               if (last) {
                  delayed += ({ SINGLE_WORD });
               } else {
                  delayed = ({ STRING });
                  last = FIND_FIRST;
               }
               word_offset++;
               pos++;
            }
            i++;
            break;
         case STRING :
            if (last) {
               pos -= word_offset-1;
               for (j=0;j<sizeof(delayed);j++) {
                  switch (delayed[j]) {
                     case STRING :
                        matches += ({ pos - 1 });
                        pos++;
                        break;
                     case OPTIONAL :
                        matches += ({ matches[<1] });
                        break;
                     case SINGLE_WORD :
                        matches += ({ pos - 1 });
                        pos++;
                        break;
                  }
               }
            }
            delayed = ({ STRING });
            word_offset = 1;
            pos++;
            last = FIND_LAST;
            break;
         case QUOTED_STRING :
            if (last) {
                while (pos < sizeof(bits) &&
                           bits[pos][0] != '"' &&
                           bits[pos][0] != '\'' &&
                           bits[pos][0] != '`') {
                     pos++;
                }
                if (pos < sizeof(bits)) {
                     pos -= word_offset;
                     for (j = 0; j < sizeof(delayed); j++) {
                         switch (delayed[j]) {
                              case STRING :
                                  matches += ({ pos });
                                  pos++;
                                  break;
                              case OPTIONAL :
                                  matches += ({ matches[<1] });
                                  break;
                              case SINGLE_WORD :
                                  matches += ({ pos });
                                  pos++;
                                  break;
                         }
                     }
                     last = FIND_NONE;
                } else {
                     failed = 1;
                }
            }
            if (pos > sizeof(bits)) {
                failed = 1;
            }
            if (!failed) {
                switch (bits[pos][0]) {
                     case '"' :
                     case '\'' :
                     case '`' :
                         j = pos;
                         while (j < sizeof(bits) &&
                                    bits[j][<1] != bits[pos][0]) {
                              j++;
                         }
                         if (j < sizeof(bits)) {
                              matches += ({ j });
                              pos = j + 1;
                         } else {
                              failed = 1;
                         }
                         break;
                     default :
                         failed = 1;
                         break;
                }
            }
            break;
         case SHORT_STRING :
            if (last) {
               delayed += ({ SINGLE_WORD });
            } else {
               delayed = ({ STRING });
            }
            word_offset++;
            pos++;
            last = FIND_FIRST;
            break;
         case SINGLE_WORD :
            if (last) {
               delayed += ({ SINGLE_WORD });
               word_offset++;
               pos++;
            } else {
               matches += ({ pos });
               pos++;
            }
            failed |= pos > sizeof(bits);
            break;
         case NUMBER :
         case FRACTION :
            failed = 1;
            if (last == FIND_LAST) {
               for (j = sizeof(bits) - 1; j >= pos; j--)
                  if ((bits[j][0] >= '0' && bits[j][0] <= '9') ||
                        (pattern[i] != FRACTION && bits[j][0] == '-' &&
                         bits[j][1] >= '0' && bits[j][1] <= '9')) {
                     if (pattern[i] != FRACTION || sizeof(explode(bits[j], "/")) > 1) {
                        failed = 0;
                        pos = j + 1;
                        break;
                     }
                  }
            } else if (last == FIND_FIRST) {
               for (j = pos; j < sizeof(bits); j++)
                  if ((bits[j][0] >= '0' && bits[j][0] <= '9') ||
                        (pattern[i] != FRACTION && bits[j][0] == '-' &&
                         bits[j][1] >= '0' && bits[j][1] <= '9')) {
                     if (pattern[i] != FRACTION || sizeof(explode(bits[j], "/")) > 1) {
                        failed = 0;
                        pos = j + 1;
                        break;
                     }
                  }
            } else {
               if (pos < sizeof(bits) &&
                     ((bits[pos][0] >= '0' && bits[pos][0] <= '9') ||
                        (pattern[i] != FRACTION && bits[pos][0] == '-' &&
                         bits[pos][1] >= '0' && bits[pos][1] <= '9'))) {
                  failed = 0;
                  pos++;
               } else {
                  failed = 1;
               }
            }
            if (!failed) {
               if (sizeof(delayed)) {
                  pos -= word_offset;
                  for (j=0;j<sizeof(delayed);j++) {
                     switch (delayed[j]) {
                        case STRING :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                        case OPTIONAL :
                           matches += ({ matches[<1] });
                           break;
                        case SINGLE_WORD :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                     }
                  }
                  delayed = ({ });
                  word_offset = 0;
               }
               last = FIND_NONE;
               matches += ({ pos - 1 });
            }
            break;
         case OPTIONAL_SPACES :
         case OPTIONAL :
         case WORD_LIST_SPACES :
            switch (pattern[i]) {
               case OPTIONAL_SPACES :
                  spaces = opt = 1;
                  break;
               case OPTIONAL:
                  opt = 1;
                  break;
               case WORD_LIST_SPACES :
                  spaces = 1;
                  break;
            }
         case WORD_LIST :
            if (pointerp(pattern[++i])) {
               string *words;
               if (spaces) {
                  tmp = "";
                  foreach (words in pattern[i])
                     tmp += implode(words, " ") + "|";
                  tmp = tmp[0..<2];
               }
               _curpat += (sizeof(pattern[i]) > 1?"{":"");
               _curpat += (spaces ? tmp : implode(pattern[i], "|")) +
                  (opt?"] ":(sizeof(pattern[i]) > 1?"} ":" "));
               elms = pattern[i];
            } else {
               _curpat += pattern[i] + (opt?"] ":"} ");
               elms = (string *)master()->query_word_list(pattern[i]);
               if (!elms) {
                  elms = query_word_list(pattern[i]);
               }
            }
            if (!pointerp(elms) || !sizeof(elms))
               failed = 1;
            else {
               if (!(last || failed || spaces)) {
                  tmp = member_array(bits[pos], elms);
                  if (tmp == -1) {
                     failed = 1;
                  }
               } else if (sizeof(elms) == 1 && last == FIND_FIRST && !spaces) {
                  tmp = member_array(elms[0], bits[pos..]);
                  if (tmp != -1) {
                     pos += tmp;
                  } else {
                     failed = 1;
                  }
               } else if (!spaces) {
                  tmp = bits[pos..] - elms;
                  if (sizeof(tmp) < sizeof(bits)-pos) {
                     if (last == FIND_FIRST) {
                        for (j = 0; (j+pos) < sizeof(bits) && j < sizeof(tmp) &&
                                  bits[j+pos] == tmp[j]; j++);
                        pos += j;
                     } else {
                        int k;
                        for (j = sizeof(tmp)-1, k = sizeof(bits)-1;
                               j >= 0 && bits[k] == tmp[j]; j--, k--);
                        pos = k;
                     }
                  } else {
                     failed = 1;
                  }
               } else {
                  string *elem;
                  int success;
                  foreach(elem in elms) {
                     if (!last) {
                        if (implode(bits[pos..pos+sizeof(elem)-1], " ") ==
                              implode(elem, " ")) {
                           success = 1;
                           wcount = sizeof(elem);
                           break;
                        }
                        failed = 1;
                     } else {
                        tmp = bits[pos..] - elem;
                        if (sizeof(tmp) <= (sizeof(bits) - pos - sizeof(elem))) {
                           success = 1;
                           wcount = sizeof(elem);
                           if (last == FIND_FIRST) {
                              for (j = 0; (j+pos) < sizeof(bits) && j < sizeof(tmp) &&
                                        bits[j+pos] == tmp[j]; j++);
                              pos += j;
                              break;
                           } else {
                              int k;
                              for (j = sizeof(tmp)-1, k = sizeof(bits)-1;
                                     j >= 0 && bits[k] == tmp[j]; j--, k--);
                              pos = k - wcount + 1;
                              break;
                           }
                        } else {
                           failed = 1;
                        }
                     }
                  }
                  if (success) {
                     failed = 0;
                  }
               }
            }
            if (opt && failed) {
               failed = 0;
               if (!last)
                  matches += ({ pos - 1 });
               else {
                  delayed += ({ OPTIONAL });
                  opt = 0;
                  spaces = 0;
                  break;
               }
            } else {
               if (!failed) {
                   pos += wcount;
               }
               if (sizeof(delayed) && !failed) {
                  pos -= word_offset;
                  for (j=0;j<sizeof(delayed);j++) {
                     switch (delayed[j]) {
                        case STRING :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                        case OPTIONAL :
                           matches += ({ matches[<1] });
                           break;
                        case SINGLE_WORD :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                     }
                  }
                  delayed = ({ });
                  word_offset = 0;
               }
               if (!failed) {
                  last = FIND_NONE;
                  matches += ({ pos - 1 });
               }
               wcount = 1;
               delayed = ({ });
            }
            opt = 0;
            spaces = 0;
            last = FIND_NONE;
            break;
      }
   }
   if (sizeof(delayed)) {
      if ( 1) {
         pos = sizeof(bits) + 1;
         pos -= word_offset;
         for (j=0;j<sizeof(delayed);j++) {
            switch (delayed[j]) {
               case OPTIONAL :
                  matches += ({ matches[<1] });
                  break;
               case SINGLE_WORD :
               case STRING :
                  matches += ({ pos - 1 });
                  pos++;
                  break;
            }
         }
         delayed = ({ });
         word_offset = 0;
         pos = sizeof(bits);
      } else
         pos = -1;
   }
   matches += ({ sizeof(bits) });
   if (failed || pos != sizeof(bits)) {
      return 0;
   }
   return matches + ({ sizeof(bits)+1 });
}
int check_living(object ob) {
   return living(ob);
}
int check_if_creator(object ob) {
   return (int)ob->query_creator() &&
      !(ob == this_player() || ob->query_invis());
}
int check_if_allowed(object ob) {
   return ob != this_player() && reference_allowed(ob);
}
class obj_match my_find_match(string pattern, object *where, int type) {
    object ob;
    class obj_match omatch;
    where = copy(where);
    foreach (ob in where) {
         if (ob && (!ob->query_closed() ||
                        (ob->query_closed() && !ob->query_property("opaque")))) {
             if (ob->query_mirror_room()) {
                  where += ({ ob->query_mirror_room() });
             }
         } else {
             where -= ({ ob });
         }
    }
    if (!sizeof(where)) {
         omatch = new(class obj_match);
         omatch->text = lower_case(pattern);
         omatch->objects = ({   });
         omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
         return omatch;
    }
    omatch = (class obj_match)match_objects_in_environments(pattern,
                                          where, type, this_object());
    if (omatch->result != OBJ_PARSER_SUCCESS) {
         ob = find_object(pattern);
         if (ob && member_array(environment(ob), where) != -1) {
             omatch->text = lower_case(pattern);
             omatch->objects = ({ ob });
             omatch->result = OBJ_PARSER_SUCCESS;
         }
    }
    return omatch;
}
private class obj_match match_objects(int type, string pattern, object *env) {
   class obj_match omatch;
   class obj_match new_omatch;
   object* tmp;
   switch (type) {
   case WIZ_PRESENT_TARGET :
      omatch = new(class obj_match);
      omatch->text = pattern;
      omatch->objects = WIZ_PRESENT->wiz_present(pattern, env[0]);
      if (sizeof(omatch->objects)) {
          omatch->result = OBJ_PARSER_SUCCESS;
      } else {
          omatch->result = OBJ_PARSER_NO_MATCH;
      }
      break;
   case ANY_OBJECT :
      omatch = my_find_match(pattern, env, 0);
      break;
   case DISTANT_LIVING :
      omatch = new(class obj_match);
      omatch->text = pattern;
      if ( environment() && !this_object()->query_creator() ) {
         if ( environment()->query_property( "no remote" ) ) {
            omatch->objects = ({ });
            omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
            break;
         }
      }
      omatch->objects = filter(map(explode(lower_case(pattern), ","),
                  (: find_living( lower_case(this_object()->
            expand_nickname( $1 ))) :) ), (: $1 && check_if_allowed($1) :) );
      omatch->objects = uniq_array(omatch->objects);
      if (sizeof(omatch->objects)) {
          omatch->result = OBJ_PARSER_SUCCESS;
      } else {
          omatch->result = OBJ_PARSER_NO_MATCH;
      }
      break;
   case LIVING :
      omatch = my_find_match(pattern, env, OBJ_PARSER_TYPE_LIVING);
      tmp = filter(omatch->objects, (: check_living( $1 ) :) );
      if (sizeof(omatch->objects) != sizeof(tmp)) {
          if (pattern != "all") {
               omatch->result = OBJ_PARSER_NOT_LIVING;
               omatch->objects -= tmp;
          } else {
               omatch->objects = tmp;
          }
      }
      break;
   case TARGET_PLAYER :
      omatch = new(class obj_match);
      omatch->text = pattern;
      if (environment() && !this_object()->query_creator()) {
         if (environment()->query_property("no remote")) {
            omatch->objects = ({ });
            omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
            break;
         }
      }
      omatch->objects = filter(map(explode(lower_case(pattern), ","),
                  (: find_player( lower_case(this_object()->
            expand_nickname( $1 ))) :) ), (: $1 && check_if_allowed($1) :) );
      omatch->objects = uniq_array(omatch->objects);
      if (!sizeof(omatch->objects)) {
         if (pattern == "creators" && this_object()->query_creator()) {
            omatch->objects = filter(users(), (: check_if_creator($1) :));
         }
      }
      if (sizeof(omatch->objects)) {
          omatch->result = OBJ_PARSER_SUCCESS;
      } else {
          omatch->result = OBJ_PARSER_NO_MATCH;
      }
      break;
   case ANY_LIVING :
      new_omatch = new(class obj_match);
      new_omatch->text = pattern;
      if ( environment() && !this_object()->query_creator() ) {
         if ( environment()->query_property( "no remote" ) ) {
            new_omatch->objects = ({ });
            new_omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
            omatch = new_omatch;
         }
      }
      if (new_omatch->result != OBJ_PARSER_BAD_ENVIRONMENT) {
         new_omatch->objects = filter(map(explode(lower_case(pattern), ","),
                                     (: find_player( lower_case(this_object()->
            expand_nickname( $1 ))) :) ), (: $1 && check_if_allowed($1) :) );
         new_omatch->objects = uniq_array(new_omatch->objects);
         if(sizeof(new_omatch->objects)) {
            new_omatch->result = OBJ_PARSER_SUCCESS;
            omatch = new_omatch;
         }
      }
      if(!omatch || omatch->result != OBJ_PARSER_SUCCESS ||
         !sizeof(omatch->objects)) {
         omatch = my_find_match(pattern, env, OBJ_PARSER_TYPE_LIVING);
         tmp = filter(omatch->objects, "check_living", this_object());
         if (sizeof(omatch->objects) != sizeof(tmp)) {
            if (pattern != "all") {
               omatch->result = OBJ_PARSER_NOT_LIVING;
               omatch->objects -= tmp;
            } else {
               omatch->objects = tmp;
            }
         }
      }
      if (omatch->result != OBJ_PARSER_SUCCESS) {
         new_omatch = new(class obj_match);
         new_omatch->text = pattern;
         if (pattern == "creators" && this_object()->query_creator()) {
            new_omatch->objects = filter(users(), (: check_if_creator($1) :));
         }
         if (pattern == "someone") {
            new_omatch->objects = filter(users(), (: check_if_allowed($1) :));
            if (sizeof(new_omatch->objects) > 1) {
               new_omatch->objects = ({ new_omatch->objects[random(sizeof(new_omatch->objects))]});
            }
         }
         if (sizeof(new_omatch->objects)) {
            new_omatch->result = OBJ_PARSER_SUCCESS;
            omatch = new_omatch;
         }
      }
      break;
   }
   if (!omatch) {
      omatch = new(class obj_match);
      omatch->text = pattern;
      omatch->objects = ({ });
      omatch->result = OBJ_PARSER_NO_MATCH;
      return omatch;
   }
   return omatch;
}
void setup_failed_mess(class obj_match failed_match) {
    switch (failed_match->result) {
    case OBJ_PARSER_BAD_ENVIRONMENT :
       _failed_mess[0] += "Cannot find \""+ failed_match->text +
                                    "\" here, access is not allowed.\n";
       break;
    case OBJ_PARSER_NOT_LIVING :
       _failed_mess[0] += "The objects \""+
                                    query_multiple_short(failed_match->objects) +
                                    "\" are not living.\n";
       break;
    case OBJ_PARSER_TOO_DARK :
       _failed_mess[0] += "Cannot find \""+ failed_match->text +
                                    "\", it is too dark.\n";
       break;
    default :
       _failed_mess[0] += match_objects_failed_mess(failed_match);
       break;
    }
}
private int handle_command(string *bits, int *matches, mixed *pattern,
                            mixed *command, string pattern_string) {
   int p;
   int failed;
   int i;
   int j;
   int k;
   string dir_match;
   string fail_mess_check;
   string *add_comm_bit;
   string fail_mesg;
   string succ_mesg;
   class obj_match direct_obs;
   object *env;
   object *fail_ob;
   class obj_match failed_match;
   mixed start;
   mixed indirect_obs;
   mixed ret;
   mixed *stuff;
   mixed indir_match;
   mixed bity;
   class obj_match omatch;
   string pattern_str;
   start = 1;
   add_comm_bit = ({ });
   indirect_obs = ({ });
   direct_obs = new(class obj_match);
   direct_obs->objects = ({ });
   if (!sizeof(matches)) {
      return 0;
   }
   for (i=1, p=1;i<sizeof(pattern) && !failed_match;i++,p++) {
      switch (pattern[i]) {
      case DIRECT_OBJECT :
         dir_match = implode(bits[start..matches[p]], " ");
         if (intp(pattern[i+2])) {
             switch (pattern[i+2]) {
                  case ENV_ME :
                     env = ({ this_object() });
                     break;
                  case ENV_HERE :
                     env = ({ environment() });
                     break;
                  case ENV_HERE_ME :
                     env = ({ environment(), this_object() });
                     break;
                  case ENV_ME_HERE :
                     env = ({ this_object(), environment() });
                     break;
             }
         } else if (stringp(pattern[i+2])) {
             ret = find_object(pattern[i+2]);
             if (!ret) {
                  pattern[i+2]->frog_me_a_lot();
                  ret = find_object(pattern[i+2]);
             }
             if (ret) {
                  env = ({ ret });
             }
         }
         direct_obs = match_objects(pattern[++i], dir_match, env);
         i++;
         add_comm_bit += ({ dir_match });
         start = matches[p];
         if (direct_obs->result != OBJ_PARSER_SUCCESS) {
            failed_match = direct_obs;
         }
         break;
      case INDIRECT_OBJECT :
         pattern_str = implode(bits[start..matches[p]], " ");
         if (intp(pattern[i+2])) {
             switch (pattern[i+2]) {
             case ENV_ME :
                env = ({ this_object() });
                break;
             case ENV_HERE :
                env = ({ environment() });
                break;
             case ENV_HERE_ME :
                env = ({ environment(), this_object() });
                break;
             case ENV_ME_HERE :
                env = ({ this_object(), environment() });
                break;
             }
         } else if (stringp(pattern[i+2])) {
             ret = find_object(pattern[i+2]);
             if (!ret) {
                  pattern[i+2]->frog_me_a_lot();
                  ret = find_object(pattern[i+2]);
             }
             if (ret) {
                  env = ({ ret });
             }
         }
         if (pattern[i+2] == ENV_DIRECT_OBS) {
            omatch = new(class obj_match);
            omatch->text = pattern_str;
            omatch->objects = ({ ENV_DIRECT_OBS });
            omatch->result = OBJ_PARSER_SUCCESS;
            i++;
         } else {
            omatch = match_objects(pattern[++i], pattern_str, env);
         }
         i++;
         add_comm_bit += ({ pattern_str });
         if (omatch->result != OBJ_PARSER_SUCCESS) {
            failed_match = omatch;
         } else {
            if (stringp(indir_match)) {
                if (pointerp(indir_match)) {
                     indirect_obs += ({ omatch->objects });
                     indir_match += ({ pattern_str });
                } else {
                     indirect_obs = ({ indirect_obs, omatch->objects });
                     indir_match = ({ indir_match, pattern_str });
                }
            } else {
                indirect_obs = omatch->objects;
                indir_match = pattern_str;
            }
         }
         start = matches[p];
         break;
      case SINGLE_WORD :
      case STRING :
      case SHORT_STRING :
         add_comm_bit += ({ implode(bits[start..matches[p]], " ") });
         break;
      case QUOTED_STRING :
         pattern_str = implode(bits[start..matches[p]], " ");
         add_comm_bit += ({ pattern_str[1..<2] });
         break;
      case NUMBER :
         sscanf(implode(bits[start..matches[p]], " "), "%d", j);
         add_comm_bit += ({ j });
         break;
      case FRACTION :
         sscanf(implode(bits[start..matches[p]], " "), "%d/%s", j, k);
         add_comm_bit += ({ j, k });
         break;
      case OPTIONAL_SPACES :
      case OPTIONAL :
         i++;
         break;
      case WORD_LIST_SPACES :
      case WORD_LIST :
         if (pointerp(pattern[++i]))
            if (sizeof(pattern[i]) > 1)
               add_comm_bit += ({ implode(bits[start..matches[p]], " ") });
         break;
      }
      start = matches[p]+1;
   }
   if (failed_match) {
      if (query_notify_fail()) {
         _failed_mess[1] += query_notify_fail();
         notify_fail(0);
      } else {
         setup_failed_mess(failed_match);
      }
      return (matches[0]?-1:0);
   }
   _fail_mess = ([ ]);
   _succ_mess = ([ ]);
   _succ_mess_dir = ({ });
   _succ_mess_indir = ({ });
   ret = 0;
   if (!sizeof(direct_obs->objects) &&
         (indirect_obs == ENV_DIRECT_OBS ||
          sizeof(indirect_obs & ({ ENV_DIRECT_OBS }) ) ) ) {
      direct_obs->objects = ({ });
      for (i = 0; i < sizeof(command); i += 2) {
          direct_obs->objects += ({ command[i] });
      }
   }
   if (!sizeof(direct_obs->objects)) {
      indirect_obs -= ({ ENV_DIRECT_OBS });
      for (i = 0; i < sizeof(command) && !ret;i += 2) {
         if (!add_comm_bit) {
            add_comm_bit = ({ });
            start = 1;
            for (j = 0; j < sizeof(matches); j++) {
               add_comm_bit += implode(bits[start..matches[j]], " ");
               start = matches[j]+1;
            }
         }
         if (functionp(command[i+1])) {
            if ( functionp( command[ i + 1 ] ) & FP_OWNER_DESTED ) {
               start = command[i];
               if (!start) {
                  remove_object_force(start);
                  if (start == command[i]) {
                     remove_from_command(bits[0], start);
                  }
                  ret = 0;
                  continue;
               }
            }
            ret = evaluate(command[i+1], indirect_obs, dir_match, indir_match,
                                  add_comm_bit, pattern_string, bits[0]);
         } else {
            start = command[i];
            if (!start) {
               remove_object_force(start);
               if (start == command[i]) {
                  remove_from_command(bits[0], start);
               }
               ret = 0;
               continue;
            }
            do {
               if (function_exists("do_"+bits[0], start)) {
                  ret = call_other(start, "do_"+bits[0], indirect_obs,
                                             dir_match, indir_match, add_comm_bit,
                                             pattern_string);
                  break;
               } else {
                  start = shadow(start, 0);
               }
            } while (start);
            if (!start) {
                ret = call_other(command[i], "command_control", bits[0],
                                          indirect_obs,
                                          dir_match, indir_match, add_comm_bit,
                                          pattern_string);
            }
         }
      }
      if (!ret || ret == -1) {
         if (query_notify_fail()) {
            _failed_mess[1] += query_notify_fail();
            notify_fail(0);
         } else {
            fail_mess_check = get_fail_messages( bits[ 0 ], ({ }) );
            if (_failed_mess[1] == "") {
                _failed_mess[1] += fail_mess_check;
            }
         }
      }
      if (_succ_mess_dir) {
          print_special_messages( bits[ 0 ] );
      }
      _fail_mess = ([ ]);
      return ret;
   }
   fail_ob = ({ });
   bity = ({ });
   failed = 0;
   for (i=0;i<sizeof(direct_obs->objects);i++) {
      j = member_array(direct_obs->objects[i], command);
      if (j == -1) {
         fail_ob += ({ direct_obs->objects[i] });
         continue;
      }
      if (!direct_obs->objects[i]->short()) {
         continue;
      }
      if (member_array(ENV_DIRECT_OBS, indirect_obs) != -1) {
         failed_match = my_find_match(indir_match, ({ direct_obs->objects[i] }), 0);
         if (failed_match->result == OBJ_PARSER_SUCCESS) {
             stuff = failed_match->objects;
         } else {
             stuff = ({ });
         }
         debug_printf("Direct Obs Env (%O %O %O)\n", indir_match, stuff, direct_obs->objects[i]);
      } else if (pointerp(indir_match)) {
         failed_match = 0;
         stuff = copy(indirect_obs);
         for (k = 0; k < sizeof(indirect_obs); k++) {
            if (intp(stuff[k]) || ( arrayp(stuff[k]) && sizeof( stuff[k] ) &&
                intp(stuff[k][0]) ) ) {
               failed_match = my_find_match(indir_match[k], ({ direct_obs->objects[i] }), 0);
               if (failed_match->result == OBJ_PARSER_SUCCESS) {
                  stuff[k] = failed_match->objects;
               } else {
                  break;
               }
            }
         }
      } else {
         stuff = indirect_obs;
         failed_match = 0;
      }
      if (failed_match && failed_match->result != OBJ_PARSER_SUCCESS) {
         setup_failed_mess(failed_match);
         failed = 1;
         continue;
      }
      if (functionp(command[j+1])) {
         if (functionp(command[j+1]) & FP_OWNER_DESTED) {
            start = direct_obs->objects[i];
            if (!start) {
                remove_object_force(start);
                if (start == command[i]) {
                   remove_from_command(bits[0], start);
                }
                ret = 0;
                continue;
            } else {
                if (start == command[i]) {
                    remove_from_command(bits[0], start);
                }
                ret = 0;
                continue;
            }
         }
         ret = evaluate(command[j+1], stuff, dir_match, indir_match,
                        add_comm_bit, pattern_string, bits[0]);
      } else {
         start = direct_obs->objects[i];
         if (!start) {
             remove_object_force(start);
             if (start == command[i]) {
                remove_from_command(bits[0], start);
             }
             ret = 0;
             continue;
         }
         do {
            if (function_exists("do_"+bits[0], start)) {
                ret = call_other(start, "do_"+bits[0], stuff,
                                          dir_match, indir_match, add_comm_bit,
                                          pattern_string);
                break;
            } else {
                start = shadow(start, 0);
            }
         } while (start);
         if (!start) {
             ret = call_other(direct_obs->objects[i], "command_control", bits[0], stuff,
                                       dir_match, indir_match, add_comm_bit,
                                       pattern_string);
         }
      }
      if (stringp(ret) || pointerp(ret)) {
         bity += ({ ret });
      } else if (ret && ret != -1) {
         bity += ({ direct_obs->objects[i]});
      } else {
         fail_ob += ({ direct_obs->objects[i] });
         if (ret == -1) {
            failed = 1;
         }
      }
   }
   if (!sizeof(bity)) {
      fail_mess_check = get_fail_messages( bits[ 0 ], fail_ob );
      if (query_notify_fail()) {
         _failed_mess[1] += query_notify_fail();
         notify_fail(0);
      } else if (_failed_mess[1] == "") {
         _failed_mess[1] += fail_mess_check;
         if (_failed_mess[1] == "" && sizeof(fail_ob)) {
            notify_fail(0);
            fail_mesg = create_message(bits, matches, pattern, fail_ob, 1);
            if (!pointerp(indirect_obs)) {
               _failed_mess[1] += "You cannot " + bits[ 0 ] +
                   replace_string( fail_mesg, "$succ_indir$",
                                          ( pointerp( indir_match ) ?
                                             query_multiple_short( indir_match ) :
                                             indir_match) );
            } else {
               if (pointerp(indir_match)) {
                   bity = explode("F" + fail_mesg, "$succ_indir$");
                   _failed_mess[1] += "You cannot "+ bits[ 0 ];
                   bity[0] = bity[0][1..];
                   for (i = 0; i < sizeof(bity) - 1; i++) {
                        if (i >= sizeof(indir_match)) {
                            if (stuff && pointerp(stuff[<1])) {
                                 _failed_mess[1] += bity[i] +
                                                             query_multiple_short( stuff[<1] );
                            } else {
                                 _failed_mess[1] += bity[i] +
                                                             query_multiple_short( indir_match[<1] );
                            }
                        } else {
                            if (stuff && pointerp(stuff[i])) {
                                 _failed_mess[1] += bity[i] +
                                                             query_multiple_short( stuff[i] );
                            } else {
                                 _failed_mess[1] += bity[i] + indir_match[i];
                            }
                        }
                   }
                   _failed_mess[1] += bity[<1];
               } else {
                  if ( member_array( ENV_DIRECT_OBS, indirect_obs ) == -1 ) {
                     stuff = indirect_obs;
                  }
                  if ( member_array( this_player(), stuff ) == -1 ) {
                     _failed_mess[1] += "You cannot "+ bits[ 0 ] +
                           replace_string( fail_mesg, "$succ_indir$",
                                                query_multiple_short( stuff, "a" ) );
                  } else {
                     _failed_mess[1] += "You cannot "+ bits[ 0 ] +
                        replace_string( fail_mesg, "$succ_indir$",
                                                query_multiple_short( stuff -
                                                                                 ({this_player()}) +
                                                                                 ({ "yourself" }),
                                                                                 "a" ) );
                  }
               }
            }
         }
      }
      _fail_mess = ([ ]);
      if (!failed) {
          return 0;
      }
      return -1;
   }
   if (sizeof(bity) != sizeof(_succ_mess_dir)) {
      succ_mesg = create_message( bits, matches, pattern, bity - _succ_mess_dir);
      if ( member_array( this_player(), _succ_indir ) == -1 ) {
         write( "You "+ bits[ 0 ] + replace( succ_mesg, "$succ_indir$",
                                                               query_multiple_short( _succ_indir,
                                                                                                "one" ) ) );
         stuff = _succ_indir;
      } else {
         write("You "+ bits[0] + replace(succ_mesg, "$succ_indir$",
                                                         query_multiple_short(_succ_indir -
                                                                                        ({ this_player() })
                                                                                        + ({ "yourself" }),
                                                                                        "one") ) );
         stuff = _succ_indir - ({ this_player() });
         stuff = ({ (string)this_player()->query_objective() +"self" }) + stuff;
      }
      say( capitalize( (string)this_player()->the_short() ) +" "+
             pluralize(bits[0]) + replace(succ_mesg, "$succ_indir$",
                                                         query_multiple_short(stuff, "one")),
             _succ_indir );
      for ( i = 0; i < sizeof( _succ_indir ); i++ ) {
         if ( _succ_indir[ i ] != this_player() ) {
            tell_object( _succ_indir[ i ],
                               capitalize( (string)this_player()->the_short() ) +" "+
                               pluralize(bits[0]) + replace(succ_mesg, "$succ_indir$",
                                                                           query_multiple_short(stuff -
                                                                              ({ _succ_indir[i] }) +
                                                                              ({ "you" }), "one" ) ) );
         }
      }
      if (sizeof(_succ_mess_dir)) {
          print_special_messages( bits[ 0 ] );
      }
   } else {
      print_special_messages( bits[ 0 ] );
   }
   _succ_indir = ({ });
   _succ_mess = ([ ]);
   _succ_mess_dir = ({ });
   _succ_mess_dir = ({ });
   return 1;
}
void print_special_messages( string verb ) {
    int i, j;
    string words, *messes;
    string type;
    mixed *stuff, *tmp;
    messes = keys( _succ_mess );
    for ( i = 0; i < sizeof( messes ); i++ ) {
         if ( functionp( messes[i] ) ||
                (messes[i][0..1] == MY_MESS_HEADER &&
                  strlen(messes[i]) > 2)) {
            if (functionp(messes[i])) {
                words = evaluate(messes[i], 0);
            } else {
                words = messes[i][2..];
            }
            type = "one";
            if (strsrch("$Iposs$", words) != -1) {
                type = "poss";
                words = replace_string(words, "$Iposs$", "");
            }
            if (strsrch("$Ithe$", words) != -1) {
                type = "the";
                words = replace_string(words, "$Ithe$", "");
            }
            if (strsrch("$Ia$", words) != -1) {
                type = "a";
                words = replace_string(words, "$Ia$", "");
            }
            if ( member_array( this_player(), _succ_mess[ messes[ i ] ][ 1 ] ) ==
                     -1 ) {
                words = capitalize( replace( words, ({ "$C$", "$CATFROG",
                         "$N", "you", "$p ", "your ",
                         "$r", "you", "$o", "you", "$V", verb, "$es", "",
                         "$s", "", "$y", "y",
                         "$I", query_multiple_short( _succ_mess[ messes[ i ] ][ 1 ],
                                                          type ) }) ) );
            } else {
                words = capitalize( replace( words, ({ "$C$", "$CATFROG",
                         "$N", "you", "$p ", "your ",
                         "$r", "you", "$o", "you", "$V", verb, "$es", "", "$s", "",
                         "$y", "y",
                         "$I", query_multiple_short( (mixed *)_succ_mess[ messes[ i ] ][ 1 ] -
                         ({ this_player() }) + ({ "yourself" }), type ) }) ) );
            }
            write( replace( words, ({ "$D",
                                    query_multiple_short( _succ_mess[ messes[ i ] ][ 0 ],
                                                                     "one" ),
                                    "$CATFROG", "$C$" }) ) );
         } else if (messes[i][0..1] == OTHER_MESS_HEADER &&
                         strlen(messes[i]) > 2) {
            if (functionp(messes[i])) {
               words = replace( evaluate(messes[i], 1),
                   ({ "$C$", "$CATFROG",
                        "$N", (string)this_player()->the_short(),
                        "$p ", (string)this_player()->query_possessive() +" ",
                        "$r", (string)this_player()->query_pronoun(),
                        "$o", (string)this_player()->query_objective(),
                        "$V", pluralize( verb ), "$es", "es", "$s", "s", "$y", "ies" }) );
            } else {
               words = replace( messes[i][2..],
                   ({ "$C$", "$CATFROG",
                        "$N", (string)this_player()->the_short(),
                        "$p ", (string)this_player()->query_possessive() +" ",
                        "$r", (string)this_player()->query_pronoun(),
                        "$o", (string)this_player()->query_objective(),
                        "$V", pluralize( verb ), "$es", "es", "$s", "s", "$y", "ies" }) );
            }
            words = replace( words, "$D",
                     query_multiple_short( _succ_mess[ messes[ i ] ][ 0 ], "one" ) );
            if (member_array(this_player(), _succ_mess[ messes[i] ][ 1 ]) == -1) {
               stuff = _succ_mess[messes[i]][1];
            } else {
                stuff = ({ (string)this_player()->query_objective() +"self" });
                stuff += (mixed *)_succ_mess[ messes[ i ] ][ 1 ] - ({ this_player() });
            }
            type = "one";
            if (strsrch("$Iposs$", words) != -1) {
                type = "poss";
                words = replace_string(words, "$Iposs$", "");
            }
            if (strsrch("$Ithe$", words) != -1) {
                type = "the";
                words = replace_string(words, "$Ithe$", "");
            }
            if (strsrch("$Ia$", words) != -1) {
                type = "a";
                words = replace_string(words, "$Ia$", "");
            }
            say( capitalize( replace( words, ({ "$I", query_multiple_short( stuff,
                                                                                                       type),
                                                   "$CATFROG", "$C$" }) ) ),
                     _succ_mess[ messes[ i ] ][ 1 ] );
            for ( j = 0; j < sizeof( _succ_mess[ messes[ i ] ][ 1 ] ); j++ ) {
                if ( _succ_mess[ messes[ i ] ][ 1 ][ j ] != this_player() ) {
                     if (strsrch(words, "$I's") != -1) {
                         tmp = stuff - _succ_mess[ messes[ i ] ][ 1 ][ j..j ];
                         tell_object( _succ_mess[ messes[ i ] ][ 1 ][ j ],
                               capitalize( replace( words, ({ "$I's",
                                                 query_multiple_short( tmp + ({ "your" }) ),
                                                 "$I", query_multiple_short( tmp + ({ "you" }),
                                                                                           "one"),
                                                 "$CATFROG", "$C$" }) ) ) );
                     } else {
                         tell_object( _succ_mess[ messes[ i ] ][ 1 ][ j ],
                               capitalize( replace( words, ({ "$I",
                                                               query_multiple_short( stuff -
                               ({ _succ_mess[ messes[ i ] ][ 1 ][ j ] }) + ({ "you" }),
                               "one"), "$CATFROG", "$C$" }) ) ) );
                     }
                }
            }
       }
   }
}
string get_fail_messages( string verb, object *fail_obs ) {
    string whole;
    string words;
    string mess;
    string *str;
    object ob;
    class fail_mess_data data;
    whole = "";
    foreach (mess, data in _fail_mess) {
         if ( !stringp( mess ) ) {
             continue;
         }
         str = ({ });
         foreach(ob in data->direct)
            str += ({ "one_short:" + sprintf("%O", ob) });
         words = this_player()->evaluate_message( ({ mess, ({ str }) }) );
         words = replace( words,
                                  ({ "$D", query_multiple_short( data->direct, "one" ),
                                       "$V", verb }) );
         if ( member_array( this_player(), data->indirect) == -1 )
             words = replace( words, "$I",
                      query_multiple_short( data->indirect, "one" ) );
         else
             words = replace( words, "$I",
                      query_multiple_short( data->indirect -
                      ({ this_player() }) + ({ "yourself" }), "one" ) );
         whole += capitalize( words );
    }
    return whole;
}
string *query_word_list(string list) {
   return 0;
}
varargs string create_message(string *bits, int *matches, mixed *pattern,
                                             object *dir, int flag) {
   string ret;
   int i, pos;
   ret = " ";
   if (matches[0])
      matches[0] = 0;
   for (i=1;i<sizeof(pattern);i++, pos++) {
      switch (pattern[i]) {
      case DIRECT_OBJECT :
         if (member_array(this_player(), dir) != -1)
            ret += query_multiple_short(dir - ({ this_player() }) +
                                                      ({ "yourself" }), (flag?"a":"one"));
         else
            ret += query_multiple_short(dir, (flag?"a":"one"));
         i += 2;
         break;
      case INDIRECT_OBJECT :
         ret += "$succ_indir$";
         i += 2;
         break;
      case SHORT_STRING :
      case STRING :
         ret += implode(bits[matches[pos]+1..matches[pos+1]], " ");
         break;
      case WORD_LIST_SPACES :
         pos += matches[pos+1]-1;
      case WORD_LIST :
         ret += implode(bits[matches[pos]+1..matches[pos+1]], " ");
         i++;
         break;
      case NUMBER :
      case FRACTION :
      case SINGLE_WORD :
         ret += bits[matches[pos]+1];
         break;
      case OPTIONAL_SPACES :
         if (!matches[pos] == matches[pos+1])
            pos += matches[pos+1]-1;
      case OPTIONAL :
         if (matches[pos] == matches[pos+1]) {
            if (pointerp(pattern[i+1][0]))
               ret += implode(pattern[i+1][0], " ");
            else
               ret += pattern[i+1][0];
         } else {
            ret += implode(bits[matches[pos]+1..matches[pos+1]], " ");
         }
         i++;
         break;
      }
      if (i+1 < sizeof(pattern))
         ret += " ";
   }
   return ret+".\n";
}

==================================================
FILE: newbie_junk.c
==================================================

#include <armoury.h>
#include <config.h>
#ifndef  __DISTRIBUTION_LIB__
#include <priest.h>
#endif
#define CABBAGE "/obj/monster/cabbage"
#define LEMON "/obj/monster/muffled_lemon"
#define STICK "/obj/misc/boring_stick"
#define CAT "/obj/monster/present_cat"
#define BUG "/obj/misc/bug"
#define BINKY_PATH "/obj/misc/binky/"
#define BINKY_TOY (BINKY_PATH "my_binky")
#define BINKY_BRUSH (BINKY_PATH "binky_brush")
#define BINKY_COMB (BINKY_PATH "binky_comb")
#define BINKY_KEY (BINKY_PATH "binky_key")
void start_player(object pl) {
  object ob, bucket, bottle, drink, label;
  seteuid(getuid());
  bucket = ARMOURY->request_item( "bucket small", 100 );
  bucket->set_short( "champagne bucket" );
  bucket->set_long( "This metal bucket was designed for a purpose, "
    "and looks like it would fit a champagne bottle perfectly.\n" );
  bucket->add_adjective( "champagne", "wine" );
  bucket->add_alias( "cooler" );
  bucket->add_read_mess( this_player()->query_cap_name(),
    "etched characters", "general" );
  bucket->move(this_player());
  bottle = clone_object( "/obj/bottle" );
  bottle->set_max_volume( 750 );
  bottle->set_name( "bottle" );
  bottle->set_short( "champagne bottle" );
  bottle->set_main_plural( "champagne bottles" );
  bottle->add_adjective( "champagne" );
  bottle->add_alias( "champagne" );
  bottle->set_long( "An expensive-looking bottle of champagne, just right "
               "to celebrate being on " + mud_name() + ".\n" );
  bottle->set_weight( 5 );
  bottle->set_max_weight( 20 );
  bottle->set_full_weight( 25 );
  bottle->set_volume( 750 );
  bottle->set_value( 400 );
  bottle->set_leak_rate( 0 );
  drink = clone_object("/obj/reagents/generic_liquid.ob");
  drink->set_name("champagne");
  drink->set_short("fine champagne");
  drink->set_long("This is a fine champagne, $amount_size$.\n");
  drink->set_medium_alias("Champagne");
  drink->add_eat_effect("/std/effects/ingested/drunk", 500);
  drink->set_amount(750);
  drink->move(bottle);
  label = clone_object("/obj/misc/label");
  label->add_read_mess( "\n    _________________  \n"
                          "   |                 | \n"
                          "   |                 | \n"
                          "   | Vintage Century | \n"
                          "   |      of the     | \n"
                          "   |    Fruit Bat,   | \n"
                          "   |   Year of the   | \n"
                          "   |  Midnight Frog  | \n"
                          "   |                 | \n"
                          "   |_________________| \n",
                     "cursive lettering on the bottle's label", "general" );
  bottle->add_effect("/std/effects/object/label", label);
  bottle->move( bucket );
  ob = clone_object("/obj/armour");
  ob->set_name("sash");
  ob->set_long("A large colourful sash.\n");
  ob->add_read_mess( "Welcome to " + mud_name() + ", "+
                     capitalize( (string)(pl->query_name()) ) +".", 0,
                     "general");
  ob->set_type( "sash" );
  ob->set_weight(3);
  ob->set_adjective(({ "large", "colourful" }));
  ob->setup_armour(1000);
  ob->set_damage_chance(10);
  if (ob->move(pl)) {
    if (ob->move(environment(pl)))
      ob->dest_me();
  }
  pl->wear_armour( ob );
  ob = ARMOURY->request_item( "torch" );
  ob->add_read_mess( "\n" + mud_name() + " MUD, it brightens up your night!  "
                     "More torches can be purchased from the general stores "
                     "found across the Disc!", "to the wood",
                     "general" );
  ob->move( pl );
  ob = clone_object( "/d/liaison/NEWBIE/newbie_book" );
  ob->move( pl );
  pl->adjust_money( 8, "Pumpkin dollar" );
  pl->adjust_money( 100, "Pumpkin pence" );
}
void give_junk(object pl) {
  call_out("start_player", 2, pl);
}
void logged_on_times(int num) {
  object ob;
  int bing;
  this_player()->remove_property("binky level");
  switch (num) {
  case 3 :
    ob = clone_object(CABBAGE);
    if(!environment(this_player()))
      return;
    ob->move(environment(this_player()));
    ob->set_owner(this_player());
    ob->init_command("follow "+this_player()->query_name());
    tell_object(this_player(),
                "%^YELLOW%^Congratulations on logging onto " + mud_name() + " for the "
                "third time.  Please accept this cabbage as a token of our "
                "appreciation.%^RESET%^\n");
    break;
  case 10 :
    ob = clone_object("/obj/clothing");
    ob->set_name("badge");
    ob->set_type("badge");
    ob->set_short("fruitbat flavoured badge");
    ob->add_adjective(({ "fruitbat", "flavoured" }));
    ob->set_weight(1);
    ob->set_damage_chance(5);
    ob->setup_clothing(10000);
    ob->set_long("The badge is brightly fruitbat flavoured with a bit of "
                 "banana around the edges.  You are very proud to own it.\n");
    ob->add_read_mess("Congratulations on being a 10 time loginer to "
                      "" + mud_name() + " MUD!\n", 0,
                      this_player()->query_default_language());
    if (ob->move(this_player()))
      ob->move(environment(this_player()));
    tell_object(this_player(),
                "%^CYAN%^A little fruitbat flies down out of a small "
                "non-existent black hole and gives you a badge.  The "
                "fruitbat chirps excitedly at you in fruitbat and then "
                "leaps into your badge.%^RESET%^\n");
    break;
  case 42 :
    ob = clone_object("/obj/misc/paper");
    ob->add_read_mess("What do you get when you multiply 6 by nine.", 0,
                      this_player()->query_default_language());
    if (ob->move(this_player()))
      ob->move(environment(this_player()));
    tell_object(this_player(),
                "%^YELLOW%^This is your 42nd login.  You suddenly discover "
                "a piece of paper in your hand, something froths up in your "
                "mind and you just have to write it on the paper.\nAfterwards "
                "you stare blankly down at the paper not remembering what "
                "you just wrote.%^RESET%^\n");
    break;
  case 100 :
    ob = clone_object(LEMON);
    ob->set_owner(this_player());
    tell_object(this_player(),
                "%^YELLOW%^Congratulations!  You have now logged onto "
                "" + mud_name() + " 100 times.  You are now officially addicted.  "
                "This lemon will help you on your travels.%^RESET%^\n");
    break;
  case 150 :
    ob = clone_object(STICK);
    if (ob->move(this_player()))
      ob->move(environment(this_player()));
    tell_object(this_player(),
                "%^YELLOW%^This is your 150th login!  Everybody here "
                "wishes you a good time, to help you in designs we have "
                "provided this stick for you.%^RESET%^\n");
    break;
  case 200 :
    ob = clone_object(CAT);
    ob->set_owner(this_player());
    tell_object(this_player(),
                "A cat slinks in from somewhere and rubs itself up "
                "against your leg.\n");
    ob->move(environment(this_player()));
    break;
  case 512 :
    ob = clone_object(BUG);
    tell_object(this_player(),
                "A strange black noise starts to slowly grow louder and "
                "louder.  Suddenly in a bunch of silvery wiggling a black "
                "bug crawls into your inventory.\n");
    ob->move(this_player());
    break;
  case 990 :
    ob = clone_object(BINKY_KEY);
    ob->move(this_player());
    tell_object(this_player(),
                "You hear a tinkling noise in the distance which slowly "
                "grows closer.  Something sparkly and shiny drops out of "
                "the sky into your hands.  It appears to be some sort of "
                "key.\n");
    break;
  case 1000 :
    ob = clone_object(BINKY_TOY);
    ob->move(environment(this_player()));
    tell_object(this_player(),
                "You feel a chill in your bones and turn around to see "
                "a large imposing figure wearing a black coat.  He smiles "
                "down at you in a way that makes your hair stand on end "
                "and places a small horse on the ground in front of "
                "you.\nDeath says: TREAT HIM WELL AND COMB HIM OFTEN.\n");
    break;
  case 1010 :
    ob = clone_object(BINKY_COMB);
    ob->move(this_player());
    tell_object(this_player(),
                "Something black and unseen taps you on the shoulder.\n"
                "Death says: I FORGOT THIS.\n"
                "Death gives you a small ivory comb.\n");
    break;
  case 1020 :
    ob = clone_object(BINKY_BRUSH);
    ob->move(this_player());
    tell_object(this_player(),
                "You feel a brush in your hands, you wonder where this "
                "came from?\n");
    break;
  }
  bing = -this_player()->query_time_on();
  if (bing / (24 * 60 * 60) > 100) {
    this_player()->add_player_title("old man");
    this_player()->add_player_title("old woman");
  }
}

==================================================
FILE: nickname.c
==================================================

mapping map_nicknames;
void nickname_commands() {
}
mapping query_nicknames() { return map_nicknames; }
void set_nicknames(mapping map) { map_nicknames = map; }
string expand_nickname( string phrase ) {
   int i;
   string new_n, *words;
   if ( stringp( phrase ) )
      words = explode( phrase, " " );
   else
      return phrase;
   if ( !map_nicknames )
      map_nicknames = ([ ]);
   for ( i = 0; i < sizeof( words ); i++ ) {
      new_n = map_nicknames[ lower_case( words[ i ] ) ];
      if ( new_n )
         words[ i ] = new_n;
   }
   return implode( words, " " );
}

==================================================
FILE: options_control.c
==================================================

#define PLAYER_OPTIONS_CLASS
#include <player.h>
mixed query_property(string);
varargs void add_property(string,mixed,int);
private class player_options_control query_player_options() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return new(class player_options_control);
   }
   if (sizeof(options) == 4) {
      class player_options_control newbit;
      newbit = new(class player_options_control);
      newbit->follow_everyone = options->follow_everyone;
      newbit->follow_groups = options->follow_groups;
      newbit->follow_friends = options->follow_friends;
      newbit->lead_behind = options->lead_behind;
      options = newbit;
   }
   return options;
}
int query_auto_follow_group() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->follow_groups;
}
int query_auto_follow_friends() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->follow_friends;
}
int query_auto_follow_everyone() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->follow_everyone;
}
int query_lead_from_behind() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->lead_behind;
}
void set_auto_follow_group(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->follow_groups = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_auto_follow_friends(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->follow_friends = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_auto_follow_everyone(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->follow_everyone = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_lead_from_behind(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->lead_behind = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_mxp_disable(int flag) {
   class player_options_control options;
   options = query_player_options();
   options->mxp_disable = 1;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
int query_mxp_disable() {
   class player_options_control options;
   options = query_player_options();
   return options->mxp_disable;
}
int is_mxp_enabled() {
#if efun_defined(has_mxp)
   if (has_mxp(this_object())) {
      return !query_mxp_disable();
   }
#endif
   return 0;
}

==================================================
FILE: parser.c
==================================================

#include <creator.h>
#include <parser.h>
#define LMASTER "/d/liaison/master"
int pos, force_string;
mixed func;
protected void create() {
  seteuid("Root");
}
mixed *parse_args(string str, string close) {
  mixed *args, *m, *m2;
  object *obs;
  string s1, s2, s3, s4, s5, s6, s7;
  int i;
  mapping map;
  args = ({ });
  while (strlen(str)) {
    while (strlen(str) && str[0] == ' ') str = str[1..<1];
    if (!strlen(str) || str[0..0] == close) return ({ args, str[1..<1] });
    switch (str[0]) {
      case '\'' :
        if (sscanf(str, "'%s'%s", s1, s2) != 2) {
          printf("Unterminated string.\n");
          return 0;
        }
        args += ({ replace_string(s1, "\\n", "\n") });
        str = s2;
        break;
      case '`' :
        if (sscanf(str, "`%s`%s", s1, s2) != 2) {
          printf("Unterminated string.\n");
          return 0;
        }
        args += ({ replace_string(s1, "\\n", "\n") });
        str = s2;
        break;
      case '"' :
        if (sscanf(str, "\"%s\"%s", s1, s2) != 2) {
          printf("Unterminated string.\n");
          return 0;
        }
        args += ({ replace_string(s1, "\\n", "\n") });
        str = s2;
        break;
      case '{' :
        m = parse_args(str[1..<1], "}");
        if (!m) {
          return 0;
        }
        args += ({ m[0] });
        str = m[1];
        break;
      case '[' :
       if (sscanf(str[1..<1], "%s]%s", s1, s2) != 2) {
          printf("Unmatched [.\n");
          return 0;
        }
        str = str[1..<1];
        map = ([ ]);
        while (1) {
          m = parse_args(str, ":");
          if (!m) {
            while (strlen(str) && str[0] == ' ') {
               str = str[1..<1];
            }
            if (str[0] == ']') {
              break;
            }
          }
          if (!(m2 = parse_args(str, ","))) {
            if (!(m2 = parse_args(str, "]"))) {
              return 0;
            }
            if (sizeof(m[0])) {
              map[m[0][0]] = (sizeof(m2[0])?m2[0][0]:0);
            }
            break;
          }
          if (sizeof(m[0])) {
            map[m[0][0]] = (sizeof(m2[0])?m2[0][0]:0);
          }
        }
        args += ({ map });
        break;
      case '|' :
        if (sscanf(str, "|%s|%s", s1, s2) != 2) {
          printf("Unmatched |\n");
          return 0;
        }
        obs = WIZ_PRESENT->wiz_present(str, this_player());
        if (!sizeof(obs)) {
          args += ({ this_player() });
        } else if (sizeof(obs) == 1) {
          args += ({ obs[0] });
        } else {
          args += ({ obs });
        }
        str = s2;
        break;
      case '0'..'9' :
      case '-' :
        if (sscanf(str, "%d%s", i, str) != 2) {
          printf("Number expected.\n");
          return 0;
        }
        args += ({ i });
        break;
      default :
        s2 = s3 = 0;
        sscanf(str, "%s,%s", s4, s2);
        sscanf(str, "%s"+close+"%s", s5, s3);
        if (sscanf(str, "%s->%s", s6, s7) == 2 &&
            (!s3 || strlen(s5) > strlen(s6)) &&
            (!s2 || strlen(s4) > strlen(s6))) {
          while (s7[0] == ' ') s7 = s7[1..<1];
          if (sscanf(s7, "%s(%s", s1, s7) != 2) {
            printf("'(' expected.\nLine left unprocessed %s\n", s7);
            return 0;
          }
          obs = WIZ_PRESENT->wiz_present(s6, this_player());
          if (!sizeof(obs)) {
            printf("The object %s needs to exist.\n", s6);
            return 0;
          }
          m = parse_args(s7, ")");
          if (!m) {
             return 0;
          }
          if (sizeof(m[0]) < 6) {
             m[0] += allocate(6-sizeof(m[0]));
          }
          obs = map_array(obs, "mapped_call", this_object(), s1, m[0]);
          if (sizeof(obs) == 1) {
            args += obs;
          } else {
            args += ({ obs });
          }
          str = m[1];
          break;
        } else if (s2 && s3)
          if (strlen(s4) < strlen(s5)) {
            s1 = ",";
            str = s4;
          } else {
            s1 = close;
            s2 = s3;
            str = s5;
          } else if (s2) {
            s1 = ",";
            str = s4;
          } else if (s3) {
            s1 = close;
            s2 = s3;
            str = s5;
          } else {
            s1 = "";
            s2 = "";
          }
          obs = WIZ_PRESENT->wiz_present(str, this_player());
          if (!sizeof(obs)) {
            if (str[0] >= '0' && str[0] <= '9' || str[0] == '-') {
              sscanf(str, "%d%s", i, str);
              args += ({ i });
            } else
              args += ({ replace_string(str, "\\n", "\n") });
          } else if (sizeof(obs) == 1)
            args += ({ obs[0] });
          else
            args += ({ obs });
          str = s1+s2;
          break;
    }
    while (strlen(str) && str[0] == ' ') {
       str = str[1..<1];
    }
    if (!strlen(str)) {
      return ({ args, str });
    }
    if (str[0..0] == close) {
      return ({ args, str[1..<1] });
    }
    if (str[0] != ',') {
      printf("Parse error reading arguments, ',' or '%s' expected.\n", close);
      printf("Line left unprocessed %s\n", str);
      return 0;
    }
    str = str[1..<1];
  }
  return ({ args, str });
}
#ifdef NOPE
void inform_of_call(object ob, mixed *argv) {
  string str;
  int i;
  str = this_object()->query_cap_name() + " calls " + argv[0] + "(";
  for (i=1; i<sizeof(argv); ) {
    str += replace(sprintf("%O", argv[i]), "\n", " ");
    if (++i < sizeof(argv)) str += ",";
  }
}
#endif
protected mixed mapped_call(object ob, string func, mixed *argv) {
  return call_other(ob, func, argv ...);
}
protected int parse_frogs(string str) {
  mixed junk;
  junk = parse_args(str, ";");
  if (!junk)
    return 1;
  write("The line "+str+" returns: \n");
  printf("%O\n", junk[0]);
  return 1;
}
mixed expr();
protected mixed bit4() {
  mixed val1, val2, val3;
  if (pos < sizeof(func)) {
    if (pointerp(func[pos])) {
      return func[pos++][0];
    }
    if (stringp(func[pos])) {
      if (func[pos][0] == '$') {
        val1 = (object)this_player()->get_obvar(func[pos][1..<1]);
        pos++;
        return val1;
      }
      if (force_string) {
        force_string = 0;
        return func[pos++];
      }
      val1 = (object *)WIZ_PRESENT->wiz_present(func[pos], this_player());
      if (!sizeof(val1)) {
        return func[pos++];
      }
      pos++;
      if (sizeof(val1) == 1) {
        return val1[0];
      }
      return val1;
    }
    switch (func[pos]) {
      case TOK_OBRAC :
        pos++;
        val1 = expr();
        if (func[pos] != TOK_CBRAC) {
          printf("Mismatched brackets.\n");
        } else {
          pos++;
        }
        break;
      case TOK_SARRAY :
        pos++;
        val1 = ({ });
        while (pos < sizeof(func) &&
            func[pos] != TOK_EARRAY) {
          if (func[pos] == TOK_COMMA) {
             pos++;
          }
          val2 = expr();
          if (func[pos] != TOK_COMMA &&
              func[pos] != TOK_EARRAY) {
            printf("Error processing array.\n");
            return 0;
          }
          val1 += ({ val2 });
        }
        pos++;
        break;
      case TOK_SMAPPING :
        pos++;
        val1 = ([ ]);
        while (pos < sizeof(func) && func[pos] != TOK_EMAPPING) {
          if (func[pos] == TOK_COMMA) pos++;
          val2 = expr();
          if (func[pos] != TOK_COLON) {
            printf("Error processing mapping, expected :.\n");
            return 0;
          }
          pos++;
          val3 = expr();
          if (func[pos] != TOK_EMAPPING && func[pos] != TOK_COMMA) {
            printf("Error processing mapping, expected , or ].\n");
            return 0;
          }
          val1[val2] = val3;
        }
        printf("End of mapping.\n");
        pos++;
        break;
      default :
        printf("Broken parser....\n");
        break;
    }
  }
  return val1;
}
protected mixed do_function_call(object ob, string name, mixed stuff) {
  string found;
  object shad;
  if (objectp(ob)) {
    shad = ob;
    while ((shad = shadow(shad, 0))) {
      if ((found = function_exists(name, ob)))
        break;
    }
    if (!found && !(found = function_exists(name, ob))) {
      printf("*** function %s not found in %s ***\n",
          name, file_name(ob));
      return 0;
    } else {
      printf("*** function %s on %s found in %s ***\n", name, file_name(ob),
          found);
    }
    if ((ob != this_player()) && ob->query_property("player") &&
        !ob->query_property("no score")) {
        unguarded((: write_file,
                   (LMASTER->query_member(this_player()->query_name()) ?
                    "/d/admin/log/CALL_LIAISONS.log" :
                    "/d/admin/log/CALL_CREATORS.log" ),
                   sprintf("%s: %s (%O) called %s(%s) on %s (%O)\n",
                           ctime(time()),
                           this_player()->query_name(), this_player(),
                           name,
                           implode(stuff - ({0}), ", "), ob->query_name(),
                           ob) :));
        user_event( this_object(), "inform",
              sprintf("%s called %s(%s) on %s",
            this_player()->query_name(), name, implode(stuff - ({0}), ", "),
            ob->query_name()), "calls");
    }
    return call_other(ob, name, stuff[0], stuff[1], stuff[2],
        stuff[3], stuff[4], stuff[5]);
  }
  return 0;
}
protected mixed bit3() {
  mixed *tmp, val1, val2, val3;
  int i;
  val1 = bit4();
  while (pos < sizeof(func)) {
    switch (func[pos]) {
      case TOK_CALL :
        pos++;
        force_string = 1;
        val2 = bit4();
        force_string = 0;
        if (func[pos] != TOK_OBRAC) {
          printf("Open bracket expected.\n");
        } else {
          tmp = ({ });
          pos++;
          while (pos < sizeof(func) && func[pos] != TOK_CBRAC) {
            if (func[pos] == TOK_COMMA) pos++;
            val3 = expr();
            if (func[pos] != TOK_COMMA && func[pos] != TOK_CBRAC) {
              printf("Error in function arguments.\n");
              return 0;
            }
            tmp += ({ val3 });
          }
          pos++;
        }
        if (objectp(val1)) {
          val1 = ({ val1 });
        }
        if (!pointerp(val1)) {
          printf("Array or object expected for function call.\n");
          break;
        }
        if (!stringp(val2)) {
          printf("String expected for the function call name.\n");
          break;
        }
        if (sizeof(tmp) < 6) {
          tmp += allocate(6-sizeof(tmp));
        }
        for (i=0;i<sizeof(val1);i++) {
          val1[i] = do_function_call(val1[i], val2, tmp);
        }
        if (sizeof(val1) == 1) {
          val1 = val1[0];
        }
        break;
      case TOK_SMAPPING :
        pos++;
        val2 = expr();
        if (func[pos] == TOK_DOTDOT) {
          pos++;
          val3 = expr();
          if (func[pos] != TOK_EMAPPING) {
            printf("Expected closeing ].\n");
            break;
          }
          pos++;
          if (!pointerp(val1)) {
            printf("Can only use the .. syntax on arrays.\n");
            break;
          }
          if (!intp(val2) || !intp(val3)) {
            printf("Indexes must be integers.\n");
            break;
          }
          val1 = val1[val2..val3];
          break;
        }
        if (func[pos] != TOK_EMAPPING) {
          printf("Expected closeing ].\n");
          break;
        }
        pos++;
        if (mapp(val1)) {
          val1 = val1[val2];
        } else if (pointerp(val1)) {
          if (!intp(val2)) {
            printf("Can only use integers as an index on an array.\n");
          } else if (val2 < 0 || val2 >= sizeof(val1)) {
            printf("Index out of bounds.\n");
          } else {
            val1 = val1[val2];
          }
        } else {
          printf("Can only index off arrays or mappings.\n");
        }
        break;
      default :
        return val1;
    }
  }
  return val1;
}
protected mixed bit2() {
  mixed val1, val2;
  val1 = bit3();
  while (pos < sizeof(func)) {
    switch (func[pos]) {
      case TOK_MULT :
        pos ++;
        val2 = bit3();
        if ((!intp(val1) && !floatp(val1)) || (!intp(val2) && !floatp(val2))) {
          printf("Incompatible types in multiply, both must be integers.\n");
          val1 = 0;
        } else {
          val1 = val1*val2;
        }
        break;
      case TOK_DIV :
        pos ++;
        val2 = bit3();
        if ((!intp(val1) && !floatp(val1)) || (!intp(val2) && !floatp(val2))) {
          printf("Incompatible types in division, both must be integers.\n");
          val1 = 0;
        } else if (!val2) {
          printf("Division by 0 error.\n");
        } else {
          val1 = val1/val2;
        }
        break;
      default :
        return val1;
    }
  }
  return val1;
}
mixed expr() {
  mixed val1, val2;
  val1 = bit2();
  while (pos < sizeof(func)) {
    switch (func[pos]) {
      case TOK_PLUS :
        pos ++;
        val2 = bit2();
        if (pointerp(val1) && !pointerp(val2)) {
          printf("Incompatible types in addition, array and something "
                 "else.\n");
          val1 = 0;
        } else {
          val1 = val1 + val2;
        }
        break;
      case TOK_MINUS :
        pos ++;
        val2 = bit2();
        if (pointerp(val1) && !pointerp(val2)) {
          printf("Incompatible types in addition, array and something "
                 "else.\n");
          val1 = 0;
        } else {
          val1 = val1 + val2;
        }
        break;
      case TOK_ASSIGN :
        pos++;
        val2 = expr();
        if (pointerp(val1) || mapp(val1)) {
          printf("Cannot use an array or mapping as a variable name.\n");
        } else {
          this_player()->set_obvar(val1, val2);
        }
        val1 = val2;
        break;
      default :
        return val1;
    }
  }
  return val1;
}
void init_expr(string expr) {
  pos = 0;
  force_string = 0;
  func = TOKENISER->tokenise(expr);
}
void finish_expr() {
  func = 0;
}
#ifdef BOOLEAN
mixed eval() {
  mixed *tmp, val1, val2;
  int i, j;
  val1 = bit2();
  while (pos < sizeof(func))
    switch(func[pos]) {
      case TOK_EQUAL :
      case TOK_GREATOR :
      case TOK_LESS :
      case TOK_GREATOREQ :
      case TOK_LESSEQ :
    }
}
#endif

==================================================
FILE: path.c
==================================================

private string home_dir;
private nosave string current_path;
string get_path(string str) {
   string *array;
   string *array1;
   string temp;
   int i;
   if (!str) {
      if(!home_dir) {
         home_dir = "/w/" + this_player()->query_name();
      }
      str = home_dir;
   }
   if (str == "~") {
      str = "w/"+this_player()->query_name();
   } else {
      if(str[0] == '~') {
         if(str[1] == '/') {
            sscanf(str, "~%s", temp);
            str = "/w/" + this_player()->query_name() + temp;
         } else {
            string name;
            if (sscanf(str,"~%s/%s",name,str)!=2) {
               name = extract(str,1);
               str = "w/"+name;
            } else {
               str = "w/"+name+"/"+str;
            }
         }
      } else {
         if (str[0] != '/') {
            str = current_path+"/"+str+"/";
         }
      }
      if (str == "/") {
         return "/";
      } else {
         array = explode(str,"/") - ({ "" }) ;
         array1 = ({ });
      }
      for (i = 0; i < sizeof(array); i++) {
         reset_eval_cost();
         if (array[i] == "..") {
           if (sizeof(array1)) {
             array1 = array1[0..<2];
           }
         } else if (array[i] != ".") {
           array1 += ({ array[i] });
         }
      }
      if (sizeof(array1)) {
         str = implode(array1, "/");
      } else {
         str = "";
      }
   }
   return "/"+str;
}
string *get_files( string str ) {
   int loop;
   int count;
   string *filenames;
   string rmpath;
   string temp1;
   string temp2;
   string *names;
   string *files;
   names = explode(str, " ")- ({ "" });
   if(sizeof(names) == 0) {
      return ({ });
   }
   filenames = ({ });
   for(count = 0; count < sizeof(names); count++) {
      str = names[count];
      str = rmpath = get_path(str);
      if(rmpath == "/") {
         filenames += ({ "/" });
         continue;
      }
      if(sscanf(rmpath, "%s/%s", temp1, temp2) == 2) {
         string *path_elements;
         path_elements = explode(rmpath, "/") - ({ "" });
         rmpath = implode(path_elements[0..sizeof(path_elements) - 2], "/");
      }
      files = get_dir(str);
      if(files) {
         int loop2;
         for(loop2 = 0; loop2 < sizeof(files); loop2++) {
            filenames += ({ rmpath + "/" + files[loop2] });
         }
      }
   }
   for(loop = 0; loop < sizeof(filenames); loop++) {
      if(filenames[loop][0] != '/') {
         filenames[loop] = "/" + filenames[loop];
      }
   }
   return filenames;
}
string *get_cfiles(string str) {
   int loop;
   string temp, *names, temp2;
   names = explode(str, " ") - ({ "" });
   for(loop = 0; loop < sizeof(names); loop++) {
      if(sscanf(names[loop], "%s.%s", temp, temp2) != 2) {
         names[loop] += ".c";
      }
   }
   str = implode(names, " ");
   return get_files(str);
}
string query_current_path() {
   return current_path;
}
string query_home_dir() {
   return home_dir;
}
protected int set_home_dir(string dir) {
   home_dir = dir;
   return 1;
}
void set_current_path(string str) {
   current_path = str;
}

==================================================
FILE: player.c
==================================================

#include <config.h>
#include <board.h>
#include <bounty.h>
#ifndef __DISTRIBUTION_LIB__
#include <deity.h>
#endif
#include <drinks.h>
#include <library.h>
#include <living.h>
#include <login.h>
#include <login_handler.h>
#include <log.h>
#include <quest_handler.h>
#include <command.h>
#include <mail.h>
#include <player.h>
#include <skills.h>
#include <top_ten_tables.h>
#include <tune.h>
#include <weather.h>
#include <refresh.h>
#include <nroff.h>
#include <db.h>
#include <error_handler.h>
#include <player_handler.h>
#include <playerinfo.h>
#include <group_handler.h>
class player_info {
   int hb_num;
   int level;
   int level_time;
   int save_inhibit;
   int update_tmps_call_out;
   int last_save;
   object snoopee;
   mapping titles;
}
#include <clubs.h>
inherit "/global/line_ed";
inherit "/global/events";
inherit "/global/log";
inherit "/global/spells";
inherit "/global/more_string";
inherit "/global/finger";
inherit "/global/pweath";
inherit "/std/living/living";
inherit "/global/psoul";
inherit "/global/guild-race";
inherit "/global/more_file";
inherit "/global/path";
inherit "/global/start_position";
inherit "/global/family";
#define MIN_TIME_TO_SAVE 1800
#define FORGOT_CO_ORD_TIME (840553267+(8*60*60))
#define LEVEL_CACHE 60
#define ITEM_TRACKER ("/obj/handlers/item_tracker")
private nosave class player_info _pinfo;
private int time_on;
private int max_deaths;
private int monitor;
private int _refresh_time;
private int start_time;
private int creator;
private int deaths;
private int last_log_on;
private int no_logins;
private int activity_counter;
private int _flags;
private string cap_name;
private string last_on_from;
private nosave string my_file_name;
void start_player();
void public_commands();
int save();
void set_desc(string str);
void do_load_auto();
void set_name(string str);
int check_dark(int light);
void continue_start_player();
int restart_heart_beat();
int brief_verbose(string,
                  string);
int quit_alt(int verbose);
int review();
int toggle_wimpy(string);
int do_refresh(string);
int do_cap(string);
protected void set_invis(int level);
void set_player_killer(int);
int query_player_killer();
void finished_error_check( object player, string my_name, int status,
    mixed data );
void check_error_count();
void check_approve_list();
void create()
{
   if (query_name()) {
      return;
   }
   living::create();
   events::create();
   psoul::create();
   line_ed::create();
   more_string::create();
   start_position::create();
   add_property("determinate", "");
   spells::create();
   time_on = time();
   start_time = time();
   seteuid("PLAYER");
   Str = 13;
   Dex = 13;
   Int = 13;
   Con = 13;
   Wis = 13;
   set_max_sp(50);
   set_sp(50);
   wimpy = 20;
   max_deaths = 7;
   set_desc(0);
   add_ac("bing", "blunt", 15);
   add_ac("bing2", "sharp", 15);
   add_ac("bing3", "pierce", 15);
   add_property("player", 1);
   set_cols(79);
   set_rows(24);
   last_log_on = time();
   race_ob = RACE_STD;
   sscanf(file_name(this_object()), "%s#", my_file_name);
   _pinfo = new (class player_info, titles: ([ ]), save_inhibit:1);
}
void dest_me()
{
   if ((query_name() != "object") && objectp(this_player()) &&
       (this_player() != this_object()) &&
       (file_name(this_player()) != "/obj/shut") &&
       (explode(file_name(this_player()), "#")[0] != "/secure/login") &&
       (explode(file_name(this_player()), "#")[0] != "/secure/nlogin")) {
      user_event(this_object(), "inform",
                 (string) this_player()->query_name() +
                 " dests " + query_name(), "dest");
      tell_object(this_object(), "You were destructed by " +
                  capitalize((string) this_player()->query_name()) + ".\n");
   }
   if(file_size(PLAYER_HANDLER->query_player_file_name(query_name())+
                ".o.gz") > 0 &&
      PLAYER_HANDLER->query_player_disk_file_name(query_name()) &&
      PLAYER_HANDLER->query_player_file_name(query_name()) !=
      PLAYER_HANDLER->query_player_disk_file_name(query_name())) {
     unguarded((:rename,
                PLAYER_HANDLER->query_player_file_name(query_name())+".o.gz",
                PLAYER_HANDLER->query_player_disk_file_name(query_name())+
                ".o.gz" :));
   }
   ::dest_me();
}
void disallow_save()
{
   _pinfo->save_inhibit = 1;
}
void allow_save()
{
   _pinfo->save_inhibit = 0;
}
int query_save_inhibit()
{
   return _pinfo->save_inhibit;
}
int query_start_time()
{
   return start_time;
}
nomask string query_cap_name()
{
   return cap_name;
}
void move_player_to_start(string bong,
                          int new_flag,
                          string c_name,
                          string ident,
                          int go_invis) {
  string lang;
   if (file_name(previous_object())[0..12] != "/secure/login" &&
       file_name(previous_object())[0..13] != "/secure/nlogin") {
      write("You don't have clearance to do that.\n");
      return;
   }
   seteuid("Root");
   set_name(bong);
   if (!new_flag) {
      unguarded((: restore_object,
                   PLAYER_HANDLER->query_player_file_name(query_name()), 1 :));
      if (go_invis) {
        switch(go_invis) {
        case -1:
          set_invis(0);
          break;
        case 2:
          if (this_object()->query_lord()) {
            set_invis(2);
            break;
          }
        case 1:
          set_invis(1);
        }
      }
   }
   disallow_save();
   add_property("player", 1);
   cap_name = c_name;
   set_short(cap_name);
   add_property("determinate", "");
   no_logins++;
   if (!query_cols()) {
      set_cols(79);
   }
   remove_property("new player");
   if (this_player()->query_creator()) {
      seteuid(query_name());
      if (file_size("/w/" + query_name() + "/cmds") == -2)
         AddSearchPath(({ "/w/" + query_name() + "/cmds" }));
      AddSearchPath(({ DIR_PLAYER_CMDS, DIR_SECURE_PLAYER_CMDS,
                       DIR_CREATOR_CMDS, DIR_SECURE_CREATOR_CMDS,
                       DIR_PLAYTESTER_CMDS }));
   } else {
      seteuid("PLAYER");
      AddSearchPath(({ DIR_PLAYER_CMDS, DIR_SECURE_PLAYER_CMDS }));
   }
   if (!last_on_from) {
      printf("You have never logged in before.\n");
   } else {
      printf("You last logged in from %s and are currently "
             "logged in from %s (%s).\n", last_on_from,
             query_ip_name(this_object()), query_ip_number(this_object()));
   }
   last_on_from = query_ip_name(this_object()) + " (" +
      query_ip_number(this_object()) + ")";
   if (time_on > 0) {
      time_on = 0;
   }
   time_on += time();
   if (new_flag) {
      add_property("new player!", 1);
   }
   LOGIN_HANDLER->player_logon(bong, query_property("guest"),
                               (query_ip_name()? query_ip_name() :
                                query_ip_number()));
   if(query_property("guest")) {
     this_player()->set_nationality(DEFAULT_NATIONALITY);
     this_player()->
       set_nationality_region(this_player()->find_region(DEFAULT_NATIONALITY,
                                                         DEFAULT_REGION));
     lang = DEFAULT_NATIONALITY->query_language();
     this_player()->add_language(lang);
     this_player()->set_default_language(lang);
     this_player()->set_language(lang);
   }
   write(LOGIN_HANDLER->get_message("/doc/NEWS"));
   call_out((: continue_start_player :), 0);
   PLAYER_HANDLER->remove_cache_entry(query_name());
}
protected void move_to_start_pos()
{
   ::move_to_start_pos();
   if (query_verbose("look"))
      command("look");
   else
      command("glance");
   if (!finger_set()) {
      write
         ("%^BOLD%^Please set your finger information with 'chfn'.%^RESET%^\n");
   }
   if(no_logins == 1 && !query_property("guest")) {
     write("\n%^BOLD%^" +
           LOGIN_HANDLER->get_message("/doc/login/NEW_USER_START") +
           "%^RESET%^\n");
   }
   no_time_left();
   START_PLAYER->logged_on_times(no_logins);
   if(query_ip_number(this_object()) == query_ip_name(this_object()))
     resolve(query_ip_number(this_object()), "");
}
protected void update_activity(int logon)
{
   int time_on;
   if (last_log_on > 0) {
      time_on = last_command - last_log_on;
      if (time_on > 0)
         activity_counter -= (time_on / (3600 * 24 * 7)) * 10;
   }
   if (activity_counter <= -55) {
      activity_counter = -55;
   }
   if (logon) {
      activity_counter += 3;
   } else {
      activity_counter += 2 * ((time() - last_log_on) / 3600);
   }
   if (activity_counter >= 0)
      activity_counter = 0;
}
int query_activity_counter()
{
   return activity_counter;
}
private void display_bug_replies(int type, class error_replies* replies) {
   if (type == DB_SUCCESS) {
      if (sizeof(replies) > 0) {
         tell_object(this_object(), "\n\nYou have %^YELLOW%^" +
            sizeof(replies) + " NEW%^RESET%^ bug repl" +
            (sizeof(replies) > 1?"ies ":"y ") +
            "(read with 'bug replies').\n\n");
      }
   }
}
private void check_mccp() {
   if(!compressedp(this_object())) {
     write("\n%^BOLD%^%^RED%^You are logged in uncompressed!\n");
     write("Use of an MCCP capable mud client will reduce your load on "
           "the " + mud_name() + " system.%^RESET%^\n\n");
   }
}
void continue_start_player()
{
   string title;
   mapping news_rc;
   mixed *stuff;
   object book;
   if (this_object()->query_lord()) {
      creator = 1;
   }
   start_player();
   no_time_left();
   if (query_property(PASSED_OUT) && !query_property(TRANCE)) {
      call_out((: remove_property :), 10 + random(30), PASSED_OUT);
   }
   remove_property(UNKNOWN_MOVE);
   remove_property(RUNNING_MOVE);
   init_after_save();
   printf("%s", fix_string(MAILER->new_mail(query_name())));
   news_rc = BOARD_HAND->query_newsrc(query_name());
   if (!news_rc) {
      news_rc = ([ ]);
   }
   stuff = BOARD_HAND->get_subjects("announcements");
   if (sizeof(stuff)) {
      if (stuff[<1][B_TIME] > news_rc["announcements"]) {
         write("\nThere are %^YELLOW%^NEW%^RESET%^ announcements.  ");
         write("You can read them with \"news\".\n\n");
      }
   }
   call_out((: check_mccp :), 4);
   if (query_property("dead")) {
      (clone_object(DEATH_SHADOW))->setup_shadow(this_object());
      book = clone_object(DEAD_BOOK);
      book->move(this_object());
   }
   if (query_property("noregen")) {
      DEATH->person_died(query_name());
   }
   exec_alias("login", "");
   update_activity(1);
   last_log_on = time();
   title = LIBRARY->query_title(query_name());
   if (stringp(title)) {
      _pinfo->titles += ([ "quest" : title ]);
   }
   if (my_file_name != "/global/player") {
      check_error_count();
      if(my_file_name != "/global/playtester") {
        check_approve_list();
      }
   }
   if (query_property("new player!")) {
     PLAYERINFO_HANDLER->player_created(query_name());
      user_event(this_object(), "inform",
                 capitalize(query_name()) +
                 " arrives on " + mud_name() + " for the first time!", "new-player");
      remove_property("new player!");
      set_last_pos(CONFIG_NEWBIE_START_LOCATION);
      START_PLAYER->start_player(this_object());
   }
   check_family_name();
   call_out((: move_to_start_pos :), 0);
   call_out((: set_heart_beat(1) :), 1);
   ERROR_HANDLER->do_error_replies(query_name(), 1, (: display_bug_replies :));
}
void check_error_count() {
   string my_name;
   my_name = query_name();
   DB_HANDLER->make_sql_request( "errors", "atuin", "",
      "SELECT COUNT(Id) AS idc FROM errors WHERE Directory = '/w/" +
      my_name + "' AND Status = 'OPEN'",
       (: finished_error_check, this_object(), my_name :) );
}
void finished_error_check( object player, string my_name, int status,
    mixed data ) {
   int num;
   int ret;
   if ( file_size("/w/" + my_name + "/" + PLAYER_ERROR_LOG) > 0 ) {
       num = file_length("/w/" + my_name + "/" + PLAYER_ERROR_LOG);
       tell_object( player, "%^YELLOW%^You have %^RED%^" + num +
           "%^YELLOW%^ director" + (num == 1 ? "y" : "ies") +
           " with %^RED%^ERRORS%^YELLOW%^ in /w/" + my_name + "/" +
           PLAYER_ERROR_LOG + ".%^RESET%^\n");
   }
   if ( status == DB_SUCCESS && sizeof( data ) > 0 ) {
      if ( ( ret = data[0]["idc"] ) > 0 ) {
         tell_object( player, "%^YELLOW%^You have %^RED%^" + ret +
            " ERROR" +  (ret == 1 ? "" : "S") + "%^YELLOW%^ in /w/" +
            my_name +  ".%^RESET%^\n");
      }
   }
}
void check_approve_list() {
  string str;
  mapping assignments;
  int count;
  assignments = master()->query_directory_assignments();
  foreach(str in keys(assignments)) {
    if(member_array(this_object()->query_name(), assignments[str]) != -1 &&
       file_size(str + "/to_approve")) {
      count = sizeof(get_dir(str + "/to_approve
void start_player()
{
   if (this_object()->query_creator() && my_file_name != "/global/player") {
      this_player()->all_commands();
      this_player()->app_commands();
      this_player()->wiz_commands();
   }
   call_out((: do_load_auto :), 1);
   reset_get();
   enable_commands();
   public_commands();
   command_commands();
   parser_commands();
   force_commands();
   race_guild_commands();
   soul_commands();
   event_commands();
   finger_commands();
   communicate_commands();
   living_commands();
   logging_commands();
   editor_commands();
   if (this_player()->query_creator()) {
      set_living_name(query_name());
   }
   set_no_check(1);
   set_con(Con);
   set_dex(Dex);
   set_int(Int);
   set_str(Str);
   set_wis(Wis);
   reset_all();
   set_current_path(query_home_dir());
   if (wimpy > 100) {
      wimpy = 25;
   }
   if (contmp || dextmp || inttmp || strtmp || wistmp) {
      _pinfo->update_tmps_call_out = call_out((: update_tmps :), 900);
   }
}
int adjust_hp(int number,
              object attacker,
              object weapon,
              string attack)
{
   if (!interactive(this_object()))
      return query_hp();
   return::adjust_hp(number, attacker, weapon, attack);
}
void do_load_auto()
{
   load_auto_load_alt(query_auto_load_string(), this_object(), this_object(),
                      (: tell_object(this_object(),
                                     "\n%^CYAN%^Inventory regeneration complete.%^RESET%^\n") :));
   set_auto_load_string(0);
   allow_save();
}
void public_commands()
{
   add_command("restart", this_object(), "", (: restart_heart_beat() :));
   add_command("save", this_object(), "", (: save() :));
   add_command("quit", this_object(), "", (: quit_alt(-1) :));
   add_command("quit", this_object(), "brief", (: quit_alt(0) :));
   add_command("quit", this_object(), "verbose", (: quit_alt(1) :));
   add_command("review", this_object(), "", (: review() :));
   add_command("wimpy", this_object(), "", (: toggle_wimpy(0) :));
   add_command("wimpy", this_object(), "<word'number'>",
               (: toggle_wimpy($4[0]) :));
   add_command("refresh", this_object(), "<word'totally'>",
               (: do_refresh($4[0]) :));
   add_command("cap", this_object(), "<word'name'>", (: do_cap($4[0]) :));
}
int glance(string str)
{
   return command("glance" + (str ? " " + str : ""));
}
int look_me(string str)
{
   return command(str ? "look" + str : "look");
}
int review()
{
   write("Entry  : " + query_msgin() + "\n");
   write("Exit   : " + query_msgout() + "\n");
   write("MEntry : " + query_mmsgin() + "\n");
   write("MExit  : " + query_mmsgout() + "\n");
   write("Editor : " + query_editor() + "\n");
   return 1;
}
int examine(string arg)
{
   return look_me(arg ? " at " + arg : "");
}
varargs string short(int dark,
                     int verbose)
{
   string str;
   string family;
   string title;
   if (!interactive(this_object())) {
      str = "the net dead statue of ";
   } else {
      str = "";
   }
   family = query_family_name();
   if (!family) {
      family = "";
   } else {
      family = " " + family;
   }
   if (verbose)
      title = query_player_title();
   if (!title) {
      title = "";
   } else {
      title = title + " ";
   }
   return str + title + living::short(dark) + family;
}
int toggle_wimpy(string str)
{
   int number;
   if (!str) {
      if (this_object()->query_wimpy())
         write("You are in wimpy mode, you will run away at " +
               this_object()->query_wimpy() +
               "% of your max hps.\n");
      else
         write("You are in brave mode.\n");
      write("Usage: wimpy <num> (caution read help wimpy)\n");
      return 1;
   }
   if (sscanf(str, "%d", number) != 1)
      return notify_fail("You must set your wimpy to a number.\n");
   if ((number < 0) || (number > 30))
      return notify_fail("Your wimpy must be between 0 and 30%.\n");
   this_object()->set_wimpy(number);
   printf("Wimpy set to %d%%\n", wimpy);
   return 1;
}
string extra_score()
{
   return "";
}
nomask int save() {
#ifdef UNUSED
  if(query_verb() == "save") {
    if(_pinfo->last_save > time() - 900) {
      tell_object(this_object(), "You saved only a few minutes ago.\n");
      return 1;
    }
    _pinfo->last_save = time();
  }
#endif
  if (((time() - time_on) < MIN_TIME_TO_SAVE) &&
      !LIBRARY->query_quest_points(query_name()) &&
      !query_property("authorised player")) {
    if (query_verb() == "save") {
      tell_object(this_object(), "You're too young to save... sorry.\n");
    }
    return 1;
  }
  tell_object(this_object(), "Saving...\n");
  this_object()->save_me();
  return 1;
}
void save_me() {
   mixed old;
#ifdef NOT_SAVEING_PLAYERS
   if (!this_object()->query_creator()) {
      write("Not saving for players currently.\n");
      return;
   }
#endif
   if (query_auto_loading())
      return;
   if (query_property("guest")) {
      if (query_verb() == "save")
         tell_object(this_object(), "But not saving for guests... Sorry.\n");
      return;
   }
   if (query_save_inhibit()) {
      return;
   }
   if (guild_ob) {
      guild_ob->player_save(this_object());
   }
   if (race_ob) {
      race_ob->player_save(this_object());
   }
   old = geteuid();
   check_last_pos();
   effect_freeze();
   effects_saving();
   create_auto_load(all_inventory(), 1);
   if (interactive(this_object())) {
      last_on_from = query_ip_name(this_object()) + " (" +
         query_ip_number(this_object()) + ")";
   }
   time_on -= time();
      catch(unguarded((: save_object,
                      PLAYER_HANDLER->query_player_file_name(query_name()), 3 :)));
   time_on += time();
   ITEM_TRACKER->save_all_item_states(this_object()->query_name());
   effect_unfreeze();
   set_auto_load_string(0);
}
void save_with_auto_load(mixed al)
{
   mixed old;
#ifdef NOT_SAVEING_PLAYERS
   if (!this_object()->query_creator()) {
      write("Not saving for players currently.\n");
      return;
   }
#endif
   if (query_property("guest")) {
      write("But not saving for guests... sorry.\n");
      return;
   }
   if (((time() - time_on) < MIN_TIME_TO_SAVE) && query_verb() == "save") {
     tell_object(this_object(), "You're too young to save... sorry.\n");
     return;
   }
   if (query_save_inhibit()) {
      return;
   }
   if (guild_ob) {
      guild_ob->player_save(this_object());
   }
   if (race_ob) {
      race_ob->player_save(this_object());
   }
   old = geteuid();
   effect_freeze();
   effects_saving();
   set_auto_load_string(al);
   if (((time() - time_on) >= MIN_TIME_TO_SAVE) ||
       LIBRARY->query_quest_points(query_name())) {
      time_on -= time();
         catch(unguarded((: save_object,
                         PLAYER_HANDLER->query_player_file_name(query_name()),
                         3 :)));
      time_on += time();
   }
   effect_unfreeze();
}
int quit_alt(int verbose)
{
   object frog;
   if (verbose == -1) {
      verbose = query_verbose("quit");
   }
   if (query_auto_loading()) {
      if (!interactive(this_object())) {
         dest_me();
      } else {
         write
            ("You cannot quit yet: your inventory is still being generated.\n");
      }
      return 1;
   }
   if (sizeof(filter_array((object *) this_object()->query_attacker_list(),
                           (: living($1) :))) &&
       this_player() == this_object() && interactive(this_object())) {
      write
         ("You cannot quit while in combat.  Use 'stop' to stop fighting.\n");
      return 1;
   }
   check_last_pos();
   update_activity(0);
   last_log_on = time();
   catch(this_object()->event_quit(this_object()));
   catch(environment(this_object())->event_quit(this_object()));
   catch(editor_check_do_quit());
   write("A small gecko takes your hand and rushes you to the departure "
         "lounge.\n");
   say(query_cap_name() + " leaves the game.\n");
   catch(move("/room/departures"));
   user_event(this_object(), "inform",
              query_cap_name() + " leaves " + mud_name() + "", "logon", this_object());
   catch(LOGIN_HANDLER->player_logout(query_name()));
   if (race_ob) {
      catch(race_ob->player_quit(this_object()));
   }
   if (guild_ob) {
      catch(guild_ob->player_quit(this_object()));
   }
   frog = clone_object("/obj/monster/greco");
   frog->move("/room/departures");
   frog->get_rid_of(this_object(), verbose);
   return 1;
}
int do_quit()
{
   return quit_alt(-1);
}
int quit()
{
   if (query_auto_loading() || query_save_inhibit()) {
      tell_object(this_object(),
                  "Forced to quit whilst auto loading.  Not saving.\n");
      ::dest_me();
      return 1;
   }
   check_last_pos();
   update_activity(0);
   last_log_on = time();
   catch(editor_check_do_quit());
   catch(this_object()->event_quit(this_object()));
   catch(environment(this_object())->event_quit(this_object()));
   tell_object(this_object(), "Thanks for playing.  See you next time.\n");
   say(query_cap_name() + " leaves the game.\n");
   user_event(this_object(), "inform",
              query_cap_name() + " leaves " + mud_name() + "", "logon", this_object());
   catch(LOGIN_HANDLER->player_logout(query_name()));
   if (race_ob) {
      catch(race_ob->player_quit(this_object()));
   }
   if (guild_ob) {
      catch(guild_ob->player_quit(this_object()));
   }
   catch(save_me());
   foreach( object inv in all_inventory( this_object() ) ) {
      reset_eval_cost();
      catch( inv->set_tracked_item_status_reason("QUIT") );
      catch( inv->dest_me() );
   }
   catch(ITEM_TRACKER->
         save_all_item_states_delete_cache(this_object()->query_name()));
   effects_quiting();
   reset_eval_cost();
   if (catch(dest_me())) {
      destruct(this_object());
   }
   return 1;
}
mapping query_titles()
{
   return copy(_pinfo->titles);
}
string query_title()
{
   return implode(m_values(_pinfo->titles), ", ");
}
void set_title(string type,
               string title)
{
   _pinfo->titles[type] = title;
}
void remove_title(string type)
{
   map_delete(_pinfo->titles, type);
}
int query_deaths()
{
   return deaths;
}
void adjust_deaths(int i)
{
   if (i > 0) {
      deaths += i;
   }
}
nomask void set_name(string str) {
  if (query_name() && query_name() != "object") {
    return;
  }
  if (file_name(previous_object())[0..12] != "/secure/login" &&
      file_name(previous_object())[0..13] != "/secure/nlogin") {
    return;
  }
  ::set_name(str);
  set_living_name(query_name());
  set_main_plural(query_name());
}
void init_static_arg(mapping map)
{
   return;
}
void init_dynamic_arg(mapping, object) {
  return;
}
string long(string str,
            int dark)
{
   string s;
   string tmp;
   string title;
   string nationality;
   title = query_player_title();
   if (!title) {
      title = "";
   } else {
      title = title + " ";
   }
   s = "You see " + title + query_short();
   tmp = query_family_name();
   if (tmp) {
      s += " " + query_family_name();
   }
   if (guild_ob) {
      s += " " + (string) guild_ob->query_title(this_object()) + ".\n";
   } else {
      s += ".\n";
   }
   if (race_ob) {
      s += (string) race_ob->query_desc(this_object());
   }
   nationality = query_nationality_description(this_player());
   if (nationality  &&  nationality != "") {
      s += nationality + "\n";
   }
   if (dark == 2 || dark == -2) {
      s += "It is too ";
      if (dark == -2) {
         s += "dark";
      } else {
         s += "bright";
      }
      s += " to see their description or what " +
         query_pronoun() + " are wearing or carrying.\n";
      s += calc_extra_look();
   } else {
      if (query_desc() && query_desc() != "") {
         s += capitalize(query_pronoun()) + " " + query_desc() +
              query_main_zone_desc(query_wearing()) + "\n";
      }
      s += capitalize(query_pronoun()) + " " +
         this_object()->health_string() + ".\n";
      s +=
         capitalize(query_pronoun()) + " is " + query_position_short() +
         ".\n";
      s += calc_extra_look();
      s += weather_extra_look();
      s += query_living_contents(0);
   }
   return s;
}
mixed second_life()
{
   object corpse;
   string death_mess;
   add_property("dead", time());
   if (!DEATH->someone_died(this_object())) {
      deaths++;
   }
   effects_thru_death();
   corpse = make_corpse();
   reset_protectors();
   if (deaths > max_deaths) {
      death_mess = query_property ("death mess");
      tell_object(this_object(), "You have died your final death.  " +
                "Your name will be inscribed in the Hall of Legends.\n");
      if (death_mess && sizeof (death_mess)) {
        death_mess = strip_colours (death_mess);
        death_mess = replace (death_mess, ({"\n", "", "\a", ""}));
        shout(capitalize(query_name()) + " has died for the last time.  " +
          death_mess + "\n");
      }
      else {
        shout(capitalize(query_name()) + " has died for the last time.  " +
             capitalize(query_pronoun()) + " is mourned.\n");
      }
      LIBRARY->complete_death(query_name());
      corpse->move(PLAYER_MORGUE);
   } else
      corpse->move(environment());
   call_out((: save_me :), 0);
   if (find_object(OFFLER) && (deaths <= max_deaths)) {
      OFFLER->person_died(query_name());
   } else {
      DEATH->person_died(query_name());
   }
   clone_object(DEATH_SHADOW)->setup_shadow(this_object());
   if (guild_ob) {
      guild_ob->member_died(this_object());
   }
   gp = 0;
   hp = 0;
   set_sp(0);
   set_max_sp(50);
   xp = 0;
   reset_spells();
   reset_processes();
   contmp = dextmp = inttmp = strtmp = wistmp = 0;
   remove_call_out(_pinfo->update_tmps_call_out);
   adjust_tmp_con(-2);
   adjust_tmp_dex(-2);
   adjust_tmp_int(-2);
   adjust_tmp_str(-2);
   adjust_tmp_wis(-2);
   return corpse;
}
void remove_ghost()
{
   if (deaths > max_deaths) {
      if (this_player() != this_object()) {
         tell_object(this_object(), this_player()->query_cap_name() +
                     " tried to raise you, but you are completely dead.\n");
         tell_object(this_player(), query_cap_name() +
                     " is completely dead, you cannot raise " +
                     query_objective() + ".\n");
      } else {
         tell_object(this_object(), "You are completely dead.  You cannot " +
                     "be raised.\n");
         say(query_cap_name() +
             " struggles to appear in a solid form, but fails.\n");
         return;
      }
   }
   remove_property("dead");
   tell_object(this_object(), "You reappear in a more solid form.\n");
   if (guild_ob) {
      guild_ob->member_resurrected(this_object());
   }
   say(query_cap_name() + " appears in more solid form.\n");
   if (query_hp() < 0) {
      set_hp(1);
   }
   set_personal_temp(0);
   this_object()->dest_death_shadow();
   save_me();
   all_inventory()->recovery_from_death();
}
void net_dead()
{
   if (!environment() || file_name(environment()) == "/room/departures") {
      return;
   }
   if ((query_name() == "guest") || (query_name() == "root")) {
      say(query_name() + " vanishes in a puff of logic.\n");
      quit();
   } else {
      say(query_name() + " goes white, looks very chalky and turns into a " +
          "statue.\n");
      user_event(this_object(), "inform",
                 capitalize(query_name()) + " has lost " +
                 query_possessive() + " link", "link-death", this_object());
      check_last_pos();
      LOGIN_HANDLER->player_net_dead(query_name());
      save_me();
   }
   event(environment(), "net_dead", this_object());
}
void idle_out()
{
   say(cap_name + " has been idle for too long; " + query_pronoun() +
       " vanishes in a puff of boredom.\n");
   write("You idled out, sorry.\n");
   quit();
}
void heart_beat()
{
   catch {
      int idle_time;
      events::print_messages();
      flush_queue();
      if (!interactive(this_object())) {
         idle_time = time() - last_command;
      } else {
         idle_time = query_idle(this_object());
      }
      if (query_creator()) {
         idle_time = idle_time / 3;
      }
      if (idle_time > FULL_IDLE) {
         if ((LOGIN_HANDLER->is_discworld_full() || idle_time > MAX_IDLE) &&
             (!interactive(this_object())
              || my_file_name != "/global/lord")) {
            call_out((: idle_out :), 2);
         }
      }
      if (interactive(this_object())) {
         living::heart_beat();
         adjust_sp(1);
         adjust_xp(3);
         living::update_volumes();
         this_object()->do_spell_effects(0);
         if (_pinfo->hb_num++ > 1800)
            _pinfo->hb_num = 0;
         if (!(_pinfo->hb_num % 120)) {
            calc_personal_temp();
            adjust_max_sp(1);
         }
      }
   };
}
int query_monitor()
{
   return monitor;
}
void set_monitor(int i) {
  monitor = i;
}
protected void write_prompt()
{
   efun::tell_object(this_object(), "> ");
   return;
}
#ifdef UNUSED
protected void write_prompt()
{
   string prompt;
   int tmp,
     i;
   string stuff;
   if (!(monitor & 2) || !this_object()->query_creator())
      efun::tell_object(this_object(), "> ");
   else {
      prompt = "";
      stuff = this_player()->query_property("prompt");
      for (i = 0; i < strlen(stuff); i++) {
         switch (stuff[i]) {
         case 'h':
            tmp = ((query_hp() * 100) / query_max_hp());
            prompt += "Hp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += tmp + "%^RESET%^";
            break;
         case 'H':
            tmp = ((query_hp() * 100) / query_max_hp());
            prompt += "Hp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += query_hp() + "%^RESET%^";
            break;
         case 'g':
            tmp = (query_gp() * 100) / query_max_gp();
            prompt += "Gp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += tmp + "%^RESET%^";
            break;
         case 'G':
            tmp = (query_gp() * 100) / query_max_gp();
            prompt += "Gp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += query_gp() + "%^RESET%^";
            break;
         case 's':
            tmp = (query_sp() * 100) / query_max_sp();
            prompt += "Sp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += tmp + "%^RESET%^";
            break;
         case 'S':
            tmp = (query_sp() * 100) / query_max_sp();
            prompt += "Sp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += query_sp() + "%^RESET%^";
            break;
         case 'X':
         case 'x':
            prompt += "Xp:" + query_xp();
            break;
         default:
            if (sizeof(prompt) > 0 && prompt[sizeof(prompt) - 1] != stuff[i])
               prompt += sprintf("%c", stuff[i]);
         }
      }
      prompt += "> ";
      efun::tell_object(this_object(), fix_string(prompt));
   }
}
#endif
int run_away()
{
   int number;
   become_flummoxed();
   number =::run_away();
   if (number)
      tell_object(this_object(), "Your feet run away with you!\n");
   else
      tell_object(this_object(), "You try to run away, but no matter how "
                  "you scrabble, you can't find any way out.\n");
   return number;
}
nomask int query_time_on()
{
   return time_on - time();
}
int query_mature()
{
   return (MATURITY * 60 * 60 + time_on < time());
}
int check_dark(int light)
{
   int i;
   if (race_ob)
      if (catch(i = (int) race_ob->query_dark(light)))
         race_ob = RACE_STD;
      else
         return i;
   return (int) RACE_STD->query_dark(light);
}
int query_level()
{
   string tmp;
   if (_pinfo->level_time < (time() - LEVEL_CACHE)) {
      if (guild_ob) {
         _pinfo->level = (int) guild_ob->query_level(this_object());
      } else {
         tmp = query_property("backup guild");
         if (tmp) {
            _pinfo->level = tmp->query_level(this_object());
         } else
            _pinfo->level = CONFIG_DEFAULT_GUILD->query_level(this_object());
      }
      _pinfo->level_time = time();
   }
   return _pinfo->level;
}
int restart_heart_beat()
{
   set_heart_beat(1);
   write("Ok, heart_beat restarted.\n");
   return 1;
}
nomask void set_snoopee(object ob)
{
   _pinfo->snoopee = ob;
}
nomask object query_snoopee()
{
   return _pinfo->snoopee;
}
void set_creator(int i)
{
   if (previous_object() != master()) {
      write("Illegal attempt to set creator!\n");
      log_file("ILLEGAL", this_player(1)->query_name() + " (" +
               file_name(this_player(1)) +
               ") Illegal attempt to set_creator " + "at " + ctime(time()) +
               " from " + file_name(previous_object()) + "\n");
      return;
   }
   creator = i;
   set_home_dir("/w/" + query_name());
   save_me();
}
int query_prevent_shadow(object ob)
{
   if (function_exists("query_prevent_shadow", ob) ||
       function_exists("query_name", ob) ||
       function_exists("query_creator", ob) ||
       function_exists("query_lord", ob) ||
       function_exists("query_hidden", ob) ||
       function_exists("dest_me", ob) ||
       function_exists("query_object_type", ob) ||
       function_exists("query_lord", ob) || function_exists("save_me", ob))
      return 1;
   return 0;
}
int query_max_deaths()
{
   return max_deaths;
}
protected void set_max_deaths(int i)
{
   max_deaths = i;
}
int adjust_max_deaths(int i)
{
   if (i > 0) {
      return (max_deaths += i);
   }
}
varargs int move(mixed dest,
                 string msgin,
                 string msgout)
{
   int i;
   object env = environment();
   i = living::move(dest, msgin, msgout);
   if (!i) {
      me_moveing(env);
   }
   return i;
}
nomask protected int do_refresh(string str) {
   if (query_property("guest")) {
      return notify_fail("Guests cannot refresh, sorry.\n");
   }
   if (!str || str != "totally") {
      return notify_fail("Please read the docs before using this command.\n");
   }
   write("%^BOLD%^WARNING!  This will restart your character.%^RESET%^\n\n" +
         "Are you sure you wish to refresh yourself totally? ");
   input_to("refresh_docs");
   return 1;
}
protected int refresh_docs(string str) {
   string helpfile = "";
   str = lower_case(str);
   if (str[0] != 'y') {
      write("Ok, not refreshing.\n");
      return 1;
   }
   NROFF_HAND->create_nroff( "/doc/helpdir/refresh", helpfile );
   helpfile = NROFF_HAND->cat_file( helpfile );
   write ( helpfile[0..670] );
   write("\n\n%^BOLD%^Having read the documentation, are you still sure you "
         "wish to refresh totally?%^RESET%^\n");
   input_to("refresh3");
   return 1;
}
protected int refresh2(string str, int noevent) {
   object ob;
   string group;
   str = lower_case(str);
   if (str[0] != 'n' && str[0] != 'y') {
      write
         ("Pardon?  I do not understand.  Do you want to refresh yourself? ");
      input_to("refresh2");
      return 1;
   }
   if (str[0] == 'n') {
      write("Ok, not refreshing.\n");
      return 1;
   }
   write("Doing refresh.\n");
   Str = 13;
   Con = 13;
   Int = 13;
   Wis = 13;
   Dex = 13;
   inttmp = dextmp = wistmp = strtmp = contmp = 0;
   race_ob = CONFIG_DEFAULT_RACE;
   if (guild_ob)
      catch(guild_ob->delete_member(query_name()));
   if (!noevent) {
      REFRESH_HANDLER->player_refreshed(this_object(), PARTIAL_REFRESH);
   }
   guild_ob = 0;
   set_al(0);
   if (query_deity()) {
#ifndef __DISTRIBUTION_LIB__
      catch(DEITY->delete_worshipper(query_deity(), query_name()));
      catch(DEITY->delete_priest(query_deity(), query_name()));
#endif
   }
   set_deity(0);
   set_skills(0);
   PLAYTESTER_HAND->remove_playtester(query_name());
   if (query_family_name()) {
      CLUB_HANDLER->remove_member(query_family_name(), query_name());
      set_family_name(0);
   }
   reset_effects();
   reset_spells();
   reset_processes();
   setup_default_titles();
   guild_ob = 0;
   set_guild_data(0);
   xp = 0;
   deaths = 0;
   max_deaths = 7;
   _refresh_time = time();
   totaly_zap_bonus_cache();
   known_commands = ({ "skills", "rearrange", "gp", "newbie" });
   reset_starts();
   race_guild_commands();
   totaly_zap_stat_cache();
   drink_info = allocate(D_SIZEOF);
   map_prop = ([ "determinate" : "",
                 "player" : 1,
                 "skills version" :
                 (string) "/obj/handlers/change_skills"->query_version() ]);
   this_object()->remove_ghost();
   set_nationality(0);
   set_nationality_region(0);
   set_language("general");
   set_default_language("general");
   reset_all();
   group = this_player()->query_group();
   if (group) {
      GROUP->remove_member(group, this_player(), " refreshed themselves.");
   }
   set_last_pos(CONFIG_NEWBIE_START_LOCATION);
   START_PLAYER->give_junk(this_object());
   foreach (ob in query_attacker_list()) {
      catch(ob->stop_fight(this_object()));
      catch(stop_fight(ob));
   }
   call_out((: move_to_start_pos :), 0);
   if (!noevent) {
      write("Done refreshing.\n");
      say(cap_name + " refreshes " + query_objective() + "self.\n");
      save_me();
   }
   return 1;
}
protected int refresh3(string str)
{
   object *items,
    *ritems,
     item;
   str = lower_case(str);
   if (str[0] != 'n' && str[0] != 'y') {
      write("Pardon?  I do not understand.  Do you want to refresh " +
            "yourself totally? ");
      input_to("refresh3");
      return 1;
   }
   if (str[0] == 'n') {
      write("Ok, not refreshing.\n");
      return 1;
   }
   write("Ok, refreshing totally.\n");
   ritems = filter(all_inventory(environment()),
                   (: $1->query_property("dropped") &&
                      $1->query_property("dropped")[0] == query_name() :));
   move(CONFIG_NEWBIE_START_LOCATION);
   refresh2("y", 1);
   set_player_killer(0);
   _pinfo->titles = ([ ]);
   REFRESH_HANDLER->player_refreshed(this_object(), TOTAL_REFRESH);
   "/secure/related_files"->delete_related_files(query_name(),
                                                 0, TOTAL_REFRESH);
   items = ritems + all_inventory();
   foreach(item in items) {
      item->dest_me();
   }
   foreach(item in children("/obj/corpse")) {
      if (item->query_owner() == this_object()->query_name()) {
        item->move("/room/rubbish");
      }
   }
   foreach (string club in query_player_clubs()) {
      catch(CLUB_HANDLER->remove_member(club, this_player()->query_name()));
   }
   if (query_family_name()) {
      catch(CLUB_HANDLER->remove_member(query_family_name(),
                                  this_player()->query_name()));
      call_out("check_family_name", 2);
   }
   write("Done refreshing.\n");
   say(cap_name + " refreshes " + query_objective() + "self.\n");
   save_me();
   return 1;
}
string query_object_type(object player)
{
   if ("/obj/handlers/playtesters"->query_playtester(query_name())) {
      return "p";
   }
   return " ";
}
int do_cap(string str)
{
   if (!str)
      return notify_fail("Syntax: " + query_verb() + " <cap_name>\n");
   if (lower_case(str) != query_name())
      return
         notify_fail
         ("You must have the same letters in your capitalized name.\n");
   cap_name = str;
   write("Capitalized name set to " + cap_name + ".\n");
   return 1;
}
void set_my_ident(string str)
{
   return;
}
string query_my_ident()
{
   return 0;
}
void event_enter(object thing,
                 string mess,
                 object from)
{
   events::event_enter(thing, mess, from);
   living::event_enter(thing, mess, from);
}
void event_exit(object thing,
                string mess,
                object to)
{
   events::event_exit(thing, mess, to);
   living::event_exit(thing, mess, to);
}
string *parse_command_id_list()
{
   if (query_player_killer()) {
      return ({ "killer" }) +
             living::parse_command_id_list() + family::parse_command_id_list();
   } else {
      return living::parse_command_id_list() + family::parse_command_id_list();
   }
}
string *parse_command_plural_id_list()
{
   if (query_player_killer()) {
      return ({ "killers" }) + living::parse_command_plural_id_list() +
         family::parse_command_plural_id_list();
   } else {
      return living::parse_command_plural_id_list() +
         family::parse_command_plural_id_list();
   }
}
string *parse_command_adjectiv_id_list()
{
   return living::parse_command_adjectiv_id_list() +
         family::parse_command_adjectiv_id_list();
}
int query_last_log_on()
{
   return last_log_on;
}
int query_refresh_time()
{
   return _refresh_time;
}
int query_no_logins()
{
   return no_logins;
}
int query_creator()
{
   return 0;
}
int _living(){return 1;}
protected void set_invis(int level) {
}
int query_player_killer() {
   return _flags & PLAYER_KILLER_FLAG;
}
void set_player_killer(int flag) {
   if (flag) {
      _flags |= PLAYER_KILLER_FLAG;
   } else {
      _flags &= ~PLAYER_KILLER_FLAG;
   }
}
void set_role_playing(int i) {
  if(i)
    add_property(RPMODE, 1);
  else
    remove_property(RPMODE);
}
int query_role_playing() {
  return query_property(RPMODE);
}

==================================================
FILE: playtester.c
==================================================

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

==================================================
FILE: psoul.c
==================================================

#include <living.h>
#include <player.h>
#include <soul.h>
inherit "/global/alias";
inherit "/global/nickname";
nosave int time_left;
nosave int tl_updated;
nosave int doing_it;
nosave int last_command;
nosave int bypass_queue;
nosave int flush_call_id;
nosave string *queued_commands;
nosave string in_command;
nosave mixed interrupt;
nosave private function cmd = 0;
#if !efun_defined(add_action)
protected mixed _process_input(string);
protected mixed command(string);
#endif
void create() {
  time_left = ROUND_TIME;
  tl_updated = time();
  last_command = time();
  queued_commands = ({ });
}
void bypass_queue() { bypass_queue = 1; }
void no_time_left() {
  time_left = -ROUND_TIME;
}
protected int drunk_check(string str);
void soul_commands() {
#if efun_defined(add_action)
  add_action("lower_check","*", -10000);
  add_action((:drunk_check:),"*", 10000);
#endif
  alias_commands();
  nickname_commands();
  history_commands();
}
int query_queued_commands() {
  return sizeof(queued_commands);
}
int soul_com_force(string str) {
  if (file_name(previous_object()) != SOUL_OBJECT)
    return 0;
  command(str);
  return 1;
}
void do_soul(string str, mixed bing) {
  say(str, bing);
}
int query_time_left() {
  time_left += ((time() - tl_updated) / 2) * ROUND_TIME;
  if(time_left > ROUND_TIME)
    time_left = ROUND_TIME;
  tl_updated = time();
  return time_left;
}
int adjust_time_left(int i) {
   return time_left += i;
}
private void do_flush(int first) {
  int i;
  string str;
  if ( ( time_left < 0 ) || !sizeof( queued_commands ) ||
       ( this_object()->queue_commands(queued_commands[0]) &&
         !this_object()->query_creator() ) ) {
    return;
  }
  if (!first) {
    str = queued_commands[0];
    queued_commands = queued_commands[1..];
    doing_it = 1;
    catch(command(str));
    doing_it = 0;
    if (!sizeof(queued_commands)) {
      queued_commands = ({ });
      doing_alias = ([ ]);
    }
    return ;
  }
  for (i = 0; (i < 2) && (i < sizeof(queued_commands)); i++) {
    flush_call_id = call_out((: do_flush(0) :), 1);
  }
  flush_call_id = call_out((: do_flush(1) :), 2);
}
private void call_interrupt(int time_left, object interupter) {
   mixed stuff;
   stuff = interrupt;
   interrupt = 0;
   if (pointerp(stuff)) {
      catch(call_other(stuff[1],
                       stuff[0],
                       time_left,
                       stuff[2],
                       this_object(),
                       interupter,
                       in_command));
   } else if (functionp(stuff)) {
      catch(evaluate(stuff,
                     time_left,
                     this_object(),
                     interupter,
                     in_command));
   }
}
protected void flush_queue() {
  query_time_left();
  remove_call_out(flush_call_id);
  do_flush(1);
  if (!sizeof(queued_commands)) {
    if (interrupt && time_left > 0) {
      call_interrupt(0, this_object());
    }
    in_alias_command = 0;
    doing_alias = ([ ]);
    if (!sizeof(queued_commands)) {
      return ;
    }
    doing_alias = ([ ]);
    in_alias_command = 0;
  }
}
void set_interupt_command(mixed func, mixed ob, mixed arg) {
  if (!functionp(func)) {
    interrupt = ({ func, ob, arg });
    if ( !stringp( func ) )
      interrupt = 0;
  } else {
    interrupt = func;
  }
}
mixed *query_interupt_command() {
   return interrupt;
}
void set_interrupt_command(function func) {
  set_interupt_command(func, 0, 0);
}
void remove_queue() {
   queued_commands = ({ });
   if ( interrupt && ( time_left < 0 ) ) {
      call_interrupt(-time_left, this_object());
   }
   tell_object( this_object(), "Removed queue.\n" );
   if (this_object()->query_lord()) {
     time_left = 0;
   } else {
     time_left = -DEFAULT_TIME;
   }
}
void interupt_command(object interupter) {
   if (interupter) {
      call_interrupt(-time_left, interupter);
   }
}
void command_override(function func){
  if(!functionp(func))
    error("command_override needs a function!");
  cmd = func;
}
protected int drunk_check(string str) {
   string *rabbit;
   string *green;
   string mess;
   string comm;
   string arg;
   if(cmd){
     object owner = function_owner(cmd);
     if(owner && owner == environment(this_player())){
       int res = evaluate(cmd, str);
       if(res)
         return res;
     } else cmd = 0;
   }
   if ( in_command == str ) {
      in_command = 0;
      sscanf(str, "%s %*s", str);
      if (is_doing_alias(str)) {
         this_object()->add_failed_mess(this_object(),
             "Recursive aliases. Bad "+
             ({"thing","boy","girl"})[(int)this_object()->query_gender()]+
                ".\n", ({ }));
      }
      return 0;
   }
   if ( bypass_queue ) {
      bypass_queue = 0;
      return 0;
   }
   last_command = time();
   if ( this_object()->query_property( PASSED_OUT ) ||
         !interactive( this_object() ) ) {
      if ( ( str == "quit" ) || ( str == "quit_old" ) ) {
         return 0;
      }
      mess = this_object()->query_passed_out_message();
      if ( !stringp( mess ) ) {
         mess = "You are unconscious.  You can't do anything.\n";
      }
      write( mess );
      if ( !this_object()->query_creator() ) {
         return 1;
      }
      write( "On the other hand, you're a creator...\n" );
   }
   if ( ( str == "stop" ) || ( str == "restart" ) ) {
      remove_queue();
      return 0;
   }
   if ( stringp( str ) ) {
      if ( str[ 0 .. 4 ] == "stop " ) {
         return 0;
      }
   }
   if ( ( time_left < 0 ) ||
        (this_object()->queue_commands(str) &&
         !this_object()->query_creator()) ||
         ( !doing_it && ( sizeof( queued_commands ) ||
         ( find_call_out( flush_call_id ) != -1 ) ) ) ) {
      rabbit = explode(str, " ");
      if (rabbit[0] != upper_case(rabbit[0])) {
         write( "Queued command: "+ str +"\n" );
      }
      if ( str == "quit" ) {
         write( "If you are trying to quit and it is queueing things, use "
               "\"stop\" to stop your commands, and or \"restart\" to start "
               "your heartbeat.\n" );
      }
      if(sizeof(queued_commands) < 256) {
        if(sizeof(rabbit) > 1 && member_array(str, queued_commands) != -1)
          time_left -= (DEFAULT_TIME / 2);
        queued_commands += ({ str });
      }
      return 1;
   }
   if (interrupt) {
      call_interrupt(0, this_object());
   }
   interrupt = 0;
   in_command = str;
   if (sscanf(str, "%s %s", comm, arg) != 2) {
      comm = str;
      arg = "";
   }
   rabbit = run_alias(comm, arg);
   if (rabbit) {
      set_doing_alias(comm);
      green = queued_commands;
      queued_commands = ({ });
      foreach (comm in rabbit) {
         catch(command(comm));
      }
      queued_commands += green;
#if USE_ADD_ACTION
   } else if(sizeof(str) > 512) {
     write("Command too long.\n");
#endif
   } else {
      time_left -= DEFAULT_TIME;
      command(str);
   }
   if (interrupt && time_left >= 0) {
      call_interrupt(0, this_object());
   }
   return 1;
}
protected string process_input(string str) {
  float secs;
  int t = time_expression{
    reset_eval_cost();
    if (str[0] == '.')
      str = expand_history(str[1..]);
    else if (str[0] == '^')
      str = substitute_history(str[1..]);
    this_object()->add_history(str);
#if efun_defined(add_action)
    return str;
#else
    _process_input(str);
  };
  secs = t/1000000.0;
  if((secs > 1.0) &&
     (strlen(str) < 2 || str[0..1] != "su") &&
     str != "upgrade") {
    log_file("GARBAGE", "%s command: %s time: %:3f place: %s\n",
       ctime(time())[4..18], str, secs,
       file_name(environment()));
    if(this_object()->query_creator())
      printf("\nThat command froze the mud for %:3f "
       "seconds.\n\n", secs);
  }
  return 0;
#endif
}
#if !efun_defined(add_action)
protected mixed _process_input(string str){
  object ob;
  int i;
  string* bits;
  if(str == "") {
    return 0;
  }
  ob = this_player();
  efun::set_this_player(this_object());
  _notify_fail(0);
  while (str[0] == ' ') {
    str = str[1..];
  }
  if (str == ""){
      efun::set_this_player(ob);
      return 0;
    }
  while(str[<1] == ' ') {
    str = str[0..<2];
  }
  if (str == ""){
    efun::set_this_player(ob);
    return 0;
  }
  if (strsrch(str, "%^") != -1) {
    bits = explode("f" + str + "g", "%^");
    for (i = 1; i < sizeof(bits); i += 2) {
      if (bits[i][0..3] != "USER") {
         bits[i] = "USER_" + bits[i];
      }
    }
    bits[0] = bits[0][1..];
    bits[<1] = bits[<1][0..<2];
    str = implode(bits, "%^");
  }
  if(!drunk_check(str)) {
    if(!this_object()->exit_command(str)) {
      if(!this_object()->cmdAll(str)) {
        if(!this_object()->new_parser(str)) {
          if(!this_object()->lower_check(str)){
            if(!(str = query_notify_fail())){
              string *responses=({"What?", "Try something else."});
              receive(responses[random(sizeof(responses))]+"\n");
            } else {
              receive(str);
            }
            efun::set_this_player(ob);
            return 0;
          }
        }
      }
    }
  }
  efun::set_this_player(ob);
  return "bing";
}
protected mixed command(string cmd){
  int time = eval_cost();
  if(_process_input(cmd))
    return eval_cost() - time + 1;
  return 0;
}
#endif
int lower_check(string str) {
  query_time_left();
  return (str == "stop");
}

==================================================
FILE: pweath.c
==================================================

#include <weather.h>
#include <clothing.h>
#include <playtesters.h>
#define COMFORTABLE 20
int temperature;
string temperature_str;
int query_wetness()
{
   return 0;
}
void add_wetness(int arg)
{
}
void dry_out()
{
}
void set_personal_temp(int i)
{
   temperature = i;
}
void adjust_personal_temp(int i)
{
   temperature += i;
}
int query_personal_temp()
{
   return temperature;
}
string query_temp_str()
{
   if (!temperature_str || temperature_str == "") {
      return "quite comfortable";
   }
   return temperature_str;
}
int calc_personal_temp()
{
   mixed tmp;
   object where,
    *clothes;
   string item,
     zone,
     type,
    *types,
    *zones;
   int adjustment,
     room_temp,
     correction,
    *enums;
   if (this_object()->query_property("dead")) {
      temperature = 0;
      return 0;
   }
   where = environment(this_object());
   if (!where->query_property("location") &&
       environment(where) && environment(where)->query_property("location"))
      where = environment(where);
   switch (where->query_property("location")) {
   case "outside":
      room_temp = (WEATHER->query_temperature(where) - COMFORTABLE);
      break;
   default:
      room_temp = 0;
   }
   room_temp += where->query_property("warmth");
   room_temp -= where->query_property("cooling");
   adjustment = room_temp;
   adjustment += this_object()->query_property("warmth");
   adjustment -= this_object()->query_property("cooling");
   clothes = filter_array(this_object()->query_wearing(),
                          (: !$1->id("scabbard") &&
                             !$1->id("belt") &&
                             !$1->id("backpack") &&
                             !$1->id("glasses") && !$1->id("jewellery") :));
   zones = ({ });
   foreach(item in clothes) {
      tmp = item->query_type();
      if (arrayp(tmp))  types = tmp;
      else types = ({ tmp });
      foreach(type in types) {
         if (CLOTHING_HANDLER->query_equivilant_type(type))
            type = CLOTHING_HANDLER->query_equivilant_type(type);
         foreach(zone in CLOTHING_HANDLER->query_zone_names(type)) {
            if (member_array(zone, zones) == -1) {
               zones += ({ zone });
            }
            tmp = item->query_property("warmth");
            if (!tmp) {
               adjustment++;
            } else if (intp(tmp) && tmp) {
               adjustment += tmp;
            }
            if (room_temp > 0 && item->query_property("cooling")) {
               adjustment -= item->query_property("cooling");
            }
         }
      }
   }
   if (room_temp < 0) {
      adjustment += sizeof(zones);
      if (room_temp + sizeof(zones) > 5) {
         adjustment -= (room_temp + sizeof(zones) - 5);
      }
   } else {
      adjustment -= sizeof(zones);
      if (room_temp - sizeof(zones) < -5) {
         adjustment -= (room_temp - sizeof(zones) + 5);
      }
   }
   enums = (int *) this_object()->effects_matching("body.wetness");
   if (sizeof(enums)) {
      adjustment -= sqrt(sqrt((int) this_object()->arg_of(enums[0]))) * 2;
   }
   if (temperature > room_temp && room_temp >= 0 || temperature > 5) {
      correction -= (temperature / 5) + 5;
   }
   if (temperature < room_temp && room_temp <= 0 || temperature < -5) {
      correction -= (temperature / 5) - 5;
   }
#ifdef 0
   if ((room_temp < 10 && temperature >= 0) ||
       (room_temp > 10 && temperature <= 0)) {
      factor = (ABS(room_temp - temperature) / 10.0);
      if (factor > 1.0 || factor < 0.0)
         factor = 1.0;
   } else {
      factor = 1.0;
   }
   temperature += to_int((adjustment + correction) * factor);
#endif
   temperature += (adjustment + correction);
   temperature_str = (this_object()->query_race_ob())->
      temperature_effects(this_object(), temperature);
   return temperature;
}
string weather_extra_look()
{
   if (stringp(temperature_str) && strlen(temperature_str)) {
      return capitalize((string) this_object()->query_pronoun()) + " looks " +
         temperature_str + ".\n";
   }
   return "";
}

==================================================
FILE: shut.c
==================================================

inherit "/std/container";
#include <config.h>
int time_of_crash;
void setup() {
  if ( file_name( this_object() ) != "/global/shut" ) {
    write("This object can't be cloned.\n");
    dest_me();
    return;
    }
  set_name("offler");
  set_living_name("offler");
  add_adjective( ({ "offler", "the", "crocodile" }));
  add_alias("god");
  enable_commands();
  set_short( "Offler" );
  add_property( "determinate", "" );
  set_long("The Crocodile God.  He looks big, green, and, well "+
           "like this really.\n");
  add_alias("shut");
  move(CONFIG_START_LOCATION,
      "Offler the Crocodile God appears in a puff of smoke.",
      "Offler the Crocodile God appears in a puff of smoke.");
  reset_get();
}
#define ishout(str) shout("Offler the Crocodile God shouts: "+str+"\n")
void ashout( string words ) {
  int i;
  object *people;
  people = users();
  for ( i = 0; i < sizeof( people ); i++ )
    tell_object( people[ i ], "Offler the Crocodile God shouts: "+
        words +"\n" );
}
void heart_beat() {
  int time_to_crash;
  if (!time_of_crash) return;
  time_to_crash = time_of_crash - time();
  if (time_to_crash < 1) {
    call_out("end_it_all",0);
    set_heart_beat(0);
    return;
  }
  if (time_to_crash < 10)  {
    ashout( "Game reboot in "+ time_to_crash +" seconds." );
    return;
  }
  if (time_to_crash < 60 && time_to_crash % 10 < 2) {
    ashout( "Game is rebooting in "+ time_to_crash +" seconds." );
    return;
  }
  if (time_to_crash % 60 > 1) return;
  time_to_crash /= 60;
  if (time_to_crash > 30) {
    return ;
  }
  if(time_to_crash == 1)
  {
    ashout( "Game is rebooting in one minute." );
    return;
  }
  if (time_to_crash < 10 || !(time_to_crash % 10)) {
    ishout( "Game is rebooting in "+ time_to_crash +" minutes." );
    return;
  }
}
void shut(int minutes) {
  object *players;
  int i;
  string fname;
  if (!intp(minutes)) {
    write("Bad argument\n");
    return;
  }
  fname = file_name(previous_object());
  if (minutes <= 0) {
    write("No time given\n");
    return;
  }
  players = users();
  for (i=0;i<sizeof(players);i++)
    if (players[i]->query_creator())
      tell_object(players[i], "Offler the Crocodile God wishes you to know:\n"+
          "The mud is rebooting in "+ number_as_string( minutes ) +
          " minutes.\n" );
  set_long("He is firmly concentrating on counting.\n");
  if (time_of_crash)
    write( "There was already a reboot scheduled, set for "+
      (time_of_crash - time()) + " seconds.\n");
  time_of_crash = time() + minutes*60;
  set_heart_beat(1);
}
string long(string str, int dark) {
  ::long();
  if (time_of_crash && this_player()->query_wizard())
     return ::long(str,dark)+
            "Game reboot will be in " + ( time_of_crash - time() ) +
            " seconds.\n";
  return ::long(str,dark);
}
void end_it_all() {
  int i;
  object *obs;
  ishout("Shutdown now!");
  obs = users();
  for (i=0;i<sizeof(obs);i++)
    call_out("force_quit", i, obs[i]);
  call_out("blue", 10);
}
void force_quit(object ob) {
  if (!objectp(ob))
    return ;
  if (!ob->query_property("quiting frog"))
    ob->quit_alt();
}
void blue() {
  if (sizeof(users()) > 0 &&
      time() - time_of_crash < 120)
    call_out("blue", 10);
  else
    shutdown(0);
}
int query_time_to_crash() {
  if ( !time_of_crash ) {
    call_out( "dest_me", 1 );
    return 9999;
  }
  return time_of_crash - time();
}

==================================================
FILE: spells.c
==================================================

#include "spells.h"
nosave mixed *_spell_effects;
void create() {
  _spell_effects = ({ });
}
mixed query_effects() { return _spell_effects; }
int queue_commands() { return sizeof( _spell_effects ); }
int add_spell_effect(int no_rnds, string type, string name, object callee,
                     string func, mixed params) {
  int i,j;
   if (strsrch(file_name(this_object()),"global")==-1)
      tell_object(find_living("olorin"),
                  sprintf("add_spell_effect in %s\n",
                          file_name(this_object())));
  if ((i=member_array(type, _spell_effects)) != -1)
    if ((j=member_array(name, _spell_effects[i+1])) == -1)
      _spell_effects[i+1] += ({ name, ({ no_rnds, callee, func, params }) });
    else
      _spell_effects[i+1][j+1] = ({ no_rnds, callee, func, params });
  else
    _spell_effects += ({ type, ({ name, ({ no_rnds, callee, func, params }) }) });
}
int remove_spell_effect(string name) {
  int i, j;
   if (strsrch(file_name(this_object()),"global")==-1)
      tell_object(find_living("olorin"),
                  sprintf("remove_spell_effect in %s\n",
                          file_name(this_object())));
  for (i=0;i<sizeof(_spell_effects);i+=2)
    if ((j=member_array(name, _spell_effects[i+1])) != -1) {
      _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2);
      if (!sizeof(_spell_effects[i+1])) {
        _spell_effects = delete(_spell_effects, i, 2);
        i -= 2;
      }
    }
  return 1;
}
mixed query_spell_effect(string name) {
   int i;
   if (strsrch(file_name(this_object()),"global")==-1)
      tell_object(find_living("olorin"),
                  sprintf("query_spell_effect in %s\n",
                          file_name(this_object())));
  if ((i=member_array(name, _spell_effects)) == -1)
    return 0;
  if (sizeof(_spell_effects[i+1]))
    return _spell_effects[i..i]+_spell_effects[0..1];
  return 0;
}
mixed *query_spell_effects_type(string type) {
  int i, j;
  mixed *ret;
  if ((i=member_array(type, _spell_effects)) == -1)
    return ({ });
  ret = ({ });
  for (j=0;j<sizeof(_spell_effects);j+=2)
    ret += ({ _spell_effects[i], _spell_effects[i+1][j..j+1] });
  return ret;
}
int do_spell_effects(object attacker) {
  int i, j;
  this_object()->remove_property("casting");
  for (i=0;i<sizeof(_spell_effects);i+=2)
    for (j=0;j<sizeof(_spell_effects[i+1]);j+=2) {
      call_out("do_call_out_effect", 1, ({ _spell_effects[i+1][j+1], attacker }));
      _spell_effects[i+1][j+1][SP_NO_RNDS]--;
      if ( !_spell_effects[i+1][j+1][SP_NO_RNDS] || !_spell_effects[i+1][j+1][SP_OBJECT]) {
        _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2);
        j -= 2;
        if (!sizeof(_spell_effects[i+1])) {
          _spell_effects = delete(_spell_effects, i, 2);
          i -= 2;
          break;
        }
      }
    }
    return 0;
}
void do_call_out_effect(mixed *params) {
  if (params[0][SP_OBJECT])
    call_other(params[0][SP_OBJECT],
             params[0][SP_FUNC],
             params[1],
             params[0][SP_PARAM],
             params[0][SP_NO_RNDS]);
}

==================================================
FILE: start_position.c
==================================================

inherit "/std/basic/virtual_quit_control";
#include <playerinfo.h>
#include <config.h>
#define MULTIPLAYER "/obj/handlers/multiplayer"
private int  *saved_co_ords;
private string last_pos;
private string *starts;
protected void inform_entered_game();
int query_creator();
string query_name();
string query_cap_name();
string the_short();
varargs int move(string pos, string messin, string messout);
string query_nationality_start_location();
void create() {
   starts = ({ });
}
int *query_saved_co_ords() { return saved_co_ords; }
protected void set_last_pos(string pos) {
  if(pos[0..4] != "/room")
    last_pos = pos;
}
string query_last_pos() {
   return last_pos;
}
string query_start_pos() {
   string start_pos;
   if ( !sizeof( starts ) ) {
      start_pos = query_nationality_start_location();
   } else {
      start_pos = starts[ 0 ];
   }
   if ( !find_object( start_pos ) ) {
      if ( catch( call_other( start_pos, "??" ) ) ) {
         start_pos = query_nationality_start_location();
      }
   }
   return start_pos;
}
string *query_starts() {
   return starts;
}
void reset_starts() { starts = ({ }); }
void add_start( string start_file, string start_desc ) {
   if ( !starts ) {
      starts = ({ });
   }
   if ( member_array( start_file, starts ) != -1 ) {
      return;
   }
   starts += ({ start_file, start_desc });
}
void remove_start( string start_file ) {
   int i;
   if ( !starts ) {
      return;
   }
   i = member_array( start_file, starts );
   if ( i == -1 ) {
      return;
   }
   starts = delete( starts, i, 2 );
}
void set_start_location( string start_file ) {
  int i;
  if ( !starts) {
    return ;
  }
  i = member_array(start_file, starts);
  if (i <= 0) {
    return ;
  }
  starts = starts[i..i + 1] + starts[0..i - 1] + starts[i + 2..];
}
protected void move_to_start_pos() {
   if (!last_pos || catch(call_other(last_pos, "??"))) {
      last_pos = query_start_pos();
      saved_co_ords = 0;
   }
   move(last_pos);
   if ( !last_pos->query_co_ord() && !last_pos->query_property( "no map" ) &&
         saved_co_ords && !query_creator() ) {
      last_pos->set_co_ord( saved_co_ords );
   }
   inform_entered_game();
}
private function query_extra_login_stuff(string start) {
   string ip_str;
   object *obs;
   object mph;
   string alert;
   int num;
   string *dups;
   switch (this_object()->query_invis()) {
      case 3 :
         start += " (trustee invisible)";
         break;
      case 2 :
         start += " (director invisible)";
         break;
      case 1 :
         start += " (invisible)";
         break;
   }
   mph = load_object(MULTIPLAYER);
   obs = filter(users() - ({ this_object() }),
                (: query_ip_number($1) == query_ip_number(this_object()) &&
                   !$1->query_login_ob() :));
   if (sizeof(obs) &&
       sizeof((dups = mph->check_allowed(this_object(), obs)))) {
      ip_str = " (" + query_ip_name(this_object()) + ")";
      ip_str += " Duplicate: " + query_multiple_short(dups);
   }
   if (!catch(num = PLAYERINFO_HANDLER->query_alerts_for(query_name()))) {
      if (num > 0) {
         alert = " %^BOLD%^%^RED%^" + num + " alert";
         if (num > 1) {
            alert += "s";
         }
         alert += "%^RESET%^";
      }
   }
   if (ip_str) {
      if (!alert) {
         alert = "";
      }
      return (: $(start) +
                       ($1->query_creator()?$(ip_str) + $(alert):"") :);
   } else {
      if (alert) {
         return (: $(start) + ($1->query_creator()?$(alert):"") :);
      } else {
         return (: $(start) :);
      }
   }
}
protected void inform_entered_game() {
   string logon_str;
   if ("/d/liaison/master"->query_member( query_name() ) ) {
      logon_str = query_cap_name() + " enters "
           "" + mud_name() + " %^YELLOW%^(Liaison)";
   } else {
      logon_str = query_cap_name() + " enters " +
           ( this_object()->query_property( "guest" ) ? "as a guest of " : "" ) +"" + mud_name() + ""+
           ( this_object()->query_property( "new player!" ) ? " (new player)" : "" );
   }
   user_event( this_object(), "inform",
               query_extra_login_stuff(logon_str),
               "logon", this_object());
   say(the_short()+" enters the game.\n", 0);
   last_pos->enter(this_object());
}
void inform_reconnect_game() {
   user_event( "inform",
         query_extra_login_stuff(query_cap_name() +
         " reconnects"), "link-death", this_object() );
}
void check_last_pos() {
   last_pos = find_start_pos(this_object(), environment());
   saved_co_ords = find_start_coord(this_object(), environment());
}

==================================================
FILE: telnet.c
==================================================

#include "telnet.h"
nosave string last_term;
nosave int got_terminal;
void check_terminal_type(string type);
void telnet_suboption(string str) {
  switch (str[0]) {
    case TELOPT_TTYPE :
      if (str[1] != TELQUAL_IS)
        return ;
      check_terminal_type(str[2..1000]);
      break;
  }
}
void player_connected() {
  printf("%c%c%c", IAC, DO, TELOPT_TTYPE);
  printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE);
}
void check_terminal_type(string type) {
  if (last_term == type) {
    if (!got_terminal)
      this_object()->set_network_terminal_type(0);
    return ;
  }
  if (!got_terminal && this_object()->set_network_terminal_type(type))
    got_terminal = 1;
  printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE);
  last_term = type;
}

==================================================
FILE: wiz_channels.c
==================================================

#include <broadcaster.h>
#include <creator.h>
#include <network.h>
#include <newudp.h>
#define TALKER "/std/shadows/object/talker"
#define BEEP sprintf("%c",7)
#define CHAN_OK 1
#define CHAN_FORCED 2
#define CHAN_EMOTED 4
#define CHAN_QUERY 8
private int channel_cmd(string mess);
private int channel_hist();
nomask string *channel_list() {
  string channel, *tmp, *channels;
  tmp = "/secure/master"->query_domains();
  tmp -= NO_CHANNELS;
  channels = ({ });
  foreach(channel in tmp)
    if("/secure/master"->query_senior(this_object()->query_name()) ||
       ("/d/"+channel+"/master")->query_member(this_object()->query_name()))
      channels += ({ channel });
  channels += ADDITIONAL_CHANNELS + keys(INTERMUD_MAP);
  if(this_object()->query_lord())
    channels += ({ "lord" });
  return channels;
}
void wiz_commands() {
  string channel;
  foreach(channel in channel_list()) {
    add_command(channel, "<string'mess'>", (: channel_cmd($4[0]) :));
    add_command(channel+"@", "<string'mess'>", (: channel_cmd("@"+$4[0]) :));
    add_command(channel+"?", "", (: channel_cmd("?") :));
    if(!INTERMUD_MAP[channel]) {
      add_command(channel+"!", "", (: channel_cmd("!") :));
      add_command("h"+channel, "", (: channel_hist() :));
    }
  }
}
private void my_mess(string fish, string erk) {
  int bing;
  if (!interactive(this_player())) {
    return;
  }
  bing = strlen(fish);
  if (bing > 15) {
    bing = 15;
  }
  efun::tell_object(this_player(),
                    this_player()->fix_string(sprintf("%s%s\n", fish, erk),
                                              (int)this_player()->query_cols(),
                                              bing));
}
protected int handle_command_line(string channel, string mess) {
  int retval;
  function map_func;
  int i;
  object *people, *off_line;
  add_failed_mess("Syntax: "+channel+"[@|?] [text]\n");
  if(!channel || !mess) {
    return 0;
  }
  if(member_array(channel, channel_list()) == -1) {
    add_failed_mess("No such channel " + channel + ".\n");
    return 0;
  }
  switch (mess[0]) {
  case '!' :
    retval |= CHAN_FORCED;
    break;
  case '@' :
    retval |= CHAN_EMOTED;
    break;
  case '?' :
    if (mess == "?") {
      if(INTERMUD_MAP[channel]) {
        SERVICES_D->eventSendChannelWhoRequest(INTERMUD_MAP[channel]);
        retval |= CHAN_QUERY;
        return retval;
      }
      people = filter(users(), (: $1 && $1->query_creator() &&
                                $1->query_visible(this_object()) :));
      off_line = ({ });
      for (i=0;i<sizeof(people);i++) {
        if(!people[i] || !people[i]->channel_list() ||
           member_array(channel, people[i]->channel_list()) == -1) {
          people = delete(people, i, 1);
          i--;
        } else if(people[i]->check_earmuffs(channel) ||
                  (member_array(channel, keys(INTERMUD_MAP)) != -1 &&
                   people[i]->check_earmuffs("intermud-all"))) {
          off_line += ({ people[i] });
          people = delete(people, i, 1);
          i--;
        }
      }
      people = sort_array(people, (: strcmp($1->query_name(),
                                            $2->query_name()) :) );
      off_line = sort_array(off_line, (: strcmp($1->query_name(),
                                                $2->query_name()) :) );
      map_func = function (object ob) {
        string str;
        if (ob->query_invis()) {
          if (ob->query_invis() == 2) {
            str = "({" + $1->query_cap_name() + "})";
          } else {
            str = "(" + $1->query_cap_name() + ")";
          }
        } else {
          str = $1->query_cap_name();
        }
        if (query_idle(ob) > 120) {
          int hours, mins, secs;
          secs = query_idle(ob);
          mins = secs / 60;
          secs %= 60;
          hours = mins / 60;
          mins %= 60;
          if ( !hours )  {
            str += sprintf(" [%02dm]", mins);
          } else {
            str += sprintf(" [%02dh:%02dm]", hours, mins);
          }
        }
        return str;
      };
      people = map(people, map_func);
      off_line = map(off_line, map_func);
      if (sizeof(people)) {
        write(sprintf( "On line: %-=" + (this_player()->query_cols() - 10) +
                       "s", query_multiple_short( people ) +".\n"));
      }
      if (sizeof(off_line)) {
        write(sprintf( "Off line: %-=" + (this_player()->query_cols() - 11) +
                       "s", query_multiple_short( off_line ) +".\n"));
      }
      retval |= CHAN_QUERY;
    }
    break;
  default :
    return CHAN_OK;
    break;
  }
  return retval;
}
private int channel_cmd(string mess) {
  int flags;
  string pad = " ";
  string start;
  string channel;
  object *things;
  channel = query_verb();
  if(channel[<1] == '?' || channel[<1] == '@' || channel[1] == ':') {
    channel = channel[0..<2];
  }
  flags = handle_command_line(channel, mess);
  if (!flags) {
    return 0;
  }
  if (flags & CHAN_QUERY) {
    return 1;
  }
  if(mess[0] == '!' || mess[0] == '@' || mess[0] == '?') {
    mess = mess[1..1000];
  }
  if (mess[0] == ' ') {
    mess = mess[1..1000];
  }
  if (mess == "") {
    return 0;
  }
  if (this_object()->check_earmuffs(channel)) {
    write("Why use " + channel + "-tell when you can't hear a response?\n");
    return 1;
  }
  mess = replace(mess, BEEP, "");
  if (mess[0..0] == "'") {
    pad = "";
  }
  if (flags & CHAN_EMOTED) {
    start = this_object()->query_cap_name() + pad;
    if(INTERMUD_MAP[channel])
      SERVICES_D->eventSendChannel((string)this_player()->query_cap_name(),
                                   INTERMUD_MAP[channel], "$N " + mess,
                                   flags & CHAN_EMOTED);
    else
      my_mess("(" + channel + ") "+
              ((string)this_object()->query_cap_name()) + pad,
              mess);
  } else {
    start = this_object()->query_cap_name() +": ";
    if(INTERMUD_MAP[channel])
      SERVICES_D->eventSendChannel((string)this_player()->query_cap_name(),
                                   INTERMUD_MAP[channel], mess,
                                   flags & CHAN_EMOTED);
    else
      my_mess("You " + channel + "-tell: ", mess);
  }
  if(INTERMUD_MAP[channel]) {
    user_event(this_object(), "intermud_tell", start, mess, channel);
    if(channel == "dwchat") {
      things = children(TALKER);
      things -= ({ find_object(TALKER) });
      if ( flags & CHAN_EMOTED ) {
        mess = ":" + mess;
      }
      things->receive("intermud", this_object()->query_cap_name(),
                       mess);
    }
  } else {
    user_event(this_object(), "creator_tell", start, mess,
                flags & CHAN_FORCED, channel);
    HIST_HANDLER->add_chat_history(channel, start, mess);
  }
  return 1;
}
private int channel_hist() {
  int i;
  mixed *hist;
  string channel;
  channel = query_verb()[1..];
  hist = HIST_HANDLER->query_chat_history(channel);
  if (!pointerp(hist) || !sizeof(hist)) {
    return notify_fail("Nobody said anything on the " + channel +
                       " channel.\n");
  }
  write("The " + channel + " channel history is:\n");
  for (i=0;i<sizeof(hist);i++) {
    if (sizeof(hist[i]) > 2) {
      efun::tell_object(this_object(),
                        this_object()->fix_string(sprintf("*%s* %s%-=*s\n",
                ctime(hist[i][2])[11..18], hist[i][0],
                (int)this_object()->query_cols()-strlen(hist[i][0])-11,
                                                          hist[i][1])));
    } else {
      efun::tell_object(this_object(),
                        (string)this_object()->fix_string(sprintf("%s%-=*s\n",
               hist[i][0], (int)this_object()->query_cols()-strlen(hist[i][0]),
                hist[i][1])));
    }
  }
  return 1;
}

==================================================
FILE: wiz_file_comm.c
==================================================

#include <creator.h>
#include <login_handler.h>
#include <ls.h>
#include <playtesters.h>
#include <player_handler.h>
#include <cmds/friends.h>
#ifdef USE_LE
inherit "/global/le";
#endif
inherit "/global/wiz_object_comm";
inherit "/global/playtester";
inherit "/global/wiz_info_comm";
inherit "/global/wiz_channels";
inherit "/global/wiz_inter_comm";
private int invis;
private string *allowed;
private nosave mixed _in_wiz_editor;
private nosave string *dir_list;
private nosave mixed last_location;
private int change_dir(string str);
private int pushd(string str);
private int popd();
protected int set_home_dir(string str);
private int visible();
private int invisible(string level);
private int allow(string word);
private int disallow(string word);
void create() {
   playtester::create();
   wiz_object_comm::create();
   allowed = ({ });
}
protected void wiz_commands() {
   wiz_object_comm::wiz_commands();
   wiz_info_comm::wiz_commands();
   wiz_inter_comm::wiz_commands();
   wiz_channels::wiz_commands();
#ifdef USE_LE
   le::le_commands();
#endif
   add_command("cd", this_object(), "<string'directory'>", (: change_dir($4[0]) :));
   add_command("cd", this_object(), "", (: change_dir(0) :));
   add_command("pushd", this_object(), "<string'directory'>", (: pushd($4[0]) :));
   add_command("pushd", this_object(), "", (: pushd(0) :));
   add_command("popd", this_object(), "", (: popd() :));
   add_command("homedir", this_object(), "<string'directory'>", (: set_home_dir($4[0]) :));
   add_command("visible", this_object(), "", (: visible() :));
   add_command("vis", this_object(), "", (: visible() :));
   add_command("invisible", this_object(), "{1|2|3}", (: invisible($4[0]) :));
   add_command("invis", this_object(), "", (: invisible("1") :));
   if (this_player()->query_director()) {
      add_command("invis", this_object(), "{1|2|3}", (: invisible($4[0]) :));
   }
   add_command("allow", this_object(), "<word'name'>", (: allow($4[0]) :));
   add_command("allow", this_object(), "", (: allow(0) :));
   add_command("disallow", this_object(), "<word'name'>", (: disallow($4[0]) :));
   add_command("disallow", this_object(), "all", (: disallow("all") :));
}
nomask int query_invis() {
  return invis;
}
protected void set_invis(int level) {
   invis = level;
}
nomask string *query_allowed() {
  return copy(allowed);
}
int is_friend(string str) {
   return ::is_friend(str) ||
          member_array(str, allowed) != -1;
}
string query_friend_tag(string str) {
   string womble;
   if(!userp(previous_object())) {
     womble = ::query_friend_tag(str);
     if (!womble) {
       if (member_array(str, allowed) != -1) {
         return "allowed to reference";
       }
     }
     return womble;
   }
   return "";
}
string* query_friends() {
   if (file_name(previous_object()) == FRIENDS_CMD) {
      return ::query_friends() | allowed;
   }
   return ({ });
}
private int visible() {
   if (GetForced()) {
      return 0;
   }
   if (!query_invis()) {
      return notify_fail("You are already visible.\n");
   }
   if (invis >= 2) {
      invis = 0;
      LOGIN_HANDLER->player_logon(this_player()->query_name());
   } else {
      invis = 0;
   }
   write("You appear.\n");
   return 1;
}
private int invisible( string word ) {
   int max, type;
   if (GetForced()) {
      return 0;
   }
   if (!word) {
      word = sprintf("%d", query_invis());
      if (word == "0") {
         word = "1";
      }
   }
   max = 1 + (int)master()->query_director(query_name()) +
      (int)master()->query_trustee(query_name());
   if (!sscanf(word, "%d", type) || (type > max) || (type < 1)) {
      return notify_fail("Syntax: invisible [1"+ ( max > 1 ? "|2" : "" ) +
                         ( max > 2 ? "|3" : "" ) + "]\n");
   }
   word = ({ "frog", "creator", "director", "trustee" })[type];
   if (type == query_invis()) {
      return notify_fail("You are already "+ word +" invisible.\n");
   }
   if (type < invis && type < 2 && invis >= 2) {
      invis = type;
      LOGIN_HANDLER->player_login(this_player()->query_name());
   } else {
      invis = type;
   }
   write("You become "+ word +" invisible.\n");
   return 1;
}
private int allow(string word) {
    string player, mud;
   if (!word) {
      if (!sizeof(allowed)) {
         write("You are not allowing anyone to refer to you.\n");
      } else {
         write("You are currently allowing "+
               query_multiple_short( map_array( sort_array(allowed, 0),
                                                (: capitalize( $1 ) :))) +
               " to refer to you.\n" );
      }
      return 1;
   }
   word = lower_case(word);
   if ( word != "playtesters" && !PLAYER_HANDLER->test_user(word) &&
       sscanf( word, "%s@%s", player, mud ) != 2 ) {
      return notify_fail("There is no user called $C$"+ word +".\n");
   }
   if (member_array(word, allowed) != -1) {
      return notify_fail("You have already allowed $C$"+ word +
                         " to refer to you.\n");
   }
   allowed += ({ word });
   write(word +" is now allowed to refer to you.\n");
   return 1;
}
private int disallow(string word) {
   if (!word) {
      return notify_fail("Disallow who?\n");
   }
   if (word == "all") {
     allowed = ({ });
     write("Cleared your allow list.\n");
   } else {
     word = lower_case(word);
     allowed -= ({ word });
     write(word +" is no longer allowed to refer to you.\n");
   }
   return 1;
}
int query_visible(object thing) {
   string word;
   if (thing == this_object()) {
      return 1;
   }
   word = (string)thing->query_name();
   if (member_array(word, allowed) != -1) {
      return ::query_visible(thing);
   } else if((member_array("playtesters", allowed) != -1) &&
             PLAYTESTER_HAND->query_playtester(word)) {
     return ::query_visible(thing);
   }
   switch (query_invis()) {
   case 3 :
      return (int)master()->query_trustee(word);
   case 2 :
      return (int)master()->query_director(word);
   case 1 :
      return (int)thing->query_creator();
   default :
      return ::query_visible(thing);
   }
}
mixed query_in_editor() {
   return _in_wiz_editor || ::query_in_editor();
}
void set_in_editor(mixed what) {
   _in_wiz_editor = what;
}
private int change_dir(string str) {
   string *filenames;
   object *obs;
   if (GetForced()) {
      return 0;
   }
   if (!str) {
      if (!query_home_dir()) {
         add_failed_mess(this_object(),
                         "No homedir.  Use homedir to set it.\n", ({ }));
         return 0;
      }
      str = query_home_dir();
   }
   else {
      if ( this_object()->query_property( LS_COMMAND_NICKNAME_PROPERTY ) ) {
         str = this_object()->expand_nickname( str );
      }
   }
   filenames = get_files(str);
   if (sizeof(filenames) > 1) {
      add_failed_mess(this_object(),
                      "Ambiguous directory.\n", ({ }));
      return 0;
   }
   if (!sizeof(filenames)) {
      if (!sizeof(obs = WIZ_PRESENT->wiz_present(str, this_object()))) {
         add_failed_mess(this_object(),
                         "No such dir.\n", ({ }));
         return 0;
      }
      if (sizeof(obs) > 1) {
         add_failed_mess(this_object(),
                         "Ambiguous directory.\n", ({ }));
         return 0;
      }
      filenames =
         map(obs,
             (: sprintf("/%s",implode(explode(file_name($1), "/")[0..<2],
                                      "/")) :));
   }
   str = filenames[0];
   if (file_size(str) != -2) {
      printf("cd: %s: Not a directory.\n", str);
   } else {
      set_current_path(str);
   }
   printf("%s\n", query_current_path());
   return 1;
}
private int pushd(string str) {
   if (!dir_list) {
      dir_list = ({ });
   }
   dir_list += ({ query_current_path() });
   return change_dir(str);
}
private int popd() {
   string dest;
   if (!sizeof(dir_list)) {
      return 0;
   }
   dest = dir_list[sizeof(dir_list)-1];
   dir_list = delete(dir_list, sizeof(dir_list)-1, 1);
   return change_dir(dest);
}
string query_path() {
   return query_current_path();
}
private int set_home_dir(string str) {
   if (GetForced()) {
      return 0;
   }
   if (str) {
      ::set_home_dir(get_path(str));
   }
   printf("Home directory set to %s.\n", query_home_dir());
   return 1;
}
int query_ed_setup() {
   return query_property("ed_setup");
}
void set_ed_setup(int i) {
   add_property("ed_setup", i);
}
int review() {
   playtester::review();
   wiz_info_comm::review();
   return 1;
}
void set_last_location(mixed loc) { last_location = loc; }
mixed query_last_location() { return last_location; }
protected string process_input(string inp){
  int start;
  start = strsrch(inp, '@');
  if(start > 0){
    int space = strsrch(inp, ' ');
    if(!(space > 0 && ((space == start+1) || space < start))){
      inp = inp[0..start] + " " + inp[start+1..];
    }
  }
  start = strsrch(inp, '`');
  if(start > 0){
    int end;
    end = strsrch(inp, '`', -1);
    if(end != start){
      string lpc = inp[start+1..end-1];
      string err;
      mixed ret;
      ret = "/secure/cmds/creator/exe_c"->do_exec("return "+lpc, ref err);
      if(!err){
        if(intp(ret))
          ret = ""+ret;
        if(objectp(ret))
           ret = file_name(ret);
        if(arrayp(ret)){
          ret = filter(ret, (:stringp($1) || intp($1) || objectp($1):));
          ret = map(ret, (:intp($1)?""+$1:(objectp($1)?file_name($1):$1):));
          if(sizeof(ret))
            ret = implode(ret, ",");
        }
        if(stringp(ret)){
          inp = inp[0..start-1] + ret + inp[end+1..];
        }
      }
    }
  }
  return ::process_input(inp);
}
protected mixed command( string txt ) {
    return ::command( txt );
}

==================================================
FILE: wiz_info_comm.c
==================================================

#define PEOPLER "/obj/handlers/peopler"
protected int do_gauge(string str);
int add_command(string name, object ob, string format, function func);
protected void wiz_commands() {
  add_command("gauge", this_object(), "<string>", (: do_gauge($4[0]) :));
  if(clonep())
    call_out("driver_version", 20);
}
int driver_version(){
  string old = this_object()->query_property("driver_version");
  if(!old) {
    return this_object()->add_property("driver_version", __VERSION__);
  }
  if(old != __VERSION__){
    this_object()->add_property("driver_version", __VERSION__);
    write("%^RED%^The driver has been changed to version " +
          __VERSION__ + ", see /doc/driver/Changes for more information.%^RESET%^\n");
  }
  return 1;
}
int review() {
  PEOPLER->review();
  return 1;
}
protected int do_gauge(string str) {
  int eval_cost;
  if (this_player(1) != this_object()) return 0;
  if(!str) {
    notify_fail("Usage : gauge command.\n");
    return 0;
  }
  eval_cost = command(str);
  write("\nThe command '" + str + "' took: " + eval_cost + " CPU cycles.\n");
  return 1;
}

==================================================
FILE: wiz_inter_comm.c
==================================================

#include <network.h>
private nosave string *imud_ignored;
int do_block(string);
int do_unblock(string);
void wiz_commands() {
  add_command("block", "", (:do_block(0):));
  add_command("block", "<word'name'>", (:do_block($4[0]):));
  add_command("unblock", "<word'name'>", (:do_unblock($4[0]):));
}
int do_block(string str) {
  if (!str) {
    if (!sizeof(imud_ignored)) {
      write("Not blocking anyone.\n");
      return 1;
    }
    write("Blocking "+query_multiple_short(imud_ignored)+".\n");
    return 1;
  }
  if (!pointerp(imud_ignored))
    imud_ignored = ({ lower_case(str) });
  else
    imud_ignored += ({ lower_case(str) });
  write("Okay, now ignoring intermud channel messages from "+str+".\n");
  write("Use \"unblock\" to remove.\n");
  return 1;
}
int do_unblock(string str) {
  int idx;
  if (!str)
    return notify_fail("Syntax: unblock <name>|all\n");
  if (!pointerp(imud_ignored) || !sizeof(imud_ignored))
    return notify_fail("You are not blocking anyone.\n");
  if (str == "all") {
    imud_ignored = 0;
    write("Okay, unblocked everyone.\n");
    return 1;
  }
  if ((idx = member_array(lower_case(str), imud_ignored)) == -1)
    return notify_fail("You are not blocking "+str+".\n");
  imud_ignored = delete(imud_ignored, idx, 1);
  write("Okay, removed "+str+" from your blocked list.\n");
  return 1;
}
int check_not_ignored(string who) {
  if (!pointerp(imud_ignored))
    return 1;
  return member_array(lower_case(who), imud_ignored) == -1;
}

==================================================
FILE: wiz_object_comm.c
==================================================

#include <creator.h>
private nosave mapping obvar;
void create() {
   obvar = ([ ]);
}
protected void wiz_commands() {
}
int affirmative(string s)
{
    s = lower_case(s);
    return (s == "y" || s == "yes" || s == "ok" || s == "please");
}
void handle_error(string erm, string desc) {
    if (erm) {
         write(desc + " failed : " + erm);
    }
}
void set_obvar(string key, object value) {
  obvar[key] = value;
}
void del_obvar(string key) {
  map_delete(obvar, key);
}
object get_obvar(string key) {
  return obvar[key];
}
mapping get_obvars() {
  return obvar;
}
string desc_object(mixed o) {
  log_file("WIZ_PRESENT", sprintf("desc_object() called by %O.\n",
      previous_object()));
  return "";
}
string desc_f_object(mixed o) {
  log_file("WIZ_PRESENT", sprintf("desc_f_object() called by %O.\n",
      previous_object()));
  return "";
}
object *wiz_present(string str, object onobj, int nogoout) {
  log_file("WIZ_PRESENT", sprintf("wiz_present() called by %O.\n",
      previous_object()));
  return ({});
}

==================================================
FILE: wiz_present.c
==================================================

#include <obj_parser.h>
string desc_object(mixed o){
  string str;
  if (!o) return "** Null-space **";
  if (!catch(str = (string)o->short()) && str) return str;
  if (!catch(str = (string)o->query_name()) && str) return str;
  return file_name(o);
}
string desc_f_object(object o){
  string str, tmp;
  str = desc_object(o);
  if (o && str != file_name(o)) {
    if (tmp)
      str += " (" + tmp + ")";
    else
      str += " (" + file_name(o) + ")";
  }
  return str;
}
object *wzpresent2(string str, mixed onobj) {
  object *obs, ob, *obs2, obj;
  string s1;
  class obj_match result;
  if (pointerp(onobj)) {
    obs = ({ });
    foreach(ob in onobj)
      obs += wzpresent2(str,ob);
    return obs;
  }
  if (str == "all")
    return all_inventory(onobj);
  if (sscanf(str,"every %s",s1) == 1) {
    obs2 = all_inventory(onobj);
    obs = ({ });
    foreach (ob in obs2)
      if (ob->id(s1)) obs += ({ ob });
    return obs;
  }
  result = (class obj_match)match_objects_in_environments(str,onobj);
  if (result->result == OBJ_PARSER_SUCCESS ||
      result->result == OBJ_PARSER_AMBIGUOUS) {
    return result->objects;
  }
  if (obj = present(str,onobj)) return ({ obj });
  for (obj = first_inventory(onobj); obj; obj = next_inventory(obj)) {
    s1 = file_name(obj);
    if (sscanf(s1, "%*s/"+str+"#%*d") || sscanf(s1, "%*s#"+str))
      return ({ obj });
  }
  return ({ });
}
varargs object *wiz_present(string str, object onobj, int nogoout) {
  int j;
  object ob, *obs, *obs2;
  string s1, s2, *sts;
  mixed thing;
  class obj_match result;
  if (!str || !onobj)
    return ({ });
  seteuid(geteuid(this_player()));
  if(str[0] == '@') {
    if (ob = find_living(
        (string)this_player()->expand_nickname(extract(str, 1))))
      return ({ ob });
    notify_fail("Unable to find living object: "+extract(str,1)+".\n");
    return ({ });
  }
  if (str == "me") return ({ this_player() });
  if (str == "here") return ({ environment(this_player()) });
  if( str == "everyone") {
    if(!this_object()->query_lord())
      return ({ });
    obs = users();
    if(nogoout)
      return filter( obs, (: environment( $1 ) == $(onobj) :) );
    return obs;
  }
  if( str == "creators" ) {
    obs = filter( users(), (: $1->query_creator() :) );
    if(nogoout)
      return filter( obs, (: environment( $1 ) == $(onobj) :) );
    return obs;
  }
  if(str[0] == '/') {
    if (ob = find_object(str)) return ({ ob });
    if (sizeof((sts = (string *)this_player()->get_cfiles(str))))  {
      obs = ({ });
      obs = map(sts, (: find_object($1) :)) - ({0});
      return obs;
    }
    notify_fail("No loaded object: "+str+".\n");
    return ({ });
  }
  if (str[0] == '(' && str[strlen(str) - 1] == ')') {
    obs = wiz_present(extract(str,1,strlen(str) - 2),onobj);
    if (!sizeof(obs)) return obs;
    obs = map(obs, (: environment($1) :)) - ({0});
    return obs;
  }
  if (sscanf(str,"%s on %s",s1,s2) == 2 ||
      sscanf(str,"%s in %s",s1,s2) == 2) {
    obs = wiz_present(s2, onobj);
    if (!sizeof(obs)) return obs;
    obs2 = ({ });
    foreach (ob in obs)
      obs2 += wiz_present(s1, ob, 1);
    return obs2;
  }
  if (sscanf(str,"%s and %s",s1,s2) == 2) {
    obs = wiz_present(s1, onobj);
    obs2= wiz_present(s2, onobj);
    obs2 += filter(obs, (: member_array($1, $(obs2)) < 0 :));
    return obs2;
  }
  if (sscanf(str,"%s except %s",s1,s2) == 2 ||
      sscanf(str,"%s but %s",s1,s2) == 2) {
    obs = wiz_present(s1, onobj);
    obs2= wiz_present(s2, onobj);
    foreach (ob in obs2)
      while ((j=member_array(ob, obs)) > -1)
        obs = delete(obs,j--,1);
    return obs;
  }
  if (sscanf(str, "env of %s", s1) == 1) {
    obs = wiz_present(s1, onobj);
    if (!sizeof(obs)) {
       return obs;
    }
    return map(obs, (: environment($1) :)) - ({0});
  }
  if (sscanf(str, "children of %s", s1) == 1) {
    obs = wiz_present(s1, onobj);
    obs2 = ({ });
    foreach (ob in obs) {
      s1 = file_name(ob);
      sscanf(s1, "%s#%*d", s1);
      obs2 += children(s1);
    }
    return obs2;
  }
  if (sscanf(str,"player %s",s1)) {
    return ({ find_player(s1) });
  }
  if (!sizeof(obs2 = wzpresent2(str,onobj)) && !nogoout) {
    obs2 = wzpresent2(str, environment(onobj));
  }
  if (sizeof(obs2)) {
    return obs2;
  }
  result = (class obj_match)match_objects_in_environments(str,onobj);
  if (result->result == OBJ_PARSER_SUCCESS ||
      result->result == OBJ_PARSER_AMBIGUOUS) {
    return result->objects;
  }
  ob = find_living( this_player()->expand_nickname(str) );
  if( ob && ( !nogoout || ( environment(ob) == onobj ) ) )
    return ({ ob });
  if (thing = this_player()->get_obvar(str)) {
    if (objectp(thing)) return ({ thing });
    if (pointerp(thing)) {
      return filter( thing, (: objectp( $1 ) :) );
    }
  }
  if (sizeof((sts = (string *)this_player()->get_cfiles(str))))  {
    obs = ({ });
    obs = map(sts, (: find_object($1) :)) - ({0});
    return obs;
  }
  return ({ });
}

==================================================
FILE: virtual/c_compiler.c
==================================================

#include "virtual.h"
void initialize_methods();
void create() {
    initialize_methods();
    seteuid(getuid());
}
void initialize_methods() {
    SERVER->add_method("c",  file_name(this_object()), "compile_c");
}
object compile_c(string name, int clone) {
    if (!clone) {
	name->go_ahead_make_my_womble();
	return efun::find_object(name);
    } else {
	return efun::clone_object(name);
    }
}

==================================================
FILE: virtual/compiler.c
==================================================

#include "virtual.h"
#include "compiler.h"
void    initialize_methods();
string  strip_string( string str );
#define WHITESPACE(c) (c == 10 || c == 32 || c == '\n')
mapping o_funcs;
mapping r_funcs;
mapping arm_funcs;
mapping clo_funcs;
mapping sca_funcs;
mapping wep_funcs;
mapping cont_funcs;
mapping food_funcs;
mapping mon_funcs;
mapping clotrans_funcs;
object  return_ob;
int     tmp_file_no;
int     debug_file;
void    create()
{
  seteuid("Root");
  initialize_methods();
  o_funcs = O_FUN;
  r_funcs = O_FUN + R_FUN;
  arm_funcs = ARM_FUN + O_FUN;
  clo_funcs = CLO_FUN + O_FUN;
  sca_funcs = SCA_FUN + O_FUN;
  wep_funcs = WEP_FUN + O_FUN;
  mon_funcs = MON_FUN + O_FUN;
  cont_funcs = CONT_FUN + O_FUN;
  food_funcs = FOOD_FUN + CONT_FUN + O_FUN;
  clotrans_funcs = O_FUN + CLO_FUN + CLOTRANS_FUN;
}
object  query_return_ob()
{
    return return_ob;
}
void    set_return_ob( object ob )
{
    return_ob = ob;
}
void    initialize_methods()
{
    SERVER->add_method( "r", file_name( this_object() ), "compile_r",
                        CLONE|LOAD );
    SERVER->add_method( "ro", file_name( this_object() ), "compile_r",
                        CLONE|LOAD );
    SERVER->add_method( "ob", file_name( this_object() ), "compile_ob" );
    SERVER->add_method( "arm", file_name( this_object() ), "compile_arm" );
    SERVER->add_method( "clo", file_name( this_object() ), "compile_clo" );
    SERVER->add_method( "trans", file_name( this_object() ), "compile_clotrans" );
    SERVER->add_method( "sca", file_name( this_object() ), "compile_sca" );
    SERVER->add_method( "wep", file_name( this_object() ), "compile_wep" );
    SERVER->add_method( "mon", file_name( this_object() ), "compile_mon" );
    SERVER->add_method( "food", file_name( this_object() ), "compile_food" );
    SERVER->add_method( "cont", file_name( this_object() ), "compile_cont" );
    SERVER->add_method( "imp", file_name( this_object() ), "compile_imp" );
}
#define Error(s) write(s); log_file( "VO_COMPILER", s); return 0;
mixed  *extract_arguments( string str );
void    do_clone( object dest, string str )
{
    object  ob;
    ob = clone_object( str );
    if( ob )
        ob->move( dest );
}
object  prop_to_fun( string file, mapping funs, string virt_class,
                    string virt_include, int clone )
{
    string *segments, *ind, data, s1, dir, tmp_name, tmp_val;
    string file_data;
    mixed  *val;
    int     i;
    int pos;
    debug_file = 0;
    file_data = "";
    pos = strsrch(file, "/", -1);
    tmp_name = file[0..pos] + "." + file[pos+1..] + "_virtual_.c";
    if (file_size(tmp_name) <= 0 ||
        stat(file)[1] > stat(tmp_name)[1]) {
       tmp_file_no++;
       if( find_object( tmp_name ) ) {
           tmp_name->dest_me();
       }
       ind = explode( file, "/" );
       dir = implode( ind[ 0..sizeof( ind ) - 2 ], "/" );
       unguarded((: rm, tmp_name :));
       file_data = "#include <"+ virt_include +">\n\n"
                "void dest_me() { destruct( this_object() ); }\n\n"
                "void create()\n{\n"
                "  seteuid( (string)\"/secure/master\"->creator_file( file_name( this_object() ) ) );\n"
                "} \n"
                "\nobject create_virtual_ob() {\n"
                "   object clone;\n\n";
       data = read_file( file );
       if( !data )
       {
           Error( "prop_to_fun() : file " + file + " not found\n" );
       }
       segments = explode( "$\n" + data, "\n#" );
       if( !segments )
       {
           Error( "prop_to_fun() : Nothing but comments?\n" );
       }
       segments[ 0 ] = segments[ 0 ][ 1..(sizeof(segments[ 0 ]) - 1) ];
       for( i = 1; i < sizeof( segments ); i++ ) {
           if( sscanf( segments[ i ], "%s\n%s", s1, segments[ i ] ) != 2 ) {
               segments[ i ] = "";
           }
       }
       data = implode( segments, "\n" );
       segments = explode( strip_string( data ), "::" );
       if (sizeof( segments ) % 2) {
         segments += ({""});
       }
       ind = allocate( sizeof( segments ) / 2 );
       val = allocate( sizeof( segments ) / 2 );
       for( i = 0; i < sizeof( ind ); i++ )
       {
           ind[ i ] = segments[ i * 2 ];
           val[ i ] = replace( segments[ i * 2 + 1 ], "\n", " " );
           if( ind[ i ][ 0..0 ] == "#" )
           {
               ind[ i ] = lower_case( ind[ i ] );
               if( ind[ i ] == "#debug" )
               {
                   sscanf( val[ i ], "%d", debug_file );
               }
               else
               {
                   if( ind[ i ] == "#class" )
                   {
                       virt_class = replace( val[i], " ", "" );
                   }
                   else
                   {
                       if( ind[ i ] == "#include" )
                       {
                           tmp_val = val[i];
                           file_data += "#include " +
                                       replace( tmp_val, " ", "" ) +
                                       "\n";
                       }
                   }
               }
           }
       }
       file_data += "  clone = (object)SERVER->create_virtual_object( " +
                   virt_class + ", 1 );\n"
                   "  clone->add_property( VIRTUAL_NAME_PROP, \""
                   + file + (clone ? "#1" : "") + "\" );\n";
       for( i = 0; i < sizeof( ind ); i++ )
       {
           ind[ i ] = lower_case( ind[ i ] );
           if( ind[ i ][ 0..0 ] == "#" )
           {
               continue;
           }
           val[ i ] = replace( val[ i ], ({"(:", "bind( (:",
                                           ":)", ":), clone )" }) );
           if( ind[ i ][ 0..0 ] == "$" )
           {
               {
                   file_data +="  call_other( clone, \"" +
                               ind[ i ][ 1..100 ] + "\", " + val[ i ] +
                               " );\n";
               }
               continue;
           }
           if( funs[ ind[ i ] ] )
           {
               if( !pointerp( funs[ ind[ i ] ] ) )
               {
                   file_data += "  call_other( clone, \"" +
                               funs[ ind[ i ] ] + "\", " + val[ i ] + " );\n";
               }
               else
               {
                   file_data += "  call_other( " + funs[ ind[ i ] ][ 1 ] +
                               ", " + funs[ ind[ i ] ][ 0 ] + ", " + val[ i ] +
                               " );\n";
               }
           }
           else
           {
               write( "Error: Unknown index " + ind[ i ] + "\n" );
           }
       }
       file_data += "   return clone;\n} \n";
       unguarded((: write_file, tmp_name, file_data :));
   }
   if( data = catch( return_ob = tmp_name->create_virtual_ob() ) )
   {
        write( "Error loading " + file + ", " + data + "\n" );
        if( debug_file )
        {
            write( "File not removed.\n" );
        }
        else
        {
        }
    }
    else
    {
        tmp_name->dest_me();
        return return_ob;
    }
}
string  strip_string( string str )
{
    int     i, j;
    j = strlen( str ) - 1;
    for( ; WHITESPACE( str[ i ] ) && i < j; i++ ) ;
    for( ; WHITESPACE( str[ j ] ) && j > i; j-- ) ;
    return str[ i..j ];
}
mixed   str_to_var( string str )
{
    int     i;
    str = strip_string( str );
    switch( str[ 0 ] )
    {
        case '{':
            {
                str = str[ 1..strlen( str ) - 2 ];
                return map_array( explode( str, "," ), "str_to_var",
                                  this_object() );
            }
        case '"':
            {
                str = str[ 1..strlen( str ) - 2 ];
                return replace( str, "\n", " " ) + "\n";
            }
        case '0'..'9':
        case '-':
            {
                sscanf( str, "%d", i );
                return i;
            }
    }
    return str;
}
mixed  *extract_arguments( string str )
{
    return map_array( explode( str, "
}
object  compile_r( string name, int clone ) {
    object r;
    r = prop_to_fun( name, r_funcs, "\"/obj/virtual_room.c\"",
                    "virtual_room.h", 1 );
    r->reset();
    return r;
}
object  compile_ob( string name, int clone ) {
    return prop_to_fun( name, o_funcs, "\"/std/object.c\"",
                    "virtual.h", clone );
}
object  compile_arm( string name, int clone ) {
    if (name[0 .. 19] == "/obj/armours/shield/")
        return prop_to_fun(name, arm_funcs, "\"/obj/shield.c\"",
                        "virtual.h", clone );
    return prop_to_fun( name, arm_funcs, "\"/obj/armour.c\"",
                    "virtual.h", clone );
}
object  compile_clo( string name, int clone ) {
    return prop_to_fun( name, clo_funcs, "\"/obj/clothing.c\"",
                    "virtual.h", clone );
}
object compile_sca( string name, int clone ) {
   return prop_to_fun( name, sca_funcs, "\"/obj/scabbard.c\"",
                    "virtual.h", clone );
}
object  compile_wep( string name, int clone ) {
    return prop_to_fun( name, wep_funcs, "\"/obj/weapon.c\"",
                    "virtual.h", clone );
}
object  compile_mon( string name, int clone ) {
    return prop_to_fun( name, mon_funcs, "\"/obj/monster.c\"",
                    "virtual.h", clone );
}
object  compile_food( string name, int clone ) {
    return prop_to_fun( name, food_funcs, "\"/obj/food.c\"",
                    "virtual.h", clone );
}
object  compile_cont( string name, int clone ) {
    return prop_to_fun( name, cont_funcs, "\"/obj/cont_medium.c\"",
                    "virtual.h", clone );
}
object  compile_clotrans( string name, int clone ) {
    return prop_to_fun( name, clotrans_funcs, "\"/obj/clothing_transport.c\"",
                    "virtual.h", clone );
}
object  compile_imp( string name, int clone ) {
    return prop_to_fun( name, o_funcs, "\"/obj/implement.c\"",
                    "virtual.h", clone );
}
int set_debug_status(int d_stat) {
  debug_file=d_stat;
  return debug_file;
}

==================================================
FILE: virtual/data_compiler.c
==================================================

#include "virtual.h"
#include <soul.h>
#include <random_names.h>
void initialize_methods();
void create() {
  initialize_methods();
  seteuid(getuid());
}
void initialize_methods() {
  SERVER->add_method("s",  file_name(this_object()), "compile_soul", 1);
  SERVER->add_method("r_n",  file_name(this_object()), "compile_random_name", 1);
}
object compile_soul(string name, int) {
  object ob;
  if (name[0] != '/')
    name = "/"+name;
  if (name[0..strlen(SOUL_DIR)-1] != SOUL_DIR) {
    return 0;
  }
  name = name[strlen(SOUL_DIR)..];
  SOUL_COMPILER->compile_file(name);
  ob = clone_object("/std/object");
  ob->set_name("compile");
  ob->set_short("Compiling "+name+" now");
  call_out((: $(ob)->dest_me() :), 2);
  return ob;
}
object compile_random_name(string name, int clone) {
  object ob;
  if (name[0] != '/')
    name = "/"+name;
  if (name[0..strlen(RANDOM_NAME_DATA_DIR)-1] != RANDOM_NAME_DATA_DIR) {
    return 0;
  }
  name = name[strlen(RANDOM_NAME_DATA_DIR)..];
  RANDOM_NAME_GENERATOR->open_file(name);
  ob = clone_object("/std/object");
  ob->set_name("compile");
  ob->set_short("Compiling "+name+" now");
  call_out((: $(ob)->dest_me() :), 2);
  return ob;
}

==================================================
FILE: virtual/efuns.c
==================================================

#define HANDLER "/global/virtual/handler"
object clone_object(string name) {
  if(name[0..2] == "/d/" || name[0..1] == "d/")
    return (object)HANDLER->clone_virtual_object(name);
  return efun::clone_object(name);
}
void destruct(mixed name) {
  object obj;
  if(stringp(name)) {
    obj = find_object(name);
    if(obj->query_property("file_name"))
      HANDLER->destruct_virtual_object(obj);
    destruct(obj);
  } else if(objectp(name)) {
    if(name->query_property("file_name"))
      HANDLER->destruct_virtual_object(name);
    destruct(name);
  }
}
string file_name(object obj) {
  string name, number, file;
  name = efun::file_name(obj);
  if(sscanf(name, "%s#%s", name, number) == 2) {
    if(file = (string)obj->query_property("file_name")) {
      return file + "#" + number;
    } else {
      return name + "#" + number;
    }
  }
  return name;
}
object find_object(string str) {
  object obj;
  if(obj = efun::find_object(str))
    return obj;
  return (object)HANDLER->find_virtual_object(str);
}

==================================================
FILE: virtual/handler.c
==================================================

mapping cloned_objects;
create() {
  seteuid("Room");
  cloned_objects = ([ ]);
  unguarded((: restore_object, "/global/virtual/handler" :));
}
self_dest() {
  unguarded((: save_object, "/global/virtual/handler" :));
  destruct(this_object());
}
mapping query_cloned_objects() { return cloned_objects; }
destruct_virtual_object(object obj) {
  string name, trash;
  name = file_name(obj);
  if(sscanf(name, "%s#%s", name, trash) == 2)
    name = trash;
  if(cloned_objects[name])
    map_delete(cloned_objects, name);
}
object find_virtual_object(string name) {
  string trash;
  if(sscanf(name, "%s#%s", name, trash) == 2)
    name = trash;
  if(cloned_objects[name])
    return (object)cloned_objects[name];
  return (object)0;
}
int error(string str) {
  write(str+"\n");
  return 1;
}
int str_to_int(string str) {
  int i, j, k;
  for(i=strlen(str)-1,j=1;i>-1;k+=(str[i--]-48)*j,j*=10) ;
  return k;
}
mixed *sort_arguments(mixed *args) {
  int i;
  for(i=0;i<sizeof(args);i++) {
    if(pointerp(args[i]))
      args[i] = sort_arguments(args[i]);
    else if(args[i][0..0] != "\"")
      args[i] = str_to_int(args[i]);
    else {
      args[i] = args[i][1..strlen(args[i])-2];
      if(args[i][strlen(args[i])-2..strlen(args[i])-1] == "\\n")
        args[i] = args[i][0..strlen(args[i])-3] + "\n";
    }
  }
  return args;
}
mixed *add_item(mixed *args, int m, string str) {
  if(m == 0)
    args += ({ str });
  else
    args[sizeof(args)-1] = add_item(args[sizeof(args)-1], m-1, str);
  return args;
}
mixed *add_level(mixed *args, int m) {
  if(m == 0) {
    args += ({ "" });
    args[sizeof(args)-1] = ({ });
  } else
    args[sizeof(args)-1] = add_level(args[sizeof(args)-1], m-1);
  return args;
}
object use_efun_clone(string file) {
  log_file("NON_VIRTUAL", file +"\n");
  return efun::clone_object(file);
}
object clone_virtual_object(string file) {
  int i, j, k, l, m, len;
  string data, *line, file_to_inherit, start, comment, rest;
  object obj;
  mixed *args;
  if(file_size(file) > 5000)
    return use_efun_clone(file);
  data = read_file(file);
  line = explode(file, "/");
  file_to_inherit = "/" + implode(line[0..sizeof(line)-2], "/") + "/";
  line = ({ (string)0 });
  while(sscanf(data, "%s#include \"%s\"%s", start, comment, rest) == 3) {
    if(!(line[0] = read_file(file_to_inherit + comment)))
      line[0] = read_file("/include/" + comment);
    if(line[0])
      data = start + line[0] + rest;
    else {
      error("Include file not found.");
      return (object)0;
    }
  }
  while(sscanf(data, "%s%s", start, comment, rest) == 3)
    data = start + rest;
  i = 0;
  file_to_inherit = data;
  while(sscanf(file_to_inherit, "%sinherit%s", start, file_to_inherit) == 2) {
    i++;
  }
  if(i != 1)
    return use_efun_clone(file);
  i = 0;
  file_to_inherit = data;
  while(sscanf(file_to_inherit, "%s({%s", start, rest)  == 2)
    file_to_inherit = start + rest;
  while(sscanf(file_to_inherit, "%s{%s", start, file_to_inherit)  == 2)
    i++;
  if(i != 1)
    return use_efun_clone(file);
  if(!(sscanf(data, "%ssetup()%s", start, rest) == 2))
    return use_efun_clone(file);
  line = explode(data, "\n");
  line -= ({ "" });
  for(i=0;i<sizeof(line);i++) {
    len = strlen(line[i]);
    for(j=0;j<len;j++) {
      if((line[i][j..j] == " " || line[i][j..j] == "\t") && j == 0) {
        line[i] = line[i][1..len];
        j--;
      }
    }
    for(j=len-1;j>-1;j--) {
      if((line[i][j..j] == " " || line[i][j] == 0) && j == (len-1)) {
        line[i] = line[i][0..len-2];
        len--;
      }
    }
  }
  for(i=0;i<sizeof(line);i++)
    if((line[i][0..3] == "int ") ||
       (line[i][0..5] == "mixed ") ||
       (line[i][0..6] == "object ") ||
       (line[i][0..6] == "string ") ||
       (line[i][0..7] == "mapping "))
      return use_efun_clone(file);
  for(i=0;i<sizeof(line);i++)
    if(line[i][0..7] == "#define ") {
      len = strlen(line[i]);
      for(j=8;j<len && line[i][j..j] != " ";j++);
      comment = line[i][8..j-1];
      file_to_inherit = line[i][j+1..len];
      line = delete(line, i--, 1);
      if(j < len)
        for(k=0;k<sizeof(line);k++)
          if(sscanf(line[k], "%s"+comment+"%s", start, rest) == 2)
            line[k] = start + file_to_inherit + rest;
    }
  for(i=0;i<sizeof(line);i++) {
    for(j=0,k=0,l=0;j<strlen(line[i]);j++) {
      switch(line[i][j..j]) {
        case "\"" :
          if(!k) {
            k = 1;
            if(l && l+1 == j)
              if(l+2 < strlen(line[i]))
                line[i] = line[i][0..l-2] + line[i][l+2..strlen(line[i])];
              else {
                line[i] = line[i][0..l-2] + line[i+1];
                line = delete(line,i+1,1);
              }
          }
          else
            k = 0;
          break;
        case " " :
          if(!k)
            if(j)
              line[i] = line[i][0..--j] + line[i][j+2..strlen(line[i])];
            else
              line[i] = line[i][1..strlen(line[i])];
          break;
        case ";" :
          if(!k && j != strlen(line[i])-1) {
            line = line[0..i] + line[i][j+1..1000] + line[i+1..1000];
            line[i] = line[i][0..j];
            j=0;
          }
          break;
        case "+" :
          if(!k && j && line[i][j-1..j-1] == "\"")
            l = j;
          break;
      }
    }
    if((k)) {
      line[i] = line[i--] + line[i+2];
      line = delete(line,i+2,1);
    }
  }
  for(i=0;i<sizeof(line);i++) {
    len = strlen(line[i]);
    if(line[i][len-1..len-1] != ";")
      if(line[i][len-2..len-1] == "\"+") {
        if(line[i+1][0..0] == "\"")
          line[i] = line[i--][0..len-3] + line[i+2][1..1000];
        else
          line[i] = line[i--] + line[i+2];
        line = delete(line,i+2,1);
      }
  }
  for(i=0;i<sizeof(line);i++)
    if(line[i][0..6] == "inherit")
      file_to_inherit = line[i][8..sizeof(line[i])-3];
  if(file_to_inherit[0..8] == "/std/room")
    return use_efun_clone(file);
  obj = clone_object(file_to_inherit);
  obj->add_property("file_name", file);
  start = file_name(obj);
  if(sscanf(start, "%s#%s", start, rest) == 2)
    cloned_objects[rest] = obj;
  else
    cloned_objects[start] = obj;
  for(i=0;i<sizeof(line);i++)
    if(line[i] == "setup(){" || line[i] == "voidsetup(){")
      break;
  for(i++;i<sizeof(line);i++) {
    if(line[i] != "}") {
      sscanf(line[i], "%s(%s", start, comment);
      for(j=0,l=0,args=({});j<strlen(comment);j++) {
        if(comment[j..j] == "(") {
          if(comment[j+1..j+1] == "{" || comment[j+1..j+1] == "[") {
            args = add_level(args, l++);
            comment = comment[j+2..1000];
            j = -1;
            continue;
          }
        }
        if(comment[j..j] == ")") {
          if(comment[j-1..j-1] == "}" || comment[j-1..j-1] == "]") {
            if(j-1)
              args = add_item(args, l--, comment[0..j-2]);
            comment = comment[j+1..1000];
            j = -1;
            continue;
          }
        }
        if(comment[j..j] == "\"") {
          if(k)
            k = 0;
          else
            k = 1;
        }
        if(comment[j..j] == "," && k == 0) {
          if(!l) {
            if(j)
              args = add_item(args, l, comment[0..j-1]);
            comment = comment[j+1..1000];
            j = -1;
            continue;
          } else {
            if(comment[j+1..j+1] == "}" || comment[j+1..j+1] == "]") {
              if(!j)
                comment = comment[j+1..1000];
              else
                comment = comment[0..j-1] + comment[j+1..1000];
            } else {
              if(j)
                args = add_item(args, l, comment[0..j-1]);
              comment = comment[j+1..1000];
            }
            j = -1;
            continue;
          }
        }
        if(comment[j..j] == ")" && k == 0 && l == 0) {
          if(comment[j-1..j-1] != "}" && comment[j-1..j-1] != "]") {
            args = add_item(args, l, comment[0..j-1]);
            comment = comment[j+1..1000];
            j = -1;
          }
        }
      }
      args = sort_arguments(args);
      switch(sizeof(args)) {
        case 1 :
          call_other(obj, start, args[0]);
          break;
        case 2 :
          call_other(obj, start, args[0], args[1]);
          break;
        case 3 :
          call_other(obj, start, args[0], args[1], args[2]);
          break;
        case 4 :
          call_other(obj, start, args[0], args[1], args[2], args[3]);
          break;
        case 5 :
          call_other(obj, start, args[0], args[1], args[2], args[3], args[4]);
          break;
        case 6 :
          call_other(obj, start, args[0], args[1], args[2], args[3], args[4], args[5]);
          break;
        case 7 :
          call_other(obj, start, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
          break;
      }
    }
  }
  log_file("VIRTUAL", file +"\n");
  return obj;
}

==================================================
FILE: virtual/modified_efuns.c
==================================================

#define MAX_SIZE 50000
varargs void say(string str, mixed avoid)
{
  if (!pointerp(avoid))
    avoid = ({ this_player(), previous_object() }) + ({ avoid });
  else
    avoid += ({ this_player(), previous_object() });
  if (!environment(previous_object()))
    if(this_player() && environment(this_player()))
      event(environment(this_player()), "say", str, avoid);
    else
      event(previous_object(), "say", str, avoid);
  else
  {
    if (environment(environment(previous_object())))
      event(environment(environment(previous_object())), "say", str, avoid);
    else
      event(environment(previous_object()), "say", str, avoid);
  }
}
varargs void tell_room(object ob, string str, mixed avoid) {
  if (!ob || !objectp(ob))
    return ;
  event(ob, "say", str, avoid);
}
void tell_object(object ob, string str) {
  if (objectp(ob))
    ob->event_write(previous_object(), str);
}
object find_living(string str) {
  string nick;
  object ob;
  if (this_player() && (nick = (string)this_player()->expand_nickname(str)))
    str = nick;
  if ((ob = efun::find_living(str)))
    if ((int)ob->query_invis() == 2) {
      if (member_array(this_player()->query_name(),
                       (object *)ob->query_allowed()) == -1)
        return 0;
    }
  return ob;
}
object find_player(string str) {
  object ob;
  if ((ob = efun::find_player(str)))
    if ((int)ob->query_invis() == 2)
      if (member_array(this_player()->query_name(),
                       (object *)ob->query_allowed()) == -1)
        return 0;
  return ob;
}
void log_file(string name, string mess) {
  if (file_size("/log/"+name) > MAX_SIZE) {
    seteuid("Root");
    rm("/log/"+name+".old");
    rename("/log/"+name, "/log/"+name+".old");
  }
  seteuid("Root");
  write_file("/log/"+name, mess);
  seteuid(0);
}
#ifdef MUD_NAME
string mud_name() {
  return capitalize(MUD_NAME);
}
#endif
void cat(string file, int start_line, int number) {
  string bing;
  seteuid(geteuid(previous_object()));
  bing = read_file(file, start_line, number);
  seteuid(0);
  if (bing)
    printf("%s", bing[0..5000]);
}
#define HANDLER "/global/virtual/handler"
object clone_object(string name) {
  seteuid(geteuid(previous_object()));
  if(name[0..2] == "/d/" || name[0..1] == "d/")
    return (object)HANDLER->clone_virtual_object(name);
  return efun::clone_object(name);
}
void destruct(mixed name) {
  object obj;
  if(stringp(name)) {
    obj = find_object(name);
    if(obj->query_property("file_name"))
      HANDLER->destruct_virtual_object(obj);
    destruct(obj);
  } else if(objectp(name)) {
    if(name->query_property("file_name"))
      HANDLER->destruct_virtual_object(name);
    destruct(name);
  }
}
string file_name(object obj) {
  string name, number, file;
  name = efun::file_name(obj);
  if(sscanf(name, "%s#%s", name, number) == 2) {
    if(file = (string)obj->query_property("file_name")) {
      return file + "#" + number;
    } else {
      return name + "#" + number;
    }
  }
  return name;
}
object find_object(string str) {
  object obj;
  if(obj = efun::find_object(str))
    return obj;
  return (object)HANDLER->find_virtual_object(str);
}

==================================================
FILE: virtual/new_c_compiler.c
==================================================

object clone_virtual_object(string name) {
  return efun::clone_object(name);
}

==================================================
FILE: virtual/server.c
==================================================

#include "virtual.h"
void add_method(string suffix, mixed ob, string fun, int type);
mapping methods;
#define OB   0
#define FUN  1
#define TYPE 2
nosave mapping cache;
void create() {
  seteuid(getuid());
  methods = ([ ]);
  add_method("c", "/global/virtual/c_compiler.c", "compile_c",
                        CLONE|LOAD);
  add_method("C", "/global/virtual/c_compiler.c", "compile_c",
                        CLONE|LOAD);
  cache = ([ ]);
}
object create_virtual_object(string name, int clone);
void add_method(string suffix, mixed ob, string fun, int type) {
  if (!type)
    type = CLONE;
  if (!methods[suffix]) {
    methods[suffix] = ({ ob, fun, type });
  }
}
#define Error(s) write(s); log_file("VO_HANDLER", s); return 0;
string get_mod_time(string name) {
  if(cache[name])
    return cache[name];
  if(file_size(name) <= 0)
    cache[name] = "";
  else
    cache[name] = stat(name)[1];
  return cache[name];
}
object create_virtual_object(string name, int clone) {
  string *split;
  mixed  *method;
  object ob;
  split = explode(name, ".");
  method = methods[split[sizeof(split) - 1]];
  if (method) {
    if (clone ||
        (method[TYPE]&LOAD)) {
      ob =  (object) call_other(method[OB], method[FUN], name, clone);
      if (ob)  {
      ob->add_property(VIRTUAL_NAME_PROP, name);
        if (get_mod_time(name) != "")
          ob->add_property("virtual time", get_mod_time(name));
      }
      return ob;
    }
    return 0;
  }
  Error("create_virtual_object() : unknown suffix to " + name + "\n");
}
void reset() {
  cache = ([ ]);
}

==================================================
FILE: virtual/server2.c
==================================================

#include "virtual.h"
void add_method(string suffix, object ob, string fun, int type);
mapping methods;
#define OB   0
#define FUN  1
#define TYPE 2
#define LOAD   1
#define CLONE  2
void create() {
  seteuid(getuid());
  methods = ([ ]);
  add_method("C", "/global/virtual/c_compiler.c", "compile_c",
                        CLONE|LOAD);
}
object create_virtual_object(string name, int clone);
void add_method(string suffix, object ob, string fun, int type) {
  if (!type)
    type = CLONE;
  if (!methods[suffix]) {
    methods[suffix] = ({ ob, fun, type });
  }
}
#define Error(s) write(s); log_file("VO_HANDLER", s); return 0;
object create_virtual_object(string name, int clone) {
  string *split;
  mixed  *method;
  object ob;
  split = explode(name, ".");
  method = methods[split[sizeof(split) - 1]];
  if (method) {
    if (clone ||
        (method[TYPE]&LOAD)) {
      ob =  (object) call_other(method[OB], method[FUN], name, clone);
      ob->add_property("virtual name", name);
      return ob;
    }
    return 0;
  }
  Error("create_virtual_object() : unknown suffix to " + name + "\n");
}

==================================================
FILE: virtual/vr_hand.c
==================================================

object compile_virtual_room(string filename);
void parse_object(object room, string command);
void create()
{
  seteuid(getuid(this_object()));
}
object compile_virtual_room(string filen)
{
  string tmp, tmp2;
  object new_room;
  int i;
  i=3;
  tmp=read_file(filen, 2, 1);
  tmp2=tmp[1..strlen(tmp)-2];
  new_room=clone_object("/"+tmp2);
  while (read_file(filen, i, 1))
  {
    tmp=read_file(filen, i, 1);
    if(tmp=="") break;
    parse_object(new_room, tmp);
    i++;
  }
  return new_room;
}
void parse_object(object room, string command)
{
  string *func_call,s1,s2,s3;
  int i1,i2,i3,i4;
  if(!command) return;
  func_call=explode(command, "#");
  if((string)func_call[0][0]==";") return;
  switch (func_call[0])
  {
    case "SHORT" :
      room->set_short(func_call[1]);
      break;
    case "LONG" :
      room->set_long(func_call[1]);
      break;
    case "EXIT" :
      room->add_exit(func_call[1], func_call[2]);
      break;
    case "LIGHT" :
      i1=sscanf(func_call[1], "%d", i2);
      room->set_light(i2);
      break;
    case "ITEM" :
      room->add_item(explode(func_call[1], ","), explode(func_call[2], ","));
      break;
    case "TASTE" :
      room->add_taste(func_call[1], func_call[2]);
      break;
    case "SMELL" :
      room->add_smell(func_call[1], func_call[2]);
      break;
    case "SOUND" :
      room->add_sound(func_call[1], func_call[2]);
      break;
    case "TOUCH" :
      room->add_feel(func_call[1], func_call[2]);
      break;
    case "OBJECT" :
      room->add_object(func_call[1]);
      break;
    case "ACTION" :
      i2=0;
      catch(i1=sscanf(func_call[3], "%d", i2));
      room->action_add(func_call[1], func_call[2], i2);
      break;
    case "CODE" :
      room->set_code_module(func_call[1]);
      break;
    case "PROP" :
      room->add_property(func_call[1], func_call[2]);
      break;
    case "COORD" :
      i1=sscanf(func_call[1], "%d,%d,%d", i2,i3,i4);
      room->set_co_ord(({i2,i3,i4}));
      break;
  }
  return;
}

==================================================
FILE: virtual/setup_compiler/Outside.c
==================================================

inherit "/std/outside.c";
#include "Room.inc"

==================================================
FILE: virtual/setup_compiler/Room.c
==================================================

inherit "/std/room.c";
#include "Room.inc"

==================================================
FILE: virtual/setup_compiler/SetupCompiler.c
==================================================

#include "SetupCompiler.h"
void initialize_methods();
object return_ob;
int tmp_file_no;
void create() {
  seteuid(getuid(this_object()));
  initialize_methods();
}
object query_return_ob() { return return_ob; }
void set_return_ob(object ob) { return_ob = ob; }
void initialize_methods() {
    SERVER->add_method("vrm",  file_name(this_object()), "compile_vrm");
    SERVER->add_method("vro",  file_name(this_object()), "compile_vro");
    SERVER->add_method("vrw",  file_name(this_object()), "compile_vrw");
    SERVER->add_method("vra",  file_name(this_object()), "compile_vra");
    SERVER->add_method("vrc",  file_name(this_object()), "compile_vrc");
}
#define Error(s) write(s); log_file("VO_COMPILER", s); return 0;
object prop_to_fun(string file, int clone, string incfile ) {
    string  data, data2, s1, *ind, dir, tmp_name;
    int      i;
    tmp_name = file+"-"+(tmp_file_no++)+".c";
    if (find_object(tmp_name))
      tmp_name->dest_me();
    ind = explode(file, "/");
    dir = implode(ind[0..sizeof(ind)-2], "/");
    unguarded((: rm, tmp_name :));
    unguarded((: write_file, tmp_name,
               "object MyRoom;\n"
               "#include \""+incfile+"\"\n\n"
               "object this_room() { return MyRoom; }\n" :));
    data = read_file(file);
    if (!data) {
        Error("prop_to_fun() : file " + file + " not found\n");
    }
    unguarded((: write_file, tmp_name, data :));
    unguarded((: write_file, tmp_name, "\n\n"
               "void dest_me() { destruct(this_object()); }\n\n"
               "void setup();\n\n"
               "void create() {\n"
               "  seteuid((string)\"/secure/master\"->"
               "creator_file(this_object()));\n"
               "  MyRoom = (object)\""+SERVER+
               "\"->create_virtual_object(CLONEFILE, 1);\n"
               "  MyRoom->add_property(\"virtual name\", \""+
               file+(clone?"#1":"")+"\");\n"
               "\n  setup();\n"+
               "\n MyRoom->reset(); \n"
               "  \""+file_name(this_object())+"\"->"
               "set_return_ob(MyRoom);\n} \n" :));
    if (data = catch(tmp_name->bing())) {
      write("Error loading "+file+", "+data+"\n");
      write("File could not be loaded.\n");
    } else {
      tmp_name->dest_me();
      unguarded((: rm, tmp_name :));
      return return_ob;
    }
}
object compile_vrc(string name, int clone) {
    return prop_to_fun(name, clone, PATH+ROOMFUNCS );
}
object compile_vmc(string name, int clone) {
    return prop_to_fun(name, clone, PATH+MON_FUNCS );
}
object compile_vac(string name, int clone) {
    return prop_to_fun(name, clone, PATH+ARM_FUNCS );
}
object compile_vwc(string name, int clone) {
    return prop_to_fun(name, clone, PATH+WEP_FUNCS );
}
object compile_voc(string name, int clone) {
    return prop_to_fun(name, clone, PATH+OBJ_FUNCS );
}

==================================================
FILE: virtual/setup_compiler/UWater.c
==================================================

inherit "/std/uwater.c";
#include "Room.inc"

==================================================
FILE: handlers/more_string.c
==================================================

#define COLS (int)this_object()->query_cols()
#define ROWS ( (int)this_object()->query_rows() - 1 )
class more_string_info {
   int fsize;
   int topl;
   int botl;
   string last_search;
   string *the_bit;
   string finish_func;
   string more_bit;
   string stat_line;
   object finish_ob;
}
nosave mixed *_pending_more;
class more_string_info _current_info;
int internal_more_string();
void create() {
   add_command("Internal_More_String", "<string>", (:internal_more_string:));
}
void string_display_file(class more_string_info info) {
  int i;
  string stuff;
  info->botl = info->topl + ROWS;
  stuff = "";
  for ( i = info->topl; ( i < info->botl ) && ( i < info->fsize ); i++ ) {
    stuff += info->the_bit[ i ] +"\n";
  }
  efun::tell_object( this_object(), stuff );
}
void more_string_status_line(class more_string_info info) {
   string *frog;
   string s;
   int i;
   int percentage;
   if (!info->stat_line) {
      info->stat_line = "$N From $T to $B of $S ($%%) - h for help. ";
   }
   s = "";
   frog = explode(info->stat_line, "$");
   for (i=0;i<sizeof(frog);i++) {
      if (frog[i] == "") {
         s += "$";
         i ++;
      } else switch (frog[i][0]) {
         case 'N' :
            s += info->more_bit+frog[i][1..];
            break;
         case 'T' :
            s += ( info->topl + 1 ) + frog[ i ][ 1 .. ];
            break;
         case 'B' :
            if (info->botl > info->fsize)
               s += info->fsize+frog[i][1..];
            else
               s += info->botl+frog[i][1..];
            break;
         case '%' :
            percentage = (info->botl*100)/info->fsize;
            if (percentage > 100) {
               percentage = 100;
            }
            s += percentage + frog[i][1..];
            break;
         case 'S' :
            s += info->fsize + frog[i][1..];
            break;
      }
   }
   efun::tell_object( this_object(), (string)this_object()->fix_string( s ) );
   return;
}
void string_next_page(string str, class more_string_info info) {
   int num;
   int noargs;
   int i;
   int redraw;
   string s1;
   if (!str) {
     str = "";
   }
   if (sscanf(str,"%d%s", num, str) != 2) {
     noargs = 1;
   }
   s1 = str[1..];
   if (str == "") {
      str = "f";
   }
   switch(str[0]) {
      case 'h' :
         cat("/doc/helpdir/more");
         break;
      case 'q' :
         if (info->finish_func) {
            if (functionp(info->finish_func)) {
               evaluate(info->finish_func);
            } else {
               call_other(info->finish_ob, info->finish_func);
            }
         }
         info->finish_func = 0;
         _current_info = 0;
         return;
      case 'f' :
      case 'F' :
         info->topl += ROWS;
         redraw = 1;
         break;
      case 'b' :
      case 'B' :
         info->topl -= ROWS;
         redraw = 1;
         break;
      case '/' :
         i = info->topl + 4;
         if (!s1 || s1 == "") {
            s1 = info->last_search;
         }
         if (!s1 || s1 == "") {
            s1 = "bing!";
         }
         for (i = info->topl + 4; i < info->fsize; i++) {
            if (strsrch(info->the_bit[i], s1) != -1) {
               if (num-- <= 0) {
                  break;
               }
            }
         }
         if (i == info->fsize) {
            tell_object( this_object(), "Sorry "+ s1 +" not found.\n" );
         } else {
            tell_object( this_object(), "Found " + s1 + " on line "+ i +".\n");
            info->topl = i - 3;
         }
         redraw = 1;
         break;
      case '?' :
         if (!s1 || s1 == "") {
            s1 = info->last_search;
         }
         if (!s1 || s1 == "") {
            s1 = "bing!";
         }
         for (i = info->topl + 2; i > 0; i--) {
            if (strsrch(info->the_bit[i], s1) != -1) {
               if (num-- <= 0) {
                  break;
               }
            }
         }
         if (i == 0) {
            tell_object(this_object(), "Sorry " + s1 + " not found.\n");
         } else {
            info->topl = i - 3;
         }
         redraw = 1;
         break;
      case 'b' :
         if (info->topl > 0) {
            info->topl -= ROWS;
            redraw = 1;
            if (info->topl < 0) {
               info->topl = 0;
            }
         }
         break;
      case 'g' :
         info->topl = num;
         if (info->topl >= info->fsize)
            info->topl = info->fsize - 2;
         redraw = 1;
         break;
      case 'G' :
         redraw = 1;
         if (noargs)
            info->topl = info->fsize - ROWS;
         else
            info->topl = num;
         if (info->topl > info->fsize)
            info->topl = info->fsize - 2;
         break;
   }
   if (redraw) {
      string_display_file(info);
      if ( info->botl < info->fsize ) {
         more_string_status_line(info);
         input_to("string_next_page", 0, info);
      } else {
         if (info->finish_func) {
            if ( info->finish_ob ) {
               call_other(info->finish_ob, info->finish_func);
            }
            info->finish_func = 0;
         }
         _current_info = 0;
      }
   } else {
      more_string_status_line(info);
      input_to("string_next_page", 0, info);
   }
}
varargs int more_string( string text, string bity, int noreline ) {
  int i, ncols;
  string *bits;
  class more_string_info info;
  if ( this_player() != this_object() ){
     if ( !_pending_more ) {
        _pending_more = ({ ({ text, bity, noreline }) });
     } else {
        _pending_more += ({ ({ text, bity, noreline }) });
     }
     this_object()->ignore_from_history("Internal_More_String something");
     command( "Internal_More_String something" );
     return 1;
  }
  _current_info = info = new(class more_string_info);
  if ( bity ) {
    info->more_bit = bity;
  } else {
    info->more_bit = "--- MORE";
  }
  info->last_search = "";
  if ( !stringp( text ) || !strlen( text ) ) {
    return notify_fail( "Empty string.\n" );
  }
  if ( noreline ) {
    info->the_bit = explode( this_object()->fix_string( text ), "\n" );
  } else {
    info->the_bit = ({ });
    ncols = COLS;
    bits = explode( text, "\n" );
    for ( i = 0; i < sizeof( bits ); i++ ) {
      reset_eval_cost();
      if ( bits[ i ] == "" ) {
        info->the_bit += ({ "" });
      } else {
        info->the_bit +=
          explode( this_object()->fix_string( bits[ i ], ncols ), "\n" );
      }
    }
  }
  info->fsize = sizeof( info->the_bit );
  info->topl = 0;
  string_display_file(info);
  if ( info->botl < info->fsize ) {
    more_string_status_line(info);
    input_to( "string_next_page", 0, info );
  } else {
      if ( info->finish_func ) {
         if ( !info->finish_ob ) {
            info->finish_func = 0;
            return 1;
         }
         call_other( info->finish_ob, info->finish_func );
         info->finish_func = 0;
      }
      _current_info = 0;
  }
  return 1;
}
varargs void set_finish_func(string str, object ob) {
  _current_info->finish_func = str;
  if (!ob) {
    _current_info->finish_ob = previous_object();
  } else {
    _current_info->finish_ob = ob;
  }
}
int internal_more_string() {
   string text, bity;
   int noreline;
   if ( sizeof( _pending_more ) ) {
      text = _pending_more[ 0 ][ 0 ];
      bity = _pending_more[ 0 ][ 1 ];
      noreline = _pending_more[ 0 ][ 2 ];
      _pending_more = _pending_more[ 1 .. <1 ];
      more_string( text, bity, noreline );
   }
   return 1;
}
