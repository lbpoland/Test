inherit "/std/object";
#include <shops/engrave.h>
void create() {
  do_setup++;
  ::create();
  do_setup--;
  set_name("key");
  set_long("A key.  Wonder where it fits?.\n");
  add_plural("keys");
  set_short("key");
  add_property(ENGRAVE_PROP, 1);
  if(!do_setup) {
    this_object()->setup();
  }
}
void set_key( string str, string prop ) {
  string *bits;
  int i;
  set_short( str + " key" );
  set_main_plural( str + " keys" );
  set_name( "key" );
  add_plural( "keys" );
  bits = explode( str, " " );
  for( i = 0; i < sizeof( bits ); i ++ ) {
    add_adjective( bits[i] );
  }
  add_property( prop, 1 );
  set_value( 0 );
  set_weight( 1 );
}
mixed query_static_auto_load() {
  if ( base_name(this_object()) + ".c" == __FILE__ )
    return int_query_static_auto_load();
  return ([ ]);
}