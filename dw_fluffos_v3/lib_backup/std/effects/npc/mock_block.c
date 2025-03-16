#include "path.h"
string *beginning( object player, string *skills ) {
  return skills;
}
string *merge_effect( object player, string *old, string *arg ) {
  arg = filter( arg, (: member_array( $1, $2 ) == -1 :), old );
  return old + arg;
}
string query_classification() { return "mock.block.npc"; }
string query_shadow_ob() { return SHADOWS "mock_block"; }
int query_indefinite() { return 1; }