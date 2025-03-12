#include <creator.h>
mixed cmd(string str) {
  return (int)PEOPLER->set_var(str);
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