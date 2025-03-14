#include <soul.h>
#include <creator.h>
#include <user_parser.h>
#include <command.h>
#include <obj_parser.h>
#include <function.h>
inherit "/global/command";
#define NEW_SOUL
#define MY_MESS_HEADER "#!"
#define OTHER_MESS_HEADER "!#"
class fail_mess_data {
    object* direct;
    object* indirect;
    int weight;
}
private nosave mapping _succ_mess;
private nosave mapping _fail_mess;
private nosave mapping _cur_objects;
private nosave object *_succ_indir;
private nosave object *_succ_mess_dir;
private nosave object *_succ_mess_indir;
private nosave mapping _commands;
private nosave string *_failed_mess;
private nosave string _curpat;
int *pattern_match(string *bits, mixed *pattern);
private int handle_command(string *bits, int *matches, mixed *pattern,
                            mixed *command, string pattern_str);
string get_fail_messages(string verb, object *fail_obs);
void print_special_messages(string verb);
string *query_word_list(string bing);
private void remove_object2(object ob, int flag);
private void remove_object_force(object ob);
varargs string create_message(string *bits, int *matches, mixed *pattern,
                                             object *dir_obs, int flag);
int syntax_messages(string str);
string query_name();
void create() {
   _commands = ([ ]);
   _fail_mess = ([ ]);
   _succ_mess = ([ ]);
   _cur_objects = ([ ]);
   _succ_indir = _succ_mess_dir = _succ_mess_indir = ({ });
   command::create();
}
mapping query_p_commands() { return copy( _commands ); }
mapping query_p_objects() { return copy( _cur_objects ); }
mixed *query_parse_command(string name) { return _commands[name]; }
object* query_parse_command_objects(string name) {
   class command_class command;
   class command_data command_data;
   string pattern;
   object* obs;
   command = _commands[name];
   obs = ({ });
   if (command) {
      foreach (pattern, command_data in command->patterns) {
         obs += filter(command_data->calls, (: objectp($1) :));
      }
   }
   return obs;
}
object* query_succ_mess_indir() {
    return _succ_mess_indir;
}
void parser_commands() {
#if efun_defined(add_action)
   add_action("new_parser", "*", -2);
#endif
   add_command("syntax", "<word'verb'>", (:syntax_messages($4[0]):));
}
int add_succeeded(mixed ob) {
   int i;
   if (!pointerp(_succ_indir)) _succ_indir = ({ });
   if (objectp(ob)) {
      if (member_array(ob, _succ_indir) == -1) {
         _succ_indir += ({ ob });
      } else {
         return 1;
      }
   } else if (!pointerp(ob)) {
      return 0;
   } else for (i=0;i<sizeof(ob);i++) {
      if (member_array(ob[i], _succ_indir) == -1) {
         _succ_indir += ({ ob[i] });
      }
   }
   return 1;
}
int add_succeeded_mess(object dir, mixed incoming_mess, object *in_dir) {
   string my_mess, other_mess;
   if (!pointerp(incoming_mess)) {
      if (stringp(incoming_mess)) {
         my_mess = MY_MESS_HEADER+incoming_mess;
         other_mess = OTHER_MESS_HEADER+incoming_mess;
      } else {
         write("Parameter to add_succeeded_mess() must be a string or "
                  "array.\n");
         return 0;
      }
   } else if (sizeof(incoming_mess) == 2) {
      my_mess = MY_MESS_HEADER+incoming_mess[0];
      other_mess = OTHER_MESS_HEADER+incoming_mess[1];
   } else {
      write("Message array to add_succeeded_mess() must be two long.\n");
      return 0;
   }
   if ( undefinedp( in_dir ) ) {
       in_dir = ({ });
   }
   if (!_succ_mess[my_mess]) {
      _succ_mess[my_mess] = ({ ({ dir }), in_dir });
   } else {
      if (member_array(dir, _succ_mess[my_mess][0]) == -1) {
         _succ_mess[my_mess][0] += ({ dir });
      }
      in_dir = in_dir - _succ_mess[my_mess][1];
      _succ_mess[my_mess][1] += in_dir;
   }
   if (!_succ_mess[other_mess]) {
      _succ_mess[other_mess] = ({ ({ dir }), in_dir });
   } else {
      if (member_array(dir, _succ_mess[other_mess][0]) == -1) {
         _succ_mess[other_mess][0] += ({ dir });
      }
      in_dir = in_dir - _succ_mess[other_mess][1];
      _succ_mess[other_mess][1] += in_dir;
   }
   if (member_array(dir, _succ_mess_dir) == -1) {
      _succ_mess_dir += ({ dir });
   }
   return 1;
}
void add_failed_mess( object dir, string mess, mixed *in_dir ) {
   int i;
   class fail_mess_data fail;
   if (!stringp(mess)) {
      write("Parameter to add_failed_mess() must be a string.\n");
      return;
   }
   if ( undefinedp( in_dir ) ) {
      in_dir = ({ });
   }
   if (!_fail_mess[mess]) {
      fail = new(class fail_mess_data);
      fail->direct = ({ dir });
      fail->indirect = in_dir;
      _fail_mess[mess] = fail;
   } else {
      if (member_array(dir, _fail_mess[mess]->direct) == -1) {
         _fail_mess[mess]->direct += ({ dir });
      }
      for (i=0;i<sizeof(in_dir);i++) {
         if (member_array(in_dir[i], _fail_mess[mess]->indirect) == -1) {
            _fail_mess[mess]->indirect += in_dir[i..i];
         }
      }
   }
   if (member_array(dir, _succ_mess_indir) == -1) {
      _succ_mess_indir += ({ dir });
   }
}
object *query_succ_mess_dir() {
    return _succ_mess_dir;
}
int query_failed_message_exists(object dir) {
    string mess;
    class fail_mess_data stuff;
    foreach (mess, stuff in _fail_mess) {
         if (member_array(dir, stuff->direct) != -1) {
             return 1;
         }
    }
    return 0;
}
varargs int add_command(string cmd, object ob, mixed format, function funct) {
   int i;
   int idx;
   class command_class command;
   class command_data command_data;
   if ((funct && !functionp(funct)) || !objectp(ob)) {
      return 0;
   }
   if (!format) {
      format = "<direct:object>";
   } else if (pointerp(format)) {
      for (i = 0; i < sizeof(format); i++) {
         add_command(cmd, ob, format[i], funct);
      }
      return 1;
   } else if (!stringp(format)) {
      return 0;
   }
   command = _commands[cmd];
   if (!command) {
      command = new(class command_class);
      command->patterns = ([ ]);
      command->order = 0;
      _commands[cmd] = command;
   }
   command_data = command->patterns[format];
   if (command_data) {
      idx = member_array(ob, command_data->calls);
      if (idx != -1) {
         command_data->calls[idx + 1] = funct;
      } else {
         command_data->calls += ({ ob, funct });
      }
   } else {
      command_data = new(class command_data);
      command_data->calls = ({ ob, funct });
      command->order = 0;
      command->patterns[format] = command_data;
   }
   if (_cur_objects[ob]) {
      _cur_objects[ob] |= ({ cmd });
   } else {
      _cur_objects[ob] = ({ cmd });
   }
   return 1;
}
int remove_object(mixed ob, int was_env) {
   if (objectp(ob) && !_cur_objects[ob] && !was_env) {
      return 0;
   }
   remove_object2(ob, was_env);
   return 1;
}
private void remove_object2(object ob, int was_env) {
   object womble;
   object *inv_match;
   if (!ob ||
       (!was_env && (environment() == ob ||
                     environment(ob) == this_object() ||
                     environment(ob) == environment()))) {
      return ;
   }
   if (was_env == 1) {
      remove_object_force(ob);
      inv_match = ob->find_inv_match();
      if ( arrayp( inv_match ) ) {
        foreach (womble in inv_match) {
           if (objectp(womble) && womble != this_object() &&
               _cur_objects[womble]) {
              remove_object_force(womble);
           }
        }
      }
      return ;
   }
   return ;
}
private void remove_from_command(string cmd, object ob) {
   int k;
   string format;
   class command_data command_data;
   if (!_commands[cmd]) {
      return ;
   }
   foreach (format, command_data in _commands[cmd]->patterns) {
      for (k = 0; k < sizeof(command_data->calls); k += 2) {
         if (!command_data->calls[k] || command_data->calls[k] == ob) {
            command_data->calls = command_data->calls[0..k - 1] + command_data->calls[k + 2..];
         }
      }
      if (!sizeof(command_data->calls)) {
         map_delete(_commands[cmd]->patterns, format);
         if (_commands[cmd]->order) {
            _commands[cmd]->order -= ({ format });
         }
      }
   }
   if (!sizeof(_commands[cmd]->patterns)) {
      map_delete(_commands, cmd);
   }
}
private void remove_object_force(object ob) {
   string ind;
   if (!_cur_objects[ob]) {
      return 0;
   }
   foreach (ind in _cur_objects[ob]) {
      remove_from_command(ind, ob);
   }
   map_delete(_cur_objects, ob);
}
void event_dest_me(object ob) {
   remove_object_force(ob);
}
void event_exit(object ob, string mess, object dest) {
   if (dest == this_object() || dest == environment()) {
      return ;
   }
   remove_object_force(ob);
}
void me_moveing(object from) {
   if (from) {
      remove_object(from, 1);
   }
}
nomask int new_parser(string str) {
   string *bits;
   string pattern_str;
   string format;
   mixed *wombat;
   mixed *soul_stuff;
   mixed *pattern;
   mixed *command_stuff;
   mixed *stuff;
   int i;
   int j;
   int ret;
   int flag;
   class command_class command;
   class command_data command_data;
   bits = explode(str, " ") - ({ "", 0 });
   command_stuff = cmdPatterns(bits[0]);
   if (this_object()->command_shadowed(bits[0], implode(bits[1..], " "))) {
      return 1;
   }
   command = _commands[bits[0]];
#ifdef NEW_SOUL
   if (!command && !sizeof(command_stuff)) {
      soul_stuff = SOUL_OBJECT->query_soul_command(bits[0]);
      if (!soul_stuff) {
         return 0;
      }
   }
#else
   if (!_commands[bits[0]] && !sizeof(command_stuff)) {
      return 0;
   }
#endif
   _failed_mess = ({ "", "" });
    current_verb = bits[ 0 ];
   if (!soul_stuff) {
      if (command) {
         if (!command->order) {
            foreach (pattern_str, command_data in command->patterns) {
               if (!command_data->weight) {
                  pattern =  PATTERN_OB->query_pattern(pattern_str);
                  if (pattern) {
                     command_data->weight = pattern[0];
                  } else {
                     map_delete(command->patterns, pattern_str);
                  }
               }
            }
            command->order = sort_array(keys(command->patterns),
                                   (: ((class command_data)$3[$2])->weight -
                                      ((class command_data)$3[$1])->weight :),
                                   command->patterns);
         }
         format = command->order[0];
         command_data = command->patterns[format];
      } else {
         command = new(class command_class);
         command->order = ({ });
         command->patterns = ([ ]);
      }
      for (i = 0, j = 0; i < sizeof(command->order) ||
                         j < sizeof(command_stuff); ) {
         if (i < sizeof(command->order)) {
            format = command->order[i];
            command_data = command->patterns[format];
         } else {
            command_data = 0;
         }
         if (j < sizeof(command_stuff) &&
             (!command_data ||
              command_data->weight < command_stuff[j][PATTERN_WEIGHT])) {
            pattern_str = command_stuff[j][PATTERN_STRING];
            stuff = command_stuff[j++][OBJS..];
            flag = 1;
         } else {
            pattern_str = format;
            flag = 0;
            stuff = command_data->calls;
            i++;
         }
         pattern = PATTERN_OB->query_pattern(pattern_str);
         if (!pattern) {
            continue;
         }
         wombat = pattern_match(bits, pattern);
         if (wombat && (ret = handle_command(bits, wombat, pattern, stuff,
                                             pattern_str))) {
            if (ret == -1) {
               if (flag) {
                  j = 100;
               } else {
                  i = 100;
               }
            } else {
               return 1;
            }
         }
         if (wombat && !sizeof(wombat)) {
            int cont;
            string pat;
            mixed *junk;
            if (_curpat[<2] == '}' || _curpat[<2] == ']') {
               if (_curpat[<2] == '}') {
                  _curpat = _curpat[0..strsrch(_curpat, '{', -1)-2];
               } else {
                  _curpat = _curpat[0..strsrch(_curpat, '[', -1)-2];
               }
            } else {
               _curpat = implode((explode(_curpat, " ") - ({0,""}))[0..<2], " ");
            }
            if (flag) {
               foreach (junk in command_stuff[j..]) {
                  pat = junk[PATTERN_STRING];
                  pat = replace(pat, ({":object", "", ":living", "",
                                                 ":any-living", "", ":distant-living", "",
                                                 ":here", "", ":me>", ">", ":here-me", "",
                                                 ":me-here", "" }));
                  if (_curpat == pat) {
                     cont = 1;
                     break;
                  }
               }
               if (!cont) {
                  j = 100;
               }
            } else {
               foreach (pat in command->order[i..]) {
                  pat = junk[PATTERN_STRING];
                  pat = replace(pat, ({":object", "", ":living", "",
                                                 ":any-living", "", ":distant-living", "",
                                                 ":here", "", ":me>", ">", ":here-me", "",
                                                 ":me-here", "" }));
                  if (_curpat == pat) {
                     cont = 1;
                     break;
                  }
               }
               if (!cont) {
                  i = 100;
               }
            }
         }
      }
   }
#ifdef NEW_SOUL
   if ( !ret ) {
      if (!soul_stuff) {
         soul_stuff = SOUL_OBJECT->query_soul_command(bits[0]);
      }
      for (i=0;i<sizeof(soul_stuff);i++) {
         pattern = PATTERN_OB->query_pattern(soul_stuff[i][PATTERN_STRING]);
         wombat = pattern_match(bits, pattern);
         if (wombat && handle_command(bits, wombat, pattern, soul_stuff[i][OBJS..],
                                      soul_stuff[i][PATTERN_STRING])) {
            return 1;
         }
      }
   }
#endif
   if (_failed_mess[1] == "") {
      if (!query_notify_fail()) {
         if (_failed_mess[0] == "") {
            notify_fail( "See \"syntax "+ bits[ 0 ] +
                  "\" for the input patterns.\n");
         } else {
            notify_fail( _failed_mess[0] );
         }
      }
   } else {
      notify_fail(_failed_mess[1]);
   }
   _fail_mess = ([ ]);
   return 0;
}
int syntax_messages(string str) {
   string the_mess;
   int i;
   string tmp;
   class command_data fluff;
   mixed *soul_stuff;
   mixed *command_stuff;
   if (!str) {
      notify_fail("Syntax: syntax <verb>\n");
      return 0;
   }
   command_stuff = cmdPatterns(str);
#ifdef NEW_SOUL
   soul_stuff = SOUL_OBJECT->query_soul_command(str);
   if (!_commands[str] && !soul_stuff && !sizeof(command_stuff)) {
      notify_fail("Could not find the verb '"+str+"'.\n");
      return 0;
   }
#else
   if (!_commands[str] && !sizeof(command_stuff)) {
      notify_fail("Could not find the verb '"+str+"'.\n");
      return 0;
   }
#endif
   the_mess = "Forms of syntax available for the command \""+ str +"\":\n";
   if (_commands[str]) {
      foreach (tmp, fluff in _commands[str]->patterns) {
         the_mess += str+" "+PATTERN_OB->query_short_pattern(tmp) + "\n";
      }
   }
   for (i=0;i<sizeof(command_stuff);i++) {
       the_mess += str+" "+PATTERN_OB->query_short_pattern(
                                        command_stuff[i][PATTERN_STRING]) + "\n";
   }
   for (i=0;i<sizeof(soul_stuff);i++) {
       the_mess += str+" "+PATTERN_OB->query_short_pattern(
                                        soul_stuff[i][PATTERN_STRING]) + "\n";
   }
   write(the_mess);
   return 1;
}
int *pattern_match(string *bits, mixed *pattern) {
   string *elms;
   int pos, *delayed, last, failed, j, opt, i, word_offset, spaces, wcount,
      *matches;
   mixed tmp;
   pos = wcount = 1;
   _curpat = "";
   matches = ({ 0 });
   delayed = ({ });
   for (i = 1; i < sizeof(pattern) && !failed; i++) {
      if (pos >= sizeof(bits))
         failed = 1;
      _curpat += PATTERN[pattern[i]];
      switch (pattern[i]) {
         case DIRECT_OBJECT :
         case INDIRECT_OBJECT :
            i++;
            if (pattern[i] == TARGET_PLAYER) {
               if (last) {
                  delayed += ({ SINGLE_WORD });
                  word_offset++;
                  pos++;
               } else {
                  pos++;
                  matches += ({ pos - 1 });
               }
               failed |= pos > sizeof(bits);
            } else {
               if (last) {
                  delayed += ({ SINGLE_WORD });
               } else {
                  delayed = ({ STRING });
                  last = FIND_FIRST;
               }
               word_offset++;
               pos++;
            }
            i++;
            break;
         case STRING :
            if (last) {
               pos -= word_offset-1;
               for (j=0;j<sizeof(delayed);j++) {
                  switch (delayed[j]) {
                     case STRING :
                        matches += ({ pos - 1 });
                        pos++;
                        break;
                     case OPTIONAL :
                        matches += ({ matches[<1] });
                        break;
                     case SINGLE_WORD :
                        matches += ({ pos - 1 });
                        pos++;
                        break;
                  }
               }
            }
            delayed = ({ STRING });
            word_offset = 1;
            pos++;
            last = FIND_LAST;
            break;
         case QUOTED_STRING :
            if (last) {
                while (pos < sizeof(bits) &&
                           bits[pos][0] != '"' &&
                           bits[pos][0] != '\'' &&
                           bits[pos][0] != '`') {
                     pos++;
                }
                if (pos < sizeof(bits)) {
                     pos -= word_offset;
                     for (j = 0; j < sizeof(delayed); j++) {
                         switch (delayed[j]) {
                              case STRING :
                                  matches += ({ pos });
                                  pos++;
                                  break;
                              case OPTIONAL :
                                  matches += ({ matches[<1] });
                                  break;
                              case SINGLE_WORD :
                                  matches += ({ pos });
                                  pos++;
                                  break;
                         }
                     }
                     last = FIND_NONE;
                } else {
                     failed = 1;
                }
            }
            if (pos > sizeof(bits)) {
                failed = 1;
            }
            if (!failed) {
                switch (bits[pos][0]) {
                     case '"' :
                     case '\'' :
                     case '`' :
                         j = pos;
                         while (j < sizeof(bits) &&
                                    bits[j][<1] != bits[pos][0]) {
                              j++;
                         }
                         if (j < sizeof(bits)) {
                              matches += ({ j });
                              pos = j + 1;
                         } else {
                              failed = 1;
                         }
                         break;
                     default :
                         failed = 1;
                         break;
                }
            }
            break;
         case SHORT_STRING :
            if (last) {
               delayed += ({ SINGLE_WORD });
            } else {
               delayed = ({ STRING });
            }
            word_offset++;
            pos++;
            last = FIND_FIRST;
            break;
         case SINGLE_WORD :
            if (last) {
               delayed += ({ SINGLE_WORD });
               word_offset++;
               pos++;
            } else {
               matches += ({ pos });
               pos++;
            }
            failed |= pos > sizeof(bits);
            break;
         case NUMBER :
         case FRACTION :
            failed = 1;
            if (last == FIND_LAST) {
               for (j = sizeof(bits) - 1; j >= pos; j--)
                  if ((bits[j][0] >= '0' && bits[j][0] <= '9') ||
                        (pattern[i] != FRACTION && bits[j][0] == '-' &&
                         bits[j][1] >= '0' && bits[j][1] <= '9')) {
                     if (pattern[i] != FRACTION || sizeof(explode(bits[j], "/")) > 1) {
                        failed = 0;
                        pos = j + 1;
                        break;
                     }
                  }
            } else if (last == FIND_FIRST) {
               for (j = pos; j < sizeof(bits); j++)
                  if ((bits[j][0] >= '0' && bits[j][0] <= '9') ||
                        (pattern[i] != FRACTION && bits[j][0] == '-' &&
                         bits[j][1] >= '0' && bits[j][1] <= '9')) {
                     if (pattern[i] != FRACTION || sizeof(explode(bits[j], "/")) > 1) {
                        failed = 0;
                        pos = j + 1;
                        break;
                     }
                  }
            } else {
               if (pos < sizeof(bits) &&
                     ((bits[pos][0] >= '0' && bits[pos][0] <= '9') ||
                        (pattern[i] != FRACTION && bits[pos][0] == '-' &&
                         bits[pos][1] >= '0' && bits[pos][1] <= '9'))) {
                  failed = 0;
                  pos++;
               } else {
                  failed = 1;
               }
            }
            if (!failed) {
               if (sizeof(delayed)) {
                  pos -= word_offset;
                  for (j=0;j<sizeof(delayed);j++) {
                     switch (delayed[j]) {
                        case STRING :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                        case OPTIONAL :
                           matches += ({ matches[<1] });
                           break;
                        case SINGLE_WORD :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                     }
                  }
                  delayed = ({ });
                  word_offset = 0;
               }
               last = FIND_NONE;
               matches += ({ pos - 1 });
            }
            break;
         case OPTIONAL_SPACES :
         case OPTIONAL :
         case WORD_LIST_SPACES :
            switch (pattern[i]) {
               case OPTIONAL_SPACES :
                  spaces = opt = 1;
                  break;
               case OPTIONAL:
                  opt = 1;
                  break;
               case WORD_LIST_SPACES :
                  spaces = 1;
                  break;
            }
         case WORD_LIST :
            if (pointerp(pattern[++i])) {
               string *words;
               if (spaces) {
                  tmp = "";
                  foreach (words in pattern[i])
                     tmp += implode(words, " ") + "|";
                  tmp = tmp[0..<2];
               }
               _curpat += (sizeof(pattern[i]) > 1?"{":"");
               _curpat += (spaces ? tmp : implode(pattern[i], "|")) +
                  (opt?"] ":(sizeof(pattern[i]) > 1?"} ":" "));
               elms = pattern[i];
            } else {
               _curpat += pattern[i] + (opt?"] ":"} ");
               elms = (string *)master()->query_word_list(pattern[i]);
               if (!elms) {
                  elms = query_word_list(pattern[i]);
               }
            }
            if (!pointerp(elms) || !sizeof(elms))
               failed = 1;
            else {
               if (!(last || failed || spaces)) {
                  tmp = member_array(bits[pos], elms);
                  if (tmp == -1) {
                     failed = 1;
                  }
               } else if (sizeof(elms) == 1 && last == FIND_FIRST && !spaces) {
                  tmp = member_array(elms[0], bits[pos..]);
                  if (tmp != -1) {
                     pos += tmp;
                  } else {
                     failed = 1;
                  }
               } else if (!spaces) {
                  tmp = bits[pos..] - elms;
                  if (sizeof(tmp) < sizeof(bits)-pos) {
                     if (last == FIND_FIRST) {
                        for (j = 0; (j+pos) < sizeof(bits) && j < sizeof(tmp) &&
                                  bits[j+pos] == tmp[j]; j++);
                        pos += j;
                     } else {
                        int k;
                        for (j = sizeof(tmp)-1, k = sizeof(bits)-1;
                               j >= 0 && bits[k] == tmp[j]; j--, k--);
                        pos = k;
                     }
                  } else {
                     failed = 1;
                  }
               } else {
                  string *elem;
                  int success;
                  foreach(elem in elms) {
                     if (!last) {
                        if (implode(bits[pos..pos+sizeof(elem)-1], " ") ==
                              implode(elem, " ")) {
                           success = 1;
                           wcount = sizeof(elem);
                           break;
                        }
                        failed = 1;
                     } else {
                        tmp = bits[pos..] - elem;
                        if (sizeof(tmp) <= (sizeof(bits) - pos - sizeof(elem))) {
                           success = 1;
                           wcount = sizeof(elem);
                           if (last == FIND_FIRST) {
                              for (j = 0; (j+pos) < sizeof(bits) && j < sizeof(tmp) &&
                                        bits[j+pos] == tmp[j]; j++);
                              pos += j;
                              break;
                           } else {
                              int k;
                              for (j = sizeof(tmp)-1, k = sizeof(bits)-1;
                                     j >= 0 && bits[k] == tmp[j]; j--, k--);
                              pos = k - wcount + 1;
                              break;
                           }
                        } else {
                           failed = 1;
                        }
                     }
                  }
                  if (success) {
                     failed = 0;
                  }
               }
            }
            if (opt && failed) {
               failed = 0;
               if (!last)
                  matches += ({ pos - 1 });
               else {
                  delayed += ({ OPTIONAL });
                  opt = 0;
                  spaces = 0;
                  break;
               }
            } else {
               if (!failed) {
                   pos += wcount;
               }
               if (sizeof(delayed) && !failed) {
                  pos -= word_offset;
                  for (j=0;j<sizeof(delayed);j++) {
                     switch (delayed[j]) {
                        case STRING :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                        case OPTIONAL :
                           matches += ({ matches[<1] });
                           break;
                        case SINGLE_WORD :
                           matches += ({ pos - 1 });
                           pos++;
                           break;
                     }
                  }
                  delayed = ({ });
                  word_offset = 0;
               }
               if (!failed) {
                  last = FIND_NONE;
                  matches += ({ pos - 1 });
               }
               wcount = 1;
               delayed = ({ });
            }
            opt = 0;
            spaces = 0;
            last = FIND_NONE;
            break;
      }
   }
   if (sizeof(delayed)) {
      if ( 1) {
         pos = sizeof(bits) + 1;
         pos -= word_offset;
         for (j=0;j<sizeof(delayed);j++) {
            switch (delayed[j]) {
               case OPTIONAL :
                  matches += ({ matches[<1] });
                  break;
               case SINGLE_WORD :
               case STRING :
                  matches += ({ pos - 1 });
                  pos++;
                  break;
            }
         }
         delayed = ({ });
         word_offset = 0;
         pos = sizeof(bits);
      } else
         pos = -1;
   }
   matches += ({ sizeof(bits) });
   if (failed || pos != sizeof(bits)) {
      return 0;
   }
   return matches + ({ sizeof(bits)+1 });
}
int check_living(object ob) {
   return living(ob);
}
int check_if_creator(object ob) {
   return (int)ob->query_creator() &&
      !(ob == this_player() || ob->query_invis());
}
int check_if_allowed(object ob) {
   return ob != this_player() && reference_allowed(ob);
}
class obj_match my_find_match(string pattern, object *where, int type) {
    object ob;
    class obj_match omatch;
    where = copy(where);
    foreach (ob in where) {
         if (ob && (!ob->query_closed() ||
                        (ob->query_closed() && !ob->query_property("opaque")))) {
             if (ob->query_mirror_room()) {
                  where += ({ ob->query_mirror_room() });
             }
         } else {
             where -= ({ ob });
         }
    }
    if (!sizeof(where)) {
         omatch = new(class obj_match);
         omatch->text = lower_case(pattern);
         omatch->objects = ({   });
         omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
         return omatch;
    }
    omatch = (class obj_match)match_objects_in_environments(pattern,
                                          where, type, this_object());
    if (omatch->result != OBJ_PARSER_SUCCESS) {
         ob = find_object(pattern);
         if (ob && member_array(environment(ob), where) != -1) {
             omatch->text = lower_case(pattern);
             omatch->objects = ({ ob });
             omatch->result = OBJ_PARSER_SUCCESS;
         }
    }
    return omatch;
}
private class obj_match match_objects(int type, string pattern, object *env) {
   class obj_match omatch;
   class obj_match new_omatch;
   object* tmp;
   switch (type) {
   case WIZ_PRESENT_TARGET :
      omatch = new(class obj_match);
      omatch->text = pattern;
      omatch->objects = WIZ_PRESENT->wiz_present(pattern, env[0]);
      if (sizeof(omatch->objects)) {
          omatch->result = OBJ_PARSER_SUCCESS;
      } else {
          omatch->result = OBJ_PARSER_NO_MATCH;
      }
      break;
   case ANY_OBJECT :
      omatch = my_find_match(pattern, env, 0);
      break;
   case DISTANT_LIVING :
      omatch = new(class obj_match);
      omatch->text = pattern;
      if ( environment() && !this_object()->query_creator() ) {
         if ( environment()->query_property( "no remote" ) ) {
            omatch->objects = ({ });
            omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
            break;
         }
      }
      omatch->objects = filter(map(explode(lower_case(pattern), ","),
                  (: find_living( lower_case(this_object()->
            expand_nickname( $1 ))) :) ), (: $1 && check_if_allowed($1) :) );
      omatch->objects = uniq_array(omatch->objects);
      if (sizeof(omatch->objects)) {
          omatch->result = OBJ_PARSER_SUCCESS;
      } else {
          omatch->result = OBJ_PARSER_NO_MATCH;
      }
      break;
   case LIVING :
      omatch = my_find_match(pattern, env, OBJ_PARSER_TYPE_LIVING);
      tmp = filter(omatch->objects, (: check_living( $1 ) :) );
      if (sizeof(omatch->objects) != sizeof(tmp)) {
          if (pattern != "all") {
               omatch->result = OBJ_PARSER_NOT_LIVING;
               omatch->objects -= tmp;
          } else {
               omatch->objects = tmp;
          }
      }
      break;
   case TARGET_PLAYER :
      omatch = new(class obj_match);
      omatch->text = pattern;
      if (environment() && !this_object()->query_creator()) {
         if (environment()->query_property("no remote")) {
            omatch->objects = ({ });
            omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
            break;
         }
      }
      omatch->objects = filter(map(explode(lower_case(pattern), ","),
                  (: find_player( lower_case(this_object()->
            expand_nickname( $1 ))) :) ), (: $1 && check_if_allowed($1) :) );
      omatch->objects = uniq_array(omatch->objects);
      if (!sizeof(omatch->objects)) {
         if (pattern == "creators" && this_object()->query_creator()) {
            omatch->objects = filter(users(), (: check_if_creator($1) :));
         }
      }
      if (sizeof(omatch->objects)) {
          omatch->result = OBJ_PARSER_SUCCESS;
      } else {
          omatch->result = OBJ_PARSER_NO_MATCH;
      }
      break;
   case ANY_LIVING :
      new_omatch = new(class obj_match);
      new_omatch->text = pattern;
      if ( environment() && !this_object()->query_creator() ) {
         if ( environment()->query_property( "no remote" ) ) {
            new_omatch->objects = ({ });
            new_omatch->result = OBJ_PARSER_BAD_ENVIRONMENT;
            omatch = new_omatch;
         }
      }
      if (new_omatch->result != OBJ_PARSER_BAD_ENVIRONMENT) {
         new_omatch->objects = filter(map(explode(lower_case(pattern), ","),
                                     (: find_player( lower_case(this_object()->
            expand_nickname( $1 ))) :) ), (: $1 && check_if_allowed($1) :) );
         new_omatch->objects = uniq_array(new_omatch->objects);
         if(sizeof(new_omatch->objects)) {
            new_omatch->result = OBJ_PARSER_SUCCESS;
            omatch = new_omatch;
         }
      }
      if(!omatch || omatch->result != OBJ_PARSER_SUCCESS ||
         !sizeof(omatch->objects)) {
         omatch = my_find_match(pattern, env, OBJ_PARSER_TYPE_LIVING);
         tmp = filter(omatch->objects, "check_living", this_object());
         if (sizeof(omatch->objects) != sizeof(tmp)) {
            if (pattern != "all") {
               omatch->result = OBJ_PARSER_NOT_LIVING;
               omatch->objects -= tmp;
            } else {
               omatch->objects = tmp;
            }
         }
      }
      if (omatch->result != OBJ_PARSER_SUCCESS) {
         new_omatch = new(class obj_match);
         new_omatch->text = pattern;
         if (pattern == "creators" && this_object()->query_creator()) {
            new_omatch->objects = filter(users(), (: check_if_creator($1) :));
         }
         if (pattern == "someone") {
            new_omatch->objects = filter(users(), (: check_if_allowed($1) :));
            if (sizeof(new_omatch->objects) > 1) {
               new_omatch->objects = ({ new_omatch->objects[random(sizeof(new_omatch->objects))]});
            }
         }
         if (sizeof(new_omatch->objects)) {
            new_omatch->result = OBJ_PARSER_SUCCESS;
            omatch = new_omatch;
         }
      }
      break;
   }
   if (!omatch) {
      omatch = new(class obj_match);
      omatch->text = pattern;
      omatch->objects = ({ });
      omatch->result = OBJ_PARSER_NO_MATCH;
      return omatch;
   }
   return omatch;
}
void setup_failed_mess(class obj_match failed_match) {
    switch (failed_match->result) {
    case OBJ_PARSER_BAD_ENVIRONMENT :
       _failed_mess[0] += "Cannot find \""+ failed_match->text +
                                    "\" here, access is not allowed.\n";
       break;
    case OBJ_PARSER_NOT_LIVING :
       _failed_mess[0] += "The objects \""+
                                    query_multiple_short(failed_match->objects) +
                                    "\" are not living.\n";
       break;
    case OBJ_PARSER_TOO_DARK :
       _failed_mess[0] += "Cannot find \""+ failed_match->text +
                                    "\", it is too dark.\n";
       break;
    default :
       _failed_mess[0] += match_objects_failed_mess(failed_match);
       break;
    }
}
private int handle_command(string *bits, int *matches, mixed *pattern,
                            mixed *command, string pattern_string) {
   int p;
   int failed;
   int i;
   int j;
   int k;
   string dir_match;
   string fail_mess_check;
   string *add_comm_bit;
   string fail_mesg;
   string succ_mesg;
   class obj_match direct_obs;
   object *env;
   object *fail_ob;
   class obj_match failed_match;
   mixed start;
   mixed indirect_obs;
   mixed ret;
   mixed *stuff;
   mixed indir_match;
   mixed bity;
   class obj_match omatch;
   string pattern_str;
   start = 1;
   add_comm_bit = ({ });
   indirect_obs = ({ });
   direct_obs = new(class obj_match);
   direct_obs->objects = ({ });
   if (!sizeof(matches)) {
      return 0;
   }
   for (i=1, p=1;i<sizeof(pattern) && !failed_match;i++,p++) {
      switch (pattern[i]) {
      case DIRECT_OBJECT :
         dir_match = implode(bits[start..matches[p]], " ");
         if (intp(pattern[i+2])) {
             switch (pattern[i+2]) {
                  case ENV_ME :
                     env = ({ this_object() });
                     break;
                  case ENV_HERE :
                     env = ({ environment() });
                     break;
                  case ENV_HERE_ME :
                     env = ({ environment(), this_object() });
                     break;
                  case ENV_ME_HERE :
                     env = ({ this_object(), environment() });
                     break;
             }
         } else if (stringp(pattern[i+2])) {
             ret = find_object(pattern[i+2]);
             if (!ret) {
                  pattern[i+2]->frog_me_a_lot();
                  ret = find_object(pattern[i+2]);
             }
             if (ret) {
                  env = ({ ret });
             }
         }
         direct_obs = match_objects(pattern[++i], dir_match, env);
         i++;
         add_comm_bit += ({ dir_match });
         start = matches[p];
         if (direct_obs->result != OBJ_PARSER_SUCCESS) {
            failed_match = direct_obs;
         }
         break;
      case INDIRECT_OBJECT :
         pattern_str = implode(bits[start..matches[p]], " ");
         if (intp(pattern[i+2])) {
             switch (pattern[i+2]) {
             case ENV_ME :
                env = ({ this_object() });
                break;
             case ENV_HERE :
                env = ({ environment() });
                break;
             case ENV_HERE_ME :
                env = ({ environment(), this_object() });
                break;
             case ENV_ME_HERE :
                env = ({ this_object(), environment() });
                break;
             }
         } else if (stringp(pattern[i+2])) {
             ret = find_object(pattern[i+2]);
             if (!ret) {
                  pattern[i+2]->frog_me_a_lot();
                  ret = find_object(pattern[i+2]);
             }
             if (ret) {
                  env = ({ ret });
             }
         }
         if (pattern[i+2] == ENV_DIRECT_OBS) {
            omatch = new(class obj_match);
            omatch->text = pattern_str;
            omatch->objects = ({ ENV_DIRECT_OBS });
            omatch->result = OBJ_PARSER_SUCCESS;
            i++;
         } else {
            omatch = match_objects(pattern[++i], pattern_str, env);
         }
         i++;
         add_comm_bit += ({ pattern_str });
         if (omatch->result != OBJ_PARSER_SUCCESS) {
            failed_match = omatch;
         } else {
            if (stringp(indir_match)) {
                if (pointerp(indir_match)) {
                     indirect_obs += ({ omatch->objects });
                     indir_match += ({ pattern_str });
                } else {
                     indirect_obs = ({ indirect_obs, omatch->objects });
                     indir_match = ({ indir_match, pattern_str });
                }
            } else {
                indirect_obs = omatch->objects;
                indir_match = pattern_str;
            }
         }
         start = matches[p];
         break;
      case SINGLE_WORD :
      case STRING :
      case SHORT_STRING :
         add_comm_bit += ({ implode(bits[start..matches[p]], " ") });
         break;
      case QUOTED_STRING :
         pattern_str = implode(bits[start..matches[p]], " ");
         add_comm_bit += ({ pattern_str[1..<2] });
         break;
      case NUMBER :
         sscanf(implode(bits[start..matches[p]], " "), "%d", j);
         add_comm_bit += ({ j });
         break;
      case FRACTION :
         sscanf(implode(bits[start..matches[p]], " "), "%d/%s", j, k);
         add_comm_bit += ({ j, k });
         break;
      case OPTIONAL_SPACES :
      case OPTIONAL :
         i++;
         break;
      case WORD_LIST_SPACES :
      case WORD_LIST :
         if (pointerp(pattern[++i]))
            if (sizeof(pattern[i]) > 1)
               add_comm_bit += ({ implode(bits[start..matches[p]], " ") });
         break;
      }
      start = matches[p]+1;
   }
   if (failed_match) {
      if (query_notify_fail()) {
         _failed_mess[1] += query_notify_fail();
         notify_fail(0);
      } else {
         setup_failed_mess(failed_match);
      }
      return (matches[0]?-1:0);
   }
   _fail_mess = ([ ]);
   _succ_mess = ([ ]);
   _succ_mess_dir = ({ });
   _succ_mess_indir = ({ });
   ret = 0;
   if (!sizeof(direct_obs->objects) &&
         (indirect_obs == ENV_DIRECT_OBS ||
          sizeof(indirect_obs & ({ ENV_DIRECT_OBS }) ) ) ) {
      direct_obs->objects = ({ });
      for (i = 0; i < sizeof(command); i += 2) {
          direct_obs->objects += ({ command[i] });
      }
   }
   if (!sizeof(direct_obs->objects)) {
      indirect_obs -= ({ ENV_DIRECT_OBS });
      for (i = 0; i < sizeof(command) && !ret;i += 2) {
         if (!add_comm_bit) {
            add_comm_bit = ({ });
            start = 1;
            for (j = 0; j < sizeof(matches); j++) {
               add_comm_bit += implode(bits[start..matches[j]], " ");
               start = matches[j]+1;
            }
         }
         if (functionp(command[i+1])) {
            if ( functionp( command[ i + 1 ] ) & FP_OWNER_DESTED ) {
               start = command[i];
               if (!start) {
                  remove_object_force(start);
                  if (start == command[i]) {
                     remove_from_command(bits[0], start);
                  }
                  ret = 0;
                  continue;
               }
            }
            ret = evaluate(command[i+1], indirect_obs, dir_match, indir_match,
                                  add_comm_bit, pattern_string, bits[0]);
         } else {
            start = command[i];
            if (!start) {
               remove_object_force(start);
               if (start == command[i]) {
                  remove_from_command(bits[0], start);
               }
               ret = 0;
               continue;
            }
            do {
               if (function_exists("do_"+bits[0], start)) {
                  ret = call_other(start, "do_"+bits[0], indirect_obs,
                                             dir_match, indir_match, add_comm_bit,
                                             pattern_string);
                  break;
               } else {
                  start = shadow(start, 0);
               }
            } while (start);
            if (!start) {
                ret = call_other(command[i], "command_control", bits[0],
                                          indirect_obs,
                                          dir_match, indir_match, add_comm_bit,
                                          pattern_string);
            }
         }
      }
      if (!ret || ret == -1) {
         if (query_notify_fail()) {
            _failed_mess[1] += query_notify_fail();
            notify_fail(0);
         } else {
            fail_mess_check = get_fail_messages( bits[ 0 ], ({ }) );
            if (_failed_mess[1] == "") {
                _failed_mess[1] += fail_mess_check;
            }
         }
      }
      if (_succ_mess_dir) {
          print_special_messages( bits[ 0 ] );
      }
      _fail_mess = ([ ]);
      return ret;
   }
   fail_ob = ({ });
   bity = ({ });
   failed = 0;
   for (i=0;i<sizeof(direct_obs->objects);i++) {
      j = member_array(direct_obs->objects[i], command);
      if (j == -1) {
         fail_ob += ({ direct_obs->objects[i] });
         continue;
      }
      if (!direct_obs->objects[i]->short()) {
         continue;
      }
      if (member_array(ENV_DIRECT_OBS, indirect_obs) != -1) {
         failed_match = my_find_match(indir_match, ({ direct_obs->objects[i] }), 0);
         if (failed_match->result == OBJ_PARSER_SUCCESS) {
             stuff = failed_match->objects;
         } else {
             stuff = ({ });
         }
         debug_printf("Direct Obs Env (%O %O %O)\n", indir_match, stuff, direct_obs->objects[i]);
      } else if (pointerp(indir_match)) {
         failed_match = 0;
         stuff = copy(indirect_obs);
         for (k = 0; k < sizeof(indirect_obs); k++) {
            if (intp(stuff[k]) || ( arrayp(stuff[k]) && sizeof( stuff[k] ) &&
                intp(stuff[k][0]) ) ) {
               failed_match = my_find_match(indir_match[k], ({ direct_obs->objects[i] }), 0);
               if (failed_match->result == OBJ_PARSER_SUCCESS) {
                  stuff[k] = failed_match->objects;
               } else {
                  break;
               }
            }
         }
      } else {
         stuff = indirect_obs;
         failed_match = 0;
      }
      if (failed_match && failed_match->result != OBJ_PARSER_SUCCESS) {
         setup_failed_mess(failed_match);
         failed = 1;
         continue;
      }
      if (functionp(command[j+1])) {
         if (functionp(command[j+1]) & FP_OWNER_DESTED) {
            start = direct_obs->objects[i];
            if (!start) {
                remove_object_force(start);
                if (start == command[i]) {
                   remove_from_command(bits[0], start);
                }
                ret = 0;
                continue;
            } else {
                if (start == command[i]) {
                    remove_from_command(bits[0], start);
                }
                ret = 0;
                continue;
            }
         }
         ret = evaluate(command[j+1], stuff, dir_match, indir_match,
                        add_comm_bit, pattern_string, bits[0]);
      } else {
         start = direct_obs->objects[i];
         if (!start) {
             remove_object_force(start);
             if (start == command[i]) {
                remove_from_command(bits[0], start);
             }
             ret = 0;
             continue;
         }
         do {
            if (function_exists("do_"+bits[0], start)) {
                ret = call_other(start, "do_"+bits[0], stuff,
                                          dir_match, indir_match, add_comm_bit,
                                          pattern_string);
                break;
            } else {
                start = shadow(start, 0);
            }
         } while (start);
         if (!start) {
             ret = call_other(direct_obs->objects[i], "command_control", bits[0], stuff,
                                       dir_match, indir_match, add_comm_bit,
                                       pattern_string);
         }
      }
      if (stringp(ret) || pointerp(ret)) {
         bity += ({ ret });
      } else if (ret && ret != -1) {
         bity += ({ direct_obs->objects[i]});
      } else {
         fail_ob += ({ direct_obs->objects[i] });
         if (ret == -1) {
            failed = 1;
         }
      }
   }
   if (!sizeof(bity)) {
      fail_mess_check = get_fail_messages( bits[ 0 ], fail_ob );
      if (query_notify_fail()) {
         _failed_mess[1] += query_notify_fail();
         notify_fail(0);
      } else if (_failed_mess[1] == "") {
         _failed_mess[1] += fail_mess_check;
         if (_failed_mess[1] == "" && sizeof(fail_ob)) {
            notify_fail(0);
            fail_mesg = create_message(bits, matches, pattern, fail_ob, 1);
            if (!pointerp(indirect_obs)) {
               _failed_mess[1] += "You cannot " + bits[ 0 ] +
                   replace_string( fail_mesg, "$succ_indir$",
                                          ( pointerp( indir_match ) ?
                                             query_multiple_short( indir_match ) :
                                             indir_match) );
            } else {
               if (pointerp(indir_match)) {
                   bity = explode("F" + fail_mesg, "$succ_indir$");
                   _failed_mess[1] += "You cannot "+ bits[ 0 ];
                   bity[0] = bity[0][1..];
                   for (i = 0; i < sizeof(bity) - 1; i++) {
                        if (i >= sizeof(indir_match)) {
                            if (stuff && pointerp(stuff[<1])) {
                                 _failed_mess[1] += bity[i] +
                                                             query_multiple_short( stuff[<1] );
                            } else {
                                 _failed_mess[1] += bity[i] +
                                                             query_multiple_short( indir_match[<1] );
                            }
                        } else {
                            if (stuff && pointerp(stuff[i])) {
                                 _failed_mess[1] += bity[i] +
                                                             query_multiple_short( stuff[i] );
                            } else {
                                 _failed_mess[1] += bity[i] + indir_match[i];
                            }
                        }
                   }
                   _failed_mess[1] += bity[<1];
               } else {
                  if ( member_array( ENV_DIRECT_OBS, indirect_obs ) == -1 ) {
                     stuff = indirect_obs;
                  }
                  if ( member_array( this_player(), stuff ) == -1 ) {
                     _failed_mess[1] += "You cannot "+ bits[ 0 ] +
                           replace_string( fail_mesg, "$succ_indir$",
                                                query_multiple_short( stuff, "a" ) );
                  } else {
                     _failed_mess[1] += "You cannot "+ bits[ 0 ] +
                        replace_string( fail_mesg, "$succ_indir$",
                                                query_multiple_short( stuff -
                                                                                 ({this_player()}) +
                                                                                 ({ "yourself" }),
                                                                                 "a" ) );
                  }
               }
            }
         }
      }
      _fail_mess = ([ ]);
      if (!failed) {
          return 0;
      }
      return -1;
   }
   if (sizeof(bity) != sizeof(_succ_mess_dir)) {
      succ_mesg = create_message( bits, matches, pattern, bity - _succ_mess_dir);
      if ( member_array( this_player(), _succ_indir ) == -1 ) {
         write( "You "+ bits[ 0 ] + replace( succ_mesg, "$succ_indir$",
                                                               query_multiple_short( _succ_indir,
                                                                                                "one" ) ) );
         stuff = _succ_indir;
      } else {
         write("You "+ bits[0] + replace(succ_mesg, "$succ_indir$",
                                                         query_multiple_short(_succ_indir -
                                                                                        ({ this_player() })
                                                                                        + ({ "yourself" }),
                                                                                        "one") ) );
         stuff = _succ_indir - ({ this_player() });
         stuff = ({ (string)this_player()->query_objective() +"self" }) + stuff;
      }
      say( capitalize( (string)this_player()->the_short() ) +" "+
             pluralize(bits[0]) + replace(succ_mesg, "$succ_indir$",
                                                         query_multiple_short(stuff, "one")),
             _succ_indir );
      for ( i = 0; i < sizeof( _succ_indir ); i++ ) {
         if ( _succ_indir[ i ] != this_player() ) {
            tell_object( _succ_indir[ i ],
                               capitalize( (string)this_player()->the_short() ) +" "+
                               pluralize(bits[0]) + replace(succ_mesg, "$succ_indir$",
                                                                           query_multiple_short(stuff -
                                                                              ({ _succ_indir[i] }) +
                                                                              ({ "you" }), "one" ) ) );
         }
      }
      if (sizeof(_succ_mess_dir)) {
          print_special_messages( bits[ 0 ] );
      }
   } else {
      print_special_messages( bits[ 0 ] );
   }
   _succ_indir = ({ });
   _succ_mess = ([ ]);
   _succ_mess_dir = ({ });
   _succ_mess_dir = ({ });
   return 1;
}
void print_special_messages( string verb ) {
    int i, j;
    string words, *messes;
    string type;
    mixed *stuff, *tmp;
    messes = keys( _succ_mess );
    for ( i = 0; i < sizeof( messes ); i++ ) {
         if ( functionp( messes[i] ) ||
                (messes[i][0..1] == MY_MESS_HEADER &&
                  strlen(messes[i]) > 2)) {
            if (functionp(messes[i])) {
                words = evaluate(messes[i], 0);
            } else {
                words = messes[i][2..];
            }
            type = "one";
            if (strsrch("$Iposs$", words) != -1) {
                type = "poss";
                words = replace_string(words, "$Iposs$", "");
            }
            if (strsrch("$Ithe$", words) != -1) {
                type = "the";
                words = replace_string(words, "$Ithe$", "");
            }
            if (strsrch("$Ia$", words) != -1) {
                type = "a";
                words = replace_string(words, "$Ia$", "");
            }
            if ( member_array( this_player(), _succ_mess[ messes[ i ] ][ 1 ] ) ==
                     -1 ) {
                words = capitalize( replace( words, ({ "$C$", "$CATFROG",
                         "$N", "you", "$p ", "your ",
                         "$r", "you", "$o", "you", "$V", verb, "$es", "",
                         "$s", "", "$y", "y",
                         "$I", query_multiple_short( _succ_mess[ messes[ i ] ][ 1 ],
                                                          type ) }) ) );
            } else {
                words = capitalize( replace( words, ({ "$C$", "$CATFROG",
                         "$N", "you", "$p ", "your ",
                         "$r", "you", "$o", "you", "$V", verb, "$es", "", "$s", "",
                         "$y", "y",
                         "$I", query_multiple_short( (mixed *)_succ_mess[ messes[ i ] ][ 1 ] -
                         ({ this_player() }) + ({ "yourself" }), type ) }) ) );
            }
            write( replace( words, ({ "$D",
                                    query_multiple_short( _succ_mess[ messes[ i ] ][ 0 ],
                                                                     "one" ),
                                    "$CATFROG", "$C$" }) ) );
         } else if (messes[i][0..1] == OTHER_MESS_HEADER &&
                         strlen(messes[i]) > 2) {
            if (functionp(messes[i])) {
               words = replace( evaluate(messes[i], 1),
                   ({ "$C$", "$CATFROG",
                        "$N", (string)this_player()->the_short(),
                        "$p ", (string)this_player()->query_possessive() +" ",
                        "$r", (string)this_player()->query_pronoun(),
                        "$o", (string)this_player()->query_objective(),
                        "$V", pluralize( verb ), "$es", "es", "$s", "s", "$y", "ies" }) );
            } else {
               words = replace( messes[i][2..],
                   ({ "$C$", "$CATFROG",
                        "$N", (string)this_player()->the_short(),
                        "$p ", (string)this_player()->query_possessive() +" ",
                        "$r", (string)this_player()->query_pronoun(),
                        "$o", (string)this_player()->query_objective(),
                        "$V", pluralize( verb ), "$es", "es", "$s", "s", "$y", "ies" }) );
            }
            words = replace( words, "$D",
                     query_multiple_short( _succ_mess[ messes[ i ] ][ 0 ], "one" ) );
            if (member_array(this_player(), _succ_mess[ messes[i] ][ 1 ]) == -1) {
               stuff = _succ_mess[messes[i]][1];
            } else {
                stuff = ({ (string)this_player()->query_objective() +"self" });
                stuff += (mixed *)_succ_mess[ messes[ i ] ][ 1 ] - ({ this_player() });
            }
            type = "one";
            if (strsrch("$Iposs$", words) != -1) {
                type = "poss";
                words = replace_string(words, "$Iposs$", "");
            }
            if (strsrch("$Ithe$", words) != -1) {
                type = "the";
                words = replace_string(words, "$Ithe$", "");
            }
            if (strsrch("$Ia$", words) != -1) {
                type = "a";
                words = replace_string(words, "$Ia$", "");
            }
            say( capitalize( replace( words, ({ "$I", query_multiple_short( stuff,
                                                                                                       type),
                                                   "$CATFROG", "$C$" }) ) ),
                     _succ_mess[ messes[ i ] ][ 1 ] );
            for ( j = 0; j < sizeof( _succ_mess[ messes[ i ] ][ 1 ] ); j++ ) {
                if ( _succ_mess[ messes[ i ] ][ 1 ][ j ] != this_player() ) {
                     if (strsrch(words, "$I's") != -1) {
                         tmp = stuff - _succ_mess[ messes[ i ] ][ 1 ][ j..j ];
                         tell_object( _succ_mess[ messes[ i ] ][ 1 ][ j ],
                               capitalize( replace( words, ({ "$I's",
                                                 query_multiple_short( tmp + ({ "your" }) ),
                                                 "$I", query_multiple_short( tmp + ({ "you" }),
                                                                                           "one"),
                                                 "$CATFROG", "$C$" }) ) ) );
                     } else {
                         tell_object( _succ_mess[ messes[ i ] ][ 1 ][ j ],
                               capitalize( replace( words, ({ "$I",
                                                               query_multiple_short( stuff -
                               ({ _succ_mess[ messes[ i ] ][ 1 ][ j ] }) + ({ "you" }),
                               "one"), "$CATFROG", "$C$" }) ) ) );
                     }
                }
            }
       }
   }
}
string get_fail_messages( string verb, object *fail_obs ) {
    string whole;
    string words;
    string mess;
    string *str;
    object ob;
    class fail_mess_data data;
    whole = "";
    foreach (mess, data in _fail_mess) {
         if ( !stringp( mess ) ) {
             continue;
         }
         str = ({ });
         foreach(ob in data->direct)
            str += ({ "one_short:" + sprintf("%O", ob) });
         words = this_player()->evaluate_message( ({ mess, ({ str }) }) );
         words = replace( words,
                                  ({ "$D", query_multiple_short( data->direct, "one" ),
                                       "$V", verb }) );
         if ( member_array( this_player(), data->indirect) == -1 )
             words = replace( words, "$I",
                      query_multiple_short( data->indirect, "one" ) );
         else
             words = replace( words, "$I",
                      query_multiple_short( data->indirect -
                      ({ this_player() }) + ({ "yourself" }), "one" ) );
         whole += capitalize( words );
    }
    return whole;
}
string *query_word_list(string list) {
   return 0;
}
varargs string create_message(string *bits, int *matches, mixed *pattern,
                                             object *dir, int flag) {
   string ret;
   int i, pos;
   ret = " ";
   if (matches[0])
      matches[0] = 0;
   for (i=1;i<sizeof(pattern);i++, pos++) {
      switch (pattern[i]) {
      case DIRECT_OBJECT :
         if (member_array(this_player(), dir) != -1)
            ret += query_multiple_short(dir - ({ this_player() }) +
                                                      ({ "yourself" }), (flag?"a":"one"));
         else
            ret += query_multiple_short(dir, (flag?"a":"one"));
         i += 2;
         break;
      case INDIRECT_OBJECT :
         ret += "$succ_indir$";
         i += 2;
         break;
      case SHORT_STRING :
      case STRING :
         ret += implode(bits[matches[pos]+1..matches[pos+1]], " ");
         break;
      case WORD_LIST_SPACES :
         pos += matches[pos+1]-1;
      case WORD_LIST :
         ret += implode(bits[matches[pos]+1..matches[pos+1]], " ");
         i++;
         break;
      case NUMBER :
      case FRACTION :
      case SINGLE_WORD :
         ret += bits[matches[pos]+1];
         break;
      case OPTIONAL_SPACES :
         if (!matches[pos] == matches[pos+1])
            pos += matches[pos+1]-1;
      case OPTIONAL :
         if (matches[pos] == matches[pos+1]) {
            if (pointerp(pattern[i+1][0]))
               ret += implode(pattern[i+1][0], " ");
            else
               ret += pattern[i+1][0];
         } else {
            ret += implode(bits[matches[pos]+1..matches[pos+1]], " ");
         }
         i++;
         break;
      }
      if (i+1 < sizeof(pattern))
         ret += " ";
   }
   return ret+".\n";
}