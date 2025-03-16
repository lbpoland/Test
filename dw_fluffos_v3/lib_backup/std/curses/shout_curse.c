#include "path.h"
#define MY_NAME "Shout curse"
object my_player;
int init_curse(object pl) {
  string str, i;
  if (sscanf((str = file_name(this_object())), "%s#%d", str, i) != 2) {
    seteuid((string)"/secure/master"->creator_file(str));
    return (int)clone_object(str)->init_curse(pl);
  }
  my_player = pl;
  printf("%O, %O\n", pl, this_object());
  pl->add_curse(MY_NAME, str);
  if (!shadow(pl, 1)) {
    pl->remove_curse(MY_NAME);
    return 0;
  }
  return 1;
}
int query_remove(string name) {
  return 1;
}
int player_start(object pl) {
  object ob;
  if (!pl)
    pl = this_player();
  ob = clone_object(HERE+"shout_curse");
  ob->init_curse(pl);
}
int destruct_curse(string str) {
  if (str == MY_NAME)
    destruct(this_object());
  else
    my_player->destruct_curse(str);
}
int do_emote_all(string str) {
  write("Your voice is too hoarse to shout.\n");
  return 1;
}
int do_shout(string str) {
  write("Your voice is too hoarse to shout.\n");
  return 1;
}