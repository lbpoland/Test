#include "path.h"
string query_classification() { return "mudlib.owned.weapon"; }
string query_shadow_ob() { return SHADOWS +"owned_weapon"; }
int query_indefinite() { return 1; }
void beginning( object thing, string owner, int id ) { return; }
string merge_effect( object thing, string old_owner, string new_owner,
      int id ) {
   write( "There is a bug with the ownership of "+
         (string)thing->the_short() +" ("+ file_name( thing ) +
         ")!  Please bug report it and contact a creator!\n" );
   return old_owner;
}