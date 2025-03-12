#include <living.h>
#include <player.h>
#include <soul.h>
inherit "/global/alias";
inherit "/global/nickname";
nosave int time_left;
nosave int tl_updated;
nosave int doing_it;
nosave int last_command;
nosave int bypass_queue;
nosave int flush_call_id;
nosave string *queued_commands;
nosave string in_command;
nosave mixed interrupt;
nosave private function cmd = 0;
#if !efun_defined(add_action)
protected mixed _process_input(string);
protected mixed command(string);
#endif
void create() {
  time_left = ROUND_TIME;
  tl_updated = time();
  last_command = time();
  queued_commands = ({ });
}
void bypass_queue() { bypass_queue = 1; }
void no_time_left() {
  time_left = -ROUND_TIME;
}
protected int drunk_check(string str);
void soul_commands() {
#if efun_defined(add_action)
  add_action("lower_check","*", -10000);
  add_action((:drunk_check:),"*", 10000);
#endif
  alias_commands();
  nickname_commands();
  history_commands();
}
int query_queued_commands() {
  return sizeof(queued_commands);
}
int soul_com_force(string str) {
  if (file_name(previous_object()) != SOUL_OBJECT)
    return 0;
  command(str);
  return 1;
}
void do_soul(string str, mixed bing) {
  say(str, bing);
}
int query_time_left() {
  time_left += ((time() - tl_updated) / 2) * ROUND_TIME;
  if(time_left > ROUND_TIME)
    time_left = ROUND_TIME;
  tl_updated = time();
  return time_left;
}
int adjust_time_left(int i) {
   return time_left += i;
}
private void do_flush(int first) {
  int i;
  string str;
  if ( ( time_left < 0 ) || !sizeof( queued_commands ) ||
       ( this_object()->queue_commands(queued_commands[0]) &&
         !this_object()->query_creator() ) ) {
    return;
  }
  if (!first) {
    str = queued_commands[0];
    queued_commands = queued_commands[1..];
    doing_it = 1;
    catch(command(str));
    doing_it = 0;
    if (!sizeof(queued_commands)) {
      queued_commands = ({ });
      doing_alias = ([ ]);
    }
    return ;
  }
  for (i = 0; (i < 2) && (i < sizeof(queued_commands)); i++) {
    flush_call_id = call_out((: do_flush(0) :), 1);
  }
  flush_call_id = call_out((: do_flush(1) :), 2);
}
private void call_interrupt(int time_left, object interupter) {
   mixed stuff;
   stuff = interrupt;
   interrupt = 0;
   if (pointerp(stuff)) {
      catch(call_other(stuff[1],
                       stuff[0],
                       time_left,
                       stuff[2],
                       this_object(),
                       interupter,
                       in_command));
   } else if (functionp(stuff)) {
      catch(evaluate(stuff,
                     time_left,
                     this_object(),
                     interupter,
                     in_command));
   }
}
protected void flush_queue() {
  query_time_left();
  remove_call_out(flush_call_id);
  do_flush(1);
  if (!sizeof(queued_commands)) {
    if (interrupt && time_left > 0) {
      call_interrupt(0, this_object());
    }
    in_alias_command = 0;
    doing_alias = ([ ]);
    if (!sizeof(queued_commands)) {
      return ;
    }
    doing_alias = ([ ]);
    in_alias_command = 0;
  }
}
void set_interupt_command(mixed func, mixed ob, mixed arg) {
  if (!functionp(func)) {
    interrupt = ({ func, ob, arg });
    if ( !stringp( func ) )
      interrupt = 0;
  } else {
    interrupt = func;
  }
}
mixed *query_interupt_command() {
   return interrupt;
}
void set_interrupt_command(function func) {
  set_interupt_command(func, 0, 0);
}
void remove_queue() {
   queued_commands = ({ });
   if ( interrupt && ( time_left < 0 ) ) {
      call_interrupt(-time_left, this_object());
   }
   tell_object( this_object(), "Removed queue.\n" );
   if (this_object()->query_lord()) {
     time_left = 0;
   } else {
     time_left = -DEFAULT_TIME;
   }
}
void interupt_command(object interupter) {
   if (interupter) {
      call_interrupt(-time_left, interupter);
   }
}
void command_override(function func){
  if(!functionp(func))
    error("command_override needs a function!");
  cmd = func;
}
protected int drunk_check(string str) {
   string *rabbit;
   string *green;
   string mess;
   string comm;
   string arg;
   if(cmd){
     object owner = function_owner(cmd);
     if(owner && owner == environment(this_player())){
       int res = evaluate(cmd, str);
       if(res)
         return res;
     } else cmd = 0;
   }
   if ( in_command == str ) {
      in_command = 0;
      sscanf(str, "%s %*s", str);
      if (is_doing_alias(str)) {
         this_object()->add_failed_mess(this_object(),
             "Recursive aliases. Bad "+
             ({"thing","boy","girl"})[(int)this_object()->query_gender()]+
                ".\n", ({ }));
      }
      return 0;
   }
   if ( bypass_queue ) {
      bypass_queue = 0;
      return 0;
   }
   last_command = time();
   if ( this_object()->query_property( PASSED_OUT ) ||
         !interactive( this_object() ) ) {
      if ( ( str == "quit" ) || ( str == "quit_old" ) ) {
         return 0;
      }
      mess = this_object()->query_passed_out_message();
      if ( !stringp( mess ) ) {
         mess = "You are unconscious.  You can't do anything.\n";
      }
      write( mess );
      if ( !this_object()->query_creator() ) {
         return 1;
      }
      write( "On the other hand, you're a creator...\n" );
   }
   if ( ( str == "stop" ) || ( str == "restart" ) ) {
      remove_queue();
      return 0;
   }
   if ( stringp( str ) ) {
      if ( str[ 0 .. 4 ] == "stop " ) {
         return 0;
      }
   }
   if ( ( time_left < 0 ) ||
        (this_object()->queue_commands(str) &&
         !this_object()->query_creator()) ||
         ( !doing_it && ( sizeof( queued_commands ) ||
         ( find_call_out( flush_call_id ) != -1 ) ) ) ) {
      rabbit = explode(str, " ");
      if (rabbit[0] != upper_case(rabbit[0])) {
         write( "Queued command: "+ str +"\n" );
      }
      if ( str == "quit" ) {
         write( "If you are trying to quit and it is queueing things, use "
               "\"stop\" to stop your commands, and or \"restart\" to start "
               "your heartbeat.\n" );
      }
      if(sizeof(queued_commands) < 256) {
        if(sizeof(rabbit) > 1 && member_array(str, queued_commands) != -1)
          time_left -= (DEFAULT_TIME / 2);
        queued_commands += ({ str });
      }
      return 1;
   }
   if (interrupt) {
      call_interrupt(0, this_object());
   }
   interrupt = 0;
   in_command = str;
   if (sscanf(str, "%s %s", comm, arg) != 2) {
      comm = str;
      arg = "";
   }
   rabbit = run_alias(comm, arg);
   if (rabbit) {
      set_doing_alias(comm);
      green = queued_commands;
      queued_commands = ({ });
      foreach (comm in rabbit) {
         catch(command(comm));
      }
      queued_commands += green;
#if USE_ADD_ACTION
   } else if(sizeof(str) > 512) {
     write("Command too long.\n");
#endif
   } else {
      time_left -= DEFAULT_TIME;
      command(str);
   }
   if (interrupt && time_left >= 0) {
      call_interrupt(0, this_object());
   }
   return 1;
}
protected string process_input(string str) {
  float secs;
  int t = time_expression{
    reset_eval_cost();
    if (str[0] == '.')
      str = expand_history(str[1..]);
    else if (str[0] == '^')
      str = substitute_history(str[1..]);
    this_object()->add_history(str);
#if efun_defined(add_action)
    return str;
#else
    _process_input(str);
  };
  secs = t/1000000.0;
  if((secs > 1.0) &&
     (strlen(str) < 2 || str[0..1] != "su") &&
     str != "upgrade") {
    log_file("GARBAGE", "%s command: %s time: %:3f place: %s\n",
       ctime(time())[4..18], str, secs,
       file_name(environment()));
    if(this_object()->query_creator())
      printf("\nThat command froze the mud for %:3f "
       "seconds.\n\n", secs);
  }
  return 0;
#endif
}
#if !efun_defined(add_action)
protected mixed _process_input(string str){
  object ob;
  int i;
  string* bits;
  if(str == "") {
    return 0;
  }
  ob = this_player();
  efun::set_this_player(this_object());
  _notify_fail(0);
  while (str[0] == ' ') {
    str = str[1..];
  }
  if (str == ""){
      efun::set_this_player(ob);
      return 0;
    }
  while(str[<1] == ' ') {
    str = str[0..<2];
  }
  if (str == ""){
    efun::set_this_player(ob);
    return 0;
  }
  if (strsrch(str, "%^") != -1) {
    bits = explode("f" + str + "g", "%^");
    for (i = 1; i < sizeof(bits); i += 2) {
      if (bits[i][0..3] != "USER") {
         bits[i] = "USER_" + bits[i];
      }
    }
    bits[0] = bits[0][1..];
    bits[<1] = bits[<1][0..<2];
    str = implode(bits, "%^");
  }
  if(!drunk_check(str)) {
    if(!this_object()->exit_command(str)) {
      if(!this_object()->cmdAll(str)) {
        if(!this_object()->new_parser(str)) {
          if(!this_object()->lower_check(str)){
            if(!(str = query_notify_fail())){
              string *responses=({"What?", "Try something else."});
              receive(responses[random(sizeof(responses))]+"\n");
            } else {
              receive(str);
            }
            efun::set_this_player(ob);
            return 0;
          }
        }
      }
    }
  }
  efun::set_this_player(ob);
  return "bing";
}
protected mixed command(string cmd){
  int time = eval_cost();
  if(_process_input(cmd))
    return eval_cost() - time + 1;
  return 0;
}
#endif
int lower_check(string str) {
  query_time_left();
  return (str == "stop");
}