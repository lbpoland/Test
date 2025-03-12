#include <player.h>
#include <player_handler.h>
#include <cmds/friends.h>
private mapping _friends;
void create() {
   _friends = ([ ]);
}
int is_friend(string person) {
   if (!_friends) {
     _friends = ([ ]);
   }
   return stringp(_friends[person]);
}
string query_friend_tag(string person) {
  if(!interactive(previous_object()))
     return _friends[person];
  if(previous_object()->query_name())
    log_file("CHEAT", "%s query_friend_tag called on %s by %s\n",
             ctime(time()), this_object()->query_name(),
             previous_object()->query_name());
  else
    log_file("CHEAT", "%s query_friend_tag called on %s by %s\n",
             ctime(time()), this_object()->query_name(),
             file_name(previous_object()));
  return "";
}
void add_friend(string person, string tag) {
   if (strlen(tag) > PLAYER_MAX_FRIEND_TAG_LEN) {
      return ;
   }
   if (!PLAYER_HANDLER->test_user(person)) {
      return ;
   }
   _friends[person] = tag;
}
void remove_friend(string person) {
   map_delete(_friends, person);
}
string* query_friends() {
   if (file_name(previous_object()) == FRIENDS_CMD) {
      return keys(_friends);
   }
   if(previous_object()->query_name())
     log_file("CHEAT", "%s query_friends called on %s by %s\n",
              ctime(time()), this_object()->query_name(),
              previous_object()->query_name());
   else
     log_file("CHEAT", "%s query_friends called on %s by %s\n",
              ctime(time()), this_object()->query_name(),
              file_name(previous_object()));
   return ({ });
}