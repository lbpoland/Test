inherit "/cmds/base";
int cmd( ) {
  string *cmds;
  write( "Your current commands are:\n"+ sprintf( "%-#*s\n",
         (int)this_player()->query_cols(), implode( sort_array(
         (string *)this_player()->query_known_commands(), 1 ),
         "\n" ) ) );
  if (this_player()->query_playtester()) {
    cmds = get_dir ("/cmds/playtester/");
    cmds = filter (cmds, (: strsrch ($1, ".c") == (sizeof ($1) - 2) :));
    write( "\n\nYour playtester commands are:\n"+ replace (sprintf( "%-#*s\n",
         (int)this_player()->query_cols(), implode( sort_array(
         (string *)cmds, 1 ),
         "\n" ) ), ({".c", ""})) );
  }
   return 1;
}
mixed* query_patterns() {
   return ({ "", (: cmd() :) });
}