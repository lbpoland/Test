#ifndef __PLAYERINFO_H
#define __PLAYERINFO_H
class dbentry {
    int     time;
    string  creator;
    string  event;
    string  comment;
    mixed   *extra;
}
class playerinfo {
    string          name;
    int             last_check;
    string          *alts;
    class dbentry   *data;
    string          main_alt;
    string          *old_alts;
    mapping         access_log;
}
#define PLAYERINFO_HANDLER "/obj/handlers/playerinfo"
#define VERBOSE_PI "verbose playerinfo"
#endif