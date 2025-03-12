#include <parser.h>
#include <player_handler.h>
inherit "/cmds/base";
mixed cmd(string creator) {
  seteuid("Root");
  if ( !PLAYER_HANDLER->test_user( creator ) ||
       !"/secure/master"->query_trustee( previous_object( -1 ) ) )
    return notify_fail("You must be a trustee to add a director.\n");
  if("/secure/master"->add_director(creator)) {
    write(creator + " promoted to directorship.\n");
    return 1;
  } else
    return notify_fail("Call to add_director failed.\n");
}
mixed *query_patterns() {
  return ({ "<string>", (: cmd($4[0]) :), });
}