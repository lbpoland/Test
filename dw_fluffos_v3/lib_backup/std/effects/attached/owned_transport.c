#include <player.h>
inherit "/std/basic/virtual_quit_control";
class riding {
   object* transport;
   string* environments;
   mixed save_stuff;
}
private nosave int _transport_id;
void create() {
   _transport_id = random(3000) + 1;
}
string query_classification() {
   return "mudlib.riding.owned";
}
int query_indefinite() {
   return 1;
}
class riding beginning(object player, object transport, int id) {
   class riding bing;
   bing = new(class riding);
   bing->transport = ({ transport });
   bing->save_stuff = 0;
   transport->set_transport_id(_transport_id++);
   return bing;
}
class riding merge_effect(object player, class riding fluff, object transport) {
   if ( member_array(transport, fluff->transport) == -1) {
      if (!transport->query_transport_id()) {
         while(sizeof(filter(fluff->transport,
                             (: $1 && $1->query_transport_id() == $2 :),
                             _transport_id))) {
            _transport_id++;
         }
         transport->set_transport_id(_transport_id++);
      } else if (sizeof(filter(fluff->transport,
                        (: $1 && $1->query_transport_id() == $2 :),
                        transport->query_transport_id()))) {
         transport->dest_me();
         return fluff;
      }
      fluff->transport += ({ transport });
   }
   return fluff;
}
void end(object player, class riding arg) {
}
void restart(object player, class riding bing) {
   int i;
   object* blue;
   object* green;
   blue = filter(bing->transport, (: $1 :));
   if (!sizeof(blue) &&
       bing->save_stuff) {
      green = AUTO_LOAD_OB->load_auto_load_to_array(bing->save_stuff,
                                         player);
      for (i = 0; i < sizeof(bing->transport); i++) {
         if (green) {
            bing->transport[i] = green[i];
            green->move(bing->environments[i],
                        "$N appears with a puff of fluff.");
         }
      }
   }
}
void clear_thingy(class riding bing) {
   bing->save_stuff = 0;
}
void saving(object player, class riding bing) {
   string *env;
   bing->transport -= ({ 0 });
   env = map(bing->transport,
             (: find_start_pos($1, environment($1)) :));
   bing->environments = map(bing->transport,
                            (: find_start_pos($1, environment($1)) :));
   bing->save_stuff = AUTO_LOAD_OB->create_auto_load( bing->transport );
   call_out( (: clear_thingy :), 2, bing);
}
void quiting(object player, class riding bing) {
   call_out((: $1->move("/room/rubbish", 0,
                        "$N vanishes in a puff of fluff.") :),
            2, bing->transport);
}
void remove_owner(object player, class riding bing, int id, object trans) {
   bing->transport -= ({ trans });
   if (!sizeof(bing->transport)) {
      player->delete_effect(id);
   }
}