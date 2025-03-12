inherit "/cmds/base";
#define TP this_player()
mixed cmd(string str) {
  if(TP->query_creator() || TP->query_property("setm")) {
    str = str + " ";
    if (sizeof(explode("^"+str, "$N")) < 2)
      return notify_fail("Must have a $N in your teleport entry message.\n");
    TP->set_mmsgin(str);
    write("Ok.\n");
    return 1;
  }
  return notify_fail("You are not allowed that power yet.\n");
}
mixed *query_patterns() {
   return ({ "<string>", (: cmd($4[0]) :) });
}