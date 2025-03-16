#include <player.h>
#define FORCE_COST 1
#define ILLEGAL_FORCE ({ "alias", "unalias", "mv", "mkdir", "call", "rm", \
                         "force", "kill", "gauge", "exec", "promote", \
                         "new_domain", "rmdir", "cd", "history", "echoall", \
                         "shout" })
nosave string fname;
nosave int no_force_me;
protected int no_force(string str);
protected int do_force(object *obs, string str);
void force_commands() {
  fname = base_name(this_object());
  if ((!this_object()->query_property("npc") &&
      master()->query_senior( geteuid(this_object()) ) ) || fname == LORD_OB) {
    add_command("force", "<indirect:distant-living> <string'command'>",
                (: do_force($1, $4[1]) :));
 }
  if (fname == LORD_OB) {
    add_command("noforce", "{on|off}", (: no_force($4[0]) :));
    add_command("noforce", "", (: no_force(0) :));
  }
}
protected int no_force(string str) {
  if (str == "on") {
    no_force_me = 1;
    write("Ok, forcing you disabled.\n");
    return 1;
  }
  if (str == "off") {
    no_force_me = 0;
    write("Ok, forcing you enabled.\n");
    return 1;
  }
  write("Forcing you is currently ");
  if (no_force_me) {
    write("disabled.\n");
  }
  else {
    write("enabled.\n");
  }
  return 1;
}
protected int do_force(object *obs, string str) {
  object ob;
#ifdef PLAYERS_CAN_FORCE
  if (fname == PLAYER_OB && !this_player()->query_property("force")) {
    notify_fail("You do not have the ability to do that yet.\n");
    return 0;
  }
  if (this_player()->adjust_social_points(-FORCE_COST) < 0) {
    notify_fail("Insufficient social points.\n");
    return 0;
  }
#endif
  foreach( ob in obs ) {
    if(!ob->do_force_on_me( str )) {
      write(capitalize( ob->query_name() ) + " didn't want to do that.\n");
    }
  }
  write("Ok.\n");
  return 1;
}
nomask int do_force_on_me(string str) {
  string temp1, temp2;
  object forcer;
  forcer = this_player(1);
  if (!forcer || (this_player() != previous_object())) {
    if (interactive(previous_object())) {
      forcer = previous_object();
    } else {
      log_file("FORCE", "Attempted illegal force from "+
               file_name(previous_object())+"\n");
      return 0;
    }
  }
  log_file("FORCE", ctime(time()) + " " + forcer->query_name() + " " +
                    this_object()->query_name() + " : " + str);
  tell_object(this_object(), forcer->query_cap_name() +
        " tries to force you to " + str + "\n");
  if (no_force_me || (string)this_object()->query_name() == "pinkfish") {
    event(users(), "inform", forcer->query_cap_name()+" forces "+
          this_object()->query_name()+" to "+str+" (failed)", "force");
    log_file("FORCE", " (failed)\n");
    return 0;
  }
  if (sscanf(str, "%s %s", temp1, temp2) != 2) {
    temp1 = str;
  }
  if (member_array(temp1, ILLEGAL_FORCE) != -1 &&
      !master()->high_programmer(geteuid(forcer))) {
    event(users(), "inform", forcer->query_cap_name()+" forces "+
          this_object()->query_name()+" to "+str+" (failed)", "force");
    log_file("FORCE", " (failed)\n");
    return 0;
  }
  if (function_exists("eventForce", this_object())) {
    command(str);
  } else {
    this_object()->eventForce(str);
  }
  event(users(), "inform", forcer->query_cap_name()+" forces "+
        this_object()->query_name()+" to "+str, "force");
  log_file("FORCE", " (succeeded)\n");
  return 1;
}