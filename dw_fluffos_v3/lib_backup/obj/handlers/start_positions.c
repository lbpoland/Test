#include <login_handler.h>
#define SAVE_FILE "/save/start_position_handler"
#define CHECKED_PROP "checked start positions"
private int _last_added;
private string * _buggy_starts;
void load_file() {
   if ( file_size( SAVE_FILE + ".o" ) > 0 ||
        file_size( SAVE_FILE + ".o.gz" ) > 0 )
   {
      unguarded( (: restore_object, SAVE_FILE :) );
   }
}
void save_file() {
   unguarded( (: save_object, SAVE_FILE :) );
}
void create() {
   _last_added = 0;
   _buggy_starts = ({ });
   load_file();
   if ( !_buggy_starts ) {
      _buggy_starts = ({ });
   }
}
int add_buggy_start( string fname ) {
   if ( !fname ) {
      return 0;
   }
   fname = lower_case( fname );
   if ( fname[ <2 .. ] == ".c" ) {
      fname = fname[ 0 .. <3 ];
   }
   if ( member_array( fname, _buggy_starts ) != -1 ) {
      return -1;
   }
   _buggy_starts += ({ fname });
   _last_added = time();
   save_file();
   return 1;
}
int delete_buggy_start( string fname ) {
   if ( !fname ) {
      return 0;
   }
   fname = lower_case( fname );
   if ( fname[ <2 .. ] == ".c" ) {
      fname = fname[ 0 .. <3 ];
   }
   if ( member_array( fname, _buggy_starts ) == -1 ) {
      return -1;
   }
   _buggy_starts -= ({ fname });
   save_file();
   return 1;
}
string * list_buggy_starts() {
   return copy( _buggy_starts );
}
void remove_buggy_starts( object player ) {
   string * starts;
   if ( !player ) {
      return;
   }
   starts = copy( player->query_starts() );
   for( int i = 0; i < sizeof( starts ); i += 2 ) {
      if ( member_array( starts[i], _buggy_starts ) != -1 ) {
         player->remove_start( starts[i] );
      }
   }
   player->add_property( CHECKED_PROP, time() );
}
void login_callback( string player, string type ) {
   object playerob;
   if ( !player ||
        !type ||
        type != LOGIN )
   {
      return;
   }
   player = lower_case( player );
   if ( !( playerob =  find_player( player ) ) ||
        ( playerob->query_property( CHECKED_PROP ) >= _last_added ) )
   {
      return;
   }
   remove_buggy_starts( playerob );
}
void dest_me() {
   destruct( this_object() );
}