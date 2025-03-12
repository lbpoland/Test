#include <board.h>
#include <mail.h>
#include <clubs.h>
#include <player_handler.h>
#define T_MIN 0
#define T_MAX 1
#define T_TIMEOUT 2
#define DEFAULT_MIN 10
#define DEFAULT_MAX 80
#define DEFAULT_TIMEOUT 14
#define ARCHIVE_DIR "/open/boards/"
#define MAX_ARCHIVE_SIZE 1048576
#define BACKUPS_DIR "/save/board_backups/"
#define NEWSRC_SAVE_DIR "/save/newsrc/"
#define BACKUP_TIME_OUT (7 * 24 * 60 * 60)
#define BOARD_HANDLE_VERSION 1
#ifdef USE_RAMDISK
#define CACHE_SIZE 10
#else
#define CACHE_SIZE 250
#endif
#define CACHE_TIMEOUT 1800
#define NEWSRC_SAVE_DELAY 300
class newsrc {
  int cached;
  int changed;
  mapping newsrc;
  string *kill;
  string *board_order;
}
class read_access_cache {
   int read_time;
   int read_access;
}
private int num;
private int board_version;
private mapping archives;
private mapping boards;
private mapping priv;
private mapping security;
private mapping timeouts;
private nosave string *_allowed_objects;
private nosave mapping message_cache;
private nosave mapping _newsrc_cache;
private nosave int total_reads, cache_hits, ram_hits, clean_out;
private nosave int _ram_exists;
private nosave int _newsrc_reads, _newsrc_cache_hits;
private mapping _idiots;
private nosave mapping _read_access_cache;
string query_archive(string board);
protected int zap_message(string board, int num, string name);
int can_delete_message(string board, int off, string pname);
void save_me();
void create() {
  int number;
  int last;
  string line;
  string *lines;
  seteuid(master()->creator_file(file_name(this_object())));
  num = 1;
  boards = ([ ]);
  security = ([ ]);
  _read_access_cache = ([ ]);
  priv = ([ ]);
  timeouts = ([ ]);
  archives = ([ ]);
  message_cache = ([ ]);
  _newsrc_cache = ([ ]);
  _allowed_objects = ({
    BOARD_HAND,
      "/obj/misc/board",
      "/obj/misc/board_mas",
      "/obj/handlers/applications_handler",
      "/w/ceres/board",
      "/w/ceres/board_mas",
      "/www/boards",
      "/www/secure/nboards",
      "/obj/handlers/club_handler",
      "/obj/handlers/deity_handler",
      "/obj/handlers/folder_handler",
      "/obj/handlers/playtesters",
      "/obj/handlers/error_tracker",
      "/obj/handlers/twiki",
      "/d/forn/utils/error_tracker",
      "/d/forn/handlers/peer_review",
      "/d/sur/utils/error_tracker",
      "/d/cwc/utils/error_tracker",
      "/d/Ankh-Morpork_dev/utils/error_tracker",
      "/d/liaison/utils/error_tracker",
      "/d/am/utils/error_tracker",
      "/d/guilds/priests/items/desk",
      "/d/ram/error_tracker",
      "/d/ram/cool/bank",
      "/d/special/error_tracker",
      "/d/klatch/utils/error_tracker",
      "/d/guilds/error_tracker",
      "/d/special/utils/error_tracker",
      "/d/am/patrician/pat_applications",
      "/d/am/patrician/pat_complaints",
      "/cmds/player/news",
      "/cmds/player/apply",
      "/d/guilds/assassins/Ankh-Morpork/admin/vote_room",
      "/d/special/player_shops/tarnach's_office",
      "/std/shops/player_shop/office",
      "/d/playtesters/handlers/applications",
      "/d/guilds/warriors/Ankh-Morpork/voting_booth",
      "/secure/cmds/creator/errors",
      "/obj/handlers/player_council",
      "/d/guilds/wizards/utils/board_hand",
      "/obj/handlers/complaints_handler",
      "/obj/handlers/project_management",
      "/d/guilds/thieves/Ankh-Morpork/rooms/ground/voting_booth",
      "/d/underworld/utils/error_tracker"
      });
  _idiots = ([ ]);
  if (file_size(BOARD_FILE +".gz") > 0) {
     unguarded((: cp, BOARD_FILE +".gz", BACKUPS_DIR +"boards."+ time() :));
  }
  lines = unguarded((: get_dir, BACKUPS_DIR +"boards.*" :));
  if ( sizeof( lines ) > 6 ) {
    last = time() - BACKUP_TIME_OUT;
    foreach(line in lines) {
      sscanf(line, "boards.%d", number);
      if (number < last)
        unguarded((: rm, BACKUPS_DIR + line :));
    }
  }
  if(!unguarded((: restore_object, BOARD_FILE+".gz" :)))
    unguarded((: restore_object, BOARD_FILE :));
  call_out("expire_boards", 5);
}
private string get_filename(string board, int num) {
   string fixed_board;
   fixed_board = replace(board, ({" ", "_", "'", ""}));
   return BOARD_DIR + fixed_board + "/" + num;
}
private string get_ram_filename(string board, int num) {
   string fixed_board;
   fixed_board = replace(board, ({" ", "_", "'", ""}));
   if(!_ram_exists) {
     _ram_exists = file_size(BOARD_RAM_DIR);
   }
   if(_ram_exists == -2)
     return BOARD_RAM_DIR + fixed_board + "/" + num;
   else
     return BOARD_DIR + fixed_board + "/" + num;
}
string *query_boards() {
   return keys(boards);
}
int is_board(string board) {
   if (boards[board]) {
      return 1;
   }
   return 0;
}
private int query_lord(string str) {
   return (int)master()->query_lord(str);
}
int is_idiot(string name) {
   if (!_idiots) {
      _idiots = ([ ]);
   }
   if (_idiots[name]) {
      if (_idiots[name] > time()) {
         return 1;
      }
      map_delete(_idiots, name);
   }
   return 0;
}
void add_idiot(string idiot, int length) {
   _idiots[idiot] = time() + (60 * 60 * 24 * length);
   save_me();
}
int query_idiot(string idiot) {
   return _idiots[idiot];
}
int test_can_read(string board, object previous,
                      string name) {
   int bit;
   int ret;
   if (member_array(base_name(previous), _allowed_objects) == -1 &&
       board != "announcements") {
#ifdef DEBUG
      log_file("BAD_BOARD", ctime(time()) + " (read): [" + board + "] " +
               base_name(previous) +
               sprintf(" (%O)\n", this_player()->query_name()));
#endif
      return 0;
   }
   bit = priv[board] & B_PRIV_TYPE_MASK;
   if (bit == 0) {
      return 1;
   }
   if (_read_access_cache[board] &&
       !undefinedp(_read_access_cache[board][name])) {
      return _read_access_cache[board][name];
   }
   ret = 1;
   if (bit == B_PRIV_ACCESS_RESTRICTED) {
      ret = query_lord(name) ||
         (member_array(name, security[board]) != -1);
   } else if (bit == B_PRIV_ACCESS_RESTRICTED_METHOD) {
      if (query_lord(name)) {
         ret = 1;
      } else {
         if (sizeof(security[board]) == 2) {
            ret = call_other(security[board][1],
                           security[board][0],
                           B_ACCESS_READ,
                           board, previous, name);
         }
      }
   }
   if (!_read_access_cache[board]) {
      _read_access_cache[board] = ([ ]);
   }
   _read_access_cache[board][name] = ret;
   return ret;
}
int test_can_write(string board, object previous,
                      string name) {
  int bit;
  if (is_idiot(name)) {
     return 0;
  }
  if (member_array(base_name(previous), _allowed_objects) == -1) {
#ifdef DEBUG
    log_file("BAD_BOARD", ctime(time()) + " (write): " + base_name(previous) +
                          sprintf(" (%O)\n", this_player()));
#endif
    return 0;
  }
  bit = priv[board] & B_PRIV_TYPE_MASK;
  if (bit == B_PRIV_ACCESS_RESTRICTED_FILE) {
    return member_array(base_name(previous), security[board]) != -1;
  }
  if (bit == B_PRIV_ACCESS_RESTRICTED_METHOD) {
    if (query_lord(name)) {
      return 1;
    }
    if (sizeof(security[board]) == 2) {
      return call_other(security[board][1],
                        security[board][0],
                        B_ACCESS_WRITE,
                        board, previous, name);
    }
    return 0;
  }
  if (bit == B_PRIV_ACCESS_RESTRICTED ||
      bit == B_PRIV_READ_ONLY) {
    return query_lord(name) ||
           (member_array(name, security[board]) != -1);
  }
  return 1;
}
int test_can_delete(string board, object previous,
                      string name) {
  int bit;
  if (member_array(base_name(previous), _allowed_objects) == -1) {
#ifdef DEBUG
    log_file("BAD_BOARD", ctime(time()) + " (write): " + base_name(previous) +
                          sprintf(" (%O)\n", this_player()));
#endif
    return 0;
  }
  bit = priv[board] & B_PRIV_TYPE_MASK;
  if (bit == B_PRIV_ACCESS_RESTRICTED_FILE) {
    return query_lord(name) ||
           member_array(base_name(previous), security[board]) != -1;
  }
  if (bit == B_PRIV_ACCESS_RESTRICTED ||
      bit == B_PRIV_READ_ONLY) {
    return query_lord(name) ||
           (member_array(name, security[board]) != -1);
  }
  if (bit == B_PRIV_ACCESS_RESTRICTED_METHOD) {
    if (query_lord(name)) {
      return 1;
    }
    if (sizeof(security[board]) == 2) {
      return call_other(security[board][1],
                        security[board][0],
                        B_ACCESS_DELETE,
                        board, previous, name);
    }
  }
  return query_lord(name);
}
private string query_destination_eaten_note(string  board, object previous,
                                            string name) {
  int bit;
  bit = priv[board] & B_PRIV_TYPE_MASK;
  if (bit == B_PRIV_ACCESS_RESTRICTED_METHOD) {
    if (sizeof(security[board]) == 2) {
      return call_other(security[board][1],
                        security[board][0],
                        B_ACCESS_DELETE,
                        board, previous, name);
    }
  }
  return 0;
}
varargs mixed get_subjects(string name, string person) {
   string pl;
   int bit;
   if (file_name(previous_object()) == BOARD_WEB ||
       file_name(previous_object()) == "/w/ceres/cmds/test") {
      pl = person;
   } else if (this_player()) {
      pl = (string)this_player()->query_name();
   } else {
      pl = "unknown";
   }
   if (!test_can_read(name, previous_object(), pl)) {
      return ({ });
   }
   if (!boards[name] || bit) {
      return ({ });
   }
   return boards[name];
}
string get_message(string board, int num, string person) {
  string name, rname;
  if (file_name(previous_object()) == BOARD_WEB) {
     name = person;
  } else  if (file_name(previous_object())[0..10] !=
              "/obj/misc/board"[0..10]) {
    name = "unknown";
  } else {
    name = (string)this_player()->query_name();
  }
  if(board == "lordboard") {
    catch(log_file("/d/admin/log/LORDBOARD", "%s read by prev %s player %s\n",
                   ctime(time()), base_name(previous_object()),
                   this_player()->query_name()));
  }
  if (!test_can_read(board, previous_object(), name)) {
    return 0;
  }
  if (num < 0 || num >= sizeof(boards[board])) {
    return 0;
  }
  if(!message_cache) {
    message_cache = ([ ]);
  }
  total_reads++;
  if(message_cache[boards[board][num][B_NUM]]) {
    cache_hits++;
    return message_cache[boards[board][num][B_NUM]];
  }
  name = get_filename(board, boards[board][num][B_NUM]);
  if (file_size(name) <= 0) {
    return 0;
  }
  if(!clean_out && sizeof(keys(message_cache)) > CACHE_SIZE)
    clean_out = call_out("clean_cache", 10);
#ifdef USE_RAMDISK
  rname = get_ram_filename(board, boards[board][num][B_NUM]);
  if(rname != name) {
    if(file_size(rname) == -1) {
      unguarded((: cp, name, rname :));
    } else
      ram_hits++;
    name = rname;
  }
#endif
  if(!_ram_exists || _ram_exists == -1) {
    message_cache[boards[board][num][B_NUM]] = unguarded((: read_file, name :));
    return message_cache[boards[board][num][B_NUM]];
  } else {
    return unguarded((: read_file, name :));
  }
}
void clean_cache() {
  int i;
  int count;
  int *list;
  string name;
  count = sizeof(keys(message_cache));
  list = sort_array(keys(message_cache), 0);
  for(i=0; i < (count - CACHE_SIZE); i++) {
    map_delete(message_cache, list[i]);
  }
  foreach(name in keys(_newsrc_cache)) {
    if(!_newsrc_cache[name]->changed &&
       _newsrc_cache[name]->cached < time() - CACHE_TIMEOUT) {
      map_delete(_newsrc_cache, name);
    }
  }
  clean_out = 0;
   foreach (name in keys(_read_access_cache)) {
      _read_access_cache[name] = ([ ]);
   }
}
void save_me() {
  unguarded((: save_object, BOARD_FILE, 2 :));
}
int add_message(string board, string cap_name, string subject, string body,
                int reply_to, class reply_type bing) {
   int test;
   int irp;
   int index;
   string fname;
   string name;
   string from_mess;
   string mail_to;
   class reply_type reply;
   name = lower_case(cap_name);
   if (reply_to) {
      for (index = 0; index < sizeof(boards[board]); index++) {
         if (boards[board][index][B_NUM] == reply_to) {
            if (boards[board][index][B_REPLY_TYPE]) {
               reply = (class reply_type)boards[board][index][B_REPLY_TYPE];
               if (reply->type == B_REPLY_POSTER) {
                  mail_to = boards[board][index][B_NAME];
               } else if (reply->type == B_REPLY_NAMED) {
                  mail_to = reply->data;
               }
               if (mail_to) {
                  MAILER->do_mail_message(mail_to,
                                          name,
                                          subject,
                                          "",
                                          body);
                  return 1;
               }
            }
         }
      }
   }
   if (!test_can_write(board, previous_object(), name)) {
      return 0;
   }
   if (!boards[board] || test) {
      return 0;
   } else {
      boards[board] += ({ ({ subject,
                                cap_name,
                                num++,
                                time(),
                                bing,
                                reply_to }) });
   }
   if (file_name(previous_object())[0..4] == "/www/") {
      from_mess = " [Web post]";
   } else {
      from_mess = "";
   }
   fname = get_filename(board, num-1);
   unguarded((: rm, fname :));
   fname = get_filename(board, num-1);
   unguarded((: write_file, fname, body :));
   save_me();
   message_cache[num-1] = body;
   if (timeouts[board] && timeouts[board][T_MAX] &&
       sizeof(boards[board]) > timeouts[board][T_MAX]) {
      while (sizeof(boards[board]) > timeouts[board][T_MAX]) {
         zap_message(board, 0, 0);
         irp++;
      }
      if ((priv[board] & B_PRIV_TYPE_MASK) ==
          B_PRIV_ACCESS_RESTRICTED_METHOD) {
         if (sizeof(security[board]) == 2) {
            call_other(security[board][1],
                       security[board][0],
                       B_ACCESS_INFORM,
                       board, 0, cap_name, irp);
         }
      }
      if ( !(priv[board] & B_PRIV_NO_INFORM) ) {
         user_event( "inform",
                     sprintf( "%s posts a message to %s and %d message%s in sympathy%s",
                              cap_name, board, irp,
                              ( irp > 1 ? "s explode" : " explodes" ),
                              from_mess ),
                     "message",
                     this_player() );
      }
   } else {
      if ((priv[board] & B_PRIV_TYPE_MASK) ==
          B_PRIV_ACCESS_RESTRICTED_METHOD) {
         if (sizeof(security[board]) == 2) {
            call_other(security[board][1],
                       security[board][0],
                       B_ACCESS_INFORM,
                       board, 0, cap_name, 0);
         }
      }
      if ( !(priv[board] & B_PRIV_NO_INFORM) ) {
         user_event( "inform",
                     sprintf( "%s posts a message to %s%s",
                              cap_name, board, from_mess),
                     "message",
                     this_player() );
      }
   }
   return num-1;
}
int create_board(string board,
                 int priviliges,
                 string person) {
   if (boards[board]) {
      return 0;
   }
   if (!person) {
      person = this_player()->query_name();
   }
   boards[board] = ({ });
   security[board] = ({ person });
   if (priviliges) {
      priv[board] = priviliges;
   }
   save_me();
   return 1;
}
int add_allowed(string board, string name) {
  string nam;
  int board_type;
  board_type = priv[board] & B_PRIV_TYPE_MASK;
  if (sscanf(file_name(previous_object()), "/obj/misc/board%s", nam) != 1) {
    return 0;
  }
  nam = (string)this_player()->query_name();
  if (!test_can_write(board, previous_object(), nam) ||
      (board_type != B_PRIV_ACCESS_RESTRICTED &&
       board_type != B_PRIV_READ_ONLY &&
       board_type != B_PRIV_ACCESS_RESTRICTED_FILE)) {
    return 0;
  }
  if (!PLAYER_HANDLER->test_user(name)) {
    return 0;
  }
  security[board] += ({ name });
  save_me();
  printf("Added %s to the security array for %s.\n",name, board);
  return 1;
}
int remove_allowed(string board, string name) {
  string nam;
  int i;
  int board_type;
  if (sscanf(file_name(previous_object()), "/obj/misc/board%s", nam) != 1) {
    return 0;
  }
  nam = geteuid(previous_object());
  board_type = priv[board] & B_PRIV_TYPE_MASK;
  if (!test_can_write(board, previous_object(), nam) ||
      (board_type != B_PRIV_ACCESS_RESTRICTED &&
       board_type != B_PRIV_READ_ONLY &&
       board_type != B_PRIV_ACCESS_RESTRICTED_FILE)) {
    return 0;
  }
  security[board] = delete(security[board], i, 1);
  save_me();
  printf("Removed %s from the security array for %s.\n", name, board);
  return 1;
}
int set_method_access_call(string board, string method, string name) {
   string pl;
   if (!boards[board] ||
       (priv[board] & B_PRIV_TYPE_MASK) != B_PRIV_ACCESS_RESTRICTED_METHOD) {
      return 0;
   }
   if (this_player()) {
      pl = (string)this_player()->query_name();
   } else {
      pl = "unknown";
   }
   if (query_lord(pl) ||
       file_name(previous_object()) == CLUB_HANDLER) {
      security[board] = ({ method, name });
      save_me();
      return 1;
   }
   return 0;
}
int force_board_method_access_restricted(string board) {
   string pl;
   if (!boards[board]) {
      return 0;
   }
   if (this_player()) {
      pl = (string)this_player()->query_name();
   } else {
      pl = "unknown";
   }
   if (query_lord(pl) ||
       file_name(previous_object()) == CLUB_HANDLER) {
      priv[board] = (priv[board] & ~B_PRIV_TYPE_MASK) |
                    B_PRIV_ACCESS_RESTRICTED_METHOD;
      save_me();
      return 1;
   }
   return 0;
}
protected int zap_message(string board, int off, string name) {
  int num;
  string nam, archive;
  if (off < 0 || off >= sizeof(boards[board])) {
    return 0;
  }
  num = boards[board][off][B_NUM];
  nam = get_filename(board, num);
  archive = query_archive(board);
  if (archive) {
    mixed *stuff;
    stuff = boards[board][off];
    unguarded((: write_file, archive,
               sprintf("\n----\nNote #%d by %s posted at %s\nTitle: '%s'\n\n",
                       off, stuff[B_NAME], ctime(stuff[B_TIME]),
                       stuff[B_SUBJECT])+unguarded((: read_file, nam :)) :));
    if(unguarded( (: file_size, archive :) ) > MAX_ARCHIVE_SIZE)
      unguarded((: rename, archive, archive+"."+time() :));
  }
  boards[board] = delete(boards[board],off,1);
  unguarded((: rm, nam :));
  save_me();
  return 1;
}
int delete_message(string board, int off, string override_name) {
  string nam;
  if (file_name(previous_object()) == "/www/boards") {
    nam = override_name;
  } else {
    nam = this_player()->query_name();
  }
  if (!can_delete_message(board, off, nam)) {
    return 0;
  }
  return zap_message(board, off, nam);
}
int can_delete_message(string board, int off, string pname) {
  if (!boards[board]) {
    return 0;
  }
  if (off >= sizeof(boards[board])) {
    return 0;
  }
  if (!test_can_delete(board, previous_object(), pname) &&
      (lower_case(boards[board][off][B_NAME]) != lower_case(pname))) {
    return 0;
  }
  return 1;
}
string *query_security(string board) {
  string *str;
  str = security[board];
  if (!str) {
    return str;
  }
  return copy(str);
}
int delete_board(string board) {
  string nam;
  if (!boards[board]) {
    return 0;
  }
  nam = geteuid(previous_object());
  if (!query_lord(nam) ||
      file_name(previous_object()) == CLUB_HANDLER) {
    return 0;
  }
  while (sizeof(boards[board])) {
    if (!zap_message(board, 0, 0)) {
        return 0;
    }
  }
  map_delete(boards, board);
  map_delete(security, board);
  map_delete(archives, board);
  map_delete(timeouts, board);
  save_me();
  return 1;
}
string *list_of_boards() {
  return keys(boards);
}
int set_timeout(string board, int timeout) {
  string nam;
  if (!boards[board]) {
    return 0;
  }
  nam = geteuid(previous_object());
  if (!test_can_write(board, previous_object(), nam)) {
    return 0;
  }
  if (!timeouts[board]) {
    timeouts[board] = ({ DEFAULT_MIN, DEFAULT_MAX, timeout });
    return 1;
  }
  timeouts[board][T_TIMEOUT] = timeout;
  save_me();
  printf("Set the automagic timeout to %d days for %s.\n", timeout, board);
  return 1;
}
int set_minimum(string board, int min) {
  string nam;
  if (!boards[board]) {
    return 0;
  }
  nam = geteuid(previous_object());
  if (!test_can_write(board, previous_object(), nam)) {
    return 0;
  }
  if (!timeouts[board]) {
    timeouts[board] = ({ min, DEFAULT_MAX, DEFAULT_TIMEOUT });
    return 1;
  }
  timeouts[board][T_MIN] = min;
  save_me();
  printf("Set the minimum number of messages to %d for %s.\n", min, board);
  return 1;
}
int set_maximum(string board, int max) {
  string nam;
  if (!boards[board]) {
    return 0;
  }
  nam = geteuid(previous_object());
  if (!test_can_write(board, previous_object(), nam)) {
    return 0;
  }
  if (!timeouts[board]) {
    timeouts[board] = ({ DEFAULT_MIN, max, DEFAULT_TIMEOUT });
    return 1;
  }
  timeouts[board][T_MAX] = max;
  save_me();
  printf("Set the maximum number of messages to %d for %s.\n", max, board);
  return 1;
}
int set_archive(string board, string file) {
  string nam;
  if (!boards[board]) {
    return 0;
  }
  nam = geteuid(previous_object());
  if (!test_can_write(board, previous_object(), nam)) {
    return 0;
  }
  archives[board] = file;
  save_me();
  printf("Set the archive file to %s for %s.\n", file, board);
  return 1;
}
int query_timeout(string board) {
  if (!timeouts[board]) {
    return 0;
  }
  return timeouts[board][T_TIMEOUT];
}
int query_minimum(string board) {
  if (!timeouts[board]) {
    return 0;
  }
  return timeouts[board][T_MIN];
}
int query_maximum(string board) {
  if (!timeouts[board]) {
    return 0;
  }
  return timeouts[board][T_MAX];
}
string query_archive(string board) {
  if (!boards[board]) {
    return 0;
  }
  if (undefinedp(archives[board])) {
    return ARCHIVE_DIR+board;
  }
  return archives[board];
}
int query_restricted_access(string board) {
   return (priv[board] & B_PRIV_TYPE_MASK) == B_PRIV_ACCESS_RESTRICTED;
}
int query_restricted_access_file(string board) {
   return (priv[board] & B_PRIV_TYPE_MASK) == B_PRIV_ACCESS_RESTRICTED_FILE;
}
int query_read_only(string board) {
  return (priv[board] & B_PRIV_TYPE_MASK) == B_PRIV_READ_ONLY;
}
int query_no_inform(string board) {
  return priv[board] & B_PRIV_NO_INFORM;
}
int query_privilage(string board) {
   return priv[board];
}
void expire_boards() {
  string nam;
  int tim, num, *val;
  foreach (nam, val in timeouts) {
    num = 0;
    if ((tim = val[T_TIMEOUT]) &&
        (sizeof(boards[nam]) > val[T_MIN]) &&
        ((boards[nam][0][B_TIME]+(tim*(24*60*60))) < time())) {
      while (sizeof(boards[nam]) > val[T_MIN] &&
             boards[nam][0][B_TIME]+(tim*24*60*60) < time()) {
        zap_message(nam, 0, 0);
        num++;
      }
      user_event( "inform", sprintf("Board handler removes %d messages "
                                       "from %s", num, nam), "message");
    }
  }
  if (find_call_out("expire_boards") == -1) {
    call_out("expire_boards", 60*60);
  }
}
int query_prevent_shadow() {
  return 1;
}
int query_num() {
  return num;
}
mixed *stats() {
  if(!total_reads)
    total_reads = 1;
  if(!cache_hits)
    cache_hits = 1;
  if(!ram_hits)
    ram_hits = 1;
  return  ({
    ({ "messages read", total_reads, }),
#ifdef USE_CACHE
      ({ "cache hit percent", (cache_hits * 100) / total_reads, }),
#endif
      ({ "ram hit percent", (ram_hits * 100) / total_reads, }),
      ({ "messages in cache", sizeof(keys(message_cache)), }),
      ({ "newsrc reads", _newsrc_reads, }),
      ({ "newsrc hit percent", (_newsrc_cache_hits * 100) / _newsrc_reads, }),
        ({ "newsrcs in cache", sizeof(keys(_newsrc_cache)), }),
          });
}
void query_cache() {
    printf("%O\n", sort_array(keys(message_cache), 0));
}
int load_newsrc(string player) {
  string fname, board;
  _newsrc_reads++;
  if(_newsrc_cache[player]) {
    _newsrc_cache_hits++;
    return 1;
  }
  fname = NEWSRC_SAVE_DIR+player[0..0]+"/"+player+ ".o";
  if(unguarded( (: file_size($(fname)) :)) > 0) {
    _newsrc_cache[player] =
      unguarded((: restore_variable(read_file($(fname))) :));
    if (arrayp(_newsrc_cache[player]->newsrc)) {
      _newsrc_cache[player]->newsrc = ([ ]);
      if (find_call_out("flush_newsrc") == -1) {
        call_out("flush_newsrc", NEWSRC_SAVE_DELAY);
      }
    }
    return 1;
  } else {
    _newsrc_cache[player] = new(class newsrc,
                                cached : time(),
                                kill : ({ }),
                                newsrc : ([ ]),
                                board_order : ({ }));
    if(PLAYER_HANDLER->test_property(player, NEWS_RC))
      _newsrc_cache[player]->newsrc =
        PLAYER_HANDLER->test_property(player, NEWS_RC);
    if(PLAYER_HANDLER->test_property(player, BOARD_ORDER))
      _newsrc_cache[player]->board_order =
        PLAYER_HANDLER->test_property(player, BOARD_ORDER);
    foreach(board in keys(boards)) {
      if(PLAYER_HANDLER->test_property(player, "news_kill_"+board)) {
        _newsrc_cache[player]->kill += ({ board });
      }
    }
    _newsrc_cache[player]->changed = time();
    if(find_call_out("flush_newsrc") == -1)
      call_out("flush_newsrc", NEWSRC_SAVE_DELAY);
    return 1;
  }
  return 0;
}
void flush_newsrc(int force) {
  string fname, player, board, *board_list;
  object ob;
  board_list = map(keys(boards), (: lower_case($1) :));
  foreach(player in keys(_newsrc_cache)) {
    if(!force && (!_newsrc_cache[player]->changed ||
       (_newsrc_cache[player]->changed > time() - NEWSRC_SAVE_DELAY &&
        !find_object("/obj/shut"))))
      continue;
    fname = NEWSRC_SAVE_DIR + player[0..0] + "/" + player + ".o";
    if(unguarded( (: file_size($(fname)) :)) > 0) {
      _newsrc_cache[player]->newsrc =
        filter(_newsrc_cache[player]->newsrc,
               (: member_array(lower_case($1), $(board_list)) != -1 :));
      if(_newsrc_cache[player]->kill)
        _newsrc_cache[player]->kill =
          filter(_newsrc_cache[player]->kill,
                 (: member_array(lower_case($1), $(board_list)) != -1 :));
      if(_newsrc_cache[player]->board_order)
        _newsrc_cache[player]->board_order =
          filter(_newsrc_cache[player]->board_order,
                 (: member_array(lower_case($1), $(board_list)) != -1 :));
      unguarded( (: write_file($(fname), save_variable(_newsrc_cache[$(player)]),
                               1) :));
    } else if(ob = find_player(player)) {
      unguarded( (: write_file($(fname),
                               save_variable(_newsrc_cache[$(player)]), 1) :));
      ob->remove_property(NEWS_RC);
      ob->remove_property(BOARD_ORDER);
      foreach(board in keys(boards)) {
        ob->remove_property("news_kill_" + lower_case(board));
      }
    } else {
      PLAYER_HANDLER->special_add_property(player, NEWS_RC, _newsrc_cache[player]->newsrc);
    }
    _newsrc_cache[player]->changed = 0;
  }
}
mapping query_newsrc(string player) {
  if(!load_newsrc(player))
    return ([ ]);
  _newsrc_cache[player]->cached = time();
  return _newsrc_cache[player]->newsrc;
}
int set_newsrc(string player, mapping newsrc) {
  if(!load_newsrc(player))
    return 0;
  _newsrc_cache[player]->newsrc = (mapping)newsrc;
  _newsrc_cache[player]->cached = time();
  _newsrc_cache[player]->changed = time();
  if(find_call_out("flush_newsrc") == -1)
    call_out("flush_newsrc", NEWSRC_SAVE_DELAY);
  return 1;
}
int query_killfile(string player, string board) {
  if(!load_newsrc(player))
    return 0;
  _newsrc_cache[player]->cached = time();
  return member_array(board, _newsrc_cache[player]->kill) != -1;
}
int set_killfile(string player, string board) {
  if(!load_newsrc(player))
    return 0;
  if(member_array(board, _newsrc_cache[player]->kill) != -1)
    return 1;
  _newsrc_cache[player]->kill += ({ board });
  _newsrc_cache[player]->changed = time();
  _newsrc_cache[player]->cached = time();
  if(find_call_out("flush_newsrc") == -1)
    call_out("flush_newsrc", NEWSRC_SAVE_DELAY);
  return 1;
}
int remove_killfile(string player, string board) {
  if(!load_newsrc(player))
    return 0;
  if(member_array(board, _newsrc_cache[player]->kill) == -1)
    return 1;
  _newsrc_cache[player]->kill -= ({ board });
  _newsrc_cache[player]->changed = time();
  _newsrc_cache[player]->cached = time();
  if(find_call_out("flush_newsrc") == -1)
    call_out("flush_newsrc", NEWSRC_SAVE_DELAY);
  return 1;
}
string *list_killfile(string player) {
  if(!load_newsrc(player))
    return ({ });
  return _newsrc_cache[player]->kill;
}
string *query_board_order(string player) {
  if(!load_newsrc(player))
    return ({ });
  _newsrc_cache[player]->cached = time();
  if(!_newsrc_cache[player]->board_order)
    return ({ });
  return _newsrc_cache[player]->board_order;
}
int set_board_order(string player, string *new_order) {
  if(!load_newsrc(player))
    return 0;
  _newsrc_cache[player]->board_order = new_order;
  _newsrc_cache[player]->changed = time();
  _newsrc_cache[player]->cached = time();
  if(find_call_out("flush_newsrc") == -1)
    call_out("flush_newsrc", NEWSRC_SAVE_DELAY);
  return 1;
}
void dest_me() {
  flush_newsrc(1);
  destruct(this_object());
}