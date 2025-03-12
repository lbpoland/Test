#include <tasks.h>
#include <player.h>
inherit "/cmds/base";
#define SKILL "other.perception"
#define GP_COST 15
nosave mapping callouts = ([]);
int cmd(string str) {
   if (this_player()->query_specific_gp("other") < GP_COST) {
      add_failed_mess("You are too weary to complete a "
                      "proper search of your surroundings.\n");
      return 0;
   }
   if (this_player()->query_property("dead")) {
      add_failed_mess("Ghosts cannot search!\n");
      return 0;
   }
   if (sizeof(filter(this_player()->query_attacker_list(),
                     (: environment($1) == environment(this_player()) :)))) {
      add_failed_mess("You cannot search, you are in combat!\n");
      return 0;
   }
   this_player()->adjust_time_left( -ROUND_TIME * 4 );
   if (callouts[this_player()->query_name()]) {
      remove_call_out(callouts[this_player()->query_name()]);
   }
   callouts[this_player()->query_name()] =
      call_out("search_callout", 4*1, this_player(), str);
   this_player()->adjust_gp(-GP_COST);
   write("You start to search around.\n");
   say(this_player()->the_short() + " $V$0=starts,start$V$ to search around.\n");
   return 1;
}
void search_callout(object who, string str) {
   mapping hide_invis;
   int i;
   string *types;
   string* ground;
   mixed see;
   object *found, ob;
   if (who->query_fighting()) {
      write("Oops!  You appear to have entered combat and cannot "
            "finish searching.\n");
      return ;
   }
   if ( function_exists( "do_search", environment( who ) ) ) {
      i = (int)environment( who )->do_search( str );
      switch(i) {
      case 1:
         return;
      case 0:
         if(query_notify_fail())
            write(query_notify_fail());
         return;
      default:
         break;
      }
   }
   if(!str) {
      found = ({ });
      foreach(ob in all_inventory(environment(who))) {
         if(ob->query_visible(who) ||
            ob->query_creator() ||
            pk_assist(this_player(), ob))
           continue;
         hide_invis =  ob->query_hide_invis();
         if(mapp(hide_invis)) {
            types = m_indices( hide_invis );
         } else {
            types = ({});
         }
         if ( !sizeof( types ) ) {
            continue;
         }
         for ( i = 0; i < sizeof( types ); i++ ) {
            if ( hide_invis[ types[ i ] ][ 0 ] == who ) {
               continue;
            }
            see = hide_invis[ types[ i ] ][ 1 ];
            if ( intp( see ) ) {
               see -= random(environment(who)->query_light());
               see /= 2;
               switch(TASKER->perform_task(who, SKILL, see, TM_FREE)) {
               case AWARD:
                  write("%^YELLOW%^"+
                        ({"You feel very perceptive", "You realise "
                             "something new about searching"})[random(2)]+
                             "%^RESET%^.\n");
               case SUCCEED:
                  found += ({ ob });
                  ob->remove_hide_invis(types[i]);
                  break;
               }
               break;
            }
         }
      }
   }
   if(sizeof(found)) {
      write("You search around and find "+query_multiple_short(found)+".\n");
   } else {
      ground = environment(who)->query_default_search_description();
      if (!ground) {
         write( ({
         "You search around for a while, but don't find anything.\n",
         "You scrounge around.  The ground does look interesting, "
            "you decide.\n",
         "You look carefully at everything, but you find nothing.\n",
         "After an intense search, you find nothing.\n" })[ random( 4 ) ] );
      } else {
         write(ground[random(sizeof(ground))]);
      }
   }
   say("$one_short:" + file_name(who) + "$ $V$0=searches,search$V$ around the "
       "place a bit.\n" );
   event(environment(who), "player_search");
   map_delete(callouts, who->query_name());
   return;
}
void interrupt_search(object who) {
   if(callouts[who->query_name()]) {
      remove_call_out(callouts[who->query_name()]);
      tell_object(who, "You stop searching.\n");
      map_delete(callouts, who->query_name());
   }
}
mixed* query_patterns() {
   return ({ "<string>", (: cmd($4[0]) :),
             "here", (: cmd(0) :),
             "", (: cmd(0) :) });
}