inherit "/obj/handlers/inherit/club_family";
#define __CLUBS_H_NO_CLASSES
#include <clubs.h>
#include <mail.h>
#include <board.h>
#include <player_handler.h>
private mapping _elections;
private string *_boards;
private nosave mapping _discussion_items;
#define CLUB_PRESIDENT_INDEX          "president"
#define CLUB_VICE_PRESIDENT_INDEX     "vice-president"
#define CLUB_TREASURER_INDEX          "treasurer"
#define CLUB_SECRETARY_INDEX          "secretary"
#define CLUB_ORDINARY_COMMITTEE_INDEX "committee"
#define CLUB_BOARD_PREFIX "club "
#define CLUB_DISCUSS_MESSAGE_VERIFY            1
#define CLUB_DISCUSS_MESSAGE_COMPLETE          2
#define CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION 3
#define CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION  4
#define CLUB_DISCUSS_MESSAGE_NOMINATION        5
#define CLUB_MAX_ARCHIVE_SIZE 50
int is_nomination_accepted(string club_name,
                           string position,
                           string person);
int complete_election(string club_name);
int start_election(string club_name);
int holds_position_of(string name, string position, string person);
string query_position_name(string club_name,
                           string position);
int set_position_holder(string club_name,
                                  string position,
                                  string person);
protected int add_archive(string club_name,
                          string subject,
                          string thingy);
