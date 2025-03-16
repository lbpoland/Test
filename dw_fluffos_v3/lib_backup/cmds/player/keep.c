#define EFFECT "/std/effects/object/identity_hold"
inherit "/cmds/base";
int cmd( object *obs )  {
   object thing;
   foreach(thing in obs) {
      thing->add_effect( EFFECT, ([ "keep" : 1 ]) );
   }
   write( "You will now attempt to keep "+
         (string)query_multiple_short(obs)+".\n" );
   return 1;
}
int cmd_list() {
   object* obs;
   obs = all_inventory(this_player());
   obs = filter(obs, (: $1->query_keep() :) );
   if (!sizeof(obs)) {
      add_failed_mess("You are not keeping anything.\n");
      return 0;
   }
   write("You are keeping " + query_multiple_short(obs) + ".\n");
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:object:me>", (: cmd( $1 ) :),
             "", (: cmd_list :) });
}