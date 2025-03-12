#include <soul.h>
#include <language.h>
#define SPECIAL_DAY "/obj/handlers/special_day"
class response_data {
   object last_ob;
   string last_mess;
   int stop_responding;
   int use_regexp;
   int last_count;
   int last_time;
   int understand_anything;
   object* only_respond_to;
}
mixed *_respond_to_with;
nosave class response_data _response_data;
int match(string str, mixed str2);
void event_soul(object per, string mess, object *avoid, string verb,
                string last, mixed at) ;
void create() {
  _respond_to_with = ({ });
  _response_data = new(class response_data);
  _response_data->only_respond_to = ({ });
}
void set_response_mon_understand_anything(int flag) {
   _response_data->understand_anything = flag;
}
void set_response_mon_regexp(int flag) { _response_data->use_regexp = flag; }
int query_response_mon_regexp() { return _response_data->use_regexp; }
int query_response_mon_debug_mode() {
  return this_object()->query_property("respon mon debug");
}
void set_response_mon_debug_mode(int flag) {
  this_object()->add_property("respon mon debug", flag);
}
void set_stop_responding(int i) { _response_data->stop_responding = i; }
int query_stop_responding() { return _response_data->stop_responding; }
int query_response_allowed(object ob,
                           string *response) {
  if (!this_object()->query_visible(ob)) {
    return 0;
  }
  return 1;
}
void set_respond_to_with( mixed map ) {
  mixed *old_keys;
  int i;
  if ( mapp( map ) ) {
#ifdef DEBUG
    log_file("BAD_RESPONSE", "set_respond_to_with() called by %O (%s)\n",
             previous_object(), previous_object()->query_name());
#endif
    old_keys = keys(map);
    _respond_to_with = allocate(sizeof(old_keys) * 2);
    for (i = sizeof(old_keys); i--; ) {
      _respond_to_with[2*i] = old_keys[i];
      _respond_to_with[2*i+1] = map[old_keys[i]];
    }
    return;
  }
  _respond_to_with = map;
}
mixed *query_respond_to_with() { return _respond_to_with; }
void add_respond_to_with( mixed *trigger, mixed response ) {
  _respond_to_with += ({ trigger, response });
}
void add_only_respond_to(object person) {
  _response_data->only_respond_to += ({ person });
}
void remove_only_respond_to(object person) {
   _response_data->only_respond_to -= ({ person });
}
object* query_only_respond_to() {
   return _response_data->only_respond_to;
}
protected mixed *check_sub_sequence( mixed *words ) {
  int word_index;
  int format_index;
  int format_size;
  int word_size;
  int match_counter;
  int cu_format_size;
  string word_str;
  mixed data;
  string *patterns;
  string pattern;
  string extra;
  format_index = 0;
  word_size = sizeof( words );
  word_str = implode(words, " ");
  format_size = sizeof( _respond_to_with );
  while (format_index < format_size) {
    if ( _response_data->use_regexp ) {
        data = _respond_to_with[ format_index ];
        if ( arrayp( data ) && sizeof( data ) > 1 ) {
            if ( arrayp( data[0] ) ) {
                extra = "(" + implode( data, "|" ) + ")+";
            }
            else {
                extra = data[0];
            }
            patterns = map( data[1], (: $(extra) + " " + $1 :) );
        }
        else {
            patterns = ({ data });
        }
        foreach( pattern in patterns ) {
            if ( regexp( word_str, pattern ) ) {
                return _respond_to_with[ format_index + 1 ];
            }
        }
    }
    else {
        word_index = 0;
        match_counter = 0;
        cu_format_size = sizeof(_respond_to_with[format_index]);
        while ((word_index < word_size) && (match_counter < cu_format_size)) {
          match_counter += match(words[word_index],
                                 _respond_to_with[format_index][match_counter]);
          word_index++;
        }
        if (match_counter == (cu_format_size)) {
          return _respond_to_with[format_index + 1];
        }
    }
    format_index += 2;
  }
  return 0;
}
protected int match(string str, mixed format) {
  if (pointerp(format)) {
    return (member_array(str, format) != -1);
  }
  if (str == format) {
    return 1;
  }
  return 0;
}
protected string remove_read_marks(string str) {
  int blij;
  string result;
  int size;
  string temp;
  size = strlen(str);
  blij = 0;
  result = "";
  while (blij < size) {
    temp = str[blij..blij];
    if (((temp >= "a") && (temp <= "z")) ||
        ((temp >= "0") && (temp <= "9")) ||
        (temp == " ")) {
      result += temp;
    } else {
      result += " ";
    }
    blij++;
  }
  return result;
}
protected void senddstr(string str, object per) {
  if ( environment( this_object() ) ) {
    if ( per ) {
      command(replace(str, ({ "$hname$", per->query_name(), "$hcname$",
                                per->query_short(),
                              "$hshort$", per->query_short() })));
    } else {
      command( str );
    }
  }
}
protected void exec_response(mixed rep, object per, string mess) {
  string *rabbit;
  if (pointerp(rep)) {
    return exec_response(rep[random(sizeof(rep))], per, mess);
  }
  if (functionp(rep)) {
    evaluate(rep, per, mess);
  } else if (stringp(rep)) {
    if (rep[0..0] == "#") {
      rabbit = explode(rep[1..], "#");
      if (sizeof(rabbit) > 1) {
        call_out((: call_other($1, $2, $3, $4) :), 0,
                 rabbit[0], rabbit[1], per, mess);
      } else {
        call_out(rabbit[0], 0, per, mess);
      }
    } else {
      call_out("senddstr", 0, rep, per);
    }
  }
}
private void do_delay_thingy(string *extra, string mess, object per) {
  mixed *response;
  mess = lower_case(mess);
  if (!_response_data->use_regexp) {
    mess = remove_read_marks(mess);
  }
  if (query_response_mon_debug_mode()) {
    tell_object(per, "Parsing the text: " + implode(extra, " ") + " " + mess + "\n");
  }
  response = check_sub_sequence(extra + explode(mess, " "));
  if (query_response_mon_debug_mode()) {
    tell_object(per, sprintf("Responding with %O\n", response));
  }
  if (response) {
    if (query_response_allowed(per, response)) {
      exec_response(response, per, mess);
    }
  }
}
int check_loop(object per, string mess) {
  if(interactive(per)) {
    return 0;
  }
  if (_response_data->last_ob == per &&
      (_response_data->last_mess = mess) &&
      _response_data->last_time > time() - 10)
  {
    if(_response_data->last_count > 1) {
      return 1;
    } else {
      _response_data->last_count++;
    }
    _response_data->last_time = time();
  } else {
    _response_data->last_ob = per;
    _response_data->last_mess = mess;
    _response_data->last_count = 1;
    _response_data->last_time = time();
  }
  return 0;
}
private void do_response(string *extra, string mess, object per) {
  if (sizeof(_response_data->only_respond_to)) {
     _response_data->only_respond_to -= ({ 0 });
     if (sizeof(_response_data->only_respond_to) &&
         member_array(per, _response_data->only_respond_to) == -1) {
        return ;
     }
  }
  call_out((: do_delay_thingy($1, $2, $3) :), 2, extra, mess, per);
}
void event_person_sayto(object per, string mess, string lang, object* targets) {
  string skill;
  if(_response_data->stop_responding ||
     !sizeof(_respond_to_with) ||
     environment() == find_object( "/room/rubbish" ) ||
     environment() == find_object( "/room/void" ) ||
     !per || per == this_object()) {
    return ;
  }
  if(check_loop(per, mess)) {
    return;
  }
  skill = LANGUAGES->query_language_spoken_skill(lang);
  if (this_object()->query_skill(skill) < 90 ||
      per->query_skill(skill) < 60) {
    return;
  }
  do_response(({ "@sayto" }), mess, per);
}
void event_person_say(object per, string start, string mess, string lang) {
  string skill;
  if(_response_data->stop_responding ||
     !sizeof(_respond_to_with) ||
     environment() == find_object( "/room/rubbish" ) ||
     environment() == find_object( "/room/void" ) ||
     !per || per == this_object()) {
    return ;
  }
  if(check_loop(per, mess))
    return;
  if (!_response_data->understand_anything) {
     skill = LANGUAGES->query_language_spoken_skill(lang);
     if (this_object()->query_skill(skill) < 90 ||
         per->query_skill(skill) < 60) {
       return;
     }
  }
  do_response(({ "@say" }), mess, per);
}
varargs void event_soul(object per, string mess, object *avoid, string verb,
                        string last, mixed at) {
  if (per == find_object(SOUL_OBJECT))
    per = previous_object(2);
  if(!interactive(per) ||
     _response_data->stop_responding ||
     environment() == find_object( "/room/rubbish" ) ||
     environment() == find_object( "/room/void" ) ||
      member_array(this_object(), avoid) != -1 ||
     !sizeof(_respond_to_with)) {
    return ;
  }
  if((!objectp(at) || (objectp(at) && at != this_object())) &&
     environment(per) != environment() ) {
    return;
  }
  mess = this_object()->convert_message( mess );
  if(check_loop(per, mess))
    return;
  if (objectp(at)) {
    do_response(({ "@" + verb, "#" + last, at->query_name() }), mess, per);
  } else {
    do_response(({ "@" + verb, "#" + last }), mess, per);
  }
}
varargs void event_whisper(object per, string mess, object *obs, string lang,
                           object me) {
  string skill;
  if (!interactive(per) || _response_data->stop_responding ||
      environment() == find_object( "/room/rubbish" ) ||
      !sizeof(_respond_to_with)) {
    return ;
  }
  if(check_loop(per, mess)) {
    return;
  }
  if (!_response_data->understand_anything) {
    skill = LANGUAGES->query_language_spoken_skill(lang);
    if (this_object()->query_skill(skill) < 90 ||
        per->query_skill(skill) < 60) {
      return;
    }
  }
  if (member_array(this_object(), obs) == -1) {
    do_response(({ "@whisper", map(obs, (: $1->query_name() :)) }),
                "", per);
  } else {
    mess = this_object()->convert_message( mess );
    do_response(({ "@whisper", map(obs, (: $1->query_name() :)) }),
                mess, per);
  }
}