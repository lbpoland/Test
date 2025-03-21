inherit "/obj/handlers/inherit/club_elected";
#define __CLUBS_H_NO_CLASSES
#include <clubs.h>
#include <broadcaster.h>
#include <player_handler.h>
#include <player_handler.h>
private nosave mapping _discussion_items;
#define CLUB_DISCUSS_FUNCTION_OBJECT     0
#define CLUB_DISCUSS_FUNCTION_FUNCTION   1
#define CLUB_DISCUSS_QUORUM_COMMITTEE   75
#define CLUB_DISCUSS_QUORUM_OPEN        25
private void add_club_discussion(int type,
                                 function func);
protected int remove_discussion_item(string club_name,
                                     class discussion_idea item);
private mixed club_discuss_new_position(int message,
                                        string club_name,
                                        class discussion_idea frog);
private mixed club_discuss_position_name(int message,
                                         string club_name,
                                         class discussion_idea frog,
                                         string arg1,
                                         string arg2);
private mixed club_discuss_position_remove(int message,
                                           string club_name,
                                           class discussion_idea frog,
                                           string arg1,
                                           string arg2);
private mixed club_discuss_description(int message,
                                       string club_name,
                                       class discussion_idea frog);
private mixed club_discuss_memo(int message,
                                string club_name,
                                class discussion_idea frog);
private mixed club_discuss_secret(int message,
                                  string club_name,
                                  class discussion_idea frog);
private mixed club_discuss_remove_member(int message,
                                         string club_name,
                                         class discussion_idea frog,
                                         string member);
private mixed club_discuss_no_confidence(int message,
                                         string club_name,
                                         class discussion_idea frog,
                                         string arg1,
                                         string arg2);
private mixed club_discuss_election(int message,
                                    string club_name,
                                    class discussion_idea frog,
                                    string arg1,
                                    string arg2);
private mixed club_discuss_nomination(int message,
                                      string club_name,
                                      class discussion_idea frog,
                                      string arg1,
                                      string arg2);
private mixed club_discuss_function(int message,
                                    string club_name,
                                    class discussion_idea frog,
                                    string arg1,
                                    string arg2);
private mixed club_discuss_create_account(int message,
                                    string club_name,
                                    class discussion_idea frog,
                                    string arg1,
                                    string arg2);
class discussion_idea query_discussion_item_by_type(string club_name,
                                                    int type,
                                                    class discussion_idea idea);
protected mixed send_discuss_message(string club_name,
                                    int message,
                                    class discussion_idea item,
                                    string arg1,
                                    string arg2);
protected void broadcast_discuss_message(string club_name,
                                         int message,
                                         string arg1,
                                         string arg2);
int add_discussion_item(string club,
                        int type,
                        string added_by,
                        string name,
                        string info,
                        string *choices,
                        int time_to_finish,
                        mixed extra_data);
int setup_by_election(string club,
                      string position,
                      string info);
int is_discuss_nominateable(string club_name,
                            int id);
