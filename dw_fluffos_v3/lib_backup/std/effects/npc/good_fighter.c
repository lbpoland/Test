#include "path.h"
#include <effect.h>
#define CLASS "npc.fighter"
string query_classification() { return CLASS; }
int query_indefinite() { return 1; }
string query_shadow_ob() { return SHADOWS "good_fighter"; }
void gfs(object player)
{
  player->good_fighter_setup();
}
int *beginning(object player, int *arg)
{
  if (!arg || !arrayp(arg) || sizeof(arg) != 2)
    arg = ({ 0, 0 });
  player->submit_ee("gfs", 1, EE_ONCE);
  return arg;
}
void restart(object player, int *arg)
{
  beginning(player, arg);
}
int *merge_effect(object player, int *oldarg, int *newarg)
{
  return oldarg;
}
void end(object player, int *arg)
{
}