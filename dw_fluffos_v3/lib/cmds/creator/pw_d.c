inherit "/cmds/base";
int cmd() {
   write(this_player()->query_path() + "\n");
   return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd :) });
}