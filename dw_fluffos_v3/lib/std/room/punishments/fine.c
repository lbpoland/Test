#include <money.h>
#include <nomic_system.h>
#include <player_handler.h>
inherit "/std/room/inherit/punishment_inherit";
#define TIMEOUT (4 * 7 * 24 * 60 * 60)
private mapping _fines;
private nosave string _money_area;
private nosave string _save_file;
class fine_type {
   int paid;
   int fines;
   int last_touched;
}
void load_me();
void setup() {
   _fines = ([ ]);
   set_short("fine");
   set_description_file(NOMIC_PUNISHMENT_DOCS_DIR + "fine");
   seteuid(getuid());
   load_me();
}
void load_me() {
   if (_save_file) {
      unguarded((: restore_object( _save_file ) :));
      call_out("remove_old_fines", 2);
   }
}
void save_me() {
   unguarded((: save_object( _save_file ) :));
}
void remove_old_fines() {
   class fine_type fine;
   string player;
   int changed;
   foreach (player, fine in _fines) {
      if (!PLAYER_HANDLER->test_user(player)) {
         map_delete(_fines, player);
         changed = 1;
      }
      if (sizeof(fine) == 2) {
         fine = new(class fine_type, paid : fine->paid, fines : fine->fines,
                                last_touched : time());
         _fines[player] = fine;
         changed = 1;
      }
      if (fine->fines <= 0 && fine->last_touched + TIMEOUT < time()) {
         map_delete(_fines, player);
         changed = 1;
      }
   }
   if (changed) {
      save_me();
   }
}
void set_money_area(string area) {
   _money_area = area;
}
string query_money_area() {
   return _money_area;
}
void set_save_file(string fname) {
   _save_file = fname;
}
string query_save_file() {
   return _save_file;
}
void start_punishment(string area,
                      class nomic_case the_case,
                      string type,
                      function finish) {
   write("How much do you wish to fine " +
         query_multiple_short(the_case->people) + "? ");
   input_to("fine_amount", 0, area, the_case, type, finish);
}
string query_short(string area,
                      class nomic_case the_case,
                      string type,
                      mixed data) {
   return "fined " +
          MONEY_HAND->money_value_string(data, _money_area);
}
void fine_amount(string amt, string area, class nomic_case the_case,
                 string type, function finish) {
   int value;
   amt = lower_case(amt);
   if (!strlen(amt) || amt[0] == 'q') {
      write("Aborting the fine.\n");
      return ;
   }
   value = MONEY_HAND->value_from_string(amt, _money_area);
   if (value <= 0) {
      write("You did not specify a positive money value.\n");
      write("How much do you wish to fine " +
            query_multiple_short(the_case->people) + "? ");
      input_to("fine_amount", 0, area, the_case, type, finish);
      return ;
   }
   evaluate(finish, the_case, type, value);
}
void complete_punishment(string area,
                      class nomic_case the_case,
                      string type,
                      mixed data) {
   string person;
   foreach (person in the_case->people) {
      if (!_fines[person]) {
         _fines[person] = new(class fine_type);
      }
      _fines[person]->fines += data;
      _fines[person]->last_touched = time();
   }
   save_me();
   return ;
}
void suspend_punishment(string area,
                      class nomic_case the_case,
                      string type,
                      mixed data) {
   string person;
   foreach (person in the_case->people) {
      if (!_fines[person]) {
         _fines[person] = new(class fine_type);
      }
      _fines[person]->fines -= data;
      _fines[person]->last_touched = time();
   }
   save_me();
   return ;
}
int pay_fine(string person, int amount) {
   if (_fines[person]) {
      _fines[person]->paid += amount;
      _fines[person]->last_touched = time();
      save_me();
      return 1;
   }
   return 0;
}
int query_current_fine(string person) {
   if (_fines[person]) {
      return _fines[person]->fines - _fines[person]->paid;
   }
   return 0;
}
int query_total_fine(string person) {
   if (_fines[person]) {
      return _fines[person]->fines;
   }
   return 0;
}
int query_total_payments(string person) {
   if (_fines[person]) {
      return _fines[person]->paid;
   }
   return 0;
}
string* query_people_with_fines() {
   return keys(_fines);
}