#include <login.h>
#ifdef LOGIN_DEBUG
#undef MAX_COMPRESSED_PLAYERS
#undef MAX_UNCOMPRESSED_PLAYERS
#undef MAX_PLAYERS
#define LOGIN_MAX_COMPRESSED_PLAYERS 2
#define MAX_UNCOMPRESSED_PLAYERS 1
#define MAX_PLAYERS (MAX_COMPRESSED_PLAYERS + MAX_UNCOMPRESSED_PLAYERS)
#endif
#ifdef LOGIN_DEBUG
#define is_compressed_login(x) (strsrch((x)->query_name(), "test") > -1)
#else
#define is_compressed_login(x) (compressedp(x))
#endif
#define COMPRESSED_INTAKE_COUNT 5
#ifdef USE_RAMDISK
#define SAVE_TIME 300
#else
#define SAVE_TIME 900
#endif
#define NEW_SAVE_TIME 15
#define SAVE_NAME "/save/login_handler"
#define BUFFER_TIME 30
#define LOCKDOWN_TIME 900
#define MAX_FAILURES 3
class login_information {
    mixed ob;
    string funct;
}
mapping _static_login_calls;
nosave mapping _dynamic_login_calls;
nosave string _best;
nosave string _worst;
nosave string *_players_on;
nosave mapping _compressed_players_on;
nosave mapping _telnet_players_on;
nosave object *_compressed_login_queue;
nosave object *_telnet_login_queue;
nosave int _compressed_login_count;
nosave string enter_log;
nosave int last_entry;
nosave mapping messages;
nosave mapping lockdowns;
nosave int _creators;
nosave int _players;
nosave int _login_q;
nosave int _next_user_log;
nosave int _title_call;
nosave int _save_call;
nosave int _out_q;
nosave int _q_time;
nosave int _last_queue_time;
nosave int _last_queue_result;
int is_discworld_full(int test_login_queue);
void write_log(string event, string name, int guest, string other);
void save_users();
private void store_user_count();
private void log_user_count();
protected void check_all_titles( string player );
private void do_all_calls(string player, string event);
private void do_call(class login_information login_inf,
  string player, int event);
