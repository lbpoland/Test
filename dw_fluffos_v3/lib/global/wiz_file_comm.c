#include <creator.h>
#include <login_handler.h>
#include <ls.h>
#include <playtesters.h>
#include <player_handler.h>
#include <cmds/friends.h>
#ifdef USE_LE
inherit "/global/le";
#endif
inherit "/global/wiz_object_comm";
inherit "/global/playtester";
inherit "/global/wiz_info_comm";
inherit "/global/wiz_channels";
inherit "/global/wiz_inter_comm";
private int invis;
private string *allowed;
private nosave mixed _in_wiz_editor;
private nosave string *dir_list;
private nosave mixed last_location;
private int change_dir(string str);
private int pushd(string str);
private int popd();
protected int set_home_dir(string str);
private int visible();
private int invisible(string level);
private int allow(string word);
private int disallow(string word);
void create() {
   playtester::create();
   wiz_object_comm::create();
   allowed = ({ });
}
protected void wiz_commands() {
   wiz_object_comm::wiz_commands();
   wiz_info_comm::wiz_commands();
   wiz_inter_comm::wiz_commands();
   wiz_channels::wiz_commands();
#ifdef USE_LE
   le::le_commands();
#endif
   add_command("cd", this_object(), "<string'directory'>", (: change_dir($4[0]) :));
   add_command("cd", this_object(), "", (: change_dir(0) :));
   add_command("pushd", this_object(), "<string'directory'>", (: pushd($4[0]) :));
   add_command("pushd", this_object(), "", (: pushd(0) :));
   add_command("popd", this_object(), "", (: popd() :));
   add_command("homedir", this_object(), "<string'directory'>", (: set_home_dir($4[0]) :));
   add_command("visible", this_object(), "", (: visible() :));
   add_command("vis", this_object(), "", (: visible() :));
   add_command("invisible", this_object(), "{1|2|3}", (: invisible($4[0]) :));
   add_command("invis", this_object(), "", (: invisible("1") :));
   if (this_player()->query_director()) {
      add_command("invis", this_object(), "{1|2|3}", (: invisible($4[0]) :));
   }
   add_command("allow", this_object(), "<word'name'>", (: allow($4[0]) :));
   add_command("allow", this_object(), "", (: allow(0) :));
   add_command("disallow", this_object(), "<word'name'>", (: disallow($4[0]) :));
   add_command("disallow", this_object(), "all", (: disallow("all") :));
}
nomask int query_invis() {
  return invis;
}
protected void set_invis(int level) {
   invis = level;
}
nomask string *query_allowed() {
  return copy(allowed);
}
int is_friend(string str) {
   return ::is_friend(str) ||
          member_array(str, allowed) != -1;
}
string query_friend_tag(string str) {
   string womble;
   if(!userp(previous_object())) {
     womble = ::query_friend_tag(str);
     if (!womble) {
       if (member_array(str, allowed) != -1) {
         return "allowed to reference";
       }
     }
     return womble;
   }
   return "";
}
string* query_friends() {
   if (file_name(previous_object()) == FRIENDS_CMD) {
      return ::query_friends() | allowed;
   }
   return ({ });
}
private int visible() {
   if (GetForced()) {
      return 0;
   }
   if (!query_invis()) {
      return notify_fail("You are already visible.\n");
   }
   if (invis >= 2) {
      invis = 0;
      LOGIN_HANDLER->player_logon(this_player()->query_name());
   } else {
      invis = 0;
   }
   write("You appear.\n");
   return 1;
}
private int invisible( string word ) {
   int max, type;
   if (GetForced()) {
      return 0;
   }
   if (!word) {
      word = sprintf("%d", query_invis());
      if (word == "0") {
         word = "1";
      }
   }
   max = 1 + (int)master()->query_director(query_name()) +
      (int)master()->query_trustee(query_name());
   if (!sscanf(word, "%d", type) || (type > max) || (type < 1)) {
      return notify_fail("Syntax: invisible [1"+ ( max > 1 ? "|2" : "" ) +
                         ( max > 2 ? "|3" : "" ) + "]\n");
   }
   word = ({ "frog", "creator", "director", "trustee" })[type];
   if (type == query_invis()) {
      return notify_fail("You are already "+ word +" invisible.\n");
   }
   if (type < invis && type < 2 && invis >= 2) {
      invis = type;
      LOGIN_HANDLER->player_login(this_player()->query_name());
   } else {
      invis = type;
   }
   write("You become "+ word +" invisible.\n");
   return 1;
}
private int allow(string word) {
    string player, mud;
   if (!word) {
      if (!sizeof(allowed)) {
         write("You are not allowing anyone to refer to you.\n");
      } else {
         write("You are currently allowing "+
               query_multiple_short( map_array( sort_array(allowed, 0),
                                                (: capitalize( $1 ) :))) +
               " to refer to you.\n" );
      }
      return 1;
   }
   word = lower_case(word);
   if ( word != "playtesters" && !PLAYER_HANDLER->test_user(word) &&
       sscanf( word, "%s@%s", player, mud ) != 2 ) {
      return notify_fail("There is no user called $C$"+ word +".\n");
   }
   if (member_array(word, allowed) != -1) {
      return notify_fail("You have already allowed $C$"+ word +
                         " to refer to you.\n");
   }
   allowed += ({ word });
   write(word +" is now allowed to refer to you.\n");
   return 1;
}
private int disallow(string word) {
   if (!word) {
      return notify_fail("Disallow who?\n");
   }
   if (word == "all") {
     allowed = ({ });
     write("Cleared your allow list.\n");
   } else {
     word = lower_case(word);
     allowed -= ({ word });
     write(word +" is no longer allowed to refer to you.\n");
   }
   return 1;
}
int query_visible(object thing) {
   string word;
   if (thing == this_object()) {
      return 1;
   }
   word = (string)thing->query_name();
   if (member_array(word, allowed) != -1) {
      return ::query_visible(thing);
   } else if((member_array("playtesters", allowed) != -1) &&
             PLAYTESTER_HAND->query_playtester(word)) {
     return ::query_visible(thing);
   }
   switch (query_invis()) {
   case 3 :
      return (int)master()->query_trustee(word);
   case 2 :
      return (int)master()->query_director(word);
   case 1 :
      return (int)thing->query_creator();
   default :
      return ::query_visible(thing);
   }
}
mixed query_in_editor() {
   return _in_wiz_editor || ::query_in_editor();
}
void set_in_editor(mixed what) {
   _in_wiz_editor = what;
}
private int change_dir(string str) {
   string *filenames;
   object *obs;
   if (GetForced()) {
      return 0;
   }
   if (!str) {
      if (!query_home_dir()) {
         add_failed_mess(this_object(),
                         "No homedir.  Use homedir to set it.\n", ({ }));
         return 0;
      }
      str = query_home_dir();
   }
   else {
      if ( this_object()->query_property( LS_COMMAND_NICKNAME_PROPERTY ) ) {
         str = this_object()->expand_nickname( str );
      }
   }
   filenames = get_files(str);
   if (sizeof(filenames) > 1) {
      add_failed_mess(this_object(),
                      "Ambiguous directory.\n", ({ }));
      return 0;
   }
   if (!sizeof(filenames)) {
      if (!sizeof(obs = WIZ_PRESENT->wiz_present(str, this_object()))) {
         add_failed_mess(this_object(),
                         "No such dir.\n", ({ }));
         return 0;
      }
      if (sizeof(obs) > 1) {
         add_failed_mess(this_object(),
                         "Ambiguous directory.\n", ({ }));
         return 0;
      }
      filenames =
         map(obs,
             (: sprintf("/%s",implode(explode(file_name($1), "/")[0..<2],
                                      "/")) :));
   }
   str = filenames[0];
   if (file_size(str) != -2) {
      printf("cd: %s: Not a directory.\n", str);
   } else {
      set_current_path(str);
   }
   printf("%s\n", query_current_path());
   return 1;
}
private int pushd(string str) {
   if (!dir_list) {
      dir_list = ({ });
   }
   dir_list += ({ query_current_path() });
   return change_dir(str);
}
private int popd() {
   string dest;
   if (!sizeof(dir_list)) {
      return 0;
   }
   dest = dir_list[sizeof(dir_list)-1];
   dir_list = delete(dir_list, sizeof(dir_list)-1, 1);
   return change_dir(dest);
}
string query_path() {
   return query_current_path();
}
private int set_home_dir(string str) {
   if (GetForced()) {
      return 0;
   }
   if (str) {
      ::set_home_dir(get_path(str));
   }
   printf("Home directory set to %s.\n", query_home_dir());
   return 1;
}
int query_ed_setup() {
   return query_property("ed_setup");
}
void set_ed_setup(int i) {
   add_property("ed_setup", i);
}
int review() {
   playtester::review();
   wiz_info_comm::review();
   return 1;
}
void set_last_location(mixed loc) { last_location = loc; }
mixed query_last_location() { return last_location; }
protected string process_input(string inp){
  int start;
  start = strsrch(inp, '@');
  if(start > 0){
    int space = strsrch(inp, ' ');
    if(!(space > 0 && ((space == start+1) || space < start))){
      inp = inp[0..start] + " " + inp[start+1..];
    }
  }
  start = strsrch(inp, '`');
  if(start > 0){
    int end;
    end = strsrch(inp, '`', -1);
    if(end != start){
      string lpc = inp[start+1..end-1];
      string err;
      mixed ret;
      ret = "/secure/cmds/creator/exe_c"->do_exec("return "+lpc, ref err);
      if(!err){
        if(intp(ret))
          ret = ""+ret;
        if(objectp(ret))
           ret = file_name(ret);
        if(arrayp(ret)){
          ret = filter(ret, (:stringp($1) || intp($1) || objectp($1):));
          ret = map(ret, (:intp($1)?""+$1:(objectp($1)?file_name($1):$1):));
          if(sizeof(ret))
            ret = implode(ret, ",");
        }
        if(stringp(ret)){
          inp = inp[0..start-1] + ret + inp[end+1..];
        }
      }
    }
  }
  return ::process_input(inp);
}
protected mixed command( string txt ) {
    return ::command( txt );
}