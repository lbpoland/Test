#include <armoury.h>
#include <dirs.h>
#include <door.h>
#include <move_failures.h>
#include <room.h>
#include <position.h>
#include <situations.h>
#include <weather.h>
#include <nroff.h>
inherit "/std/basic/cute_look";
inherit "/std/basic/desc";
inherit "/std/basic/extra_look";
inherit "/std/basic/light";
inherit "/std/basic/property";
inherit "/std/basic/export_inventory";
inherit "/std/basic/help_files";
inherit "/std/basic/effects";
nosave int do_setup;
nosave int *co_ord;
nosave int co_ord_calculated;
nosave string long_exit;
nosave string long_exit_mxp;
nosave string short_exit;
nosave string theft_handler;
nosave string *aliases;
nosave string *_exits;
nosave object item;
private nosave object chatter;
nosave object sitchanger;
nosave object linker;
nosave object terrain;
nosave object wall;
nosave object *hidden_objects;
private nosave object* _use_internal_objects;
nosave mapping door_control;
nosave mixed *dest_other;
nosave int enchant_time;
nosave int background_enchant;
nosave float dynamic_enchant;
private nosave int last_visited;
private nosave string *variablelongs;
private nosave mixed variablechats;
private nosave mixed variableitems;
private nosave int is_day = -1;
varargs int add_item( mixed shorts, mixed desc, int no_plural );
int remove_item( string word );
private void setup_room_chat( );
void set_not_replaceable(int replace);
int query_not_replaceable();
void set_night_long( string str );
protected void create() {
   object *npcs;
   object virt_room;
   string *inhs;
   desc::create();
   extra_look::create();
   property::create();
   export_inventory::create();
   light::create();
   effects::create();
   set_can_export_inventory();
   set_ignore_livings_in_inventory( 0 );
   aliases = ({ });
   _exits = ({ });
   hidden_objects = ({ });
   _use_internal_objects = ({ });
   door_control = ([ ]);
   dest_other = ({ });
   seteuid( (string)"/secure/master"->creator_file( file_name(
           this_object() ) ) );
   add_property( "location", "inside" );
   add_property( "here", "on the floor" );
   if ( !do_setup ) {
      this_object()->setup();
      this_object()->reset();
   }
   if ( find_object( "/obj/handlers/map" ) ) {
      catch( "/obj/handlers/map"->check_map( file_name( this_object() ) ) );
   }
   if( (virt_room = find_object("/room/virtual") ) ){
     npcs = ({}) + all_inventory(virt_room);
     catch(npcs->real_room(file_name()));
   }
   inhs = inherit_list(this_object());
   if (sizeof(inhs) == 1) {
      if (replaceable(this_object(), ({ "setup" }))) {
         call_out(function(string fname) {
           if (!query_not_replaceable()) {
               catch(replace_program(fname));
           }
         }, 0, inhs[0]);
      }
   }
}
int query_is_room()
{
  return 1;
}
int query_enchant() {
  int enchant_level =  to_int( floor( 0.5 + dynamic_enchant *
                        exp( -0.693 *
                             ( time() - enchant_time ) /
                             ENCHANT_HALF)) +
                 background_enchant );
  if ( enchant_level > 5000 ) {
    return 5000;
  }
  return enchant_level;
}
int set_enchant(int number) {
  if (number < 0) {
    number = 0;
  }
  if (previous_object()==this_object()) {
    background_enchant = (float) number;
    dynamic_enchant = 0.0;
    enchant_time = time();
  } else {
    dynamic_enchant = number - background_enchant;
    enchant_time=time();
  }
  return number;
}
int add_enchant( int number ) {
  dynamic_enchant = dynamic_enchant * exp( -0.693 *
                                           ( time() - enchant_time ) /
                                           ENCHANT_HALF ) + number;
  enchant_time = time();
  return floor( 0.5 + dynamic_enchant ) + background_enchant;
}
void set_background_enchant( int number ) {
  background_enchant = number;
}
void set_dynamic_enchant( float number ) {
  dynamic_enchant = number;
  enchant_time = time();
}
int query_background_enchant() {
  return background_enchant;
}
float query_dynamic_enchant() {
  dynamic_enchant = dynamic_enchant * exp( -0.693 *
                                           ( time() - enchant_time ) /
                                           ENCHANT_HALF );
  enchant_time = time();
  return dynamic_enchant;
}
int *query_co_ord() {
  if ( pointerp( co_ord ) ) {
    return copy(co_ord);
  }
  return 0;
}
void set_co_ord( int *new_co_ord ) {
  if ( !pointerp( new_co_ord ) ) {
    write( "Warning: Co-ordinate must be an array.\n" );
    return;
  }
  if ( sizeof( new_co_ord ) != 3 ) {
      write( "Warning: The co-ordinate must have three elements.\n" );
      return;
  }
  co_ord = new_co_ord;
  if ( previous_object() == this_object() ) {
    co_ord_calculated = 0;
  } else {
    co_ord_calculated = 1;
  }
}
void flush_co_ord() {
    co_ord = 0;
    co_ord_calculated = 0;
}
int query_co_ord_calculated() { return co_ord_calculated; }
string query_long_exit() { return long_exit; }
string query_long_exit_mxp() { return long_exit_mxp; }
void calc_long_exit() {
  int i, add;
  string *words;
  mixed tmp;
  words = ({ });
  for ( i = 0; i < sizeof( dest_other ); i += 2 ) {
    tmp = dest_other[ i + 1 ][ ROOM_OBV ];
    if ( !tmp ) {
      continue;
    }
    if ( intp( tmp ) && tmp ) {
      add = 1;
    }
    if ( stringp( tmp ) ) {
      add = (int)call_other( this_object(), tmp, dest_other[ i ] );
    }
    if ( pointerp( tmp ) ) {
      add = (int)call_other( tmp[ 0 ], tmp[ 1 ], dest_other[ i ] );
    }
    if ( add ) {
      if(dest_other[i+1][ROOM_REL]) {
        words += ({ "$R$-"+ dest_other[ i ] +"$R$" });
      } else {
        words += ({ dest_other[i] });
      }
    }
  }
  switch ( sizeof( words ) ) {
  case 0 :
    long_exit = "There are no obvious exits.";
    long_exit_mxp = mxp_expire("Exits") + "There are no obvious exits.";
    break;
  case 1 :
    long_exit = "There is one obvious exit: "+ words[ 0 ] + ".";
    long_exit_mxp = mxp_expire("Exits") +
                    "There is one obvious exit: "+ mxp_tag("Exit", words[ 0 ], 1) + ".";
    break;
  default :
    long_exit = "There are "+ query_num( sizeof( words ), 0 ) +
      " obvious exits: "+ query_multiple_short( words ) +
      ".";
    long_exit_mxp = mxp_expire("Exits") +
      "There are "+ query_num( sizeof( words ), 0 ) +
      " obvious exits: "+ query_multiple_short( map(words, (: mxp_tag("Exit", $1, 1) :) ) ) +
      ".";
  }
}
string query_theft_handler() { return theft_handler; }
void set_theft_handler( string word ) { theft_handler = word; }
string *query_aliases() { return copy( aliases ); }
void add_alias( mixed names, string word ) {
  string name;
  if ( !aliases ) {
    aliases = ({ });
  }
  if ( pointerp( names ) ) {
    foreach ( name in names ) {
      add_alias( name, word );
    }
    return;
  }
  aliases += ({ word, names });
  if ( find_call_out( "calc_exits" ) == -1 ) {
    call_out( "calc_exits", 1 );
  }
}
void remove_alias( mixed names, string word ) {
  int i;
  string name;
  if ( !aliases ) {
    return;
  }
  if ( pointerp( names ) ) {
    foreach ( name in names ) {
      remove_alias( name, word );
    }
    return;
  }
  for ( i = sizeof( aliases ) - 2; i >= -1; i -= 2 ) {
    if ( ( aliases[ i ] == word ) && ( aliases[ i + 1 ] == names ) ) {
      aliases = delete( aliases, i, 2 );
    }
  }
}
string *query_exits() { return copy(_exits); }
void reset_exits() { _exits = ({ }); }
object query_item() { return item; }
object query_chatter() { return chatter; }
object query_situation_changer() { return sitchanger; }
object query_linker() { return linker; }
object query_terrain() { return terrain; }
object query_wall() { return wall; }
object *query_hidden_objects() { return hidden_objects + ({ }); }
int add_hidden_object( object thing ) {
  if ( !hidden_objects ) {
    hidden_objects = ({ });
  }
  if ( member_array( thing, hidden_objects ) != -1 ) {
    return 0;
  }
  hidden_objects += ({ thing });
  return 1;
}
int remove_hidden_object( object thing ) {
  int i;
  i = member_array( thing, hidden_objects );
  if ( i == -1 ) {
    return 0;
  }
  hidden_objects = hidden_objects[0..i - 1] + hidden_objects[i + 1..];
  return 1;
}
void add_use_internal_object(object thing) {
   _use_internal_objects |= ({ thing });
}
void remove_use_internal_object(object thing) {
   _use_internal_objects -= ({ thing });
}
object* query_use_internal_objects() {
   return _use_internal_objects;
}
varargs mixed query_door_control( string direc, string name ) {
   if ( !stringp( direc ) ) {
      return copy( door_control );
   }
   if (name) {
      return door_control[ direc + " " + name ];
   }
   return door_control[ direc ];
}
varargs mixed *query_dest_other( string direc ) {
  int i;
  if ( !stringp( direc ) ) {
    return copy( dest_other );
  }
  i = member_array( direc, dest_other );
  if ( i == -1 ) {
    return 0;
  }
  return copy( dest_other[ i + 1 ] );
}
varargs string *query_dest_dir( object thing ) {
  int i;
  string *ret;
  ret = ({ });
  for ( i = sizeof( dest_other ) - 2; i > -1; i -= 2 ) {
    if ( !dest_other[ i + 1 ][ ROOM_REL ] || !objectp( thing ) ) {
      ret += ({ dest_other[ i ], dest_other[ i + 1 ][ ROOM_DEST ] });
    } else {
      ret += ({ (string)thing->find_rel( dest_other[ i ] ),
                  dest_other[ i + 1 ][ ROOM_DEST ] });
    }
  }
  return ret;
}
varargs string *query_direc( object thing ) {
  int i;
  string *ret;
  ret = ({ });
  for ( i = sizeof( dest_other ) - 2; i > -1; i -= 2 ) {
    if ( !dest_other[ i + 1 ][ ROOM_REL ] || !objectp( thing ) ) {
      ret += ({ dest_other[ i ] });
    } else {
      ret += ({ (string)thing->find_rel( dest_other[ i ] ) });
    }
  }
  return ret;
}
string query_destination( string exit ) {
   int i;
   i = member_array( exit, dest_other );
   if ( ( i < 0 ) && objectp( this_player() ) )
      i = member_array( (string)this_player()->reorient_rel( exit ),
            dest_other );
   if ( i < 0 )
      return ROOM_VOID;
   return dest_other[ i + 1 ][ ROOM_DEST ];
}
int test_add( object thing, int flag ) { return 1; }
int test_remove( object thing, int flag, mixed dest ) { return 1; }
int add_weight( int number ) { return 1; }
int query_no_writing() { return 1; }
int query_decay() { return 10; }
int query_day() { return is_day; }
int attack_speed() { return 15; }
string query_dark_mess() {
  mixed dark_mess;
  if ( !stringp( dark_mess = query_property( "dark mess" ) ) ) {
    return "It's dark here, isn't it?";
  }
  return dark_mess;
}
void set_dark_mess( string word ) {
    add_property( "dark mess", word );
}
string query_bright_mess() {
  mixed bright_mess;
  if ( !stringp( bright_mess = query_property( "bright mess" ) ) ) {
    return "It's too bright to see anything!";
  }
  return bright_mess;
}
void set_bright_mess( string word ) { add_property( "bright mess", word ); }
mixed query_room_size() {
   mixed room_size;
   room_size = query_property( "room size" );
   if ( !room_size ) {
      return 10;
   }
   return room_size;
}
int *query_room_size_array() {
   mixed room_size;
   room_size = query_room_size();
   if ( pointerp( room_size ) ) {
      return room_size;
   }
   return ({ room_size, room_size, room_size });
}
void set_room_size( mixed number ) {
   if ( intp( number ) ) {
      add_property( "room size", number );
      return;
   }
   if ( pointerp( number ) ) {
      if ( sizeof( number ) == 3 ) {
         add_property( "room size", number );
         return;
      }
   }
   write( "Room size must be an integer or an array of three integers.\n" );
}
int id( string word ) { return 0; }
string expand_alias( string word ) {
   int i;
   if ( !aliases || !sizeof( aliases ) ) {
      return word;
   }
   i = member_array( word, aliases );
   if ( i == -1 ) {
      return word;
   }
   if ( i % 2 ) {
      return aliases[ i - 1 ];
   }
   return word;
}
string calc_short_exit_string() {
   int i, add;
   string *words;
   int pos;
   string tmp_dir;
   mixed tmp;
   words = ({ });
   for ( i = 0; i < sizeof( dest_other ); i += 2 ) {
      tmp = dest_other[ i + 1 ][ ROOM_OBV ];
      if ( !tmp ) {
         continue;
      }
      if ( intp( tmp ) && tmp ) {
         add = 1;
      }
      if ( stringp( tmp ) ) {
         add = (int)call_other( this_object(), tmp, dest_other[ i ] );
      }
      if ( pointerp( tmp ) ) {
         add = (int)call_other( tmp[ 0 ], tmp[ 1 ], dest_other[ i ] );
      }
      if ( add ) {
         if ( tmp = SHORTEN[ dest_other[ i ] ] ) {
            if (dest_other[i+1][ROOM_REL]) {
               words += ({ "$r$-"+tmp+"$r$" });
            } else {
               words += ({ tmp });
            }
         } else {
            if (dest_other[i+1][ROOM_REL]) {
               words += ({ "$r$-"+dest_other[ i ]+"$r$" });
            } else {
               pos = strsrch(dest_other[i], " ");
               if (pos != -1) {
                  tmp_dir = dest_other[i][pos + 1..];
                  tmp = SHORTEN[tmp_dir];
                  if (tmp) {
                     tmp_dir = tmp;
                  }
                  words += ({ dest_other[i][0..pos] + tmp_dir });
               } else {
                  words += ({ dest_other[i] });
               }
            }
         }
      }
   }
   if(!sizeof(words)) {
     return " [none]";
   }
   return " ["+ implode( words, "," ) +"]";
}
string query_short_exit_string() {
   string tmp;
   if(short_exit) {
      return this_player()->colour_event("exits", "%^GREEN%^") +
     short_exit + "%^RESET%^";
   }
   tmp = calc_short_exit_string();
   if (!query_property("no exit cache")) {
      short_exit = tmp;
   }
   return this_player()->colour_event("exits", "%^GREEN%^") +
     tmp + "%^RESET%^";
}
string enchant_string() {
   string words;
   words = (string)this_object()->query_property( "octarine_mess" );
   if ( words ) {
      return words +"\n";
   }
   switch ( query_enchant() ) {
      case 0 .. 49 :
         return "";
      case 50 .. 149 :
         return "There is the residual taste of magic in this place.\n";
      case 150 .. 299 :
         return "This place has seen some use of magic.\n";
      case 300 .. 499 :
         return "A considerable amount of magic has been used here.\n";
      case 500 .. 749 :
         return "A very large quantity of magic has been manipulated here.\n";
      case 750 .. 1000 :
         return "You can feel the Dungeon Dimensions trying to push in.\n";
      case 1001 .. 1500 :
         return "Little sparks flash in from the Dungeon Dimensions.\n";
      case 1501 .. 2000 :
         return "Apparations of things with lots of tentacles seem to be "
                "on the edge of your vision.\n";
      default :
         return "So much magic has been expended here that the area is in "+
               "danger of dumping itself into the Dungeon Dimensions.\n";
   }
}
string long( string word, int dark ) {
   string ret;
   if ( !long_exit ) {
      calc_long_exit();
   }
   if ( dark ) {
      if ( dark < 0 ) {
         ret = mxp_tag("RoomDesc", this_object()->query_dark_mess(), this_player()) +"\n";
      } else {
         ret = mxp_tag("RoomDesc", this_object()->query_bright_mess(), this_player()) +"\n";
      }
      if ( query_property( "location" ) == "outside" ) {
         ret += "$weather$";
      }
      if ( ( dark == 1 ) || ( dark == -1 ) ) {
         ret = "$C$"+ mxp_tag("RoomName", a_short(), this_player()) +".  "+ ret +
           this_player()->colour_event("exits", "%^GREEN%^") +
           mxp_tag("RoomExits", mxp_choice(long_exit, long_exit_mxp, this_player()), this_player())
           +"%^RESET%^\n";
         if ( query_contents( "" ) != "" ) {
            ret += this_player()->colour_event("inventory", "") + "Some objects you can't make out are here.%^RESET%^\n";
         }
      }
   } else {
      if ( query_property( "location" ) == "outside" ) {
         ret = "$long$";
      } else {
         ret = query_long();
      }
      if(!ret) {
         ret = "Erk, this room seems to be broken.\n";
      }
      word = calc_extra_look();
      if ( stringp( word ) && ( word != "" ) ) {
         ret += word;
      }
      if ( this_player()->query_see_octarine() ) {
         ret += enchant_string();
      }
      if ( query_property( "location" ) == "outside" ) {
         ret += "$weather$";
      }
      ret = mxp_tag("RoomDesc", ret, this_player());
      ret += this_player()->colour_event("exits", "%^GREEN%^") +
         mxp_tag("RoomExits", mxp_choice(long_exit, long_exit_mxp, this_player()), this_player())
         +"%^RESET%^\n"+ query_contents( "" );
   }
   if ( query_property( "no exit cache" ) )  {
      long_exit = 0;
   }
   return mxp_secure(this_player()) + ret + mxp_open(this_player());
}
string pretty_short( object thing ) {
   int dark;
   if ( thing ) {
      dark = (int)thing->check_dark( (int)this_object()->query_light() );
   }
   return ::short( dark );
}
int query_visibility() {
   return 100;
}
int can_use_for_co_ords(string other) {
   return 1;
}
void calc_co_ord() {
  int i, j, k, shift, *delta, *other_co_ord;
  string other;
  mixed* std_orders = STD_ORDERS;
  for ( i = sizeof( dest_other ) - 2; ( i > -1 ) && !co_ord; i -= 2 ) {
    other = dest_other[ i + 1 ][ ROOM_DEST ];
    if ( !find_object( other ) ) {
       continue;
    }
    if ( other->query_do_not_use_coords()) {
       continue;
    }
    if (stringp(other) && other[0..2] == "/w/") {
       continue;
    }
    other_co_ord = (int *)other->query_co_ord();
    if ( !other_co_ord ) {
      continue;
    }
    if (!other_co_ord[0] && !other_co_ord[1] && !other_co_ord[2]) {
      continue;
    }
    if (!can_use_for_co_ords(other)) {
       continue;
    }
    j = -1;
    if ( delta = dest_other[ i + 1 ][ ROOM_DELTA ] ) {
      co_ord = copy( other_co_ord );
      if (pointerp(delta)) {
        k = 3;
        while ( k-- ) {
          co_ord[ k ] -= delta[ k ];
        }
        continue;
      } else {
        j = member_array(delta, std_orders);
      }
    }
    if (j == -1) {
      j = member_array( dest_other[ i ], std_orders );
      if ( j == -1 ) {
        continue;
      }
    }
    co_ord = copy( other_co_ord );
    delta = query_room_size_array() + (int *)other->query_room_size_array();
    for ( k = 0; k < 3; k++ ) {
      co_ord[ k ] += std_orders[ j + 1 ][ k ] *
        ( delta[ k ] + delta[ k + 3 ] );
    }
    if ( ( j < 16 ) && dest_other[ i + 1 ][ ROOM_GRADE ] ) {
      switch ( j ) {
      case 0 .. 1 :
        shift = delta[ 0 ] + delta[ 3 ];
        break;
      case 2 .. 3 :
        shift = delta[ 1 ] + delta[ 4 ];
        break;
      default :
        shift = delta[ 0 ] + delta[ 1 ] + delta[ 3 ] + delta[ 4 ];
      }
      co_ord[ 2 ] -= ( dest_other[ i + 1 ][ ROOM_GRADE ] * shift ) / 100;
      }
    co_ord_calculated = 1;
  }
}
void calc_exits() {
   int i, j;
   string exit, word, *tmp_al;
   _exits = ({ });
   for ( i = sizeof( dest_other ) - 2; i > -1; i -= 2 ) {
      exit = dest_other[ i ];
      if ( member_array( exit, _exits ) == -1 ) {
         _exits += ({ exit });
         word = SHORTEN[ exit ];
         if ( stringp( word ) ) {
            _exits += ({ word });
         }
      }
      tmp_al = aliases;
      j = member_array( exit, tmp_al );
      while ( j != -1 ) {
         if ( j % 2 ) {
            j--;
         } else {
            word = tmp_al[ j + 1 ];
            if ( member_array( word, _exits ) == -1 ) {
               _exits += ({ word });
            }
         }
         tmp_al = delete( tmp_al, j, 2 );
         j = member_array( exit, tmp_al );
      }
   }
}
void init() {
  object ob;
  int i;
  if(this_player() && interactive(this_player())) {
    if(((!last_visited && uptime() > 1800 + random(3600)) ||
      (last_visited && (time() - last_visited > random(900) + 900)))) {
      if(clonep(this_object()))
        this_player()->adjust_xp(random(random(50)), 0);
      else
        this_player()->adjust_xp(random(random(500)), 0);
    }
    last_visited = time();
  }
  if(is_day != -1 && ((WEATHER_HANDLER->query_day() > 0) != is_day)) {
    is_day = (1 - is_day);
    if(variablelongs && strlen(variablelongs[is_day]))
      set_long(variablelongs[is_day]);
    if(variableitems) {
      for(i=0; i<sizeof(variableitems[1-is_day]); i += 2)
        remove_item(variableitems[1-is_day][i]);
      for(i=0; i<sizeof(variableitems[is_day]); i += 2)
        add_item(variableitems[is_day][i], variableitems[is_day][i+1]);
    }
    setup_room_chat();
  }
  if(chatter) {
    chatter->check_chat();
  }
  if(sitchanger) {
    sitchanger->check_situations();
  }
  if(!sizeof(_exits)) {
    calc_exits();
  }
  if(!pointerp(co_ord)) {
    this_object()->calc_co_ord();
  }
  foreach (ob in hidden_objects) {
    if ( ob && objectp( ob ) ) {
      ob->init();
    } else {
      hidden_objects -= ({ 0, ob });
    }
  }
  if (this_player() && userp(this_player())) {
    foreach (ob in _use_internal_objects) {
      if (ob && objectp(ob)) {
        _use_internal_objects->find_inv_match("all", this_player())->init();
      } else {
        _use_internal_objects -= ({ 0, ob });
      }
    }
  }
  if(item) {
    item->init();
  }
}
string *query_zones() {
  string *zones;
  zones = query_property( "room zone" );
  if ( !zones ) {
    return ({ "nowhere" });
  }
  return zones + ({ });
}
void add_zone(string zone) {
   string *zones;
   zones = query_property( "room zone" );
   if ( !zones ) {
      zones = ({ zone });
   } else {
      zones += ({ zone });
   }
   add_property( "room zone", zones );
}
void remove_zone(string zone) {
   string *zones;
   zones = query_property( "room zone" );
   if ( !zones ) {
      return;
   } else {
      zones -= ({ zone });
   }
   add_property( "room zone", zones );
}
void set_zone( string zone ) {
   add_zone(zone);
}
int query_exit( string direc ) {
  return ( member_array( direc, dest_other ) != -1 );
}
int add_exit( string direc, mixed dest, string type ) {
   mixed *stuff;
   if ( !dest_other ) dest_other = ({ });
   if ( member_array( direc, dest_other ) != -1 ) return 0;
   if ( objectp( dest ) )
      dest = file_name( dest );
   if ( dest[ 0 .. 0 ] != "/" )
      dest = "/"+ dest;
   stuff = ({ dest }) + (mixed *)ROOM_HANDLER->query_exit_type( type, direc );
   dest_other += ({ direc, stuff });
   stuff = ROOM_HANDLER->query_door_type( type, direc,
                                                         dest );
   if ( stuff ) {
      door_control[ direc ] = clone_object( DOOR_OBJECT );
      door_control[ direc ]->setup_door( direc, this_object(), dest, stuff,
                                         type);
      hidden_objects += ({ door_control[ direc ] });
      if (door_control[ direc ]->query_door_name()) {
         door_control[ dest + " " + door_control[ direc ]->query_door_name()] = direc;
      } else {
         door_control[ dest ] = direc;
      }
   }
   if ( find_call_out( "calc_exits" ) == -1 ) {
      call_out( "calc_exits", 1 );
   }
   long_exit = 0;
   short_exit = 0;
   return 1;
}
int modify_exit( mixed direc, mixed *data ) {
   int i, j, k;
   if(pointerp(direc)) {
     for(k = 0; k < sizeof(direc); k++) {
       modify_exit(direc[k], data);
     }
     return 0;
   }
   if ( ( i = member_array( direc, dest_other ) ) == -1 ) {
     return 0;
   }
   for ( j = 0; j < sizeof( data ); j+= 2 ) {
     switch ( lower_case( data[ j ] ) ) {
     case "message" :
       dest_other[ i + 1 ][ ROOM_EXIT ] = data[ j + 1 ];
       break;
     case "exit mess" :
     case "exit_mess" :
       dest_other[ i + 1 ][ ROOM_EXIT ] = data[ j + 1 ];
       break;
     case "move mess" :
       dest_other[ i + 1 ][ ROOM_MESS ] = data[ j + 1 ];
       break;
     case "linker mess" :
       dest_other[ i + 1 ][ ROOM_LINK_MESS ] = data[ j + 1 ];
       break;
     case "obvious" :
       dest_other[ i + 1 ][ ROOM_OBV ] = data[ j + 1 ];
       if ( !intp( data[ j + 1 ] ) )
         add_property( "no exit cache", 1 );
       long_exit = 0;
       short_exit = 0;
       break;
     case "function" :
       dest_other[ i + 1 ][ ROOM_FUNC ] = data[ j + 1 ];
       break;
     case "size" :
       dest_other[ i + 1 ][ ROOM_SIZE ] = data[ j + 1 ];
       break;
     case "upgrade" :
       dest_other[ i + 1 ][ ROOM_GRADE ] = data[ j + 1 ];
       break;
     case "downgrade" :
       dest_other[ i + 1 ][ ROOM_GRADE ] = -data[ j + 1 ];
       break;
     case "enter" :
       dest_other[ i + 1 ][ ROOM_ENTER ] = data[ j + 1 ];
       break;
     case "enter mess" :
     case "enter_mess" :
       if ( sizeof( dest_other[ i + 1 ][ ROOM_ENTER ] ) == 2 )
         dest_other[ i + 1 ][ ROOM_ENTER ] = replace( data[ j + 1 ],
           "$F", dest_other[ i + 1 ][ ROOM_ENTER ][ 1 ] );
       else
         dest_other[ i + 1 ][ ROOM_ENTER ] = data[ j + 1 ];
       break;
     case "dest" :
       dest_other[ i + 1 ][ ROOM_DEST ] = data[ j + 1 ];
       if ( objectp( door_control[ direc ] ) ) {
         map_delete(door_control, door_control[ direc ]->query_dest() + " " + door_control[ direc ]->query_door_name());
         door_control[ direc ]->set_dest( data[ j + 1 ] );
         door_control[ data[ j + 1 ] ] = direc;
         if (door_control[ direc ]->query_door_name()) {
            door_control[ data[ j + 1 ] + " " + door_control[ direc ]->query_door_name()] = direc;
         }
       }
       break;
     case "door name" :
       if ( objectp( door_control[ direc ] ) ) {
          map_delete(door_control, door_control[ direc ]->query_dest() + " " + door_control[ direc ]->query_door_name());
          door_control[ direc ]->set_door_name( data[ j + 1 ] );
          door_control[ door_control[ direc ]->query_dest() + " " + data[ j + 1 ]] = direc;
       }
       break;
     case "relative" :
       dest_other[ i + 1 ][ ROOM_REL ] = data[ j + 1 ];
       break;
     case "lock owner" :
       if ( objectp( door_control[ direc ] ) ) {
          door_control[ direc ]->set_lock_owner( data[ j + 1 ] );
       }
       break;
     case "look" :
       dest_other[ i + 1][ ROOM_LOOK ] = data[ j + 1 ];
       break;
     case "look func" :
       dest_other[ i + 1][ ROOM_LOOK_FUNC ] = data[ j + 1 ];
       break;
     case "no map" :
       dest_other[ i + 1][ ROOM_NO_MAP ] = data[ j + 1 ];
       break;
     case "delta" :
       dest_other[ i + 1][ ROOM_DELTA ] = data[ j + 1 ];
       break;
     case "closed" :
       if ( objectp( door_control[ direc ] ) ) {
         if ( data[j+1]) {
            door_control[ direc ]->set_closed();
         } else {
            door_control[ direc ]->set_open();
         }
       }
       break;
     case "open" :
       if ( objectp( door_control[ direc ] ) ) {
         if ( data[j+1]) {
            door_control[ direc ]->set_open();
         } else {
            door_control[ direc ]->set_closed();
         }
       }
       break;
     case "transparent" :
       if ( objectp( door_control[ direc ] ) ) {
         data[j+1] ? door_control[ direc ]->set_transparent() :
           door_control[ direc ]->reset_transparent();
       }
       break;
     case "stuck" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_stuck( data[ j + 1 ] );
       }
       break;
     case "locked" :
       if ( objectp( door_control[ direc ] ) ) {
         if(data[j+1]) {
           door_control[ direc ]->set_closed();
           door_control[ direc ]->set_locked();
         } else
           door_control[ direc ]->set_unlocked();
       }
       break;
     case "unlocked" :
       if ( objectp( door_control[ direc ] ) ) {
         data[j+1] ? door_control[ direc ]->set_unlocked() :
           door_control[ direc ]->set_locked();
       }
       break;
     case "autolock":
       if ( objectp( door_control [direc ] ) ) {
         door_control[ direc ]->set_autolock( data[ j + 1 ] );
       }
       break;
     case "key" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_key( data[ j + 1 ] );
       }
       break;
     case "other" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_other_id( data[ j + 1 ] );
       }
       break;
     case "difficulty" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_difficulty( data[ j + 1 ] );
       }
       break;
     case "door long" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_long( data[ j + 1 ] );
       }
       break;
     case "open/close func" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[direc]->set_open_trap(data[j+1][0], data[j+1][1]);
       }
       break;
     case "lock/unlock func" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[direc]->set_lock_trap(data[j+1][0], data[j+1][1]);
       }
       break;
     case "door short" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_short( data[ j + 1 ] );
       }
       break;
     case "double doors" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_how_many( data[ j + 1 ] );
       }
       break;
     case "one way" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->set_one_way( data[ j + 1 ] );
       }
       break;
     case "secret" :
       if ( objectp( door_control[ direc ] ) ) {
         door_control[ direc ]->remove_hide_invis( "secret" );
         if ( data[ j + 1 ] > 0 ) {
           door_control[ direc ]->add_hide_invis( "secret", 0,
                                                  data[ j + 1 ], 0 );
         }
       }
       break;
     case "undoor" :
       if ( objectp( door_control[ direc ] ) ) {
         map_delete( door_control, dest_other[ i + 1 ][ ROOM_DEST ] + " " +
                                   door_control[ direc ]->query_door_name() );
         door_control[ direc ]->go_away();
         hidden_objects -= ({ door_control[ direc ] });
         map_delete( door_control, direc );
         map_delete( door_control, dest_other[ i + 1 ][ ROOM_DEST ] );
       }
       break;
     case "no follow" :
       if (data[j + 1]) {
         dest_other[ i + 1 ][ROOM_NPC_STOP] = 1;
       } else {
         dest_other[ i + 1 ][ROOM_NPC_STOP] = 0;
       }
       break;
     }
   }
   return 1;
}
int remove_exit( string direc ) {
  int i;
  if ( !dest_other ) {
    dest_other = ({ });
    return 0;
  }
  i = member_array( direc, dest_other );
  if ( i == -1 )
    return 0;
  if ( door_control[ direc ] ) {
    door_control[ direc ]->dest_me();
    hidden_objects -= ({ door_control[ direc ] });
    door_control = m_delete( door_control, direc );
    door_control = m_delete( door_control, dest_other[ i + 1 ][ ROOM_DEST ] );
  }
  dest_other = delete( dest_other, i, 2 );
  if ( find_call_out( "calc_exits" ) == -1 )
    call_out( "calc_exits", 1 );
   long_exit = 0;
   short_exit = 0;
  return 1;
}
int query_door_open( string direc ) {
  if ( !objectp( door_control[ direc ] ) ) {
    return -1;
  }
  return (int)door_control[ direc ]->query_open();
}
int query_relative( string direc ) {
   int i;
   i = member_array( direc, dest_other );
   if ( i == -1 ) {
      return 0;
   }
   return dest_other[ i + 1 ][ ROOM_REL ];
}
string query_look( string direc ) {
   int i;
   i = member_array( direc, dest_other );
   if ( i == -1 )
      return 0;
   if ( !dest_other[ i + 1 ] )
      return 0;
   return (string)evaluate(dest_other[ i + 1 ][ ROOM_LOOK ]);
}
mixed *query_look_func( string direc ) {
  int i;
  if ( ( i = member_array( direc, dest_other ) ) == -1 ) return 0;
  if( !dest_other[ i + 1 ] ) return 0;
  return dest_other[ i + 1 ][ ROOM_LOOK_FUNC ];
}
int query_size( string direc ) {
  int i;
  if ( ( i = member_array( direc, dest_other ) ) == -1 ) return 0;
  if ( stringp( dest_other[ i + 1 ][ ROOM_SIZE ] ) )
    return (int)call_other( this_object(), dest_other[ i + 1 ][ ROOM_SIZE ] );
  if ( pointerp( dest_other[ i + 1 ][ ROOM_SIZE ] ) )
    return (int)call_other( dest_other[ i + 1 ][ ROOM_SIZE ][ 0 ],
        dest_other[ i + 1 ][ ROOM_SIZE ][ 1 ] );
  return dest_other[ i + 1 ][ ROOM_SIZE ];
}
void event_magic( object channel, int amount, object caster ) {
   add_enchant( amount / 5 );
}
void event_theft( object command_ob, object thief, object victim,
                  object *stolen ) {
  if(thief->query_caster())
    thief = find_player(thief->query_caster());
  else if(thief->query_owner())
    thief = thief->query_owner();
  log_file( "THEFT", "%s: %s stole %s from %s in %s\n",
            ctime( time() )[4..18], (string)thief->query_short(),
            implode( (string *)stolen->query_short(), ", " ),
            (string)victim->query_short(), file_name() );
  if ( stringp( theft_handler )) {
    if( theft_handler != "none" )
      theft_handler->handle_theft( this_object(), command_ob, thief,
                                   victim, stolen );
  } else
    "/obj/handlers/theft_handler"->handle_theft( this_object(), command_ob,
                                                 thief, victim, stolen );
}
int query_last_visited() { return last_visited; }
varargs int add_item( mixed shorts, mixed desc, int no_plural ) {
  if (!desc) {
     printf("Error!  In %O add_item(%O, 0), not added.\n", file_name(),
                                                           shorts);
     return 0;
  }
  if ( !item ) {
     item = clone_object( ITEM_OBJECT );
  }
  item->setup_item( shorts, desc, no_plural );
  return 1;
}
int remove_item( string word ) {
  if ( !item ) {
    return 1;
  }
  return (int)item->remove_item( word );
}
int modify_item( string word, mixed new_desc ) {
  if ( !item ) {
    return 0;
  }
  return (int)item->modify_item( word, new_desc );
}
varargs int set_linker( string *rooms, string d_prep, string s_prep,
    string r_name ) {
  if ( linker ) {
    return 0;
  }
  linker = clone_object( LINKER_OBJECT );
  linker->setup_shadow( this_object(), rooms, d_prep, s_prep, r_name );
  return 1;
}
int set_terrain( string terrain_name ) {
   if ( terrain ) {
      return 0;
   }
   terrain = clone_object( TERRAIN_OBJECT );
   terrain->setup_shadow( this_object(), terrain_name );
   set_not_replaceable(1);
   return 1;
}
void set_wall( mixed *args ) {
   if ( !wall ) {
      wall = clone_object( WALL_OBJECT );
      wall->setup_shadow( this_object() );
   }
   wall->set_wall( args );
}
void set_default_position(mixed stuff) {
  add_property(DEFAULT_POSITION_PROPERTY, stuff);
}
mixed query_default_position() {
   return query_property(DEFAULT_POSITION_PROPERTY);
}
int is_allowed_position(string poss) {
  switch (poss) {
    case SITTING :
    case STANDING :
    case KNEELING :
    case LYING :
    case MEDITATING :
    case CROUCHING :
      return 1;
    default :
      return 0;
  }
}
void dest_me() {
  object thing;
  if ( file_name( this_object() ) != ROOM_VOID ) {
    foreach( thing in all_inventory( this_object() ) ) {
      if ( userp( thing ) ) {
        thing->move_with_look( ROOM_VOID, "$N fall$s into the void." );
        continue;
      }
      thing->dest_me();
    }
  }
  if ( chatter )
    chatter->dest_me();
  if ( sitchanger )
    sitchanger->dest_me();
  if ( linker )
    linker->destruct_shadow( linker );
  if ( terrain )
    terrain->destruct_shadow( terrain );
  if(wall)
    wall->destruct_shadow(wall);
  if ( item )
    item->dest_me();
  if(door_control)
    foreach(thing in keys(door_control))
      if(objectp(thing))
        catch(thing->dest_me());
  if ( sizeof( hidden_objects ) )
    foreach( thing in hidden_objects ) {
      if ( objectp( thing ) && ( thing->multiple_hidden() == 0 ) )
        catch( thing->dest_me() );
    }
  destruct( this_object() );
}
void set_keep_room_loaded(int flag) {
   add_property(ROOM_KEEP_PROP, flag);
}
int query_keep_room_loaded() {
   return query_property(ROOM_KEEP_PROP);
}
int clean_up( int parent ) {
  if (parent) {
    return 0;
  }
  if (this_object()->query_keep_room_loaded()) {
      return 0;
  }
  call_out("real_clean", 30 + random(120));
  return 1;
}
int real_clean() {
   object thing;
   foreach ( thing in all_inventory( this_object() ) ) {
     if(thing->query_property("transient")) {
       if(thing->query_property("hospital"))
         thing->move(thing->query_property("hospital"), "$N wander$s in.",
                     "$N wander$s out.");
       else
         thing->move("/room/rubbish", "$N wander$s in.", "$N wander$s out.");
     }
     if ( thing->query_property( "player" ) ||
          (thing->query_property( "unique" ) &&
           last_visited > time() - 3600) ||
          thing->query_slave() ||
          thing->query_name() == "corpse") {
         return 0;
      }
   }
   dest_me();
   return 1;
}
int filter_inventory(object item, object looker) {
  return item && item->short(0) && (!looker || item->query_visible(looker));
}
object *find_inv_match( string words, object looker ) {
   object *things;
   things = all_inventory( this_object() );
   if ( pointerp( hidden_objects ) ) {
      things += hidden_objects;
   }
   if (looker && userp(looker)) {
      things = filter(things, "filter_inventory", this_object(), looker);
   }
   if ( item ) {
      things += ({ item });
   }
   return things;
}
varargs object add_sign( string sign_long, mixed sign_read_mess, string
    sign_short, mixed sign_name, string sign_language ) {
  object sign;
  string* bits;
  sign = clone_object( "/std/object" );
  if ( !sign_name ) {
     sign_name = "sign";
  }
  if (pointerp(sign_name)) {
    bits = explode(sign_name[0], " ");
    sign->set_name( bits[<1] );
    sign->add_adjective( bits[0..<2]);
    sign->add_alias(implode(map(sign_name[1..], (: explode($1, " ")[<1] :)),
           (: $1 | ({ $2 }) :), ({ })));
    sign->add_plural(implode(map(sign_name[1..],
           (: pluralize(explode($1, " ")[<1]) :)), (: $1 | ({ $2 }) :), ({ })));
    sign->add_adjective(implode(map(sign_name[1..],
           (: explode($1, " ")[0..<2] :)), (: $1 | ({ $2 }) :), ({ })));
  } else {
    bits = explode(sign_name, " ");
    sign->set_name( bits[<1] );
    sign->add_adjective( bits[0..<2]);
  }
  sign->set_long( sign_long );
  if ( !sign_language ) sign_language = "common";
  sign->set_read_mess( sign_read_mess, sign_language );
  sign->reset_get();
  if ( sign_short && ( sign_short != "" ) ) {
    sign->set_short( sign_short );
    sign->set_main_plural( pluralize( sign_short ) );
    sign->move( this_object() );
    sign->add_property("there", "here");
  } else {
    hidden_objects += ({ sign });
    bits = sign->query_adjectives();
    if (sizeof(bits) > 0)
      sign->set_short(implode(bits, " ") + " " + sign->query_name());
    else
      sign->set_short(sign->query_name());
  }
  return sign;
}
void tell_door( string direc, string message, object thing ) {
   if ( objectp( door_control[ direc ] ) )
      door_control[ direc ]->tell_door( message, thing );
}
varargs mixed call_door( string direc, string func, mixed arg1, mixed arg2,
      mixed arg3 ) {
   if ( objectp( door_control[ direc ] ) )
      return (mixed)call_other( door_control[ direc ], func, arg1, arg2,
            arg3 );
}
string query_door( mixed dest, string name ) {
   int i;
   string direc;
   mixed bing;
   if ( objectp( dest ) ) {
      dest = file_name( dest );
   }
   if ( !stringp( dest ) ) {
      return 0;
   }
   if (name) {
      bing = door_control[ dest + " " + name];
      if (!bing) {
         bing = door_control[ dest ];
      }
   } else {
      bing = door_control[ dest ];
   }
   if ( bing ) {
      if ( !objectp( bing ) ) {
         direc = bing;
      }
   }
   if ( !direc ) {
      return 0;
   }
   bing = door_control[ direc ];
   if ( objectp( bing ) ) {
      return direc;
   }
   bing = clone_object( DOOR_OBJECT );
   i = member_array( direc, dest_other );
   bing->setup_door( direc, this_object(), dest, dest_other[ i + 1 ] );
   hidden_objects += ({ bing });
   door_control[ direc ] = bing;
   return direc;
}
void stop_room_chats() {
   if ( chatter ) {
      chatter->dest_me();
   }
}
void set_chat_min_max( int min,int  max ) {
  if (chatter) chatter->set_chat_min_max(min,max);
}
void add_room_chats( string *new_chats ) {
  if (chatter) {
    chatter->add_room_chats( new_chats );
  }
}
void remove_room_chats( string *dead_chats ) {
  if (chatter) {
    chatter->remove_room_chats( dead_chats );
  }
}
mixed *query_room_chats() {
  if (chatter) {
    return chatter->query_room_chats();
  }
  return 0;
}
private void setup_room_chat() {
  mixed* chats;
  if (!chatter) {
    chatter = clone_object( CHATTER_OBJECT );
    if(base_name(this_object()) == "/d/sur/Maps/basic_rooms/plains/plains")
      log_file("CHATTER", "%s cloned chatter: %O\n",
               file_name(this_object()), chatter);
  }
  if(is_day == -1) {
    is_day = (WEATHER_HANDLER->query_day() > 0);
  }
  if (!variablechats) {
    variablechats = allocate(3);
  }
  if (is_day) {
    chats = variablechats[ROOM_DAY_INDEX];
  } else {
    chats = variablechats[ROOM_NIGHT_INDEX];
  }
  if (!chats) {
    chats = variablechats[ROOM_DEFAULT_INDEX];
  } else if (variablechats[ROOM_DEFAULT_INDEX]) {
    chats[2] += variablechats[ROOM_DEFAULT_INDEX][2];
  }
  chatter->setup_chatter( this_object(), chats );
}
varargs void room_chat( mixed *args, object chatobj ) {
   if (!args)  {
      return;
   }
   if ( !pointerp( args[ 2 ] ) ) {
      write( "Error: second argument of room_chat args is not an array.\n" );
      return;
   }
   if (!chatter && objectp(chatobj)) {
     chatter = chatobj;
   }
   if (!variablechats) {
      variablechats = allocate(3);
   }
   variablechats[ROOM_DEFAULT_INDEX] = args;
   setup_room_chat();
}
varargs object set_situation_changer( mixed changer ) {
  if (stringp(changer)) {
    sitchanger = clone_object( changer );
  } else if (objectp(changer)) {
    sitchanger = changer;
  } else {
    sitchanger = clone_object( SITUATION_CHANGER_OBJECT );
  }
  return (sitchanger = sitchanger->set_room( this_object() ));
}
void add_situation( mixed label, class situation sit ) {
  if (!sitchanger) {
    sitchanger = clone_object( SITUATION_CHANGER_OBJECT );
    sitchanger->set_room( this_object() );
  }
  sitchanger->add_situation( label, sit );
}
void make_situation_seed(int xval, int yval) {
  if (sitchanger) sitchanger->set_seed(xval,yval);
}
void start_situation(int label, int do_start_mess) {
  if (sitchanger)
    sitchanger->start_situation( label, do_start_mess );
}
void end_situation(mixed label) {
  if (sitchanger) sitchanger->end_situation( label );
}
varargs mixed change_situation( mixed label, mixed duration, mixed words ) {
  if (sitchanger)
    return sitchanger->change_situation(label,duration,words,0);
  return 0;
}
varargs void automate_situation( mixed label, mixed duration, mixed when,
    mixed chance, mixed category ) {
  if (sitchanger)
    sitchanger->automate_situation(label,duration,when,chance,category);
}
void shutdown_all_situations() {
  if (sitchanger) sitchanger->shutdown_all_situations();
}
void shutdown_situation(int call, mixed label) {
  if (sitchanger) sitchanger->shutdown_situation(call,label);
}
int query_not_replaceable() {
   return query_property(ROOM_NOT_REPLACE_PROGRAM_PROP);
}
void set_not_replaceable(int replace) {
   add_property(ROOM_NOT_REPLACE_PROGRAM_PROP, replace);
}
mixed stats() {
   int i;
   mixed *stuff;
   stuff = ({ });
   for ( i = sizeof( dest_other ) - 2; i > -1; i -= 2 )
      stuff += ({
         ({ dest_other[ i ], dest_other[ i + 1 ][ ROOM_DEST ] })
      });
   if ( co_ord )
      stuff += ({
         ({ "co-ord x", co_ord[ 0 ] }),
         ({ "co-ord y", co_ord[ 1 ] }),
         ({ "co-ord z", co_ord[ 2 ] })
      });
   return light::stats() + property::stats() + effects::stats() + stuff + ({
      ({ "short", short( 0 ) }),
      ({ "enchantment", query_enchant() }),
      ({ "background enchantment", background_enchant }),
      ({ "dynamic enchantment", dynamic_enchant }),
      ({ "enchantment time", enchant_time }),
      ({ "theft handler", theft_handler }),
   });
}
void set_day_long( string str ) {
  if(!variablelongs) {
    variablelongs = allocate(2);
  }
  variablelongs[ROOM_DAY_INDEX] = str;
  if(is_day == -1) {
    is_day = (WEATHER_HANDLER->query_day() > 0);
  }
  if(is_day == ROOM_DAY_INDEX) {
    set_long(str);
  }
}
string query_day_long() {
   if(variablelongs && strlen(variablelongs[ROOM_DAY_INDEX]))
     return variablelongs[ROOM_DAY_INDEX];
   return this_object()->query_long();
}
void set_night_long( string str ) {
  if(!variablelongs)
    variablelongs = allocate(2);
  variablelongs[ROOM_NIGHT_INDEX] = str;
  if(is_day == -1)
    is_day = (WEATHER_HANDLER->query_day() > 0);
  if(is_day == ROOM_NIGHT_INDEX)
    set_long(str);
}
string query_night_long() {
   if(variablelongs && strlen(variablelongs[ROOM_NIGHT_INDEX]))
     return variablelongs[ROOM_NIGHT_INDEX];
   return this_object()->query_long();
}
private string return_long(mixed desc) {
  int ma;
  if(!pointerp(desc))
    return (string)desc;
  ma = member_array("long", desc);
  if(ma < 0)
    return "Error: No long found.";
  return (string)desc[ma+1];
}
varargs int add_day_item(mixed shorts, mixed desc, mixed no_plural) {
  string the_item;
  if(pointerp(shorts))
    the_item = shorts[0];
  else
    the_item = shorts;
  if(!variableitems)
    variableitems = ({ ({ }), ({ }) });
  variableitems[ROOM_DAY_INDEX] += ({ the_item, return_long(desc) });
  if(is_day == -1)
    is_day = (WEATHER_HANDLER->query_day() > 0);
  if(is_day == ROOM_DAY_INDEX)
    return add_item(shorts, desc, no_plural);
  return 1;
}
varargs int add_night_item(mixed shorts, mixed desc, mixed no_plural) {
  string the_item;
  if(pointerp(shorts))
    the_item = shorts[0];
  else
    the_item = shorts;
  if(!variableitems)
    variableitems = ({ ({ }), ({ }) });
  variableitems[ROOM_NIGHT_INDEX] += ({ the_item, return_long( desc ) });
  if(is_day == -1) {
    is_day = (WEATHER_HANDLER->query_day() > 0);
  }
  if(is_day == ROOM_NIGHT_INDEX)  {
    return add_item(shorts, desc, no_plural);
  }
  return 1;
}
void room_day_chat(mixed *args) {
  if(!variablechats) {
    variablechats = allocate(3);
  }
  variablechats[ROOM_DAY_INDEX] = args;
  if(is_day == -1) {
    is_day = (WEATHER_HANDLER->query_day() > 0);
  }
  if(is_day == ROOM_DAY_INDEX) {
    setup_room_chat();
  }
}
void room_night_chat( mixed *args ) {
  if(!variablechats) {
    variablechats = allocate(3);
  }
  variablechats[ROOM_NIGHT_INDEX] = args;
  if(is_day == -1) {
    is_day = (WEATHER_HANDLER->query_day() > 0);
  }
  if(is_day == ROOM_NIGHT_INDEX) {
    setup_room_chat();
  }
}
string query_help_file_directory() {
  return ROOM_HELP_FILE_DIR;
}
mixed* query_room_night_chats() {
  if (sizeof (variablechats)) {
    return variablechats[ROOM_NIGHT_INDEX];
  }
  return ({ });
}
mixed* query_room_day_chats() {
  if (sizeof (variablechats)) {
    return variablechats[ROOM_DAY_INDEX];
  }
  return ({ });
}
mixed* query_room_default_chats() {
   if (sizeof(variablechats)) {
      return variablechats[ROOM_DEFAULT_INDEX];
   }
   return ({ });
}
mixed* query_day_items() {
  if (sizeof (variableitems)) {
    return variableitems[ROOM_DAY_INDEX];
  }
  return ({ });
}
mixed* query_night_items() {
  if (sizeof (variableitems)) {
    return variableitems[ROOM_NIGHT_INDEX];
  }
  return ({ });
}