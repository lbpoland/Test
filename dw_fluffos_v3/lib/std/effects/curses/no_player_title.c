#include <effect.h>
#include "path.h"
void beginning( object ob, int time, int id ) {
    if ( time > 0 ) {
        ob->submitt_ee( 0, time, EE_REMOVE );
    }
}
void end( object ob, int time, int id ) {
}
string query_classification() {
    return "player.no-title-allowed";
}
string query_shadow_ob() {
    return SHADOWS + "no_player_title";
}
void spam( object player, mixed args, int id ) {
tell_creator ("taffyd", "Spam\n" );
}