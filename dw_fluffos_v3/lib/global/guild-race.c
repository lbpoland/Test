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