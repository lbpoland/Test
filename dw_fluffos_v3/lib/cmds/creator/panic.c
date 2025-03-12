#include <panic.h>
inherit "/cmds/base";
int cmd( ) {
    return 0;
  PANIC_HANDLER->do_startup(previous_object());
  this_player()->add_succeeded_mess(this_object(),
                  "$N panic$s hopefully.", ({ }) );
  return 1;
}
mixed *query_pattern() {
  return ({ "", (: cmd() :) });
}