#include <clubs.h>
#include <player_handler.h>
#include <player_handler.h>
#define MAX_SUBJECT_LEN 40
#define MAX_CHOICE_LEN 10
#define MIN_TIMEOUT 1
#define MAX_TIMEOUT 20
#define MIN_POSITION_LEN 5
#define SAVE_START "club_discuss -- "
#define CLUB_ALL_POSITIONS "all positions"
string query_club();
int do_vote(int id, string choice);
int do_nominate(int id, string person);
int do_withdraw(int id);
int do_list_all();
int do_list_item(int id);
int do_list_archives();
int do_archive(int num);
private nosave int _last_time;
string discussion_item_list(string player) {
   class discussion_idea* ideas;
   class discussion_idea bing;
   string ret;
   int no;
   ideas = CLUB_HANDLER->query_all_discussion_items(query_club());
   ret = "";
   no = 0;
   if (sizeof(ideas)) {
      foreach (bing in ideas) {
         if (CLUB_HANDLER->is_discussion_item_finished(query_club(),
                                                       bing->id)) {
            CLUB_HANDLER->complete_discussion_item(query_club(),
                                                   bing->id);
         } else {
            if (CLUB_HANDLER->can_reference_discussion_item(query_club(),
                                                            bing->id,
                                                            player)) {
               ret += bing->id + ") " +
                  CLUB_HANDLER->query_discussion_item_short_description(query_club(),
                                                                        bing->id);
               if (CLUB_HANDLER->is_discussion_item_quorum(query_club(),
                                                           bing->id)) {
                  ret += " (quorum)";
               }
               if (CLUB_HANDLER->has_voted_for_discussion_item(query_club(),
                                                               bing->id,
                                                               player)) {
                  ret += " (voted)\n";
               } else {
                  ret += "\n";
               }
               no++;
            }
         }
      }
   }
   if (no == 0) {
      ret += "No items up for discussion.\n";
   }
   return ret;
}
string discussion_item(int id,
                       string player) {
   string ret;
   if (CLUB_HANDLER->query_discussion_item(query_club(), id) &&
       CLUB_HANDLER->can_reference_discussion_item(query_club(),
                                                   id,
                                                   player)) {
      ret = "Discussion item #" + id + " by " +
         CLUB_HANDLER->query_discussion_added_by(query_club(), id) +
         " (Finish: " +
         ctime(CLUB_HANDLER->query_discussion_time_finish(query_club(),
                                                          id)) + ")\n" +
         CLUB_HANDLER->query_discussion_item_long_description(query_club(),
                                                              id) +
         "\n\nWith voting choices of " +
         query_multiple_short(CLUB_HANDLER->query_discussion_choices(query_club(),
                                                                     id)) +
         ".\n";
      if (CLUB_HANDLER->has_voted_for_discussion_item(query_club(),
                                                      id,
                                                      player)) {
         ret += "You have voted for the discussion item.\n";
      }
      if (CLUB_HANDLER->is_no_quorum_discussion_item(query_club(), id)) {
         ret += "The discussion item does not require a quorum to carry.\n";
      } else if (CLUB_HANDLER->is_discussion_item_quorum(query_club(), id)) {
         ret += "The discussion item has reached a quorum, so any result "
            "will be final.\n";
         ret += "The discussion item needed " +
                CLUB_HANDLER->query_discussion_item_quorum_number(query_club(),
                                                                  id) +
                " to vote for quorum and so far " +
                CLUB_HANDLER->query_discussion_item_number_voted(query_club(),
                                                                 id) +
                " people have voted.\n";
      } else {
         ret += "The discussion item needs " +
                CLUB_HANDLER->query_discussion_item_quorum_number(query_club(),
                                                                  id) +
                " to vote for quorum and so far " +
                CLUB_HANDLER->query_discussion_item_number_voted(query_club(),
                                                                 id) +
                " people have voted.\n";
      }
      if (CLUB_HANDLER->is_committee_discussion_item(query_club(), id)) {
         ret += "This is a committee only discussion item.\n";
      }
      return ret;
   }
   return "Lost discussion item of the far west.\n";
}
protected void add_elected_commands(object per) {
   string tmp_name;
   class discussion_idea* ideas;
   tmp_name = replace(lower_case(query_club()), " ", "_");
   per->add_command(tmp_name,
               this_object(),
               "vote for <string'choice'> in <number'id'>",
               (: do_vote($4[1], $4[0]) :));
   per->add_command(tmp_name,
               this_object(),
               "nominate <string'person'> in <number'id'>",
               (: do_nominate($4[1], $4[0]) :));
   per->add_command(tmp_name,
               this_object(),
               "withdraw from <number'id'>",
               (: do_withdraw($4[0]) :));
   per->add_command(tmp_name,
               this_object(),
               "list all [discussion items]",
               (: do_list_all() :));
   per->add_command(tmp_name,
               this_object(),
               "list [discussion item] <number'id'>",
               (: do_list_item($4[0]) :));
   per->add_command(tmp_name,
               this_object(),
               "archives",
               (: do_list_archives() :));
   per->add_command(tmp_name,
               this_object(),
               "archives [list] <number>",
               (: do_archive($4[0]) :));
   if (_last_time + 24 * 60 * 60 < time()) {
      _last_time = time();
      ideas = CLUB_HANDLER->query_all_discussion_items(query_club());
      ideas = filter(ideas,  (:
                   CLUB_HANDLER->can_reference_discussion_item(query_club(),
                                        $1->id,
                                        this_player()->query_name()) :) );
      ideas = filter(ideas, (:
                   !CLUB_HANDLER->has_voted_for_discussion_item(query_club(),
                                        $1->id,
                                        this_player()->query_name()) :) );
      if (sizeof(ideas)) {
         write("%^YELLOW%^There are discussion items you have not voted "
               "for, use '" + tmp_name +
               " list all' for a list.\n%^RESET%^");
      }
   }
}
protected void add_club_commands(object per) {
}
int do_list_all() {
   string ret;
   ret = discussion_item_list(this_player()->query_name());
   write("$P$Discussion items$P$" + ret);
   return 1;
}
int do_list_item(int id) {
   string ret;
   if (!CLUB_HANDLER->query_discussion_item(query_club(), id) ||
       !CLUB_HANDLER->can_reference_discussion_item(query_club(),
                                                    id,
                                                    this_player()->query_name())) {
      add_failed_mess("There is no discussion item #" + id + ".\n");
      return 0;
   }
   ret = discussion_item(id, this_player()->query_name());
   write("$P$Discussion item$P$" + ret);
   return 1;
}
int do_vote(int id,
            string choice) {
   if (!CLUB_HANDLER->query_discussion_item(query_club(), id) ||
       !CLUB_HANDLER->can_reference_discussion_item(query_club(),
                                                    id,
                                                    this_player()->query_name())) {
      add_failed_mess("There is no discussion item #" + id + ".\n");
      return 0;
   }
   if (!CLUB_HANDLER->is_discuss_votable(query_club(), id)) {
      add_failed_mess("The discussion item #" + id + " is not able "
                      "to be voted for.\n");
      return 0;
   }
   if (!CLUB_HANDLER->is_valid_discussion_choice(query_club(),
                                                 id,
                                                 choice)) {
      add_failed_mess("Invalid choice to the discussion item, the allowed "
                      "choices are " +
                      query_multiple_short(
                        CLUB_HANDLER->query_discussion_choices(query_club(),
                                                               id)) +
                      ".\n");
      return 0;
   }
   if (CLUB_HANDLER->vote_for_discussion_item(query_club(),
                                              id,
                                              this_player()->query_name(),
                                              choice)) {
      add_succeeded_mess(({ "Voted '" + choice + "' for discussion item #" +
                            id + ".\n",
                            "$N voted for a discussion item in '" +
                            CLUB_HANDLER->query_club_name(query_club()) +
                            "'.\n" }));
      return 1;
   } else {
      add_failed_mess("Unable to vote for the discussion item for "
                      "some reason.\n");
      return 0;
   }
}
int do_nominate(int id, string person) {
   if (!CLUB_HANDLER->query_discussion_item(query_club(), id) ||
       !CLUB_HANDLER->can_reference_discussion_item(query_club(),
                                                    id,
                                                    this_player()->query_name())) {
      add_failed_mess("There is no discussion item #" + id + ".\n");
      return 0;
   }
   if (!CLUB_HANDLER->is_discuss_nominateable(query_club(), id)) {
      add_failed_mess("The discussion item #" + id + " is not able "
                      "to be nominated for.\n");
      return 0;
   }
   if (CLUB_HANDLER->is_discuss_person_nominated(query_club(),
                                                 id,
                                                 person,
                                                 this_player()->query_name())) {
      add_failed_mess("The person " + person + " has already been nominated "
                      "for that position.\n");
      return 0;
   }
   if (!CLUB_HANDLER->is_creator_club(query_club()) &&
       PLAYER_HANDLER->test_creator(person)) {
      add_failed_mess("You can only nominated creators to positions in "
                      "creator clubs.\n");
      return 0;
   }
   if (CLUB_HANDLER->nominate_discussion_item(query_club(),
                                              id,
                                              this_player()->query_name(),
                                              person)) {
      add_succeeded_mess(({ "Nominated '" + person +
                            "' for discussion item #" + id + ".\n",
                            "$N nominated someone in a discussion item in '" +
                            CLUB_HANDLER->query_club_name(query_club()) +
                            "'.\n" }));
      return 1;
   } else {
      add_failed_mess("Unable to nominate " + person + " for "
                      "some reason.\n");
      return 0;
   }
}
int do_withdraw(int id) {
   if (!CLUB_HANDLER->query_discussion_item(query_club(), id) ||
       !CLUB_HANDLER->can_reference_discussion_item(query_club(),
                                                    id,
                                                    this_player()->query_name())) {
      add_failed_mess("There is no discussion item #" + id + ".\n");
      return 0;
   }
   if (!CLUB_HANDLER->is_discuss_nominateable(query_club(), id)) {
      add_failed_mess("The discussion item #" + id + " is not able "
                      "to be nominated for (and therefor withdrawn from).\n");
      return 0;
   }
   if (!CLUB_HANDLER->is_discuss_person_nominated(query_club(),
                                                 id,
                                                 this_player()->query_name(),
                                                 this_player()->query_name())) {
      add_failed_mess("You have not been nominated for this position.\n");
      return 0;
   }
   if (CLUB_HANDLER->withdraw_discussion_item(query_club(),
                                              id,
                                              this_player()->query_name(),
                                              this_player()->query_name())) {
      add_succeeded_mess(({ "Withdrew from discussion item #" + id + ".\n",
                            "$N withdrew from a discussion item in '" +
                            CLUB_HANDLER->query_club_name(query_club()) +
                            "'.\n" }));
      return 1;
   } else {
      add_failed_mess("Unable to withdraw from the discussion item for "
                      "some reason.\n");
      return 0;
   }
}
int do_list_archives() {
   class club_archive* archives;
   string bing;
   class club_archive fluff;
   int num;
   archives = CLUB_HANDLER->query_archives(query_club());
   if (!sizeof(archives)) {
      add_failed_mess("This club has no archives currently.\n");
      return 0;
   }
   bing = "";
   num = 1;
   foreach (fluff in archives) {
      bing += "#" + num + " finished at " + ctime(fluff->archive_date) + " " +
              fluff->subject + "\n";
      num++;
   }
   write("$P$Club Archives$P$" + bing);
   return 1;
}
int do_archive(int num) {
   string bing;
   class club_archive fluff;
   class club_archive* archives;
   archives = CLUB_HANDLER->query_archives(query_club());
   if (!sizeof(archives)) {
      add_failed_mess("This club has no archives currently.\n");
      return 0;
   }
   if (num < 1 || num > sizeof(archives)) {
      add_failed_mess("The number must be between 1 and " +
                      sizeof(archives) + ".\n");
      return 0;
   }
   fluff = archives[num - 1];
   bing = "Archive #" + num + " finished at " +
           ctime(fluff->archive_date) + " " +
           fluff->subject + "\n" + fluff->matter + "\n";
   write("$P$Club Archives$P$" + bing);
   return 1;
}
mapping query_dynamic_auto_load(mapping map) {
   if (!map) {
      map = ([ ]);
   }
   map[SAVE_START + "last time"] = _last_time;
   return map;
}
void init_dynamic_arg(mapping map) {
   _last_time = map[SAVE_START + "last time"];
}