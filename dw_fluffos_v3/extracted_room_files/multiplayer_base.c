# File: /lib/std/room/furniture/games/multiplayer_base.c

private inherit "/std/basic/auto_load";
#define LOAD_TAG "multiplayer base"
class player_info {
   int number;
   string cap_name;
   string name;
   mixed data;
}
private mapping _players;
private string _winner;
private string* _ids_when_started;
private string _current_player;
private int _minimum_needed;
private int _maximum_allowed;
private int _can_join_as_new;
private int _game_started;
string* query_currently_playing_ids();
void delete_gone_players();
string find_player_id_of_person(object person);
void create() {
   _players = ([ ]);
   _ids_when_started = ({ });
}
void reset_game() {
}
int start_game() {
   delete_gone_players();
   if (sizeof(query_currently_playing_ids()) < _minimum_needed) {
      return 0;
   }
   _winner = 0;
   _game_started = 1;
   _ids_when_started = query_currently_playing_ids();
   _current_player = _ids_when_started[random(sizeof(_ids_when_started))];
   return 1;
}
void finish_game(string winner) {
   _winner = winner;
   _game_started = 0;
}
string query_winner() {
   return _winner;
}
int is_game_started() {
   return _game_started;
}
int can_join_as_new_player() {
   return _can_join_as_new;
}
void set_can_join_as_new_player(int join) {
   _can_join_as_new = join;
}
int is_person_playing(string id) {
   if (_players[id]->name) {
      if (find_player(_players[id]->name) &&
          is_in_me_or_environment(this_object(),
                                  find_player(_players[id]->name)) &&
          interactive(find_player(_players[id]->name))) {
         return 1;
      }
   }
   return 0;
}
int is_playing(object ob) {
   string id;
   id = find_player_id_of_person(ob);
   return id != 0;
}
int is_current_player(object ob) {
   string id;
   id = find_player_id_of_person(ob);
   return id == _current_player;
}
int add_person_to_game(string id, object person) {
   class player_info info;
   if (is_person_playing(id)) {
      return 0;
   }
   info = _players[id];
   info->name = person->query_name();
   info->cap_name = person->query_cap_name();
   return 1;
}
int remove_person_object_from_game(object person) {
   class player_info info;
   string id;
   foreach (id, info in _players) {
      if (find_player(info->name) == person) {
         info->name = 0;
         info->cap_name = 0;
         return 1;
      }
   }
   return 0;
}
int remove_person_id_from_game(string id) {
   if (_players[id]->name) {
      _players[id]->name = 0;
      return 1;
   }
   return 0;
}
void randomise_player_numbers() {
   string* ids;
   int num;
   int pos;
   ids = keys(_players);
   num = 0;
   while (sizeof(ids)) {
      pos = random(sizeof(ids));
      _players[ids[pos]]->number = num;
      ids = ids[0..pos-1] + ids[pos+1..];
      num++;
   }
}
void add_player_id_type(string id, int number) {
   _players[id] = new(class player_info);
   _players[id]->number = number;
}
void remove_player_id_type(string id) {
   map_delete(_players, id);
}
class player_info find_player_info_from_number(int num) {
   class player_info info;
   string id;
   foreach (id, info in _players) {
      if (info->number == num) {
         return info;
      }
   }
   return 0;
}
string find_player_id_from_number(int num) {
   class player_info info;
   string id;
   foreach (id, info in _players) {
      if (info->number == num) {
         return id;
      }
   }
   return 0;
}
string* query_player_ids() {
   return keys(_players);
}
string* query_currently_playing_ids() {
   return filter(keys(_players), (: is_person_playing($1) :));
}
string* query_started_player_ids() {
   return _ids_when_started;
}
string query_player_cap_name(string id) {
   if (_players[id] && _players[id]->name) {
      return _players[id]->cap_name;
   }
   return "No one";
}
object query_player_object(string id) {
   return find_player(_players[id]->name);
}
string query_player_the_short(string id) {
   object ob;
   if (_players[id]->name) {
      ob = query_player_object(id);
      if (ob) {
         return ob->the_short();
      }
   }
   return "No one";
}
string query_player_poss_short(string id) {
   object ob;
   if (_players[id]->name) {
      ob = query_player_object(id);
      if (ob) {
         return ob->poss_short();
      }
   }
   return "No one";
}
void delete_gone_players() {
   string id;
   class player_info info;
   foreach (id, info in _players) {
      if (info->name) {
         if (!find_player(info->name) ||
             !is_in_me_or_environment(this_object(), find_player(info->name))) {
            info->name = 0;
         }
      }
   }
}
void set_minimum_needed(int minimun) {
   _minimum_needed = minimun;
}
int can_start_game() {
   if (sizeof(query_currently_playing_ids()) > _minimum_needed) {
      return 1;
   }
   return 0;
}
string find_next_player(string id) {
   class player_info info;
   int start;
   int cur;
   string new_id;
   if (!id) {
      id = _current_player;
   }
   start = _players[id]->number;
   cur = start;
   do {
      cur = (cur + 1) % sizeof(_players);
      new_id = find_player_id_from_number(cur);
      info = _players[new_id];
   } while (((_can_join_as_new && !info->name) ||
            (!_can_join_as_new &&
                member_array(new_id, _ids_when_started) == -1)) &&
            cur != start);
   return new_id;
}
string find_previous_player(string id) {
   class player_info info;
   int start;
   string new_id;
   int cur;
   if (!id) {
      id = _current_player;
   }
   start = _players[id]->number;
   cur = start;
   do {
      cur = (cur - 1 + sizeof(_players)) % sizeof(_players);
      new_id = find_player_id_from_number(cur);
      info = _players[new_id];
   } while (((_can_join_as_new && !info->name) ||
            (!_can_join_as_new &&
               member_array(new_id, _ids_when_started) == -1)) &&
            cur != start);
   return new_id;
}
void increment_current_player() {
   _current_player = find_next_player(_current_player);
}
string find_player_id_of_person(object person) {
   class player_info info;
   string id;
   foreach (id, info in _players) {
      if (find_player(info->name) == person) {
         return id;
      }
   }
   return 0;
}
string query_current_player() {
   if (!_current_player) {
      _current_player = find_player_id_from_number(0);
   }
   return _current_player;
}
string set_current_player(string id) {
   _current_player = id;
}
void tell_player(string id, string message) {
   object player;
   player = find_player(_players[id]->name);
   if (player && (environment(player) == environment() ||
                  player == environment())) {
      tell_object(player, message);
   }
}
void tell_current_player(string message) {
   tell_player(_current_player, message);
}
varargs void tell_all_players(string message, string* exclude) {
   class player_info info;
   string id;
   if (!exclude) {
      exclude = ({ });
   }
   foreach (id, info in _players) {
      if (member_array(id, exclude) == -1) {
         tell_player(id, message);
      }
   }
}
mixed query_player_data(string id) {
   return _players[id]->data;
}
void set_player_data(string id, mixed data) {
   _players[id]->data = data;
}
void multiplayer_someone_joins(string id) {
}
void multiplayer_someone_resigns(string id, string name) {
}
mixed* shuffle_array(mixed *arr) {
   int i;
   int pos;
   mixed* new_arr;
   for (i = 0; i < 2; i++) {
      new_arr = ({ });
      while (sizeof(arr)) {
         pos = random(sizeof(arr));
         new_arr += arr[pos..pos];
         arr = arr[0..pos - 1] + arr[pos + 1..];
      }
      arr = new_arr;
   }
   return arr;
}
int do_join(string id) {
   if (is_person_playing(id)) {
      add_failed_mess("Someone is already playing " + id + " on $D.\n");
      return 0;
   }
   if (is_playing(this_player())) {
      add_failed_mess("You are already playing on $D.\n");
      return 0;
   }
   if (is_game_started() &&
       !can_join_as_new_player() &&
       member_array(id, query_started_player_ids()) == -1) {
      add_failed_mess("You can only take over one of the spots vacated by "
                      "someone else.\n");
      return 0;
   }
   if (add_person_to_game(id, this_player())) {
      add_succeeded_mess("$N $V as " + id + " on $D.\n");
      multiplayer_someone_joins(id);
      return 1;
   }
   add_failed_mess("Some weird error joining game on $D.\n");
   return 0;
}
int do_resign() {
   string id;
   id = find_player_id_of_person(this_player());
   if (remove_person_object_from_game(this_player())) {
      add_succeeded_mess("$N $V from the game on $D.\n");
      multiplayer_someone_resigns(id, this_player()->query_cap_name());
      if (id == query_current_player()) {
         increment_current_player();
      }
      return 1;
   }
   add_failed_mess("You are not playing on $D to resign.\n");
   return 0;
}
void init() {
   string ids;
   ids = implode(keys(_players), "|");
   add_command("join", "[game] [as] {" + ids + "} on <direct:object>",
                (: do_join($4[0]) :));
   add_command("resign", "[from] [game] on <direct:object>",
               (: do_resign() :));
}
mapping query_dynamic_auto_load(mapping map) {
   if (!map) {
      return 0;
   }
   add_auto_load_value(map, LOAD_TAG, "players", _players);
   add_auto_load_value(map, LOAD_TAG, "current player", _current_player);
   add_auto_load_value(map, LOAD_TAG, "started ids", _ids_when_started);
   add_auto_load_value(map, LOAD_TAG, "winner", _winner);
   add_auto_load_value(map, LOAD_TAG, "game started", _game_started);
   return map;
}
void init_dynamic_arg(mapping map, object player) {
   if (!map) {
      return ;
   }
   _players = query_auto_load_value(map, LOAD_TAG, "players");
   _current_player = query_auto_load_value(map, LOAD_TAG, "current player");
   _ids_when_started = query_auto_load_value(map, LOAD_TAG, "started ids");
   _winner = query_auto_load_value(map, LOAD_TAG, "winner");
   _game_started = query_auto_load_value(map, LOAD_TAG, "game started");
}