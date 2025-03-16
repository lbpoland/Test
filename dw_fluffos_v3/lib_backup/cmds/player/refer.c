#include <login.h>
#include <clubs.h>
inherit "/cmds/base";
int cmd(string str) {
   string ret;
   str = lower_case(str);
   str = (string)this_player()->expand_nickname(str);
   ret = (string)"/secure/finger"->refer_info(str);
   if (ret) {
      this_player()->more_string( this_player()->fit_message(ret),
                                  "refer: "+str );
      return 1;
   }
   add_failed_mess("No one by the name of " + str + " has "
                   "ever visited " + mud_name() + ".\n");
   return 0;
}
mixed *query_patterns() {
   return ({"<string'name'>", (: cmd($4[0]) :) });
}