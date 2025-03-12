#include <clubs.h>
#include <broadcaster.h>
inherit "/obj/clothing";
inherit "/std/basic/club_insignia";
protected int club_members(int online);
protected int do_recruit(object *players, string club);
protected int club_chat(string str, int emote);
protected int club_members(int online);
protected int club_info();
protected int do_history();
private string *extra_adjs;
void setup() {
   extra_adjs = ({ });
   set_name("badge");
   add_adjective("club");
   set_type("badge");
   set_short("club badge");
   setup_clothing(1000);
   set_damage_chance(5);
   set_long("The badge is a nice blue colour with a fringe "
            "like a bunny rabbit.\n");
   add_extra_look(this_object());
}
string extra_look() {
   string tmp_name;
   if (query_club() &&
       CLUB_HANDLER->is_member_of(query_club(), this_player()->query_name())) {
      tmp_name = replace(lower_case(query_club()), " ", "_");
      return "  You feel like the command '" + tmp_name + "' does something.\n";
   }
   return "\n";
}
void init() {
   club_insignia::init();
}
mapping query_dynamic_auto_load(mapping map) {
   map = clothing::query_dynamic_auto_load();
   map = club_insignia::query_dynamic_auto_load(map);
   map["verSion"] = 1;
   return map;
}
void init_dynamic_arg(mapping map) {
   if (map["verSion"] != 1) {
      clothing::init_dynamic_arg(map["::"]);
   } else {
      clothing::init_dynamic_arg(map);
   }
   club_insignia::init_dynamic_arg(map);
}
void set_club(string name) {
   if (!name) {
      extra_adjs = ({ });
      set_short("club badge");
   } else {
      if (CLUB_HANDLER->is_club(name)) {
         name = CLUB_HANDLER->query_club_name(name);
         extra_adjs = explode(lower_case(name), " ");
            set_short("club badge");
      }
   }
   ::set_club(name);
}
string *parse_command_adjectiv_id_list() {
   return ::parse_command_adjectiv_id_list() +
           extra_adjs;
}
mixed *stats()
{
  return clothing::stats() +
    club_insignia::stats();
}