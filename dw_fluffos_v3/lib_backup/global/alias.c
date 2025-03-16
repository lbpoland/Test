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