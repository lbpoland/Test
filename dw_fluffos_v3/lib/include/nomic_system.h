#ifndef __NOMIC_SYSTEM__
#define __NOMIC_SYSTEM__
#define NOMIC_HANDLER "/obj/handlers/player_council"
#ifndef NOMIC_SYSTEM_NO_CLASSES
class nomic_amendment {
   string amender;
   string text;
   int date_amended;
}
class nomic_rule {
   int id;
   int type;
   int date_created;
   string creator;
   string text;
   class nomic_amendment* amendments;
}
class nomic_area {
   int* new_type_num;
   class nomic_rule* rules;
}
class nomic_comment {
   string text;
   string commenter;
   int date_commented;
}
class nomic_motion {
   int identifier;
   int motion_type;
   class nomic_rule rule;
   int new_rule_type;
   class nomic_comment* comments;
   int yes_votes;
   int no_votes;
   int abstain_votes;
   string* voted;
   int state;
   int date_added;
   int date_event;
   string added_by;
}
#endif
#ifdef NOMIC_SYSTEM_CASE_CLASSES
class nomic_case_note {
   int id;
   string person;
   string text;
   int time_created;
}
class nomic_case_event {
   int type;
   string mess;
   string person;
   int event_time;
   mixed data;
}
class nomic_case {
   int id;
   string opener;
   string short;
   string* people;
   int* notes;
   class nomic_case_event* events;
   int time_opened;
}
#endif
#define NOMIC_DEFAULT_TYPE_NUMS ({ 100, 300, 2000 })
#define NOMIC_TYPE_IMMUTABLE 0
#define NOMIC_TYPE_GENERAL   1
#define NOMIC_TYPE_CITIZEN   2
#define NOMIC_ERROR -1
#define NOMIC_MOTION_TYPE_RULE_ADD     1
#define NOMIC_MOTION_TYPE_RULE_AMEND   2
#define NOMIC_MOTION_TYPE_RULE_MOVE    3
#define NOMIC_MOTION_TYPE_RULE_REMOVE  3
#define NOMIC_STATE_COUNCIL_REVIEW 1
#define NOMIC_STATE_COUNCIL_VOTE   2
#define NOMIC_STATE_CITIZEN_VOTE   3
#define NOMIC_VOTE_YES 1
#define NOMIC_VOTE_NO  2
#define NOMIC_VOTE_ABSTAIN  3
#define NOMIC_CASE_EVENT_CLOSE  1
#define NOMIC_CASE_EVENT_APPEAL 2
#define NOMIC_CASE_EVENT_ADD_PERSON 3
#define NOMIC_CASE_EVENT_REMOVE_PERSON 4
#define NOMIC_RULE_DEFAULT_DIR "/save/nomic/default/"
#define NOMIC_PUNISHMENT_DIR "/std/room/punishments/"
#define NOMIC_PUNISHMENT_DOCS_DIR "/doc/punishments/"
#define NOMIC_SYSTEM_SAVE_FILE "/save/nomic/main.o"
#define NOMIC_CASE_SAVE "/save/nomic/"
#define NOMIC_CASE_APPEAL_TIME (14 * 60 * 60 * 24)
#define NOMIC_SYSTEM_ADMINISTRATOR_NAME "Administration"
#endif