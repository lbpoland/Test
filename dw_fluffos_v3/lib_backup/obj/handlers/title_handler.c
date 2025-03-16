#include <login.h>
private mapping _pending;
private mapping _titles;
private nosave string* _allowed_multiple;
#define SAVE_FILE "/save/titles"
void load_me();
void save_me();
class blob {
   string ob;
   string func;
}
void create() {
   _pending = ([ ]);
   _titles = ([ ]);
   load_me();
   _allowed_multiple = ({ "very reverend", "mostly reverend",
                          "reverend mother", "mad granny",
                          "mad nanny", "mad mr", "mad ms", "mad miss",
                          "mad mrs" });
}
int is_allowed_multiple_title(string title) {
   return member_array(lower_case(title), _allowed_multiple) != -1;
}
string* query_allowed_multiple_titles() {
   return _allowed_multiple;
}
void add_title_to_player(string person, string title) {
   object ob;
   ob = find_player(person);
   if (ob) {
      ob->add_player_title(title);
      return ;
   }
   if (!_pending[person]) {
      _pending[person] = ({ });
   }
   _pending[person] += ({ title });
   save_me();
}
string* query_pending_titles(string person) {
   if (_pending[person]) {
      return _pending[person];
   }
   return ({ });
}
void add_controlled_title(string title, string ob, string func) {
   class blob fluff;
   fluff = new(class blob);
   fluff->ob = ob;
   fluff->func = func;
   _titles[title] = fluff;
   save_me();
}
protected class blob query_controlled_title(string title) {
   return _titles[title];
}
void check_player(object player) {
   string* titles;
   string title;
   if (!player) {
      return ;
   }
   if (_pending[player->query_name()]) {
      foreach (title in _pending[player->query_name()]) {
         player->add_player_title(title);
      }
      map_delete(_pending, player->query_name());
      save_me();
   }
   titles = player->query_all_player_titles();
   foreach (title in titles) {
      if (_titles[title]) {
         if(!find_object(_titles[title]->ob) ||
            !call_other(_titles[title]->ob, _titles[title]->func,
                        player->query_name())) {
           player->remove_player_title(title);
         }
      }
   }
}
void login_handler_call(string person, string type) {
   if (type == LOGIN) {
      call_out((: check_player(find_player($1)) :), 2, person);
   }
}
void save_me() {
   unguarded((: save_object(SAVE_FILE) :));
}
void load_me() {
   unguarded((: restore_object(SAVE_FILE, 1) :));
}