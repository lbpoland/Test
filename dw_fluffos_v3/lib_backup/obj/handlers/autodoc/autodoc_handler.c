#include <autodoc.h>
#define MAIN_FILE 0
#define INDEX_FILE 1
#define SAVE_FILE (SAVE_DIR "main_rubbish")
string *files;
int file_pos;
int something_changed;
int last_created_index;
nosave function *filters;
nosave int call_id;
nosave mapping summary_map;
nosave mixed *extra_indexes;
mapping help_map;
private void create_nroff_file(object ob, int type);
private void create_html_file(object ob, int type);
private void after_thingy(int no_index);
private void start_processing();
private void do_parse_next_file();
private void create_index();
private void add_to_index(object ob);
private void load();
private void save();
string *query_files();
int remove_file(string fname);
void create() {
   seteuid(getuid());
   filters = ({ (: create_nroff_file($1, $2) :),
                (: create_html_file($1, $2) :) });
   file_pos = 0;
   something_changed = 0;
   files = ({ });
   load();
   do_parse_next_file();
}
private void create_nroff_file(mixed ob, int type) {
   string fname;
   mixed *stuff;
   mixed *index_stuff;
   int i;
   if (type == MAIN_FILE) {
      fname = replace(ob->query_file_name(), "/", ".");
      if (fname[0] == '.') {
         fname = fname[1..];
      }
      rm(NROFF_DOC_DIR + fname);
      AUTODOC_NROFF->create_nroff_file(ob, NROFF_DOC_DIR + fname);
   } else if (type == INDEX_FILE) {
      index_stuff = ob;
      stuff = map(query_files(), function (string name) {
           string *bits;
           bits = explode(name, "/");
           return ({ bits[sizeof(bits)-1], name });
        } );
      stuff = unique_array(index_stuff + stuff, (: lower_case($1[0])[0] :));
      for (i = 0; i < sizeof(stuff); i++) {
         fname = NROFF_DOC_DIR + "index_" + lower_case(stuff[i][0][0][0..0]);
         AUTODOC_NROFF->create_nroff_index_file(stuff[i], fname);
      }
   }
}
private void create_html_file(mixed ob, int type) {
   string fname;
   mixed *stuff;
   mixed *index_stuff;
   int i;
   mapping chars;
   if (type == MAIN_FILE) {
      fname = replace(ob->query_file_name(), "/", ".");
      if (fname[0] == '.') {
         fname = fname[1..];
      }
      fname += ".html";
      rm(HTML_DOC_DIR + fname);
      AUTODOC_HTML->create_html_file(ob, HTML_DOC_DIR + fname);
   } else if (type == INDEX_FILE) {
      index_stuff = ob;
      stuff = map(query_files(), function (string name) {
           string *bits;
           bits = explode(name, "/");
           return ({ bits[sizeof(bits)-1], name, "", summary_map[name] });
        } );
      stuff = unique_array(index_stuff + stuff, (: lower_case($1[0])[0] :));
      chars = ([ ]);
      for (i = 0; i < sizeof(stuff); i++) {
         fname = "index_" + lower_case(stuff[i][0][0][0..0]) + ".html";
         rm(HTML_DOC_DIR + fname);
         AUTODOC_HTML->create_html_index_file(stuff[i], stuff[i][0][0][0..0],
                                       HTML_DOC_DIR + fname);
         reset_eval_cost();
         chars[capitalize(stuff[i][0][0][0..0])] =  fname;
      }
      fname = HTML_DOC_DIR;
      AUTODOC_HTML->create_main_index(chars, fname);
   }
}
private void after_thingy(int no_index) {
   int i;
   if (no_index) {
      printf("Finished recreating the documentation for %O\n",
              previous_object()->query_file_name(),
             previous_object());
   }
   if (previous_object()->query_changed()) {
      something_changed = 1;
   }
   if (previous_object()->query_num_failed_tries() > 1) {
      remove_file(files[file_pos - 1]);
   } else if (previous_object()->query_changed() || no_index) {
      for (i = 0; i < sizeof(filters); i++) {
         call_out((: evaluate($1, $2, $3) :), 0, filters[i],
                  previous_object(), MAIN_FILE);
      }
   }
   call_out((: $1->dest_me() :), 20, previous_object());
   save();
}
private void do_parse_next_file() {
   call_id = call_out((: start_processing() :), 60);
   if (file_pos >= sizeof(files)) {
      file_pos = 0;
   }
   new(AUTODOC_FILE)->parse_file(files[file_pos++], (: after_thingy(0) :));
}
private void start_processing() {
   if (sizeof(files) == 0) {
      return ;
   }
   if (last_created_index + SAVE_INDEX_DELAY < time()) {
      if (something_changed) {
         call_out( (: create_index() :), 2);
      }
      something_changed = 0;
      save();
   }
   call_id = call_out((: do_parse_next_file() :), 360);
}
private string query_short_args_def(mixed *args) {
   string ret;
   int i;
   ret = "";
   for (i = 0; i < sizeof(args); i += 2) {
      if (i != 0) {
         ret += ", ";
      }
      ret += implode(args[AUTO_ARGS_TYPE], " ");
   }
   return "(" + ret + ")";
}
private string *process_stuff(string name,
                              string fname,
                              string fn,
                              mapping docs) {
   string blue;
   int i;
   int end;
   mixed *ret;
   mapping fluff;
   if (name != "create" && name != "setup" && name != "init") {
      if (help_map[name]) {
         help_map[name] += ({ fn });
      } else {
         help_map[name] = ({ fn });
      }
   }
   if (docs[name]) {
      if (arrayp(docs[name])) {
         fluff = docs[name][AUTO_DOCS];
         ret =  ({ name, fname, query_short_args_def(docs[name][AUTO_ARGS]) });
      } else {
         ret = ({ name, fname, "" });
         fluff = docs[name];
      }
   } else {
      ret = ({ name, fname, "" });
      if (mapp(docs)) {
         fluff = docs;
      } else {
         fluff = ([ ]);
      }
   }
   if (fluff["main"]) {
      blue = implode(fluff["main"], "\n");
      end = strlen(blue);
      i = strsrch(blue, ".");
      if (i > 0) {
         end = i;
      }
      i = strsrch(blue, "!");
      if (i > 0 && i < end) {
         end = i;
      }
      i = strsrch(blue, "?");
      if (i > 0 && i < end) {
         end = i;
      }
      blue = blue[0..end];
   }
   ret += ({ blue });
   if (fluff["index"]) {
      foreach (blue in fluff["index"]) {
         blue = replace(blue, ({ " ", "", "\n", "" }));
         if (help_map[blue]) {
            help_map[blue] += ({ fn });
         } else {
            help_map[blue] = ({ fn });
         }
         extra_indexes += ({ ({ blue, fname, "", ret[AUTO_INDEX_SUMMARY] }) });
      }
   }
   return ret;
}
private void create_index() {
   int i;
   mixed *index_stuff;
   mixed *rabbit;
   string fname;
   string fn;
   string *bits;
   object parse;
   index_stuff = ({ });
   help_map = ([ ]);
   extra_indexes = ({ });
   summary_map = ([ ]);
   parse = clone_object(AUTODOC_FILE);
   for (i = 0; i < sizeof(files); i++) {
      parse->parse_file(files[i], 0, 1);
      fname = parse->query_file_name();
      if (fname) {
         fn = replace(fname, "/", ".");
         if (fn[0] == '.') {
            fn = fn[1..];
         }
         fn = NROFF_DOC_DIR + fn;
         bits = explode(fname[0..strlen(fname)-3], "/");
         rabbit = process_stuff(bits[sizeof(bits) - 1], "", fn,
                                parse->query_main_docs());
         if (rabbit[AUTO_INDEX_SUMMARY]) {
            summary_map[fname] = rabbit[AUTO_INDEX_SUMMARY];
         } else {
            map_delete(summary_map, fname);
         }
         index_stuff += map(keys(parse->query_public_functions()),
                            (: process_stuff($1, $(fname), $(fn),
                               $(parse)->query_public_functions()) :) );
         index_stuff += map(keys(parse->query_protected_functions()),
                            (: process_stuff($1, $(fname), $(fn),
                               $(parse)->query_protected_functions()) :) );
         index_stuff += map(keys(parse->query_class_docs()),
                            (: process_stuff($1, $(fname), $(fn),
                               $(parse)->query_class_docs()) :) );
         if (sscanf(fname, "%*s.h") == 1) {
            index_stuff += map(keys(parse->query_define_docs()),
                               (: process_stuff($1, $(fname), $(fn),
                               $(parse)->query_define_docs()) :) );
         }
      }
      reset_eval_cost();
   }
   index_stuff += extra_indexes;
   extra_indexes = ({ });
   for (i = 0; i < sizeof(filters); i++) {
      reset_eval_cost();
      catch(evaluate(filters[i], index_stuff, INDEX_FILE));
   }
   summary_map = ([ ]);
   last_created_index = time();
   save();
}
int recreate_documentation(string fname) {
   object ob;
   if (member_array(fname, files) != -1) {
      ob = clone_object(AUTODOC_FILE);
      ob->parse_file(fname, (: after_thingy(1) :));
      return 1;
   }
   return 0;
}
void recreate_indexes() {
   unguarded( (: create_index() :));
}
int add_file(string fname) {
   fname = "/" + implode(explode(fname, "/") - ({ "" }), "/");
   if (member_array(fname, files) == -1) {
      if (sizeof(unguarded( (: stat($(fname)) :) ))) {
         files += ({ fname });
         save();
         if (sizeof(files) == 1) {
            start_processing();
         } else {
            call_out((: recreate_documentation($1) :), random(60), fname);
         }
         return 1;
      }
   }
   return 0;
}
int remove_file(string fname) {
   string fn;
   string dfn;
   string *our_files;
   if (member_array(fname, files) != -1) {
      files -= ({ fname });
      file_pos = 0;
      fn = HTML_DOC_DIR + replace(fname, "/", ".");
      unguarded((: rm($(fn)) :));
      fn = NROFF_DOC_DIR + replace(fname, "/", ".");
      unguarded((: rm($(fn)) :));
      fn = NROFF_DOC_SINGLE + fname[0..<3] + "/";
      our_files = get_dir(fn);
      if (sizeof(our_files)) {
         foreach (dfn in our_files) {
            dfn =  fn + dfn;
            unguarded( (: rm($(dfn)) :) );
         }
      }
      if (file_size(fn[0..<2]) != -1) {
         unguarded((: rm($(fn[0..<2])) :));
      }
      save();
      if (!sizeof(files)) {
         remove_call_out(call_id);
      }
      return 1;
   }
   return 0;
}
private void load() {
   unguarded( (: restore_object( SAVE_FILE ) :) );
}
private void save() {
   unguarded( (: save_object( SAVE_FILE ) :) );
}
string *query_files() { return files; }
mapping query_help_map() { return help_map; }
string query_help_on(string file, string func) {
   if (file[0] == '/') {
      file = file[1..];
   }
   if (sscanf(file, "%*s.c") == 1) {
      file = file[0..<3];
   }
   file = NROFF_DOC_SINGLE + file + "/" + func;
   if (file_size(file) > 0) {
      return file;
   }
   return 0;
}
mapping query_summary_map() { return summary_map; }
int is_autodoc_file(string name) {
   return member_array(name, files) != -1;
}