#include <volumes.h>
#define FOUNTAIN_SIZE 150000
#define DEFAULT_CYCLE_TIME 60 * ( 2 + random( 2 ) )
inherit "/obj/vessel";
string _liquid_path;
int _liquid_volume;
int _time;
void setup() {
  set_name( "fountain" );
  set_short( "fountain" );
  set_long( "This is a fountain.\n" );
  set_max_volume( FOUNTAIN_SIZE );
  set_weight( 100000 );
  set_stuck( 1 );
}
varargs void initialise( string path, int amount, int time) {
  if ( !stringp( path ) )
    error( "Path not set in initialise.\n" );
  if ( !intp( amount ) )
    amount = VOLUME_LITRE;
  if ( !time )
    time = DEFAULT_CYCLE_TIME;
  _liquid_path = path;
  _liquid_volume = amount;
  _time = time;
  call_out( "make_water", 5 );
  return;
}
varargs void reinitialise( string path, int amount, int time) {
  if ( !stringp( path ) )
    error( "Path not set in initialise.\n" );
  if ( !intp( amount ) )
    amount = VOLUME_LITRE;
  if ( !time )
    time = DEFAULT_CYCLE_TIME;
  _liquid_path = path;
  _liquid_volume = amount;
  _time = time;
  return;
}
void make_water() {
object water;
  if ( !( query_max_volume() - query_volume() ) ) {
    tell_room( environment(), sprintf( "Some of the %s in %s sloshes over the sides.\n",
      query_multiple_short( all_inventory() ), this_object()->the_short() ) );
    remove_volume( -VOLUME_QUART * random( 4 ) * 2 );
  }
  water = clone_object( _liquid_path );
  water->set_amount( _liquid_volume );
  call_out( (: $(water)->move( this_object() ) :), 1 );
  switch( water->query_amount() ) {
	case 0 .. VOLUME_SHOT:
      tell_room( environment(), sprintf( "$C$%s %s into %s.\n",
  	  water->a_short(), ({ "trickles", "seeps", "dribbles" })[random(3)],
	  this_object()->the_short() ) );
      break;
    case VOLUME_SHOT + 1 .. VOLUME_PINT:
      tell_room( environment(), sprintf( "$C$%s %s into %s.\n",
		water->a_short(),  ({ "flows", "splashes", "pours" })[random(3)],
		this_object()->the_short() ) );
      break;
    case VOLUME_PINT + 1 .. VOLUME_LITRE:
      tell_room( environment(), sprintf( "$C$%s %s into %s.\n",
		water->a_short(), ({ "streams", "cascades", "sloshes" })[random(3)],
		this_object()->the_short() ) );
      break;
    case VOLUME_LITRE + 1 .. VOLUME_QUART:
      tell_room( environment(), sprintf( "$C$%s %s into %s.\n",
	    water->a_short(), ({ "gushes", "courses", "swirls" })[random(3)],
        this_object()->the_short() ) );
      break;
    default:
      tell_room( environment(), sprintf( "$C$%s %s into %s.\n",
        water->a_short(), ({ "floods", "surges", "washes" })[random(3)],
  	    this_object()->the_short() ) );
      break;
  }
  call_out( "make_water", _time );
}