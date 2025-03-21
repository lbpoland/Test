#include <config.h>
#include <board.h>
#include <bounty.h>
#ifndef __DISTRIBUTION_LIB__
#include <deity.h>
#endif
#include <drinks.h>
#include <library.h>
#include <living.h>
#include <login.h>
#include <login_handler.h>
#include <log.h>
#include <quest_handler.h>
#include <command.h>
#include <mail.h>
#include <player.h>
#include <skills.h>
#include <top_ten_tables.h>
#include <tune.h>
#include <weather.h>
#include <refresh.h>
#include <nroff.h>
#include <db.h>
#include <error_handler.h>
#include <player_handler.h>
#include <playerinfo.h>
#include <group_handler.h>
class player_info {
   int hb_num;
   int level;
   int level_time;
   int save_inhibit;
   int update_tmps_call_out;
   int last_save;
   object snoopee;
   mapping titles;
}
#include <clubs.h>
inherit "/global/line_ed";
inherit "/global/events";
inherit "/global/log";
inherit "/global/spells";
inherit "/global/more_string";
inherit "/global/finger";
inherit "/global/pweath";
inherit "/std/living/living";
inherit "/global/psoul";
inherit "/global/guild-race";
inherit "/global/more_file";
inherit "/global/path";
inherit "/global/start_position";
inherit "/global/family";
#define MIN_TIME_TO_SAVE 1800
#define FORGOT_CO_ORD_TIME (840553267+(8*60*60))
#define LEVEL_CACHE 60
#define ITEM_TRACKER ("/obj/handlers/item_tracker")
private nosave class player_info _pinfo;
private int time_on;
private int max_deaths;
private int monitor;
private int _refresh_time;
private int start_time;
private int creator;
private int deaths;
private int last_log_on;
private int no_logins;
private int activity_counter;
private int _flags;
private string cap_name;
private string last_on_from;
private nosave string my_file_name;
void start_player();
void public_commands();
int save();
void set_desc(string str);
void do_load_auto();
void set_name(string str);
int check_dark(int light);
void continue_start_player();
int restart_heart_beat();
int brief_verbose(string,
                  string);
int quit_alt(int verbose);
int review();
int toggle_wimpy(string);
int do_refresh(string);
int do_cap(string);
protected void set_invis(int level);
void set_player_killer(int);
int query_player_killer();
void finished_error_check( object player, string my_name, int status,
    mixed data );
