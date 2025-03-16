#include <panic.h>
#include <move_failures.h>
inherit "/cmds/base";
void create() {
  seteuid(getuid());
}
int cmd( ) {
  mixed why_not;
  string destination;
  int ret;
  string str;
  if (!environment(this_player())) {
      destination = this_player()->query_last_pos();
      str = catch(ret = this_player()->move_with_look(destination,
                             "$N appears out of nowhere.",
                             "$N disappears with a pop."));
      if (str || ret != MOVE_OK) {
         destination = this_player()->query_start_pos();
         str = catch(ret = this_player()->move_with_look(destination,
                                "$N appears out of nowhere.",
                                "$N disappears with a pop."));
      }
      if (str || ret != MOVE_OK) {
         destination = this_player()->query_nationality()->query_default_start_location();
         str = catch(ret = this_player()->move_with_look(destination,
                                "$N appears out of nowhere.",
                                "$N disappears with a pop."));
      }
      if (str || ret != MOVE_OK) {
         add_failed_mess("Unable to move you out of limbo.  Try again "
                         "soon.\n");
         return 0;
      }
     add_succeeded_mess("You escape from limbo.\n");
     return 1;
  }
  if (environment() ||
      (why_not = environment(this_player())->query_property("no godmother"))) {
          if ( why_not && stringp( why_not ) ) {
              add_failed_mess( why_not );
          } else {
              add_failed_mess("You cannot summon the godmother here.\n");
          }
          return 0;
   }
   why_not = this_player()->query_property( "no godmother" );
   if( why_not )
   {
      if( stringp( why_not ) && sizeof( why_not ) ) {
         add_failed_mess( why_not );
      } else {
         add_failed_mess( "You cannot summon a godmother at this moment.\n" );
      }
      return 0;
   }
   if (PANIC_HANDLER->do_startup(previous_object())) {
      this_player()->add_succeeded_mess(this_object(),
                      ({ "",
                         "$N stares into space and looks pensive.\n" }),
                      ({ }) );
   } else {
      return 0;
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "help", (: cmd() :) });
}