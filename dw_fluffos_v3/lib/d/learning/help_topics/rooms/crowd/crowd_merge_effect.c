#include <effect.h>
#include "path.h"
#define SHADOWS  CROWD
mixed beginning( object player, mixed arg, int id ) {
  call_out( (: $1->crowd_merge() :), 5, player );
}
mixed merge_effect( object player, mixed oldarg, mixed newarg, int id ) {
   return newarg;
}
string query_classification() { return "npc.crowd.merge"; }
string query_shadow_ob() { return SHADOWS + "crowd_merge_shadow"; }