inherit "/std/room/basic_room";
inherit "/std/room/inherit/council_base";
#define NOMIC_SYSTEM_CASE_CLASSES
#include <nomic_system.h>
#include <player_handler.h>
#include <mail.h>
void create() {
   ::create();
   add_help_file("council_archive");
}
string query_case_short(class nomic_case the_case) {
   string ret;
   ret = "Case #" + the_case->id + " \"" +
         the_case->short + "\" opened by " + the_case->opener +
         " against " + query_multiple_short(the_case->people) + " at " +
         ctime(the_case->time_opened);
   return ret;
}
int do_list_all_cases() {
   int* cases;
   string ret;
   int id;
   cases = NOMIC_HANDLER->query_closed_cases(query_council_area());
   if (!sizeof(cases)) {
      add_failed_mess("There are no open cases.\n");
      return 0;
   }
   ret = "Currently closed cases:\n";
   foreach (id in cases) {
      ret += "$I$5=$C$Case #" + id;
      ret += "\n";
   }
   this_player()->more_string(ret, "closed cases");
   return 1;
}
int do_list_case(int case_id) {
   string ret;
   class nomic_case the_case;
   class nomic_case_note note;
   class nomic_case_event event;
   int id;
   ret = "";
   the_case = NOMIC_HANDLER->query_closed_case(query_council_area(), case_id);
   if (!the_case) {
      add_failed_mess("Unable to find the case.\n");
      return 0;
   }
   ret += "$I$3=" + query_case_short(the_case);
   if (sizeof(the_case->events)) {
      ret += "\n";
      ret += "$I$0=%^YELLOW%^Events%^RESET%^:\n";
      foreach (event in the_case->events) {
         ret += "$I$6=   " +
                capitalize(NOMIC_HANDLER->query_event_name(event->type)) +
                " " +
                "by " + event->person + " at " + ctime(event->event_time) +
                " " +
                event->mess + "\n";
      }
   }
   if (sizeof(the_case->notes)) {
      ret += "\n";
      ret += "$I$0=%^YELLOW%^Notes%^RESET%^:\n";
      foreach (id in the_case->notes) {
         note = NOMIC_HANDLER->query_note(id);
         ret += "$I$6=   Note by " + note->person + " at " +
                ctime(note->time_created) +
                ".\n" + note->text + "\n\n";
      }
   }
   this_player()->more_string(ret, "closed case");
   return 1;
}
int do_list_citizens() {
    object* cits;
    string ret;
    string area;
    area = this_object()->query_council_area();
    cits = filter( users(), (: NOMIC_HANDLER->is_citizen_of(
       this_object()->query_council_area(), $1->query_name() ) &&
       $1->query_visible( this_player() ) :) );
    cits = sort_array(cits, (: strcmp($1->query_name(), $2->query_name()) :));
    ret = "The online citizens (and magistrates) of " + area + " are:\n\n";
    ret += query_multiple_short(cits);
    write("$P$Citizens Online$P$" + ret);
    return 1;
}
void init() {
   add_command("list", "", (: do_list_all_cases() :));
   add_command("list", "[case] <number>", (: do_list_case($4[0]) :));
   add_command("list", "citizens", (: do_list_citizens() :));
}