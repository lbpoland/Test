#define TP this_player()
inherit "/cmds/base";
int cmd() {
   int no_limbs;
   string stuff;
   object thing;
   object *equipped;
   object *things;
   equipped = ({ });
   things = all_inventory( TP ) - TP->query_wearing() -
            TP->query_holding();
   foreach ( thing in things ) {
      no_limbs = thing->query_no_limbs();
      if ( no_limbs > TP->query_free_limbs() ) {
         continue;
      }
      if ( thing->query_wearable() ) {
         if ( !TP->wear_armour( thing, 0 ) ) {
            equipped += ({ thing });
         }
         continue;
      }
      if (thing->query_weapon() && no_limbs) {
         if ( sizeof( TP->set_hold( thing,
               member_array( 0, TP->query_holding() ) ) ) ) {
            equipped += ({ thing });
         }
      }
   }
   if ( !sizeof( equipped ) ) {
      return notify_fail( "You have no equippable items.\n" );
   }
   stuff = query_multiple_short( equipped );
   say( (string)TP->one_short() +" equips "+ stuff +".\n" );
   write( "You equip "+ stuff +".\n" );
   return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd() :) });
}