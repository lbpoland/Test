inherit "/cmds/base";
#include <creator.h>
int cmd(object *obs, int detail) {
   object ob;
   foreach (ob in obs) {
      write(WIZ_PRESENT->desc_object(ob) + ":\n" + debug_info(detail, ob) + "\n");
   }
   return 1;
}
mixed *query_patterns() {
  return ({ "-v <indirect:wiz-present>", (: cmd($1, 2) :),
              "<indirect:wiz-present>", (: cmd($1, 1) :) });
}