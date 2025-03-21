inherit "/obj/handlers/inherit/citizens";
#include <player_handler.h>
#include <player.h>
#include <board.h>
#define NOMIC_SYSTEM_NO_CLASSES
#include <nomic_system.h>
#define CITIZEN_ELECTION_PHASE_NONE       0
#define CITIZEN_ELECTION_PHASE_NOMINATION 1
#define CITIZEN_ELECTION_PHASE_ELECTION   2
#define CITIZEN_ELECTION_PHASE_GRACE      3
#define CITIZEN_ELECTION_PHASE_DISABLED 4
#define CITIZEN_ELECTION_TIME   (20 * (7 * 24 * 60 * 60))
#define CITIZEN_ELECTION_PHASE_TIME      (10 * 24 * 60 * 60)
#define CITIZEN_PHASE_TIME      (14 * 24 * 60 * 60)
#define CITIZEN_GRACE_TIME      (14 * 24 * 60 * 60)
#define CITIZEN_ELECTION_DISABLED_TIME (14 * 24 * 60 * 60)
class election_data {
   int last_election;
   int phase;
   int phase_start;
   mapping nominations;
   mapping votes;
   string* voted;
}
protected void finish_election_phase(string area);
int post_citizen_message(string area, string subject, string message);
private mapping _elections;
private mapping _boards;
void create() {
   _elections = ([ ]);
   _boards = ([ ]);
   citizens::create();
   call_out("do_next_event", 10);
}
void create_area(string area) {
   _elections[area] = new(class election_data);
   _elections[area]->phase = CITIZEN_ELECTION_PHASE_GRACE;
   _elections[area]->phase_start = time();
   _elections[area]->nominations = ([ ]);
   _elections[area]->votes = ([ ]);
   _elections[area]->voted = ({ });
   ::create_area(area);
}
int query_next_election_time(string area) {
   if (!_elections[area]) {
      return 0;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_GRACE) {
      return _elections[area]->phase_start + CITIZEN_GRACE_TIME;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_NONE) {
      return _elections[area]->last_election + CITIZEN_ELECTION_TIME;
   }
   return 0;
}
int query_end_of_phase_time(string area) {
   if (!_elections[area]) {
      return 0;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_NONE) {
      return 0;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_ELECTION) {
      return _elections[area]->phase_start + CITIZEN_ELECTION_PHASE_TIME;
   }
   return _elections[area]->phase_start + CITIZEN_PHASE_TIME;
}
protected int query_election_phase(string area) {
   if (!_elections[area]) {
      return CITIZEN_ELECTION_PHASE_NONE;
   }
   return _elections[area]->phase;
}
int is_nomination_phase(string area) {
   return query_election_phase(area) == CITIZEN_ELECTION_PHASE_NOMINATION;
}
int is_election_phase(string area) {
   return query_election_phase(area) == CITIZEN_ELECTION_PHASE_ELECTION;
}
int is_grace_phase(string area) {
   return query_election_phase(area) == CITIZEN_ELECTION_PHASE_GRACE;
}
int nominate_magistrate(string area, string person, string nominator) {
   if (!_elections[area] ||
       !is_citizen_of(area, person) ||
       !is_citizen_of(area, nominator)) {
      return 0;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_NOMINATION) {
      if (!_elections[area]->nominations[person]) {
         _elections[area]->nominations[person] = ({ });
      } else if (member_array(nominator,
                              _elections[area]->nominations[person]) != -1) {
         return 0;
      }
      _elections[area]->nominations[person] += ({ nominator });
      save_me();
      return 1;
   }
   return 0;
}
string* query_nominated_by(string area, string person) {
   if (!_elections[area]) {
      return ({ });
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_NOMINATION) {
      if (_elections[area]->nominations[person]) {
         return copy(_elections[area]->nominations[person]);
      }
   }
   return ({ });
}
string* query_people_nominated(string area) {
   if (!_elections[area]) {
      return ({ });
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_NOMINATION) {
      return keys(_elections[area]->nominations);
   }
   return ({ });
}
int is_nomination_accepted(string area, string person) {
   string* nominations;
   nominations = query_nominated_by(area, person);
   if (sizeof(nominations) >= 2 &&
       member_array(person, nominations) != -1) {
      return 1;
   }
   return 0;
}
int has_voted(string area, string person) {
   if (!_elections[area]) {
      return 0;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_ELECTION) {
      return member_array(person, _elections[area]->voted) != -1;
   }
   return 0;
}
int is_eligible_to_vote_for(string area, string person) {
   if (!_elections[area]) {
      return 0;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_ELECTION) {
      return member_array(person, keys(_elections[area]->votes)) != -1;
   }
   return 0;
}
int vote_for_people(string area, string* people, string voter) {
   string person;
   if (!_elections[area] ||
       !is_citizen_of(area, voter)) {
      return 0;
   }
   foreach (person in people) {
      if (!is_citizen_of(area, person)) {
         return 0;
      }
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_ELECTION) {
      if (has_voted(area, voter)) {
         return 0;
      }
      foreach (person in people) {
         if (is_eligible_to_vote_for(area, person)) {
            _elections[area]->votes[person]++;
         }
      }
      _elections[area]->voted += ({ voter });
      save_me();
      return 1;
   }
   return 0;
}
string* query_can_vote_for(string area) {
   if (!_elections[area]) {
      return ({ });
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_ELECTION) {
      return keys(_elections[area]->votes);
   }
   return ({ });
}
protected void start_election(string area) {
   if (!_elections[area]) {
      return ;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_NONE ||
       _elections[area]->phase == CITIZEN_ELECTION_PHASE_GRACE) {
      _elections[area]->votes = ([ ]);
      _elections[area]->voted = ({ });
      _elections[area]->nominations = ([ ]);
      _elections[area]->phase_start = time();
      _elections[area]->phase = CITIZEN_ELECTION_PHASE_NOMINATION;
      save_me();
      post_citizen_message(area, "Nomination phase has started.",
                           "Please go to your council offices and "
                           "nominate\nthe magistrates for office.\n");
   }
}
protected void finish_nomination_phase(string area) {
   string person;
   string* nominators;
   if (!_elections[area]) {
      return ;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_NOMINATION) {
      _elections[area]->votes = ([ ]);
      _elections[area]->voted = ({ });
      foreach (person, nominators in _elections[area]->nominations) {
         if (is_citizen_of(area, person) &&
             is_nomination_accepted(area, person) &&
             !PLAYER_HANDLER->test_creator(person)) {
            _elections[area]->votes[person] = 0;
         }
      }
      _elections[area]->phase = CITIZEN_ELECTION_PHASE_ELECTION;
      _elections[area]->phase_start = time();
      _elections[area]->nominations = ([ ]);
      save_me();
      post_citizen_message(area, "Nomination phase finished.",
                           "The people nominated for election are:\n" +
                           implode(map(keys(_elections[area]->votes),
                                       (: "   " + $1 :)), "\n"));
      if (sizeof(keys(_elections[area]->votes)) <=
          query_number_of_magistrates(area)) {
          finish_election_phase(area);
      }
   }
}
protected void finish_election_phase(string area) {
   string* voted;
   string* sorted_voted;
   string high_pk;
   string high_non_pk;
   string person;
   string results;
   int needed;
   int num;
   if (!_elections[area]) {
      return ;
   }
   if (_elections[area]->phase == CITIZEN_ELECTION_PHASE_ELECTION) {
      if (sizeof(keys(_elections[area]->votes)) <=
          query_number_of_magistrates(area)) {
         voted = sort_array(keys(_elections[area]->votes),
                            (: $3[$2] - $3[$1] :), _elections[area]->votes);
         sorted_voted = voted;
      } else {
         voted = sort_array(keys(_elections[area]->votes),
                            (: $3[$2] - $3[$1] :), _elections[area]->votes);
         sorted_voted = voted;
         needed = query_number_of_magistrates(area);
         foreach (person in voted) {
            if (PLAYER_HANDLER->test_player_killer(person)) {
               if (!high_pk) {
                  needed--;
                  high_pk = person;
               }
            } else {
               if (!high_non_pk) {
                  needed--;
                  high_non_pk = person;
               }
            }
            if (high_pk && high_non_pk) {
               break;
            }
         }
         voted -= ({ high_pk, high_non_pk });
         voted = voted[0..needed - 1];
         voted += ({ high_pk, high_non_pk });
         voted -= ({ 0 });
      }
      results = "Votes:\n";
      foreach (person in sorted_voted) {
         results += sprintf("%20s %d\n", capitalize(person),
                            _elections[area]->votes[person]);
      }
      results += "\nElected officals are " + query_multiple_short(voted) + "\n";
      results += "\nNumber of people who voted " +
                 sizeof(_elections[area]->voted);
      num = query_number_of_citizens(area);
      if (num == 0) {
         results += " (100% of the citizens)\n";
      } else {
         results += " (" + (sizeof(_elections[area]->voted) * 100 / num) +
                    "% of the citizens)\n";
      }
      _elections[area]->votes = ([ ]);
      _elections[area]->voted = ({ });
      _elections[area]->phase = CITIZEN_ELECTION_PHASE_NONE;
      _elections[area]->phase_start = time();
      _elections[area]->last_election = time();
      _elections[area]->nominations = ([ ]);
      post_citizen_message(area, "Election results", results);
      setup_magistrates(area, voted);
      save_me();
   }
}
protected void do_next_event() {
   int next_event;
   int time_to_next_event;
   string area;
   class election_data data;
   foreach (area, data in _elections) {
      switch (data->phase) {
      case CITIZEN_ELECTION_PHASE_NONE :
         next_event = (data->last_election - time()) + CITIZEN_ELECTION_TIME;
         if (next_event <= 0) {
            start_election(area);
         }
         break;
      case CITIZEN_ELECTION_PHASE_NOMINATION :
         next_event = (data->phase_start - time()) + CITIZEN_PHASE_TIME;
         if (next_event <= 0) {
            finish_nomination_phase(area);
         }
         break;
      case CITIZEN_ELECTION_PHASE_ELECTION :
         next_event = (data->phase_start - time()) + CITIZEN_ELECTION_PHASE_TIME;
         if (next_event <= 0) {
            finish_election_phase(area);
         }
         break;
      case CITIZEN_ELECTION_PHASE_GRACE :
         next_event = (data->phase_start - time()) + CITIZEN_GRACE_TIME;
         if (next_event <= 0) {
            start_election(area);
         }
         break;
      case CITIZEN_ELECTION_PHASE_DISABLED :
         next_event = (data->phase_start - time()) +
            CITIZEN_ELECTION_DISABLED_TIME;
         if (next_event <= 0) {
             next_event = next_event;
         }
         break;
      }
      if (next_event > 0 &&
          (next_event < time_to_next_event || !time_to_next_event)) {
         time_to_next_event = next_event;
      }
   }
   if(time_to_next_event) {
     call_out("do_next_event", time_to_next_event);
   }
}
void set_citizen_board(string area, string name) {
   if (!pointerp(_boards[area])) {
      _boards[area] = ({ 0, 0 });
   }
   _boards[area][0] = name;
   save_me();
}
string query_magistrate_board(string area) {
   if (pointerp(_boards[area])) {
      return _boards[area][1];
   }
   return 0;
}
void set_magistrate_board(string area, string name) {
   if (!pointerp(_boards[area])) {
      _boards[area] = ({ 0, 0 });
   }
   _boards[area][1] = name;
   save_me();
}
string query_citizen_board(string area) {
   if (pointerp(_boards[area])) {
      return _boards[area][0];
   }
   return 0;
}
int post_citizen_message(string area, string subject, string message) {
   string board;
   board = query_citizen_board(area);
   if (board) {
      return BOARD_HAND->add_message(board,
                           NOMIC_SYSTEM_ADMINISTRATOR_NAME,
                           subject,
                           message);
   }
   return 0;
}
int post_magistrate_message(string area, string subject, string message) {
   string board;
   board = query_magistrate_board(area);
   if (board) {
      return BOARD_HAND->add_message(board,
                           NOMIC_SYSTEM_ADMINISTRATOR_NAME,
                           subject,
                           message);
   }
   return 0;
}
int disable_citizen_election(string area) {
    if (!_elections[area]) {
      return 0;
    }
   _elections[area]->phase = CITIZEN_ELECTION_PHASE_DISABLED;
   _elections[area]->phase_start = time();
   _elections[area]->nominations = ([ ]);
   _elections[area]->votes = ([ ]);
   _elections[area]->voted = ({ });
   save_me();
   return 1;
}