#define EFFECT "/std/effects/object/identity_hold"
inherit "/cmds/base";
int cmd( object *obs ) {
   object thing, *success;
   success = ({ });
   foreach (thing in obs)  {
      if (thing->query_keep())  {
         thing->reset_keep();
         success += ({ thing });
      }
   }
   if (!sizeof(success))  {
      write("You are not attempting to keep anything.\n");
   }
   else  {
      write("You will no longer attempt to keep " +
            query_multiple_short(success) + ".\n");
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:object:me>", (: cmd( $1 ) :) });
}