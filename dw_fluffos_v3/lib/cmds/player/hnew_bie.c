#include <player.h>
inherit "/cmds/guild_base";
#define HIST "/obj/handlers/hist_handler"
int cmd() {
  mixed *history;
  string result;
  history = HIST->query_chat_history("newbie");
  if ( !arrayp( history ) || !sizeof( history ) ) {
    tell_object(this_player(), "Nothing has been said on the newbie "
                "channel.\n");
  }
  else {
    result = "$P$Newbie Channel$P$";
    result += implode(map(history, (: "$I$5=*" + ctime($1[2])[11..18] +
                                      "* $C$" + $1[0] + $1[1] +
                                    "%^RESET%^" :)), "\n");
    tell_object(this_player(), result);
  }
  return 1;
}
mixed *query_patterns() {
  return ({ "", (: cmd() :) });
}