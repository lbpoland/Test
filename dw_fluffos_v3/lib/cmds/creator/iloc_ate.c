#include <network.h>
mixed cmd(string who) {
  if (!who) {
    notify_fail("Syntax: locate <name>\n");
    return 0;
  }
  SERVICES_D->eventSendLocateRequest(who);
  printf("Locating %s. Don't explode !\n", who);
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