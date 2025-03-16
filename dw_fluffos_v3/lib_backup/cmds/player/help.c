inherit "/cmds/base";
#include <nroff.h>
#include <soul.h>
#include <log.h>
#include <autodoc.h>
#include <login_handler.h>
#include <player_handler.h>
#include <command.h>
#define SYNONYMS "/doc/SYNONYMS"
#define MATCH_THRESHOLD 55
void do_help(mixed *stuff);
private void list_help(string title, string dir);
private mixed *help_list(string name);
int command_cmd(string name);
int here_cmd();
int object_cmd(object ob);
int spell_cmd(string name, int spell);
int file_help(string name);
void rehash_dirs();
mixed *query_help_on(string name, int creator, int, int);
mixed *create_help_files(string *names, string nroff_dir);
private mapping read_directories(string *directories, int recurse);
private mapping read_synonyms();
private string letter_name(int letter, mixed *things);
private string start_letter( mixed *things );
private string end_letter( mixed *things );
private int query_number_from_string(string name, mixed *things );
private nosave mapping _help_files_player;
private nosave mapping _help_files_creator;
private nosave mapping _help_files_playtester;
private nosave mapping _help_files_lord;
private nosave mapping _synonyms;
private nosave string *_player_dirs;
private nosave string *_creator_dirs;
private nosave string *_lord_dirs;
private nosave string *_playtester_dirs;
void create() {
   ::create();
   _player_dirs = ({ "/doc/helpdir/",
                    "/doc/concepts/",
                    "/doc/known_command/",
                    "/doc/room/",
                    "/doc/spells/",
                    "/doc/object/" });
   _creator_dirs = ({"/doc/creator/",
                    "/doc/driver/",
                    "/doc/policy/",
                    "/doc/new/" });
   _playtester_dirs = ({ "/doc/playtesters/" });
   _lord_dirs = ({"/doc/lord/"});
   unguarded((: rehash_dirs() :));
}
int *find_match_in_array( string entry, string *items )  {
   int i;
   int j;
   int elength;
   int ilength;
   int this_match;
   int best_match;
   int best_try;
   elength = strlen( entry );
   best_match = this_match = -1;
   for ( i = sizeof( items ) - 1; i >= 0; i--, this_match = 0 )  {
      ilength = strlen( items[ i ] );
      for ( j = 0; j < elength  &&  j < ilength; j++ )
        if ( entry[ j ] == items[ i ][ j ] ||
             entry[ j ] == items[ i ][ j - 1 + ( j == 0 ) ]  ||
             entry[ j ] == items[ i ][ j + 1 - ( j + 1 == ilength ) ] )
          ++this_match;
      this_match = 100 * this_match / ( j == elength ? ilength : elength );
      if ( this_match > best_match )  {
        best_match = this_match;
        best_try = i;
      }
   }
   return ({ best_try, best_match });
}
int cmd(string name) {
  class command cmd;
   mixed *list;
   string str;
   string suggestion;
   int i;
   int *matches;
   list = help_list(name);
   if (sizeof(list) == 0 &&
       mapp(_synonyms) &&
       _synonyms[name]) {
      list = help_list(_synonyms[name]);
   }
   if (sizeof(list) == 0) {
      if (PLAYER_HANDLER->test_user(name)) {
         add_failed_mess("That is a player, silly.\n");
         return 0;
      }
      list = keys(_help_files_player) + ({ "command_list", "concepts"});
      matches = find_match_in_array(name, list);
      if (matches[1] > MATCH_THRESHOLD) {
         suggestion = list[matches[0]];
      } else {
         list = keys(_synonyms);
         matches = find_match_in_array(name, list);
         if(matches[1] > MATCH_THRESHOLD) {
            suggestion = _synonyms[list[matches[0]]];
         }
      }
      if (!this_player()->query_creator()) {
         log_file("MISSING_HELP", "%s %s looked for help on %s, "
                  "recommended %s\n",
                  ctime(time()), this_player()->query_name(),
                  name, suggestion);
      }
      str = "Could not find any help on '" + name + "'.  ";
      if (!suggestion && this_player()->query_known_command("newbie"))
        str += "Many useful commands are explained in 'help essentials'.  ";
      else if(suggestion)
        str += "Perhaps you are looking for 'help " +suggestion + "'?  ";
      cmd = new(class command, verb : name);
      if((CMD_D->IsGRCommand(name) &&
          this_player()->query_known_command(name)) ||
         (CMD_D->HandleStars(cmd) &&
          sizeof(((mixed *)CMD_D->GetPaths(cmd->verb) &
                  (mixed *)this_player()->GetSearchPath()))) ||
         sizeof(this_player()->query_parse_command_objects(name)))
        str += "The syntax for the command '" + name + "' can be found by "
          "entering 'syntax " + name + "'.  ";
      if (environment(this_player()) &&
          environment(this_player())->help_function())
         str += "Type 'help here' for help on how to use this room.";
      return notify_fail(str + "\n");
   }
   if (sizeof(list) == 1) {
      do_help(list[0]);
      return 1;
   }
   str = "";
   for (i = 0; i < sizeof(list); i++) {
      str += sprintf("%s) %s\n", letter_name(i, list), list[i][0]);
   }
   printf("Discworld help found multiple matches, please choose one of:\n"
          "%-*#s\nChoice: ", this_player()->query_cols(), str);
   input_to("help_input", 0, list);
   return 1;
}
void help_input(string str, mixed *list) {
   int num;
   str = lower_case(str);
   if (str == "quit" || str == "**" || str == "." || str == "") {
      write("OK, exiting help.\n");
      return ;
   }
   if ( ( num = query_number_from_string( str, list ) ) == -1 ) {
       printf("Incorrect choice, must be between %s and %s.\nChoice: ",
        start_letter( list ), end_letter( list ) );
      input_to("help_input", 0, list);
      return ;
   }
   do_help(list[num]);
}
void do_help(mixed *stuff) {
   string str;
   str = evaluate(stuff[1]);
   if (!str || !strlen(str)) {
      write("Broken help file!\n");
   } else {
      write("$P$" + stuff[0] + "$P$" + str);
   }
}
int here_cmd() {
  mixed str;
  mixed *list;
  int i;
  str = environment(this_player())->help_function();
  if(pointerp(str))
    list = str;
  else if(str)
    list += ({ ({ environment(this_player())->short(), str }) });
  else {
    write("There is no help available for this room.\n");
    return 1;
  }
  if (sizeof(list) == 1) {
    do_help(list[0]);
    return 1;
  }
  str = "";
  for (i = 0; i < sizeof(list); i++) {
    str += sprintf("%s) %s\n", letter_name(i, list), list[i][0]);
  }
  printf("Discworld help found multiple matches, please choose one of:\n"
         "%-*#s\nChoice: ", this_player()->query_cols(), str);
  input_to("help_input", 0, list);
  return 1;
}
int object_cmd(object ob) {
  mixed str;
  mixed *list;
  int i;
  str = ob->help_function();
  if(pointerp(str))
    list = str;
  else if(str)
    list += ({ ({ environment(this_player())->short(), str }) });
  else {
    add_failed_mess("There is no help available for $I.\n", ({ob}));
    return -1;
  }
  if (sizeof(list) == 1) {
    do_help(list[0]);
    return 1;
  }
  str = "";
  for (i = 0; i < sizeof(list); i++) {
    str += sprintf("%s) %s\n", letter_name(i, list), list[i][0]);
  }
  printf("Discworld help found multiple matches, please choose one of:\n"
         "%-*#s\nChoice: ", this_player()->query_cols(), str);
  input_to("help_input", 0, list);
  return 1;
}
int command_cmd(string name) {
   mixed help;
   help = this_player()->help_command(name);
   if (!help) {
      notify_fail("No such command as '" + name + "'.\n");
      return 0;
   } else {
      if (functionp(help)) {
         help = evaluate(help);
      }
      write("$P$" + name + "$P$P" + help);
      return 1;
   }
}
int soul_cmd(string name) {
   string help;
   help = SOUL_OBJECT->help_string(name);
   if (!help) {
      notify_fail("No such soul as '" + name + "'.\n");
      return 0;
   } else {
      write("$P$" + name + "$P$P" + help);
      return 1;
   }
}
int spell_cmd(string name, int spell) {
   mixed help;
   help = this_player()->help_spell(name);
   if (!help) {
      notify_fail("No such spell as '" + name + "'.\n");
      return 0;
   } else {
      if (functionp(help)) {
         this_player()->move_string(evaluate(help), name);
      } else {
         write("$P$" + name + "$P$P" + help);
      }
      return 1;
   }
}
int command_list_cmd() {
   list_help("Command list, try 'help concepts' for a list of concepts.",
       "/doc/helpdir/");
   return 1;
}
int concepts_list_cmd() {
   list_help("Concepts list, try 'help command_list' for a list of commands.",
       "/doc/concepts/");
   return 1;
}
int error_log_cmd() {
   notify_fail("Unable to get help on '" + ERROR_LOG + "'.\n");
   return 0;
}
private void list_help(string title, string dir) {
   string *files;
   files = get_dir(dir + "*") - ({ ".", "..", "ERROR_REPORTS", "RCS", "old" });
   write("$P$Help$P$" + sprintf("%s\n%-#*s\n", title,
                                     (int)this_player()->query_cols(),
                                     implode(files, "\n")));
}
 mixed *help_list(string name) {
   string* stuff;
   mixed str;
   object* fluff;
   object blue;
   stuff = query_help_on(name, this_player()->query_creator(),
                         this_player()->query_lord(),
                         this_player()->query_playtester());
   if (name == "room" || name == "here") {
      str = environment(this_player())->help_function();
      if (pointerp(str)) {
         stuff += str;
      } else if (str) {
         stuff += ({ ({ environment(this_player())->short(),
                        str }) });
      } else {
         add_failed_mess("There is no help available for this room.\n");
         return 0;
      }
   }
   str = this_player()->help_spell(name);
   if (stringp(str)) {
      stuff += ({ ({ name + " (Spell)",
                    (: $(str) :) }) });
   }
   if (functionp(str)) {
      stuff += ({ ({ name + " (Spell)", str }) });
   }
   str = SOUL_OBJECT->help_string(name);
   if (str) {
      stuff += ({ ({ name + " (Soul)",
                    (: $(SOUL_OBJECT)->help_string($(name)) :) }) });
   }
   fluff = filter(match_objects_for_existence(name, ({ this_player(),
                                      environment(this_player()) })),
                    (: $1 && $1->help_function() :));
   if (sizeof(fluff)) {
      foreach (blue in fluff) {
         stuff += blue->help_function();
      }
   }
   return stuff;
}
private string letter_name(int letter, mixed *things) {
   string bing;
   if (sizeof(things) > 26) {
      bing = "aa";
      bing[0] = 'a' + (letter / 26);
      bing[1] = 'a' + (letter % 26);
      return bing;
   }
   bing = "a";
   bing[0] = 'a' + letter;
   return bing;
}
private string start_letter( mixed *things ) {
   return letter_name(0, things);
}
private string end_letter( mixed *things ) {
   return letter_name(sizeof(things) - 1, things);
}
private int query_number_from_string(string name, mixed *things ) {
   int pos;
   if (sizeof(things) > 26) {
      if (strlen(name) != 2) {
         return -1;
      }
      name = lower_case(name);
      if (name[0] < 'a' || name[0] > 'z') {
         return -1;
      }
      if (name[1] < 'a' || name[1] > 'z') {
         return -1;
      }
      pos = (name[0] - 'a') * 26 + name[1] - 'a';
      if (pos >= sizeof(things)) {
         return -1;
      }
      return pos;
   }
   if (strlen(name) != 1) {
      return -1;
   }
   name = lower_case(name);
   if (name[0] < 'a' || name[0] > 'z') {
      return -1;
   }
   pos = name[0] - 'a';
   if (pos >= sizeof(things)) {
      return -1;
   }
   return pos;
}
mixed *query_patterns() {
   return ({ "<string>", (: cmd($4[0]) :),
               "here", (: here_cmd() :),
               "object <indirect:object:me-here'item'>", (: object_cmd($1[0]) :),
               "command <string>", (: command_cmd($4[0]) :),
               "spell <string>", (: spell_cmd($4[0], 0) :),
               "ritual <string>", (: spell_cmd($4[0], 1) :),
               "soul <string>", (: soul_cmd($4[0]) :),
               "command_list", (: command_list_cmd() :),
               "concepts", (: concepts_list_cmd() :),
               "", (: concepts_list_cmd() :) });
}
void rehash_dirs() {
   _help_files_player = read_directories(_player_dirs, 1);
   _help_files_creator = read_directories(_creator_dirs, 1);
   _help_files_lord = read_directories(_lord_dirs, 1);
   _help_files_playtester = read_directories(_playtester_dirs, 1);
   _synonyms = read_synonyms();
}
void rehash_specific_dir(string dir) {
   string start;
   mapping ret;
   string name;
   string* files;
   if (dir[<1] != '/') {
      dir += "/";
   }
   start = "/" + implode(explode(dir, "/")[0..1], "/") + "/";
   if (member_array(start, _player_dirs) != -1) {
      ret = read_directories(({ dir }), 0);
      foreach (name, files in ret) {
         if (_help_files_player[name]) {
            _help_files_player[name] &= files;
         } else {
            _help_files_player[name] = files;
         }
      }
   }
   if (member_array(start, _creator_dirs) != -1) {
      ret = read_directories(({ dir }), 0);
      foreach (name, files in ret) {
         if (_help_files_creator[name]) {
            _help_files_creator[name] &= files;
         } else {
            _help_files_creator[name] = files;
         }
      }
   }
   if (member_array(start, _lord_dirs) != -1) {
      ret = read_directories(({ dir }), 0);
      foreach (name, files in ret) {
         if (_help_files_lord[name]) {
            _help_files_lord[name] &= files;
         } else {
            _help_files_lord[name] = files;
         }
      }
   }
   if (member_array(start, _playtester_dirs) != -1) {
      ret = read_directories(({ dir }), 0);
      foreach (name, files in ret) {
         if (_help_files_playtester[name]) {
            _help_files_playtester[name] &= files;
         } else {
            _help_files_playtester[name] = files;
         }
      }
   }
}
private mapping read_synonyms() {
  string *bits, *bits2;
  int i;
  mapping tmp;
  tmp = ([ ]);
  bits = explode(read_file(SYNONYMS), "\n");
  for(i=0; i<sizeof(bits); i++) {
    bits2 = explode(bits[i], " ");
    tmp[bits2[0]] = bits2[1];
  }
  return tmp;
}
private mapping read_directories(string *directories, int recurse) {
   string *files;
   string fname;
   int i;
   string dir;
   mapping ret;
   ret = ([ ]);
   for (i = 0; i < sizeof(directories); i++) {
     dir = directories[i];
     files = get_dir(dir + "*") - ({ "ERROR_REPORTS" });
     foreach (fname in files) {
       if (file_size( dir + fname) == -2) {
         if (fname != "." &&
             fname != ".." &&
             fname != "old" &&
             fname != "RCS") {
           directories += ({ dir + fname + "/" });
         }
       } else if (fname != "." &&
                  fname != ".." &&
                  fname != "old") {
         if (!ret[fname]) {
           ret[fname] = ({ dir + fname });
         } else {
           ret[fname] += ({ dir + fname });
         }
         if (strsrch(fname, "_") > 0) {
           fname = replace(fname, "_", " ");
           if (!ret[fname]) {
             ret[fname] = ({ dir + fname });
           } else {
             ret[fname] += ({ dir + fname });
           }
         }
       }
     }
   }
   return ret;
}
mixed *query_help_on(string name, int creator, int lord, int pt) {
   string *files;
   mapping map;
   files = ({ });
   name = replace_string(name, " ", "_");
   if (_help_files_player[name]) {
      files += create_help_files(_help_files_player[name], NROFF_DIR);
   }
   if (lord || creator || pt) {
     if(_help_files_playtester && _help_files_playtester[name]) {
         files += create_help_files(_help_files_playtester[name], NROFF_DIR);
      }
   }
   if (lord || creator) {
     if(_help_files_creator && _help_files_creator[name]) {
         files += create_help_files(_help_files_creator[name], NROFF_DIR);
      }
      map = AUTODOC_HANDLER->query_help_map();
      if (map && map[name]) {
         files += create_help_files(map[name], NROFF_DIR);
      }
   }
   if (lord) {
     if(_help_files_lord && _help_files_lord[name]) {
         files += create_help_files(_help_files_lord[name], NROFF_DIR);
      }
      map = AUTODOC_HANDLER->query_help_map();
      if (map && map[name]) {
         files += create_help_files(map[name], NROFF_DIR);
      }
  }
   return files;
}
string query_synonym(string name) {
  if(mapp(_synonyms) && _synonyms[name])
    return _synonyms[name];
  return "";
}
private string nroff_file(string name, string nroff_dir) {
   string nroff_fn;
   string str;
   nroff_fn = nroff_dir + replace(name, "/", ".");
   str = NROFF_HAND->cat_file(nroff_fn, 1);
   if (!str) {
      NROFF_HAND->create_nroff(name, nroff_fn);
      str = NROFF_HAND->cat_file(nroff_fn, 0);
   }
   return str;
}
mixed *create_help_files(string *names, string nroff_dir) {
   int i;
   mixed *ret;
   string *bits;
   ret = ({ });
   for (i = 0; i < sizeof(names); i++) {
      bits = explode(names[i], "/");
      ret += ({ ({ bits[<1] + " (" +
                   names[i] + ")",
                   (: nroff_file($(names[i]), $(nroff_dir)) :) }) });
   }
   return ret;
}
mapping query_help_files_player() { return _help_files_player; }
mapping query_help_files_creator() { return _help_files_creator; }
mixed *stats() {
  mapping map;
  map = AUTODOC_HANDLER->query_help_map();
  return ({
      ({ "player help files", sizeof( keys(_help_files_player) ) }),
      ({ "creator help files", sizeof( keys(_help_files_creator) ) }),
        ({ "autodoc help map", sizeof(keys(map)) }) ,
          });
}
int clean_up() {
  return 0;
}
void dest_me() {
}