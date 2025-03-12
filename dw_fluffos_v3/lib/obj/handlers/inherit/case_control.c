#define NOMIC_SYSTEM_NO_CLASSES
#define NOMIC_SYSTEM_CASE_CLASSES
#include <nomic_system.h>
private mapping _open_cases;
private mapping _recently_closed_cases;
private mapping _closed_cases;
private int _next_case_id;
private int _next_note_id;
void save_me();
void send_council_inform(string area, int only_magistrates,
                         string mess);
void create() {
   _open_cases = ([ ]);
   _closed_cases = ([ ]);
   _recently_closed_cases = ([ ]);
   _next_case_id = 1;
   _next_note_id = 1;
}
void create_area(string area) {
   if (_open_cases[area]) {
      return ;
   }
   _open_cases[area] = ({ });
   _closed_cases[area] = ({ });
   _recently_closed_cases[area] = ({ });
}
int* query_open_cases(string area) {
   return _open_cases[area];
}
int* query_closed_cases(string area) {
   return _closed_cases[area];
}
int* query_recently_closed_cases(string area) {
   return _recently_closed_cases[area];
}
string query_case_file_name(int id) {
   return NOMIC_CASE_SAVE + sprintf("cases/%02d/%d_case", id % 20, id);
}
int query_next_case_id() {
   int next;
   do {
      next = _next_case_id++;
   } while (sizeof(stat(query_case_file_name(next))));
   return next;
}
private void save_case(class nomic_case stuff) {
   string fname;
   string tmp;
   fname = query_case_file_name(stuff->id);
   tmp = save_variable(stuff);
   unguarded((: write_file($(fname), $(tmp), 1) :));
}
string query_note_file_name(int id) {
   return NOMIC_CASE_SAVE + sprintf("notes/%02d/%d_note", id % 20, id);
}
int query_next_note_id() {
   int next;
   do {
      next = _next_note_id++;
   } while (sizeof(stat(query_note_file_name(next))));
   return next;
}
private void save_note(class nomic_case_note stuff) {
   string fname;
   string tmp;
   fname = query_note_file_name(stuff->id);
   tmp = save_variable(stuff);
   unguarded((: write_file($(fname), $(tmp) ) :));
}
private int create_case(string opener, string short, string* people) {
   class nomic_case new_case;
   new_case = new(class nomic_case);
   new_case->id = query_next_case_id();
   new_case->opener = opener;
   new_case->short = short;
   new_case->people = people;
   new_case->notes = ({ });
   new_case->events = ({ });
   new_case->time_opened = time();
   save_case(new_case);
   return new_case->id;
}
private int create_note(string person, string text) {
   class nomic_case_note new_note;
   new_note = new(class nomic_case_note);
   new_note->id = query_next_note_id();
   new_note->person = person;
   new_note->text = text;
   new_note->time_created = time();
   save_note(new_note);
   return new_note->id;
}
private class nomic_case_event create_event(int type, string person,
                                            string mess, mixed data) {
   class nomic_case_event event;
   event = new(class nomic_case_event);
   event->type = type;
   event->mess = mess;
   event->person = person;
   event->event_time = time();
   event->data = data;
   return event;
}
string query_event_name(int type) {
   switch (type) {
   case NOMIC_CASE_EVENT_CLOSE :
      return "closed case";
   case NOMIC_CASE_EVENT_APPEAL :
      return "appealed case";
   case NOMIC_CASE_EVENT_ADD_PERSON :
      return "add person";
   case NOMIC_CASE_EVENT_REMOVE_PERSON :
      return "remove person";
   default :
      return "unknown";
   }
}
class nomic_case query_open_case(string area, int id) {
   string fname;
   string tmp;
   if (!_open_cases[area]) {
      return 0;
   }
   if (member_array(id, _open_cases[area]) == -1) {
      return 0;
   }
   fname = query_case_file_name(id);
   tmp = unguarded((: read_file($(fname)) :));
   if (tmp) {
      return restore_variable(tmp);
   }
   return 0;
}
class nomic_case query_recently_closed_case(string area, int id) {
   string fname;
   string tmp;
   if (!_recently_closed_cases[area]) {
      return 0;
   }
   if (member_array(id, _recently_closed_cases[area]) == -1) {
      return 0;
   }
   fname = query_case_file_name(id);
   tmp = unguarded((: read_file($(fname)) :));
   if (tmp) {
      return restore_variable(tmp);
   }
   return 0;
}
class nomic_case query_closed_case(string area, int id) {
   string fname;
   string tmp;
   if (!_closed_cases[area]) {
      return 0;
   }
   if (member_array(id, _closed_cases[area]) == -1) {
      return 0;
   }
   fname = query_case_file_name(id);
   tmp = unguarded((: read_file($(fname)) :));
   if (tmp) {
      return restore_variable(tmp);
   }
   return 0;
}
class nomic_case_note query_note(int note_num) {
   string fname;
   string tmp;
   fname = query_note_file_name(note_num);
   tmp = unguarded((: read_file($(fname)) :));
   if (tmp) {
      return restore_variable(tmp);
   }
   return 0;
}
int add_new_case(string area, string opener, string short, string* people) {
   int case_id;
   if (!_open_cases[area]) {
      return 0;
   }
   case_id = create_case(opener, short, people);
   _open_cases[area] += ({ case_id });
   save_me();
   send_council_inform(area, 1, opener + " opened a case with " +
                      query_multiple_short(people));
   return case_id;
}
int close_case(string area, int id, string closer, string result,
               mixed data) {
   class nomic_case the_case;
   class nomic_case_event event;
   the_case = query_open_case(area, id);
   if (!the_case || !stringp(result)) {
      return 0;
   }
   event = create_event(NOMIC_CASE_EVENT_CLOSE, closer, result, data);
   the_case->events += ({ event });
   save_case(the_case);
   _open_cases[area] -= ({ the_case->id });
   _recently_closed_cases[area] += ({ the_case->id });
   save_me();
   send_council_inform(area, 1, closer + " closed a case with " +
                      query_multiple_short(the_case->people));
   return 1;
}
int appeal_case(string area, int id, string appealer, string reason) {
   class nomic_case the_case;
   class nomic_case_event event;
   the_case = query_recently_closed_case(area, id);
   if (!the_case || !stringp(reason)) {
      return 0;
   }
   event = create_event(NOMIC_CASE_EVENT_APPEAL, appealer, reason, 0);
   the_case->events += ({ event });
   save_case(the_case);
   _recently_closed_cases[area] -= ({ the_case->id });
   _open_cases[area] += ({ the_case->id });
   save_me();
   send_council_inform(area, 1, appealer + " appeals a case with " +
                      query_multiple_short(the_case->people));
   return 1;
}
int add_note_to_case(string area, int id, string person, string text) {
   class nomic_case the_case;
   int note_id;
   the_case = query_open_case(area, id);
   if (!the_case) {
      return 0;
   }
   note_id = create_note(person, text);
   the_case->notes += ({ note_id });
   save_case(the_case);
   save_me();
   return 1;
}
int add_person_to_case(string area, int id, string adder,
                       string person, string text) {
   class nomic_case the_case;
   class nomic_case_event event;
   the_case = query_open_case(area, id);
   if (!the_case || !stringp(text) ||
       member_array(person, the_case->people) != -1) {
      return 0;
   }
   event = create_event(NOMIC_CASE_EVENT_ADD_PERSON, adder, text, 0);
   the_case->events += ({ event });
   the_case->people += ({ person });
   save_case(the_case);
   return 1;
}
int remove_person_from_case(string area, int id, string remover,
                       string person, string text) {
   class nomic_case the_case;
   class nomic_case_event event;
   the_case = query_open_case(area, id);
   if (!the_case || !stringp(text) ||
       member_array(person, the_case->people) == -1) {
      return 0;
   }
   event = create_event(NOMIC_CASE_EVENT_REMOVE_PERSON, remover, text, 0);
   the_case->events += ({ event });
   the_case->people -= ({ person });
   save_case(the_case);
   return 1;
}
void update_recently_closed_cases() {
   string area;
   int* stuff;
   int id;
   class nomic_case the_case;
   class nomic_case_event event;
   int last_close;
   foreach (area, stuff in _recently_closed_cases) {
      foreach (id in stuff) {
         the_case = query_recently_closed_case(area, id);
         last_close = 0;
         foreach (event in the_case->events) {
            if (event->type == NOMIC_CASE_EVENT_CLOSE) {
               last_close = event->event_time;
            }
         }
         if (last_close < time() - NOMIC_CASE_APPEAL_TIME) {
            _closed_cases[area] += ({ id });
            _recently_closed_cases[area] -= ({ id });
         }
      }
   }
}