#include <board.h>
#include <db.h>
#include <config.h>
#include <project_management.h>
#define HELPER "/obj/handlers/finderror_helper"
inherit "/global/path";
private void finished_count_errors( object player, int status, mixed data );
private string domain = "unset";
private string _board;
private string tracker_name = "generic error tracker";
private string *other_dirs = ({ });
private int period = 604800;
private int nexttime;
private nosave mapping _messages;
private nosave string *_queue;
private nosave object _tester;
private nosave string _save_file;
private nosave int starttime;
#define ERROR_INDEX 0
#define TYPO_INDEX 1
#define IDEA_INDEX 2
#undef OLD_SYTEM
void do_the_work();
protected void save_me()
{
   if (domain != "unset" && _save_file) {
      unguarded( (: save_object, _save_file, 0 :) );
   }
}
void create()
{
   int retval;
   _messages = ([ ]);
   _tester = 0;
   seteuid(master()->creator_file(file_name()));
   _save_file = file_name();
   if (catch(retval = unguarded((: restore_object, _save_file, 1 :))) ||
         !retval) {
      string temp;
      temp = "/save/" + replace(file_name()[1..], "/", "_");
      if (catch(retval = unguarded((: restore_object, temp, 1 :))) ||
            !retval) {
         if (catch(save_me())) {
            _save_file = temp;
         }
      } else {
         _save_file = temp;
      }
   }
   if (!retval) {
      nexttime = 0;
   }
   if (nexttime < time()) {
      do_the_work();
   } else {
      call_out("do_the_work", nexttime - time());
   }
}
void set_board(string board) {
   _board = board;
}
string query_board() {
   return _board;
}
void dest_me()
{
   save_me();
   destruct(this_object());
}
nomask mixed dwep()
{
   destruct(this_object());
   return "Destructed With Extreme Prejudice";
}
protected varargs int post( string message, string title )
{
   string temp;
   if( undefinedp( title ) ) {
      temp = "Status summary for "+ capitalize( domain ) + ".";
   } else {
      temp = title;
   }
   if (_tester) {
      _tester->more_string(message);
      _tester = 0;
      return 0;
   }
   if (_board) {
      return BOARD_HAND->add_message(_board,
         capitalize(tracker_name), temp ,
         message);
   } else {
      return BOARD_HAND->add_message(domain,
         capitalize(tracker_name), temp ,
         message);
   }
}
string * query_classifications() {
    return ({ "live", "playtesting", "development" });
}
string query_post_message() {
   string message;
   int diff;
   if (!sizeof(_messages)) {
      message = "Congratulations!   There are no errors in all of " +
         capitalize(domain) + "!   Excellent work, everyone.\n";
   }
   else {
       message = "";
         foreach( string key in query_classifications() ) {
            if ( _messages[ key ] ) {
                message += "There are reports in the following " + key +
                    " areas:\n\n" + _messages[ key ] + "\n";
            }
            else {
                if ( key == "live" ) {
                    message += "\n\nThere are no live bugs in all of " +
                        capitalize(domain) + ".   Good work, everyone!\n";
                }
                else {
                    message += "\n\nThere are no outstanding " + key + " bugs.\n";
                }
            }
        }
   }
   diff = (real_time() - starttime);
   message += "\n\nThis message took " + diff +
     " second" + (diff != 1 ? "s" : "") + " to produce.\n";
   return message;
}
string query_project_message() {
   string str;
   class project* projects, *my_projects;
   class project project;
   mapping status;
   str = "\nCurrent Domain Projects:\n\n";
   projects = PROJECT_HANDLER->filter_by_query(([ "domains" : domain ]));
   if (sizeof(projects)) {
        status = unique_mapping( projects, (: STATUS[((class project)$1)->status] :) );
        map_delete( status, "play" );
        if ( !sizeof(status) ){
            str += "This domain is project free.\n";
        }
        foreach( string key in sort_array( keys( status ), 1 ) ) {
            str += "Projects classified as " +
                upper_case(key) + ":\n";
            my_projects = sort_array(status[key],
                (: strcmp(((class project)$1)->name,
                ((class project)$2)->name) :) );
            foreach (project in my_projects) {
                str += "    * " + project->name + " - " +
                    query_multiple_short(sort_array(map(project->creators,
                    (: capitalize :) ), 1)) + "\n";
            }
            str += "\n";
        }
   }
   else {
      str += "This domain is project free.\n";
   }
   return str;
}
protected void iterate()
{
#ifdef OLD
   string message;
   if (sizeof(_queue)) {
      string dir = _queue[0];
      if (sizeof(_queue) > 1) {
         _queue = _queue[1..];
      } else {
         _queue = ({ });
      }
      if (strsrch (dir, "_dev") != -1) {
         dodir(dir, (: _dev_msg += ({ $1 }), iterate() :));
      } else if (strsrch (dir, "_pt") != -1) {
         dodir(dir, (: _pt_msg += ({ $1 }), iterate() :));
      } else {
         dodir(dir, (: _messages += ({ $1 }), iterate() :));
      }
   } else {
      message = query_project_message() + "\n";
      message += query_post_message();
      post(message);
      _messages = ({ });
      if( function_exists( "domain_customisation" , this_object() ) ) {
            call_out( "domain_customisation" , 1 );
      }
   }
#endif
    HELPER->query_errors_in_dirs(_queue, (: finished_count_errors :) );
}
void initialise_variables() {
   _queue = ({ "/d/" + domain + "%" }) + other_dirs;
   _messages = ([ ]);
}
void do_the_work()
{
   if (domain == "unset") return;
   nexttime = time() + period;
   remove_call_out("do_the_work");
   call_out("do_the_work", period);
   save_me();
   starttime = real_time();
   initialise_variables();
   iterate();
}
varargs void test()
{
   _tester = this_player();
   starttime = real_time();
   initialise_variables();
   iterate();
}
void set_name(string name)
{
   tracker_name = name;
   save_me();
}
void set_domain(string name)
{
   domain = name;
   save_me();
}
string query_domain() {
   return domain;
}
void set_period(int length)
{
   remove_call_out("do_the_work");
   nexttime -= period;
   period = length;
   nexttime += period;
   save_me();
}
void set_other_dirs(string *others)
{
   if (arrayp(others)) {
      other_dirs = others;
   } else {
      other_dirs = ({ });
   }
   save_me();
}
mixed stats()
{
   return ({
      ({ "domain", domain }),
      ({ "name", tracker_name }),
      ({ "period", period }),
      ({ "next time", ctime(nexttime) }),
      ({ "testing by", _tester }),
      ({ "queue length", sizeof(_queue) }),
      ({ "message length", sizeof(_messages) }),
      ({ "other dirs", sizeof(other_dirs) ? implode(other_dirs, ", ") : 0 }),
      ({ "save file", _save_file }),
   });
}
protected string classify_directory(string path) {
    if ( strsrch( path, "_pt" ) > -1 ) {
        return "playtesting";
    }
    if ( strsrch( path, "_dev" ) > -1 ) {
        return "development";
    }
    return "live";
}
private int sort_errors( mapping mdata, string key1, string key2 ) {
    int total1, total2;
    total1 = mdata[key1][0] + mdata[key1][1] + mdata[key1][2];
    total2 = mdata[key2][0] + mdata[key2][1] + mdata[key2][2];
    if ( total1 > total2 )  {
        return -1;
    } else {
        if ( total1 == total2 ) {
            return 0;
        } else {
            return 1;
        }
    }
}
private void finished_count_errors( object player, int status, mixed data ) {
    int *count;
    string *paths;
    mapping errors = ([ ]);
    mapping total = ([ ]);
    string txt;
    string classification;
    mapping mdata;
    string message;
    foreach( mapping direc in data ) {
        classification = classify_directory( direc[ "Directory" ] );
        if ( !errors[ classification ] ) {
            errors[ classification ] = ([ ]);
        }
        if ( !total[ classification ] ) {
            total[ classification ] = ({ 0, 0, 0 });
        }
        count = errors[ classification ][ direc[ "Directory" ] ];
        if ( undefinedp( count ) ) {
            count = ({ 0, 0, 0 });
        }
        switch( direc[ "Type" ] ) {
            case "BUG":
                count[ 0 ] = direc[ "C" ];
                total[ classification ][ 0 ] += count[ 0 ];
            break;
            case "TYPO":
                count[ 1 ] = direc[ "C" ];
                total[ classification ][ 1 ] += count[ 1 ];
            break;
            case "IDEA":
            default:
                count[ 2 ] = direc[ "C" ];
                total[ classification ][ 2 ] += count[ 2 ];
        }
        errors[ classification ][ direc[ "Directory" ] ] = count;
    }
    foreach ( classification, mdata in errors ) {
        paths = sort_array( keys( mdata ), (: sort_errors( $(mdata), $1, $2 ) :) );
        txt = "BUGS TYPO IDEA [Assigned] Dir\n";
        foreach( string key in paths ) {
            string* assigned;
            assigned = master()->query_assigned_to_directory(key);
            if (!sizeof(assigned)) {
               assigned = ({ "No one" });
            }
            txt += sprintf( "%4d %4d %4d %-11s %s\n",
                mdata[ key ][ 0 ],
                mdata[ key ][ 1 ],
                mdata[ key ][ 2 ],
                query_multiple_short(assigned),
                key );
        }
        txt += "-------------\n";
        txt += sprintf( "%4d %4d %4d\n",
            total[ classification ][ 0 ], total[ classification ][ 1 ],
            total[ classification ][ 2 ] );
        _messages[ classification ] = txt;
    }
  message = query_project_message() + "\n";
  message += query_post_message();
  if (function_exists("extend_error_message", this_object())) {
      message += this_object()->extend_error_message( copy( errors ) );
  }
  post(message);
  _messages = ([ ]);
  if( function_exists( "domain_customisation" , this_object() ) ) {
        call_out( "domain_customisation" , 1 );
  }
}