void check_error_count();
void check_approve_list();
void create()
{
   if (query_name()) {
      return;
   }
   living::create();
   events::create();
   psoul::create();
   line_ed::create();
   more_string::create();
   start_position::create();
   add_property("determinate", "");
   spells::create();
   time_on = time();
   start_time = time();
   seteuid("PLAYER");
   Str = 13;
   Dex = 13;
   Int = 13;
   Con = 13;
   Wis = 13;
   set_max_sp(50);
   set_sp(50);
   wimpy = 20;
   max_deaths = 7;
   set_desc(0);
   add_ac("bing", "blunt", 15);
   add_ac("bing2", "sharp", 15);
   add_ac("bing3", "pierce", 15);
   add_property("player", 1);
   set_cols(79);
   set_rows(24);
   last_log_on = time();
   race_ob = RACE_STD;
   sscanf(file_name(this_object()), "%s#", my_file_name);
   _pinfo = new (class player_info, titles: ([ ]), save_inhibit:1);
}
void dest_me()
{
   if ((query_name() != "object") && objectp(this_player()) &&
       (this_player() != this_object()) &&
       (file_name(this_player()) != "/obj/shut") &&
       (explode(file_name(this_player()), "#")[0] != "/secure/login") &&
       (explode(file_name(this_player()), "#")[0] != "/secure/nlogin")) {
      user_event(this_object(), "inform",
                 (string) this_player()->query_name() +
                 " dests " + query_name(), "dest");
      tell_object(this_object(), "You were destructed by " +
                  capitalize((string) this_player()->query_name()) + ".\n");
   }
   if(file_size(PLAYER_HANDLER->query_player_file_name(query_name())+
                ".o.gz") > 0 &&
      PLAYER_HANDLER->query_player_disk_file_name(query_name()) &&
      PLAYER_HANDLER->query_player_file_name(query_name()) !=
      PLAYER_HANDLER->query_player_disk_file_name(query_name())) {
     unguarded((:rename,
                PLAYER_HANDLER->query_player_file_name(query_name())+".o.gz",
                PLAYER_HANDLER->query_player_disk_file_name(query_name())+
                ".o.gz" :));
   }
   ::dest_me();
}
void disallow_save()
{
   _pinfo->save_inhibit = 1;
}
void allow_save()
{
   _pinfo->save_inhibit = 0;
}
int query_save_inhibit()
{
   return _pinfo->save_inhibit;
}
int query_start_time()
{
   return start_time;
}
nomask string query_cap_name()
{
   return cap_name;
}
void move_player_to_start(string bong,
                          int new_flag,
                          string c_name,
                          string ident,
                          int go_invis) {
  string lang;
   if (file_name(previous_object())[0..12] != "/secure/login" &&
       file_name(previous_object())[0..13] != "/secure/nlogin") {
      write("You don't have clearance to do that.\n");
      return;
   }
   seteuid("Root");
   set_name(bong);
   if (!new_flag) {
      unguarded((: restore_object,
                   PLAYER_HANDLER->query_player_file_name(query_name()), 1 :));
      if (go_invis) {
        switch(go_invis) {
        case -1:
          set_invis(0);
          break;
        case 2:
          if (this_object()->query_lord()) {
            set_invis(2);
            break;
          }
        case 1:
          set_invis(1);
        }
      }
   }
   disallow_save();
   add_property("player", 1);
   cap_name = c_name;
   set_short(cap_name);
   add_property("determinate", "");
   no_logins++;
   if (!query_cols()) {
      set_cols(79);
   }
   remove_property("new player");
   if (this_player()->query_creator()) {
      seteuid(query_name());
      if (file_size("/w/" + query_name() + "/cmds") == -2)
         AddSearchPath(({ "/w/" + query_name() + "/cmds" }));
      AddSearchPath(({ DIR_PLAYER_CMDS, DIR_SECURE_PLAYER_CMDS,
                       DIR_CREATOR_CMDS, DIR_SECURE_CREATOR_CMDS,
                       DIR_PLAYTESTER_CMDS }));
   } else {
      seteuid("PLAYER");
      AddSearchPath(({ DIR_PLAYER_CMDS, DIR_SECURE_PLAYER_CMDS }));
   }
   if (!last_on_from) {
      printf("You have never logged in before.\n");
   } else {
      printf("You last logged in from %s and are currently "
             "logged in from %s (%s).\n", last_on_from,
             query_ip_name(this_object()), query_ip_number(this_object()));
   }
   last_on_from = query_ip_name(this_object()) + " (" +
      query_ip_number(this_object()) + ")";
   if (time_on > 0) {
      time_on = 0;
   }
   time_on += time();
   if (new_flag) {
      add_property("new player!", 1);
   }
   LOGIN_HANDLER->player_logon(bong, query_property("guest"),
                               (query_ip_name()? query_ip_name() :
                                query_ip_number()));
   if(query_property("guest")) {
     this_player()->set_nationality(DEFAULT_NATIONALITY);
     this_player()->
       set_nationality_region(this_player()->find_region(DEFAULT_NATIONALITY,
                                                         DEFAULT_REGION));
     lang = DEFAULT_NATIONALITY->query_language();
     this_player()->add_language(lang);
     this_player()->set_default_language(lang);
     this_player()->set_language(lang);
   }
   write(LOGIN_HANDLER->get_message("/doc/NEWS"));
   call_out((: continue_start_player :), 0);
   PLAYER_HANDLER->remove_cache_entry(query_name());
}
protected void move_to_start_pos()
{
   ::move_to_start_pos();
   if (query_verbose("look"))
      command("look");
   else
      command("glance");
   if (!finger_set()) {
      write
         ("%^BOLD%^Please set your finger information with 'chfn'.%^RESET%^\n");
   }
   if(no_logins == 1 && !query_property("guest")) {
     write("\n%^BOLD%^" +
           LOGIN_HANDLER->get_message("/doc/login/NEW_USER_START") +
           "%^RESET%^\n");
   }
   no_time_left();
   START_PLAYER->logged_on_times(no_logins);
   if(query_ip_number(this_object()) == query_ip_name(this_object()))
     resolve(query_ip_number(this_object()), "");
}
protected void update_activity(int logon)
{
   int time_on;
   if (last_log_on > 0) {
      time_on = last_command - last_log_on;
      if (time_on > 0)
         activity_counter -= (time_on / (3600 * 24 * 7)) * 10;
   }
   if (activity_counter <= -55) {
      activity_counter = -55;
   }
   if (logon) {
      activity_counter += 3;
   } else {
      activity_counter += 2 * ((time() - last_log_on) / 3600);
   }
   if (activity_counter >= 0)
      activity_counter = 0;
}
int query_activity_counter()
{
   return activity_counter;
}
private void display_bug_replies(int type, class error_replies* replies) {
   if (type == DB_SUCCESS) {
      if (sizeof(replies) > 0) {
         tell_object(this_object(), "\n\nYou have %^YELLOW%^" +
            sizeof(replies) + " NEW%^RESET%^ bug repl" +
            (sizeof(replies) > 1?"ies ":"y ") +
            "(read with 'bug replies').\n\n");
      }
   }
}
private void check_mccp() {
   if(!compressedp(this_object())) {
     write("\n%^BOLD%^%^RED%^You are logged in uncompressed!\n");
     write("Use of an MCCP capable mud client will reduce your load on "
           "the " + mud_name() + " system.%^RESET%^\n\n");
   }
}
void continue_start_player()
{
   string title;
   mapping news_rc;
   mixed *stuff;
   object book;
   if (this_object()->query_lord()) {
      creator = 1;
   }
   start_player();
   no_time_left();
   if (query_property(PASSED_OUT) && !query_property(TRANCE)) {
      call_out((: remove_property :), 10 + random(30), PASSED_OUT);
   }
   remove_property(UNKNOWN_MOVE);
   remove_property(RUNNING_MOVE);
   init_after_save();
   printf("%s", fix_string(MAILER->new_mail(query_name())));
   news_rc = BOARD_HAND->query_newsrc(query_name());
   if (!news_rc) {
      news_rc = ([ ]);
   }
   stuff = BOARD_HAND->get_subjects("announcements");
   if (sizeof(stuff)) {
      if (stuff[<1][B_TIME] > news_rc["announcements"]) {
         write("\nThere are %^YELLOW%^NEW%^RESET%^ announcements.  ");
         write("You can read them with \"news\".\n\n");
      }
   }
   call_out((: check_mccp :), 4);
   if (query_property("dead")) {
      (clone_object(DEATH_SHADOW))->setup_shadow(this_object());
      book = clone_object(DEAD_BOOK);
      book->move(this_object());
   }
   if (query_property("noregen")) {
      DEATH->person_died(query_name());
   }
   exec_alias("login", "");
   update_activity(1);
   last_log_on = time();
   title = LIBRARY->query_title(query_name());
   if (stringp(title)) {
      _pinfo->titles += ([ "quest" : title ]);
   }
   if (my_file_name != "/global/player") {
      check_error_count();
      if(my_file_name != "/global/playtester") {
        check_approve_list();
      }
   }
   if (query_property("new player!")) {
     PLAYERINFO_HANDLER->player_created(query_name());
      user_event(this_object(), "inform",
                 capitalize(query_name()) +
                 " arrives on " + mud_name() + " for the first time!", "new-player");
      remove_property("new player!");
      set_last_pos(CONFIG_NEWBIE_START_LOCATION);
      START_PLAYER->start_player(this_object());
   }
   check_family_name();
   call_out((: move_to_start_pos :), 0);
   call_out((: set_heart_beat(1) :), 1);
   ERROR_HANDLER->do_error_replies(query_name(), 1, (: display_bug_replies :));
}
void check_error_count() {
   string my_name;
   my_name = query_name();
   DB_HANDLER->make_sql_request( "errors", "atuin", "",
      "SELECT COUNT(Id) AS idc FROM errors WHERE Directory = '/w/" +
      my_name + "' AND Status = 'OPEN'",
       (: finished_error_check, this_object(), my_name :) );
}
void finished_error_check( object player, string my_name, int status,
    mixed data ) {
   int num;
   int ret;
   if ( file_size("/w/" + my_name + "/" + PLAYER_ERROR_LOG) > 0 ) {
       num = file_length("/w/" + my_name + "/" + PLAYER_ERROR_LOG);
       tell_object( player, "%^YELLOW%^You have %^RED%^" + num +
           "%^YELLOW%^ director" + (num == 1 ? "y" : "ies") +
           " with %^RED%^ERRORS%^YELLOW%^ in /w/" + my_name + "/" +
           PLAYER_ERROR_LOG + ".%^RESET%^\n");
   }
   if ( status == DB_SUCCESS && sizeof( data ) > 0 ) {
      if ( ( ret = data[0]["idc"] ) > 0 ) {
         tell_object( player, "%^YELLOW%^You have %^RED%^" + ret +
            " ERROR" +  (ret == 1 ? "" : "S") + "%^YELLOW%^ in /w/" +
            my_name +  ".%^RESET%^\n");
      }
   }
}
void check_approve_list() {
  string str;
  mapping assignments;
  int count;
  assignments = master()->query_directory_assignments();
  foreach(str in keys(assignments)) {
    if(member_array(this_object()->query_name(), assignments[str]) != -1 &&
       file_size(str + "/to_approve")) {
      count = sizeof(get_dir(str + "/to_approve
void start_player()
{
   if (this_object()->query_creator() && my_file_name != "/global/player") {
      this_player()->all_commands();
      this_player()->app_commands();
      this_player()->wiz_commands();
   }
   call_out((: do_load_auto :), 1);
   reset_get();
   enable_commands();
   public_commands();
   command_commands();
   parser_commands();
   force_commands();
   race_guild_commands();
   soul_commands();
   event_commands();
   finger_commands();
   communicate_commands();
   living_commands();
   logging_commands();
   editor_commands();
   if (this_player()->query_creator()) {
      set_living_name(query_name());
   }
   set_no_check(1);
   set_con(Con);
   set_dex(Dex);
   set_int(Int);
   set_str(Str);
   set_wis(Wis);
   reset_all();
   set_current_path(query_home_dir());
   if (wimpy > 100) {
      wimpy = 25;
   }
   if (contmp || dextmp || inttmp || strtmp || wistmp) {
      _pinfo->update_tmps_call_out = call_out((: update_tmps :), 900);
   }
}
int adjust_hp(int number,
              object attacker,
              object weapon,
              string attack)
{
   if (!interactive(this_object()))
      return query_hp();
   return::adjust_hp(number, attacker, weapon, attack);
}
void do_load_auto()
{
   load_auto_load_alt(query_auto_load_string(), this_object(), this_object(),
                      (: tell_object(this_object(),
                                     "\n%^CYAN%^Inventory regeneration complete.%^RESET%^\n") :));
   set_auto_load_string(0);
   allow_save();
}
void public_commands()
{
   add_command("restart", this_object(), "", (: restart_heart_beat() :));
   add_command("save", this_object(), "", (: save() :));
   add_command("quit", this_object(), "", (: quit_alt(-1) :));
   add_command("quit", this_object(), "brief", (: quit_alt(0) :));
   add_command("quit", this_object(), "verbose", (: quit_alt(1) :));
   add_command("review", this_object(), "", (: review() :));
   add_command("wimpy", this_object(), "", (: toggle_wimpy(0) :));
   add_command("wimpy", this_object(), "<word'number'>",
               (: toggle_wimpy($4[0]) :));
   add_command("refresh", this_object(), "<word'totally'>",
               (: do_refresh($4[0]) :));
   add_command("cap", this_object(), "<word'name'>", (: do_cap($4[0]) :));
}
int glance(string str)
{
   return command("glance" + (str ? " " + str : ""));
}
int look_me(string str)
{
   return command(str ? "look" + str : "look");
}
int review()
{
   write("Entry  : " + query_msgin() + "\n");
   write("Exit   : " + query_msgout() + "\n");
   write("MEntry : " + query_mmsgin() + "\n");
   write("MExit  : " + query_mmsgout() + "\n");
   write("Editor : " + query_editor() + "\n");
   return 1;
}
int examine(string arg)
{
   return look_me(arg ? " at " + arg : "");
}
varargs string short(int dark,
                     int verbose)
{
   string str;
   string family;
   string title;
   if (!interactive(this_object())) {
      str = "the net dead statue of ";
   } else {
      str = "";
   }
   family = query_family_name();
   if (!family) {
      family = "";
   } else {
      family = " " + family;
   }
   if (verbose)
      title = query_player_title();
   if (!title) {
      title = "";
   } else {
      title = title + " ";
   }
   return str + title + living::short(dark) + family;
}
int toggle_wimpy(string str)
{
   int number;
   if (!str) {
      if (this_object()->query_wimpy())
         write("You are in wimpy mode, you will run away at " +
               this_object()->query_wimpy() +
               "% of your max hps.\n");
      else
         write("You are in brave mode.\n");
      write("Usage: wimpy <num> (caution read help wimpy)\n");
      return 1;
   }
   if (sscanf(str, "%d", number) != 1)
      return notify_fail("You must set your wimpy to a number.\n");
   if ((number < 0) || (number > 30))
      return notify_fail("Your wimpy must be between 0 and 30%.\n");
   this_object()->set_wimpy(number);
   printf("Wimpy set to %d%%\n", wimpy);
   return 1;
}
string extra_score()
{
   return "";
}
nomask int save() {
#ifdef UNUSED
  if(query_verb() == "save") {
    if(_pinfo->last_save > time() - 900) {
      tell_object(this_object(), "You saved only a few minutes ago.\n");
      return 1;
    }
    _pinfo->last_save = time();
  }
#endif
  if (((time() - time_on) < MIN_TIME_TO_SAVE) &&
      !LIBRARY->query_quest_points(query_name()) &&
      !query_property("authorised player")) {
    if (query_verb() == "save") {
      tell_object(this_object(), "You're too young to save... sorry.\n");
    }
    return 1;
  }
  tell_object(this_object(), "Saving...\n");
  this_object()->save_me();
  return 1;
}
void save_me() {
   mixed old;
#ifdef NOT_SAVEING_PLAYERS
   if (!this_object()->query_creator()) {
      write("Not saving for players currently.\n");
      return;
   }
#endif
   if (query_auto_loading())
      return;
   if (query_property("guest")) {
      if (query_verb() == "save")
         tell_object(this_object(), "But not saving for guests... Sorry.\n");
      return;
   }
   if (query_save_inhibit()) {
      return;
   }
   if (guild_ob) {
      guild_ob->player_save(this_object());
   }
   if (race_ob) {
      race_ob->player_save(this_object());
   }
   old = geteuid();
   check_last_pos();
   effect_freeze();
   effects_saving();
   create_auto_load(all_inventory(), 1);
   if (interactive(this_object())) {
      last_on_from = query_ip_name(this_object()) + " (" +
         query_ip_number(this_object()) + ")";
   }
   time_on -= time();
      catch(unguarded((: save_object,
                      PLAYER_HANDLER->query_player_file_name(query_name()), 3 :)));
   time_on += time();
   ITEM_TRACKER->save_all_item_states(this_object()->query_name());
   effect_unfreeze();
   set_auto_load_string(0);
}
void save_with_auto_load(mixed al)
{
   mixed old;
#ifdef NOT_SAVEING_PLAYERS
   if (!this_object()->query_creator()) {
      write("Not saving for players currently.\n");
      return;
   }
#endif
   if (query_property("guest")) {
      write("But not saving for guests... sorry.\n");
      return;
   }
   if (((time() - time_on) < MIN_TIME_TO_SAVE) && query_verb() == "save") {
     tell_object(this_object(), "You're too young to save... sorry.\n");
     return;
   }
   if (query_save_inhibit()) {
      return;
   }
   if (guild_ob) {
      guild_ob->player_save(this_object());
   }
   if (race_ob) {
      race_ob->player_save(this_object());
   }
   old = geteuid();
   effect_freeze();
   effects_saving();
   set_auto_load_string(al);
   if (((time() - time_on) >= MIN_TIME_TO_SAVE) ||
       LIBRARY->query_quest_points(query_name())) {
      time_on -= time();
         catch(unguarded((: save_object,
                         PLAYER_HANDLER->query_player_file_name(query_name()),
                         3 :)));
      time_on += time();
   }
   effect_unfreeze();
}
int quit_alt(int verbose)
{
   object frog;
   if (verbose == -1) {
      verbose = query_verbose("quit");
   }
   if (query_auto_loading()) {
      if (!interactive(this_object())) {
         dest_me();
      } else {
         write
            ("You cannot quit yet: your inventory is still being generated.\n");
      }
      return 1;
   }
   if (sizeof(filter_array((object *) this_object()->query_attacker_list(),
                           (: living($1) :))) &&
       this_player() == this_object() && interactive(this_object())) {
      write
         ("You cannot quit while in combat.  Use 'stop' to stop fighting.\n");
      return 1;
   }
   check_last_pos();
   update_activity(0);
   last_log_on = time();
   catch(this_object()->event_quit(this_object()));
   catch(environment(this_object())->event_quit(this_object()));
   catch(editor_check_do_quit());
   write("A small gecko takes your hand and rushes you to the departure "
         "lounge.\n");
   say(query_cap_name() + " leaves the game.\n");
   catch(move("/room/departures"));
   user_event(this_object(), "inform",
              query_cap_name() + " leaves " + mud_name() + "", "logon", this_object());
   catch(LOGIN_HANDLER->player_logout(query_name()));
   if (race_ob) {
      catch(race_ob->player_quit(this_object()));
   }
   if (guild_ob) {
      catch(guild_ob->player_quit(this_object()));
   }
   frog = clone_object("/obj/monster/greco");
   frog->move("/room/departures");
   frog->get_rid_of(this_object(), verbose);
   return 1;
}
int do_quit()
{
   return quit_alt(-1);
}
int quit()
{
   if (query_auto_loading() || query_save_inhibit()) {
      tell_object(this_object(),
                  "Forced to quit whilst auto loading.  Not saving.\n");
      ::dest_me();
      return 1;
   }
   check_last_pos();
   update_activity(0);
   last_log_on = time();
   catch(editor_check_do_quit());
   catch(this_object()->event_quit(this_object()));
   catch(environment(this_object())->event_quit(this_object()));
   tell_object(this_object(), "Thanks for playing.  See you next time.\n");
   say(query_cap_name() + " leaves the game.\n");
   user_event(this_object(), "inform",
              query_cap_name() + " leaves " + mud_name() + "", "logon", this_object());
   catch(LOGIN_HANDLER->player_logout(query_name()));
   if (race_ob) {
      catch(race_ob->player_quit(this_object()));
   }
   if (guild_ob) {
      catch(guild_ob->player_quit(this_object()));
   }
   catch(save_me());
   foreach( object inv in all_inventory( this_object() ) ) {
      reset_eval_cost();
      catch( inv->set_tracked_item_status_reason("QUIT") );
      catch( inv->dest_me() );
   }
   catch(ITEM_TRACKER->
         save_all_item_states_delete_cache(this_object()->query_name()));
   effects_quiting();
   reset_eval_cost();
   if (catch(dest_me())) {
      destruct(this_object());
   }
   return 1;
}
mapping query_titles()
{
   return copy(_pinfo->titles);
}
string query_title()
{
   return implode(m_values(_pinfo->titles), ", ");
}
void set_title(string type,
               string title)
{
   _pinfo->titles[type] = title;
}
void remove_title(string type)
{
   map_delete(_pinfo->titles, type);
}
int query_deaths()
{
   return deaths;
}
void adjust_deaths(int i)
{
   if (i > 0) {
      deaths += i;
   }
}
nomask void set_name(string str) {
  if (query_name() && query_name() != "object") {
    return;
  }
  if (file_name(previous_object())[0..12] != "/secure/login" &&
      file_name(previous_object())[0..13] != "/secure/nlogin") {
    return;
  }
  ::set_name(str);
  set_living_name(query_name());
  set_main_plural(query_name());
}
void init_static_arg(mapping map)
{
   return;
}
void init_dynamic_arg(mapping, object) {
  return;
}
string long(string str,
            int dark)
{
   string s;
   string tmp;
   string title;
   string nationality;
   title = query_player_title();
   if (!title) {
      title = "";
   } else {
      title = title + " ";
   }
   s = "You see " + title + query_short();
   tmp = query_family_name();
   if (tmp) {
      s += " " + query_family_name();
   }
   if (guild_ob) {
      s += " " + (string) guild_ob->query_title(this_object()) + ".\n";
   } else {
      s += ".\n";
   }
   if (race_ob) {
      s += (string) race_ob->query_desc(this_object());
   }
   nationality = query_nationality_description(this_player());
   if (nationality  &&  nationality != "") {
      s += nationality + "\n";
   }
   if (dark == 2 || dark == -2) {
      s += "It is too ";
      if (dark == -2) {
         s += "dark";
      } else {
         s += "bright";
      }
      s += " to see their description or what " +
         query_pronoun() + " are wearing or carrying.\n";
      s += calc_extra_look();
   } else {
      if (query_desc() && query_desc() != "") {
         s += capitalize(query_pronoun()) + " " + query_desc() +
              query_main_zone_desc(query_wearing()) + "\n";
      }
      s += capitalize(query_pronoun()) + " " +
         this_object()->health_string() + ".\n";
      s +=
         capitalize(query_pronoun()) + " is " + query_position_short() +
         ".\n";
      s += calc_extra_look();
      s += weather_extra_look();
      s += query_living_contents(0);
   }
   return s;
}
mixed second_life()
{
   object corpse;
   string death_mess;
   add_property("dead", time());
   if (!DEATH->someone_died(this_object())) {
      deaths++;
   }
   effects_thru_death();
   corpse = make_corpse();
   reset_protectors();
   if (deaths > max_deaths) {
      death_mess = query_property ("death mess");
      tell_object(this_object(), "You have died your final death.  " +
                "Your name will be inscribed in the Hall of Legends.\n");
      if (death_mess && sizeof (death_mess)) {
        death_mess = strip_colours (death_mess);
        death_mess = replace (death_mess, ({"\n", "", "\a", ""}));
        shout(capitalize(query_name()) + " has died for the last time.  " +
          death_mess + "\n");
      }
      else {
        shout(capitalize(query_name()) + " has died for the last time.  " +
             capitalize(query_pronoun()) + " is mourned.\n");
      }
      LIBRARY->complete_death(query_name());
      corpse->move(PLAYER_MORGUE);
   } else
      corpse->move(environment());
   call_out((: save_me :), 0);
   if (find_object(OFFLER) && (deaths <= max_deaths)) {
      OFFLER->person_died(query_name());
   } else {
      DEATH->person_died(query_name());
   }
   clone_object(DEATH_SHADOW)->setup_shadow(this_object());
   if (guild_ob) {
      guild_ob->member_died(this_object());
   }
   gp = 0;
   hp = 0;
   set_sp(0);
   set_max_sp(50);
   xp = 0;
   reset_spells();
   reset_processes();
   contmp = dextmp = inttmp = strtmp = wistmp = 0;
   remove_call_out(_pinfo->update_tmps_call_out);
   adjust_tmp_con(-2);
   adjust_tmp_dex(-2);
   adjust_tmp_int(-2);
   adjust_tmp_str(-2);
   adjust_tmp_wis(-2);
   return corpse;
}
void remove_ghost()
{
   if (deaths > max_deaths) {
      if (this_player() != this_object()) {
         tell_object(this_object(), this_player()->query_cap_name() +
                     " tried to raise you, but you are completely dead.\n");
         tell_object(this_player(), query_cap_name() +
                     " is completely dead, you cannot raise " +
                     query_objective() + ".\n");
      } else {
         tell_object(this_object(), "You are completely dead.  You cannot " +
                     "be raised.\n");
         say(query_cap_name() +
             " struggles to appear in a solid form, but fails.\n");
         return;
      }
   }
   remove_property("dead");
   tell_object(this_object(), "You reappear in a more solid form.\n");
   if (guild_ob) {
      guild_ob->member_resurrected(this_object());
   }
   say(query_cap_name() + " appears in more solid form.\n");
   if (query_hp() < 0) {
      set_hp(1);
   }
   set_personal_temp(0);
   this_object()->dest_death_shadow();
   save_me();
   all_inventory()->recovery_from_death();
}
void net_dead()
{
   if (!environment() || file_name(environment()) == "/room/departures") {
      return;
   }
   if ((query_name() == "guest") || (query_name() == "root")) {
      say(query_name() + " vanishes in a puff of logic.\n");
      quit();
   } else {
      say(query_name() + " goes white, looks very chalky and turns into a " +
          "statue.\n");
      user_event(this_object(), "inform",
                 capitalize(query_name()) + " has lost " +
                 query_possessive() + " link", "link-death", this_object());
      check_last_pos();
      LOGIN_HANDLER->player_net_dead(query_name());
      save_me();
   }
   event(environment(), "net_dead", this_object());
}
void idle_out()
{
   say(cap_name + " has been idle for too long; " + query_pronoun() +
       " vanishes in a puff of boredom.\n");
   write("You idled out, sorry.\n");
   quit();
}
void heart_beat()
{
   catch {
      int idle_time;
      events::print_messages();
      flush_queue();
      if (!interactive(this_object())) {
         idle_time = time() - last_command;
      } else {
         idle_time = query_idle(this_object());
      }
      if (query_creator()) {
         idle_time = idle_time / 3;
      }
      if (idle_time > FULL_IDLE) {
         if ((LOGIN_HANDLER->is_discworld_full() || idle_time > MAX_IDLE) &&
             (!interactive(this_object())
              || my_file_name != "/global/lord")) {
            call_out((: idle_out :), 2);
         }
      }
      if (interactive(this_object())) {
         living::heart_beat();
         adjust_sp(1);
         adjust_xp(3);
         living::update_volumes();
         this_object()->do_spell_effects(0);
         if (_pinfo->hb_num++ > 1800)
            _pinfo->hb_num = 0;
         if (!(_pinfo->hb_num % 120)) {
            calc_personal_temp();
            adjust_max_sp(1);
         }
      }
   };
}
int query_monitor()
{
   return monitor;
}
void set_monitor(int i) {
  monitor = i;
}
protected void write_prompt()
{
   efun::tell_object(this_object(), "> ");
   return;
}
#ifdef UNUSED
protected void write_prompt()
{
   string prompt;
   int tmp,
     i;
   string stuff;
   if (!(monitor & 2) || !this_object()->query_creator())
      efun::tell_object(this_object(), "> ");
   else {
      prompt = "";
      stuff = this_player()->query_property("prompt");
      for (i = 0; i < strlen(stuff); i++) {
         switch (stuff[i]) {
         case 'h':
            tmp = ((query_hp() * 100) / query_max_hp());
            prompt += "Hp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += tmp + "%^RESET%^";
            break;
         case 'H':
            tmp = ((query_hp() * 100) / query_max_hp());
            prompt += "Hp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += query_hp() + "%^RESET%^";
            break;
         case 'g':
            tmp = (query_gp() * 100) / query_max_gp();
            prompt += "Gp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += tmp + "%^RESET%^";
            break;
         case 'G':
            tmp = (query_gp() * 100) / query_max_gp();
            prompt += "Gp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += query_gp() + "%^RESET%^";
            break;
         case 's':
            tmp = (query_sp() * 100) / query_max_sp();
            prompt += "Sp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += tmp + "%^RESET%^";
            break;
         case 'S':
            tmp = (query_sp() * 100) / query_max_sp();
            prompt += "Sp:";
            switch (tmp) {
            case 50..100:
               prompt += "%^GREEN%^";
               break;
            case 20..49:
               prompt += "%^YELLOW%^";
               break;
            default:
               prompt += "%^RED%^";
            }
            prompt += query_sp() + "%^RESET%^";
            break;
         case 'X':
         case 'x':
            prompt += "Xp:" + query_xp();
            break;
         default:
            if (sizeof(prompt) > 0 && prompt[sizeof(prompt) - 1] != stuff[i])
               prompt += sprintf("%c", stuff[i]);
         }
      }
      prompt += "> ";
      efun::tell_object(this_object(), fix_string(prompt));
   }
}
#endif
int run_away()
{
   int number;
   become_flummoxed();
   number =::run_away();
   if (number)
      tell_object(this_object(), "Your feet run away with you!\n");
   else
      tell_object(this_object(), "You try to run away, but no matter how "
                  "you scrabble, you can't find any way out.\n");
   return number;
}
nomask int query_time_on()
{
   return time_on - time();
}
int query_mature()
{
   return (MATURITY * 60 * 60 + time_on < time());
}
int check_dark(int light)
{
   int i;
   if (race_ob)
      if (catch(i = (int) race_ob->query_dark(light)))
         race_ob = RACE_STD;
      else
         return i;
   return (int) RACE_STD->query_dark(light);
}
int query_level()
{
   string tmp;
   if (_pinfo->level_time < (time() - LEVEL_CACHE)) {
      if (guild_ob) {
         _pinfo->level = (int) guild_ob->query_level(this_object());
      } else {
         tmp = query_property("backup guild");
         if (tmp) {
            _pinfo->level = tmp->query_level(this_object());
         } else
            _pinfo->level = CONFIG_DEFAULT_GUILD->query_level(this_object());
      }
      _pinfo->level_time = time();
   }
   return _pinfo->level;
}
int restart_heart_beat()
{
   set_heart_beat(1);
   write("Ok, heart_beat restarted.\n");
   return 1;
}
nomask void set_snoopee(object ob)
{
   _pinfo->snoopee = ob;
}
nomask object query_snoopee()
{
   return _pinfo->snoopee;
}
void set_creator(int i)
{
   if (previous_object() != master()) {
      write("Illegal attempt to set creator!\n");
      log_file("ILLEGAL", this_player(1)->query_name() + " (" +
               file_name(this_player(1)) +
               ") Illegal attempt to set_creator " + "at " + ctime(time()) +
               " from " + file_name(previous_object()) + "\n");
      return;
   }
   creator = i;
   set_home_dir("/w/" + query_name());
   save_me();
}
int query_prevent_shadow(object ob)
{
   if (function_exists("query_prevent_shadow", ob) ||
       function_exists("query_name", ob) ||
       function_exists("query_creator", ob) ||
       function_exists("query_lord", ob) ||
       function_exists("query_hidden", ob) ||
       function_exists("dest_me", ob) ||
       function_exists("query_object_type", ob) ||
       function_exists("query_lord", ob) || function_exists("save_me", ob))
      return 1;
   return 0;
}
int query_max_deaths()
{
   return max_deaths;
}
protected void set_max_deaths(int i)
{
   max_deaths = i;
}
int adjust_max_deaths(int i)
{
   if (i > 0) {
      return (max_deaths += i);
   }
}
varargs int move(mixed dest,
                 string msgin,
                 string msgout)
{
   int i;
   object env = environment();
   i = living::move(dest, msgin, msgout);
   if (!i) {
      me_moveing(env);
   }
   return i;
}
nomask protected int do_refresh(string str) {
   if (query_property("guest")) {
      return notify_fail("Guests cannot refresh, sorry.\n");
   }
   if (!str || str != "totally") {
      return notify_fail("Please read the docs before using this command.\n");
   }
   write("%^BOLD%^WARNING!  This will restart your character.%^RESET%^\n\n" +
         "Are you sure you wish to refresh yourself totally? ");
   input_to("refresh_docs");
   return 1;
}
protected int refresh_docs(string str) {
   string helpfile = "";
   str = lower_case(str);
   if (str[0] != 'y') {
      write("Ok, not refreshing.\n");
      return 1;
   }
   NROFF_HAND->create_nroff( "/doc/helpdir/refresh", helpfile );
   helpfile = NROFF_HAND->cat_file( helpfile );
   write ( helpfile[0..670] );
   write("\n\n%^BOLD%^Having read the documentation, are you still sure you "
         "wish to refresh totally?%^RESET%^\n");
   input_to("refresh3");
   return 1;
}
protected int refresh2(string str, int noevent) {
   object ob;
   string group;
   str = lower_case(str);
   if (str[0] != 'n' && str[0] != 'y') {
      write
         ("Pardon?  I do not understand.  Do you want to refresh yourself? ");
      input_to("refresh2");
      return 1;
   }
   if (str[0] == 'n') {
      write("Ok, not refreshing.\n");
      return 1;
   }
   write("Doing refresh.\n");
   Str = 13;
   Con = 13;
   Int = 13;
   Wis = 13;
   Dex = 13;
   inttmp = dextmp = wistmp = strtmp = contmp = 0;
   race_ob = CONFIG_DEFAULT_RACE;
   if (guild_ob)
      catch(guild_ob->delete_member(query_name()));
   if (!noevent) {
      REFRESH_HANDLER->player_refreshed(this_object(), PARTIAL_REFRESH);
   }
   guild_ob = 0;
   set_al(0);
   if (query_deity()) {
#ifndef __DISTRIBUTION_LIB__
      catch(DEITY->delete_worshipper(query_deity(), query_name()));
      catch(DEITY->delete_priest(query_deity(), query_name()));
#endif
   }
   set_deity(0);
   set_skills(0);
   PLAYTESTER_HAND->remove_playtester(query_name());
   if (query_family_name()) {
      CLUB_HANDLER->remove_member(query_family_name(), query_name());
      set_family_name(0);
   }
   reset_effects();
   reset_spells();
   reset_processes();
   setup_default_titles();
   guild_ob = 0;
   set_guild_data(0);
   xp = 0;
   deaths = 0;
   max_deaths = 7;
   _refresh_time = time();
   totaly_zap_bonus_cache();
   known_commands = ({ "skills", "rearrange", "gp", "newbie" });
   reset_starts();
   race_guild_commands();
   totaly_zap_stat_cache();
   drink_info = allocate(D_SIZEOF);
   map_prop = ([ "determinate" : "",
                 "player" : 1,
                 "skills version" :
                 (string) "/obj/handlers/change_skills"->query_version() ]);
   this_object()->remove_ghost();
   set_nationality(0);
   set_nationality_region(0);
   set_language("general");
   set_default_language("general");
   reset_all();
   group = this_player()->query_group();
   if (group) {
      GROUP->remove_member(group, this_player(), " refreshed themselves.");
   }
   set_last_pos(CONFIG_NEWBIE_START_LOCATION);
   START_PLAYER->give_junk(this_object());
   foreach (ob in query_attacker_list()) {
      catch(ob->stop_fight(this_object()));
      catch(stop_fight(ob));
   }
   call_out((: move_to_start_pos :), 0);
   if (!noevent) {
      write("Done refreshing.\n");
      say(cap_name + " refreshes " + query_objective() + "self.\n");
      save_me();
   }
   return 1;
}
protected int refresh3(string str)
{
   object *items,
    *ritems,
     item;
   str = lower_case(str);
   if (str[0] != 'n' && str[0] != 'y') {
      write("Pardon?  I do not understand.  Do you want to refresh " +
            "yourself totally? ");
      input_to("refresh3");
      return 1;
   }
   if (str[0] == 'n') {
      write("Ok, not refreshing.\n");
      return 1;
   }
   write("Ok, refreshing totally.\n");
   ritems = filter(all_inventory(environment()),
                   (: $1->query_property("dropped") &&
                      $1->query_property("dropped")[0] == query_name() :));
   move(CONFIG_NEWBIE_START_LOCATION);
   refresh2("y", 1);
   set_player_killer(0);
   _pinfo->titles = ([ ]);
   REFRESH_HANDLER->player_refreshed(this_object(), TOTAL_REFRESH);
   "/secure/related_files"->delete_related_files(query_name(),
                                                 0, TOTAL_REFRESH);
   items = ritems + all_inventory();
   foreach(item in items) {
      item->dest_me();
   }
   foreach(item in children("/obj/corpse")) {
      if (item->query_owner() == this_object()->query_name()) {
        item->move("/room/rubbish");
      }
   }
   foreach (string club in query_player_clubs()) {
      catch(CLUB_HANDLER->remove_member(club, this_player()->query_name()));
   }
   if (query_family_name()) {
      catch(CLUB_HANDLER->remove_member(query_family_name(),
                                  this_player()->query_name()));
      call_out("check_family_name", 2);
   }
   write("Done refreshing.\n");
   say(cap_name + " refreshes " + query_objective() + "self.\n");
   save_me();
   return 1;
}
string query_object_type(object player)
{
   if ("/obj/handlers/playtesters"->query_playtester(query_name())) {
      return "p";
   }
   return " ";
}
int do_cap(string str)
{
   if (!str)
      return notify_fail("Syntax: " + query_verb() + " <cap_name>\n");
   if (lower_case(str) != query_name())
      return
         notify_fail
         ("You must have the same letters in your capitalized name.\n");
   cap_name = str;
   write("Capitalized name set to " + cap_name + ".\n");
   return 1;
}
void set_my_ident(string str)
{
   return;
}
string query_my_ident()
{
   return 0;
}
void event_enter(object thing,
                 string mess,
                 object from)
{
   events::event_enter(thing, mess, from);
   living::event_enter(thing, mess, from);
}
void event_exit(object thing,
                string mess,
                object to)
{
   events::event_exit(thing, mess, to);
   living::event_exit(thing, mess, to);
}
string *parse_command_id_list()
{
   if (query_player_killer()) {
      return ({ "killer" }) +
             living::parse_command_id_list() + family::parse_command_id_list();
   } else {
      return living::parse_command_id_list() + family::parse_command_id_list();
   }
}
string *parse_command_plural_id_list()
{
   if (query_player_killer()) {
      return ({ "killers" }) + living::parse_command_plural_id_list() +
         family::parse_command_plural_id_list();
   } else {
      return living::parse_command_plural_id_list() +
         family::parse_command_plural_id_list();
   }
}
string *parse_command_adjectiv_id_list()
{
   return living::parse_command_adjectiv_id_list() +
         family::parse_command_adjectiv_id_list();
}
int query_last_log_on()
{
   return last_log_on;
}
int query_refresh_time()
{
   return _refresh_time;
}
int query_no_logins()
{
   return no_logins;
}
int query_creator()
{
   return 0;
}
int _living(){return 1;}
protected void set_invis(int level) {
}
int query_player_killer() {
   return _flags & PLAYER_KILLER_FLAG;
}
void set_player_killer(int flag) {
   if (flag) {
      _flags |= PLAYER_KILLER_FLAG;
   } else {
      _flags &= ~PLAYER_KILLER_FLAG;
   }
}
void set_role_playing(int i) {
  if(i)
    add_property(RPMODE, 1);
  else
    remove_property(RPMODE);
}
int query_role_playing() {
  return query_property(RPMODE);
}