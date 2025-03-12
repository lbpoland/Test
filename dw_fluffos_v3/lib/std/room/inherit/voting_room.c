#include <board.h>
#define DEFAULT_VOTE_DURATION (2600*24*7)
class vote {
  string type;
  string desc;
  string *choices;
  mixed *votes;
  int ending;
  string *voted;
}
class election {
  mixed *candidates;
  int closes;
}
private int vote_counter;
private mapping votes;
private mapping elections;
private nosave string _vote_file;
private nosave mixed _vote_cond;
private nosave mixed _comp_action;
private nosave int _vote_duration;
private nosave int _open_voting;
private nosave int _no_elections;
private nosave string _proxy;
private nosave mixed _stand_cond;
private nosave mixed _second_cond;
private nosave mixed _election_announcement;
int list_votes();
int cast_vote( string words, int num );
int stand_for_election(string position);
int second_candidate(string who, string position);
int list_elections();
int do_create_vote(string choices);
void create() {
  seteuid("Room");
  votes = ([ ]);
  elections = ([ ]);
}
void init() {
   add_command("vote", "<string> on <number>", (: cast_vote($4[0], $4[1]) :) );
   add_command("list", "votes", (: list_votes :));
   add_command("votes", "", (: list_votes :));
   if (!_no_elections) {
      add_command( "stand", "[for] <string>", (: stand_for_election($4[0]) :));
      add_command( "second", "<string> [for] <string>",
                   (: second_candidate($4[0], $4[1]) :) );
      add_command("list", "elections", (: list_elections :));
      add_command("elections", "", (: list_elections :));
   }
}
protected mapping query_our_votes() {
   if (_proxy) {
      return _proxy->query_votes();
   }
   if (votes) {
      return votes;
   }
   return ([ ]);
}
protected void add_our_vote(int id, class vote data) {
   if (!votes) {
      votes = ([ ]);
   }
   votes[id] = data;
}
protected mapping query_our_elections() {
   if (_proxy) {
      return _proxy->query_elections();
   }
   if (elections) {
      return elections;
   }
   return ([ ]);
}
protected void add_our_election(string name, class election data) {
   if (!elections) {
      elections = ([ ]);
   }
   elections[name] = data;
}
void init_add_vote() {
   add_command( "add", "vote with <string'choices'>",
               (: do_create_vote($4[0]) :));
}
void setup_after_load() {
  int i;
  string election;
  int *vote_ids;
  if (_proxy) {
    return ;
  }
  vote_ids = m_indices( query_our_votes() );
  for ( i = 0; i < sizeof( vote_ids ); i++ ) {
    if ( query_our_votes()[ vote_ids[ i ] ]->ending < time() ) {
      call_out( "end_vote", 10 * ( i + 1 ), vote_ids[ i ] );
    } else {
      call_out( "end_vote", query_our_votes()[ vote_ids[ i ] ]->ending - time(),
                vote_ids[ i ] );
    }
  }
  foreach(election in keys(query_our_elections())) {
    if(query_our_elections()[election]->closes < time()) {
      call_out( "start_election_vote", 30 * random(5), election);
    } else {
      call_out( "start_election_vote", query_our_elections()[election]->closes - time(),
                election);
    }
  }
}
void set_save_file(string file) {
  _vote_file = file;
  if( file_size( _vote_file + ".o" ) > 0 ) {
    unguarded( (: restore_object, _vote_file :) );
    setup_after_load();
  } else {
    elections = ([ ]);
    votes = ([ ]);
  }
}
string query_save_file() { return _vote_file; }
protected void save_room() {
   if (_vote_file) {
      unguarded( (: save_object, _vote_file :) );
   }
}
void set_proxy(string proxy) {
   _proxy = proxy;
}
void set_no_elections(int no_elections) {
   _no_elections = no_elections;
}
void set_open_voting(int open) {
   _open_voting = open;
}
int query_open_voting(int open) {
   return _open_voting;
}
void set_vote_conditions(mixed cond) { _vote_cond = cond; }
void set_completion_action(mixed cond) { _comp_action = cond; }
void set_vote_duration(int duration) { _vote_duration = duration; }
int query_vote_duration() {
   if (!_vote_duration) {
      return DEFAULT_VOTE_DURATION;
   }
   return _vote_duration;
}
void set_stand_conditions(mixed cond) { _stand_cond = cond; }
void set_second_conditions(mixed cond) { _second_cond = cond; }
void set_election_announcement(string board, string person, string subject,
                               string prefix, string suffix) {
  _election_announcement = ({ board, person, subject, prefix, suffix });
}
int cast_vote( string which_str, int vote_id ) {
  string pname;
  int which, ok;
  class vote this_vote;
  if (_proxy) {
     return _proxy->cast_vote(which_str, vote_id);
  }
  if ( undefinedp(query_our_votes()[vote_id])) {
    add_failed_mess("There is no vote " + vote_id + ".\n");
    return 0;
  }
  this_vote = query_our_votes()[vote_id];
  which = member_array(which_str, this_vote->choices);
  if (which == -1) {
    if(strlen(which_str) > 1) {
      add_failed_mess("There is no choice " + which_str + " for vote id " +
           vote_id + ".\n");
      return 0;
    }
     which = upper_case( which_str )[ 0 ] - 65;
  }
  if(which < 0 || which > sizeof(this_vote->choices) -1) {
    add_failed_mess("There is no choice " + which_str + " for vote id " +
                           vote_id + ".\n");
    return 0;
  }
  ok = 1;
  if (functionp(_vote_cond)) {
    ok = evaluate(_vote_cond, this_player(), this_vote->desc);
  }
  if(arrayp(_vote_cond)) {
    ok = call_other(_vote_cond[0], _vote_cond[1], this_player(), this_vote->desc);
  }
  if(!intp(ok)) {
    ok = 0;
  }
  if(!ok) {
    add_failed_mess("Sorry, but you are not allowed to vote on this "
                       "subject.\n");
    return 0;
  }
  pname = this_player()->query_name();
  if(member_array(pname, this_vote->voted) != -1) {
    add_succeeded_mess(({"You have already voted on this subject.\n", ""}));
    return 1;
  }
  this_vote->voted += ({ pname });
  if (_open_voting) {
     this_vote->votes[which] += ({ pname });
  } else {
     if (arrayp(this_vote->votes[which])) {
        this_vote->votes[which] = sizeof(this_vote->votes[which]);
     }
     this_vote->votes[which]++;
  }
  save_room();
  add_succeeded_mess(({ "You cast your vote for "+which_str + " on " +
                        vote_id+".\n",
                        "$N casts a vote.\n" }));
  return 1;
}
int list_votes() {
  int i, j, *vote_ids;
  string text;
  class vote this_vote;
  if ( !m_sizeof( query_our_votes() ) ) {
    write( "There are no votes in progress.\n" );
    return 1;
  }
  vote_ids = m_indices( query_our_votes() );
  if ( sizeof( vote_ids ) > 1 )
    write( "The following votes are in progress:\n" );
  else
    write( "The following vote is in progress:\n" );
  text = "";
  for ( i = 0; i < sizeof( vote_ids ); i++ ) {
    this_vote = query_our_votes()[vote_ids[i]];
    text += "  "+ vote_ids[i] + ". " + this_vote->desc +"\n Choices are :\n";
    for(j=0; j<sizeof(this_vote->choices); j++) {
      text += sprintf("    %c. %s\n", 'A'+j, this_vote->choices[j]);
    }
    text += " Voting closes at "+ ctime( this_vote->ending ) +".\n\n";
  }
  this_player()->more_string(sprintf( "%-=*s",
                                      (int)this_player()->query_cols(),
                                      text ));
  return 1;
}
void add_vote(string type, string description, string *choices, int ending) {
  class vote new_vote;
  if (_proxy) {
     return _proxy->add_vote(type, description, choices, ending);
  }
  vote_counter++;
  new_vote = new(class vote);
  new_vote->type = type;
  new_vote->desc = description;
  new_vote->choices = choices;
  if (_open_voting) {
    new_vote->votes = allocate(sizeof(choices), (: ({ }) :));
  } else {
    new_vote->votes = allocate(sizeof(choices));
  }
  if(ending) {
    new_vote->ending = ending;
  } else if(_vote_duration) {
    new_vote->ending = (_vote_duration + time());
  } else {
    new_vote->ending = (DEFAULT_VOTE_DURATION + time());
  }
  new_vote->voted = ({ });
  add_our_vote(vote_counter, new_vote);
  call_out( "end_vote", new_vote->ending - time(), vote_counter );
  save_room();
}
mapping query_votes() { return query_our_votes() + ([ ]); }
mapping query_elections() { return query_our_elections() + ([ ]); }
void end_vote( int which ) {
  if ( !query_our_votes()[ which ] ) {
      return;
  }
  if(functionp(_comp_action)) {
      evaluate(_comp_action, query_our_votes()[which]->type, query_our_votes()[which]->desc,
               query_our_votes()[which]->choices, query_our_votes()[which]->votes,
               query_our_votes()[which]->voted);
  } else if(arrayp(_comp_action)) {
    call_other(_comp_action[0], _comp_action[1], query_our_votes()[which]->type,
               query_our_votes()[which]->desc, query_our_votes()[which]->choices, query_our_votes()[which]->votes,
               query_our_votes()[which]->voted);
  }
  map_delete(query_our_votes(), which);
  save_room();
}
void make_announcement(string board, string name, string subject,
                       string message ) {
  BOARD_HAND->add_message(board, name, subject,
                          sprintf( "%-=*s", 64, message));
}
void initiate_election(string position) {
  class election tmp;
  if (_proxy) {
     return _proxy->initiate_election(position);
  }
  if(query_our_elections()[position])
    return;
  tmp = new(class election);
  tmp->candidates = ({});
  if(_vote_duration) {
    tmp->closes = time() + _vote_duration;
  } else {
    tmp->closes = time() + DEFAULT_VOTE_DURATION;
  }
  add_our_election(position, tmp);
  call_out("start_election_vote", tmp->closes + 60, position);
  save_room();
}
int query_election_in_progress(string position) {
   if (classp(query_our_elections()[position])) {
       return 1;
   }
   return 0;
}
int stand_for_election(string position) {
  int ok, i;
  if (_proxy) {
     return _proxy->stand_for_election(position);
  }
  ok = 1;
  if(functionp(_stand_cond)) {
    ok = evaluate(_stand_cond, this_player(), position);
  } else if(arrayp(_stand_cond)) {
    ok = call_other(_stand_cond[0], _stand_cond[1], this_player(), position);
  }
  if(!intp(ok))
    ok = 0;
  if(!ok) {
    add_succeeded_mess(({ "Sorry, but you are not allowed to stand for this "
                            "election.\n", ""}));
    return 1;
  }
  if(!query_our_elections()[position]) {
    add_succeeded_mess(({"There is no election in progress for the post of " +
                    position + ".\n", ""}));
    return 1;
  }
  for(i=0; i<sizeof(query_our_elections()[position]->candidates); i++) {
    if(query_our_elections()[position]->candidates[i][0] == this_player()->query_name()) {
      add_succeeded_mess(({"You are already standing in this "
                             "election.\n", ""}));
      return 1;
    }
  }
  query_our_elections()[position]->candidates += ({({ this_player()->query_name(), "" })});
  save_room();
  add_succeeded_mess(({"You have been added to the list of candidates for "
                         "the position of " + position + ".  You must now "
                         "find someone to second your candidacy.\n",
                         "$N stands for election.\n"}));
  return 1;
}
int second_candidate(string who, string position) {
  mixed *candidates;
  int i, found, ok;
  if (_proxy) {
     return _proxy->second_candidate(who, position);
  }
  ok = 1;
  if(functionp(_second_cond)) {
    ok = evaluate(_second_cond, this_player(), position);
  } else if(arrayp(_second_cond)) {
    ok = call_other(_second_cond[0], _second_cond[1], this_player(), position);
  }
  if(!intp(ok))
    ok = 0;
  if(!ok) {
    add_succeeded_mess(({"Sorry, but you are not allowed to second candidates "
                           "in this election.\n", ""}));
    return 1;
  }
  if(!query_our_elections()[position]) {
    add_succeeded_mess(({"There is no election in progress for " + position +
                           ".\n", ""}));
    return 1;
  }
  candidates = (query_our_elections()[position])->candidates;
  for(i=0; i< sizeof(candidates); i++) {
    if(candidates[i][0] == who)
      found = i+1;
  }
  if(!found) {
    add_succeeded_mess(({who + " is not standing for the position of " +
                           position + ".\n", ""}));
    return 1;
  }
  if(this_player()->query_name() == who) {
    add_succeeded_mess(({"You cannot second yourself.\n", ""}));
    return 1;
  }
  if(candidates[found-1][1] != "") {
    add_succeeded_mess(({candidates[found-1][0] +
                           " has already been seconded by " +
                           candidates[found-1][1] + ".\n", ""}));
    return 1;
  }
  candidates[found-1][1] = this_player()->query_name();
  save_room();
  add_succeeded_mess(({candidates[found-1][0] +
                         " has been seconded in the election for "+
                         position+".\n", ""}));
  return 1;
}
void start_election_vote(string post) {
  string str, *choices;
  int i;
  if(!query_our_elections()[post])
    return;
  if(_election_announcement[3])
    str = _election_announcement[3];
  else
    str = "All eligible persons are requested to vote for the position of ";
  str += post + "\n\nThe candidates are:\n";
  choices = ({ });
  for(i=0; i<sizeof(query_our_elections()[post]->candidates); i++) {
    if(query_our_elections()[post]->candidates[i][1] != "") {
      str += sprintf("  %s seconded by %s.\n",
                     query_our_elections()[post]->candidates[i][0],
                     query_our_elections()[post]->candidates[i][1]);
      choices += ({ query_our_elections()[post]->candidates[i][0] });
    }
  }
  if(!sizeof(choices)) {
    str = "In the election for the position of " + post +
      " no candidate stood for election therefore the election "
      "is null and void.\n";
  } else if(sizeof(choices) < 2) {
    str = "In the election for the position of " + post +
      " only one candidate stood for election therefore the election "
      "is null and void.\n";
  } else {
    if(_election_announcement[4])
      str += _election_announcement[4];
    add_vote("election", "Election for the post of " + post + "\n", choices,
             0);
  }
  make_announcement(_election_announcement[0], _election_announcement[1],
                    _election_announcement[2], str);
  map_delete(query_our_elections(), post);
  save_room();
}
int list_elections() {
  class election this_election;
  string *posts, text;
  int i, j;
  if ( !m_sizeof( query_our_elections() ) ) {
    write( "There are no elections in progress.\n" );
    return 1;
  }
  posts = m_indices( query_our_elections() );
  if ( sizeof( posts ) > 1 )
    write( "The following elections are in progress:\n" );
  else
    write( "The following election is in progress:\n" );
  text = "";
  for ( i = 0; i < sizeof( posts ); i++ ) {
    this_election = query_our_elections()[posts[i]];
    text += "  Election to the post of "+ posts[i] + ".\n";
    if(!sizeof(this_election->candidates)) {
      text += "  No candidates have declared yet.\n";
    } else {
      text += "    Current candidates are :\n";
      for(j=0; j<sizeof(this_election->candidates); j++) {
        if(this_election->candidates[j][1] != "")
          text += sprintf("    %c. %s seconded by %s.\n", 'A'+j,
                          this_election->candidates[j][0],
                          this_election->candidates[j][1]);
        else
          text += sprintf("    %c. %s not yet seconded.\n", 'A'+j,
                          this_election->candidates[j][0]);
      }
    }
    text += " Candidacies must be declared by "+
      ctime( this_election->closes ) +".\n\n";
  }
  this_player()->more_string(sprintf( "%-=*s",
                                      (int)this_player()->query_cols(),
                                      text ));
  return 1;
}
string strip_spaces(string str) {
   if (!strlen(str)) {
      return str;
   }
   while (str[0] == ' ') {
      str = str[1..];
   }
   if (!strlen(str)) {
      return str;
   }
   while (str[<1] == ' ') {
      str = str[0..<2];
   }
   return str;
}
int do_create_vote(string choices) {
   string* bits;
   bits = map(explode(choices, ","), (: strip_spaces($1) :)) - ({ "" });
   write("Choices: " + query_multiple_short(bits) + ".\n");
   write("What description would you like for your vote?\n");
   this_player()->do_edit("", "create_vote_desc", this_object(), 0, bits);
   add_succeeded_mess(({ "", "$N starts to create a new vote.\n" }));
   return 1;
}
void create_vote_desc(string str, string* choices) {
   if (!str) {
      write("Aborting.\n");
      return ;
   }
   write("Are you sure you wish to create a vote with a description of:\n" +
         str + "\nWith vote choices of " + query_multiple_short(choices) +
         ".\n");
   write("Please answer yes or no: ");
   input_to("create_vote_desc_confirm", 0, str, choices);
}
void create_vote_desc_confirm(string str, string desc, string* choices) {
   str = lower_case(str);
   if (!strlen(str) ||
       (str[0] != 'y' && str[0] != 'n' && str[0] != 'q')) {
      write("Please answer yes or no: ");
      input_to("create_vote_desc_confirm", 0, str, choices);
   }
   if (str[0] == 'q' || str[0] == 'n') {
      write("Ok, quitting.\n");
      return ;
   }
   add_vote("freeform", desc, choices, 0);
   write("Added in the vote.\n");
}
int delete_election(string election) {
  if(!query_our_elections()[election])
    return 0;
  map_delete(query_our_elections(), election);
  save_room();
  return 1;
}
int delete_vote(int vote_id) {
  if(!query_our_votes()[vote_id])
    return 0;
  map_delete(query_our_votes(), vote_id);
  save_room();
  return 1;
}