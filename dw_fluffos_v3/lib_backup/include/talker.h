class talker_args {
    int status;
    string *channels;
    int verbose;
    int local_echo;
    mixed colour;
}
class cache_data {
    int playtester;
    int talker_quest;
    int apex_member;
}
#define LIST_FORMAT "   %12-s %*-=s\n"
#define HIST "/obj/handlers/hist_handler"
#define ON_PATTERN "{on|off}"
#define VERBOSE_PATTERN "{brief|verbose}"
#define CHANNEL_PATTERN "channels"
#define NEW_CHANNEL_PATTERN "<word'new channel'>"
#define SET_COLOUR_FULL_PATTERN "colour <word'channel'> <string'colour'> for <direct:object'talker'>"
#define SET_COLOUR_PATTERN "colour <word'channel'> <string'colour'>"
#define COLOUR_LIST "colour list"
#define TOGGLE_COLOUR_PATTERN "colour"
#define COLOUR_ON_OFF_PATTERN "colour {on|off|reset}"
#define DELETE_CHANNEL_PATTERN "delete <word'channel'>"
#define HISTORY_PATTERN "history"
#define HISTORY_CHANNEL_PATTERN "history <word'channel'>"
#define LIST_PATTERN "list"
#define LIST_CHANNEL_PATTERN "list <word'channel'>"
#define LIST_CHANNEL_PATTERN_BRIEF "list brief <word'channel'>"
#define ECHO_PATTERN "echo {on|off}"
#define DEFAULT_COLOUR "%^BOLD%^%^GREEN%^"
#define DEFAULT_COLOUR_SETTINGS ([ "default" : DEFAULT_COLOUR, "status" : "on" ])
#define DEFAULT_COLOUR_WITH(n) ([ "default" : (n), "status" : "on" ])