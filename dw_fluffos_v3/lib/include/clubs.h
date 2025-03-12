#ifndef __CLUBS_H
#define __CLUBS_H
#include <am_time.h>
#define CLUB_PERSONAL  0
#define CLUB_ELECTED   1
#define CLUB_FAMILY    2
#define CLUB_ARRAY ({"Personal", "Elected", "Family"})
#define CLUB_DEFAULT_ACCOUNT_NAME "default"
#define CLUB_TYPE_MASK (15)
#define CLUB_FLAGS_MASK (~CLUB_TYPE_MASK)
#define CLUB_SECRET_FLAG 16
#define CLUB_COST_PER_YEAR (400 * 50)
#define CLUB_STARTUP_COST (400 * 100)
#define FAMILY_STARTUP_COST (400 * 300)
#define FAMILY_COST_PER_YEAR (400 * 300)
#define CLUB_COST_PER_MEMBER_PER_YEAR 100
#define FAMILY_COST_PER_MEMBER_PER_YEAR 200
#define CLUB_COST_INSIGNIA (400)
#define CLUB_MINIMUM_ELECTED_MEMBERS 10
#define CLUB_MAXIMUM_ELECTED_MEMBERS 30
#define CLUB_HANDLER "/obj/handlers/club_handler"
#define CLUB_BADGE "/obj/misc/club_badge"
#define CLUB_INVALID_TIME 0
#define CLUB_TIMEOUT (8 * 7 * 24 * 60 * 60)
#define CLUB_PAY_PERIOD (AM_SECONDS_PER_HALF_YEAR / 4)
#define CLUB_ELECTION_PERIOD (AM_SECONDS_PER_HALF_YEAR * 2)
#define CLUB_MINIMUM_ELECTION_PERIOD (AM_SECONDS_PER_HALF_YEAR / 2)
#define CLUB_NOMINATION_TIME (7 * 24 * 60 * 60)
#define CLUB_ELECTION_TIME (7 * 24 * 60 * 60)
#define CLUB_RESPOND_TYPE "club"
#define CLUB_FAMILY_RESPOND_TYPE "family"
#ifndef __CLUBS_H_NO_CLASSES
class family_response_data {
   string family;
   string relationship;
}
class relationship_data {
   string related_to;
   string relationship;
}
#endif
#define CLUB_TRANSACTION_INSIGNIA 1
#define CLUB_TRANSACTION_DEPOSIT 2
#define CLUB_TRANSACTION_UPKEEP 3
#define CLUB_TRANSACTION_START_BALANCE 4
#define CLUB_TRANSACTION_WITHDRAWL 5
#define CLUB_TRANSACTION_TRANSFER 6
#ifndef __CLUBS_H_NO_CLASSES
class club_transaction {
   string who;
   int amount;
   int transaction_type;
   int date;
   string information;
}
class club_archive {
   int archive_date;
   string subject;
   string matter;
}
#endif
#define CLUB_MESSAGE_EMOTE_INDEX 1
#define CLUB_MESSAGE_MESSAGE_INDEX 0
#define CLUB_MAX_NAME_LEN 40
#define MAX_FAMILY_NAME_LEN 15
#define CLUB_ROOM_CLUB_OR_FAMILY 0
#define CLUB_ROOM_CLUB_ONLY   1
#define CLUB_ROOM_FAMILY_ONLY 2
#ifndef __CLUBS_H_NO_CLASSES
class discussion_idea {
   int id;
   int time_added;
   int time_finish;
   int discuss_type;
   string added_by;
   string name;
   string information;
   mapping choices;
   string *voted;
   mixed optional_data;
}
#endif
#define CLUB_DISCUSS_OPEN 0x800000
#define CLUB_DISCUSS_NO_QUORUM 0x400000
#define CLUB_DISCUSS_TYPE_MASK 0xff
#define CLUB_DISCUSS_ELECTION      1
#define CLUB_DISCUSS_DESCRIPTION   2
#define CLUB_DISCUSS_MEMO          3
#define CLUB_DISCUSS_NO_CONFIDENCE 4
#define CLUB_DISCUSS_NEW_POSITION 5
#define CLUB_DISCUSS_POSITION_NAME 6
#define CLUB_DISCUSS_SECRET_TYPE 7
#define CLUB_DISCUSS_MEMBER_REMOVE 8
#define CLUB_DISCUSS_POSITION_REMOVE 9
#define CLUB_DISCUSS_NOMINATION 10
#define CLUB_DISCUSS_FUNCTION 11
#define CLUB_DISCUSS_CREATE_ACCOUNT 12
#define CLUB_DISCUSS_REMOVE_ACCOUNT 13
#define CLUB_DISCUSS_YES_CHOICE "yes"
#define CLUB_DISCUSS_NO_CHOICE "no"
#define CLUB_DISCUSS_ABSTAIN_CHOICE "abstain"
#define CLUB_DISCUSS_MESSAGE_VERIFY            1
#define CLUB_DISCUSS_MESSAGE_COMPLETE          2
#define CLUB_DISCUSS_MESSAGE_SHORT_DESCRIPTION 3
#define CLUB_DISCUSS_MESSAGE_LONG_DESCRIPTION  4
#define CLUB_DISCUSS_MESSAGE_NOMINATION        5
#define CLUB_DISCUSS_MESSAGE_TYPE              6
#define CLUB_DISCUSS_MESSAGE_REMOVE_MEMBER     7
#define CLUB_DISCUSS_MESSAGE_CHANGE_POSITION   8
#define CLUB_DISCUSS_MESSAGE_NOMINATION_QUERY  9
#define CLUB_DISCUSS_MESSAGE_REMOVE_POSITION   10
#define CLUB_DISCUSS_MESSAGE_WITHDRAW          11
#define CLUB_DISCUSS_MESSAGE_TYPE_VOTE         0
#define CLUB_DISCUSS_MESSAGE_TYPE_NOMINATE     1
#define CLUB_DISCUSS_FUNCTION_OBJECT     0
#define CLUB_DISCUSS_FUNCTION_FUNCTION   1
#define CLUB_MAX_POSITION_NAME 30
#define CLUB_UNKNOWN_MEMBER "unknown"
#define CLUB_CONTROLLER_MEMBER "Club Controller"
#endif