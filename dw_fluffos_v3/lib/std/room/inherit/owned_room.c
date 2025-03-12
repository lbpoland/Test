#include <room.h>
private string _owner;
private string* _allowed;
private nosave string _save_file;
private nosave string _front_door;
protected int do_allow(string name);
protected int do_throwout(string name);
protected int do_disallow(string name);
void load_room();
varargs mixed call_door( string direc,
                         string func,
                         mixed arg1,
                         mixed arg2,
                         mixed arg3);
string query_owner();
void create() {
   _allowed = ({ });
   load_room();
}
void init() {
   if (this_player()->query_name() == query_owner()) {
      add_command("room",
                  "allow <string'person'>",
                  (: do_allow($4[0]) :));
      add_command("room",
                  "disallow <string'person'>",
                  (: do_disallow($4[0]) :));
      add_command("room",
                  "throwout <indirect:living'person'>",
                  (: do_throwout($4[0]) :));
   }
}
void set_save_file(string name) {
   _save_file = name;
}
string query_save_file() {
   return _save_file;
}
string *query_allowed() {
   return _allowed;
}
protected void set_allowed(string *allowed) {
   _allowed = allowed;
}
string query_owner() {
   return _owner;
}
void set_owner(string owner) {
   _owner = owner;
}
protected int do_allow(string name) {
   name = lower_case(name);
   if (member_array(name, _allowed) != -1) {
      add_failed_mess("The person " + name + " is already allowed.\n");
      return 0;
   }
   _allowed += ({ name });
   write("Ok, you have allowed " + name + " to enter your room.\n");
   return 1;
}
protected int do_disallow(string name) {
   name = lower_case(name);
   if (member_array(name, _allowed) == -1) {
      add_failed_mess("The person " + name + " is not allowed to disallow.\n");
      return 0;
   }
   _allowed -= ({ name });
   write("Ok, you have disallowed " + name + " from entering your room.\n");
   return 1;
}
protected int do_throwout(object *people) {
   object per;
   object *moved;
   moved = ({ });
   foreach (per in people) {
      if ( ROOM_HANDLER->exit_move( _front_door, 0, 0, per) ) {
         moved += ({ per });
      }
   }
   if (!sizeof(moved)) {
      add_failed_mess("Unable to move $I for some reason.\n", people);
      return 0;
   }
   add_succeeded_mess("$N throw$s $I out of the room.\n", moved);
   return 1;
}
void set_front_door(string exit) {
   _front_door = exit;
}
string query_front_door() {
   return _front_door;
}
int is_allowed_in(string person) {
   person = lower_case(person);
   if (person != query_owner()) {
      if (call_door(_front_door,
                    "query_locked")) {
         if (member_array(person, _allowed) != -1) {
            return 0;
         }
      }
   }
   return 1;
}
int is_allowed(string person) {
   if (person == query_owner() ||
       member_array(person, query_allowed()) != -1) {
      return 1;
   }
   return 0;
}
void load_room() {
   if (_save_file) {
      restore_object(_save_file);
      call_door(_front_door,
                "set_locked",
                1);
   }
}
void save_room() {
   if (_save_file) {
      save_object(_save_file);
   }
}