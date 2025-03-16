#include <room.h>
nosave int _off;
nosave object _room;
nosave mixed *_chats;
void set_chat_min_max( int min,int  max ) {
  if (_chats) {
    _chats[0]=min;
    _chats[1]=max;
  }
}
void setup_chatter( object my_room,  mixed *chat_args ) {
   _off = 1;
   _room = my_room;
   if( !arrayp( chat_args ) ) {
      chat_args = ({ chat_args });
   }
   _chats = chat_args + ({ 0 });
}
void dest_me() {
  destruct( this_object() );
}
void make_chat() {
   int saying;
   mixed stuff;
   if(!_room) {
     dest_me();
     return;
   }
   if ( !_chats || sizeof(_chats) < 3 || !sizeof(_chats[2]) ||
        !sizeof( filter( all_inventory( _room ), (: interactive($1) :),
         this_object() ) ) ) {
      _off = 1;
      return;
   }
   saying = random( sizeof( _chats[ 2 ] ) );
   if ( saying == _chats[ 3 ] ) {
     saying = ( saying + 1 ) % sizeof( _chats[ 2 ] );
   }
   _chats[ 3 ] = saying;
   stuff = _chats[ 2 ][ saying ];
   if (stringp(stuff)) {
      if ( stuff[ 0 ] == '#' ) {
         call_other( _room, stuff[ 1 .. 99 ] );
      } else {
         tell_room( _room, _chats[ 2 ][ saying ] +"\n" );
      }
   }
   if ( intp( stuff ) ) {
      map( filter( all_inventory( _room ), (: $1 && living( $1 )
         && $1->query_creator() :) ), (: tell_creator( $1, "Warning: "
         "room_chat array contains integer argument. Did you mix up "
         "the syntax with load_chat()'s?\n" ) :) );
   }
   ROOM_HANDLER->add_chatter( this_object(), _chats[ 0 ] +
         random( _chats[ 1 ] - _chats[ 0 ] + 1 ) );
}
void check_chat() {
   if ( !_off || !pointerp( _chats ) ) {
      return;
   }
   _off = 0;
   ROOM_HANDLER->add_chatter( this_object(), ( _chats[ 0 ] +
         random( _chats[ 1 ] - _chats[ 0 ] + 1 ) ) / 2 );
}
void add_room_chats( string *new_chats ) {
   if (sizeof(new_chats)) {
     if (sizeof(_chats[2])) {
        _chats[2] = _chats[2] + new_chats;
     } else {
        _chats[2]= new_chats;
     }
   }
}
void remove_room_chats( string *dead_chats ) {
   if (sizeof(_chats[2])) {
      _chats[2] = _chats[2] - dead_chats;
   }
   if (!sizeof(_chats[2])) {
      destruct(this_object());
   }
}
mixed *query_room_chats() { return _chats; }
int clean_up( int parent ) {
  if (parent)
    return 0;
  if (!_room || _room->query_chatter() != this_object())
    dest_me();
}