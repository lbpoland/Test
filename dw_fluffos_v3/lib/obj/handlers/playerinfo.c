#include <playerinfo.h>
#include <player_handler.h>
#include <refresh.h>
#include <applications.h>
#include <newbiehelpers.h>
#define SAVE_DIR         "/save/playerinfo"
#define SAVE_FILE        ( SAVE_DIR + "/handler_data" )
#define NO_ACCESS_LOG    6
#define LIAISON_WAND       "/d/liaison/items/wand"
#define LIAISON_SCEPTRE    "/d/liaison/items/mort_sceptre"
#define LIAISON_PEN        "/d/liaison/items/quota_pen"
#define LIAISON_INTERVIEW  "/d/liaison/utils/interview"
#define MULTIPLAY          "/obj/handlers/multiplayer"
#define GAG                "/cmds/creator/gag"
#define UNGAG              "/cmds/creator/ungag"
#define METEOR             "/cmds/creator/meteor"
#define FRY                "/cmds/creator/fry"
#define REPORT_COMMAND     "/cmds/creator/playerinfo"
#define ADD_COMMAND        "/cmds/creator/addevent"
#define DELETE_COMMAND     "/cmds/creator/delevent"
#define ADDALT_COMMAND     "/cmds/creator/addalt"
#define DELALT_COMMAND     "/cmds/creator/delalt"
#define FAMILY_COMMAND     "/cmds/creator/family"
#define SUSPENDER          "/secure/bastards"
#define SHOWHELP_COMMAND   "/cmds/creator/show_help"
#define PATRICIAN_PALACE   "/d/am/patrician/patrician"
#define REFRESH_HANDLER    "/obj/handlers/refresh"
#define PRISON             "/d/sur/beta/prison/dungeon"
#define FETCH_COMMAND      "/cmds/creator/fetch"
#define REARRANGE_COMMAND  "/cmds/guild-race/rearrange"
#define PATRICIAN_PT       "/d/playtesters/handlers/applications"
#define PATRICIAN_COMPLAIN "/d/am/patrician/pat_complaints"
#define RUN_HANDLER        "/obj/handlers/guild_things/run"
#define BANISH_COMMAND     "/secure/cmds/creator/banish"
#define FAIRY_GODMOTHER    "/obj/handlers/fairy_godmothers"
#define CACHE_SIZE 150
#define CL_CREATOR      "%^CYAN%^"
#define CL_EVENT        "%^RED%^"
#define CL_RESET        "%^RESET%^"
#define CL_HEADER       "%^RED%^"
#define DEBOUNCE_PERIOD (60*30)
#define TIMEOUT_PERIOD  (60*60*24)
#define ONE_WEEK           ( 60 * 60 * 24 * 7 )
nosave inherit "/std/object";
mapping          query_timeouts();
protected string filename(string name);
string *         query_events();
protected int    query_debounced(string event);
protected int    query_lord_only(string event);
int              query_source_ok(string event, string source);
protected int    query_deleter_ok(string event, object deleter);
protected int    query_can_add(string e, object p);
protected int    query_can_delete(string e, object p);
protected int    query_can_handle_alts(object p);
protected void   do_debouncing(string player, class dbentry entry);
protected void   do_timeout();
protected void   load_player(string player);
protected void   save_player(string player);
void             player_remove(string player);
int              add_entry(object creator, string player, string event,
                   string comment, mixed *extra);
int              delete_entry(object creator, string player, string event,
                   int n);
protected string query_header(string player);
protected string query_entry(int idx, class dbentry e,
                   string display_name);
string           query_access_log(object source, string player, int lastn);
string           query_event(object source, string player, string event);
string           add_alt(object creator, string player, string alt);
string           delete_alt(object creator, string player, string alt);
mapping          query_alerts();
int              query_alerts_for( string player );
int              is_alert( string player, int idx );
int              acknowledge_alert( object creator, string player,
                   string event, int idx, string update, mixed * extra );
