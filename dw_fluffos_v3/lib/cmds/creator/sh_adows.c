#include <creator.h>
inherit "/cmds/base";
int cmd(object *indirect_obs) {
  object *objs, *shadows, ob, shad, nobj;
   objs = indirect_obs;
  foreach (ob in objs) {
    shadows = ({ });
     nobj = ob;
     while(nobj = shadow(nobj, 0))
       shadows += ({ nobj });
     if(!sizeof(shadows)) {
       write(WIZ_PRESENT->desc_f_object(ob) + " is not being shadowed.\n");
     } else {
       write(WIZ_PRESENT->desc_f_object(ob) + " is being shadowed by:\n");
       foreach (shad in shadows)
         write("    " + file_name(shad) + "\n");
    }
  }
  return 1;
}
mixed *query_patterns() {
    return ({ "<indirect:wiz-present>", (: cmd( $1 ) :) });
}