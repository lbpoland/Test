#include <drinks.h>
#include <library.h>
#include <player.h>
#include <language.h>
#define TELL_CMD "/cmds/player/t_ell"
#define REMOTE_CMD "/cmds/player/rem_ote"
class language_info {
   string cur_lang;
   int mangle_accent;
   string default_lang;
}
private int *_sp = ({0, 0});
private class language_info cur_lang;
private mixed *tell_reply_list = ({ 0, 0 });
private nosave object converse_ob;
string drunk_speech(string str);
string expand_nickname(string str);
private int converse(string);
private int do_write(string);
private int do_repeat(string);
string query_current_language();
void communicate_commands() {
  add_command("converse", "", (: converse(0) :));
  add_command("converse", "<string'person'>", (: converse($4[0]) :));
  add_command("frimble", "<string>", (: do_write($4[0]) :));
  add_command("repeat", "<string'command'>", (: do_repeat($4[0]) :));
}
int query_real_max_sp() {
  int ret;
  ret = sqrt(this_object()->query_time_on() / -15);
  if(ret < 50)
    return 50;
  if(ret > 500)
    return 500;
  return ret;
}
int query_max_sp() { return _sp[1]; }
int adjust_max_sp( int number ) {
   _sp[1] += number;
   if ( _sp[1] < 0 )
      _sp[1] = 0;
   number = query_real_max_sp();
   if ( _sp[1] > number )
      _sp[1] = number;
   return _sp[1];
}
int set_max_sp( int number ) { return adjust_max_sp( number - _sp[1] ); }
int query_sp() { return _sp[0]; }
int adjust_sp( int number ) {
  if (_sp[0] + number < 0)
    return -1;
  if (number < 0)
    adjust_max_sp(1);
  _sp[0] += number;
  if ( _sp[0] > _sp[1] )
    _sp[0] = _sp[1];
  return _sp[0];
}
int set_sp( int number ) {
   return adjust_sp( number - _sp[0] );
}
void comm_event( mixed thing, string type, string start, string rest,
      string lang, string accent ) {
   if ( !objectp( thing ) && !pointerp( thing ) ) {
      return;
   }
   event( thing, type, start, rest, lang, accent );
   call_other(all_inventory(), "event_" + type, this_object(),
              start, rest, lang, accent);
}
void comm_event_to(object ob, string event_type, string start, string type,
                   string words, object *others, string lang, object me,
                   string accent) {
  event(ob, event_type, start, type, words, others, lang, me, accent);
}
void do_whisper(object ob, string event_type, string start, string type,
                string words, object *others, string lang, object me,
                string accent) {
  event(ob, event_type, start, type, words, others, lang, me, accent);
}
private int do_write(string arg) {
  if (!arg || arg == "") {
    notify_fail("Syntax: "+query_verb()+" <string>\n");
    return 0;
  }
  write(sprintf("$I$0=%s\n", arg));
  this_player()->adjust_time_left(-DEFAULT_TIME);
  return 1;
}
private int converse(string str) {
  if (!LANGUAGE_HAND->query_language_spoken(query_current_language())) {
    notify_fail(capitalize(query_current_language())+" is not a spoken language.\n");
    return 0;
  }
  if (str) {
    if (!LANGUAGE_HAND->query_language_distance(query_current_language())) {
      notify_fail(capitalize(query_current_language())+" is not able to spoken at a "+
                  "distance.\n");
      return 0;
    }
    str = lower_case(str);
    str = (string)this_object()->expand_nickname(str);
    converse_ob = find_player(str);
    if (!converse_ob)
      converse_ob = find_living(str);
    if (!converse_ob) {
      notify_fail("Syntax: converse [player]\n");
      return 0;
    }
    if (converse_ob == this_object()) {
      notify_fail("You have a nice conversation with yourself. Gee, what fun.\n");
      return 0;
    }
  }
  write("Give '**' to stop.\n");
  write("] ");
  input_to("do_converse");
  return 1;
}
void do_converse(string str) {
  if(str == "**") {
    write("Ok.\n");
    converse_ob = 0;
    return;
  }
  if(str)
    if (!converse_ob)
      "/cmds/living/sa_y"->cmd( str );
    else
      if ( function_exists( "trap_tell", environment() ) )
        environment()->trap_tell( str, converse_ob, 1 );
      else
        TELL_CMD->cmd( str, converse_ob, 1 );
  write("] ");
  input_to("do_converse");
}
void add_language(string lang) {
  int lvl;
  string skill;
  if (!LANGUAGE_HAND->test_language(lang))
    return ;
  if (LANGUAGE_HAND->query_language_spoken(lang)) {
    skill = LANGUAGE_HAND->query_language_spoken_skill(lang);
    lvl = this_object()->query_skill(skill);
    this_object()->add_skill_level(skill, 100 - lvl);
  }
  if (LANGUAGE_HAND->query_language_written(lang) ||
      LANGUAGE_HAND->query_language_magic(lang)) {
    skill = LANGUAGE_HAND->query_language_written_skill(lang);
    lvl = this_object()->query_skill(skill);
    this_object()->add_skill_level(skill, 100 - lvl);
  }
}
private void fixup_lang_class() {
   mixed tmp;
   if (!classp(cur_lang)) {
      tmp = cur_lang;
      if (!tmp) {
         tmp = "common";
      }
      cur_lang = new(class language_info);
      cur_lang->cur_lang = tmp;
      cur_lang->default_lang = "common";
      cur_lang->mangle_accent = 1;
   }
}
int set_language(string str) {
  if (!LANGUAGE_HAND->test_language(str))
    return 0;
  fixup_lang_class();
  cur_lang->cur_lang = str;
  return 1;
}
string query_current_language() {
  fixup_lang_class();
  return cur_lang->cur_lang;
}
void set_default_language(string def) {
  fixup_lang_class();
  cur_lang->default_lang = def;
}
string query_default_language() {
  fixup_lang_class();
  return cur_lang->default_lang;
}
void set_mangle_accent(int flag) {
   fixup_lang_class();
   cur_lang->mangle_accent = flag;
}
int query_mangle_accent() {
   fixup_lang_class();
   return cur_lang->mangle_accent;
}
private int do_repeat(string str) {
  if (!str) {
    notify_fail("Syntax: repeat <cmd>\n");
    return 0;
  }
  input_to("do_wombat_repeat", 0, str);
  write("Enter the commands you wish to pass to "+str+".  '**' on a line "+
        "by itself to exit.\n");
  write("] ");
  return 1;
}
protected int do_wombat_repeat(string str, string com) {
  if (str == "**") {
    return 0;
  }
  write("Doing '"+com+" "+str+"\n");
  command(com+" "+str);
  write("] ");
  input_to("do_wombat_repeat", 0, com);
  return 0;
}
object *query_ignoring(object *people)  {
   string *ignore;
   object *fail = ({ });
   ignore = this_object()->query_property( "ignoring" );
   if ( ignore )  {
      fail = filter_array( people,
                (: member_array( $1 && $1->query_name(), $(ignore) ) > -1 :) );
   }
   return fail;
}
object *query_ignored_by(object *people) {
   return filter(people, (: sizeof($1->query_ignoring( ({ this_player() }) )) :));
}
int set_tell_reply_list(mixed list) {
  if (base_name(previous_object())[0 .. strlen(TELL_CMD) - 1] != TELL_CMD &&
      base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
     !previous_object()->query_lord())
    return 0;
  tell_reply_list = ({time() + (60 * 15), list });
  return 1;
}
mixed query_tell_reply_list() {
  if(base_name(previous_object())[0..strlen(TELL_CMD) - 1] != TELL_CMD &&
     base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
     !previous_object()->query_lord())
    return 0;
  if(tell_reply_list[0] < time())
    return 0;
  return tell_reply_list[1];
}