#include <player_handler.h>
#include <playtesters.h>
#include <player.h>
private mapping _magistrates;
private mapping _citizens;
int is_citizen_of(string area, string citizen);
void save_me();
void create() {
   _citizens = ([ ]);
   _magistrates = ([ ]);
}
int create_area(string area, int num_magistrates) {
   _citizens[area] = ({ });
   _magistrates[area] = allocate(num_magistrates);
   save_me();
}
string* query_citizenship_areas() {
   return keys(_citizens);
}
int remove_citizen(string area, string citizen) {
   int pos;
   if (!_citizens[area]) {
      return 0;
   }
   if (member_array(citizen, _citizens[area]) != -1) {
      _citizens[area] -= ({ citizen });
      if (citizen) {
         pos = member_array(citizen, _magistrates[area]);
         if (pos != -1) {
            _magistrates[area][pos] = 0;
         }
      }
      save_me();
      return 1;
   }
   return 0;
}
int add_magistrate(string area, string magistrate) {
   int pos;
   if (!is_citizen_of(area, magistrate)) {
      return 0;
   }
   pos = member_array(0, _magistrates[area]);
   if (pos == -1) {
      return 0;
   }
   _magistrates[area][pos] = magistrate;
   save_me();
   PLAYER_TITLE_HANDLER->add_title_to_player(magistrate, "magistrate");
   return 1;
}
protected void setup_magistrates(string area, string* magistrates) {
   int i;
   int num;
   string magistrate;
   if (!_magistrates[area]) {
      return ;
   }
   for (i = 0; i < sizeof(_magistrates[area]); i++) {
      _magistrates[area][i] = 0;
   }
   num = sizeof(_magistrates[area]);
   if (num <= sizeof(magistrates)) {
      magistrates = magistrates[0..num];
   } else {
      magistrates += allocate(num - sizeof(magistrates));
   }
   _magistrates[area] = magistrates;
   save_me();
   foreach (magistrate in magistrates) {
      PLAYER_TITLE_HANDLER->add_title_to_player(magistrate, "magistrate");
   }
}
int query_number_of_magistrates(string area) {
   if (!_magistrates[area]) {
      return 0;
   }
   return sizeof(_magistrates[area]);
}
string* query_magistrates(string area) {
   if (!_magistrates[area]) {
      return ({ });
   }
   return _magistrates[area] - ({ 0 });
}
int add_citizen(string area, string citizen) {
   if (!PLAYER_HANDLER->test_user(citizen)) {
      return 0;
   }
   if (!_citizens[area]) {
      return 0;
   }
   _citizens[area] += ({ citizen });
   save_me();
   return 1;
}
int is_citizen_of(string area, string citizen) {
   if (!_citizens[area]) {
      return 0;
   }
   if (master()->query_lord(citizen)) {
      return 1;
   }
   return member_array(citizen, _citizens[area]) != -1;
}
int is_magistrate_of(string area, string magistrate) {
   if (!_magistrates[area]) {
      return 0;
   }
   if (master()->query_lord(magistrate)) {
      return 1;
   }
   return member_array(magistrate, _magistrates[area]) != -1;
}
string query_citizen(string citizen) {
   string bing;
   foreach (bing in query_citizenship_areas()) {
      if (is_citizen_of(bing, citizen)) {
         return bing;
      }
   }
   return 0;
}
int is_magistrate_anywhere(string person) {
   string bing;
   foreach (bing in query_citizenship_areas()) {
      if (is_magistrate_of(bing, person)) {
         return 1;
      }
   }
   return 0;
}
int query_number_of_citizens(string area) {
   return sizeof(_citizens[area]);
}