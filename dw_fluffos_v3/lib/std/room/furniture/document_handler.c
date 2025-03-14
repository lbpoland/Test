inherit "/std/room/furniture/commercial";
inherit "/std/room/furniture/inherit/document_handler";
#include <room/document_handler.h>
void create() {
   document_handler::create();
   commercial::create();
   add_help_file("document_handler");
   set_shop_use_types( ({ "document_view",
                          "document_add",
                          "document_delete" }) );
}
string query_save_dir() {
   return commercial::query_save_dir() + "/" + query_commercial_id();
}
void load_me() {
   if (!query_commercial_id()) {
      setup_new_commercial_id();
   }
   if (unguarded( (: file_size(query_save_dir()) :) ) != -2) {
      unguarded( (: mkdir(query_save_dir()) :));
   }
}
void save_me() {
   environment()->event_save(this_object());
}
void init() {
   add_command("list", "documents [from] <direct:object>", (: do_list() :));
   add_command("view", "document <string'id'> [from] <direct:object>",
                (: do_display($4[0]) :));
   add_command("add", "documents {html|plain} called <string:quoted'title'> to <direct:object>",
               (: do_add_document($4[1], ($4[0] == "html"?DOCUMENT_HTML:DOCUMENT_PLAIN)) :));
   add_command("delete", "document <string'id'> [from] <direct:object>",
                (: do_delete_document($4[0]) :));
}
mapping query_dynamic_auto_load() {
   mapping map;
   map = commercial::query_dynamic_auto_load();
   document_handler::query_dynamic_auto_load(map);
   return map;
}
void init_dynamic_arg(mapping map) {
   document_handler::init_dynamic_arg(map);
   commercial::init_dynamic_arg(map);
}