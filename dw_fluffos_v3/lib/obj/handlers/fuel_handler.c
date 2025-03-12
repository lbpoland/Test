#include <fuel_handler.h>
object *burners;
void create() {
   seteuid( (string)"/secure/master"->
           creator_file( file_name( this_object() ) ) );
   burners = ({ });
   call_out( "consume_fuel", FUEL_TIME );
}
void add_burner( object thing ) {
   burners += ({ thing });
}
void consume_fuel() {
   burners -= ({ 0 });
   catch( burners->consume_fuel() );
   call_out( "consume_fuel", FUEL_TIME );
}
void remove_burner( object thing ) {
   burners -= ({ thing });
}
object *query_burners() {
   return burners - ({ 0 });
}
mixed *stats() {
  return ({
    ({ "burners" , sizeof( burners ) }),
    ({ "next event", find_call_out( "consume_fuel" ) }),
   });
}