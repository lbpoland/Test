#include <npc/events.h>
inherit "/obj/monster";
inherit "/std/npc/goals_inherit";
int _last_hp;
protected int check_heart_beat_results();
void create() {
   goals_inherit::create();
   monster::create();
}
void heart_beat() {
   int hp;
   ::heart_beat();
   call_out((: check_heart_beat_results :), 0);
}
protected int check_heart_beat_results() {
   hp = query_hp();
   if (hp != _last_hp) {
      if (hp > _last_hp) {
         notify_npc_event(EVENT_GAIN_HPS, hp - _last_hp, hp);
      } else {
         notify_npc_event(EVENT_LOSE_HPS, _last_hp - hp, hp);
      }
      _last_hp = hp;
   }
}
mixed *stats() {
   return monster::stats() + goals_inherit::stats();
}
int move(mixed dest, string messin, string messout) {
   int ret;
   object from;
   from = environment();
   ret = ::move(dest, messin, messout);
   if (from) {
      call_out((: notify_npc_event :), 0, EVENT_MOVED, from);
   }
   return ret;
}
void event_enter(object moving, string mess, object from) {
   if (living(from)) {
      call_out((: notify_npc_event :), 0, EVENT_GIVEN, moving);
   }
}