#include <effect.h>
#define CLASS "object.talker.response"
#define SHADOW "/std/shadows/attached/"
string query_classification() { return CLASS; }
int query_indefinite() { return 1; }
string query_shadow_ob() { return SHADOW + "talker_response"; }
mixed beginning( object item, mixed arg, int id )
{
}
mixed restart( object player, mixed arg, int id )
{
  return beginning(player, arg, id);
}
mixed merge_effect(object player, mixed oldarg, mixed newarg, int id)
{
	return oldarg;
}
void end( object player, mixed arg, int id )
{}