#include <parser.h>
#include <player_handler.h>
inherit "/cmds/base";
mixed cmd(string creator) {
  seteuid("Root");
  if ( !PLAYER_HANDLER->test_user( creator ) ||
       !"/secure/master"->query_lord( previous_object( -1 ) ) )
    return notify_fail("You must be a lord to remove a senior creator.\n");
  if("/secure/master"->remove_senior(creator)) {
    write(creator + " removed from senior.\n");
    return 1;
  } else
    return notify_fail("Call to remove_senior failed.\n");
}
mixed *query_patterns() {
  return ({ "<string>", (: cmd($4[0]) :), });
}