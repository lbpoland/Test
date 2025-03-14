#include <player.h>
#define MAXLEN 30
inherit "/cmds/base";
private string* _bad_words;
void create() {
   _bad_words = ({ "teach", "skill", "finger", "lesson", ":)", ";)",
                   "chainsaw", "0", "1", "2", "3", "4", "5", "6", "7", "8",
                   "9", ":", ";", ",", "'", "*", "%", "!",
                   "@", "~", "`", "#", "$", "^", "&", "(", ")",
                   "_", "-", "=", "+", "{", "}", "[", "]",
                   "<", ".", ">", "?", "/", "\\",
                   ":->", ":-)", ";-)", ";->", "\""});
}
int cmd( string new_pos ) {
  object player = this_player();
  string word, tmp;
  if (!new_pos) {
    write("You are " + player->query_position_short() + ".\n");
    return 1;
  }
  if ( strlen(new_pos) > MAXLEN ) {
    add_failed_mess("Sorry, your position cannot be more than " +
                        MAXLEN + " letters long.\n");
    return 0;
  }
  if ( player->query_sp() < SET_POSITION_COST ) {
    add_failed_mess( NO_POWER );
    return 0;
  }
  new_pos = replace_string(new_pos, "^", "");
  new_pos = replace_string(new_pos, "%", "");
  tmp = lower_case(new_pos);
  foreach(word in _bad_words) {
    if(strsrch(tmp, word) != -1) {
      add_failed_mess("You cannot bring yourself to set that position.\n");
      return 0;
    }
  }
  player->set_position( new_pos );
  player->adjust_sp( - SET_POSITION_COST );
  tell_object( player, "People will now see:\n" +
               player->query_cap_name() + " is " + new_pos + ".\n");
  return 1;
}
mixed *query_patterns() {
  return ({ "", (: cmd(0) :),
          "<string'new position'>", (: cmd( $4[0] ) :) });
}