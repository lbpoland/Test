#include <command.h>
inherit "/cmds/base";
mixed cmd() {
  write( "You are "+ (string)( DIR_PLAYER_CMDS +"/who" )->
         who_line(this_player(), this_player()->query_creator(),
                  this_player()->query_cols(), 1) +".\n" );
  return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd() :) });
}