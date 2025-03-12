#include <surface.h>
nosave object *surface_shadows;
object *query_surface_shadows() {
   return surface_shadows;
}
void make_shadow( object thing ) {
  object shadow;
  shadow = clone_object( SURFACE_SHADOW );
  shadow->setup_shadow( thing, this_object() );
  if ( !surface_shadows ) surface_shadows = ({ });
  surface_shadows += ({ shadow });
}
void check_shadows() {
  int i;
  for ( i = 0; i < sizeof( surface_shadows ); i++ ) {
    if ( surface_shadows[ i ] ) {
      if ( environment() == (object)surface_shadows[ i ]->
          query_shadowed( surface_shadows[ i ] ) ) {
        surface_shadows[ i ]->destruct_shadow( surface_shadows[ i ] );
        surface_shadows = surface_shadows[0..i-1] + surface_shadows[i + 1..];
        i--;
      }
    } else {
      surface_shadows = surface_shadows[0..i-1] + surface_shadows[i + 1..];
      i--;
    }
  }
  call_out( "check_environment", 0 );
}
void check_environment() {
  if ( environment() ) {
     make_shadow( environment() );
  }
}
void dest_me() {
  int i;
  for ( i = 0; i < sizeof( surface_shadows ); i++ )
    if ( surface_shadows[ i ] )
      surface_shadows[ i ]->destruct_shadow( surface_shadows[ i ] );
}