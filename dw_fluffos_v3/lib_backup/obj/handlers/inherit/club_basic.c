#include <clubs.h>
#include <broadcaster.h>
#include <player_handler.h>
class club_info {
   string actual_name;
   string founder;
   string *recruiters;
   string *members;
   int type;
   mapping accounts;
   int last_paid;
   int last_touched;
   mixed extra_data;
   string description;
   string region;
}
#define CLUB_CACHE_SIZE 20
private mapping _club_names;
private string *_observers;
private nosave int _no_cache_hits;
private nosave int _no_cache_requests;
private nosave int _no_cache_miss;
private nosave int _cache_call_out;
private nosave mapping _cache;
private nosave string *_cache_order;
#define SAVE_FILE_NAME "/save/clubs"
#define SAVE_FILE_DIR "/save/clubs/"
protected void save_club(string name);
protected void load_main();
protected void save_main();
int is_club(string club_name);
int remove_recruiter(string name, string recruiter);
int is_recruiter_of(string name, string recruiter);
int query_club_type(string name);
void check_extra_information(string club_name, string member, int login);
int is_family(string name);
int disband_club(string name);
protected void set_club_changed(string name);
protected void send_broadcast_message(string club,
                                      string message);
protected void send_observer_event(string event_name,
                                   string *args ...);
