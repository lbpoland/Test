#include <philosophies.h>
inherit "/cmds/base";
int cmd() {
   string *args;
   args = PHILOSOPHY_HANDLER->query_all_known(this_player()->query_name());
   if (!sizeof(args)) {
      write("You do not know any theological arguments.\n");
   } else {
      write("You know the following theological arguments:\n" +
            query_multiple_short(args) + ".\n");
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd() :) });
}