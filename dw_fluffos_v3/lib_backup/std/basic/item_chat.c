#include <room.h>
private nosave int _off, _already_added;
private nosave mixed *_chats;
void check_chat();
mixed *query_chats() { return _chats; }
void init() {
  check_chat();
}
void item_chat( mixed *args ) {
  if ( !args || sizeof(args) < 3 || !sizeof(args[2]) ){
    write( "Incorrect args to item_chat.\n" );
    return;
  }
  args = args - ({ 0 });
  args[2] = map( args[2],
        (: replace( $1, ({ "$a_short$", this_object()->a_short(),
                           "$the_short$", this_object()->the_short(),
                           "$poss_short$", this_object()->poss_short() }) ) :) );
  _off = 0;
  _chats = args + ({ 0 });
  check_chat();
}
void chat_on(){
   _off = 0;
   check_chat();
}
void chat_off(){
   _off = 1;
}
void make_chat(){
  int saying;
  string stuff;
  object env, *targets;
  _already_added = 0;
  if( !(env = environment()) || _off )
    return;
  saying = random( sizeof(_chats[ 2 ]) );
  if( saying == _chats[ 3 ] )
    saying = ( saying + 1 ) % sizeof( _chats[ 2 ] );
  _chats[ 3 ] = saying;
  stuff = _chats[ 2 ][ saying ];
  if( env->query_is_room() ||
      ( interactive(env) && (env = environment(env)) && env->query_is_room() ) ){
    targets = filter( all_inventory(env), (: interactive($1) :) );
    if( !sizeof(targets) )
      return;
    if( stuff[0..0] == "#" )
      call_other( this_object(), stuff[ 1 .. ] );
    else
      tell_room( env, stuff + "\n" );
    _already_added = 1;
    ROOM_HANDLER->add_chatter( this_object(), _chats[ 0 ] +
                               random( _chats[ 1 ] - _chats[ 0 ] + 1 ) );
  }
}
void check_chat(){
  if( !_off && !_already_added && arrayp(_chats) && environment() ){
    if( interactive(environment()) ||
          ( environment(environment()) &&
            interactive(environment(environment()))
          )
       ){
           _already_added = 1;
           ROOM_HANDLER->add_chatter( this_object(),
           ( _chats[ 0 ] + random( _chats[ 1 ] - _chats[ 0 ] + 1 ) ) / 2 );
        }
  }
}
mapping query_dynamic_auto_load() {
   return ([ "_off"  : _off,
            "_chats" : _chats
          ]);
}
string fix_saved_chat( string chat ){
  string old_ob;
  if( !chat )
    return 0;
  sscanf( chat, "%*s$%*s_short:%s$%*s", old_ob );
  if( old_ob )
    chat = replace( chat, old_ob, file_name(this_object()) );
  return chat;
}
void init_dynamic_arg( mapping map ) {
  mixed info;
  if( !map )
    return;
  if( (info = map["_chats"]) && arrayp(info) && sizeof(info) > 2 ){
    info[2] = map( info[2], "fix_saved_chat", this_object() );
    item_chat( info );
  }
  if( !(_off = map["_off"]) )
    chat_on();
  else
    chat_off();
}