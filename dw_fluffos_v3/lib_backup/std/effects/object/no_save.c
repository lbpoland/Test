#include "path.h"
string query_classification() { return "mudlib.object.nosave"; }
string query_shadow_ob() { return SHADOWS +"no_save"; }
int query_indefinite() { return 1; }
void beginning( object thing, string owner, int id ) { return; }
string merge_effect( object thing, string old_owner, string new_owner,
      int id ) {
   return old_owner;
}