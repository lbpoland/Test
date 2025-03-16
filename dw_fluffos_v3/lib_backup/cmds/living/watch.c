#define COST 50
inherit "/cmds/base";
mixed cmd() {
   if ( this_player()->query_blinded() ) {
      add_failed_mess( "How can you watch anything?  You're blind.\n" );
      return 0;
   }
   if (this_player()->query_property("dead")) {
      add_failed_mess( "Dead people don't watch. It is rude!\n");
      return 0;
   }
   if ( sizeof( (int *)this_player()->effects_matching( "mind.alertness" ) ) ) {
      add_failed_mess( "You are already alert and watching "
        "your surroundings.\n" );
      return 0;
   }
   if ( this_player()->query_specific_gp( "other" ) < COST ) {
      add_failed_mess( "You can't concentrate enough to watch "
        "your surroundings.\n" );
      return 0;
   }
   this_player()->adjust_gp( -COST );
   this_player()->add_effect( "/std/effects/other/alertness", 60 +
     (int)this_player()->query_skill_bonus( "other.perception" ) / 2 );
   return 1;
}
int stop_watching() {
   int *enums, id;
   enums = this_player()->effects_matching( "mind.alertness" );
   if ( sizeof( enums ) ) {
      foreach( id in enums ) {
         this_player()->delete_effect( id );
      }
   }
   else {
      add_succeeded_mess( ({ "You are not currently watching!\n", "" }) );
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "stop", (: stop_watching() :),
     "", (: cmd() :) });
}