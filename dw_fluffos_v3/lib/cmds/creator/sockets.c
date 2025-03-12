inherit "/cmds/base";
mixed cmd(string ) {
  this_player()->more_string(dump_socket_status());
  return 1;
}