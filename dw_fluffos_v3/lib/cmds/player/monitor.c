#include <cmds/options.h>
inherit "/cmds/base";
#define TP this_player()
mixed cmd(string str) {
  int monitor;
  monitor = TP->query_monitor();
  if(!str) {
    write("Your hit point monitor is set to " + MONITOR_OPTIONS[monitor] +
          ".\n");
    return 1;
  }
  if(member_array(str, MONITOR_OPTIONS) != -1) {
    write("Your hit point monitor is set to " + str + ".\n");
    TP->set_monitor(member_array(str, MONITOR_OPTIONS));
  }
  return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd(0) :),
             "{" + implode(MONITOR_OPTIONS, "|") + "}", (: cmd($4[0]) :) });
}