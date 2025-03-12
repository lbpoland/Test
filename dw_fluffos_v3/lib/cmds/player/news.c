#include <board.h>
inherit "/cmds/base";
object board;
string board_name = "announcements";
void do_list(int all);
int do_read(int num);
#define LOGON_LIMIT 10
#define MOST 1
#define ALL 2
#define SOME 0
mixed cmd(string str) {
  int msg;
  switch(str) {
  case "help":
  case "?":
  case "h":
    tell_object( this_player(),
                "Usage:\n"
                "To read next news item type: \"news\".\n"
                "To read a specific news item type: \"news <num>\".\n"
                "To list new news items type: \"news list\".\n"
                "To list all news items type: \"news review\".\n");
    break;
  case "l":
  case "list":
    do_list(MOST);
    break;
  case "r":
  case "review":
    do_list(ALL);
    break;
  default:
    if(str) sscanf(str, "%d", msg);
    do_read(msg);
  }
  return 1;
}
int do_read(int num) {
  mapping news_rc;
  mixed *stuff;
  news_rc = BOARD_HAND->query_newsrc(this_player()->query_name());
  if ( !news_rc ) {
    news_rc = ([ ]);
  }
  stuff = (mixed *)BOARD_HAND->get_subjects(board_name);
  if(!num) {
    num = sizeof(stuff);
    while((num > 0) && (stuff[num - 1][B_TIME] > news_rc[board_name])) {
      num--;
    }
    if(num == sizeof(stuff)) {
      write("No news is good news.\n");
      return 1;
    }
    num++;
  }
  if(num < 0) {
    num = sizeof(stuff) + num + 1;
  }
  if(( num < 1) || (num > sizeof(stuff))) {
    write("No news item of that number.\n");
    return 1;
  }
  num--;
  if(news_rc[ board_name ] < stuff[ num ][ B_TIME ]) {
    news_rc[ board_name ] = stuff[ num ][ B_TIME ];
    BOARD_HAND->set_newsrc(this_player()->query_name(), news_rc);
  }
  this_player()->more_string( "Note #"+ ( num + 1 ) +" posted at " +
        ctime(stuff[num][B_TIME])[0..9] + " Title: \""+
        stuff[ num ][ B_SUBJECT ][ 0 .. (int)this_player()->query_cols() -
       10 ] +"\"\n\n"+ (string)BOARD_HAND->get_message( board_name, num ),
       "[Note "+ ( num + 1 ) +"]" );
  return 1;
}
string the_date(int i) {
  return ctime(i)[4..9];
}
void do_list(int all) {
  int i, newones;
  mixed *stuff;
  string ret;
  mapping news_rc;
  ret = "";
  stuff = (mixed *)BOARD_HAND->get_subjects(board_name);
  if (!sizeof(stuff)) {
    tell_object(this_player(), "No news is good news.\n");
    return;
  }
  news_rc = BOARD_HAND->query_newsrc(this_player()->query_name());
  if (!news_rc) {
    news_rc = ([ ]);
  }
  newones = 0;
  for (i = 0; i < sizeof(stuff); i++) {
    if (news_rc[board_name] < stuff[i][B_TIME]) {
      ret += sprintf("N %2d: %-=*s\n", i+1,
                     (int)this_player()->query_cols()-6,
                     stuff[i][B_SUBJECT]+" ("+the_date(stuff[i][B_TIME])+")");
      newones += 1;
      if (all == SOME) {
        if (newones > LOGON_LIMIT) {
          write("Plus more....\n");
          break;
        }
      }
    } else if(all == ALL) {
      ret += sprintf("  %2d: %-=*s\n", i+1, (int)this_player()->query_cols()-6,
                     stuff[i][B_SUBJECT]+" ("+the_date(stuff[i][B_TIME])+")");
    }
  }
  if(!newones && all != ALL) {
    ret += "\nNo news is good news.\n";
  }
  if (all == SOME) {
    ret += "\nUse 'news list' for all new news items and 'news review' for all news times.\n";
  }
  this_player()->more_string( ret, "News" );
}