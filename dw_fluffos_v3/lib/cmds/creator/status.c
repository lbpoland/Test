inherit "/cmds/base";
mixed cmd(string str) {
  if (str)
    this_player()->more_string(mud_status(1), "Status info");
  else
    printf("%s", mud_status());
  return 1;
}
mixed* query_patterns() {
   return ({ "", (: cmd(0) :),
             "detailed", (: cmd("detailed") :) });
}