void             clear_alerts_for( string player );
int              increment_alerts_for( string player );
int              decrement_alerts_for( string player );
void             correct_alts_for( string player );
void player_deleted(mixed player, int deleted);
void fix_alts(mixed player);
class source {
   string *add;
   string *delete;
}
private class playerinfo    dossier;
private nosave mapping      timeouts    = ([ "replace" : (60*60*24*30) ]);
private int local_time;
private nosave mapping _sources;
nosave mapping _alerts;
nosave string * _lordonly;
private nosave int correcting_alts;
private nosave int no_recurse;
private nosave mapping _dossier_cache;
private nosave int _dossier_cache_hits;
private nosave int _dossier_total;
void save_handler_data() {
   mapping vars = ([ ]);
   string tmp;
   vars["alerts"] = _alerts;
   tmp = save_variable( vars );
   unguarded( (: write_file, SAVE_FILE, tmp, 1 :) );
}
void load_handler_data() {
   mapping vars;
   string tmp;
   if( file_size( SAVE_FILE ) <= 0 )
      return;
   tmp = unguarded( (: read_file, SAVE_FILE :) );
   vars = restore_variable( tmp );
   _alerts = vars["alerts"];
}
void create() {
    ::create();
    _sources = ([
        "cheat":        new(class source,
                            add : ({ }),
                            delete : ({ DELETE_COMMAND })),
        "discipline":   new(class source,
                            add : ({ ADD_COMMAND, PRISON, REPORT_COMMAND,
                                     BANISH_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "email":        new(class source,
                            add : ({ }),
                            delete : ({ DELETE_COMMAND })),
        "family":       new(class source,
                            add : ({ FAMILY_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "gag":          new(class source,
                            add : ({ GAG, UNGAG,
                                     ADD_COMMAND, REPORT_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "harassment":   new(class source,
                            add : ({ ADD_COMMAND, REPORT_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "meteor":       new(class source,
                            add : ({ METEOR, FRY }),
                            delete : ({ DELETE_COMMAND })),
        "misc":         new(class source,
                            add : ({ ADD_COMMAND, APPLICATIONS_HANDLER,
                                     REARRANGE_COMMAND, PATRICIAN_PT,
                                     PATRICIAN_COMPLAIN, RUN_HANDLER,
                                     REPORT_COMMAND, NEWBIEHELPERS_HANDLER,
                                     LIAISON_SCEPTRE,
                                     LIAISON_PEN, FAIRY_GODMOTHER,
                                     LIAISON_INTERVIEW }),
                            delete : ({ DELETE_COMMAND })),
        "multiplay":    new(class source,
                            add : ({ MULTIPLAY, ADD_COMMAND,
                                     REPORT_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "replace":      new(class source,
                            add : ({ LIAISON_WAND,
                                     ADD_COMMAND, FETCH_COMMAND,
                                     REPORT_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "showhelp":     new(class source,
                            add : ({ SHOWHELP_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "suspend":      new(class source,
                            add : ({ SUSPENDER }),
                            delete : ({ })),
        "alert":        new(class source,
                            add : ({ ADD_COMMAND, REPORT_COMMAND }),
                            delete : ({ DELETE_COMMAND })),
        "refresh":      new(class source,
                            add : ({ REFRESH_HANDLER }),
                            delete : ({ DELETE_COMMAND })),
        "delete":      new(class source,
                           add : ({ REFRESH_HANDLER }),
                           delete : ({ DELETE_COMMAND }))
    ]);
    _alerts = ([ ]);
    _lordonly = ({ });
    _dossier_cache = ([ ]);
    _dossier_cache_hits = 0;
    _dossier_total = 0;
    seteuid("Room");
    load_handler_data();
}
mapping query_timeouts() {
    return timeouts;
}
string query_name() {
    return "playerinfo handler";
}
protected string filename(string name) {
    string p = lower_case(name);
    return sprintf("%s/%c/%s.o",SAVE_DIR,p[0],p);
}
string *query_events() {
    return keys(_sources);
}
protected int query_debounced(string event) {
    return (event == "replace" || event == "multiplay" ||
            event == "gag" || event == "misc" ||
            event == "discipline" || event == "showhelp" ||
            event == "suspend");
}
protected int query_lord_only(string event) {
    return ( member_array( event, _lordonly ) >= 0 ) ? 1 : 0;
}
int query_source_ok(string event, string source) {
    string *reqd;
    reqd = _sources[event]->add;
    if(reqd == 0) {
        return 1;
    }
    if(sizeof(reqd) == 0) {
        return 0;
    }
    return member_array(source,reqd) >= 0;
}
protected int query_deleter_ok(string event, object deleter) {
    string *reqd;
    reqd = _sources[event]->delete;
    if (reqd == 0) {
        return 1;
    }
    if (sizeof(reqd) == 0) {
        return 0;
    }
    return member_array(base_name(deleter),reqd) >= 0;
}
protected int query_can_add(string e, object p) {
    if(member_array(e,query_events()) < 0)
        return 0;
    if(!interactive(p))
        return 1;
    return !(query_lord_only(e) && !p->query_lord());
}
protected int query_can_delete(string e, object p) {
    if( !interactive(p) ) {
        return 1;
    }
    if( e == "misc" || e == "replace" ) {
        return master()->query_senior( p->query_name() ) ||
               "/d/liaison/master"->query_deputy( p->query_name() );
    }
    return p->query_lord();
}
protected int query_can_handle_alts(object p) {
    if( !interactive(p) ) {
        return 1;
    }
    return master()->query_senior( p->query_name() ) ||
           "/d/liaison/master"->query_deputy( p->query_name() );
}
protected void do_debouncing(string player, class dbentry entry) {
    int             n;
    class dbentry   last;
    if (query_debounced(entry->event)) {
        n = sizeof(dossier->data);
        if ( n ) {
            last = dossier->data[ n - 1 ];
            if( entry->event == last->event &&
                entry->creator == last->creator &&
                entry->time - last->time <= DEBOUNCE_PERIOD)
            {
                last->comment += entry->comment;
                last->time = entry->time;
                if(last->extra != 0) {
                    if(entry->extra == 0) {
                        entry->extra = ({ });
                    }
                    last->extra += entry->extra;
                }
                return;
            }
        }
    }
    dossier->data += ({ entry });
    return;
}
protected void do_timeout() {
    function not_timed_out = function(class dbentry p)
    {
        int life = timeouts[p->event];
        if(life == 0)
            return 1;
        return local_time <= (p->time + life);
    };
    local_time = time();
    dossier->data = filter(dossier->data, not_timed_out);
    dossier->last_check = time();
}
protected void load_player(string player) {
    string  p = lower_case(player);
    string  fn = filename(p);
    class playerinfo tmp;
    mixed result;
    _dossier_total++;
    if ( !undefinedp(_dossier_cache[ player ] ) ) {
        dossier = _dossier_cache[ player ];
        _dossier_cache_hits++;
        return;
    }
    if( dossier != 0 && dossier->name == p ) {
        return;
    }
    if(file_size(fn) > 0) {
        result = unguarded( (: restore_object, fn, 0 :) );
    } else {
        dossier = new(class playerinfo,
            name:       p,
            last_check: time(),
            alts:       ({ }),
            data:       ({ }));
    }
    if (!classp(dossier)) {
        dossier = new(class playerinfo,
            name:       p,
            last_check: time(),
            alts:       ({ }),
            data:       ({ }));
    }
    if(sizeof(dossier) == 5) {
      tmp = new(class playerinfo,
                name: dossier->name,
                last_check: dossier->last_check,
                alts: copy(dossier->alts),
                data: copy(dossier->data),
                main_alt: dossier->main_alt,
                old_alts: ({ }));
      dossier = tmp;
    }
    if(!dossier->old_alts)
      dossier->old_alts = ({ });
    if(!correcting_alts) {
        correct_alts_for( dossier->name );
    }
    _dossier_cache[ player ] = dossier;
}
protected void save_player(string player) {
    if( time() - dossier->last_check >= TIMEOUT_PERIOD ) {
        do_timeout();
    }
    unguarded( (: save_object, filename(player) :) );
}
void player_remove(string player) {
    string alt, new_main;
    string * alts;
    if ( !player ) {
        return;
    }
    player = lower_case( player );
    correcting_alts = 1;
    load_player( player );
    if ( sizeof( dossier->alts ) ) {
        alts = copy( dossier->alts );
        new_main = alts[0];
        alts -= ({ new_main });
        load_player( new_main );
        dossier->main_alt = 0;
        dossier->alts = uniq_array( alts + ({ player }) );
        save_player( new_main );
        foreach( alt in alts ) {
            load_player( alt );
            dossier->main_alt = new_main;
            save_player( alt );
        }
    }
    correcting_alts = 0;
    unguarded( (: rm, filename(player) :) );
    clear_alerts_for(player);
}
int add_entry(object creator, string player, string event, string comment,
  mixed *extra) {
    class dbentry   new_entry;
    if(!query_can_add(event,creator))
        return 0;
    if(!query_source_ok(event,base_name(previous_object())))
        return 0;
    if(!PLAYER_HANDLER->test_user(lower_case(player)))
        return 0;
    if(comment[<1..<1] != "\n") {
        comment += "\n";
    }
    load_player(player);
    new_entry = new(class dbentry,
            time:       time(),
            creator:    capitalize(creator->query_name()),
            event:      event,
            comment:    (comment == 0 ? "" : comment),
            extra:      extra);
    do_debouncing(player, new_entry);
    save_player(player);
    if( event == "alert" )
        increment_alerts_for(player);
    return 1;
}
int delete_entry(object creator, string player, string event, int n) {
   int idx = n - 1;
   class dbentry * data;
   class dbentry fluff;
   if( !query_can_delete( event, creator ) )
      return 0;
   if( !query_deleter_ok( event, previous_object() ) )
      return 0;
   load_player(player);
   if( ( idx < 0 ) || ( idx >= sizeof( dossier->data ) ) )
      return 0;
   fluff =  dossier->data[idx];
   if( fluff->event != event )
      return 0;
   data = copy( dossier->data );
   data = data[0 .. (idx - 1)] + data[(idx + 1) .. <1];
   dossier->data = data;
   save_player(player);
   log_file("DELETE", ctime(time()) + ": " + event + " added by " +
            fluff->creator + "\n");
   if( event == "alert" )
      decrement_alerts_for(player);
   return 1;
}
protected string query_header( string player ) {
  string aka, alts, str;
  string *tmp, *tmp2;
  aka = alts = str = "";
  if( sizeof( dossier->alts ) > 0 )
    alts = " aka " +
      query_multiple_short(map(dossier->alts,
                               (: CL_HEADER+capitalize($1)+CL_RESET :)));
  if(sizeof(dossier->old_alts) > 0)
    alts += " (and was " +
      query_multiple_short(map(dossier->old_alts,
                               (: CL_HEADER+capitalize($1)+CL_RESET :))) + ")";
  if( dossier->main_alt ) {
    if(!PLAYER_HANDLER->test_user(dossier->main_alt)) {
      fix_alts(player);
      load_player(player);
    }
    aka = " (alt of " + CL_HEADER + capitalize(dossier->main_alt) + CL_RESET;
    load_player(dossier->main_alt);
    tmp = copy(dossier->alts);
    tmp2 = copy(dossier->old_alts);
    if(!tmp) {
      tmp = ({ });
      dossier->alts = ({ });
      save_player( dossier->name );
    }
    load_player(player);
    tmp -= ({ player });
    if(sizeof(tmp))
      aka += ", aka " +
        query_multiple_short(map(tmp, (: CL_HEADER+capitalize($1)+CL_RESET :)));
    if( arrayp( tmp2 ) ) {
      tmp2 -= ({ player });
      if(sizeof(tmp2)) {
        aka += " and was " +
          query_multiple_short(map(tmp2, (: CL_HEADER+capitalize($1)+CL_RESET:)));
      }
    }
    aka += ")";
  }
  return sprintf( "Report for: %s%s%s\n\n",
                  CL_HEADER + capitalize(player) + CL_RESET, alts, aka );
}
protected string query_entry( int idx, class dbentry e,
                              string display_name ) {
   string  date      = ctime( e->time );
   string  creator   = e->creator;
   string  event     = e->event;
   string  *comments = explode( e->comment, "\n" );
   string  line, str;
   int     lines = 0;
   if( display_name )
      display_name = sprintf( "%-31s ",
        "(" + CL_CREATOR + display_name + CL_RESET + ")" );
   else
      display_name = "";
   str = sprintf( "%2d. %s%s %s%|14s%s (by %s%s%s)\n",
     idx + 1, display_name, date, CL_EVENT, event, CL_RESET,
     CL_CREATOR, creator, CL_RESET );
   foreach( line in comments ) {
      if( sizeof(line) != 0 ) {
         str += sprintf( "    %s\n", line );
         lines++;
      }
   }
   if( !lines ) {
      str += sprintf( "    (no comments)\n" );
   }
   return str;
}
varargs string query_dossier( object source, string player, int lastn ) {
   int             i;
   class dbentry   * list;
   string          msg, str;
   mapping         log;
   load_player(player);
   str = query_header(player);
   list = dossier->data;
   if ( sizeof( dossier ) == NO_ACCESS_LOG ) {
    dossier = new ( class playerinfo,
        name: dossier->name,
        last_check: dossier->last_check,
        alts: dossier->alts,
        data: dossier->data,
        main_alt: dossier->main_alt,
        old_alts: dossier->old_alts,
        access_log: ([ ]) );
   }
   if ( mapp( dossier->access_log ) )
     log = dossier->access_log;
   else
     log = ([ ]);
   if( !lastn ||
       sizeof(list) <= lastn ||
       source->query_property(VERBOSE_PI) )
   {
      i = 0;
   } else {
      i = sizeof(list) - lastn;
      msg = "%^RED%^NOTE:%^RESET%^ Only displaying this player's most "
        "recent " + lastn + " entries.  Use 'playerinfo "
        + player + " verbose' to see their entire dossier.\n";
      str += msg + "\n";
   }
   for( ; i < sizeof( list ); i++ ) {
      str += query_entry( i, list[i], 0 );
   }
   if( msg ) {
      str += "\n" + msg;
   }
   log = filter( log, (: $2 > time() - ONE_WEEK :) );
   if ( interactive( source ) )
     log[ source->query_name() ] = time();
  dossier->access_log = log;
  save_player( player );
  return str;
}
string query_event( object source, string player, string event ) {
   int             i;
   class dbentry   *list;
   string          str;
   load_player(player);
   str = query_header(player);
   list = dossier->data;
   for( i = 0; i < sizeof(list); i++ ) {
      if( list[i]->event == event )
         str += query_entry( i, list[i], 0 );
   }
   return str;
}
string query_interleaved( object source, string player, string event ) {
   class playerinfo * dossiers;
   class dbentry * stuff;
   string str;
   string * alts;
   int i, size, done, earliest, earliestt, count;
   int * earliests;
   load_player(player);
   if( dossier->main_alt ) {
      player = dossier->main_alt;
      load_player(player);
   }
   str = query_header(player);
   alts = ({ player }) + copy( dossier->alts );
   size = sizeof(alts);
   if( size == 1 ) {
      if(event) {
        str = query_event( source, player, event );
      } else {
        str = query_dossier( source, player );
      }
      return str;
   }
   dossiers = allocate(size);
   earliests = allocate(size);
   for( i = 0; i < size; i++ ) {
     load_player( alts[i] );
     if( sizeof( dossier->data ) ) {
       dossiers[i] = copy(dossier);
     } else {
       dossiers[i] = 0;
     }
     earliests[i] = 0;
   }
   count = 0;
   while( !done ) {
      done = 1;
      earliestt = 0;
      for( i = 0; i < size; i++ ) {
         if( !dossiers[i] ) {
            continue;
         }
         done = 0;
         stuff = dossiers[i]->data;
         if( !earliestt || stuff[ earliests[i] ]->time < earliestt ) {
            earliest = i;
            earliestt = stuff[ earliests[i] ]->time;
         }
      }
      if(done) {
         continue;
      }
      stuff = dossiers[earliest]->data;
      if( !event ||
          stuff[ earliests[earliest] ]->event == event )
      {
         str += query_entry( count, stuff[ earliests[earliest] ],
                             alts[earliest] );
         count++;
      }
      earliests[earliest]++;
      if( earliests[earliest] >= sizeof(stuff) ) {
         dossiers[earliest] = 0;
      }
   }
   return str;
}
string query_alt_of(string player) {
  if(!PLAYER_HANDLER->test_user(player))
    return 0;
  load_player(player);
  return dossier->main_alt;
}
string *query_alts(string player) {
  if(!PLAYER_HANDLER->test_user(player))
    return ({ });
  load_player(player);
  return dossier->alts;
}
string add_alt(object creator, string player, string alt) {
  class dbentry new_entry;
  int is_deleted;
  string *alts, tmp;
  if((base_name(previous_object()) != "/cmds/player/register") &&
     !query_can_handle_alts(this_player()))
    return "You are not allowed to add players' alts.\n";
  alt = lower_case(alt);
  if(!find_player(alt) && !PLAYER_HANDLER->test_user(alt)) {
    if(!creator)
      return "No such player: " + capitalize(alt) + ".\n";
    if(file_size(filename(alt)) == -1)
      return "No such player and no record for: " + capitalize(alt) + ".\n";
    is_deleted = 1;
  }
  load_player(alt);
  if(dossier->main_alt && PLAYER_HANDLER->test_user(dossier->main_alt) &&
     !is_deleted)
    return capitalize(alt) + " is already an alt of " +
      capitalize(dossier->main_alt) + ".\n";
  if(sizeof(dossier->alts)) {
    if(is_deleted)
      return capitalize(alt) + " already has alts.\n";
    else {
      alts = dossier->alts + dossier->old_alts;
    }
  }
  player = lower_case(player);
  if(!find_player(player) && !PLAYER_HANDLER->test_user(player))
    return "No such player: "+ capitalize(player) +".\n";
  correcting_alts = 1;
  load_player(player);
  if(dossier->main_alt == alt) {
    correcting_alts = 0;
    return capitalize(player) + " is already an alt of " +
      capitalize(dossier->main_alt) + ".\n";
  }
  if(dossier->alts && member_array(alt, dossier->alts) != -1) {
    correcting_alts = 0;
    return capitalize(alt) + " is already an alt of " +
      capitalize(player) + ".\n";
  }
  if(!dossier->alts)
    dossier->alts = ({ });
  dossier->alts += ({ alt });
  if(alts) {
    foreach(tmp in alts) {
      if(PLAYER_HANDLER->test_user(tmp))
        dossier->alts += ({ tmp });
      else
        dossier->old_alts += ({ tmp });
    }
  }
  new_entry = new(class dbentry,
                  time:       time(),
                  creator:    creator ? capitalize(creator->query_name()) :
                              player,
                  event:      "register",
                  comment:    "Registered " + capitalize(alt) +
                              " as an alt.\n",
                  extra:      0);
  do_debouncing(player, new_entry);
  save_player(player);
  load_player(alt);
  dossier->main_alt = player;
  dossier->alts = ({ });
  dossier->old_alts = ({ });
  new_entry = new(class dbentry,
                  time:       time(),
                  creator:    creator ? capitalize(creator->query_name()) :
                              player,
                  event:      "register",
                  comment:    "Registered as an alt of " + player + ".\n",
                  extra:      0);
  do_debouncing(alt, new_entry);
  save_player(alt);
  correcting_alts = 0;
  return "Added " + capitalize(alt) + " as an alt of " + capitalize(player) +
    ".\n";
}
string delete_alt(object creator, string player, string alt) {
  string ret;
  class dbentry new_entry;
  if(!query_can_handle_alts(this_player()))
    return "You are not allowed to delete players' alts.\n";
  player = lower_case(player);
  alt = lower_case(alt);
  load_player(player);
  if(!dossier->alts || member_array(alt, dossier->alts) == -1)
    ret = capitalize(alt) + " was not an alt of " + capitalize(player);
  else {
    dossier->alts -= ({ alt });
    new_entry = new(class dbentry,
                    time:       time(),
                    creator:    capitalize(creator->query_name()),
                    event:      "register",
                    comment:    "Removed " + capitalize(alt) + " as an alt.\n",
                    extra:      0);
    do_debouncing(alt, new_entry);
    save_player(player);
  }
  load_player(alt);
  if(dossier->main_alt != player) {
    if(ret)
      return capitalize(alt) + " is not an alt of " + capitalize(player) +
        ".\n";
    else
      ret = capitalize(player) + " was not the main player for " +
        capitalize(alt);
  } else {
    dossier->main_alt = 0;
    dossier->alts = ({ });
    dossier->old_alts = ({ });
    new_entry = new(class dbentry,
                    time:       time(),
                    creator:    capitalize(creator->query_name()),
                    event:      "register",
                    comment:    "Removed as an alt of " + capitalize(player) +
                    ".\n",
                    extra:      0);
    do_debouncing(alt, new_entry);
    save_player(alt);
  }
  if(ret)
    return "Deleted " + capitalize(alt) + " from " + capitalize(player) +
      "'s list of alts (" + ret + ").\n";
  else
    return "Deleted " + capitalize(alt) + " from " + capitalize(player) +
      "'s list of alts.\n";
}
mapping query_alerts() {
   if( !_alerts ) {
      _alerts = ([ ]);
   }
   return _alerts;
}
int query_alerts_for( string player ) {
   player = lower_case(player);
   if( !_alerts ) {
      _alerts = ([ ]);
   }
   return _alerts[player];
}
int is_alert( string player, int idx ) {
   load_player( player );
   if( sizeof(dossier->data) < idx ) {
      return 0;
   }
   return ( dossier->data[ idx - 1 ] )->event == "alert";
}
int acknowledge_alert( object creator, string player, string event,
   int idx, string update, mixed * extra ) {
   class dbentry entry;
   string previnfo;
   player = lower_case(player);
   if( !query_can_add( event, creator ) )
      return 0;
   if( !query_source_ok( "alert", base_name( previous_object() ) ) )
      return 0;
   if( !query_source_ok( event,  base_name( previous_object() ) ) )
      return 0;
   if( !PLAYER_HANDLER->test_user(player) )
      return 0;
   if( member_array( event, keys(_sources) ) < 0 )
      return 0;
   idx--;
   load_player( player );
   entry = dossier->data[idx];
   previnfo = sprintf( "Originally added by %s%s%s at %s:\n%s\n---\n",
     CL_CREATOR, entry->creator, CL_RESET, ctime( entry->time ),
     entry->comment );
   entry->time    = time();
   entry->creator = capitalize( creator->query_name() );
   entry->event   = lower_case( event );
   entry->comment = previnfo + update;
   dossier->data[idx] = entry;
   if( event != "alert" ) {
      decrement_alerts_for(player);
   }
   save_player( player );
   return 1;
}
void clear_alerts_for( string player ) {
   player = lower_case(player);
   if( !_alerts ) {
      _alerts = ([ ]);
   }
   map_delete( _alerts, player );
   save_handler_data();
}
int increment_alerts_for( string player ) {
   player = lower_case(player);
   if( !_alerts ) {
      _alerts = ([ ]);
   }
   if( !PLAYER_HANDLER->test_user(player) ) {
      return 0;
   }
   if( undefinedp( _alerts[player] ) ) {
      _alerts[player] = 1;
   } else {
      _alerts[player] = _alerts[player] + 1;
   }
   save_handler_data();
   return _alerts[player];
}
int decrement_alerts_for( string player ) {
   player = lower_case(player);
   if( !_alerts ) {
      _alerts = ([ ]);
   }
   if( undefinedp( _alerts[player] ) ) {
      return 0;
   }
   _alerts[player] = _alerts[player] - 1;
   if(_alerts[player] <= 0 ) {
      map_delete( _alerts, player );
   }
   save_handler_data();
   return _alerts[player];
}
string * query_online_alerts() {
   if ( !_alerts ) {
      _alerts = ([ ]);
      return ({ });
   }
   return filter( keys(_alerts), (: find_player($1) :) );
}
private void correct_alts_for(string player) {
  string main;
  string *alts, *tmp, alt;
  if(!player)
    return;
  player = lower_case(player);
  correcting_alts = 1;
  load_player(player);
  main = dossier->main_alt;
  alts = copy(dossier->alts);
  if(main && !no_recurse) {
    if(sizeof(alts)) {
      dossier->alts = ({ });
      save_player(player);
    }
    if((!PLAYER_HANDLER->test_user(player) ||
        !PLAYER_HANDLER->test_user(main))) {
      correcting_alts = 0;
      no_recurse = 1;
      correct_alts_for(main);
      load_player(player);
    }
    return;
  }
  if(!PLAYER_HANDLER->test_user(player)) {
    if(!sizeof(alts)) {
      if(this_player()->query_name("ceres"))
        write("No alts for : " + player + "\n");
      correcting_alts = 0;
      return;
    }
    tmp = filter(alts, (: PLAYER_HANDLER->test_user($1) :));
    if(sizeof(tmp)) {
      main = tmp[0];
    }
  }
  if(main) {
    dossier->main_alt = main;
    dossier->alts = ({ });
    save_player(player);
  }
  if(main)
    load_player(main);
  if(sizeof(alts)) {
    tmp = filter(alts, (: !find_player($1) &&
                        !PLAYER_HANDLER->test_user($1) :));
    tmp = uniq_array(dossier->old_alts + tmp);
  } else
    alts = ({ });
  alts = uniq_array(alts + dossier->alts) - ({ main });
  alts = filter(alts, (: find_player($1) || PLAYER_HANDLER->test_user($1) :));
  if(main && (alts != dossier->alts || tmp != dossier->old_alts)) {
    dossier->alts = copy(alts);
    dossier->old_alts = copy(tmp);
    save_player(main);
    foreach(alt in alts) {
      if(dossier->main_alt != main) {
        load_player(alt);
        dossier->main_alt = main;
        save_player(alt);
      }
    }
    foreach(alt in tmp) {
      if(dossier->main_alt != main) {
        load_player(alt);
        dossier->main_alt = main;
        save_player(alt);
      }
    }
  }
  load_player(player);
  correcting_alts = 0;
}
void reregister_parent( string player ) {
   string main;
   string * alts;
   if ( !player ) {
      return;
   }
   player = lower_case(player);
   correcting_alts = 1;
   load_player( player );
   main = dossier->main_alt;
   if ( main ) {
      load_player(main);
      alts = dossier->alts;
      if ( !alts || !sizeof( alts ) ) {
         dossier->alts = ({ player });
      } else if ( member_array( player, alts ) == -1 ) {
         dossier->alts = alts + ({ player });
      } else {
         return;
      }
      save_player( main );
   }
}
void player_refreshed(mixed player, int totally) {
  class dbentry new_entry;
  string comment;
  if(objectp(player))
    player = player->query_name();
  switch (totally) {
  case PARTIAL_REFRESH:
    comment = "They did a partial refresh.";
    break;
  case TOTAL_REFRESH:
    comment = "They did a total and complete refresh.  (Even refreshed their "
      "breath)";
    break;
  default:
    comment = "They did some weird sort of unknown refresh.";
    break;
  }
  load_player(player);
  new_entry = new(class dbentry,
                  time:       time(),
                  creator:    "Refresh Handler",
                  event:      "refresh",
                  comment:    comment,
                  extra:      0);
  do_debouncing(player, new_entry);
  save_player(player);
}
void player_deleted(mixed player, int deleted) {
  class dbentry new_entry;
  string *tmp, *tmp2, alt, main;
  if(objectp(player))
    player = player->query_name();
  if(file_size(filename(player)) == -1)
    return;
  clear_alerts_for(player);
  load_player(player);
  new_entry = new(class dbentry,
                  time:       time(),
                  creator:    "Refresh Handler",
                  event:      "delete",
                  comment:    "Player deleted",
                  extra:      0);
  do_debouncing(player, new_entry);
  save_player(player);
  if(dossier->main_alt) {
    main = dossier->main_alt;
    dossier->main_alt = 0;
    save_player(player);
    load_player(main);
    dossier->alts -= ({ player });
    dossier->old_alts += ({ player });
    save_player(main);
    return;
  }
  if(dossier->alts && sizeof(dossier->alts)) {
    tmp = filter(dossier->alts, (: PLAYER_HANDLER->test_user($1) :));
    if(sizeof(tmp))
      main = tmp[0];
    tmp2 = dossier->old_alts;
    load_player(main);
    dossier->main_alt = 0;
    if(sizeof(tmp) > 1)
      dossier->alts = copy(tmp[1..]);
    dossier->old_alts = copy(tmp2 + ({ player }));
    save_player(main);
    foreach(alt in dossier->alts) {
      load_player(alt);
      dossier->main_alt = main;
      save_player(alt);
    }
    return;
  }
}
void player_created(string player) {
  if(file_size(filename(player)) == -1)
    return;
  load_player(player);
  if(dossier->main_alt) {
    dossier->main_alt = 0;
    dossier->alts = ({ });
    save_player(player);
  }
  return;
}
void fix_alts(mixed player) {
  string *alts, alt, main;
  if(objectp(player))
    player = player->query_name();
  if(file_size(filename(player)) == -1)
    return;
  load_player(player);
  if(dossier->main_alt) {
    main = dossier->main_alt;
    load_player(dossier->main_alt);
    if(!PLAYER_HANDLER->test_user(dossier->main_alt)) {
      if(sizeof(alts))
        main = alts[0];
    }
  } else {
    main = player;
  }
  alts = ({});
  if( dossier->alts ) {
     alts = alts + dossier->alts;
  }
  if( dossier->old_alts ) {
     alts = alts + dossier->old_alts;
  }
  alts = uniq_array( alts + ({ player }));
  alts -= ({ main });
  dossier->main_alt = 0;
  dossier->alts = filter(alts, (: PLAYER_HANDLER->test_user($1) :));
  dossier->old_alts = filter(alts, (: !PLAYER_HANDLER->test_user($1) :));
  foreach(alt in alts) {
    load_player(alt);
    dossier->main_alt = main;
    dossier->alts = 0;
    dossier->old_alts = 0;
    save_player(alt);
  }
}
void reset() {
    if ( sizeof( _dossier_cache ) > CACHE_SIZE ) {
        _dossier_cache = ([ ]);
    }
}
string query_access_history( string player ) {
  mapping history;
  string ret = "";
  load_player(player);
  history = dossier->access_log;
  ret += sprintf( "Access log for player %s:\n", capitalize( player ) );
  foreach( string name in sort_array( keys( history ),
                                      (: $(history)[$2] - $(history)[$1] :) ))
    ret += sprintf( "%12s:\t%s.\n", capitalize(name),
                    query_time_string( time() - history[name], 2 ) + " ago");
  return ret;
}
mixed *stats() {
    return ({
        ({ "cache hits", _dossier_cache_hits }),
        ({ "total requests", _dossier_total }),
        ({ "cache hit %", to_int(_dossier_cache_hits * 100.0 /
                                 _dossier_total) }),
        ({ "current cache size", sizeof( _dossier_cache ) })
    });
}