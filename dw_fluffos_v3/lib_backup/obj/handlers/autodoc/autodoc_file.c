#define MASTER_OB "/secure/master.c"
#define EOF -1
#define SAVE_DIR "/save/autodoc/"
nosave mapping private_functions;
mapping public_functions;
mapping protected_functions;
mapping inherits;
mapping main_docs;
mapping define_docs;
mapping includes;
mapping class_docs;
string file_name;
int last_changed;
int num_failed_tries;
nosave string current_comment;
nosave string current_file;
nosave int current_position;
nosave int changed;
nosave mapping defines;
nosave mixed *exclude_methods;
private void setup();
private mapping parse_comment(string stuff);
private void do_parse_file(function func);
private int query_file_position();
private void handle_inherit(mixed *bits);
void create() {
   seteuid(getuid());
   setup();
}
private void setup() {
   changed = 0;
   main_docs = 0;
   file_name = "";
   private_functions = ([ ]);
   public_functions = ([ ]);
   protected_functions = ([ ]);
   inherits = ([ ]);
   defines = ([ ]);
   define_docs = ([ ]);
   includes = ([ ]);
   class_docs = ([ ]);
   current_comment = 0;
   current_file = "";
   current_position = 0;
   last_changed = 0;
   exclude_methods = ({ "setup", "create", "init", "dest_me", "reset" });
}
private int query_file_position() {
   return current_position;
}
private int lookahead_character(int num) {
   if (current_position + num - 1 < strlen(current_file)) {
      return current_file[current_position + num - 1];
   }
   return EOF;
}
private int next_character() {
   if (current_position < strlen(current_file)) {
      return current_file[current_position++];
   }
   return EOF;
}
private int pop_character(int num) {
   current_position += num;
}
private void skip_to_end_of_line() {
   int ch;
   do {
      ch = next_character();
   } while (ch != '\r' && ch != '\n' && ch != EOF);
}
private string skip_to_end_of_comment() {
   string data;
   int ch;
   int ok;
   data = "";
   do {
      ok = 1;
      ch = next_character();
      if (ch == '*' && lookahead_character(1) == '/') {
         ok = 0;
         pop_character(1);
      } else if (ch == '\r' || ch == '\n') {
         data += "\n";
         if (lookahead_character(1) == ' ') {
            pop_character(1);
         }
         if (lookahead_character(1) == '*' && lookahead_character(2) != '/') {
            pop_character(1);
            if (lookahead_character(1) == ' ') {
               pop_character(1);
            }
         }
      } else if (ch == EOF) {
         ok = 0;
      } else if (ch == '\\' && (lookahead_character(1) == '/' ||
                               lookahead_character(1) == '*' ||
                               lookahead_character(1) == '\\')) {
      } else {
         data += sprintf("%c", ch);
      }
   } while (ok);
   return data;
}
private void skip_spaces_and_comments() {
   int ok;
   do {
     switch (lookahead_character(1)) {
        case ' ' :
        case '\t' :
        case '\n' :
        case '\r' :
           ok = 1;
           pop_character(1);
           break;
        case '/' :
           if (lookahead_character(2) == '/') {
              ok = 1;
              skip_to_end_of_line();
           } else if (lookahead_character(2) == '*') {
              ok = 1;
              if (lookahead_character(3) != '*' ||
                  lookahead_character(4) == '*') {
                 pop_character(2);
                 skip_to_end_of_comment();
                 current_comment = 0;
              } else {
                 pop_character(3);
                 if (lookahead_character(1) == ' ') {
                    pop_character(1);
                 }
                 if (!main_docs) {
                    main_docs = parse_comment(skip_to_end_of_comment());
                 } else {
                    current_comment = skip_to_end_of_comment();
                 }
              }
           } else {
              ok = 0;
           }
           break;
        default :
           ok = 0;
           break;
     }
   } while (ok);
}
private string expand_token(string token) {
   if (defines[token]) {
      return defines[token];
   }
   return 0;
}
private string get_word() {
   string data;
   int ok;
   int ch;
   skip_spaces_and_comments();
   ok = 1;
   data = "";
   ch = lookahead_character(1);
   if ((ch >= 'a' && ch <= 'z') ||
       (ch >= 'A' && ch <= 'Z') ||
       (ch == '_')) {
      do {
         ch = lookahead_character(1);
         if ((ch >= 'a' && ch <= 'z') ||
             (ch >= 'A' && ch <= 'Z') ||
             (ch >= '0' && ch <= '9') ||
             (ch == '_')) {
            ch = next_character();
            data += sprintf("%c", ch);
         } else {
            ok = 0;
         }
      } while (ok);
      if (expand_token(data)) {
         current_file = expand_token(data) + current_file[current_position..];
         current_position = 0;
         return get_word();
      }
   } else if ((ch >= '0' && ch <= '9') ||
              (ch == '-')) {
      if (ch == '-') {
         data += sprintf("%c", next_character());
      }
      do {
         ch = lookahead_character(1);
         if ((ch >= '0' && ch <= '9') ||
             (ch >= '.')) {
            ch = next_character();
            data += sprintf("%c", ch);
         } else {
            ok = 0;
         }
      } while (ok);
   } else if (ch == '\"' || ch == '\'') {
      int end_ch;
      end_ch = ch;
      ch = next_character();
      data += sprintf("%c", ch);
      do {
         ch = next_character();
         if (ch == end_ch) {
            ok = 0;
            data += sprintf("%c", ch);
         } else if (ch == '\\') {
            ch = next_character();
            data += sprintf("\\%c", ch);
         } else if (ch == EOF) {
            ok = 0;
         } else {
            data += sprintf("%c", ch);
         }
      } while (ok);
   } else if (ch == '(') {
      if (lookahead_character(2) == '{' ||
          lookahead_character(2) == '[') {
         return sprintf("%c%c", next_character(), next_character());
      }
      return sprintf("%c", next_character());
   } else if (ch == '}' || ch == ']') {
      if (lookahead_character(2) == ')') {
         return sprintf("%c%c", next_character(), next_character());
      }
      return sprintf("%c", next_character());
   } else if (ch == ';' ||
              ch == ')' ||
              ch == '=' ||
              ch == '{' ||
              ch == '}') {
      return sprintf("%c", next_character());
   } else if (ch == EOF) {
      return "";
   } else {
      do {
         ch = lookahead_character(1);
         if ((ch >= 'a' && ch <= 'z') ||
             (ch >= 'A' && ch <= 'Z') ||
             (ch >= '0' && ch <= '9') ||
             (ch == '_') ||
             (ch == ' ') ||
             (ch == '\t') ||
             (ch == '\n') ||
             (ch == '(') ||
             (ch == ')') ||
             (ch == EOF) ||
             (ch == ';') ||
             (ch == '=') ||
             (ch == '{') ||
             (ch == '}') ||
             (ch == '\'') ||
             (ch == '\"') ||
             (ch == '\r')) {
            ok = 0;
         } else {
            ch = next_character();
            data += sprintf("%c", ch);
         }
      } while (ok);
   }
   return data;
}
private mixed *get_statement(string start) {
   mixed *bits;
   string curr;
   int depth;
   string temp_comment;
   int last_pos;
   int in_class;
   bits = ({ start });
   do {
      last_pos = query_file_position();
      curr = get_word();
      bits += ({ curr });
      if (last_pos != query_file_position()) {
         reset_eval_cost();
      }
   } while (curr != ";" && curr != "{" && curr != "");
   if (curr == "{") {
      if (member_array("class", bits) != -1 &&
          member_array("(", bits) == -1) {
         in_class = 1;
      }
      temp_comment = current_comment;
      depth = 1;
      do {
        last_pos = query_file_position();
        curr = get_word();
        if (curr == "{") {
           depth++;
        } else if (curr == "}") {
           depth--;
        } else if (curr == "") {
           depth = 0;
        }
        if (last_pos != query_file_position()) {
           reset_eval_cost();
        }
        if (in_class) {
           bits += ({ curr });
        }
      } while (depth > 0);
      current_comment = temp_comment;
   }
   return bits;
}
private mapping parse_comment(string stuff) {
   string *bits;
   int i;
   mapping frog;
   string name;
   int j;
   int rabbit;
   if (!stuff) {
      return ([ ]);
   }
   if (stuff[0] == '@') {
      stuff = "\n" + stuff;
   } else {
      stuff = "\n@main " + stuff;
   }
   bits = explode(stuff, "\n@");
   frog = ([ ]);
   for (i = 0; i< sizeof(bits); i++) {
      j = strsrch(bits[i], " ");
      rabbit = strsrch(bits[i], "\n");
      if (j == -1 || (rabbit != -1 && rabbit < j)) {
         j = rabbit;
      }
      if (j > 0) {
         name = bits[i][0..j - 1];
         stuff = bits[i][j+1..];
         if (!frog[name]) {
            frog[name] = ({ stuff });
         } else {
            frog[name] += ({ stuff });
         }
      }
   }
   return frog;
}
private void handle_class(mixed *bits) {
   string name;
   int i;
   string *types;
   mapping comm;
   name = bits[1];
   types = ({ });
   i = member_array("{", bits);
   if (i != -1) {
      bits = bits[i + 1..];
      while (sizeof(bits)) {
         i = member_array(";", bits);
         if (i != -1) {
            types += ({ ({ bits[i - 1], bits[0..i - 2] }) });
            bits = bits[i + 1..];
         } else {
            bits = ({ });
         }
      }
      comm = parse_comment(current_comment);
      if (!comm["ignore"]) {
         class_docs[name] = ({ 0, types,
                               parse_comment(current_comment) });
      }
   }
}
private void handle_inherit(mixed *bits) {
   int pos;
   string name;
   pos = member_array("inherit", bits);
   if (pos >= 0) {
      name = implode(map(bits[pos+1.. sizeof(bits)-2],
                         function(string str) {
                            if (str[0] == '\"') {
                               sscanf(str, "\"%s\"", str);
                               return str;
                            }
                            return "";
                         } ), "");
      inherits[name] = bits[0..pos-1];
   }
}
private void handle_function_definition(mixed *bits) {
   int pos;
   int end_pos;
   int new_pos;
   string name;
   string *type;
   mixed *args;
   mapping comm;
   pos = member_array("(", bits);
   if (pos > 0) {
      name = bits[pos-1];
      if (member_array(name, exclude_methods) == -1) {
         type = bits[0..pos-2];
         if (sizeof(type) == 0) {
            type = ({ "int" });
         }
         end_pos = member_array(")", bits, pos);
         args = ({ });
         if (end_pos > pos + 1) {
            pos++;
            while (member_array(",", bits, pos) != -1) {
               new_pos = member_array(",", bits, pos);
               args += ({ bits[pos..new_pos-2], bits[new_pos-1] });
               pos = new_pos + 1;
            }
            args += ({ bits[pos..end_pos -2], bits[end_pos-1] });
         }
         comm = parse_comment(current_comment);
         if (!comm["ignore"]) {
            if (member_array("private", type) != -1) {
               type -= ({ "private" });
               private_functions[name] = ({ type, args,
                                          comm });
            } else if (member_array("protected", type) != -1) {
               type -= ({ "protected" });
               protected_functions[name] = ({ type, args,
                                           comm });
            } else {
               type -= ({ "public" });
               public_functions[name] = ({ type, args,
                                           comm });
            }
         }
      }
      current_comment = 0;
   }
}
private string get_rest_of_line() {
   string value;
   int ch;
   int last_pos;
   value = "";
   ch = lookahead_character(1);
   while (ch == ' ' || ch == '\t') {
      pop_character(1);
      ch = lookahead_character(1);
   }
   do {
      last_pos = query_file_position();
      ch = next_character();
      if (ch == '\\') {
         ch = next_character();
         if (ch == '\r' && lookahead_character(1) == '\n') {
            ch = next_character();
         }
         ch = ' ';
      }
      if (last_pos != query_file_position()) {
         reset_eval_cost();
      }
      value += sprintf("%c", ch);
   } while (ch != '\n' && ch != '\r' && ch != EOF);
   return value;
}
private void handle_hash() {
   int i;
   string token;
   string name;
   string value;
   string *bits;
   string stuff;
   string inc_name;
   string curr_comm;
   mapping comm;
   token = get_word();
   switch (token) {
      case "define" :
      case "defin" :
         curr_comm = current_comment;
         value = get_rest_of_line();
         if (sscanf(value, "%s %s", name, value) == 2) {
            defines[name] = value;
            if (token == "define") {
               comm = parse_comment(curr_comm);
               if (!comm["ignore"]) {
                  define_docs[name] = comm;
               }
               current_comment = 0;
            }
         }
         break;
      case "include" :
         value = get_rest_of_line();
         if (value[0] == '\"') {
            bits = explode(file_name, "/");
            sscanf(value, "\"%s\"", name);
            stuff = read_file(implode(bits[0..<2], "/") +
                              "/" + name);
            if (stuff) {
               inc_name = "/" + implode(bits[0..<2], "/") +
                              "/" + name;
            }
         } else if (value[0] == '<') {
            sscanf(value, "<%s>", name);
         }
         if (name[0] == '/') {
            stuff = read_file(name);
            if (stuff) {
               inc_name = name;
            }
         }
         bits = MASTER_OB->define_include_dirs();
         while (!stuff && i < sizeof(bits)) {
            stuff = read_file(sprintf(bits[i], name));
            if (stuff) {
               stuff = replace_string(stuff, "
               stuff = replace_string(stuff, "class ", "clas ");
               stuff = replace_string(stuff, "#define ", "#defin ");
               inc_name = sprintf(bits[i], name);
            }
            i++;
         }
         if (inc_name) {
            inc_name = replace(inc_name, "
            if (inc_name[0] != '/') {
               inc_name = "/" + inc_name;
            }
         }
         if (stuff && !includes[inc_name]) {
            current_file = stuff + current_file[current_position..];
            current_position = 0;
            includes[inc_name] = unguarded( (: stat($(inc_name)) :) )[1];
         }
         break;
      default :
         skip_to_end_of_line();
         break;
   }
}
private void next_statement() {
   string token;
   string *bits;
   token = get_word();
   if (token[0] == '#') {
      return handle_hash();
   } else if (token == ";") {
      return ;
   } else if (token != "") {
      bits = get_statement(token);
      if (member_array("inherit", bits) != -1) {
         return handle_inherit(bits);
      } else if (bits[0] == "class" &&
                 member_array("(", bits) == -1) {
         return handle_class(bits);
      } else if (bits[sizeof(bits) - 1] == "{" &&
                 member_array("=", bits) == -1) {
         return handle_function_definition(bits);
      } else {
         return ;
      }
   }
}
void load_file() {
   unguarded((: restore_object(SAVE_DIR + replace_string(file_name, "/", ".")) :));
   if (!includes) {
      includes = ([ ]);
   }
   if (!class_docs) {
      class_docs = ([ ]);
   }
}
void save_file() {
   unguarded((: save_object(SAVE_DIR + replace_string(file_name, "/", ".")) :));
}
void parse_file(string name, function func, int only_load) {
   int curr_change;
   int my_change;
   string my_name;
   int reload;
   setup();
   file_name = name;
   load_file();
   if (!only_load) {
      if (sizeof(unguarded( (: stat($(name)) :) )) > 1) {
         curr_change = unguarded( (: stat($(name)) :) )[1];
         my_name = file_name(this_object());
         sscanf(my_name, "%s#%*s", my_name);
         my_name += ".c";
         my_change = unguarded( (: stat($(my_name)) :) )[1];
         reload = curr_change > last_changed;
         if (my_change > last_changed &&
             my_change > curr_change) {
            curr_change = my_change;
            reload = 1;
         }
         if (!reload) {
            foreach (my_name, my_change in includes) {
               if ( unguarded( (: stat($(my_name)) :) )[1] != my_change) {
                  reload = 1;
                  break;
               }
            }
         }
         if (reload) {
            setup();
            num_failed_tries = 0;
            file_name = name;
            changed = 1;
            last_changed = curr_change;
            current_file = read_file(name);
            current_position = 0;
            if (catch(do_parse_file(func))) {
               evaluate(func);
            }
         } else {
            if (num_failed_tries) {
               num_failed_tries = 0;
               save_file();
            }
            call_out( (: evaluate($1) :), 2, func);
         }
      } else {
         num_failed_tries++;
         save_file();
         call_out( (: evaluate($1) :), 2, func);
      }
   } else {
      call_out( (: evaluate($1) :), 2, func);
   }
}
private void do_parse_file(function func) {
   int num;
   if (unguarded( (: stat(file_name) :))[1] > last_changed) {
      return parse_file(file_name, func, 0);
   }
   num = 0;
   while (lookahead_character(1) != EOF && num < 2) {
      next_statement();
      num++;
   }
   if (lookahead_character(1) == EOF) {
      save_file();
      call_out((: evaluate($1) :), 2, func);
   } else {
      call_out((: do_parse_file($1) :), 2, func);
   }
}
mapping query_inherits() { return inherits; }
mapping query_private_functions() { return private_functions; }
mapping query_public_functions() { return public_functions; }
mapping query_protected_functions() { return protected_functions; }
mapping query_main_docs() {
   if (main_docs) {
      return main_docs;
   }
   return ([ ]);
}
string query_file_name() { return file_name; }
mapping query_defines() { return defines; }
int query_changed() { return changed; }
int query_num_failed_tries() { return num_failed_tries; }
string *query_includes() { return keys(includes); }
mapping query_define_docs() { return define_docs; }
mapping query_class_docs() { return class_docs; }
void dest_me() {
   destruct(this_object());
}