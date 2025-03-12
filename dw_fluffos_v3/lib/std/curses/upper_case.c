#include "path.h"
#define MY_NAME "UPPER CASE"
object my_player;
int init_curse(object pl) {
  string str;
  int i;
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
int query_remove() { return 1; }
int player_start(object pl) {
  object ob;
  if (!pl)
    pl = this_player();
  ob = clone_object(file_name(this_object()));
  ob->init_curse(pl);
}
int destruct_curse(string str) {
  if (str == MY_NAME)
    destruct(this_object());
  else
    my_player->destruct_curse(str);
}
protected string upper_case(string str) {
  string ret;
  int i;
  ret = "";
  for (i=0;i<strlen(str);i++)
    ret += capitalize(str[i..i]);
  return ret;
}
int do_say(string str) {
  return (int)my_player->do_say(upper_case(str));
}
int do_tell(string str) {
  return (int)my_player->do_tell(upper_case(str));
}
int do_loud_say(string str) {
  return (int)my_player->do_loud_say(upper_case(str));
}
int do_echo(string str) {
  return (int)my_player->do_echo(upper_case(str));
}
int do_emote_all(string str) {
  return (int)my_player->do_echo_all(upper_case(str));
}
int do_emote(string str) {
  return (int)my_player->do_emote(upper_case(str));
}
int do_whisper(string str) {
  return (int)my_player->do_whisper(upper_case(str));
}
int do_echo_to(string str) {
  return (int)my_player->do_echo_to(upper_case(str));
}
int do_shout(string str) {
  return (int)my_player->do_shout(upper_case(str));
}