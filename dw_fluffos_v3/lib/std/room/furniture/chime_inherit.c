inherit "/std/object";
inherit "/std/room/furniture/inherit/furniture_base";
#include <weather.h>
#define TIME 120
string chimes_short();
string chimes_long();
void set_chime_type( string type );
string chime_type();
void jingle();
string chime_verb();
void add_chime_verb( string verb );
void remove_chime_verb( string verb );
string *query_chime_verbs();
void set_hung_up( int up );
int hung_up();
void set_hook( object hook );
object hook();
int do_hang( object hook );
int do_unhang();
private string _chime_type = "metal";
private string *_chime_verbs = ({ "jingles", "tinkles" });
private int _hung_up = 0;
private object _hook;
void create() {
   furniture_base::create();
   object::create();
}
void setup() {
  set_name( "chime" );
  set_short( (: chimes_short() :) );
  set_long( (: chimes_long() :) );
  add_adjective( ({ "wind", chime_type() }) );
  set_value( 420 );
}
void init() {
  add_command( "hang", "<direct:object'chime'> {on|from} "
      "<indirect:object'hook'>", (: do_hang( $1[0] ) :) );
  add_command( "unhang", "<direct:object'chime'>" );
}
string chimes_short() {
  return chime_type() + " wind chime";
}
string chimes_long() {
  return "This little wind chime is nothing more than bits of "
             + chime_type() + " dangling from strings tied to a "
             "ring.\n";
}
void set_chime_type( string type ) {
  remove_adjective( _chime_type );
  add_adjective( type );
  _chime_type = type;
}
string chime_type() { return _chime_type; }
void jingle() {
  object env = environment();
  int wind;
  if( !env )
    return;
  if( !hung_up() )
    return;
  if( !inherits( "/std/room", env ) )
    return;
  wind = env->query_wind_speed();
  if( undefinedp( wind ) ) {
    if( env->query_property( "location" ) == "outside" ||
        env->query_property( "windy" ) )
      wind = WEATHER->query_windsp( this_object() );
    else
      return;
  }
  if( random( wind ) )
    tell_room( env, the_short() + chime_verb() + " in the "
        "wind.\n" );
  call_out( "jingle", TIME );
}
string chime_verb() {
  return " " + _chime_verbs[ random( sizeof( _chime_verbs ) ) ];
}
void add_chime_verb( string verb ) {
  _chime_verbs += ({ verb });
}
void remove_chime_verb( string verb ) {
  _chime_verbs -= ({ verb });
}
void set_chime_verbs( string *verbs ) { _chime_verbs = verbs; }
string *query_chime_verbs() { return _chime_verbs; }
void set_hung_up( int up ) {
  remove_call_out( "jingle" );
  if( up )
    call_out( "jingle", 30 );
  _hung_up = up;
}
int hung_up() { return _hung_up; }
void set_hook( object hook ) { _hook = hook; }
object hook() { return _hook; }
int jingling() { return find_call_out( "jingle" ); }
void init_dynamic_arg( mapping arg ) {
  set_chime_type( arg[ "type" ] );
  set_chime_verbs( arg[ "chime verbs" ] );
  set_hook( arg[ "hook" ] );
  set_hung_up( arg[ "hung up" ] );
  if( undefinedp( hook() ) || !hung_up() ||
      !sizeof( match_objects_for_existence( hook(), ({ environment() }) ) ) ) {
    remove_property( "there" );
    set_hung_up( 0 );
  }
}
mixed query_dynamic_auto_load() {
  return ([ "::" : ::query_dynamic_auto_load(),
            "type" : chime_type(),
            "chime verbs" : query_chime_verbs(),
            "hung up" : hung_up(),
            "hook" : hook() ]);
}
int do_hang( object hook ) {
  string where = hook->a_short();
  if( hung_up() ) {
    add_failed_mess( "The chime is already hanging up.\n" );
    return 0;
  }
  if( !hook->query_hook() && !hook->query_property( "hook" ) )
    return 0;
  if( move( environment( this_player() ) ) )
    return 0;
  if( where )
    where = "on " + where;
  else
    where = "up";
  add_property( "there", "hanging "+ where );
  reset_get();
  set_hung_up( 1 );
  set_hook( hook );
  this_player()->add_succeeded_mess( this_object(), "$N $V $D on "
      "$I.\n", ({ hook }) );
  return 1;
}
int do_unhang() {
  if( !hung_up() ) {
    add_failed_mess( "The chime isn't hanging from anything.\n" );
    return 0;
  }
  remove_property( "there" );
  set_get();
  set_hung_up( 0 );
  move( this_player() );
  return 1;
}