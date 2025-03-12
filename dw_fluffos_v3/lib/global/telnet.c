#include "telnet.h"
nosave string last_term;
nosave int got_terminal;
void check_terminal_type(string type);
void telnet_suboption(string str) {
  switch (str[0]) {
    case TELOPT_TTYPE :
      if (str[1] != TELQUAL_IS)
        return ;
      check_terminal_type(str[2..1000]);
      break;
  }
}
void player_connected() {
  printf("%c%c%c", IAC, DO, TELOPT_TTYPE);
  printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE);
}
void check_terminal_type(string type) {
  if (last_term == type) {
    if (!got_terminal)
      this_object()->set_network_terminal_type(0);
    return ;
  }
  if (!got_terminal && this_object()->set_network_terminal_type(type))
    got_terminal = 1;
  printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE);
  last_term = type;
}