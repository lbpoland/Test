#include <parser.h>
#include <player_handler.h>
inherit "/cmds/base";
mixed cmd(string creator) {
  seteuid("Root");
  if ( !PLAYER_HANDLER->test_user( creator ) ||
       !"/secure/master"->query_lord( previous_object( -1 ) ) )
    return notify_fail("You must be a lord to create a senior creator.\n");
  if("/secure/master"->add_senior(creator)) {
    write(creator + " promoted to senior.\n");
    return 1;
  } else
    return notify_fail("Call to add_senior failed.\n");
}
mixed *query_patterns() {
  return ({ "<string>", (: cmd($4[0]) :), });
}