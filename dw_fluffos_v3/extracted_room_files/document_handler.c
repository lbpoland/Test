# File: /lib/std/room/furniture/inherit/document_handler.c

#include <move_failures.h>
#include <nroff.h>
#include <room/newspaper.h>
#include <room/document_handler.h>
#define TAG "document__h"
class document {
   string title;
   string fname;
   string added_by;
   int time_added;
   int type;
}
private mapping _documents;
private int _next_doc_id;
string query_save_dir();
void save_me();
int is_open_for(string type, string name);
void add_auto_load_value(mapping map, string tag, string name, mixed value);
mixed query_auto_load_value(mapping map, string tag, string name);
void create() {
   _documents = ([ ]);
}
string query_document_file_name(string id) {
   if (_documents[id]) {
      return query_save_dir() + "/" + _documents[id]->fname;
   }
   return 0;
}
string query_document_data(string id) {
   string fname;
   fname = query_document_file_name(id);
   if (fname) {
      return unguarded( (: read_file($(fname)) :) );
   }
   return 0;
}
int is_document(string id) {
   return _documents[id] != 0;
}
string query_document_readable(string id) {
   string fname;
   string text;
   fname = query_document_file_name(id);
   if (fname) {
      switch (_documents[id]->type) {
      case DOCUMENT_PLAIN :
         text = unguarded( (: read_file($(fname)) :) );
         break;
      case DOCUMENT_HTML :
         text = unguarded( (: NROFF_HAND->cat_file($(fname) + ".nroff", 1) :) );
         if (!text) {
            text = unguarded( (: read_file( $(fname)) :) );
            if (text) {
               text = NEWSPAPER_HANDLER->convert_html(text);
               unguarded( (: write_file($(fname) + ".proc", $(text), 1) :) );
               if (unguarded( (: NROFF_HAND->create_nroff($(fname) + ".proc",
                           $(fname) + ".nroff")
:) )) {
                  text = unguarded( (: NROFF_HAND->cat_file($(fname) +
                                                            ".nroff") :) )
;
               } else {
                  text = "Unable to make nroff file.\n";
               }
            } else {
               text = "Unable to read the file, opps!\n";
            }
         }
         break;
      }
   }
   return text;
}
string query_document_html(string id) {
   string fname;
   string text;
   fname = query_document_file_name(id);
   if (fname) {
      switch (_documents[id]->type) {
      case DOCUMENT_PLAIN :
         text = unguarded( (: read_file($(fname)) :) );
         text = replace(fname, ({ "&", "&amp;", "<", "&lt;", ">", "&gt;",
                                  " ", "&nbsp;", "\n", "<br>" }) );
         break;
      case DOCUMENT_HTML :
         text = unguarded( (: read_file($(fname)) :) );
         if (!text) {
            text = unguarded( (: read_file( $(fname)) :) );
            if (text) {
               text = NEWSPAPER_HANDLER->convert_html(text);
               unguarded( (: write_file($(fname) + ".proc", $(text), 1) :) );
               if (unguarded( (: NROFF_HAND->create_nroff($(fname) + ".proc",
                           $(fname) + ".nroff")
:) )) {
                  text = unguarded( (: NROFF_HAND->cat_file($(fname) +
                                                            ".nroff") :) )
;
               } else {
                  text = "Unable to make nroff file.\n";
               }
            } else {
               text = "Unable to read the file, opps!\n";
            }
         }
         break;
      }
   }
   return text;
}
void update_document_text(string id, string text) {
   string fname;
   fname = query_document_file_name(id);
   if (fname) {
      unguarded( (: write_file($(fname), $(text), 1) :));
   }
}
void delete_document(string id) {
   string fname;
   fname = query_document_file_name(id);
   if (fname) {
      unguarded( (: rm($(fname) + ".proc") :));
      unguarded( (: rm($(fname) + ".nroff.o") :));
      unguarded( (: rm($(fname)) :));
      map_delete(_documents, id);
      save_me();
   }
}
string add_document(string title, string text, string person, int type) {
   class document bing;
   string id;
   id = _next_doc_id + "";
   bing = new(class document);
   bing->title = title;
   bing->added_by = person;
   bing->type = type;
   bing->time_added = time();
   bing->fname = id + ".txt";
   _next_doc_id++;
   _documents[id] = bing;
   update_document_text(id, text);
   save_me();
   return id;
}
int do_list() {
   string ret;
   class document info;
   string id;
   if (!is_open_for("document_view", this_player()->query_name())) {
      add_failed_mess("You cannot list documents on $I.\n",
                      ({ this_object() }));
      return 0;
   }
   if (!sizeof(_documents)) {
      add_failed_mess("Cannot find any documents to list on $I.\n",
                      ({ this_object() }));
      return 0;
   }
   ret = "";
   foreach (id, info in _documents) {
      ret += "$I$3=" + id + ") " + info->title + " [" + info->added_by +
             "] - " + ctime(info->time_added)[4..9] + " " +
             ctime(info->time_added)[<4..] + "\n";
   }
   write("$P$Documents$P$" + ret);
   add_succeeded_mess(({ "", "$N lists the documents in $I.\n" }),
                      ({ this_object() }));
   return 1;
}
int do_display(string id) {
   string ret;
   class document info;
   if (!is_open_for("document_view", this_player()->query_name())) {
      add_failed_mess("You cannot view documents on $I.\n",
                      ({ this_object() }));
      return 0;
   }
   ret = query_document_readable(id);
   if (!ret) {
      add_failed_mess("Cannot find the document " + id + " on $I.\n",
                      ({ this_object() }));
      return 0;
   }
   info = _documents[id];
   ret = "Document #" + id + " " + info->title + " [" + info->added_by +
             "] - " + ctime(info->time_added)[4..9] + " " +
             ctime(info->time_added)[<4..] + "\n" + ret;
   write("$P$Document " + id + "$P$" + ret);
   add_succeeded_mess(({ "", "$N reads a document from $I.\n" }),
                      ({ this_object() }));
   return 1;
}
int do_add_document(string title, int type) {
   if (!is_open_for("document_add", this_player()->query_name())) {
      add_failed_mess("You cannot add documents to $I.\n",
                      ({ this_object() }));
      return 0;
   }
   this_player()->do_edit("", "finish_edit", this_object(), 0,
                          ({ title, type }));
   return 1;
}
void finish_edit(string str, mixed* args) {
   string title;
   int type;
   title = args[0];
   type = args[1];
   if (!str || str == "") {
      write("Abandoning adding the document.\n");
      return ;
   }
   add_document(title, str, this_player()->query_cap_name(), type);
   write("Added the document into the collection.\n");
}
int do_delete_document(string id) {
   if (!is_open_for("document_delete", this_player()->query_name())) {
      add_failed_mess("You cannot delete documents from $I.\n",
                      ({ this_object() }));
      return 0;
   }
   if (!is_document(id)) {
      add_failed_mess("The document " + id + " does not exist in $I.\n",
                      ({ this_object() }));
      return 0;
   }
   delete_document(id);
   add_succeeded_mess("$N delete$s a document from $I.\n", ({ this_object() }));
   return 1;
}
mapping query_dynamic_auto_load(mapping map) {
   if (file_name(this_object()) != "/std/room/furniture/inherit/document_handler" && map) {
      add_auto_load_value(map, TAG, "documents", _documents);
      add_auto_load_value(map, TAG, "doc id", _next_doc_id);
      return map;
   }
}
void init_dynamic_arg(mapping map) {
   if (file_name(this_object()) != "/std/room/furniture/inherit/document_handler" && map) {
      _documents = query_auto_load_value(map, TAG, "documents");
      if (!_documents) {
         _documents = ([ ]);
      }
      _next_doc_id = query_auto_load_value(map, TAG, "doc id");
   }
}
void init_object() {
   add_command("list", "documents [from] <direct:object>", (: do_list() :));
   add_command("view", "document <string'id'> [from] <direct:object>",
                (: do_display($4[0]) :));
   add_command("add", "documents {html|plain} called <string:quoted'title'> to <direct:object>",
               (: do_add_document($4[1], ($4[0] == "html"?DOCUMENT_HTML:DOCUMENT_PLAIN)) :));
   add_command("delete", "document <string'id'> [from] <direct:object>",
                (: do_delete_document($4[0]) :));
}
void init_room() {
   add_command("list", "[documents]", (: do_list() :));
   add_command("view", "[document] <string'id'>",
                (: do_display($4[0]) :));
   add_command("add", "[document] {html|plain} called <string:quoted'title'>",
               (: do_add_document($4[1], ($4[0] == "html"?DOCUMENT_HTML:DOCUMENT_PLAIN)) :));
   add_command("delete", "[document] <string'id'>",
                (: do_delete_document($4[0]) :));
}