int is_uncompressed_full( int );
void create() {
    object pl;
    string name;
    _static_login_calls = ([ ]);
    _dynamic_login_calls = ([ ]);
    seteuid( "Root" );
    unguarded((: restore_object, SAVE_NAME :));
    foreach(name in keys(_static_login_calls)) {
      if(!sizeof(_static_login_calls[name])) {
        map_delete(_static_login_calls, name);
      }
      catch(unguarded((: save_object, SAVE_NAME :)));
    }
    _compressed_players_on = ([ ]);
    _telnet_players_on = ([ ]);
    _players_on = ({ });
    foreach(pl in users()) {
        if (is_compressed_login(pl)) {
            _compressed_players_on[ pl->query_name() ] = 1;
        }
        else {
            _telnet_players_on[ pl->query_name() ] = 1;
        }
        _players_on += ({ pl->query_name() });
    }
    _compressed_login_queue = ({ });
    _telnet_login_queue = ({ });
    _compressed_login_count = 1;
    _save_call = call_out( "save_users", NEW_SAVE_TIME );
    _next_user_log = time() + 3601 - (time() % 3600);
    enter_log = "";
    last_entry = time();
    call_out("clean_lockdowns", 3600);
    write_log("Periodic", "", 0, "");
}
mapping query_static_login_calls() {
    return copy(_static_login_calls);
}
mapping query_dynamic_login_calls() {
    return copy(_dynamic_login_calls);
}
string query_best() { return _best; }
string query_worst() { return _worst; }
string *query_players_on() {
    return keys( _compressed_players_on ) + keys( _telnet_players_on );
}
object *query_login_queue() {
    return _compressed_login_queue + _telnet_login_queue;
}
void add_to_login_queue(object login_ob) {
    if ( is_compressed_login( login_ob ) ) {
        _compressed_login_queue += ({ login_ob });
    }
    else {
        _telnet_login_queue += ({ login_ob });
    }
}
void remove_from_login_queue(object ob) {
    _compressed_login_queue -= ({ ob });
    _telnet_login_queue -= ({ ob });
}
int can_jump_queue( object ob ) {
    return ob->query_creator() || ob->query_net_dead() ||
        ob->query_property( "test character" );
}
object pop_from_login_queue() {
    object ob;
    object *login_queue;
    login_queue = query_login_queue();
    if ( !sizeof( login_queue ) ) {
        return 0;
    }
    if(time() != _q_time){
      _q_time = time();
      _out_q = 0;
    }
    _out_q++;
    foreach( ob in _compressed_login_queue ) {
        if ( can_jump_queue( ob ) ) {
            remove_from_login_queue( ob );
            return ob;
        }
    }
    reset_eval_cost();
    if(sizeof(_telnet_login_queue) &&
       !is_uncompressed_full(WITHOUT_LOGIN_QUEUE)) {
      foreach( ob in _telnet_login_queue ) {
        if ( can_jump_queue( ob ) ) {
          remove_from_login_queue( ob );
          return ob;
        }
      }
    }
    if ( sizeof( _compressed_login_queue) &&
         _compressed_login_count < COMPRESSED_INTAKE_COUNT ) {
        _compressed_login_count++;
        ob = _compressed_login_queue[ 0 ];
        _compressed_login_queue = _compressed_login_queue[ 1.. ];
    } else {
        _compressed_login_count = 0;
        ob = _telnet_login_queue[ 0 ];
        _telnet_login_queue = _telnet_login_queue[ 1.. ];
    }
    return ob;
}
int add_static_login_call(string player, mixed funct, mixed obj) {
  class login_information login_inf;
  if (!stringp(funct) || !stringp(obj) || !stringp(player)) {
    return 0;
  }
  if(obj[0..3] == "/w/")
    return 0;
  if(_static_login_calls[player]) {
    foreach (login_inf in _static_login_calls[player]) {
      if (login_inf->ob == obj &&
    login_inf->funct == funct) {
  return 1;
      }
    }
  }
  if (!_static_login_calls[player]) {
    _static_login_calls[player] = ({ });
  }
  login_inf = new (class login_information, funct : funct, ob : obj);
  _static_login_calls[player] += ({ login_inf });
  catch(unguarded((: save_object, SAVE_NAME :)));
  return 1;
}
int remove_static_login_call(string player, mixed funct, mixed obj) {
  class login_information login_inf;
  if (!stringp(funct) || !stringp(obj) || !stringp(player)) {
    return 0;
  }
  if (_static_login_calls[player]) {
    foreach (login_inf in _static_login_calls[player]) {
      if (login_inf->ob == obj &&
          login_inf->funct == funct) {
        _static_login_calls[player] -= ({ login_inf });
        if(!sizeof(_static_login_calls[player]))
          map_delete(_static_login_calls, player);
        catch(unguarded((: save_object, SAVE_NAME :)));
        return 1;
      }
    }
  }
  return 0;
}
int add_dynamic_login_call(string player, mixed funct, mixed obj) {
    class login_information login_inf;
    if (stringp(obj) || objectp(obj)) {
        if (!stringp(funct)) {
            return 0;
        }
    } else if (!functionp(funct)) {
        return 0;
    }
    if (!_dynamic_login_calls[player]) {
        _dynamic_login_calls[player] = ({ });
    }
    login_inf = new (class login_information, funct : funct, ob : obj);
    _dynamic_login_calls[player] += ({ login_inf });
    return 1;
}
int remove_dynamic_login_call(string player, mixed funct, mixed obj) {
    class login_information login_inf;
    if (stringp(obj) || objectp(obj)) {
        if (!stringp(funct)) {
            return 0;
        }
    } else if (!functionp(funct)) {
        return 0;
    }
    if (_dynamic_login_calls[player]) {
        foreach (login_inf in _dynamic_login_calls[player]) {
            if (login_inf->ob == obj &&
              login_inf->funct == funct) {
                _dynamic_login_calls[player] -= ({ login_inf });
                return 1;
            }
        }
    }
    return 0;
}
void update_players_on( string player ) {
    object ob = find_player( player );
    if ( !ob ) {
        return;
    }
    if ( is_compressed_login( ob ) ) {
        if ( undefinedp( _compressed_players_on[ player ] ) ) {
            _compressed_players_on[ player ] = 1;
        }
    }
    else {
        if ( undefinedp( _telnet_players_on[ player ] ) ) {
            _telnet_players_on[ player ] = 1;
        }
    }
    if ( member_array( player, _players_on ) == -1 ) {
        _players_on += ({ player });
    }
}
int tidy_players_on( string player ) {
    int pos;
    int ret;
    ret = 0;
    if ( _compressed_players_on[ player ] ) {
        map_delete( _compressed_players_on, player );
        ret = 1;
    }
    if ( _telnet_players_on[ player ] ) {
        map_delete( _telnet_players_on, player );
        ret = 1;
    }
    pos = member_array( player, _players_on );
    if ( pos != -1 ) {
        _players_on = _players_on[0..pos-1] + _players_on[pos+1..];
        ret = 1;
    }
    return ret;
}
int player_logon(string player, int guest, string ip) {
    if(lower_case(player) != (string)previous_object()->query_name()) {
        return 0;
    }
    update_players_on( player );
    do_all_calls(player, LOGIN);
    if (find_call_out(_title_call) == -1) {
        _title_call = call_out("check_all_titles", 5, player );
    }
    write_log("Enter", player, guest, ip);
}
private void do_all_calls(string player, string event_t) {
  class login_information login_inf;
  if (_static_login_calls[player]) {
    foreach (login_inf in _static_login_calls[player]) {
      call_out((: do_call :), 1, login_inf,
               player, event_t );
    }
  }
  if (_static_login_calls["all"]) {
    foreach (login_inf in _static_login_calls["all"]) {
      call_out((: do_call :), 1, login_inf,
               player, event_t );
    }
  }
  if (_dynamic_login_calls[player]) {
    foreach (login_inf in _dynamic_login_calls[player]) {
      call_out((: do_call :), 1, login_inf,
               player, event_t );
    }
  }
  if (_dynamic_login_calls["all"]) {
    foreach (login_inf in _dynamic_login_calls["all"]) {
      call_out((: do_call :), 1, login_inf,
               player, event_t );
    }
  }
}
private void do_call(class login_information login_inf,
                     string player, int event_t) {
  object ob;
  if (!find_player(player) || find_player(player)->query_invis() < 2) {
    if (!functionp(login_inf->funct)) {
      if(login_inf->ob && login_inf->funct)
        catch(ob = load_object(login_inf->ob));
      if ( ob ) {
        catch(call_other(ob, login_inf->funct, player,
                         event_t));
      } else {
        tell_creator("ceres", "failed to load %s", login_inf->ob);
      }
    } else {
      catch(evaluate(login_inf->funct, player, event_t));
    }
  }
}
int player_logout(string player) {
    object ob;
    do_all_calls(player, LOGOUT);
    if ( tidy_players_on( player ) ) {
        if (find_call_out(_title_call) == -1) {
            _title_call = call_out("check_all_titles", 5, player );
        }
    }
    if(find_call_out(_save_call) == -1) {
        _save_call = call_out("save_users", NEW_SAVE_TIME );
    }
    while (sizeof(query_login_queue()) &&
        !is_discworld_full(WITHOUT_LOGIN_QUEUE) ) {
        ob = pop_from_login_queue();
        if (ob) {
            ob->remove_from_login_queue();
        }
    }
    write_log("Exit", player, 0, "");
    return 1;
}
int player_net_dead(string player) {
    object ob;
    if ( tidy_players_on( player ) ) {
        do_all_calls(player, NETDEATH);
        if (find_call_out(_title_call) == -1) {
            _title_call = call_out("check_all_titles", 5, player );
        }
    }
    while ( sizeof(query_login_queue()) && !is_discworld_full(WITHOUT_ANY_LOGINS) ) {
        ob = pop_from_login_queue();
        if (ob) {
            ob->remove_from_login_queue();
        }
    }
    write_log("NDead", player, 0, "");
    return 1;
}
int player_reconnected(string player) {
    update_players_on(player);
    do_all_calls(player, RECONNECT);
    if (find_call_out(_title_call) == -1) {
        _title_call = call_out("check_all_titles", 5, player);
    }
    write_log("Recon", player, 0, query_ip_name(find_player(player)));
}
protected void check_all_titles( string player ) {
    int al, good, bad;
    object good_thing, bad_thing, thing, *things;
    good = -250;
    bad = 250;
    things = users();
    foreach( thing in things ) {
      if (!thing || thing->query_creator() ) {
        continue;
      }
      al = (int)thing->query_al();
      if ( al > bad ) {
        bad = al;
        bad_thing = thing;
      }
      if ( al < good ) {
        good = al;
        good_thing = thing;
      }
    }
    if ( bad_thing ) {
      if ( stringp( _worst ) && ( _worst != player ) ) {
        thing = find_player( _worst );
      } else {
        thing = 0;
      }
      if ( bad_thing != thing ) {
        if ( thing ) {
          thing->remove_title( "align" );
        }
        switch ( (int)bad_thing->query_gender() ) {
        case 1 :
          bad_thing->set_title( "align", "Lord of Darkness" );
          break;
        case 2 :
          bad_thing->set_title( "align", "Lady of Darkness" );
          break;
        default :
          bad_thing->set_title( "align", "Monster of Darkness" );
        }
        _worst = (string)bad_thing->query_name();
      }
    }
    if ( good_thing ) {
      if ( stringp( _best ) && ( _best != player ) ) {
        thing = find_player( _best );
      } else {
        thing = 0;
      }
      if ( good_thing != thing ) {
        if ( thing ) {
          thing->remove_title( "align" );
        }
        switch ( (int)good_thing->query_gender() ) {
        case 1 :
          good_thing->set_title( "align", "Lord of Light" );
          break;
        case 2 :
          good_thing->set_title( "align", "Lady of Light" );
          break;
        default :
          good_thing->set_title( "align", "Creature of Light" );
        }
        _best = (string)good_thing->query_name();
      }
    }
}
void save_users() {
    int number;
    int next_time;
    string word;
    object thing;
    number = sizeof( _players_on );
    if ( !number ) {
        _players_on = query_players_on();
        _save_call = call_out("save_users", NEW_SAVE_TIME );
        return;
    }
    store_user_count();
    if(_next_user_log < time()) {
        log_user_count();
    }
    word = _players_on[ 0 ];
    thing = find_player( word );
    if ( objectp( thing ) && ( number > 1 ) ) {
        if ( environment( thing ) ) {
            thing->save_me();
        }
        _players_on = _players_on[1..] + ({ word });
    } else {
        _players_on = _players_on[1..] + ({ word });
    }
    next_time = SAVE_TIME / number;
    if ( next_time > 10 ) {
        next_time = 10;
    }
    _save_call = call_out( (: save_users :), next_time );
}
int int_is_discworld_full(int logins) {
    object *players;
    int compressed;
    int uncompressed;
    int ret;
    int ext;
    players = users();
    switch (logins) {
    case WITHOUT_LOGINS_NOT_IN_QUEUE :
        players = filter(players, (: objectp($1) && !$1->query_login_ob() &&
            !$1->query_creator() :)) + query_login_queue();
        break;
    case WITHOUT_LOGIN_QUEUE :
        players -= query_login_queue();
        players = filter(players, (: objectp($1) && !$1->query_creator() :));
        break;
    case WITHOUT_ANY_LOGINS :
        players = filter(players, (: objectp($1) && !$1->query_login_ob() &&
            !$1->query_creator() :));
        ext = _out_q;
        break;
    default :
        players = filter(players, (: objectp($1) && !$1->query_creator() :));
        break;
    }
    if(time() != _q_time){
      ext = 0;
      _out_q = 0;
      _q_time = time();
    }
    compressed = sizeof( filter( players, (: is_compressed_login($1) :) )  ) + ext;
    uncompressed = sizeof( players ) - compressed;
    ret = DISCWORLD_IS_EMPTY;
    if ( compressed >= MAX_COMPRESSED_PLAYERS ) {
        ret |= COMPRESSED_FULL;
    }
    if ( uncompressed >= MAX_UNCOMPRESSED_PLAYERS ) {
        ret |= UNCOMPRESSED_FULL;
    }
    return ret;
}
int is_compressed_full( int logins ) {
    return int_is_discworld_full( logins ) & COMPRESSED_FULL;
}
int is_uncompressed_full( int logins ) {
    return int_is_discworld_full( logins ) & UNCOMPRESSED_FULL;
}
int is_discworld_full(int logins) {
    int ret;
    ret = int_is_discworld_full( logins );
    ret = (ret & COMPRESSED_FULL) && (ret & UNCOMPRESSED_FULL);
    return ret;
}
private void store_user_count() {
    object pl;
    int current_players, current_creators, current_login_q;
    string *logins_n;
    foreach(pl in users()) {
      if (pl && !pl->query_login_ob()) {
        if (pl->query_creator()) {
          current_creators++;
        } else {
          current_players++;
        }
      }
    }
    logins_n = map(LOGIN_HANDLER->query_login_queue(),
      (: $1->query_cap_name() :));
    logins_n = sort_array(logins_n, 1);
    current_login_q = sizeof(logins_n);
    if(current_players + current_login_q > _players + _login_q) {
        _players = current_players;
        _creators = current_creators;
        _login_q = current_login_q;
    }
}
private void log_user_count() {
    log_file("USERS", "%s %d %d %d\n" ,ctime(time()), _creators, _players,
      _login_q);
    _creators = 0;
    _players = 0;
    _login_q = 0;
    _next_user_log = time() + 3601 - (time() % 3600);
}
void write_log(string event, string name, int guest, string other) {
    switch(event) {
    case "Enter":
        enter_log += sprintf( "%s [Enter] %-15s %s%s\n",
          ctime(time())[4..18], name,
          guest?"(guest) ":"",
          other);
        break;
    case "Su":
        enter_log += sprintf( "%s [Su]    %15-s %15-s\n",
          ctime(time())[4..18], name, other);
        break;
    case "Periodic":
        call_out("write_log", BUFFER_TIME, "Periodic", "", 0, "");
        if (sizeof(enter_log) && time() - last_entry > BUFFER_TIME) {
            unguarded((: write_file, "/d/admin/log/ENTER.log", enter_log :));
            enter_log = "";
            last_entry = time();
        }
        return;
    case "Recon":
        enter_log += sprintf( "%s [Recon] %15-s %s\n",
          ctime(time())[4..18], name, other);
        break;
    default:
        enter_log += sprintf("%s %-7s %15-s\n", ctime(time())[4..18],
          "["+event+"]", name);
        break;
    }
    last_entry = time();
    if(sizeof(enter_log) > 1024) {
        unguarded((: write_file, "/d/admin/log/ENTER.log", enter_log :));
        enter_log = "";
    }
}
void dest_me() {
    unguarded((: write_file, "/d/admin/log/ENTER.log", enter_log :));
    enter_log = "";
    destruct(this_object());
}
string get_message(string mess_name) {
    if(!messages)
        messages = ([ ]);
    if(mess_name[0..4] != "/doc/")
        return 0;
    if(!messages[mess_name])
        messages[mess_name] = read_file(mess_name);
    return messages[mess_name];
}
void clear_messages() {
    messages = ([ ]);
}
int site_lockeddown(string ip_addr) {
    if(!lockdowns)
        lockdowns = ([ ]);
    if(lockdowns[ip_addr] &&
      (sizeof(lockdowns[ip_addr]) >= MAX_FAILURES) &&
      (lockdowns[ip_addr][0] > time() - LOCKDOWN_TIME))
        return 1;
    return 0;
}
void failed_login(string ip_addr) {
  int i;
  if(!lockdowns)
    lockdowns = ([ ]);
  if(!lockdowns[ip_addr])
    lockdowns[ip_addr] = ({ time() });
  else {
    for(i=0; i<sizeof(lockdowns[ip_addr]); i++)
      if(lockdowns[ip_addr][i] < time() - LOCKDOWN_TIME) {
        lockdowns[ip_addr] -= ({ lockdowns[ip_addr][i] });
        i--;
      }
    lockdowns[ip_addr] += ({ time() });
    if(sizeof(lockdowns[ip_addr]) > MAX_FAILURES) {
      lockdowns[ip_addr] =
        lockdowns[ip_addr][sizeof(lockdowns[ip_addr])-MAX_FAILURES..];
    }
  }
}
void clean_lockdowns() {
  string ip;
  call_out("clean_lockdowns", 1800);
  foreach(ip in keys(lockdowns)) {
    if(lockdowns[ip][sizeof(lockdowns[ip])-1] < time() - LOCKDOWN_TIME) {
      map_delete(lockdowns, ip);
    }
  }
}
void clear_lockdowns(string ip) {
  if(!ip)
    lockdowns = ([ ]);
  else if(lockdowns[ip])
    map_delete(lockdowns, ip);
}
void query_lockdowns() {
    printf("%O\n", lockdowns);
}
void reset() {
    if (find_call_out(_save_call) == -1) {
        save_users();
    }
}