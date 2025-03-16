#include <mail.h>
#include <player_handler.h>
mixed cmd(string str) {
  if (!str || str=="")
    str = this_player()->query_name();
  else
    str = this_player()->expand_nickname(str);
  if (!PLAYER_HANDLER->test_user(lower_case(str)))
  {
    write("Sorry, but I don't know any "+capitalize(str)+".\n");
    return 1;
  }
  write("Player "+capitalize(str)+": "+(string)MAILER->finger_mail(str));
  return 1;
}
void dest_me() {
  destruct(this_object());
}
void clean_up() {
  dest_me();
}
void reset() {
  dest_me();
}