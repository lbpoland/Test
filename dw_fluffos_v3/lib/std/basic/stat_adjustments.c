#include <effects/stat_adjustment.h>
private nosave mapping _adjs;
void create() {
   _adjs = ([ ]);
}
void set_stat_adjustment(object player, mapping adjs) {
   _adjs[player] = adjs;
   player->add_effect(STAT_ADJUSTMENT_EFFECT, ({ this_object(), adjs }));
}
void remove_stat_adjustment(object player) {
   STAT_ADJUSTMENT_EFFECT->remove_stat_adjustment_ob(player, this_object());
   map_delete(_adjs, player);
}
void remove_all_stat_adjustments() {
   mapping adj;
   object play;
   foreach (play, adj in _adjs) {
      STAT_ADJUSTMENT_EFFECT->remove_stat_adjustment_ob(play, this_object());
      map_delete(_adjs, play);
   }
   _adjs = ([ ]);
}
mapping query_stat_adjustments(object play) {
   return _adjs[play];
}