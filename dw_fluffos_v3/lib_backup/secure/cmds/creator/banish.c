#include <player_handler.h>
#define LIAISON "/d/liaison/master"
inherit "/cmds/base";
int cmd(string str)
{
  string str1, temp1, ban;
  if (this_player() != this_player(1)) {
    return 0;
  }
  if (this_player()->GetForced()) {
    return 0;
  }
  if(!master()->query_senior(geteuid(previous_object())) &&
      !LIAISON->query_deputy(geteuid(previous_object()))) {
    return notify_fail( "Only Liaison domain "
        "deputies, Senior Creators and above can banish player names.\n" );
  }
  notify_fail("Syntax : banish <name> <reason>\n");
  if (!str)
    return 0;
  if (sscanf(str, "%s %s", str, str1) != 2)
    return 0;
  str = lower_case(str);
  if (sscanf(str,"%s.",temp1))
    return 0;
  if (sscanf(str, "%s/", temp1))
    return 0;
  if (file_size("/banish/"+str[0..0]+"/"+str+".o") >= 0)
  {
    notify_fail("That name is already banished.\n");
    return 0;
  }
  PLAYER_HANDLER->remove_cache_entry(str);
  if (PLAYER_HANDLER->test_user(str))
    return notify_fail("That is a player.  You must rm or mv the player "
                       "file first.\n");
  ban = "Banished by : "+(string)this_player()->query_name()+"\n";
  ban += ctime(time())+"\n";
  ban += "Banish Reason : " + str1 + "\n";
  unguarded((: write_file, "/banish/"+str[0..0]+"/"+str+".o", ban :));
  write(str + " banished.\n");
  return 1;
}
string *query_patterns() {
  return ({ "", (: cmd(0) :), "<string>", (: cmd($4[0]) :) });
}