#include <effect.h>
string query_classification() {return "terrain.dont.unload"; }
string query_shadow_ob() {return "/std/shadows/room/terrain_dont_unload"; }
mixed beginning( object player, mixed *arg) {
    player->setup_shad();
    return arg;
}
mixed merge_effect( object player, mixed *old, mixed *newish ) {
    player->setup_shad();
    return newish;
}