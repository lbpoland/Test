#include <group_handler.h>
inherit "/cmds/base";
mixed cmd(string str, string pattern) {
   return GROUP_CMD->group_command_control( "list", "", "", "",
                                            ({ str }), pattern );
}
mixed *query_patterns() {
   return ({ "", (: cmd("", "list") :),
             "[with] <string'player'>",
             (: cmd($4[0], "list [with] <string'player'>") :) });
}