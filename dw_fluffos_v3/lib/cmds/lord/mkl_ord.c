#include <parser.h>
#include <player_handler.h>
inherit "/cmds/base";
mixed cmd(string creator) {
  seteuid("Root");
  if ( !PLAYER_HANDLER->test_user( creator ) ||
       !"/secure/master"->high_programmer( previous_object( -1 ) ) )
    return notify_fail("You must be a highlord to add a lord.\n");
  if("/secure/master"->add_director(creator)) {
    write(creator + " promoted to director.\n");
    return 1;
  } else
    return notify_fail("Call to add_director failed.\n");
}
mixed *query_patterns() {
  return ({ "<string>", (: cmd($4[0]) :), });
}