#include <armoury.h>
#define CMD_D "/secure/command"
mixed cmd(string str) {
  if (!str)
    return notify_fail("Syntax: rehash <path>\n");
  if (file_size(str) != -2)
    return notify_fail(str+": Path not found.\n");
  if (str[0..4] == "/doc/") {
     "/cmds/player/help"->rehash_specific_dir(str);
     write("Rehashed help dir: " + str + "\n");
     return 1;
  }
  if (str[0..4] == "/obj/" || str[0..2] == "/d/") {
     if (ARMOURY->rehash_specific_dir(str)) {
        write("Rehashed armoury dir: " + str + "\n");
        return 1;
     }
  }
  CMD_D->eventRehash(str);
  write(str+": Rehashed.\n");
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