#include <move_failures.h>
inherit "/std/effect_shadow";
int actually_attacked=0;
varargs void crowd_merge() {
  object crowd,thing;
  object *list;
  crowd=(arg())[0];
  if (!crowd) {
    int *effs=player->effects_matching("npc.crowd.merge");
    player->delete_effect(effs[0]);
    return;
  }
  if (sizeof(player->query_attacker_list()) ||
     (player->query_hp()<player->query_max_hp())) {
    call_out( "crowd_merge", 60 );
    return;
  }
  if (actually_attacked) {
    foreach( thing in filter(all_inventory(environment(player)),
          (: living($1) :) )) {
      if ( (list = thing->query_attacker_list())
           && member_array(player,list) != -1 ) {
        call_out( "crowd_merge", 60 );
        return;
      }
    }
  }
  if ( environment(player) == environment(crowd) ) {
    crowd->merge_crowd_member( player );
    return;
  }
  player->add_effect( "/std/effects/npc/goto_destination",
    ({ file_name(environment(crowd)),
       ({ this_object(), "crowd_merge" }), 1 }) );
}
int attack_by( object thing ) {
  actually_attacked=1;
  return player->attack_by( thing );
}
object crowd_object( ) { return (arg())[0]; }
object crowd_number() { return (arg())[1]; }
object do_death( object thing) {
   if ((arg())[0]) ((arg())[0])->crowd_member_died();
   return player->do_death( thing );
}