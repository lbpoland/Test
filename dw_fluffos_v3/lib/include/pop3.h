#ifndef __POP3_H
#define __POP3_H
#define PORT_POP3 4110
#define POP3_VERSION "0.1"
#define POP_AUTH_USER   0
#define POP_AUTH_PASS   1
#define POP_TRANSACTION 2
#define POP_UPDATE      3
#define LOGIN_OB "/secure/login"
#define FOLDER_H "/obj/handlers/folder_handler"
#define DEBUG
#ifdef DEBUG
#define TP(_x) tell_object(find_player("turrican"), (_x))
#else
#define TP(_x)
#endif
#define CHECK_STATE(_state) if ((_state) != sess->state) \
{ \
    eventWrite(fd, sprintf("-ERR Unknown command in %s state\r\n", \
                           pop_states[sess->state])); \
    break; \
}
#define CHECK_CMD(_num, _str) if (sizeof(bits) < (_num)+1) \
                       { \
                         eventWrite(fd, _str); \
                         break; \
                       }
class pop_session {
  int fd;
  int state;
  int time;
  string command;
  string user_name;
  int *deleted;
  int num_messages;
  class mail_header *headers;
  string *messages;
  int *sizes;
  int last;
}
#endif