inherit "/cmds/base";
#include <dirs.h>
#define THRESHOLDS ({ 10, 30, 200, 300 })
#define OBJECT_WET_EFFECT "/std/effects/object/wet"
#define BODY_WET_EFFECT "/std/effects/other/wetness"
mixed cmd(object *things) {
   string results;
   string no_wet_results;
   object thing;
   object* not_wet;
   string wet_mess;
   if (!things) {
      things = all_inventory(this_player()) + ({ this_player() });
   }
   results = "";
   not_wet = ({ });
   no_wet_results = "";
   foreach (thing in things) {
      wet_mess = OBJECT_WET_EFFECT->wet_string(thing);
      if (strlen(wet_mess)) {
         if (thing == this_player()) {
            wet_mess = "are " + wet_mess;
         } else {
            wet_mess = "is " + wet_mess;
         }
      } else {
         wet_mess = BODY_WET_EFFECT->wet_string(thing, thing == this_player());
      }
      if (strlen(wet_mess)) {
         results += "$C$" + thing->the_short(1) + " " + wet_mess + ".\n";
      } else {
         not_wet += ({ thing });
      }
   }
   if (results == "") {
      write(query_multiple_short(not_wet) +
            ((sizeof(not_wet) > 1  ||  not_wet[0] == this_player()) ?
               " are ":" is ") + "not wet.\n");
   } else {
      write(results);
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:object>", (: cmd($1) :),
             "", (: cmd(0) :) });
}