void create() {
   _discussion_items = ([ ]);
   ::create();
   add_club_discussion(CLUB_DISCUSS_NEW_POSITION,
                       (: club_discuss_new_position :));
   add_club_discussion(CLUB_DISCUSS_POSITION_NAME,
                       (: club_discuss_position_name :));
   add_club_discussion(CLUB_DISCUSS_POSITION_REMOVE,
                       (: club_discuss_position_remove :));
   add_club_discussion(CLUB_DISCUSS_DESCRIPTION,
                       (: club_discuss_description :));
   add_club_discussion(CLUB_DISCUSS_MEMO,
                       (: club_discuss_memo :));
   add_club_discussion(CLUB_DISCUSS_MEMBER_REMOVE,
                       (: club_discuss_remove_member :));
   add_club_discussion(CLUB_DISCUSS_SECRET_TYPE,
                       (: club_discuss_secret :));
   add_club_discussion(CLUB_DISCUSS_NO_CONFIDENCE,
                       (: club_discuss_no_confidence :));
   add_club_discussion(CLUB_DISCUSS_ELECTION,
                       (: club_discuss_election :));
   add_club_discussion(CLUB_DISCUSS_NOMINATION,
                       (: club_discuss_nomination :));
   add_club_discussion(CLUB_DISCUSS_FUNCTION,
                       (: club_discuss_function :));
   add_club_discussion(CLUB_DISCUSS_CREATE_ACCOUNT,
                       (: club_discuss_create_account :));
}
private void add_club_discussion(int type,
                                 function func) {
   _discussion_items[type] = func;
}
protected int archive_discussion_item(string club_name,
                                      string subject,
                                      string item) {
   if (is_elected_club(club_name)) {
      add_archive(club_name,
                  subject,
                  item);
   }
}
int is_discussion_position_valid(string club_name,
                                 string position) {
   class discussion_idea bing;
   position = lower_case(position);
   if (is_valid_position(club_name, position)) {
      return 0;
   }
   do {
      bing = query_discussion_item_by_type(club_name,
                                           CLUB_DISCUSS_POSITION_NAME,
                                           bing);
      if (bing) {
         if (!undefinedp(bing->choices[position])) {
            return 0;
         }
      }
   } while (bing);
   do {
      bing = query_discussion_item_by_type(club_name,
                                           CLUB_DISCUSS_NEW_POSITION,
                                           bing);
      if (bing) {
         if (bing->information == position) {
            return 0;
         }
      }
   } while (bing);
   return 1;
}
private mixed club_discuss_position_name(int message,
                                         string club_name,
                                         class discussion_idea frog,
                                         string arg1,
                                         string arg2) {
   string body;
   string position;
   int num;
   string old_pos;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         if (!is_discussion_position_valid(club_name, frog->optional_data)) {
            return 0;
         }
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         if (!is_valid_position(club_name, frog->name)) {
            return 0;
         }
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The final votes for the discussion item to change the "
                "position " +frog->name + " to " + frog->optional_data +
                " is:\n";
         foreach (position, num in frog->choices) {
            body += position + ":   " + num + "\n";
         }
         body += "\n";
         if (frog->information) {
            body += frog->information + "\n";
         }
         old_pos = frog->name;
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            change_position_name_in_club(club_name,
                                        frog->name,
                                        frog->optional_data);
            body += "Which means the position " + old_pos +
                     " has been changed to " + frog->optional_data + ".\n";
         } else {
            body += "Which means the position " + old_pos +
                    " has not been changed to " + frog->optional_data + ".\n";
         }
         do_mail_committee(club_name,
                           "Results of changing the position " +
                              frog->name,
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Voting on changing the position '" + frog->name +
                "' to '" + frog->optional_data + "'.\n";
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Changing the position '" + frog->name + "'";
      case CLUB_DISCUSS_MESSAGE_CHANGE_POSITION :
         if (frog->name == arg1) {
            frog->name = arg2;
            return 1;
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_REMOVE_POSITION :
         if (frog->name == arg1) {
            remove_discussion_item(club_name, frog);
            return 1;
         }
         return 0;
   }
   return 0;
}
private mixed club_discuss_position_remove(int message,
                                           string club_name,
                                           class discussion_idea frog,
                                           string arg1,
                                           string arg2) {
   string body;
   string position;
   int num;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         if (!is_valid_position(club_name, frog->name)) {
            return 0;
         }
         if (is_basic_position(club_name, frog->name)) {
            return 0;
         }
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The final votes for the discussion item "
                "to remove the position " + frog->name + " are:\n";
         foreach (position, num in frog->choices) {
            body += position + ":   " + num + "\n";
         }
         body += "\n";
         if (frog->information) {
            body += frog->information + "\n";
         }
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            if (is_basic_position(club_name, frog->name)) {
               body += "Unable to remove the basic position " + frog->name +
                        ".\n";
            } else if (remove_position_in_club(club_name, frog->name)) {
               body += "Which means the position " + frog->name +
                        " has been removed.\n";
            } else {
               body += "Unable to remove the position " + frog->name +
                        " for some reason, basic position or something?\n";
            }
         } else {
            body += "Which means the position " + frog->name +
                    " has not been removed.\n";
         }
         do_mail_committee(club_name,
                           "Results of removing the position " +
                              frog->name,
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Voting on removing the position '" + frog->name +
                "'.\n";
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Removing the position '" + frog->name + "'";
      case CLUB_DISCUSS_MESSAGE_CHANGE_POSITION :
         if (frog->name == arg1) {
            frog->name = arg2;
            return 1;
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_REMOVE_POSITION :
         if (frog->name == arg1) {
            remove_discussion_item(club_name, frog);
            return 1;
         }
         return 0;
   }
   return 0;
}
private mixed club_discuss_new_position(int message,
                                        string club_name,
                                        class discussion_idea frog) {
   string body;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         if (!is_discussion_position_valid(club_name, frog->name)) {
            return 0;
         }
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The vote for adding the position " +
            frog->name + " to the club " + query_club_name(club_name) +
            " has been completed and the results are " +
            frog->choices[CLUB_DISCUSS_YES_CHOICE] + " in favour, " +
            frog->choices[CLUB_DISCUSS_NO_CHOICE] + " against and " +
            frog->choices[CLUB_DISCUSS_ABSTAIN_CHOICE] + " abstaining.\n";
         if (frog->information) {
            body += frog->information;
         }
         if (is_valid_position(club_name, frog->name)) {
            body += "\nUnfortunately " + frog->name +
               " is not a valid position.  Vote forfited.\n";
            do_mail_committee(club_name,
                              "Results of adding " + frog->name,
                              body);
            return 0;
         }
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            if (create_position_in_club(club_name, frog->name)) {
               body += "\nWhich means that the position " + frog->name +
                  " has been created.\n";
               setup_by_election(club_name,
                                 frog->name,
                                 frog->information);
            } else if (is_voting_in_progress(club_name)) {
               body += "\nWhich means we attempted to create the position " +
                  frog->name + " but were prevented because "
                  "voting is in progress?\n";
            } else {
               body += "\nWhich means we attempted to create the position " +
                  frog->name + " but were prevented for some reason.\n";
            }
         } else {
            body += "\nWhich means that the position " + frog->name +
               " was not created.\n";
         }
         do_mail_committee(club_name,
                           "Results of adding " + frog->name,
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Voting on adding the position '" + frog->name +
            "' to the club.\n";
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Adding the position '" + frog->name + "'";
   }
   return 0;
}
private mixed club_discuss_description(int message,
                                       string club_name,
                                       class discussion_idea frog) {
   string body;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         if (query_discussion_item_by_type(club_name,
                                           CLUB_DISCUSS_DESCRIPTION,
                                           0)) {
            return 0;
         }
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The vote for changing the description of the " +
            "club " + query_club_name(club_name) +
            " to:\n" + frog->information + "\nThe vote has been completed "
            "and the results are " +
            frog->choices[CLUB_DISCUSS_YES_CHOICE] + " in favour, " +
            frog->choices[CLUB_DISCUSS_NO_CHOICE] + " against and " +
            frog->choices[CLUB_DISCUSS_ABSTAIN_CHOICE] + " abstaining.\n";
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            set_club_description(club_name, frog->information);
            body += "Which means the description has been changed.\n";
         } else {
            body += "Which means the description has not been changed.\n";
         }
         do_mail_committee(club_name,
                           "Results of changing the description",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Voting on changing the description of the club to:\n" +
                frog->information + "\n";
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Changing the description";
   }
   return 0;
}
private mixed club_discuss_secret(int message,
                                  string club_name,
                                  class discussion_idea frog) {
   string body;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         if (query_discussion_item_by_type(club_name,
                                           CLUB_DISCUSS_SECRET_TYPE,
                                           0)) {
            return 0;
         }
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The vote for changing the club " +
                query_club_name(club_name) + " to ";
         if (query_club_secret(club_name)) {
            body += "an open club";
         } else {
            body += "a secret club";
         }
         body += " has been completed and the "
            "results are " +
            frog->choices[CLUB_DISCUSS_YES_CHOICE] + " in favour and " +
            frog->choices[CLUB_DISCUSS_NO_CHOICE] + " against with " +
            frog->choices[CLUB_DISCUSS_ABSTAIN_CHOICE] + " abstaining.\n\n";
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            if (query_club_secret(club_name)) {
               reset_club_secret(club_name);
               body += "Which means the club is now open.\n";
            } else {
               set_club_secret(club_name);
               body += "Which means the club is now secret.\n";
            }
         } else {
            body += "Which means the club's secret flag has not been "
                    "changed.\n";
         }
         if (frog->information) {
            body += "\n" + frog->information;
         }
         do_mail_committee(club_name,
                           "Results of changing the secret flag",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         if (query_club_secret(club_name)) {
            body = "Voting on changing the club to be open.\n";
         } else {
            body = "Voting on changing the club to be secret.\n";
         }
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         if (query_club_secret(club_name)) {
            return "Changing the club to be open";
         } else {
            return "Changing the club to be secret";
         }
   }
   return 0;
}
private mixed club_discuss_memo(int message,
                                string club_name,
                                class discussion_idea frog) {
   string body;
   string choice;
   int num;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "   The final votes for discussion memo '" +
                frog->name + "' were:\n";
         foreach (choice, num in frog->choices) {
            body += choice + ":   " + num + "\n";
         }
         body += "\n" + frog->information;
         do_mail_committee(club_name,
                           "Results of memo '" +
                           frog->name + "'\n",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Voting on the memo '" + frog->name +
                "'.\n";
         if (stringp(frog->information)) {
            body += "\n" + frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Memo: " + frog->name;
   }
   return 0;
}
private mixed club_discuss_remove_member(int message,
                                         string club_name,
                                         class discussion_idea frog,
                                         string member) {
   string body;
   class discussion_idea womble;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         frog->name = lower_case(frog->name);
         do {
            womble = query_discussion_item_by_type(club_name,
                                                   CLUB_DISCUSS_MEMBER_REMOVE,
                                                   womble);
            if (womble &&
                womble->name == frog->name) {
               return 0;
            }
         } while (womble);
         if (!is_member_of(club_name, frog->name)) {
            return 0;
         }
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The vote for changing removing the member " +
                frog->name + " from the club " +
                query_club_name(club_name) +
                " has been completed and the "
            "results are " +
            frog->choices[CLUB_DISCUSS_YES_CHOICE] + " in favour and " +
            frog->choices[CLUB_DISCUSS_NO_CHOICE] + " against with " +
            frog->choices[CLUB_DISCUSS_ABSTAIN_CHOICE] + " abstaining.\n\n";
         if (frog->information) {
            body += frog->information;
         }
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            if (!is_member_of(club_name, frog->name)) {
               body += "Looks like someone beat us to removing them.\n";
            } else {
               body += "Which means they have now been removed.\n";
               remove_member(club_name, frog->name);
            }
         } else {
            body += "Which means no one has been removed.\n";
         }
         do_mail_committee(club_name,
                           "Results of removing the member",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Voting on removing the member " + frog->name + ".\n";
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Removing the member " + frog->name;
      case CLUB_DISCUSS_MESSAGE_REMOVE_MEMBER :
         if (frog->name == member) {
            return remove_discussion_item(club_name, frog);
         }
         return 0;
   }
   return 0;
}
private mixed club_discuss_no_confidence(int message,
                                         string club_name,
                                         class discussion_idea frog,
                                         string arg1,
                                         string arg2) {
   string body;
   class discussion_idea womble;
   string real;
   string pos;
   if (!frog->name) {
      real = "all postions";
   } else {
      real = frog->name;
   }
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         frog->name = lower_case(frog->name);
         do {
            womble = query_discussion_item_by_type(club_name,
                                                   CLUB_DISCUSS_NO_CONFIDENCE,
                                                   womble);
            if (womble &&
                womble->name == frog->name) {
               return 0;
            }
         } while (womble);
         if (!is_valid_position(club_name, frog->name) &&
             frog->name) {
            return 0;
         }
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "   The vote for no confidence in " +
                real + " in the club " +
                query_club_name(club_name) +
                " has been completed and the "
            "results are " +
            frog->choices[CLUB_DISCUSS_YES_CHOICE] + " in favour and " +
            frog->choices[CLUB_DISCUSS_NO_CHOICE] + " against with " +
            frog->choices[CLUB_DISCUSS_ABSTAIN_CHOICE] + " abstaining.\n\n";
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            if (!frog->name) {
               body += "Therefor we have removed everyone from the committee "
                  "and started a new election.\n";
               foreach (pos in query_valid_positions(club_name)) {
                  catch(set_position_holder(club_name, pos, CLUB_UNKNOWN_MEMBER));
               }
               start_election(club_name);
            } else if (is_valid_position(club_name,
                                  frog->name)) {
               set_position_holder(club_name, frog->name, CLUB_UNKNOWN_MEMBER);
               body += "Therefor we had set the position as vacant.\n";
            } else {
               body += "The position in the club appears to have vanished!\n";
            }
         } else {
            body += "Which means nothing has happened.\n";
         }
         if (frog->information) {
            body += frog->information;
         }
         do_mail_committee(club_name,
                           "Results of no confidence vote",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Voting on confidence in the position " +
                real + ", a yes vote indicates that you are in favour of the "
                "no confidence vote.\n";
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "No confidence in " + real;
      case CLUB_DISCUSS_MESSAGE_REMOVE_MEMBER :
         if (holds_position_of(club_name,
                               frog->name,
                               arg1) ||
             holds_position_of(club_name,
                               frog->name,
                               CLUB_UNKNOWN_MEMBER)) {
            return remove_discussion_item(club_name, frog);
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_CHANGE_POSITION :
         if (frog->name == arg1) {
            frog->name = arg2;
            return 1;
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_REMOVE_POSITION :
         if (frog->name == arg1) {
            remove_discussion_item(club_name, frog);
            return 1;
         }
         return 0;
   }
   return 0;
}
private int is_nomination_or_election_being_discussed(
   string club_name,
   string pos_name
   )
{
   class discussion_idea womble;
   womble = 0;
   do {
      womble = query_discussion_item_by_type(club_name,
                                             CLUB_DISCUSS_ELECTION,
                                             womble);
      if (womble &&
          lower_case(womble->name) == lower_case(pos_name)) {
         return 1;
      }
   } while (womble);
   womble = 0;
   do {
      womble = query_discussion_item_by_type(club_name,
                                             CLUB_DISCUSS_NOMINATION,
                                             womble);
      if (womble &&
          lower_case(womble->name) == lower_case(pos_name)) {
         return 1;
      }
   } while (womble);
   return 0;
}
private mixed club_discuss_nomination(int message,
                                      string club_name,
                                      class discussion_idea frog,
                                      string arg1,
                                      string arg2) {
   string body;
   string name;
   string *nom;
   string *nominated;
   int ret;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         frog->name = query_position_name(club_name, frog->name);
         if (is_nomination_or_election_being_discussed(club_name, frog->name)) {
            return 0;
         }
         if (!is_valid_position(club_name, frog->name)) {
            return 0;
         }
         if (is_election_in_progress(club_name) ||
             is_nomination_in_progress(club_name)) {
            return 0;
         }
         frog->choices = ([ ]);
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The vote for nominations for the position of " +
                frog->name + " in the club " +
                query_club_name(club_name) +
                " has been completed and the "
            "results are:\n";
         nominated = ({ });
         foreach (name, nom in frog->choices) {
            body += name + ": " + query_multiple_short(nom);
            if (member_array(name, nom) != -1 &&
                sizeof(nom) >= 2) {
               body += " (accepted)\n";
               nominated += ({ name });
            } else {
               body += "\n";
            }
         }
         if (frog->information) {
            body += frog->information;
         }
         if (sizeof(nominated)) {
            if (is_valid_position(club_name,
                                  frog->name)) {
               if (sizeof(nominated) != 1) {
                  body += "Therefor we had added an election for " +
                     query_multiple_short(nominated) +
                     " .\n";
                  call_out((: add_discussion_item :), 0,
                                      club_name,
                                      CLUB_DISCUSS_ELECTION |
                                         CLUB_DISCUSS_OPEN |
                                         CLUB_DISCUSS_NO_QUORUM,
                                      CLUB_CONTROLLER_MEMBER,
                                      frog->name,
                                      frog->information,
                                      nominated,
                                      7 * (24 * 60 * 60),
                                      0);
               } else {
                  body += "Only " + nominated[0] +
                     " was nominated, so they are elected immediately.\n";
                  set_position_holder(club_name, frog->name, nominated[0]);
               }
            } else {
               body += "The position in the club appears to have vanished!\n";
            }
         } else {
            if (is_valid_position(club_name, frog->name)) {
               body += "No one accepted their nomination, so nothing "
                       "happened.\n";
               call_out((: add_discussion_item :), 0,
                                   club_name,
                                   CLUB_DISCUSS_NOMINATION |
                                      CLUB_DISCUSS_OPEN |
                                      CLUB_DISCUSS_NO_QUORUM,
                                   frog->added_by,
                                   frog->name,
                                   frog->information,
                                   ({ }),
                                   7 * (24 * 60 * 60),
                                   frog->optional_data);
            } else {
               body += "The position in the club appears to have vanished!\n";
            }
         }
         do_mail_committee(club_name,
                           "Results of nomination",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Nominations for the position " + frog->name + ":\n";
         foreach (name, nom in frog->choices) {
            body += name + ": " + query_multiple_short(nom);
            if (member_array(name, nom) != -1 &&
                sizeof(nom) >= 2) {
               body += " (accepted)\n";
            } else {
               body += "\n";
            }
         }
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Nominations for " + frog->name;
      case CLUB_DISCUSS_MESSAGE_NOMINATION :
         if (is_member_of(club_name, arg1) &&
             is_member_of(club_name, arg2)) {
            if (!frog->choices[arg2]) {
               frog->choices[arg2] = ({ arg1 });
               return 1;
            } else if (member_array(arg1,
                                    frog->choices[arg2]) == -1) {
               frog->choices[arg2] += ({ arg1 });
               return 1;
            }
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_WITHDRAW :
         if (frog->choices[arg1]) {
            map_delete(frog->choices, arg1);
            return 1;
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_REMOVE_MEMBER :
         if (frog->choices[arg1]) {
            map_delete(frog->choices, arg1);
            ret = 1;
         }
         foreach (name, nom in frog->choices) {
            if (member_array(arg1, nom) != -1) {
               frog->choices[name] = nom - ({ arg1 });
               if (!sizeof(frog->choices[name])) {
                  map_delete(frog->choices, name);
               }
               ret = 1;
            }
         }
         return ret;
      case CLUB_DISCUSS_MESSAGE_CHANGE_POSITION :
         if (frog->name == arg1) {
            frog->name = arg2;
            return 1;
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_TYPE :
         return CLUB_DISCUSS_MESSAGE_TYPE_NOMINATE;
      case CLUB_DISCUSS_MESSAGE_NOMINATION_QUERY :
         return frog->choices;
      case CLUB_DISCUSS_MESSAGE_REMOVE_POSITION :
         if (frog->name == arg1) {
            remove_discussion_item(club_name, frog);
            return 1;
         }
         return 0;
   }
   return 0;
}
private mixed club_discuss_election(int message,
                                    string club_name,
                                    class discussion_idea frog,
                                    string arg1,
                                    string arg2) {
   string body;
   string name;
   int num;
   int highest;
   string *voted;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         frog->name = query_position_name(club_name, frog->name);
         if (is_nomination_or_election_being_discussed(club_name, frog->name)) {
            return 0;
         }
         if (!is_valid_position(club_name, frog->name)) {
            return 0;
         }
         if (is_election_in_progress(club_name) ||
             is_nomination_in_progress(club_name)) {
            return 0;
         }
         foreach (name, num in frog->choices) {
            frog->choices[name] = 0;
            if (!is_member_of(club_name, name)) {
               map_delete(frog->choices, name);
            }
         }
         if (!sizeof(frog->choices)) {
            return 0;
         }
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The vote the position of " +
                frog->name + " in the club " +
                query_club_name(club_name) +
                " has been completed and the "
            "results are:\n";
         highest = 0;
         voted = ({ });
         foreach (name, num in frog->choices) {
            body += name + ": " + num + "\n";
            if (num > highest) {
               highest = num;
               voted = ({ name });
            } else if (highest == num) {
               voted += ({ name });
            }
         }
         if (frog->information) {
            body += frog->information;
         }
         if (sizeof(voted)) {
            if (is_valid_position(club_name,
                                  frog->name)) {
               if (sizeof(voted) == 1) {
                  body += "Therefor " + voted[0] +
                     " was elected to the position of " + frog->name +
                     ".\n";
                  set_position_holder(club_name, frog->name, voted[0]);
               } else {
                  body += "More than one person tied for the position, so "
                     "the election has been added again.\n";
               }
            } else {
               body += "The position in the club appears to have vanished!\n";
            }
         } else {
            body += "No one voted for anyone, so nothing happened.\n";
         }
         do_mail_committee(club_name,
                           "Results of election",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Election for the position of " + frog->name + ".\n";
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Election for " + frog->name;
      case CLUB_DISCUSS_MESSAGE_REMOVE_MEMBER :
         if (!undefinedp(frog->choices[arg1])) {
            map_delete(frog->choices, arg1);
            return 1;
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_CHANGE_POSITION :
         if (frog->name == arg1) {
            frog->name = arg2;
            return 1;
         }
         return 0;
      case CLUB_DISCUSS_MESSAGE_REMOVE_POSITION :
         if (frog->name == arg1) {
            remove_discussion_item(club_name, frog);
            return 1;
         }
         return 0;
   }
   return 0;
}
private mixed club_discuss_function(int message,
                                    string club_name,
                                    class discussion_idea frog,
                                    string arg1,
                                    string arg2) {
   mixed ret;
   ret = call_other(frog->name[CLUB_DISCUSS_FUNCTION_OBJECT],
                    frog->name[CLUB_DISCUSS_FUNCTION_FUNCTION],
                    message,
                    club_name,
                    frog,
                    arg1,
                    arg2);
   if (message == CLUB_DISCUSS_MESSAGE_COMPLETE &&
       stringp(ret)) {
      do_mail_committee(club_name,
                      send_discuss_message(club_name,
                                           CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                           frog,
                                           arg1,
                                           arg2),
                      ret);
      archive_discussion_item(club_name,
                              send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                              ret);
      return 1;
   }
   return ret;
}
private mixed club_discuss_create_account(int message,
                                    string club_name,
                                    class discussion_idea frog,
                                    string arg1,
                                    string arg2) {
   string body;
   class discussion_idea womble;
   switch (message) {
      case CLUB_DISCUSS_MESSAGE_VERIFY :
         do {
            womble = query_discussion_item_by_type(club_name,
                                                   CLUB_DISCUSS_CREATE_ACCOUNT,
                                                   womble);
            if (womble &&
                womble->name == frog->name) {
               return 0;
            }
         } while (womble);
         frog->choices = ([ CLUB_DISCUSS_YES_CHOICE : 0,
                            CLUB_DISCUSS_NO_CHOICE : 0,
                            CLUB_DISCUSS_ABSTAIN_CHOICE : 0 ]);
         if (is_account_of(club_name, frog->name)) {
            return 0;
         }
         return 1;
      case CLUB_DISCUSS_MESSAGE_COMPLETE :
         body = "Hello!\n\nThe discussion item "
                "added at " + ctime(frog->time_added) + ", finished at " +
                ctime(time()) + " and added by " + frog->added_by +
                " has finished.";
         body += "  The vote for adding the special account " +
                frog->name + " in the club " +
                query_club_name(club_name) +
                " has been completed and the "
                "results are " +
                frog->choices[CLUB_DISCUSS_YES_CHOICE] + " in favour, " +
                frog->choices[CLUB_DISCUSS_NO_CHOICE] + " against and " +
                frog->choices[CLUB_DISCUSS_ABSTAIN_CHOICE] + " abstaining.\n";
         if (frog->choices[CLUB_DISCUSS_YES_CHOICE] >
             frog->choices[CLUB_DISCUSS_NO_CHOICE]) {
            if (create_account(club_name, frog->name)) {
                body += "Which means the special account " + frog->name +
                     " has been created.\n";
            } else {
                body += "Which means the special account " + frog->name +
                     " was attempted to be created but had some problems.\n";
            }
         } else {
            body += "Which means the special account " + frog->name +
                  " has not been created.\n";
         }
         if (frog->information) {
            body += frog->information;
         }
         do_mail_committee(club_name,
                           "Results of creating account",
                           body);
         archive_discussion_item(club_name,
                                 send_discuss_message(club_name,
                                                 CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                 frog,
                                                 0,
                                                 0),
                                 body);
         return 1;
      case CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION :
         body = "Creating the special account " + frog->name + ".\n";
         if (frog->information) {
            body += frog->information;
         }
         return body;
      case CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION :
         return "Create special account " + frog->name;
   }
   return 0;
}
class discussion_idea query_discussion_item(string club_name,
                                            int id) {
   class election_info frog;
   class discussion_idea bing;
   frog = (class election_info)query_elected_info(club_name);
   if (frog) {
      foreach (bing in frog->discussion) {
         if (bing->id == id) {
            return bing;
         }
      }
   }
   return 0;
}
class discussion_idea* query_all_discussion_items(string club_name) {
   class election_info frog;
   frog = (class election_info)query_elected_info(club_name);
   if (frog) {
      return copy(frog->discussion);
   }
   return 0;
}
string query_discussion_item_short_description(string club_name,
                                               int id) {
   class discussion_idea bing;
   bing = query_discussion_item(club_name, id);
   if (bing) {
      if (_discussion_items[bing->discuss_type & CLUB_DISCUSS_TYPE_MASK]) {
         return send_discuss_message(club_name,
                                     CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                     bing,
                                     0,
                                     0);
      }
   }
   return 0;
}
string query_discussion_item_long_description(string club_name,
                                            int id) {
   class discussion_idea bing;
   bing = query_discussion_item(club_name, id);
   if (bing) {
      if (_discussion_items[bing->discuss_type & CLUB_DISCUSS_TYPE_MASK]) {
         return send_discuss_message(club_name,
                                     CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION,
                                     bing,
                                     0,
                                     0);
      }
   }
   return 0;
}
int is_valid_discussion_item_type(int type) {
   if (_discussion_items[type & CLUB_DISCUSS_TYPE_MASK]) {
      return 1;
   }
   return 0;
}
int add_discussion_item(string club,
                        int type,
                        string added_by,
                        string name,
                        string info,
                        string *choices,
                        int time_to_finish,
                        mixed extra_data) {
   class discussion_idea bing;
   class election_info frog;
   int max_id;
   string choice;
   int i;
   if (is_elected_club(club) &&
       is_valid_discussion_item_type(type) &&
       time_to_finish > 0 &&
       (is_member_of(club, lower_case(added_by)) ||
        added_by == CLUB_CONTROLLER_MEMBER ||
        normalise_name(added_by) == normalise_name(club))) {
      frog = (class election_info)query_elected_info(club);
      if (!pointerp(frog->discussion)) {
         frog->discussion = ({ });
      }
      bing = new(class discussion_idea);
      max_id = 0;
      for (i = 0; i < sizeof(frog->discussion); i++) {
         if (frog->discussion[i]->id > max_id) {
            max_id = frog->discussion[i]->id;
         }
      }
      bing->id = max_id + 1;
      bing->time_added = time();
      bing->time_finish = time() + time_to_finish;
      bing->discuss_type = type;
      bing->added_by = added_by;
      bing->name = name;
      bing->information = info;
      bing->choices = ([ ]);
      foreach (choice in choices) {
         bing->choices[lower_case(choice)] = 0;
      }
      bing->voted = ({ });
      bing->optional_data = extra_data;
      if (send_discuss_message(club,
                               CLUB_DISCUSS_MESSAGE_VERIFY,
                               bing,
                               0,
                               0)) {
         frog->discussion += ({ bing });
         set_club_changed(club);
         return 1;
      }
      return 0;
   }
   return 0;
}
class discussion_idea query_discussion_item_by_type(string club_name,
                                                    int type,
                                                    class discussion_idea idea) {
   class election_info frog;
   class discussion_idea bing;
   int found;
   frog = (class election_info)query_elected_info(club_name);
   if (frog) {
      if (!idea) {
         found = 1;
      }
      foreach (bing in frog->discussion) {
         if (found) {
            if ((bing->discuss_type & CLUB_DISCUSS_TYPE_MASK) == type) {
               return bing;
            }
         } else if (bing == idea) {
            found = 1;
         }
      }
   }
   return 0;
}
string *query_discussion_choices(string club_name,
                             int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      return keys(frog->choices);
   }
   return ({ });
}
string query_discussion_added_by(string club_name,
                                 int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog &&
       frog->added_by) {
      return frog->added_by;
   }
   return CLUB_UNKNOWN_MEMBER;
}
int query_discussion_time_finish(string club_name,
                                 int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      return frog->time_finish;
   }
   return 0;
}
int query_discussion_time_added(string club_name,
                                 int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      return frog->time_finish;
   }
   return 0;
}
mixed query_discussion_optional_data(string club_name,
                                     int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      return frog->optional_data;
   }
   return 0;
}
mapping query_discussion_nomination(string club_name,
                                    int id) {
   class discussion_idea frog;
   mapping stuff;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      stuff = send_discuss_message(club_name,
                                   CLUB_DISCUSS_MESSAGE_NOMINATION_QUERY,
                                   frog,
                                   0,
                                   0);
      if (stuff) {
         return stuff;
      }
      return ([ ]);
   }
   return ([ ]);
}
int is_discuss_person_nominated(string club_name,
                               int id,
                               string nominator,
                               string nominated) {
   mapping bing;
   bing = query_discussion_nomination(club_name, id);
   if (bing[nominated]) {
      if (member_array(nominator, bing[nominated]) != -1) {
         return 1;
      }
   }
   return 0;
}
int is_committee_discussion_item(string club_name,
                                 int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
       if (frog->discuss_type & CLUB_DISCUSS_OPEN) {
          return 0;
       }
       return 1;
   }
   return 0;
}
int is_no_quorum_discussion_item(string club_name,
                                 int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
       if (frog->discuss_type & CLUB_DISCUSS_NO_QUORUM) {
          return 1;
       }
       return 0;
   }
   return 0;
}
int is_discussion_item_finished(string club_name,
                                int id) {
   class discussion_idea frog;
   string *committee;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      if (is_committee_discussion_item(club_name, id)) {
         committee = query_committee(club_name);
         if (committee &&
             !sizeof(committee - frog->voted)) {
            return 1;
         }
      }
      if (frog->time_finish < time()) {
         return 1;
      }
   }
   return 0;
}
int query_discussion_item_quorum_number(string club_name,
                                        int id) {
   class discussion_idea bing;
   int num;
   bing = query_discussion_item(club_name, id);
   if (is_no_quorum_discussion_item(club_name, id)) {
      return 0;
   } else if (is_committee_discussion_item(club_name, id)) {
      num = sizeof(filter(query_committee(club_name),
                          (: $1 != CLUB_UNKNOWN_MEMBER &&
                             PLAYER_HANDLER->test_active($1) :)));
      return (num * CLUB_DISCUSS_QUORUM_COMMITTEE / 100);
   } else {
      num = sizeof(filter(query_members(club_name),
                          (: $1 != CLUB_UNKNOWN_MEMBER &&
                             PLAYER_HANDLER->test_active($1, 1) :)));
      return (num * CLUB_DISCUSS_QUORUM_OPEN / 100);
   }
   return 0;
}
int query_discussion_item_number_voted(string club_name,
                                       int id) {
   class discussion_idea bing;
   bing = query_discussion_item(club_name, id);
   if (bing) {
      return sizeof(bing->voted);
   }
   return 0;
}
int is_discussion_item_quorum(string club_name,
                              int id) {
   class discussion_idea bing;
   int num;
   bing = query_discussion_item(club_name, id);
   if (bing) {
      num = query_discussion_item_quorum_number(club_name, id);
      if (sizeof(bing->voted) >= num) {
         return 1;
      }
   }
   return 0;
}
int is_valid_discussion_choice(string club_name,
                               int id,
                               string choice) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   choice = lower_case(choice);
   if (frog &&
       !undefinedp(frog->choices[choice])) {
      return 1;
   }
   return 0;
}
int is_discuss_votable(string club_name,
                       int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      if (send_discuss_message(club_name,
                               CLUB_DISCUSS_MESSAGE_TYPE,
                               frog,
                               0,
                               0) == CLUB_DISCUSS_MESSAGE_TYPE_VOTE) {
         return 1;
      }
   }
   return 0;
}
int is_discuss_nominateable(string club_name,
                            int id) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog) {
      if (send_discuss_message(club_name,
                               CLUB_DISCUSS_MESSAGE_TYPE,
                               frog,
                               0,
                               0) == CLUB_DISCUSS_MESSAGE_TYPE_NOMINATE) {
         return 1;
      }
   }
   return 0;
}
int can_reference_discussion_item(string club_name,
                                  int id,
                                  string person) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog &&
       (!is_committee_discussion_item(club_name, id) ||
        holds_any_position_of(club_name, person))) {
      return 1;
   }
   return 0;
}
int has_voted_for_discussion_item(string club_name,
                                  int id,
                                  string person) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog &&
       member_array(person, frog->voted) != -1) {
      return 1;
   }
   return 0;
}
int vote_for_discussion_item(string club_name,
                             int id,
                             string person,
                             string choice) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   choice = lower_case(choice);
   if (frog &&
       can_reference_discussion_item(club_name, id, person) &&
       !has_voted_for_discussion_item(club_name, id, person) &&
       is_valid_discussion_choice(club_name, id, choice) &&
       is_discuss_votable(club_name, id)) {
      frog->choices[choice]++;
      frog->voted += ({ person });
      set_club_changed(club_name);
      return 1;
   }
   return 0;
}
int nominate_discussion_item(string club_name,
                             int id,
                             string nominator,
                             string nominated) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog &&
       is_member_of(club_name, nominator) &&
       is_member_of(club_name, nominated) &&
       is_discuss_nominateable(club_name, id)) {
      if (!is_creator_club(club_name) &&
          PLAYER_HANDLER->test_creator(nominated)) {
         return 0;
      }
      if (send_discuss_message(club_name,
                               CLUB_DISCUSS_MESSAGE_NOMINATION,
                               frog,
                               nominator,
                               nominated)) {
         set_club_changed(club_name);
         return 1;
      }
   }
   return 0;
}
int withdraw_discussion_item(string club_name,
                             int id,
                             string withdraw) {
   class discussion_idea frog;
   frog = query_discussion_item(club_name, id);
   if (frog &&
       is_member_of(club_name, withdraw) &&
       is_discuss_nominateable(club_name, id)) {
      if (send_discuss_message(club_name,
                               CLUB_DISCUSS_MESSAGE_WITHDRAW,
                               frog,
                               withdraw,
                               withdraw)) {
         set_club_changed(club_name);
         return 1;
      }
   }
   return 0;
}
protected int remove_discussion_item(string club_name,
                                     class discussion_idea item) {
   class election_info bing;
   int i;
   bing = (class election_info)query_elected_info(club_name);
   if (bing) {
      for (i = 0; i < sizeof(bing->discussion); i++) {
         if (bing->discussion[i] == item) {
            bing->discussion = bing->discussion[0..i - 1] +
               bing->discussion[i + 1..];
            set_club_changed(club_name);
            return 1;
         }
      }
   }
   return 0;
}
int complete_discussion_item(string club_name,
                             int id) {
   class discussion_idea frog;
   class election_info bing;
   int ret;
   frog = query_discussion_item(club_name, id);
   bing = (class election_info)query_elected_info(club_name);
   if (frog &&
       is_discussion_item_finished(club_name, id)) {
      if (is_discussion_item_quorum(club_name, id)) {
         if (_discussion_items[frog->discuss_type & CLUB_DISCUSS_TYPE_MASK]) {
            send_broadcast_message(club_name,
                                   "Finished discussion item: " +
                                   send_discuss_message(club_name,
                                                        CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION,
                                                        frog,
                                                        0,
                                                        0) +
                                   " see archives for results.");
            send_discuss_message(club_name,
                                 CLUB_DISCUSS_MESSAGE_COMPLETE,
                                 frog,
                                 0,
                                 0);
         } else {
            ret = -1;
            do_mail_committee(club_name,
                              "Completed vote",
                              "The completed vote on:\n" +
                              "Discussion type " +
                               (frog->discuss_type & CLUB_DISCUSS_TYPE_MASK) +
                              " failed due to major internal messes.\n");
         }
      } else {
         if (_discussion_items[frog->discuss_type & CLUB_DISCUSS_TYPE_MASK]) {
            do_mail_committee(club_name,
                              "Completed vote",
                              "The completed vote on:\n" +
                              query_discussion_item_long_description(club_name,
                                                                     id) +
                              "\n\nDid not have quorum, only " +
                              sizeof(frog->voted) + " people voted.\n");
         } else {
            do_mail_committee(club_name,
                              "Completed vote",
                              "The completed vote on:\n" +
                              "Discussion type " + (frog->discuss_type & CLUB_DISCUSS_TYPE_MASK) +
                              " failed due to major internal messes.\n");
         }
         ret = -1;
      }
      remove_discussion_item(club_name, frog);
   }
   return ret;
}
protected mixed send_discuss_message(string club_name,
                                     int message,
                                     class discussion_idea item,
                                     string arg1,
                                     string arg2) {
   return evaluate(_discussion_items[item->discuss_type &
                                           CLUB_DISCUSS_TYPE_MASK],
                   message,
                   club_name,
                   item,
                   arg1,
                   arg2);
}
protected void broadcast_discuss_message(string club_name,
                                         int message,
                                         string arg1,
                                         string arg2) {
   class discussion_idea frog;
   class election_info bing;
   bing = (class election_info)query_elected_info(club_name);
   foreach (frog in bing->discussion) {
      if (send_discuss_message(club_name,
                               message,
                               frog,
                               arg1,
                               arg2)) {
         set_club_changed(club_name);
      }
   }
}
int remove_member(string name,
                  string member) {
   if (::remove_member(name, member)) {
      if (is_elected_club(name)) {
         broadcast_discuss_message(name,
                                   CLUB_DISCUSS_MESSAGE_REMOVE_MEMBER,
                                   member,
                                   0);
      }
      return 1;
   }
   return 0;
}
int change_position_name_in_club(string name,
                                 string position,
                                 string new_position) {
   if (::change_position_name_in_club(name, position, new_position)) {
      if (is_elected_club(name)) {
         broadcast_discuss_message(name,
                                   CLUB_DISCUSS_MESSAGE_CHANGE_POSITION,
                                   position,
                                   new_position);
      }
      return 1;
   }
   return 0;
}
int remove_position_in_club(string name,
                            string position) {
   if (::remove_position_in_club(name, position)) {
      if (is_elected_club(name)) {
         broadcast_discuss_message(name,
                                   CLUB_DISCUSS_MESSAGE_REMOVE_POSITION,
                                   position,
                                   0);
      }
      return 1;
   }
   return 0;
}
int set_position_holder(string club_name,
                                  string position,
                                  string person) {
   if (::set_position_holder(club_name, position, person)) {
      if (person == CLUB_UNKNOWN_MEMBER) {
         add_discussion_item(club_name,
                             CLUB_DISCUSS_NOMINATION |
                                CLUB_DISCUSS_NO_QUORUM |
                                CLUB_DISCUSS_OPEN,
                             CLUB_CONTROLLER_MEMBER,
                             position,
                             "Position became vacant.\n",
                             ({ }),
                             7 * (24 * 60 * 60),
                             0);
      }
      return 1;
   }
   return 0;
}
int start_election(string name) {
   class discussion_idea womble;
   class election_info data;
   int type;
   if (::start_election(name)) {
      data = (class election_info)query_elected_info(name);
      foreach (womble in data->discussion) {
         type = womble->discuss_type & CLUB_DISCUSS_TYPE_MASK;
         if (type == CLUB_DISCUSS_NOMINATION ||
             type == CLUB_DISCUSS_ELECTION) {
            remove_discussion_item(name, womble);
            set_club_changed(name);
         }
      }
      return 1;
   }
   return 0;
}
protected void check_elected_information(string name,
                                        string member,
                                        int startup) {
   class election_info data;
   class discussion_idea frog;
   string pos;
   ::check_elected_information(name, member, startup);
   data = (class election_info)query_elected_info(name);
   if (data) {
      foreach (frog in data->discussion) {
         if (is_discussion_item_finished(name, frog->id)) {
            complete_discussion_item(name, frog->id);
            set_club_changed(name);
         } else if (frog->discuss_type == CLUB_DISCUSS_NOMINATION ||
                    frog->discuss_type == CLUB_DISCUSS_ELECTION) {
           if (!is_election_in_progress(name) &&
               !is_nomination_in_progress(name)) {
               frog->discuss_type |= CLUB_DISCUSS_OPEN |
                                     CLUB_DISCUSS_NO_QUORUM;
               set_club_changed(name);
            } else {
               remove_discussion_item(name, frog);
            }
         }
      }
      foreach (pos, member in data->positions) {
         if (member == CLUB_UNKNOWN_MEMBER &&
             !is_election_in_progress(name) &&
             !is_nomination_in_progress(name) &&
             !is_nomination_or_election_being_discussed(name, pos)) {
            setup_by_election(name,
                              pos,
                              "Automatic after the position is declared "
                              "vacant.\n");
            set_club_changed(name);
         }
      }
   }
}
int setup_by_election(string club,
                      string position,
                      string info) {
   return add_discussion_item(club,
                              CLUB_DISCUSS_NOMINATION |
                                 CLUB_DISCUSS_OPEN |
                                 CLUB_DISCUSS_NO_QUORUM,
                              CLUB_CONTROLLER_MEMBER,
                              position,
                              info,
                              ({ }),
                              7 * 24 * 60 * 60,
                              0);
}