inherit "/cmds/base";
#include <peopler.h>
#include <creator.h>
mixed cmd(string str) {
   mixed *stuff;
   stuff = this_player()->query_property("term list");
   if (!stuff) {
      stuff = T_DEFAULT;
   }
   return PEOPLER->do_command(stuff, str);
}
mixed *query_patterns() {
   return ({ "", (: cmd(0) :),
             "<word>", (: cmd($4[0]) :) });
}