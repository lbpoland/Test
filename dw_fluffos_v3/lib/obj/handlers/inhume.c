#include <inhume.h>
void create() {
   string * prev;
   string msg;
   prev = map( previous_object(-1), (: file_name($1) :) );
   msg = sprintf( "%s: /obj/handlers/inhume loaded: previous_object(-1) = %O",
     ctime( time() ), prev );
   tell_creator( "shrike", msg );
   log_file( LOG, msg );
}