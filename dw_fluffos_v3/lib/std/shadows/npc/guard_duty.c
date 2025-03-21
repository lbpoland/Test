inherit "/std/effect_shadow";
int id;
#define GOTO_DEST "/std/effects/npc/goto_destination"
int move(object ob, string in_thing, string out_thing) {
   int ret;
   ret = player->move(ob, in_thing, out_thing);
   if (ret) {
      if (id) {
         remove_call_out(id);
      }
      if  (!sizeof(player->query_following_route()) &&
           file_name(environment(player)) != arg()) {
         id = call_out(function() {
                       object *arr;
                       arr = filter(player->query_attacker_list(),
                              (: environment($1) == environment(player) :));
                       if (!sizeof(arr)) {
                          player->add_effect(GOTO_DEST, arg());
                       }
                    }, 10);
      }
   }
   return ret;
}