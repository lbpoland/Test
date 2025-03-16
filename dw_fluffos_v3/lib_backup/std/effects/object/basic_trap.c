#include "path.h"
string query_classification() { return "object.trap.basic"; }
string query_shadow_ob() { return SHADOWS +"basic_trap"; }
int query_indefinite() { return 1; }
int beginning( object thing, int amount, int id ) {
	tell_object(find_player("ceres"), sprintf("Adding trap to %O\n",
																						thing));
	thing->set_lock_trap(thing, "trap_lock");
	return 0;
}