#include <creator.h>
mixed cmd(string str) {
  object *ov, ob;
  if(strsrch(str, "in everyone") != -1)
    return notify_fail("Please don't do that.  You've been asked not to "
      "and it causes lag.\n");
  notify_fail("Pathof what?\n");
  ov = WIZ_PRESENT->wiz_present(str, this_player());
  if (!sizeof(ov)) return 0;
  foreach (ob in ov) {
    if (!objectp(ob)) continue;
    write("Path of " + WIZ_PRESENT->desc_object(ob) + " in " +
        WIZ_PRESENT->desc_object(environment(ob)) + ":\n");
    write(file_name(ob)+ "\n");
  }
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