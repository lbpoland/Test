#include <room.h>
nosave int off;
nosave object room;
nosave mixed *chats;
void set_chat_min_max( int min,int  max ) {
  if (chats) {
    chats[0]=min;
    chats[1]=max;
  }
}
void setup_chatter( object my_room,  mixed *chat_args ) {
   off = 1;
   room = my_room;
   if (sizeof(chats)) chats += chat_args + ({0,0});
   else chats = chat_args + ({0,0});
}
void dest_me() {
  destruct( this_object() );
}
int query_multichatter() { return 1; }
int check_interactive( object thing ) { return interactive( thing ); }
void make_chat() {
  int saying;
  string stuff;
  int set,nextt,t;
  if (!sizeof( filter_array( all_inventory( room ), "check_interactive",
        this_object() ) ) ) {
    off = 1;
    return;
  }
  nextt=2147483647;
  t=time();
  for (set=0;set<sizeof(chats);set+=5) {
    if (sizeof(chats[set+2])) {
      if (t>=chats[set+4]) {
        saying = random( sizeof( chats[ set+2 ] ) );
        if ( saying == chats[ set+3 ] )
        saying = ( saying + 1 ) % sizeof( chats[ set+2 ] );
        chats[ set+3 ] = saying;
        stuff = chats[ set+2 ][ saying ];
        if ( stuff[ 0 ] == '#' )
          call_other( room, stuff[ 1 .. 99 ] );
        else
          tell_room( room, chats[ set+2 ][ saying ] +"\n" );
        chats[ set+4 ]=time()+chats[ set ]
            +random(chats[ set+1 ] - chats[ set ] + 1)-4;
      }
      if (chats[ set+4 ]<nextt) nextt=chats[ set+4 ];
    }
  }
  if (nextt!=2147483647) {
    if ((nextt+=4-t)<5) nextt=5;
    ROOM_HANDLER->add_chatter( this_object(), nextt );
  }
}
void check_chat() {
  int set,t,nextt;
  if ( !off || !pointerp( chats ) )
      return;
  off = 0;
  t=time();
  nextt=2147483647;
  for (set=0; set<sizeof(chats); set+=5) {
    if (t>=chats[set+4]+chats[set]) chats[set+4]=t+random(chats[set+1]);
    if (chats[set+4]<nextt) nextt=chats[set+4];
  }
  if ((nextt+=4-t)<5) nextt=5;
  ROOM_HANDLER->add_chatter( this_object(), nextt );
}
void add_room_chats( string *new_chats ) {
   if (sizeof(new_chats)) {
     if (sizeof(chats[2])) chats[2] = chats[2] + new_chats;
     else chats[2]= new_chats;
   }
}
void remove_room_chats( string *dead_chats ) {
  int set;
  mixed *new_chats;
  new_chats=({ });
  for (set=0;set<sizeof(chats);set+=5) {
    if (sizeof(chats[set+2])) chats[set+2] = chats[set+2] - dead_chats;
    if (set==0 || sizeof(chats[set+2]))
       new_chats=new_chats+chats[(set)..(set+4)];
  }
  chats=new_chats;
}
mixed *query_room_chats() { return chats; }
int clean_up( int parent ) {
  if (parent) {
    return 0;
  }
  if (!room) dest_me();
}