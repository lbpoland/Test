inherit "/std/room/basic_room";
inherit "/std/room/inherit/council_base";
#define NOMIC_SYSTEM_CASE_CLASSES
#include <nomic_system.h>
#include <player_handler.h>
#include <mail.h>
void add_punishment_type(string name, string file);
string query_punishment_type(string name);
private mapping _types;
void create() {
   _types = ([ ]);
   ::create();
   if (!query_punishment_type("not guilty")) {
      add_punishment_type("not guilty", NOMIC_PUNISHMENT_DIR + "not_guilty");
   }
   if (!query_punishment_type("dismissed")) {
      add_punishment_type("dismissed", NOMIC_PUNISHMENT_DIR + "dismissed");
   }
   if (!query_punishment_type("lose citizenship")) {
      add_punishment_type("lose citizenship",
                          NOMIC_PUNISHMENT_DIR + "lose_citizenship");
   }
   add_help_file("cases");
}
void add_punishment_type(string name, string file) {
   _types[name] = file;
}
string query_punishment_type(string name) {
   return _types[name];
}
void start_punishment(string name, class nomic_case the_case, function finish) {
   string bing;
   bing = query_punishment_type(name);
   if (bing) {
      call_other(bing, "start_punishment", query_council_area(),
                 the_case, name, finish);
   } else {
      write("Big hairy error.\n");
   }
}
void complete_punishment(string name, class nomic_case the_case, mixed data) {
   string bing;
   bing = query_punishment_type(name);
   if (bing) {
      call_other(bing, "complete_punishment", query_council_area(),
                 the_case, name, data);
   } else {
      write("Big hairy error.\n");
   }
}
void suspend_punishment(class nomic_case the_case) {
   string bing;
   class nomic_case_event event;
   string type;
   mixed data;
   foreach (event in the_case->events) {
      if (event->type == NOMIC_CASE_EVENT_CLOSE) {
         type = event->data[0];
         data = event->data[1];
      }
   }
   bing = query_punishment_type(type);
   if (bing) {
      call_other(bing, "suspend_punishment", query_council_area(),
                 the_case, type, data);
   } else {
      write("Big hairy error.\n");
   }
}
string query_punishment_short(string name, class nomic_case the_case,
                              mixed data) {
   string bing;
   bing = query_punishment_type(name);
   if (bing) {
      return call_other(bing, "query_short", query_council_area(), the_case, name, data);
   } else {
      return "Big hairy error.\n";
   }
}
string query_punishment_mail_info(string name, class nomic_case the_case,
                              mixed data) {
   string bing;
   bing = query_punishment_type(name);
   if (bing) {
      return call_other(bing, "query_mail_information", query_council_area(), the_case,
                        name, data);
   } else {
      return "Big hairy error.\n";
   }
}
string* query_all_punishment_types() {
   return keys(_types);
}
string query_extra_player_status(string player) {
   return 0;
}
string query_last_appealer(class nomic_case the_case) {
   class nomic_case_event event;
   string ret;
   ret = 0;
   foreach (event in the_case->events) {
      if (event->type == NOMIC_CASE_EVENT_APPEAL) {
         ret = event->person;
      }
   }
   return ret;
}
int is_last_appealer(class nomic_case the_case, string person) {
   return query_last_appealer(the_case) == person;
}
string query_last_closer(class nomic_case the_case) {
   class nomic_case_event event;
   string ret;
   ret = 0;
   foreach (event in the_case->events) {
      if (event->type == NOMIC_CASE_EVENT_CLOSE) {
         ret = event->person;
      }
   }
   return ret;
}
int is_last_closer(class nomic_case the_case, string person) {
   return query_last_closer(the_case) == person;
}
int do_list_punishments() {
   string punish;
   string file;
   write("Punishments:\n");
   foreach (punish, file in _types) {
      write("   " + punish + "\n");
   }
   return 1;
}
int do_list_punishments_desc(string type) {
   string file;
   write("Punishments:\n");
   file = _types[type];
   if (!file) {
      add_failed_mess("No punishment of type " + type + ".\n");
      return 0;
   }
   this_player()->more_string(file->query_description(), "punishment");
   return 1;
}
int do_open_case(string people, string short) {
   string* bits;
   string* bad;
   string person;
   people = replace_string(people, " and ", ",");
   people = replace_string(people, " ", "");
   bits = explode(lower_case(people), ",");
   bad = ({ });
   foreach (person in bits) {
      if (!PLAYER_HANDLER->test_user(person)) {
         bad += ({ person });
      }
   }
   if (member_array(this_player()->query_name(), bits) != -1) {
      bits = bits - ({ this_player()->query_name() });
   }
   if (sizeof(bad) == 1) {
      add_failed_mess("The player " + query_multiple_short(bad) +
                      " does not exist.\n", bad);
      return 0;
   } else if (sizeof(bad)) {
      add_failed_mess("The players " + query_multiple_short(bad) +
                      " do not exist.\n", bad);
      return 0;
   }
   if (!sizeof(bits)) {
      add_failed_mess("There have to be some people involved in the case.\n");
      return 0;
   }
   write("For the case with the people " + query_multiple_short(bits) +
         " and a short of " + short + ", please type in an intial "
         "description of the case.\n");
   this_player()->do_edit("", "open_case_desc", this_object(), 0,
                          ({ bits, short }));
   return 1;
}
void open_case_desc(string desc, mixed* extra) {
   string* bits;
   string short;
   bits = extra[0];
   short = extra[1];
   if (!desc) {
      write("Aborted.\n");
      return ;
   }
   write("Adding in a case with " + query_multiple_short(bits) +
         " people and a short description of " + short + ".\nYour note is:\n");
   write(desc);
   write("\nAre you sure you wish to add this? ");
   input_to("open_case_desc_confirm", 0, bits, short, desc);
}
void open_case_desc_confirm(string response, string* bits,
                            string short, string desc) {
   int id;
   string* magistrates;
   response = lower_case(response);
   if (!strlen(response) || response[0] != 'y') {
      write("Aborting the addition of the case.\n");
      return ;
   }
   id = NOMIC_HANDLER->add_new_case(query_council_area(),
                                    this_player()->query_name(), short,
                                    bits);
   if (id) {
      NOMIC_HANDLER->add_note_to_case(query_council_area(),
                                      id, this_player()->query_name(),
                                      desc);
      write("Added the case into the system.\n");
      magistrates = NOMIC_HANDLER->query_magistrates(query_council_area());
      MAILER->do_mail_message(implode(magistrates + bits, ","),
                           query_council_area() + " magistrates",
                           "New case against " + implode(bits, ","),
                           "",
                           "A new case is opened against " +
                           implode(bits, ",") +
                           " by " + this_player()->query_cap_name() +
                           "\nwith a reason of:\n" +
                           desc);
      tell_room(this_object(),
           this_player()->the_short() + " opens a case against " +
           query_multiple_short(bits) + ".\n", ({ this_player() }) );
   } else {
      write("Unable to add the case for some reason.\n");
   }
}
string query_case_short(class nomic_case the_case) {
   string ret;
   ret = "Case #" + the_case->id + " \"" +
         the_case->short + "\" opened by " + the_case->opener +
         " against " + query_multiple_short(the_case->people) + " at " +
         ctime(the_case->time_opened);
   return ret;
}
int do_list_open_cases() {
   int* cases;
   string ret;
   class nomic_case the_case;
   int id;
   cases = NOMIC_HANDLER->query_open_cases(query_council_area());
   if (!sizeof(cases)) {
      add_failed_mess("There are no open cases.\n");
      return 0;
   }
   ret = "Currently open cases:\n";
   foreach (id in cases) {
      the_case = NOMIC_HANDLER->query_open_case(query_council_area(), id);
      ret += "$I$5=$C$" + query_case_short(the_case);
      ret += "\n";
   }
   this_player()->more_string(ret, "open cases");
   return 1;
}
int do_list_closed_cases() {
   int* cases;
   string ret;
   class nomic_case the_case;
   int id;
   cases = NOMIC_HANDLER->query_recently_closed_cases(query_council_area());
   if (!sizeof(cases)) {
      add_failed_mess("There are no recently closed cases.\n");
      return 0;
   }
   ret = "Recently closed cases:\n";
   foreach (id in cases) {
      the_case = NOMIC_HANDLER->query_recently_closed_case(query_council_area(), id);
      ret += "$I$5=$C$" + query_case_short(the_case);
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
   the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
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
   this_player()->more_string(ret, "open cases");
   return 1;
}
int do_list_closed_case(int case_id) {
   string ret;
   class nomic_case the_case;
   class nomic_case_note note;
   class nomic_case_event event;
   int id;
   int* cases;
   ret = "";
   cases = NOMIC_HANDLER->query_recently_closed_cases(query_council_area());
   if (member_array(case_id, cases) == -1) {
      add_failed_mess("Unable to find the case.\n");
      return 0;
   }
   the_case = NOMIC_HANDLER->query_recently_closed_case(query_council_area(),
                                                        case_id);
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
                " " + event->mess + ".\n";
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
   this_player()->more_string(ret, "open cases");
   return 1;
}
int do_add_person(int case_id, string person) {
   class nomic_case the_case;
   the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
   if (!the_case) {
      add_failed_mess("Unable to find the id of the case.\n");
      return 0;
   }
   if (!NOMIC_HANDLER->is_magistrate_of(query_council_area(),
                                        this_player()->query_name())) {
      add_failed_mess("You must be a magistrate to add a person from "
                      "the case.\n");
      return 0;
   }
   if (member_array(this_player()->query_name(), the_case->people) != -1 ||
       this_player()->query_name() == the_case->opener) {
      add_failed_mess("You cannot add a person to a case involving you or "
                      "started by you.\n");
      return 0;
   }
   write("What reason to wish to give for adding this person?\n");
   this_player()->do_edit("", "person_desc", this_object(), 0,
                          ({ case_id, person, "add" }));
   return 1;
}
void person_desc(string desc, mixed* stuff) {
   int case_id;
   string person;
   string type;
   class nomic_case the_case;
   case_id = stuff[0];
   person = stuff[1];
   type = stuff[2];
   if (!desc) {
      write("Aborted " + type + "ing " + person + ".\n");
      return ;
   }
   the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
   write("Are you sure you wish to " + type + " " + person + " to the "
        "case " + query_case_short(the_case) + ".\n");
   input_to("person_confirm", 0, case_id, person, type, desc);
}
void person_confirm(
   string response,
   int case_id,
   string person,
   string type,
   string desc
) {
   string* people;
   class nomic_case the_case;
   response = lower_case(response);
   if (!strlen(response) || response[0] != 'y') {
      write("Aborted " + type + "ing " + person + ".\n");
      return ;
   }
   the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
   people = the_case->people;
   if (type == "add") {
      if (NOMIC_HANDLER->add_person_to_case(query_council_area(), case_id,
                                            this_player()->query_name(),
                                            person, "\n" + desc)) {
         write("Sucessfully added " + person + " to the case.\n");
         people += ({ person });
      } else {
         write("Unable to add " + person + " to the case.\n");
         return ;
      }
   } else {
      if (NOMIC_HANDLER->remove_person_from_case(query_council_area(), case_id,
                                            this_player()->query_name(),
                                            person, "\n" + desc)) {
         write("Sucessfully removed " + person + " from the case.\n");
      } else {
         write("Unable to remove " + person + " from the case.\n");
         return ;
      }
   }
   MAILER->do_mail_message(implode(people, ","),
                           query_council_area() + " magistrates",
                           capitalize(type) + " person",
                           "",
                           "From the desk of " +
                           this_player()->query_cap_name() + ":\n"
                           "The " + type + "ing the person " + person +
                           " to the case " +
                           query_case_short(the_case) +
                           "\nwith a reason of:\n" +
                           desc);
   tell_room(this_object(),
           this_player()->the_short() + " " + type + "s " + person +
           " to case #" + the_case->id + ".\n", ({ this_player() }) );
}
int do_remove_person(int case_id, string person) {
   class nomic_case the_case;
   the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
   if (!the_case) {
      add_failed_mess("Unable to find the id of the case.\n");
      return 0;
   }
   if (!NOMIC_HANDLER->is_magistrate_of(query_council_area(),
                                        this_player()->query_name())) {
      add_failed_mess("You must be a magistrate to remove a person "
                      "from the case.\n");
      return 0;
   }
   if (member_array(this_player()->query_name(), the_case->people) != -1 ||
       this_player()->query_name() == the_case->opener) {
      add_failed_mess("You cannot remove a person to a case involving you or "
                      "started by you.\n");
      return 0;
   }
   if (sizeof(the_case->people) == 1) {
      add_failed_mess("You cannot remove everyone from the case.\n");
      return 0;
   }
   write("What reason to wish to give for removeing this person?\n");
   this_player()->do_edit("", "person_desc", this_object(), 0,
                          ({ case_id, person, "remove" }));
   return 1;
}
int do_add_note(int case_id) {
   class nomic_case the_case;
   the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
   if (!the_case) {
      add_failed_mess("Unable to find the id of the case.\n");
      return 0;
   }
   write(query_case_short(the_case));
   write("\nAdd note:\n");
   this_player()->do_edit("", "note_case_desc", this_object(), 0,
                          the_case);
   return 1;
}
void note_case_desc(string desc, class nomic_case the_case) {
   if (!desc) {
      write("Aborted.\n");
   }
   write("Do you wish to add the note to the case " +
         query_case_short(the_case) + ".\n");
   write(desc + "\nAre you sure you wish to add this note? ");
   input_to("note_case_desc_confirm", 0, desc, the_case);
}
void note_case_desc_confirm(string response, string desc,
                            class nomic_case the_case) {
   response = lower_case(response);
   if (!strlen(response) || response[0] != 'y') {
      write("Aborting the addition of the note.\n");
      return ;
   }
   if (NOMIC_HANDLER->add_note_to_case(query_council_area(), the_case->id,
                                       this_player()->query_name(), desc)) {
      write("Added the note to the case.\n");
      tell_room(this_object(),
           this_player()->the_short() + " adds a note "
           " to case #" + the_case->id + ".\n", ({ this_player() }) );
   } else {
      write("Unable to add the note to the case for some reason.\n");
   }
}
void close_case_bit(class nomic_case the_case, string type, mixed data) {
   write("Please add in your closing summary.\n");
   this_player()->do_edit("", "close_case_desc", this_object(), 0,
                          ({ the_case, type, data }));
}
int do_close_case(int case_id, string type) {
   class nomic_case the_case;
   the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
   if (!the_case) {
      add_failed_mess("Cannot find the case.\n");
      return 0;
   }
   if (!NOMIC_HANDLER->is_magistrate_of(query_council_area(),
                                        this_player()->query_name())) {
      add_failed_mess("You must be a magistrate to close the case.\n");
      return 0;
   }
   if (!query_punishment_type(type)) {
      add_failed_mess("This is not an allowed type for closing the case, "+
                      "it must be one of " +
                      query_multiple_short(query_all_punishment_types()) + ".\n");
      return 0;
   }
   if (member_array(this_player()->query_name(), the_case->people) != -1 ||
       this_player()->query_name() == the_case->opener) {
      add_failed_mess("You cannot close a case involving you or started "
                      "by you.\n");
      return 0;
   }
   if (is_last_appealer(the_case, this_player()->query_name())) {
      add_failed_mess("You cannot close a case you appealed.\n");
      return 0;
   }
   start_punishment(type, the_case, (: close_case_bit :));
   return 1;
}
void close_case_desc(string desc, mixed* extra) {
   class nomic_case the_case;
   string type;
   mixed data;
   if (!desc) {
      write("Aborted.\n");
      return ;
   }
   the_case = extra[0];
   type = extra[1];
   data = extra[2];
   write("Closing the case " +
         query_case_short(the_case) +  " with the type of " +
         query_punishment_short(type, the_case, data) + ".\n");
   write("Are sure you wish you wish to close this case? ");
   input_to("close_case_desc_confirm", 0, the_case, type, data, desc);
}
void close_case_desc_confirm(string response, class nomic_case the_case,
                             string type, mixed* data, string desc) {
   string* people;
   response = lower_case(response);
   if (!strlen(response) || response[0] != 'y') {
      write("Aborting the closing of the note.\n");
      return ;
   }
   if (NOMIC_HANDLER->close_case(query_council_area(), the_case->id,
                                this_player()->query_name(),
                                query_punishment_short(type, the_case, data) +
                                "\n" + desc, ({ type, data }))) {
      complete_punishment(type, the_case, data);
      write("Completed closing the case.\n");
      people = the_case->people + ({ the_case->opener }) +
               NOMIC_HANDLER->query_magistrates(query_council_area());
      if (query_last_appealer(the_case)) {
         people += ({ query_last_appealer(the_case) });
      }
      MAILER->do_mail_message(implode(people, ","),
                              query_council_area() + " magistrates",
                              "Case closed against " +
                              implode(the_case->people, ","),
                              "",
                              "From the desk of " +
                              this_player()->query_cap_name() + ":\n"
                              "The case " +
                              query_case_short(the_case) +
                              "\nhas been closed with a verdict of " +
                              query_punishment_short(type, the_case, data) +
                              "\nWith a reason of:\n" +
                              desc +
                              query_punishment_mail_info(type, the_case, data));
      tell_room(this_object(),
           this_player()->the_short() + " closes the case #" +
           the_case->id + " against " + query_multiple_short(the_case->people) +
           " with a result of " +
           query_punishment_short(type, the_case, data) +
           ".\n", ({ this_player() }) );
   } else {
      write("Unable to complete closing the case.\n");
   }
}
int do_appeal_case(int case_id) {
   class nomic_case the_case;
   the_case = NOMIC_HANDLER->query_recently_closed_case(query_council_area(),
                                                        case_id);
   if (!the_case) {
      add_failed_mess("Cannot find the case.\n");
      return 0;
   }
   if (!NOMIC_HANDLER->is_magistrate_of(query_council_area(),
                                        this_player()->query_name())) {
      add_failed_mess("You must be a magistrate to appeal the case.\n");
      return 0;
   }
   if (member_array(this_player()->query_name(), the_case->people) != -1 ||
       this_player()->query_name() == the_case->opener) {
      add_failed_mess("You cannot appeal a case involving you or started "
                      "by you.\n");
      return 0;
   }
   if (is_last_closer(the_case, this_player()->query_name())) {
      add_failed_mess("You cannot appeal a case you closed.\n");
      return 0;
   }
   write("What is the detailed reason for appealing this case?\n");
   this_player()->do_edit("", "appeal_case_desc", this_object(), 0, case_id);
   return 1;
}
void appeal_case_desc(string desc, int case_id) {
   class nomic_case the_case;
   if (!desc) {
      write("Aborted.\n");
      return ;
   }
   the_case = NOMIC_HANDLER->query_recently_closed_case(query_council_area(),
                                                        case_id);
   write("Appealing the case " +
         query_case_short(the_case) +  " because:\n" + desc + "\nAre you sure "
         "you wish to do this? ");
   input_to("appeal_case_desc_confirm", 0, case_id, desc);
}
void appeal_case_desc_confirm(string response, int case_id, string desc) {
   class nomic_case the_case;
   string* people;
   response = lower_case(response);
   if (!strlen(response) || response[0] != 'y') {
      write("Aborting the closing of the note.\n");
      return ;
   }
   the_case = NOMIC_HANDLER->query_recently_closed_case(query_council_area(),
                                                        case_id);
   if (NOMIC_HANDLER->appeal_case(query_council_area(), case_id,
                                  this_player()->query_name(),
                                  "\n" + desc)) {
      write("Appealed the case successfully.\n");
      the_case = NOMIC_HANDLER->query_open_case(query_council_area(), case_id);
      suspend_punishment(the_case);
      people = the_case->people + ({ the_case->opener });
      MAILER->do_mail_message(implode(people, ","),
                              query_council_area() + " magistrates",
                              "Case appealed",
                              "",
                              "The case " +
                              query_case_short(the_case) +
                              "\nhas been appealed by " +
                              this_player()->query_cap_name() + " because:\n" +
                              desc);
      tell_room(this_object(),
           this_player()->the_short() + " appeals the case #" +
           the_case->id + " against " + query_multiple_short(the_case->people) +
           ".\n", ({ this_player() }) );
   } else {
      write("Error trying to appeal the case!\n");
   }
}
int do_player_status(string person) {
   int* cases;
   class nomic_case the_case;
   int id;
   int found;
   int *open_defendant;
   int *open_opener;
   int *open_appealed;
   int *closed_defendant;
   int *closed_opener;
   int *closed_closed;
   string ret;
   string bing;
   person = lower_case(person);
   cases = NOMIC_HANDLER->query_open_cases(query_council_area());
   if (!sizeof(cases)) {
      add_failed_mess("There are no open cases.\n");
      return 0;
   }
   open_defendant = ({ });
   open_opener = ({ });
   foreach (id in cases) {
      the_case = NOMIC_HANDLER->query_open_case(query_council_area(), id);
      if (member_array(person, the_case->people) != -1) {
         found = 1;
         open_defendant += ({ id + "" });
      }
      if (the_case->opener == person) {
         found = 1;
         open_opener += ({ id + "" });
      }
      bing = query_last_appealer(the_case);
      if (bing == person) {
         found = 1;
         open_appealed += ({ id + "" });
      }
   }
   cases = NOMIC_HANDLER->query_recently_closed_cases(query_council_area());
   closed_defendant = ({ });
   closed_opener = ({ });
   foreach (id in cases) {
      the_case = NOMIC_HANDLER->query_recently_closed_case(query_council_area(), id);
      if (member_array(person, the_case->people) != -1) {
         found = 1;
         closed_defendant += ({ id + " (closed)"  });
      }
      if (the_case->opener == person) {
         found = 1;
         closed_opener += ({ id + " (closed)" });
      }
      bing = query_last_closer(the_case);
      if (bing == person) {
         found = 1;
         closed_closed += ({ id + "" });
      }
   }
   ret = "Status for " + capitalize(person) + ":\n";
   if (sizeof(open_opener) || sizeof(closed_opener)) {
      ret += "Opened the cases      : " +
             query_multiple_short(open_opener + closed_opener) + "\n";
   }
   if (sizeof(open_defendant) || sizeof(closed_defendant)) {
      ret += "Defendant in the cases: " +
             query_multiple_short(open_defendant + closed_defendant) + "\n";
   }
   bing = query_extra_player_status(person);
   if (bing) {
      ret += bing;
   } else if (!found) {
      add_failed_mess("The player " + person + " has no record.\n");
      return 0;
   }
   write("$P$Status$P$" + ret);
   return 1;
}
void init() {
   add_command("list", "", (: do_list_open_cases() :));
   add_command("list", "[case] <number>", (: do_list_case($4[0]) :));
   add_command("list", "closed", (: do_list_closed_cases() :));
   add_command("list", "{punishments|results}", (: do_list_punishments :));
   add_command("list", "{punishment|punishments|results} <string'type'>", (: do_list_punishments_desc($4[1]) :));
   add_command("list", "closed [case] <number>", (: do_list_closed_case($4[0]) :));
   add_command("case", "add person <string'person'> to <number'case id'>",
               (: do_add_person($4[1], $4[0]) :));
   add_command("case", "remove person <string'person'> from <number'case id'>",
               (: do_remove_person($4[1], $4[0]) :));
   add_command("case", "[add] note <number'case id'>", (: do_add_note($4[0]) :));
   add_command("case", "open [with] <string'people'> about <string'short descripion'>",
                       (: do_open_case($4[0], $4[1]) :));
   add_command("case", "close <number'case id'> result <string'result'>",
                       (: do_close_case($4[0], $4[1]) :));
   add_command("case", "appeal <number'case id'>",
                       (: do_appeal_case($4[0]) :));
   add_command("status", "[of] <string'player'>",
                       (: do_player_status($4[0]) :));
}