#include <door.h>
#include <room.h>
#include <parse_command.h>
#include <dirs.h>
#define BEVERB ({ " is ", " are " })
#define PRONOUN ({ "it", "them" })
#define CLOSED        2
#define CLOSED_LOCKED 3
inherit "/std/basic/enchant";
inherit "/std/basic/hide_invis";
inherit "/std/basic/property";
inherit "/std/basic/close_lock";
inherit "/std/basic/trap";
inherit "/std/basic/id_match";
private int how_many;
private int one_way;
private string _lock_owner;
private string shrt;
private string lng;
private string my_id;
private string other_id;
private string *name;
private string *adjs;
private string *plu;
private string dest;
private string _door_name;
private object key;
private object my_room;
void create() {
   hide_invis::create();
   property::create();
   close_lock::create();
   name = ({ "door" });
   lng = "It's just a door.\n";
   shrt = "door";
   adjs = ({ });
   plu = ({ });
   add_property( "determinate", "the " );
   set_unlocked();
}
int query_how_many() {
    return how_many;
}
void set_how_many( int number ) {
  if(number)
    add_property("group object", 1);
  else
    remove_property("group object");
  how_many = number;
}
int query_one_way() {
    return one_way;
}
void set_one_way( int number ) {
    one_way = number;
}
string query_short() {
    return shrt;
}
void set_short( string words ) {
   string *bits;
   shrt = words;
   bits = explode( words, " " );
   bits += implode( map( bits, (: explode( $1, "-" ) :) ), (: $1 + $2 :) );
   bits = uniq_array( bits );
   name += ({ bits[ sizeof( bits ) - 1 ] });
   adjs += bits[ 0 .. sizeof( bits ) - 2 ];
   plu += ({ pluralize( bits[ sizeof( bits ) - 1 ] ) });
}
string query_door_name() {
    return _door_name;
}
void set_door_name( string word ) {
    _door_name = word;
}
void set_lock_owner(string owner) {
    _lock_owner = owner;
}
mixed query_lock_owner() {
    return _lock_owner;
}
string query_long() { return lng; }
void set_long( string word ) {lng = word;}
string query_my_id() { return my_id; }
void set_my_id( string word ) { my_id = word; }
string query_other_id() { return other_id; }
void set_other_id( string word ) { other_id = word; }
string *query_name() { return name; }
string *query_adjs() { return adjs; }
string *query_plu() { return plu; }
string query_dest() { return dest; }
void set_dest( string word ) { dest = word; }
object query_my_room() { return my_room; }
void init() {
   add_command( "knock", "on <direct:object>" );
   close_lock::init();
}
string query_determinate() { return "the "; }
string short() { return query_short(); }
string a_short() { return "$a_short:"+ file_name( this_object() ) +"$"; }
string one_short() { return "$one_short:"+ file_name( this_object() ) +"$"; }
string poss_short() { return "$poss_short:"+ file_name( this_object() ) +"$"; }
string the_short() { return "$the_short:"+ file_name( this_object() ) +"$"; }
string pretty_short() { return query_short(); }
string query_plural() { return pluralize( query_short() ); }
string pretty_plural() { return pluralize( query_short() ); }
string long() {
  return lng + ( ( this_player()->query_see_octarine() ) ? enchant_string() :
                 "" ) + long_status();
}
int drop() { return 1; }
int get() { return 1; }
void setup_door( string word, object mine, string his, mixed *args,
                 string type) {
   string *bits;
   my_id = word;
   my_room = mine;
   dest = his;
   switch(type) {
   case "window":
     if(word != "window")
       shrt = word + " window";
     else
       shrt = word;
     lng = "It's just the " + shrt + ".\n";
     name = ({ shrt, "window" });
     plu = ({ "windows" });
     break;
   default:
     if ( word[ 0 .. 5 ] == "enter " ) {
       if(SHORTEN[word[6..100]])
         name += ({ SHORTEN[word[6..100]] });
       shrt = word[ 6 .. 100 ] +" door";
       lng = "It's just the " + shrt + ".\n";
       name += ({ shrt });
       if(!args[D_SECRET ])
         plu = ({ "doors" });
     } else {
       if(SHORTEN[word])
         name += ({ SHORTEN[word] });
       shrt = word +" door";
       lng = "It's just the " + shrt + ".\n";
       name += ({ shrt });
       if(!args[D_SECRET ])
         plu = ({ "doors" });
     }
     break;
   }
   bits = explode( word, " " );
   name += ({ bits[ sizeof( bits ) - 1 ] });
   adjs +=  bits;
   plu += ({ pluralize( bits[ sizeof( bits ) - 1 ] ) });
   (!args[ D_CLOSED ]) ? set_closed() : set_open();
   (args[ D_LOCKED ]) ? set_locked() : set_unlocked();
   set_key(args[ D_KEY ] );
   set_difficulty(args[ D_DIFFICULTY ] );
   if ( args[ D_SECRET ] )
      add_hide_invis( "secret", 0, 200, 0 );
   if(sizeof(args) >= D_TRANSPARENT && args[D_TRANSPARENT])
     set_transparent();
   set_door_name(args[D_NAME]);
}
void add_alias( string word ) {
   string *bits;
   bits = explode( word, " " );
   name += ({ bits[ sizeof( bits ) - 1 ] });
   adjs +=  bits[ 0 .. sizeof( bits ) - 2 ];
   plu += ({ pluralize( bits[ sizeof( bits ) - 1 ] ) });
}
int force_other() {
  string door_name, direc;
  if(!find_object(dest)) {
    if(!load_object(dest))
      return 0;
    dest->query_door( my_room, _door_name );
  }
  if(!other_id) {
    door_name = my_room->call_door(my_id, "query_door_name");
    direc = dest->query_door(my_room, door_name);
    my_room->modify_exit( my_id, ({ "other", direc }) );
  }
  if(!other_id)
    return 0;
  return 1;
}
int do_open() {
  if(!::do_open())
    return 0;
  if(!force_other() && !one_way) {
    set_closed();
    return 0;
  }
  if(((string)my_room->query_property( "location" ) == "outside") &&
     (member_array(find_object(ROOM_HANDLER), previous_object(-1)) == -1))
    ROOM_HANDLER->add_door( this_object() );
  if(!one_way && find_object(dest)) {
    dest->modify_exit(other_id, ({ "closed", 0 }));
    if(this_player())
      dest->tell_door(other_id, (string)this_player()->a_short() +
                      " opens the $D.\n", 0);
    else
      dest->tell_door(other_id, "Someone opens the $D.\n", 0);
  }
  return 1;
}
int do_close() {
  if(!::do_close())
    return 0;
  if(!force_other() && !one_way) {
    set_open();
    return 0;
  }
  if(!one_way && find_object(dest)) {
    if(query_autolock()) {
      dest->modify_exit( other_id, ({ "closed", 1, "locked", 1 }) );
      dest->tell_door( other_id, "Someone closes the $D which "
                       "lock$s as $p close$s.\n", 0 );
    } else {
      dest->modify_exit( other_id, ({ "closed", 1 }) );
      dest->tell_door( other_id, "Someone closes the $D.\n", 0 );
    }
  }
  return 1;
}
int do_lock(object *obs) {
  if(!::do_lock(obs))
    return 0;
  if(!force_other() && !one_way) {
    set_unlocked();
    return 0;
  }
  if(!one_way && find_object(dest)) {
    dest->modify_exit(other_id, ({ "locked", 1 }));
    dest->tell_door(other_id, "Someone locks the $D.\n", 0);
  }
  return 1;
}
int do_unlock(object *obs) {
  if(!::do_unlock(obs))
    return 0;
  if(!force_other() && !one_way) {
    set_locked();
    return 0;
  }
  if(!one_way && find_object(dest)) {
    dest->modify_exit(other_id, ({ "locked", 0 }));
    dest->tell_door(other_id, "Someone unlocks the $D.\n", 0);
  }
  return 1;
}
int do_knock() {
  if(this_player()->query_property("dead"))
    return 0;
  if ( !other_id && !one_way ) {
    ROOM_HANDLER->check_door( ({ my_room, my_id }) );
    if ( !other_id )
      return 0;
  }
  if ( one_way )
    return 1;
  if(query_transparent())
    dest->tell_door(other_id, this_player()->a_short() +
                    " knocks on the $D.\n", 0);
  else
    dest->tell_door( other_id, "Someone knocks on the $D.\n", 0 );
  event(find_object(dest), "door_knock", this_player(), other_id);
  return 1;
}
int pick_unlock(object thing) {
  if (stringp(_lock_owner)) {
     if (pk_check(_lock_owner, thing, 1)) {
        return 0;
     }
  }
  if(!::pick_unlock(thing)) {
    return 0;
  }
  if(!force_other() && !one_way ) {
    set_locked();
    return 0;
  }
  if(!one_way && find_object(dest)) {
    dest->modify_exit( other_id, ({ "locked", 0 }) );
    dest->tell_door( other_id, "Someone unlocks the $D.\n", 0 );
  }
  return 1;
}
int pick_lock( object thing ) {
  if (stringp(_lock_owner)) {
     if (pk_check(_lock_owner, thing, 1)) {
        return 0;
     }
  }
  if(!::pick_lock(thing))
    return 0;
  if(!force_other() && !one_way ) {
    set_unlocked();
    return 0;
  }
  if(!one_way && find_object(dest)) {
    dest->modify_exit( other_id, ({ "locked", 1 }) );
    dest->tell_door( other_id, "Someone locks the $D.\n", 0 );
  }
  return 1;
}
string *parse_command_id_list() {
  return (this_player() ? name + ({ this_player()->find_rel(my_id) }) : name);
}
string *parse_command_adjectiv_id_list() { return adjs; }
string *parse_command_plural_id_list() { return plu; }
object query_parse_id( mixed *arr ) {
   if (arr[P_THING] == 0) {
      return this_object();
   }
   if (arr[P_THING] < 0) {
      arr[P_THING]++;
      if (arr[P_THING] != 0) {
         return 0;
      }
      arr[P_THING] = -10321;
      return this_object();
   }
   arr[P_THING]--;
   if (arr[P_THING] != 0) {
      return this_object();
   }
   arr[P_THING] = -10101;
   return this_object();
}
mixed parse_match_object( string* input,
                          object viewer,
                          class obj_match_context context )
{
   if (input[<1] == "all") {
      return 0;
   }
   return ::parse_match_object(input, viewer, context);
}
void dest_me() {
  destruct( this_object() );
}
void dwep() { destruct( this_object() ); }
void go_away() { call_out("dest_me", 0); }
int move() { return 1; }
int moving_open( object thing ) {
  if(!::do_open())
    return 0;
  if(!force_other() && !one_way) {
    set_closed();
    return 0;
  }
  if(!one_way && find_object(dest)) {
    dest->modify_exit(other_id, ({ "closed", 0 }));
    dest->tell_door(other_id, (string)thing->a_short() + " opens the $D.\n", 0);
  }
  tell_object( thing, "You open the "+ shrt +".\n" );
  tell_room( my_room, (string)thing->the_short() +
             " opens the "+ shrt +".\n", thing );
  return 1;
}
int moving_close( object thing ) {
  if(!::do_close())
    return 0;
  if(!force_other() && !one_way) {
    set_open();
    return 0;
  }
  if(!one_way && find_object(dest))
    if(query_autolock()) {
      dest->modify_exit( other_id, ({ "closed", 1, "locked", 1 }) );
      dest->tell_door(other_id, (string)thing->the_short() +
                      " closes the $D which lock$s as $p close$s.\n", thing );
    } else {
      dest->modify_exit( other_id, ({ "closed", 1 }) );
      if ( thing->short() )
        dest->tell_door( other_id, capitalize( (string)thing->the_short() ) +
                         " closes the $D.\n", thing );
    }
  if(query_autolock()) {
    tell_object( thing, "You close the "+
                 (string)dest->call_door( other_id, "query_short" ) +
                 " which locks as it closes.\n" );
    tell_room( my_room, (string)thing->the_short() +
               " closes the "+ shrt +" which locks as it closes.\n", thing );
  } else {
    tell_object( thing, "You close the "+
                 (string)dest->call_door( other_id, "query_short" ) +".\n" );
    tell_room( my_room, (string)thing->the_short() +
               " closes the "+ shrt +".\n", thing );
  }
  return 1;
}
int moving_unlock(object thing) {
  if(!::do_unlock(all_inventory(thing)))
    return 0;
  if(!one_way && find_object(dest))
    dest->modify_exit(other_id, ({ "locked", 0 }));
  tell_object(thing, "You unlock the "+ shrt +".\n");
  if (thing->short())
    tell_room( my_room, capitalize( (string)thing->the_short() ) +
               " unlocks the "+ shrt +".\n", thing );
  return 1;
}
int moving_lock(object thing) {
  if(!::do_lock(all_inventory(thing)))
    return 0;
  if(!one_way && find_object(dest))
    dest->modify_exit(other_id, ({ "locked", 1 }));
  tell_object( thing, "You lock the "+
               (string)dest->call_door( other_id, "query_short" ) +".\n" );
  if (thing->short())
    dest->tell_door( other_id, capitalize( (string)thing->the_short() ) +
                     " locks the $D.\n", thing );
  return 1;
}
void tell_door(string words, object thing) {
  tell_room(my_room, replace( words, ({
    "$D", shrt, "$p", PRONOUN[how_many], "$s", ({ "s", "" })[how_many] })),
            ({ thing }));
}
mixed *stats() {
  return property::stats() + close_lock::stats() +
         ({ ({ "lock owner", _lock_owner }),
            ({ "other id", other_id }),
            ({ "dest", dest }) });
}
string long_status() {
   string str;
   if (!query_stuck()) {
      if(query_how_many() > 0)
      {
        str = "They are";
      }
      else
      {
        str = "It is";
      }
      switch (query_closed_locked_status()) {
         case CLOSED_LOCKED :
            return str + " closed and locked.\n";
         case CLOSED :
            return str + " closed.\n";
         default :
            return str + " open.\n";
      }
   } else {
      return "";
   }
}