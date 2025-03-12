#include <command.h>
inherit "/cmds/base";
mixed cmd() {
   write("Nothing happens.\n" );
   return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd() :) });
}