string query_club_board_name(string club_name);
class election_info {
   string treasurer;
   string president;
   string vice_president;
   string secretary;
   mapping account_info;
   mapping positions;
   int last_election;
   int election_period;
   mapping options;
   class discussion_idea *discussion;
   class club_archive *archives;
   string announcement;
   int announce_time;
}
#define CLUB_NOMINATION        1
#define CLUB_NOMINATION_SECOND 3
#define CLUB_ELECTION          2
class election_data {
   int time_of_event;
   int state;
   mapping people;
   mapping nominated;
   mapping voted_for;
   string election_status;
}
class account_info {
   class club_transaction* transactions;
   string* allowed_people;
   string* allowed_positions;
}
private class election_info query_elected_info(string name);
void create() {
   _elections = ([ ]);
   _boards = ({ });
   ::create();
   if (!_boards) {
      _boards = ({ });
   }
}
protected void create_extra_data(string name) {
   class election_info e_info;
   class club_info data;
   class club_transaction bing;
   class account_info frog;
   if (query_club_type(name)== CLUB_ELECTED) {
      data = (class club_info)query_club_info(name);
      e_info = new(class election_info);
      e_info->treasurer = CLUB_TREASURER_INDEX;
      e_info->president = CLUB_PRESIDENT_INDEX;
      e_info->vice_president = CLUB_VICE_PRESIDENT_INDEX;
      e_info->secretary = CLUB_SECRETARY_INDEX;
      e_info->discussion = ({ });
      e_info->positions = ([
                             CLUB_TREASURER_INDEX : CLUB_UNKNOWN_MEMBER,
                             CLUB_PRESIDENT_INDEX : data->founder,
                             CLUB_VICE_PRESIDENT_INDEX : CLUB_UNKNOWN_MEMBER,
                             CLUB_SECRETARY_INDEX : CLUB_UNKNOWN_MEMBER,
                           ]);
      e_info->account_info = ([ ]);
      e_info->last_election = time();
      e_info->options = ([ ]);
      e_info->election_period = CLUB_INVALID_TIME;
      e_info->announcement = "";
      e_info->archives = ({ });
      e_info->announce_time = 0;
      data->extra_data = e_info;
      set_club_changed(name);
      bing = new(class club_transaction);
      bing->date = time();
      bing->amount = query_balance(name, CLUB_DEFAULT_ACCOUNT_NAME);
      bing->transaction_type = CLUB_TRANSACTION_START_BALANCE;
      bing->who = CLUB_CONTROLLER_MEMBER;
      frog = new(class account_info);
      frog->transactions = ({ bing });
      frog->allowed_people = ({ });
      frog->allowed_positions = ({ CLUB_TREASURER_INDEX,
                                   CLUB_PRESIDENT_INDEX });
      e_info->account_info[CLUB_DEFAULT_ACCOUNT_NAME] = frog;
      set_club_changed(name);
   } else {
      ::create_extra_data(name);
   }
}
int change_club_type(string name,
                     int type) {
   if (::change_club_type(name, type)) {
      start_election(name);
      return 1;
   }
   return 0;
}
int disband_club(string name) {
   if (::disband_club(name)) {
      map_delete(_elections, name);
      _boards -= ({ query_club_board_name(name) });
      save_main();
      return 1;
   }
   return 0;
}
protected class election_info query_elected_info(string name) {
   class club_info data;
   class account_info fluff;
   if (is_elected_club(name)) {
      data = (class club_info)query_club_info(name);
      if (pointerp(data->extra_data->account_info)) {
         fluff = new(class account_info);
         fluff->transactions = data->extra_data->account_info;
         fluff->allowed_people = ({ });
         fluff->allowed_positions = ({ data->extra_data->president,
                                       data->extra_data->treasurer });
         data->extra_data->account_info = ([ CLUB_DEFAULT_ACCOUNT_NAME : fluff ]);
      }
      return data->extra_data;
   }
   return 0;
}
protected class account_info query_account_info(string name, string account) {
   class election_info bing;
   bing = query_elected_info(name);
   if (bing) {
      if (!account) {
         account = CLUB_DEFAULT_ACCOUNT_NAME;
      }
      return bing->account_info[account];
   }
   return 0;
}
int remove_member(string club, string member) {
   class election_info bing;
   class account_info fluff;
   string account;
   string person;
   string position;
   string name;
   mapping nominations;
   string *people;
   if (::remove_member(club, member)) {
      bing = query_elected_info(club);
      if (bing) {
         foreach (account, fluff in bing->account_info) {
            fluff->allowed_people -= ({ member });
         }
         foreach (position, person in bing->positions) {
            if (person == member) {
               set_position_holder(club, position, CLUB_UNKNOWN_MEMBER);
            }
         }
      }
      name = normalise_name(club);
      if (_elections[name]) {
         foreach (position, nominations in _elections[name]->nominated) {
            map_delete(nominations, member);
            foreach (person, people in nominations) {
               nominations[person] = people - ({ member });
            }
         }
         foreach (position, nominations in _elections[name]->people) {
            map_delete(nominations, member);
         }
      }
      return 1;
   }
   return 0;
}
int query_last_election(string name) {
   class election_info info;
   info = query_elected_info(name);
   if (info) {
      return info->last_election;
   }
   return 0;
}
int query_next_election(string name) {
   int bing;
   bing = query_last_election(name);
   if (bing) {
      return bing + CLUB_ELECTION_PERIOD;
   }
   return 0;
}
int query_minimum_next_election(string name) {
   int bing;
   bing = query_last_election(name);
   if (bing) {
      return bing + CLUB_MINIMUM_ELECTION_PERIOD;
   }
   return 0;
}
int is_president_of(string name, string president) {
   class election_info info;
   info = query_elected_info(name);
   if (info) {
      return holds_position_of(name, info->president, president);
   }
   return 0;
}
int is_vice_president_of(string name, string vice_president) {
   class election_info info;
   info = query_elected_info(name);
   if (info) {
      return holds_position_of(name, info->vice_president, vice_president);
   }
   return 0;
}
int is_secretary_of(string name, string secretary) {
   class election_info info;
   info = query_elected_info(name);
   if (info) {
      return holds_position_of(name, info->secretary, secretary);
   }
   return 0;
}
int is_treasurer_of(string name, string treasurer) {
   class election_info info;
   info = query_elected_info(name);
   if (info) {
      return holds_position_of(name, info->treasurer, treasurer);
   }
   return 0;
}
int holds_any_position_of(string name, string person) {
   class election_info info;
   string pos_name;
   string per_name;
   info = query_elected_info(name);
   if (info) {
      foreach (pos_name, per_name in info->positions) {
         if (per_name == person) {
            return 1;
         }
      }
   }
   return 0;
}
int holds_position_of(string name, string position, string person) {
   class election_info info;
   info = query_elected_info(name);
   if (info) {
      position = query_position_name(name, position);
      return info->positions[position] == person;
   }
}
int create_account(string name, string account) {
   if (!account) {
      account = CLUB_DEFAULT_ACCOUNT_NAME;
   }
   if (::create_account(name, account)) {
      class election_info info;
      class account_info frog;
      info = query_elected_info(name);
      if (info) {
         frog = new(class account_info);
         frog->transactions = ({ });
         frog->allowed_people = ({ });
         frog->allowed_positions = ({ info->president, info->treasurer });
         info->account_info[account] = frog;
         set_club_changed(name);
      }
      return 1;
   }
   return 0;
}
int add_money(string name,
              int amount,
              int type,
              string person,
              string account,
              string information) {
   class account_info frog;
   class club_transaction bing;
   if (::add_money(name, amount, type, person, account)) {
      frog = query_account_info(name, account);
      if (frog) {
         bing = new(class club_transaction);
         bing->date = time();
         bing->amount = amount;
         bing->transaction_type = type;
         bing->who = person;
         bing->information = information;
         frog->transactions += ({ bing });
         set_club_changed(name);
      }
      return 1;
   }
   return 0;
}
int remove_money(string name,
                 int amount,
                 int type,
                 string person,
                 string account,
                 string information) {
   class account_info frog;
   class club_transaction bing;
   if (::remove_money(name, amount, type, person, account)) {
      frog = query_account_info(name, account);
      if (frog) {
         bing = new(class club_transaction);
         bing->date = time();
         bing->amount = -amount;
         bing->transaction_type = type;
         bing->who = person;
         bing->information = information;
         frog->transactions += ({ bing });
         set_club_changed(name);
      }
      return 1;
   }
   return 0;
}
class club_transaction* query_transactions(string name, string account) {
   class account_info frog;
   class club_transaction bing;
   class club_transaction old;
   int i;
   if (is_elected_club(name)) {
      frog = query_account_info(name, account);
      if (sizeof(frog->transactions) &&
          sizeof(frog->transactions[0]) == 4) {
         for (i = 0; i < sizeof(frog->transactions); i++) {
            old = frog->transactions[i];
            bing = new(class club_transaction);
            bing->who = old->who;
            bing->transaction_type = old->transaction_type;
            bing->amount = old->amount;
            bing->date = old->date;
            bing->information = 0;
            frog->transactions[i] = bing;
            set_club_changed(name);
         }
      }
      return frog->transactions;
   }
   return ({ });
}
string query_transaction_type_name(int type) {
   switch (type) {
      case CLUB_TRANSACTION_UPKEEP :
         return "upkeep";
      case CLUB_TRANSACTION_DEPOSIT :
         return "player deposit";
      case CLUB_TRANSACTION_INSIGNIA :
         return "insignia";
      case CLUB_TRANSACTION_START_BALANCE :
         return "start balance";
      case CLUB_TRANSACTION_WITHDRAWL :
         return "player withdrawl";
      case CLUB_TRANSACTION_TRANSFER :
         return "player transfer";
      default :
         return "unknown";
   }
}
string* query_account_allowed_people(string club_name, string account) {
   class account_info frog;
   frog = query_account_info(club_name, account);
   if (frog) {
      return frog->allowed_people;
   }
   return ({ });
}
int is_allowed_to_modify_account(string club_name,
                               string account,
                               string person) {
   class account_info frog;
   string pos;
   frog = query_account_info(club_name, account);
   if (frog) {
      if (member_array(person, frog->allowed_people) != -1) {
         return 1;
      }
      foreach (pos in frog->allowed_positions) {
         if (holds_position_of(club_name, pos, person)) {
            return 1;
         }
      }
   }
   return 0;
}
int add_account_allowed_person(string club_name, string account, string person) {
   class account_info frog;
   frog = query_account_info(club_name, account);
   if (frog &&
       member_array(person, frog->allowed_people) == -1) {
      frog->allowed_people += ({ person });
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
int remove_account_allowed_person(string club_name, string account, string person) {
   class account_info frog;
   frog = query_account_info(club_name, account);
   if (frog &&
       member_array(person, frog->allowed_people) != -1) {
      frog->allowed_people -= ({ person });
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
string* query_account_allowed_positions(string club_name, string account) {
   class account_info frog;
   frog = query_account_info(club_name, account);
   if (frog) {
      return frog->allowed_positions;
   }
   return ({ });
}
int add_account_allowed_position(string club_name, string account, string position) {
   class account_info frog;
   frog = query_account_info(club_name, account);
   if (frog &&
       member_array(position, frog->allowed_positions) == -1) {
      frog->allowed_positions += ({ position });
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
int remove_account_allowed_position(string club_name, string account, string position) {
   class account_info frog;
   frog = query_account_info(club_name, account);
   if (frog &&
       member_array(position, frog->allowed_positions) != -1) {
      frog->allowed_positions -= ({ position });
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
int set_elected_option(string club_name,
                       string option,
                       mixed value) {
   class election_info data;
   data = query_elected_info(club_name);
   if (data) {
      data->options[option] = value;
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
int remove_elected_option(string club_name,
                          string option) {
   class election_info data;
   data = query_elected_info(club_name);
   if (data) {
      map_delete(data->options, option);
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
mixed query_elected_option(string club_name,
                           string option) {
   class election_info data;
   data = query_elected_info(club_name);
   if (data) {
      return data->options[option];
   }
   return 0;
}
int is_elected_option(string club_name,
                      string option) {
   class election_info data;
   data = query_elected_info(club_name);
   if (data) {
      return !undefinedp(data->options[option]);
   }
   return 0;
}
int start_election(string club_name) {
   string name;
   string pos;
   class election_info bing;
   string *stuff;
   name = normalise_name(club_name);
   if (is_elected_club(name)) {
      if (!_elections[name]) {
         bing = query_elected_info(name);
         _elections[name] = new(class election_data);
         _elections[name]->people = ([ ]);
         _elections[name]->nominated = ([ ]);
         _elections[name]->voted_for = ([ ]);
         _elections[name]->time_of_event = time() + CLUB_NOMINATION_TIME;
         _elections[name]->state = CLUB_NOMINATION;
         foreach (pos, stuff in bing->positions) {
            _elections[name]->people[pos] = ([ ]);
            _elections[name]->nominated[pos] = ([ ]);
            _elections[name]->voted_for[pos] = ({ });
         }
         save_main();
         send_broadcast_message(name,
                         "An election has just started!  Nominate your "
                         "favourite person now at the club control centre.");
         return 1;
      }
   }
   return 0;
}
int nominate_person(string club_name, string position, string person,
                    string nominating) {
   string name;
   name = normalise_name(club_name);
   if (is_elected_club(name)) {
      if (_elections[name] &&
          (_elections[name]->state == CLUB_NOMINATION ||
           _elections[name]->state == CLUB_NOMINATION_SECOND)) {
         position = query_position_name(club_name, position);
         if (_elections[name]->nominated[position]) {
            if (!_elections[name]->nominated[position][person]) {
                _elections[name]->nominated[position][person] = ({ });
            }
            if (member_array(nominating,
                        _elections[name]->nominated[position][person]) == -1) {
               _elections[name]->nominated[position][person] += ({ nominating });
               save_main();
               return 1;
            }
         }
      }
   }
   return 0;
}
mixed finish_nomination(string club_name) {
   string name;
   string position_name;
   mapping position_data;
   string *data;
   string person;
   string *bad_positions;
   class election_info frog;
   name = normalise_name(club_name);
   bad_positions = ({ });
   if (is_elected_club(name)) {
      frog = query_elected_info(name);
      if (_elections[name] &&
          (_elections[name]->state == CLUB_NOMINATION ||
           _elections[name]->state == CLUB_NOMINATION_SECOND)) {
         foreach (position_name,
                  position_data in _elections[name]->nominated) {
            _elections[name]->people[position_name] = ([ ]);
            foreach (person, data in position_data) {
               if (is_nomination_accepted(club_name, position_name, person)) {
                  _elections[name]->people[position_name][person] = 0;
               }
            }
            if (sizeof(_elections[name]->people[position_name]) == 0) {
               bad_positions += ({ position_name });
            }
         }
         if (!sizeof(bad_positions) ||
             _elections[name]->state == CLUB_NOMINATION_SECOND) {
            foreach (position_name, position_data in _elections[name]->people) {
               if (sizeof(position_data) == 1) {
                  set_position_holder(club_name,
                                      position_name,
                                      keys(position_data)[0]);
                  map_delete(_elections[name]->people, position_name);
               }
            }
            foreach (position_name in bad_positions) {
               set_position_holder(club_name,
                                   position_name,
                                   CLUB_UNKNOWN_MEMBER);
               map_delete(_elections[name]->people, position_name);
            }
            bad_positions = ({ });
            _elections[name]->state = CLUB_ELECTION;
            if (!sizeof(_elections[name]->people)) {
               save_main();
               complete_election(name);
            } else {
               _elections[name]->election_status = 0;
               _elections[name]->time_of_event = time() +
                                                CLUB_ELECTION_TIME;
               set_club_changed(name);
               save_main();
               send_broadcast_message(name,
                            "The nomination period has finished.  Vote "
                            "for your favourite person for each position now "
                            "at the club control centre.");
            }
         } else {
            _elections[name]->election_status = "No one has accepted "
                           "nominations for " +
                           query_multiple_short(bad_positions);
            save_main();
         }
         return bad_positions;
      }
   }
   return 0;
}
int vote_for_person(string club_name,
                    string position,
                    string person,
                    string voter) {
   string name;
   name = normalise_name(club_name);
   if (is_club(name)) {
      if (_elections[name] &&
          _elections[name]->state == CLUB_ELECTION) {
         position = query_position_name(club_name, position);
         if (_elections[name]->voted_for[position] &&
             member_array(voter,
                          _elections[name]->voted_for[position]) == -1) {
            if (!undefinedp(_elections[name]->people[position][person])) {
               _elections[name]->people[position][person]++;
               _elections[name]->voted_for[position] += ({ voter });
               save_main();
               return 1;
            }
         }
      }
   }
}
int complete_election(string club_name) {
   string name;
   string position;
   mapping people;
   string person_name;
   int count;
   int max_count;
   string *max_people;
   mapping elected_positions;
   int pos;
   class election_info frog;
   name = normalise_name(club_name);
   if (is_elected_club(name) &&
       _elections[name] &&
       _elections[name]->state = CLUB_ELECTION) {
      elected_positions = ([ ]);
      foreach (position, people in _elections[name]->people) {
         max_count = 0;
         max_people = ({ });
         if (sizeof(people) > 1) {
            foreach (person_name, count in people) {
               if (count > max_count) {
                  max_count = count;
                  max_people = ({ person_name });
               } else if (count == max_count) {
                  max_people += ({ person_name });
               }
            }
         } else {
            max_people = keys(people);
         }
         if (sizeof(max_people) == 0) {
           _elections[name]->election_status = "No one has voted for "
             "the position of " + position;
           return 0;
         }
         pos = random(sizeof(max_people));
         person_name = max_people[pos];
         elected_positions[position] = person_name;
      }
      frog = query_elected_info(name);
      foreach (position, person_name in elected_positions) {
         set_position_holder(club_name, position, person_name);
      }
      frog->last_election = time();
      set_club_changed(name);
      touch_club(name);
      map_delete(_elections, name);
      save_main();
      send_broadcast_message(name, "The election has finished!");
      return 1;
   }
   return 0;
}
int is_election_in_progress(string club) {
   string name;
   name = normalise_name(club);
   if (is_elected_club(name) &&
       _elections[name]) {
      return 1;
   }
}
int is_nomination_in_progress(string club) {
   string name;
   name = normalise_name(club);
   if (is_elected_club(name) &&
       _elections[name] &&
       (_elections[name]->state == CLUB_NOMINATION ||
        _elections[name]->state == CLUB_NOMINATION_SECOND)) {
      return 1;
   }
}
int is_voting_in_progress(string club) {
   string name;
   name = normalise_name(club);
   if (is_elected_club(name) &&
       _elections[name] &&
       _elections[name]->state == CLUB_ELECTION) {
      return 1;
   }
}
string *query_valid_positions(string club_name) {
   string name;
   class election_info frog;
   name = normalise_name(club_name);
   if (is_elected_club(name)) {
      frog = query_elected_info(club_name);
      return keys(frog->positions);
   }
   return ({ });
}
string *query_committee(string club_name) {
   string name;
   class election_info frog;
   name = normalise_name(club_name);
   if (is_elected_club(name)) {
      frog = query_elected_info(club_name);
      return values(frog->positions);
   }
   return ({ });
}
int is_valid_position(string club_name,
                      string position) {
   string *pos;
   pos = map(query_valid_positions(club_name), (: lower_case :));
   return (member_array(lower_case(position), pos) != -1);
}
int is_basic_position(string club_name,
                      string position) {
   class election_info frog;
   if (is_club(club_name) &&
       is_valid_position(club_name, position)) {
      frog = query_elected_info(club_name);
      position = query_position_name(club_name, position);
      return (position == frog->president) ||
             (position == frog->vice_president) ||
             (position == frog->secretary) ||
             (position == frog->treasurer);
   }
   return 0;
}
string query_position_name(string club_name,
                           string position) {
   string *pos;
   string *real_pos;
   int i;
   real_pos = query_valid_positions(club_name);
   pos = map(real_pos, (: lower_case :));
   i = member_array(lower_case(position), pos);
   if (i == -1) {
      return 0;
   }
   return real_pos[i];
}
string query_position_members(string club_name, string position) {
   class election_info frog;
   if (is_elected_club(club_name) &&
       is_valid_position(club_name, position)) {
      position = query_position_name(club_name, position);
      frog = query_elected_info(club_name);
      if (frog->positions[position]) {
         return frog->positions[position];
      }
   }
   return "not found";
}
int create_position_in_club(string name,
                            string position) {
   class election_info frog;
   if (is_elected_club(name) &&
       !is_voting_in_progress(name) &&
       !is_valid_position(name, position)) {
      frog = query_elected_info(name);
      frog->positions[position] = CLUB_UNKNOWN_MEMBER;
      set_club_changed(name);
      if (is_nomination_in_progress(name)) {
         name = normalise_name(name);
         _elections[name]->nominated[position] = ([ ]);
         _elections[name]->voted_for[position] = ({ });
         _elections[name]->people[position] = ([ ]);
         save_main();
      }
      return 1;
   }
   return 0;
}
int remove_position_in_club(string name,
                            string position) {
   class election_info frog;
   class account_info green;
   string account;
   if (is_elected_club(name) &&
       is_valid_position(name, position) &&
       !is_voting_in_progress(name) &&
       !is_basic_position(name, position)) {
      position = query_position_name(name, position);
      frog = query_elected_info(name);
      map_delete(frog->positions, position);
      set_club_changed(name);
      if (is_nomination_in_progress(name)) {
         name = normalise_name(name);
         map_delete(_elections[name]->nominated, position);
         map_delete(_elections[name]->voted_for, position);
         map_delete(_elections[name]->people, position);
         save_main();
      }
      foreach (account, green in frog->account_info) {
         green->allowed_positions -= ({ position });
      }
      send_observer_event("club_event_remove_position",
                          name,
                          position);
      return 1;
   }
   return 0;
}
int change_position_name_in_club(string name,
                                 string position,
                                 string new_position) {
   class election_info frog;
   class account_info green;
   string account;
   int pos;
   if (is_elected_club(name) &&
       !is_valid_position(name, new_position) &&
       !is_voting_in_progress(name) &&
       is_valid_position(name, position)) {
      position = query_position_name(name, position);
      frog = query_elected_info(name);
      frog->positions[new_position] = frog->positions[position];
      map_delete(frog->positions, position);
      if (frog->president == position) {
         frog->president = new_position;
      } else if (frog->vice_president == position) {
         frog->vice_president = new_position;
      } else if (frog->secretary == position) {
         frog->secretary = new_position;
      } else if (frog->treasurer == position) {
         frog->treasurer = new_position;
      }
      set_club_changed(name);
      name = normalise_name(name);
      if (is_nomination_in_progress(name)) {
         _elections[name]->nominated[new_position] =
                                         _elections[name]->nominated[position];
         map_delete(_elections[name]->nominated, position);
         _elections[name]->voted_for[new_position] =
                                         _elections[name]->voted_for[position];
         map_delete(_elections[name]->voted_for, position);
         _elections[name]->people[new_position] =
                                         _elections[name]->people[position];
         map_delete(_elections[name]->people, position);
         save_main();
      }
      foreach (account, green in frog->account_info) {
         pos = member_array(position, green->allowed_positions);
         if (pos != -1) {
            green->allowed_positions[pos] = new_position;
         }
      }
      send_observer_event("club_event_change_position_name",
                          name,
                          position,
                          new_position);
      return 1;
   }
   return 0;
}
int set_position_holder(string club_name,
                                  string position,
                                  string person) {
   class election_info info;
   info = query_elected_info(club_name);
   if (info) {
      if (is_valid_position(club_name, position)) {
         if (is_member_of(club_name, person) ||
             person == CLUB_UNKNOWN_MEMBER) {
            position = query_position_name(club_name, position);
            info->positions[position] = person;
            set_club_changed(club_name);
            send_observer_event("club_event_position_holder",
                                club_name,
                                position,
                                person);
            return 1;
         }
      }
   }
   return 0;
}
int has_person_voted(string club_name,
                    string position,
                    string person) {
   string name;
   name = normalise_name(club_name);
   if (is_valid_position(club_name, position)) {
      if (_elections[name]) {
         position = query_position_name(club_name, position);
         if (_elections[name]->voted_for[position]) {
            return (member_array(person,
                              _elections[name]->voted_for[position]) != -1);
         } else {
            return 1;
         }
      }
   }
   return 0;
}
int has_nominated_person(string club_name,
                         string position,
                         string nominated,
                         string by) {
   string name;
   name = normalise_name(club_name);
   if (is_valid_position(club_name, position)) {
      position = query_position_name(club_name, position);
      if (_elections[name] &&
          _elections[name]->nominated[position][nominated]) {
         return (member_array(by,
                      _elections[name]->nominated[position][nominated]) != -1);
      }
   }
}
string *query_nominated_for(string club_name,
                            string position) {
   string name;
   name = normalise_name(club_name);
   if (is_valid_position(club_name, position)) {
      if (_elections[name]) {
         position = query_position_name(club_name, position);
         if (is_voting_in_progress(club_name)) {
            if (_elections[name]->people[position]) {
               return keys(_elections[name]->people[position]);
            }
            return ({ });
         } else if (is_nomination_in_progress(club_name)) {
            return keys(_elections[name]->nominated[position]);
         }
      }
   }
   return ({ });
}
string *query_nominators_for(string club_name,
                             string position,
                             string nominated) {
   string name;
   name = normalise_name(club_name);
   if (is_valid_position(club_name, position)) {
      if (_elections[name]) {
         position = query_position_name(club_name, position);
         if (is_nomination_in_progress(club_name) &&
            _elections[name]->nominated[position][nominated]) {
            return _elections[name]->nominated[position][nominated];
         }
      }
   }
   return ({ });
}
int is_nominated_for(string club_name,
                     string position,
                     string person) {
   if (is_valid_position(club_name, position)) {
      return member_array(person,
                          query_nominated_for(club_name, position)) != -1;
   }
}
int is_nomination_accepted(string club_name,
                           string position,
                           string person) {
   string *nom;
   if (is_nominated_for(club_name, position, person)) {
      nom = query_nominators_for(club_name, position, person);
      if (sizeof(nom) > 1 &&
          member_array(person, nom) != -1) {
         return 1;
      }
   }
   return 0;
}
int query_next_event_time(string club_name) {
   if (is_club(club_name)) {
      club_name = normalise_name(club_name);
      if (_elections[club_name]) {
         return _elections[club_name]->time_of_event;
      }
   }
}
string query_election_status(string club_name) {
   if (is_elected_club(club_name)) {
      if (is_election_in_progress(club_name)) {
         club_name = normalise_name(club_name);
         return _elections[club_name]->election_status;
      }
   }
}
string query_announcement(string club_name) {
   class election_info bing;
   bing = query_elected_info(club_name);
   if (bing) {
      return bing->announcement;
   }
   return "";
}
int query_announcement_time(string club_name) {
   class election_info bing;
   bing = query_elected_info(club_name);
   if (bing) {
      return bing->announce_time;
   }
   return 0;
}
int set_announcement(string club_name,
                     string announce) {
   class election_info bing;
   bing = query_elected_info(club_name);
   if (bing) {
      if (bing->announce_time &&
          strlen(bing->announcement)) {
         add_archive(club_name,
                     "Announcement",
                     "Announcement on " + ctime(time()) + ":\n\n" +
                     bing->announcement);
      }
      bing->announce_time = time();
      bing->announcement = announce;
      set_club_changed(club_name);
      send_broadcast_message(club_name, "A new announcement has been added.");
      return 1;
   }
   return 0;
}
private class club_archive* convert_archives(mixed *archives) {
   string archive;
   class club_archive bing;
   int i;
   for (i = 0; i < sizeof(archives); i++) {
      archive = archives[i];
      if (stringp(archive)) {
         bing = new(class club_archive);
         bing->archive_date = time();
         bing->subject = "unknown";
         bing->matter = archive;
         archives[i] = bing;
      }
   }
   return archives;
}
protected int add_archive(string club_name,
                          string subject,
                          string thingy) {
   class election_info data;
   class club_archive fluff;
   data = query_elected_info(club_name);
   if (data) {
      fluff = new(class club_archive);
      fluff->subject = subject;
      fluff->matter = thingy;
      fluff->archive_date = time();
      data->archives += ({ fluff });
      if (sizeof(data->archives) > CLUB_MAX_ARCHIVE_SIZE) {
         data->archives = data->archives[<CLUB_MAX_ARCHIVE_SIZE..];
      }
      if (stringp(data->archives[0])) {
         data->archives = convert_archives(data->archives);
      }
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
class club_archive *query_archives(string club_name) {
   class election_info data;
   data = query_elected_info(club_name);
   if (data) {
      if (sizeof(data->archives) &&
          stringp(data->archives[0])) {
         data->archives = convert_archives(data->archives);
         set_club_changed(club_name);
      }
      return data->archives;
   }
   return ({ });
}
string *query_boards() {
   return _boards;
}
int query_club_board(string club_name) {
   string name;
   name = query_club_board_name(club_name);
   return member_array(name, _boards) != -1;
}
string query_club_board_name(string club_name) {
   return CLUB_BOARD_PREFIX + normalise_name(club_name);
}
int create_club_board(string club_name) {
   string name;
   name = query_club_board_name(club_name);
   if(is_elected_club(club_name) || this_player()->query_director()) {
      if (BOARD_HAND->is_board(name)) {
         return 0;
      }
      BOARD_HAND->create_board(name,
                               B_PRIV_ACCESS_RESTRICTED_METHOD |
                               B_PRIV_NO_INFORM,
                               "frog");
      BOARD_HAND->set_method_access_call(name,
                                         "check_board_post",
                                         CLUB_HANDLER);
      BOARD_HAND->set_timeout(10);
      BOARD_HAND->set_maximum(60);
      BOARD_HAND->set_minimum(10);
      _boards += ({ name });
      save_main();
      return 1;
   }
   return 0;
}
int remove_club_board(string club_name) {
   string name;
   if (query_club_board(club_name)) {
      name = query_club_board_name(club_name);
      BOARD_HAND->delete_board(name);
      _boards -= ({ name });
      save_main();
      return 1;
   }
}
int check_board_post(int type,
                     string board,
                     string previous,
                     string name,
                     int num) {
   string club;
   club = board[strlen(CLUB_BOARD_PREFIX)..];
   switch (type) {
   case B_ACCESS_READ :
      return is_member_of(club, name);
   case B_ACCESS_WRITE :
      return is_member_of(club, name);
   case B_ACCESS_DELETE :
      return holds_any_position_of(club, name);
   case B_ACCESS_INFORM :
      if (!num) {
         send_broadcast_message(club,
                                name + " posts a message to the board.");
      } else {
         send_broadcast_message(club,
                                name + " posts a message to the board and " +
                                num + " message" +
                                (num > 1?"s":"") + " explode in sympathy.");
      }
      return 1;
   }
}
protected void do_mail_committee(string club_name,
                            string subject,
                            string body) {
   string *committee;
   body += "\n\nYours,\nFindlewoodlwinks\n(Club Handler)\n";
   committee = query_committee(club_name) - ({ CLUB_UNKNOWN_MEMBER });
   if (!sizeof(committee)) {
      if (PLAYER_HANDLER->test_user(query_founder(club_name))) {
         committee = ({ query_founder(club_name) });
      } else {
         return ;
      }
   }
   MAILER->do_mail_message(implode(committee, ","),
                           "Patricians office",
                           subject,
                           "",
                           body);
}
protected void check_elected_information(string name,
                                         string member,
                                         int startup) {
   class election_info data;
   string position_name;
   string person;
   mapping gruff;
   string *nom;
   int cre_club;
   int votes;
   name = normalise_name(name);
   data = query_elected_info(name);
   if (data) {
      if (!mapp(data->options)) {
         data->options = ([ ]);
         set_club_changed(name);
      }
      foreach (position_name, person in data->positions) {
         if (person != CLUB_UNKNOWN_MEMBER &&
             (!is_member_of(name, person) ||
              !PLAYER_HANDLER->test_active(person) ||
              member == person)) {
            set_position_holder(name, position_name, CLUB_UNKNOWN_MEMBER);
         }
      }
      if (query_next_election(name) < time() ||
          _elections[name]) {
         if (!_elections[name]) {
            start_election(name);
         } else {
            switch (_elections[name]->state) {
               case CLUB_NOMINATION_SECOND :
               case CLUB_NOMINATION :
                  if (_elections[name]->time_of_event < time()) {
                     if (sizeof(finish_nomination(name))) {
                        _elections[name]->time_of_event = time() +
                                                          CLUB_ELECTION_TIME;
                        _elections[name]->state = CLUB_NOMINATION_SECOND;
                        save_main();
                     }
                  }
                  break;
               case CLUB_ELECTION :
                  if (_elections[name]->time_of_event < time()) {
                     complete_election(name);
                  }
                  break;
            }
         }
      }
      if (_elections[name] &&
          startup) {
         cre_club = is_creator_club(name);
         foreach (position_name, gruff in _elections[name]->people) {
            foreach (person, votes in gruff) {
               if ((!cre_club &&
                    PLAYER_HANDLER->test_creator(person)) ||
                   !is_member_of(name, person) ||
                   !PLAYER_HANDLER->test_user(person)) {
                  map_delete(gruff, person);
               }
            }
         }
         foreach (position_name,
                  gruff in _elections[name]->nominated) {
            foreach (person, nom in gruff) {
               if ((!cre_club &&
                    PLAYER_HANDLER->test_creator(person)) ||
                   !is_member_of(name, person) ||
                   !PLAYER_HANDLER->test_user(person)) {
                  map_delete(gruff, person);
               }
            }
         }
      }
   }
}