inherit "/cmds/base";
int no_okay;
object tmp;
mixed cmd( string word ) {
   object *atts;
   switch( word ) {
      case "debate" :
      case "debating" :
         this_player()->interrupt_debate();
         break;
      case "spell" :
         this_player()->interrupt_spell();
         break;
      case "ritual" :
         this_player()->interrupt_ritual();
         break;
      case "fight" :
      case "fighting" :
         atts = this_player()->query_attacker_list();
         if ( !sizeof( atts ) ) {
            write( "You are not fighting anyone.\n" );
            return 1;
         }
         if ( (int)this_player()->query_hp() < 0 ) {
            write( "You have already died; stopping now is pointless.\n" );
            return 1;
         }
         write( "Stopping fight.  Please wait.\n" );
         call_out( "stop_fight", 5+random(10), this_player() );
         return 1;
      default:
         no_okay = 1;
         cmd( "debate" );
         cmd( "spell" );
         cmd( "ritual" );
         cmd( "fight" );
         no_okay = 0;
   }
   "/cmds/player/sea_rch"->interrupt_search(this_player());
   if ( !no_okay )
      write( "Okay.\n" );
   return 1;
}
void stop_fight( object who ) {
  object *atts, ob;
  if ( !who )
    return;
  atts = who->query_attacker_list();
  atts -= ({ 0 });
  tmp = who;
  if(atts == ({ }))
    return;
  tell_object( who, "You stop fighting "+
               query_multiple_short( map_array( atts,
         (: $1->query_property( "dead" ) ? (string)$1->a_short() + " (dead anyway)" : $1 :) ) ) +".\n" );
  foreach(ob in atts)
    who->stop_fight(ob);
}
mixed *query_patterns() {
   return ({ "", (: cmd(0) :),
             "{debate|debating|spell|ritual|fight|fighting}", (: cmd($4[0]) :) });
}