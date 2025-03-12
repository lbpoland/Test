#include <telnet.h>
inherit "/cmds/base";
mixed cmd(string str) {
  printf("%c%c%c", IAC, DO, TELOPT_NAWS);
  write("Okay, resizing your terminal...\n");
  return 1;
}