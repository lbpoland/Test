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