#define MAX_SIZE 50000
#define LIV "/obj/handlers/livings"
#define LOG_NAME(X) ((X[0] == '/') ? X : "/log/"+X)
#include <login.h>
#include <player_handler.h>
#include <playtesters.h>
#if !efun_defined(base_name)
inherit "/secure/simul_efun/base_name";
#endif
string back_trace();
#if !efun_defined(event)
void event(mixed,string,mixed ...);
#endif
#if !efun_defined(add_action)
int _notify_fail(string);
int living(object ob);
object find_player(string);
#endif
private nosave int _callouttime;
private nosave mapping _calloutfunc = ([]);
private nosave mapping _log_file_info = ([ ]);
private nosave int _log_file_flush_id;
private nosave mapping _loggers = ([ ]);
private nosave string _reset_eval_message="simul_efun updated";
private nosave int _reset_eval_message_count=1;
private nosave int _in_reference_allowed;
#define DELAY_LOG_FLUSH 15
varargs void say(string str, mixed avoid)
{
  if (!pointerp(avoid)) {
    avoid = ({ this_player(), previous_object() }) + ({ avoid });
  } else {
    avoid += ({ this_player(), previous_object() });
  }
  if (!environment(previous_object())) {
    if(this_player() && environment(this_player())) {
      event(environment(this_player()), "say", str, avoid);
    } else {
      event(previous_object(), "say", str, avoid);
    }
  } else {
    if (environment(environment(previous_object()))) {
      event(environment(environment(previous_object())), "say", str, avoid);
    } else {
      event(environment(previous_object()), "say", str, avoid);
    }
  }
}
varargs void tell_room(mixed ob, string str, mixed avoid) {
  if (!ob || !(objectp(ob) || stringp(ob))) {
    return ;
  }
  if (stringp(ob)) {
    ob = load_object(ob);
  }
  event(ob, "say", str, avoid);
}
void tell_object(object ob, string str) {
  if (objectp(ob)) {
    ob->do_efun_write( str );
  }
}
#if !efun_defined(reference_allowed)
varargs int reference_allowed(object referree, mixed referrer) {
  string referrer_name;
  string *allowed;
  object referrer_obj;
  int ret, invis;
  if(!referree)
    return 0;
  invis = (int)referree->query_invis();
  if(!invis || !referree->query_creator() || _in_reference_allowed)
    return 1;
  _in_reference_allowed = 1;
  if(!referrer)
    referrer = this_player();
  if (objectp(referrer)) {
    if(!referrer || (referree == referrer)) {
      _in_reference_allowed = 0;
      return 1;
    }
    referrer_name = referrer->query_name();
    referrer_obj = referrer;
  } else if (stringp(referrer)) {
    referrer_name = referrer;
    referrer_obj = find_player(referrer);
  } else {
    _in_reference_allowed = 0;
    return 0;
  }
  if(!referrer_name) {
    _in_reference_allowed = 0;
    return 1;
  }
  allowed = (string *)referree->query_allowed();
  if ( pointerp( allowed ) ) {
    if ( member_array( referrer_name, allowed ) != -1 ||
         (member_array("playtesters", allowed) != -1 &&
          PLAYTESTER_HAND->query_playtester(referrer_name))) {
      _in_reference_allowed = 0;
      return 1;
    }
  }
  switch(invis) {
  case 3 :
    ret = master()->high_programmer( referrer_name );
    break;
  case 2 :
    ret = master()->query_lord( referrer_name );
    break;
  case 1 :
    if(referrer_obj)
      ret = referrer_obj->query_creator();
    else
      ret = PLAYER_HANDLER->test_creator( referrer_name );
    break;
  default :
    ret = 1;
  }
  _in_reference_allowed = 0;
  return ret;
}
#endif
object find_living( string word ) {
   object thing;
   if ( !word ) {
      return 0;
   }
#if efun_defined(find_living)
   thing = efun::find_living( word );
#else
   thing = LIV->find_living( word );
#endif
   if ( !thing || !this_player() ) {
      return thing;
   }
   if ( reference_allowed( thing ) ) {
      return thing;
   }
   return 0;
}
object find_player( string word ) {
   object thing;
   if ( !word ) {
      return 0;
   }
#if efun_defined(find_player)
   thing = efun::find_player( word );
#else
   thing = LIV->find_player( word );
#endif
   if ( !thing || !this_player() ) {
      return thing;
   }
    if ( reference_allowed( thing ) && thing->query_property( "player" ) ) {
      return thing;
   }
   return 0;
}
object *users() {
   if ( !this_player() || ( previous_object() == master() ) ||
         ( previous_object() == find_object( "/obj/shut" ) ) ||
         ( previous_object() == find_object( "/obj/handlers/livings") ) ) {
      return efun::users();
   }
   return filter( efun::users(), (: $1 && reference_allowed($1) :) );
}
object *named_livings() {
#if efun_defined(named_livings)
  return filter( efun::named_livings(), (: reference_allowed :) );
#else
  return filter( LIV->named_livings(), (: reference_allowed :) );
#endif
}
object *children(string name) {
   if (strsrch(name, "global/lord") != -1) {
      return filter( efun::children(name), (: reference_allowed :) );
   }
   return efun::children(name);
}
void user_event( mixed from, mixed first, mixed args ... ) {
   if ( stringp( from ) ) {
      call_other( efun::users(), "event_"+ from, previous_object(),
            first, args ... );
   } else {
      if ( objectp( from ) && stringp( first ) ) {
         call_other( efun::users(), "event_"+ first, from, args ... );
      }
   }
}
mixed unguarded(function f);
void flush_log_files() {
   string fname;
   string data;
   int size;
   _log_file_flush_id = 0;
   foreach (fname, data in _log_file_info) {
     size = file_size(LOG_NAME(fname));
      if (size > MAX_SIZE) {
        if ( file_size( LOG_NAME(fname) + ".5" ) >= 0 ) {
          unguarded((: rm, LOG_NAME(fname)+".5" :));
        }
        if ( file_size( LOG_NAME(fname) + ".4" ) >= 0 ) {
          unguarded((: rename, LOG_NAME(fname)+".4", LOG_NAME(fname)+".5" :));
        }
        if ( file_size( LOG_NAME(fname) + ".3" ) >= 0 ) {
          unguarded((: rename, LOG_NAME(fname)+".3", LOG_NAME(fname)+".4" :));
        }
        if ( file_size( LOG_NAME(fname) + ".2" ) >= 0 ) {
          unguarded((: rename, LOG_NAME(fname)+".2", LOG_NAME(fname)+".3" :));
        }
        if ( file_size( LOG_NAME(fname) + ".1" ) >= 0 ) {
          unguarded((: rename, LOG_NAME(fname)+".1", LOG_NAME(fname)+".2" :));
        }
        unguarded((: rename, LOG_NAME(fname), LOG_NAME(fname)+".1" :));
      }
      map_delete(_log_file_info, fname);
      if(size == -2)
        fname = fname + "BAD";
      unguarded((: write_file, LOG_NAME(fname), data :));
   }
   _log_file_info = ([ ]);
}
varargs void log_file(string name, string fmt, mixed *args ...) {
  if ( strlen( fmt ) > 8000 ) {
    fmt = fmt[ 0 .. 7999 ] +"\n\nPlus more...\n\n";
  }
  _loggers[name] = base_name(previous_object());
  fmt = terminal_colour(fmt, ([]));
  if (!_log_file_flush_id) {
     _log_file_flush_id = call_out((: flush_log_files :), DELAY_LOG_FLUSH);
  }
  if (!_log_file_info[name]) {
     _log_file_info[name] = "";
  }
  if (sizeof(args)) {
    _log_file_info[name] += sprintf(fmt, args ...);
  } else {
    _log_file_info[name] += fmt;
  }
}
mapping query_loggers() { return _loggers; }
#ifdef MUD_NAME
string mud_name() {
  return capitalize(MUD_NAME);
}
#endif
void cat(string file, int start_line, int number) {
  string bing;
  bing = read_file(file, start_line, number);
  if (bing) {
    printf("%s", bing[0..5000]);
  }
}
#ifdef NEW_DRIVER
int wizardp(mixed arg) {
  if (!objectp(arg)) {
    return 0;
  }
  return interactive(arg) && arg->query_creator();
}
#endif
int exec(object to, object from) {
  string s;
  object prev;
  if(!objectp(to) || !objectp(from))
    return 0;
  if (file_name(previous_object())[0..12] == "/secure/login" ||
      file_name(previous_object())[0..13] == "/secure/nlogin") {
    return efun::exec(to, from);
  }
  s = "";
  if (prev = this_player()) {
    s += "TP:"+ sprintf("%8s ", prev -> query_name());
  }
  if (prev = this_player(1)) {
    s += "TP1:"+ sprintf("%8s ", prev -> query_name());
  }
  s += "PO:"+ sprintf("%8s ", file_name(previous_object()));
  log_file("ILLEGAL", "Exec: %-40s : %s\n", s, ctime( time() ) );
  return 0;
}
varargs int call_out(mixed fun, int delay, mixed *args ...) {
  string func;
  if (_callouttime != time()) {
    _callouttime = time();
    _calloutfunc = ([]);
  }
  if(delay == 0) {
    func = functionp(fun)?""+functionp(fun):fun +
      file_name(previous_object());
    if(_calloutfunc[func] == -1)
      delay = 2;
    else if(++_calloutfunc[func] > 100) {
      delay = 2;
      _calloutfunc[func] = -1;
      if ( stringp(previous_object()->query_name())) {
        log_file("CALL_OUT_LOG", ctime(time()) + ": " +
                 "Object %O (%s) seems to loop in function %O.\n",
                 previous_object(), previous_object()->query_name(), fun);
      } else {
        log_file("CALL_OUT_LOG", ctime(time()) + ": " +
                 "Object %O (%s) seems to loop in function %O.\n",
                 previous_object(), file_name(previous_object()), fun);
      }
    }
  }
  return evaluate(bind((: efun::call_out($(fun), $(delay), $(args) ... ) :)
                       , previous_object()));
}
string query_verb() {
   string verb;
#if efun_defined(query_verb)
   verb = efun::query_verb();
#else
   verb = "";
#endif
   if ( ( verb != "" ) || !objectp( this_player() ) ) {
      return verb;
   }
   return (string)this_player()->query_current_verb();
}
int strcasecmp(string str1, string str2) {
  return strcmp(lower_case(str1), lower_case(str2));
}
#define COMPAT_TAIL
#ifdef COMPAT_TAIL
int tail(string fname) {
   int offset = file_size(fname);
   string str;
   if (offset < 0) {
      return 0;
   }
   offset -= 54 * 20;
   if (offset < 0) {
      offset = 0;
   }
   str = read_bytes(fname, offset, 1080);
   if (!str) {
      return 0;
   }
   if (offset) {
      str = str[strsrch(str, "\n")+1..];
   }
   write(str);
   return 1;
}
#else
varargs string tail(string fname, int nlines) {
  int chunk = nlines * 80;
  int offset = file_size(fname);
  int num_nl, p, skip;
  string str = "";
  reset_eval_cost();
  while (offset > 0 && num_nl <= nlines) {
    num_nl = 0;
    offset -= chunk;
    if (offset < 0) {
      chunk += offset;
      offset = 0;
    }
    str = read_bytes(fname, offset, chunk) + str;
    p = -1;
    while (p < sizeof(str)-1 && p = member_array('\n', str, p+1))
      num_nl++;
  }
  skip = num_nl - nlines;
  p = -1;
  while (skip--)
    p = member_array('\n', str, p+1);
  return str[p..];
}
#endif
void write(mixed str) {
  if (!this_player()) {
    return ;
  }
  if (intp(str)) {
    str = ""+str;
  }
  this_player()->do_efun_write(str);
}
int notify_fail( mixed stuff ) {
   if (!this_player())  {
      return 0;
   }
   if ( functionp( stuff ) ) {
      stuff = evaluate( stuff );
   }
   if ( !stringp( stuff ) ) {
      return 0;
   }
   this_player()->print_messages();
   stuff = (string)this_player()->convert_message( stuff );
   stuff = (string)this_player()->fit_message( stuff );
   stuff = (string)this_player()->fix_string( stuff );
#if efun_defined(notify_fail)
   return efun::notify_fail( stuff );
#else
   return _notify_fail( stuff );
#endif
}
varargs string replace(string str, mixed bing, string rep) {
  int i;
  if (pointerp(bing)) {
    for (i=0;i<sizeof(bing);i+=2) {
      if (stringp(bing[i]) && stringp(bing[i+1])) {
        str = replace_string(str, bing[i], bing[i+1]);
      }
    }
    return str;
  }
  if(!stringp(str) || !stringp(rep))
    return str;
  return replace_string(str, bing, rep);
}
string cap_words(string words)  {
  return implode(map(explode(words, " "), (: capitalize :)), " ");
}
mixed *uniq_array(mixed *arr){
  return keys(allocate_mapping(arr, 1));
}
varargs void shout( string words, object avoid ) {
   object thing, *things;
   things = efun::users();
   foreach( thing in things ) {
      if ( thing && ( thing != avoid ) && !thing->check_earmuffs( "shout" ) ) {
         if ( thing != this_player() ) {
            thing->event_say( previous_object(), words, ({ }) );
         }
      }
   }
}
nosave int eval_cost_time;
nosave int eval_cost_real_time;
nosave string reset_eval_message;
nosave object eval_ob;
void reset_eval_cost() {
  int i;
  string *funs, stack;
  object *obs;
  if(time() == eval_cost_time && previous_object() == eval_ob) {
    if(real_time() - eval_cost_real_time > 5) {
      stack = "";
      obs = call_stack(1);
      funs = call_stack(2);
      for(i=0; i<sizeof(obs); i++) {
        if(clonep(obs[i]))
          stack += base_name(obs[i]) + "#" + obs[i]->query_name();
        else
          stack += base_name(obs[i]);
        stack += "->" + funs[i] + "()\n";
      }
      reset_eval_message =
        sprintf("%s uses reset_eval_cost to last %d seconds\n%s",
                query_multiple_short(map(previous_object(-1),
                                         (: file_name($1) :))),
                real_time() - eval_cost_real_time,
                stack);
    }
  } else {
    if(reset_eval_message)
      log_file("GARBAGE", sprintf("%s %s\n", ctime(eval_cost_time),
                                  reset_eval_message));
    reset_eval_message = 0;
    eval_cost_time = time();
    eval_cost_real_time = real_time();
    eval_ob = previous_object();
  }
  efun::reset_eval_cost();
}
#if !efun_defined(event)
varargs int member_array(mixed item, mixed arr, int start, int flag){
  if(!arr || !arrayp(arr))
    return -1;
  if(!flag)
    return efun::member_array(item, arr, start);
  if(stringp(item)) {
    string *tmp;
    tmp = map(arr, (:$1[0..$(strlen(item)-1)]:));
    return efun::member_array(item, tmp, start);
  }
}
void event(mixed ob, string func, mixed rest ...){
  object origin = previous_object(), *bing;
  string name = "event_" + func;
  if(arrayp(ob)){
    ob = filter(ob, (:$1:));
    call_other(ob, name, origin, rest ...);
    return;
  } else if(!objectp(ob)) {
    return;
  }
  call_other(ob, name, origin, rest ...);
  bing = all_inventory(ob);
  bing -= ({origin});
  bing = filter(bing, (:$1:));
  call_other(bing, name, origin, rest ...);
}
#endif
#if !efun_defined(add_action)
void move_object(mixed ob){
  object tp, *obs, bing;
  if(stringp(ob)) {
    ob = find_object(ob);
  }
  evaluate(bind((: efun::move_object($(ob)):), previous_object()));
  if(ob->no_init()){
    return;
  }
  tp = this_player();
  if(living(previous_object())){
    efun::set_this_player(previous_object());
    ob->init();
    (all_inventory(ob) - ({previous_object()}))->init();
  }
  obs = filter(all_inventory(ob),
               (:living($1) && $1 != $(previous_object()):));
  foreach(bing in obs){
    efun::set_this_player(bing);
    previous_object()->init();
  }
  if(living(ob)){
    efun::set_this_player(ob);
    previous_object()->init();
  }
  efun::set_this_player(tp);
}
#endif
#if efun_defined(db_exec)
varargs mixed db_exec(int fd, string fmt, mixed *args ...) {
  mixed ret;
  int starttime = real_time();
  if (!sizeof(args)) {
    ret = evaluate(bind((:efun::db_exec, fd, fmt:), previous_object()));
  } else {
    ret = evaluate(bind((:efun::db_exec, fd, sprintf(fmt, args ...):), previous_object()));
  }
  if((real_time() - starttime) > 1)
    this_object()->log_file("GARBAGE", "db_exec in %O, time: %d\n",
                            previous_object(), real_time() - starttime);
  return ret;
}
#else
varargs int db_connect(mixed *args ...){
  error("No database installed");
}
varargs string db_exec(int fd, string fmt, mixed *args ...) {
  return "No database installed";
}
mixed *db_fetch(int fd, int row){
  error("No database installed");
}
void db_close(int fd){}
#endif
void shutdown(int bing){
  string thing = base_name(previous_object());
  if(thing != "/obj/shut" && thing != "/global/lord"){
    unguarded((:write_file, "/d/admin/log/SHUTDOWN.log",
               sprintf("value %d\n%s", bing, back_trace()):));
  }
  efun::shutdown(bing);
}
#if !efun_defined(real_time)
int real_time(){return time();}
#endif
#if efun_defined(memory_summary)
string memory_summary() {
   return "Not on this mud...\n";
}
#endif
#if efun_defined(debug_info)
string debug_info( int operation, object ob ) {
  string path;
  if ( operation != 2 )
    return efun::debug_info( operation, ob );
  path = base_name( ob );
  path += ".c";
  if ( !master()->valid_read( path,
                              this_player()->query_name(), "debug_info" ) ) {
    this_object()->unguarded((:write_file, "/d/admin/log/DEBUG_INFO.log",
                sprintf( "%s: %s tried to debug %s.\n", ctime( time() ),
                         this_player()->query_name(),
                         base_name( ob ) ) :));
    return "You are not authorised to do that.\n";
  }
  if ( interactive( ob ) && !this_player()->query_lord() &&
       ob != this_player()) {
    this_object()->unguarded((:write_file, "/d/admin/log/DEBUG_INFO.log",
                sprintf( "%s: %s tried to debug %s.\n", ctime( time() ),
                         this_player()->query_name(),
                         ob->query_name() ) :));
    return "Only Lords can dump an interactive object.\n";
  }
  return efun::debug_info( operation, ob );
}
#endif
void input_to(mixed fun, mixed flag, mixed args ...){
  function f = function(string input, object ob, mixed fun, mixed args){
    int t = real_time();
    if(functionp(fun))
      evaluate(fun, input, args...);
    else
      evaluate(bind((:call_other, ob, fun, input, args ...:), ob));
    if((real_time() - t) > 1) {
      if(fun == "logon2")
        input = "******";
      this_object()->log_file("GARBAGE", "input_to %O (%O) in %O, time: %d\n",
                              fun, input,
                              ob, real_time() - t);
    }
  };
  if(!args)
    args = ({});
  if(!intp(flag)){
    args = ({flag}) + args;
    flag = 0;
  }
  efun::input_to(f, flag, previous_object(), fun, args);
}
#if 0
private nosave function _wrap = function(mixed func, mixed *args) {
  int t = real_time();
  if(stringp(func)) {
    call_other(this_object(), func, args ...);
  } else if(functionp(func)) {
    evaluate(func, args ...);
  }
  if((real_time() - t) > 1) {
    "/secure/simul_efun"->log_file("GARBAGE", "object: %O function: %O time: %d\n", this_object(), func, real_time()-t);
  }
};
varargs int call_out(mixed fun, int delay, mixed *args ...) {
  string func;
  function wrap;
  wrap = bind(_wrap, previous_object());
  if (_callouttime != time()) {
    _callouttime = time();
    _calloutfunc = ([]);
  }
  if(delay == 0) {
    func = functionp(fun)?""+functionp(fun):fun +
      file_name(previous_object());
    if(_calloutfunc[func] == -1)
      delay = 2;
    else if(++_calloutfunc[func] > 100) {
      delay = 2;
      _calloutfunc[func] = -1;
      if ( stringp(previous_object()->query_name())) {
        log_file("CALL_OUT_LOG", ctime(time()) + ": " +
                 "Object %O (%s) seems to loop in function %O.\n",
                 previous_object(), previous_object()->query_name(), fun);
      } else {
        log_file("CALL_OUT_LOG", ctime(time()) + ": " +
                 "Object %O (%s) seems to loop in function %O.\n",
                 previous_object(), file_name(previous_object()), fun);
      }
    }
  }
  return evaluate(bind((: efun::call_out($(wrap), $(delay), $(fun), $(args)) :)
                       , previous_object()));
}
#endif