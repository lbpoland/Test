#include <effect.h>
void beginning( object player, int time, int id ) {
   if (time == 0) {
      time = 30*60;
   }
   player->submit_ee( "create_bug", ({ 5*60, 5*60 }), EE_CONTINUOUS );
   player->submit_ee( 0, time, EE_REMOVE );
}
void end( object player, int time, int id ) {
}
void create_bug( object player, int time, int id ) {
   object bug;
   object room;
   string env_string;
   object *ignore;
   bug = clone_object("/obj/monster/cockroach");
   room = environment(player);
   env_string = player->the_short();
   ignore = ({ });
   while (room) {
      if (room == environment(player) && living(player)) {
         tell_object(player, env_string+" have "+bug->a_short()+
                             " suddenly pop out of your "
                             "ear.\n");
         ignore += ({ player });
         tell_room(room, env_string+" has "+bug->a_short()+
                         " suddenly pop out of "+
                         player->query_possessive()+
                         " ear.\n", ignore);
      } else if (living(player)) {
         tell_room(room, env_string+" has "+bug->a_short()+
                         " suddenly pop out of "+
                         player->query_possessive()+
                         " ear.\n", ignore);
      } else {
         tell_room(room, env_string+" has "+bug->a_short()+
                         " suddenly pop out of it.\n", ignore);
      }
      if (living(room))
        ignore += ({ room });
      env_string = env_string + " in " + room->the_short();
      if (!environment(room))
        bug->move(room);
      room = environment(room);
   }
}
string query_classification() { return "object.bug"; }