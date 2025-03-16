inherit "/std/effect_shadow";
#define HANDLER "/obj/handlers/guild_things/punishment_handler"
mixed info = ({":thinks you should contact a creator. Something is wrong.",
     ":thinks you should contact a creator. Something is wrong.",
     ":thinks you should contact a creator. Something is wrong.", 0});
int attack_by(object thing){
      info = arg();
      if(!thing->query_property("player")){
         return 1;
      }
      if(thing->query_property("Wizard attack") != player->query_name()){
         if(info[0] != 0)
            player->do_command(info[0]);
         if(info[3] <= 0)
            info[3] = 1;
         HANDLER->add_offender(thing->query_name(), "attacking "+
            player->the_short(), info[3]);
         thing->add_property("Wizard attack", player->query_name(), 600);
   }
   return 1;
}
void event_enter(object ob, string mess, object from){
      string name = ob->query_name();
      int bing;
      if(!ob->query_property("player")){
         return;
      }
      bing = (HANDLER->query_no_offences(name));
      info = arg();
      if(bing){
         if(info[1] != 0)
            player->init_command(info[1], 1);
         if(HANDLER->query_unpunished(name)){
            if(info[2] != 0)
               player->init_command(info[2], 1);
            HANDLER->punishment(name);
         }
      }
     player->event_enter(ob, mess, from);
}