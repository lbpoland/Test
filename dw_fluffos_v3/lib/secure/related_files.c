#include <playerinfo.h>
#include <nomic_system.h>
void delete_related_files( string name, int mail, int refresh_type ) {
   string *files;
   string area;
   string dir;
   if (previous_object() != find_object("/secure/bulk_delete") &&
       previous_object() != find_object("/secure/delete_clear") &&
       previous_object() != find_object("/obj/handlers/refresh")) {
     if (!master()->high_programmer(previous_object(-1)) &&
         ((string)previous_object()->query_name() != name)) {
       tell_object(find_player("ceres"), "Not doing erasing. %O\n",
                   previous_object());
       unguarded( (: write_file, "/log/CHEAT", ctime( time() ) +
                   ": illegal attempt to delete related files using "+
                   "/secure/related_files\nTrace: "+ back_trace() :) );
       return;
     }
   }
   unguarded( (: rm, "/save/artifacts/"+ name :) );
   unguarded( (: rm, "/save/bank_accounts/"+name[0..0] + "/" + name + ".o" :) );
   unguarded( (: rm, "/save/cmr_library/"+ name +".o" :) );
   catch("/obj/handlers/library"->restart(name));
   unguarded( (: rm, "/save/library/"+ name[0..0] + "/" + name + ".o" :) );
   unguarded( (: rm, "/save/philosophies/"+ name[0..0] + "/"+ name + ".o" :) );
   foreach(dir in get_dir("/save/vaults