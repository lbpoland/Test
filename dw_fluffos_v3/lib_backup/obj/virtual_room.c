inherit "/std/room";
#include <virtual_room.h>
nosave mixed  *reset_definitions;
nosave object *reset_objects;
void add_cloned_object( int flag, int delay, mixed clone_info,
                       string entry_mess ) {
   if ( functionp( clone_info ) )
      clone_info = bind( clone_info, this_object() );
   if ( !sizeof( reset_definitions ) )
      reset_definitions = ({ ({ flag, delay, clone_info, entry_mess }) });
   else
      reset_definitions += ({ ({ flag, delay, clone_info, entry_mess }) });
}
mixed *query_cloned_objects() {
   return reset_objects + ({ });
}
mixed *query_cloned_definitions() {
   return reset_definitions + ({ });
}
private object make_clone( mixed func ) {
   if ( stringp( func ) ) {
      return clone_object( func );
   } else if ( functionp( func ) ) {
      return evaluate( func );
   } else
      return 0;
}
protected void make_object( int i ) {
   switch ( reset_definitions[ i ][ FLAG ] ) {
    case REMOVABLE:
    case FIXED:
      reset_objects[ i ] = make_clone( reset_definitions[ i ][ CLONE ] );
      reset_objects[ i ]->move( this_object(),
            reset_definitions[ i ][ MESS ] );
      break;
    case UNIQUE:
      if ( !stringp( reset_definitions[ i ][ CLONE ] ) )
         return;
      reset_definitions[ i ][ CLONE ]->move( this_object(),
            reset_definitions[ i ][ MESS ] );
      reset_objects[ i ] = find_object( reset_definitions[ i ][ CLONE ] );
   }
}
void reset() {
   int i;
   if ( !sizeof( reset_definitions ) )
      return;
   if ( !sizeof( reset_objects ) )
      reset_objects = allocate( sizeof( reset_definitions ) );
   for ( i = sizeof( reset_definitions ); i--; ) {
      switch ( reset_definitions[ i ][ FLAG ] ) {
       case REMOVABLE:
         if ( !reset_objects[ i ] ||
             ( environment( reset_objects[ i ] ) != this_object() ) ) {
            if ( reset_definitions[ i ][ DELAY ] >= 0 ) {
               call_out( "make_object", reset_definitions[ i ][ DELAY ], i );
            } else {
               make_object( i );
            }
         }
         break;
       case FIXED:
       case UNIQUE:
         if ( !reset_objects[ i ] ) {
            if ( reset_definitions[ i ][ DELAY ] >= 0 ) {
               call_out( "make_object", reset_definitions[ i ][ DELAY ], i );
            } else {
               make_object( i );
            }
         }
      }
   }
}