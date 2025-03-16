#include <login_handler.h>
inherit "/global/wiz_file_comm";
#define ECHO_ALLOWED
void move_player_to_start(string bong, int new_pl, string c_name, string ident, int go_invis) {
  if(!sscanf(file_name(previous_object()), "/secure/login#%*s") &&
     !sscanf(file_name(previous_object()), "/secure/nlogin#%*s"))
    return 0;
#ifndef NEW_DRIVER
#endif
  ::move_player_to_start(bong, new_pl, c_name, ident, go_invis);
  write(LOGIN_HANDLER->get_message("/doc/CREATORNEWS"));
  if(query_invis()) {
    tell_object(this_object(), "===> You are currently INVISIBLE! <===\n");
  }
}
int query_creator() { return 1; }
string query_object_type(object) {
   if ( master()->query_senior( query_name() ) )
      return "S";
   return "C";
}
void receive_snoop(string bing) {
  tell_object(this_object(), "] "+bing);
}