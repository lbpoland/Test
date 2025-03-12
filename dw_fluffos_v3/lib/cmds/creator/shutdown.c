inherit "/cmds/base";
mixed cmd(int tim, string reason, int force) {
  string str;
  seteuid(geteuid(this_player()));
  str = (string)this_player()->query_name()+" at "+ctime(time());
#ifdef GAME_LOG
  log_file("GAME_LOG", "Game shutdown by ");
  log_file("GAME_LOG", str);
  log_file("GAME_LOG", " for\n");
  log_file("GAME_LOG", num + " " + reason);
  log_file("GAME_LOG", "\n\n");
#endif
  write("Ok... shutting down game... \n");
  if (tim < 10 && (!master()->query_lord(geteuid(this_object())) && !force)) {
    tim = 10;
  }
  if (!tim) {
    "/obj/shut"->end_it_all(reason);
  } else {
    "/obj/shut"->shut(tim, reason);
  }
  return 1;
}
mixed *query_patterns() {
  return ({ "<number'number of minutes'> <string'reason'>",
              (: cmd($4[0], $4[1], 0) :),
              "now <string'reason'>", (: cmd(0, $4[0], 1) :),
              });
}