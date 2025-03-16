#include <nomic_system.h>
inherit "/std/room/inherit/punishment_inherit";
void setup() {
   set_short("lose citizenship");
   set_description_file(NOMIC_PUNISHMENT_DOCS_DIR + "lose_citizenship");
}
void start_punishment(string area,
                      class nomic_case the_case,
                      string type,
                      function finish) {
   string* not_citizens;
   string* magistrates;
   not_citizens = filter(the_case->people,
                     (: !NOMIC_HANDLER->is_citizen_of($2, $1) :), area);
   if (sizeof(not_citizens)) {
      write(query_multiple_short(not_citizens) + " cannot lose "
            "their citizenship since they are not citizens.\n");
      return ;
   }
   magistrates = filter(the_case->people,
                    (: NOMIC_HANDLER->is_magistrate_of($2, $1) :), area);
   if (sizeof(magistrates)) {
      write(query_multiple_short(magistrates) + " cannot lose "
            "their citizenship since they are magistrates.\n");
      return ;
   }
   evaluate(finish, the_case, type, 0);
}
void complete_punishment(string area,
                      class nomic_case the_case,
                      string type,
                      mixed data) {
   string citizen;
   foreach (citizen in the_case->people) {
      NOMIC_HANDLER->remove_citizen(area, citizen);
   }
   return ;
}
void suspend_punishment(string area,
                      class nomic_case the_case,
                      string type,
                      mixed data) {
   string citizen;
   foreach (citizen in the_case->people) {
      NOMIC_HANDLER->add_citizen(area, citizen);
   }
   return ;
}