void create() {
    seteuid(master()->creator_file(file_name()));
   _club_names = ([ ]);
   _cache = ([ ]);
   _cache_order = ({ });
   _observers = ({ });
   load_main();
}
string query_cap_name() {
   return "Club controller";
}
protected void load_main() {
   unguarded( (: restore_object(SAVE_FILE_NAME, 1) :) );
}
protected void save_main() {
   unguarded( (: save_object(SAVE_FILE_NAME, 1) :) );
}
string normalise_name(string name) {
   return replace_string(lower_case(name), " ", "_");
}
private void fixup_cache() {
   int i;
   if (sizeof(_cache_order) > CLUB_CACHE_SIZE) {
      for (i = sizeof(_cache_order) - CLUB_CACHE_SIZE; i >= 0; i--) {
         if (_club_names[_cache_order[i]]) {
            save_club(_cache_order[i]);
         }
         map_delete(_cache, _cache_order[i]);
      }
      _cache_order = _cache_order[sizeof(_cache_order) - CLUB_CACHE_SIZE + 1..];
   }
}
protected class club_info query_club_info(string name) {
   class club_info bing;
   name = normalise_name(name);
   _no_cache_requests++;
   if (_cache[name]) {
      _no_cache_hits++;
      return _cache[name];
   }
   if (unguarded( (: file_size(SAVE_FILE_DIR + $(name)) :)) > 0) {
      _cache[name] = unguarded( (: restore_variable(read_file(SAVE_FILE_DIR +
                                                              $(name))) :) );
      _cache_order += ({ name });
      if (intp(_cache[name]->accounts)) {
         _cache[name]->accounts = ([ CLUB_DEFAULT_ACCOUNT_NAME : _cache[name]->accounts ]);
      }
      if (sizeof(_cache[name]) == 10) {
         bing = new(class club_info);
         bing->actual_name = _cache[name]->actual_name;
         bing->founder = _cache[name]->founder;
         bing->recruiters = _cache[name]->recruiters;
         bing->members = _cache[name]->members;
         bing->type = _cache[name]->type;
         bing->accounts = _cache[name]->accounts;
         bing->last_paid = _cache[name]->last_paid;
         bing->last_touched = _cache[name]->last_touched;
         bing->extra_data = _cache[name]->extra_data;
         bing->description = _cache[name]->description;
         bing->region = "Ankh-Morpork";
         _cache[name] = bing;
         set_club_changed(name);
      }
      fixup_cache();
      return _cache[name];
   }
   _no_cache_miss++;
   return 0;
}
protected void save_club(string name) {
   name = normalise_name(name);
   if (_cache[name]) {
      _club_names[name] = 0;
      unguarded( (: write_file(SAVE_FILE_DIR + $(name),
                               save_variable(_cache[$(name)]),
                               1) :) );
   }
}
protected void save_cache() {
   string name;
   class club_info data;
   foreach (name, data in _cache) {
      if (_club_names[name]) {
         save_club(name);
      }
   }
}
protected void set_club_changed(string name) {
   name = normalise_name(name);
   if (!undefinedp(_club_names[name])) {
      if (find_call_out(_cache_call_out) == -1) {
         _cache_call_out = call_out((: save_cache :), 0);
      }
      _club_names[name] = 1;
   }
}
private void add_club(string name,
                      class club_info data) {
   name = normalise_name(name);
   _cache[name] = data;
   _club_names[name] = 0;
   set_club_changed(name);
}
string the_short() {
   return "Club Control";
}
protected void create_extra_data(string name) {
   class club_info data;
   data = query_club_info(name);
   data->extra_data = 0;
   set_club_changed(name);
}
int create_club(string name, string founder, int type, string region) {
   class club_info info;
   if (!stringp(name) || !stringp(founder)) {
      return 0;
   }
   info = new(class club_info);
   info->actual_name = name;
   if (type != CLUB_FAMILY) {
      info->recruiters = ({ founder });
      info->members = ({ founder });
   } else {
      info->recruiters = ({ });
      info->members = ({ });
   }
   info->founder = founder;
   info->last_touched = time();
   info->type = type;
   info->last_paid = time();
   info->description = 0;
   info->accounts = ([ CLUB_DEFAULT_ACCOUNT_NAME : 0 ]);
   info->region = region;
   add_club(name, info);
   create_extra_data(name);
   set_club_changed(name);
   add_club(name, info);
   save_main();
   return 1;
}
int change_club_type(string name,
                     int type) {
   int club_type;
   class club_info info;
   if (is_club(name)) {
      club_type = query_club_type(name);
      info = query_club_info(name);
      if (club_type != type) {
         info->type = (club_type & CLUB_FLAGS_MASK) | type;
         set_club_changed(name);
         create_extra_data(name);
         return 1;
      }
   }
   return 0;
}
int query_club_type(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      if (!data) {
         disband_club(name);
      } else {
         return data->type & CLUB_TYPE_MASK;
      }
   }
}
int set_club_secret(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      data->type |= CLUB_SECRET_FLAG;
      set_club_changed(name);
      return 1;
   }
   return 0;
}
int reset_club_secret(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      data->type &= ~CLUB_SECRET_FLAG;
      set_club_changed(name);
      return 1;
   }
   return 0;
}
int query_club_secret(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      return (data->type & CLUB_SECRET_FLAG) != 0;
   }
}
string query_club_region(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      return data->region;
   }
   return 0;
}
int disband_club(string name) {
   class club_info data;
   name = normalise_name(name);
   if (is_club(name)) {
      data = query_club_info(name);
      if (data) {
         log_file("CLUB", ctime(time()) + ": disbanded '" +
                       this_object()->query_club_name(name) + "'; balance = " +
                       this_object()->query_balance(name, CLUB_DEFAULT_ACCOUNT_NAME) + "; fees due = " +
                       ctime(this_object()->query_time_fees_due(name)) +
                       "\n");
      } else {
         log_file("CLUB", ctime(time()) + " disbanded '" + name + "' "
                          "which has a bad data file.\n");
      }
      map_delete(_club_names, name);
      map_delete(_cache, name);
      unguarded( (: rm(SAVE_FILE_DIR + $(name)) :) );
      save_main();
      send_observer_event("club_event_disband_club", name);
      return 1;
   }
   return 0;
}
string *query_clubs() {
   return keys(_club_names);
}
string query_insignia_path(string name) {
   return "/obj/misc/club_badge";
}
void touch_club(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      data->last_touched = time();
      set_club_changed(name);
   }
}
string *query_recruiters(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      return data->recruiters;
   }
   return ({ });
}
string query_founder(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      return data->founder;
   }
   return 0;
}
string *query_members(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      return data->members;
   }
   return ({ });
}
int add_recruiter(string name, string recruiter) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      if (member_array(recruiter, data->members) != -1 &&
          member_array(recruiter, data->recruiters) == -1) {
         data->recruiters += ({ recruiter });
         set_club_changed(name);
         touch_club(name);
         if (!is_family(name)) {
            send_broadcast_message(name,
                                   capitalize(recruiter) +
                                   " becomes a recruiter for the club.");
         }
         return 1;
      }
   }
   return 0;
}
int add_member(string name, string member) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      if (member_array(member, data->members) == -1) {
         data->members += ({ member });
         set_club_changed(name);
         touch_club(name);
         if (!is_family(name)) {
            send_broadcast_message(name,
                                   capitalize(member) + " joins the club.");
         }
         return 1;
      }
   }
   return 0;
}
int remove_member(string name, string member) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      if (member_array(member, data->members) != -1) {
         if (is_recruiter_of(name, member)) {
            remove_recruiter(name, member);
         }
         data->members -= ({ member });
         set_club_changed(name);
         check_extra_information(name, member, 0);
         if (!is_family(name)) {
            send_broadcast_message(name,
                                   capitalize(member) + " leaves the club.");
         }
         send_observer_event("club_event_remove_member", name, member);
         return 1;
      }
   }
   return 0;
}
int remove_recruiter(string name, string recruiter) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      if (member_array(recruiter, data->recruiters) != -1) {
         data->recruiters -= ({ recruiter });
         set_club_changed(name);
         if (!is_family(name)) {
            send_broadcast_message(name,
                                   capitalize(recruiter) +
                                   " stops being a recruiter for the club.");
         }
         return 1;
      }
   }
   return 0;
}
string query_club_name(string club_name) {
   class club_info data;
   if (is_club(club_name)) {
      data = query_club_info(club_name);
      if (!data) {
         return club_name;
      }
      return data->actual_name;
   }
   return 0;
}
string query_club_description(string club_name) {
   class club_info data;
   if (is_club(club_name)) {
      data = query_club_info(club_name);
      return data->description;
   }
   return 0;
}
int set_club_description(string club_name, string description) {
   class club_info data;
   if (is_club(club_name)) {
      data = query_club_info(club_name);
      data->description = description;
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
int query_time_fees_due(string club_name) {
   class club_info data;
   if (is_club(club_name)) {
      data = query_club_info(club_name);
      return data->last_paid + CLUB_PAY_PERIOD;
   }
   return 0;
}
int query_club_cost_per_period(string club_name) {
   if (is_club(club_name)) {
      return CLUB_COST_PER_YEAR +
           sizeof(query_members(club_name)) * CLUB_COST_PER_MEMBER_PER_YEAR;
   }
   return 0;
}
int is_club(string name) {
   name = normalise_name(name);
   if (!undefinedp(_club_names[name])) {
      return 1;
   }
   return 0;
}
int is_elected_club(string name) {
   name = normalise_name(name);
   if (is_club(name)) {
      return query_club_type(name) == CLUB_ELECTED;
   }
   return 0;
}
int is_personal_club(string name) {
   if (is_club(name)) {
      return query_club_type(name) == CLUB_PERSONAL;
   }
   return 0;
}
int is_family(string name) {
   if (is_club(name)) {
      return query_club_type(name) == CLUB_FAMILY;
   }
   return 0;
}
int is_member_of(string name, string member) {
   if (is_club(name)) {
      return member_array(member, query_members(name)) != -1;
   }
   return 0;
}
int is_recruiter_of(string name, string recruiter) {
   if (is_club(name)) {
      return member_array(recruiter, query_recruiters(name)) != -1;
   }
   return 0;
}
int is_founder_of(string name, string founder) {
   name = normalise_name(name);
   if (is_club(name)) {
      return query_founder(name) == founder;
   }
   return 0;
}
int create_account(string name,
                   string account) {
   class club_info data;
   if (!account) {
      account = CLUB_DEFAULT_ACCOUNT_NAME;
   }
   if (is_club(name)) {
      data = query_club_info(name);
      if (undefinedp(data->accounts[account])) {
         data->accounts[account] = 0;
         touch_club(name);
         set_club_changed(name);
         return 1;
      }
   }
   return 0;
}
int add_money(string name,
              int amount,
              int type,
              string person,
              string account) {
   class club_info data;
   if (!account) {
      account = CLUB_DEFAULT_ACCOUNT_NAME;
   }
   if (is_club(name) && amount > 0) {
      data = query_club_info(name);
      if (!undefinedp(data->accounts[account])) {
         data->accounts[account] += amount;
         touch_club(name);
         set_club_changed(name);
         return 1;
      }
   }
   return 0;
}
int remove_money(string name,
                 int amount,
                 int type,
                 string person,
                 string account) {
   class club_info data;
   if (!account) {
      account = CLUB_DEFAULT_ACCOUNT_NAME;
   }
   if (is_club(name) && amount > 0) {
      data = query_club_info(name);
      if (!undefinedp(data->accounts[account])) {
         data->accounts[account] -= amount;
         touch_club(name);
         set_club_changed(name);
         return 1;
      }
   }
   return 0;
}
int query_balance(string name,
                  string account) {
   class club_info data;
   if (!account) {
      account = CLUB_DEFAULT_ACCOUNT_NAME;
   }
   if (is_club(name)) {
      data = query_club_info(name);
      return data->accounts[account];
   }
   return 0;
}
string* query_account_names(string name) {
   class club_info data;
   if (is_club(name)) {
      data = query_club_info(name);
      if (data) {
         return keys(data->accounts);
      }
   }
   return ({ });
}
int is_account_of(string club_name, string account) {
   return member_array(account, query_account_names(club_name)) != -1;
}
int is_creator_club(string club_name) {
   if (is_club(club_name)) {
      if (PLAYER_HANDLER->test_creator(query_founder(club_name))) {
         return 1;
      }
   }
   return 0;
}
int is_observer(string obs) {
   if (member_array(obs, _observers) != -1) {
      return 1;
   }
   return 0;
}
int add_observer(string obs) {
   if (!is_observer(obs) &&
       file_size(obs) > 0) {
      _observers += ({ obs });
      save_main();
      return 1;
   }
   return 0;
}
int remove_observer(string obs) {
   if (is_observer(obs)) {
      _observers -= ({ obs });
      save_main();
      return 1;
   }
   return 0;
}
string *query_observers() {
   return _observers;
}
protected void send_observer_event(string event_name,
                                   string *args ...) {
   string bing;
   foreach (bing in _observers) {
      if (file_size(bing) > 0) {
         call_out((: call_other($1, $2, $3 ...) :),
                  0,
                  event_name,
                  bing,
                  args ...);
      } else {
         remove_observer(bing);
      }
   }
}
protected void send_broadcast_message(string club,
                                      string message) {
   BROADCASTER->broadcast_to_channel(this_object(),
                                     lower_case(query_club_name(club)),
                                     ({ message, 0 }));
}
mixed *stats() {
   return ({
              ({ "cache hits", _no_cache_hits }),
              ({ "cache requests", _no_cache_requests }),
              ({ "cache miss", _no_cache_miss }),
              ({ "percentage", _no_cache_hits * 100 / _no_cache_requests }),
           });
}