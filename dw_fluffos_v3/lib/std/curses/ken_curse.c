#include "path.h"
#define MY_NAME "ken curse"
object my_player;
int init_curse(object pl) {
  string str, i;
  if (sscanf((str = file_name(this_object())), "%s#%d", str, i) != 2) {
    seteuid((string)"/secure/master"->creator_file(str));
    return (int)clone_object(str)->init_curse(pl);
  }
  my_player = pl;
  pl->add_curse(MY_NAME, str);
  if (!shadow(pl, 1)) {
    pl->remove_curse(MY_NAME);
    return 0;
  }
  return 1;
}
int query_remove(string name) {
  if (name != MY_NAME)
    return (int)my_player->query_remove(name);
  return 1;
}
int player_start(object pl) {
  object ob;
  if (!pl)
    pl = this_player();
  ob = clone_object(HERE+"ken_curse");
  ob->init_curse(pl);
}
int destruct_curse(string str) {
  if (str == MY_NAME)
    destruct(this_object());
  else
    my_player->destruct_curse(str);
}
int do_emote_all(string str) {
  return (int)my_player->do_emote_all((HERE+"ken_mangle")->do_transmute(str));
}
int do_shout(string str) {
  return (int)my_player->do_shout((HERE+"ken_mangle")->do_transmute(str));
}
int do_say(string str) {
  return (int)my_player->do_say((HERE+"ken_mangle")->do_transmute(str));
}
int do_loud_say(string str) {
  return (int)my_player->do_loud_say((HERE+"ken_mangle")->do_transmute(str));
}
int do_emote(string str) {
  return (int)my_player->do_emote((HERE+"ken_mangle")->do_transmute(str));
}
int do_tell(string str) {
  string s1;
  if (sscanf(str, "%s %s", s1, str) != 2)
    return (int)my_player->do_tell(str);
  return (int)my_player->do_tell(s1+" "+(HERE+"ken_mangle")->do_transmute(str));
}