inherit "/cmds/base";
#include <creator.h>
int cmd(object *obs) {
   object ob;
   foreach (ob in obs) {
      write(WIZ_PRESENT->desc_object(ob) + ":\n" + debug_info(0, ob) + "\n");
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:wiz-present>", (: cmd($1) :) });
}