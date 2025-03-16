#include <room.h>
#include <nroff.h>
mixed query_property(string name);
void add_property(string name, mixed value);
void add_help_file(string help_file) {
   string* help;
   help = query_property(ROOM_HELP_FILE_PROPERTY);
   if (help) {
      if (member_array(help_file, help) == -1) {
         help += ({ help_file });
      }
   } else {
      help = ({ help_file });
   }
   add_property(ROOM_HELP_FILE_PROPERTY, help);
}
void remove_help_file(string help_file) {
   string* help;
   help = query_property(ROOM_HELP_FILE_PROPERTY);
   if (help) {
      help -= ({ help_file });
      add_property(ROOM_HELP_FILE_PROPERTY, help);
   }
}
string query_help_files() {
   return query_property(ROOM_HELP_FILE_PROPERTY);
}
string query_help_file_directory() {
   return "/doc/unknown/";
}
private string nroff_file(string name, int html) {
   string nroff_fn;
   string str;
   if (name[0] != '/') {
      name = query_help_file_directory() + name;
   }
   nroff_fn = NROFF_DIR + replace(name, "/", ".");
   if (html) {
      str = NROFF_HAND->html_file(nroff_fn, 1);
   } else {
      str = NROFF_HAND->cat_file(nroff_fn, 1);
   }
   if (!str) {
      NROFF_HAND->create_nroff(name, nroff_fn);
      if (html) {
         str = NROFF_HAND->html_file(nroff_fn, 0);
      } else {
         str = NROFF_HAND->cat_file(nroff_fn, 0);
      }
   }
   return str;
}
mixed* help_function() {
   string* help;
   string bing;
   string* ret;
   help = query_property(ROOM_HELP_FILE_PROPERTY);
   if (sizeof(help)) {
      ret = ({ });
      foreach (bing in help) {
         ret += ({ ({ replace_string(bing, "_", " "),
                   (: nroff_file($(bing), 0) :) }) });
      }
      return ret;
   }
   return 0;
}
string help_string() {
   string *help;
   string str;
   string bing;
   help = query_property(ROOM_HELP_FILE_PROPERTY);
   if (sizeof(help)) {
      str = "";
      foreach (bing in help) {
        str += nroff_file(bing, 0);
      }
      return str;
   }
   return 0;
}