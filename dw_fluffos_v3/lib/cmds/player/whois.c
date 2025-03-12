#include <command.h>
inherit "/cmds/base";
mixed cmd(object *obs) {
  write("That is " + (string)(DIR_PLAYER_CMDS +"/who")->
        who_line(this_player()->expand_nickname(obs[0]),
                 this_player()->query_creator(),
                 this_player()->query_cols()) +".\n" );
  return 1;
}
mixed *query_patterns() {
  return ({ "<indirect:player>", (: cmd($1) :),
            this_player()->query_name(), (: cmd(({this_player()})) :) });
}