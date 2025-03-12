#include <mail.h>
mixed cmd(string str) {
  return (int)MAIL_TRACK->mail(str);
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