#include <board.h>
#include <project_management.h>
#include <player_handler.h>
#include <playtesters.h>
#include <login.h>
#define SAVE_FILE "/save/playtesters"
#define LEVEL 150
#define NORMAL_PLAYTESTER 1
#define SENIOR_PLAYTESTER 2
#define BUG_SKIP 10
private int count = 0;
private nosave int updating = 0;
private string* months = ({});
private mapping pts = ([]);
private mapping playtesters = ([]);
private mapping ages = ([]);
private mapping guilds = ([]);
private mapping bugs = ([]);
private mapping leave = ([]);
private mapping tmp_pts = ([ ]);
private mapping _jump_points;
private string *executives = ({ });
int query_leave (string);
void save_file() {
    unguarded( (: save_object, SAVE_FILE :) );
}
void create() {
   seteuid( master()->creator_file( file_name( this_object() ) ) );
   months = ({ });
   pts = ([ ]);
   ages = ([ ]);
   guilds = ([ ]);
   bugs = ([ ]);
   playtesters = ([ ]);
   leave = ([ ]);
   tmp_pts = ([ ]);
   _jump_points = ([ ]);
   executives = ({ });
   if ( file_size( SAVE_FILE + ".o" ) > 0 )
      unguarded( (: restore_object, SAVE_FILE, 1 :) );
   call_out( "reset", 2 );
}
string* query_playtesters() {
    return copy( keys( pts ) );
}
int query_playtester( string name ) {
  return !undefinedp( pts[ name ] );
}
int check_playtester( string ) {
    log_file( "PLAYTESTERS", file_name( previous_object() ) + " using "
              "deprecated check_playtester() call\n" );
    return 0;
}
int query_tester( mixed person ) {
    object ob;
    string str;
    if ( stringp( person ) ) {
        ob = find_player( person );
        if ( !ob ) {
            return 0;
        }
        str = person;
    } else if ( objectp( person ) ) {
        ob = person;
        str = person->query_name();
    } else {
        return 0;
    }
    return ( ob->query_creator() ||
             ob->query_property( "test character" ) ||
             query_playtester( str ) );
}
protected int get_age_raw( string name ) {
    int fu = PLAYER_HANDLER->test_age( name );
    if ( fu < 0 )
        fu = -fu;
    return fu;
}
int get_age_cached( string name ) {
    if ( ages[ name ] < 0 )
        ages[ name ] = -ages[ name ];
    return ages[ name ];
}
int get_age_uncached( string name ) {
    if ( find_player( name ) )
        ages[ name ] = find_player( name )->query_time_on();
    return get_age_cached( name );
}
int get_age_uncached_offline( string name ) {
    ages[ name ] = get_age_raw( name );
    return get_age_cached( name );
}
int query_senior_playtester( string name ) {
    return ( pts[ name ] == SENIOR_PLAYTESTER );
}
int add_playtester( string name ) {
    if ( pts[ name ] )
        return 0;
    log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
              " added as a playtester by %s\n", this_player()->query_name() );
    pts[ name ] = NORMAL_PLAYTESTER;
    ages[ name ] = get_age_uncached_offline( name );
    guilds[ name ] = PLAYER_HANDLER->test_guild( name );
    bugs[ name ] = ([ ]);
    if (tmp_pts[name]) {
      if (tmp_pts[name] == SENIOR_PLAYTESTER) {
        pts[name] = SENIOR_PLAYTESTER;
      }
      map_delete (tmp_pts, name);
    }
    PT_APPLICATION_HANDLER->delete_applicant (name);
    save_file();
    return 1;
}
int add_senior_playtester( string name ) {
    if ( pts[ name ] != NORMAL_PLAYTESTER )
        return 0;
    log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
              " promoted to senior playtester by %s\n",
              this_player()->query_name() );
    pts[ name ] = SENIOR_PLAYTESTER;
    save_file();
    return 1;
}
int remove_senior_playtester( string name, string reason ) {
    if ( pts[ name ] != SENIOR_PLAYTESTER )
        return 0;
    log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
              " demoted from senior playtester; Reason: " + reason +
              " by "+ this_player()->query_name() + "\n" );
    pts[ name ] = NORMAL_PLAYTESTER;
    save_file();
    return 1;
}
int remove_playtester( string name, string reason ) {
    string str;
    if ( !query_playtester( name ) )
        return 0;
    str = ctime( time() ) +": "+ name + " removed as a playtester";
    if ( reason ) {
        str += "; Reason: " + reason;
    }
    str += " by "+ this_player()->query_name() + "\n" ;
    log_file( "PLAYTESTERS", str + "\n" );
    map_delete( pts, name );
    map_delete( ages, name );
    map_delete( guilds, name );
    map_delete( bugs, name );
    PROJECT_HANDLER->clear_playtesting_projects (({name }));
    save_file();
    return 1;
}
string reason_invalid_playtester(string name) {
    if ( !PLAYER_HANDLER->test_user( name ) ) {
        return "not a user";
    }
    if ( PLAYER_HANDLER->test_creator( name ) ) {
        return "currently a creator";
    }
    if ( PLAYER_HANDLER->test_level( name ) < LEVEL ) {
        return "level is too low";
    }
    return 0;
}
int valid_playtester( string name ) {
    return ( !stringp( reason_invalid_playtester( name ) ) );
}
int hire_playtester( object thing ) {
    string name;
    if ( !objectp( thing ) )
        return 0;
    name = thing->query_name();
    if ( !stringp( name ) )
        return 0;
    if ( !valid_playtester( name ) )
        return 0;
    return add_playtester( name );
}
void adjust_quota( string name, int amount ) {
    string* bits;
    string right_now;
    int* bing;
    int age;
    bits = explode( ctime( time() ), " " ) - ({ "" });
    right_now = bits[ 1 ] + " " + bits[ 4 ];
    if (!bugs[name][right_now]) {
      bugs[name][right_now] = 0;
    }
    bing = bugs[ name ][ right_now ];
    age = get_age_uncached( name );
    if ( arrayp( bing ) && ( sizeof( bing ) == 3 ) ) {
        bing[ 0 ] += amount;
        bing[ 1 ] += age - bing[ 2 ];
        bing[ 2 ] = age;
    } else {
        bing = ({ amount, 0, age });
    }
    bugs[ name ][ right_now ] = bing;
    save_file();
}
protected void check_playtesters_one( string name ) {
    if ( !valid_playtester( name ) ) {
        remove_playtester( name, reason_invalid_playtester( name ) +
                           " [automatic]" );
    } else {
        adjust_quota( name, 0 );
    }
}
void check_playtesters( string* who ) {
    string* bits;
    string right_now;
    if ( sizeof( who ) ) {
        check_playtesters_one( who[ 0 ] );
        if ( sizeof( who ) > 1 ) {
            call_out( "check_playtesters", random( 10 ) + 5, who[ 1.. ] );
        } else {
            bits = explode( ctime( time() ), " " ) - ({ "" });
            right_now = bits[ 1 ] + " " + bits[ 4 ];
            if ( member_array( right_now, months ) < 0 ) {
                months += ({ right_now });
                save_file();
            }
        }
    }
}
void reset() {
    if ( !updating )
        call_out( "check_playtesters", 30, copy( keys( pts ) ) );
    updating++;
    updating %= 12;
}
void report_made( string name, string type, string file, string text ) {
    int post = 0;
    if ( !query_playtester( name ) )
        return;
    if ( regexp( type, "IDEA" ) ) {
        post = 1;
    } else if ( regexp( type, "BUG" ) ) {
        count = ( count + 1 ) % BUG_SKIP;
        post = ( count == 0 );
    }
    if ( post ) {
        BOARD_HAND->add_message( "playtester_bugs", capitalize( name ),
                                 type + " for " + file,
                                 sprintf( "%75-=s", text ) );
    }
    adjust_quota( name, 1 );
}
string query_show_list() {
    string result;
    result = "              ";
    foreach ( string month in months[ <5.. ] ) {
        result += "    " + month;
    }
    result += "\n";
    foreach ( string name in sort_array( query_playtesters(), 1 ) ) {
        if ( query_senior_playtester( name ) ) {
            result += "S ";
        } else {
            result += "  ";
        }
        if ( stringp( leave[ name ] ) )
            result += sprintf( "%-14s", "[" + name + "]" );
        else
            result += sprintf( " %-12s ", name );
        foreach ( string month in months[ <5.. ] ) {
            if ( sizeof( bugs[ name ][ month ] ) >= 2 )
                result += sprintf( "   %4d %4d", bugs[ name ][ month ][ 0 ],
                                   ( bugs[ name ][ month ][ 1 ] / 3600 ) );
            else
                result += "   ---- ----";
        }
        result += "\n";
    }
    return result;
}
string query_show_list_colour() {
    string result;
    string colour;
    int online, reports;
    string temp;
    result = "              ";
    foreach ( string month in months[ <5.. ] ) {
        result += "    " + month;
    }
    result += "\n";
    foreach ( string name in sort_array( query_playtesters(), 1 ) ) {
        reports = 0;
        online = 0;
        if ( query_senior_playtester( name ) ) {
            temp = "S ";
        } else {
            temp = "  ";
        }
        temp += sprintf( "%%s%-12s%%%%^RESET%%%%^", name );
        foreach ( string month in months[ <5.. ] ) {
	          if (query_leave (name)) {
                    colour = "%%^WHITE%%^";
	          }
            else if ( sizeof( bugs[ name ][ month ] ) >= 2 ) {
                reports += bugs[ name ][ month ][ 0 ];
                online += bugs[ name ][ month ][ 1 ];
                if ( bugs[ name ][ month ][ 1 ] == 0 )
                    colour = ( stringp( leave[ name ] ) ?
                               "%%^MAGENTA%%^" :
                               "%%^BOLD%%^%%^MAGENTA%%^" );
                else if ( bugs[ name ][ month ][ 0 ] >=
                     ( bugs[ name ][ month ][ 1 ] / 7200 ) )
                    colour = ( stringp( leave[ name ] ) ?
                               "%%^GREEN%%^" :
                               "%%^BOLD%%^%%^GREEN%%^" );
                else if ( bugs[ name ][ month ][ 0 ] <
                          ( bugs[ name ][ month ][ 1 ] / 24000 ) )
                    colour = ( stringp( leave[ name ] ) ?
                               "%%^RED%%^" :
                               "%%^BOLD%%^%%^RED%%^" );
                else
                    colour = ( stringp( leave[ name ] ) ?
                               "%%^ORANGE%%^" :
                               "%%^YELLOW%%^" );
                temp += sprintf( "   %s%4d %4d%%%%^RESET%%%%^",
                                 colour,
                                 bugs[ name ][ month ][ 0 ],
                                 ( bugs[ name ][ month ][ 1 ] / 3600 ) );
            } else
                temp += "   ---- ----";
        }
        temp += "\n";
        if ( online == 0 )
            colour = ( stringp( leave[ name ] ) ?
                       "%^BOLD%^%^WHITE%^" :
                       "%^BOLD%^%^MAGENTA%^" );
        else if ( reports >= ( online / 7200 ) )
            colour = ( stringp( leave[ name ] ) ?
                       "%^GREEN%^" :
                       "%^BOLD%^%^GREEN%^" );
        else if ( reports < ( online / 24000 ) )
            colour = ( stringp( leave[ name ] ) ?
                       "%^RED%^" :
                       "%^BOLD%^%^RED%^" );
        else
            colour = ( stringp( leave[ name ] ) ?
                       "%^ORANGE%^" :
                       "%^YELLOW%^" );
        result += sprintf( temp, colour );
    }
    return result;
}
mapping query_playtester_guilds() {
    mapping r = ([]);
    foreach ( string pt, string guild in guilds ) {
        if ( arrayp( r[ guild ] ) )
            r[ guild ] += ({ pt });
        else
            r[ guild ] = ({ pt });
    }
    return r;
}
mapping query_guilds() {
    return copy( guilds );
}
void update_guilds() {
  string guild;
    foreach( string player, mapping data in playtesters ) {
        if ( !sizeof (data[ "guild" ]) ) {
            guild = PLAYER_HANDLER->test_guild( player );
            if (!sizeof (guild)) {
              guild = "/std/guilds/standard";
            }
            data[ "guild" ] = guild;
        }
    }
    save_file();
}
mixed query_pt_data( string name ) {
    if ( !undefinedp( playtesters[ name ] ) )
        return copy( playtesters[ name ] );
    return 0;
}
mapping query_bugs( string name ) {
    return copy( bugs[ name ] );
}
string* query_months() {
    return copy( months );
}
int set_leave( string name, string reason ) {
    if ( pts[ name ] ) {
        leave[ name ] = reason;
        log_file( "PLAYTESTERS", ctime( time() ) + ": " + name + " marked as "
                  "on leave: " + reason + "\n" );
        save_file();
        return 1;
    } else {
        return 0;
    }
}
int reset_leave( string name ) {
    if ( leave[ name ] ) {
        map_delete( leave, name );
        log_file( "PLAYTESTERS", ctime( time() ) + ": " + name + " no longer "
                  "marked as on leave\n" );
        save_file();
        return 1;
    } else {
        return 0;
    }
}
int query_leave( string name ) {
    return stringp( leave[ name ] );
}
#ifdef PLAYTESTERS_HANDLER_OLD_STYLE_CONVERSION
void transfer_data_callout( string* pts ) {
    string pt;
    mixed bing;
    int lastage;
    int nowage;
    if ( sizeof( pts ) ) {
        pt = pts[ 0 ];
        nowage = get_age_uncached_offline( pt );
        lastage = nowage - playtesters[ pt ][ "age" ];
        guilds[ pt ] = PLAYER_HANDLER->test_guild( pt );
        ages[ pt ] = nowage;
        bugs[ pt ] = ([ ]);
        foreach ( string s in keys( playtesters[ pt ] ) -
                  ({ "senior", "age", "current age", "guild" }) ) {
            bing = playtesters[ pt ][ s ];
            if ( arrayp( bing ) ) {
                bugs[ pt ][ s ] = ({ bing[ 0 ], bing[ 1 ], nowage });
            } else if ( intp( bing ) ) {
                bugs[ pt ][ s ] = ({ bing, lastage, nowage });
            }
        }
        tell_creator( "arienne", "Done " + pt + "!\n" );
        if ( sizeof( pts ) > 1 ) {
            call_out( "transfer_data_callout", 5, pts[ 1.. ] );
        } else {
            save_file();
            tell_creator( "arienne", "Done the transfer!\n" );
        }
    }
}
void transfer_data_to_new_system() {
    foreach ( string pt in keys( playtesters ) ) {
        if ( playtesters[ pt ][ "senior" ] )
            pts[ pt ] = SENIOR_PLAYTESTER;
        else
            pts[ pt ] = NORMAL_PLAYTESTER;
    }
    call_out( "transfer_data_callout", 5, copy( keys( playtesters ) ) );
}
#endif
mapping query_jump_points() {
   if (!_jump_points) {
      _jump_points = ([ ]);
   }
   return copy(_jump_points);
}
void add_jump_point(string from, string to) {
   if (!_jump_points[from]) {
      _jump_points[from] = ({ });
   }
   _jump_points[from] += ({ to });
   save_file();
}
void remove_jump_point_from(string from) {
   map_delete(_jump_points, from);
   save_file();
}
void remove_jump_point(string from, string to) {
   if (_jump_points[from]) {
      _jump_points[from] -= ({ to });
      if (!sizeof(_jump_points[from])) {
         map_delete(_jump_points, from);
      }
      save_file();
   }
}
string* query_jump_destination(string from) {
   return _jump_points[from];
}
int add_pt_exec( string name ) {
    if ( undefinedp (pts[ name ]))
        return 0;
    log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
              " promoted to playtester executive by %s\n",
              this_player()->query_name() );
    executives += ({ name });
    save_file();
    return 1;
}
int remove_pt_exec( string name ) {
    if ( !undefinedp (pts[ name ]))
        return 0;
    if (member_array (name, executives) == -1) {
      return 0;
    }
    log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
              " removed from playtester executive by %s\n",
              this_player()->query_name() );
    executives -= ({ name });
    save_file();
    return 1;
}
int query_pt_exec(string name) {
  if (member_array (name, executives) == -1) {
    return 0;
  }
  return 1;
}
int query_exec_access (string name) {
  if (master()->query_senior(name)) {
    return 1;
  }
  if (query_pt_exec (name)) {
    return 1;
  }
  if (query_senior_playtester (name)) {
    return 1;
  }
  if (load_object ("/d/playtesters/master")->query_deputy (name)) {
    return 1;
  }
  return 0;
}