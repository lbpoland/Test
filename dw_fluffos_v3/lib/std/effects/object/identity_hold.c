#include <effect.h>
#include "path.h"
class special_stuff {
   int keep;
   string identity;
}
int query_indefinite() { return 1; }
string query_classification() { return "object.identify"; }
string query_shadow_ob() { return SHADOWS + "identity_hold"; }
class special_stuff beginning( object thing, mapping data, int id ) {
   class special_stuff special_stuff;
   special_stuff = new(class special_stuff);
   special_stuff->keep = data["keep"];
   special_stuff->identity = data["identity"];
   thing->set_keep_value(special_stuff->keep);
   thing->set_identifier(special_stuff->identity);
   thing->set_identity_hold_owner(this_player());
   return special_stuff;
}
class special_stuff merge_effect( object thing,
                                  class special_stuff data,
                                  mapping arg,
                                  int id ) {
   if (!nullp(arg["keep"])) {
      data->keep = arg["keep"];
   }
   if (!nullp(arg["identity"])) {
      data->identity = arg["identity"];
   }
   thing->set_keep_value(data->keep);
   thing->set_identifier(data->identity);
   return data;
}
void end( object thing, mixed* store, int id ) {
}
class special_stuff restart( object thing, class special_stuff data, int id ) {
   thing->set_keep_value(data->keep);
   thing->set_identifier(data->identity);
   thing->set_identity_hold_owner(this_player());
   return data;
}