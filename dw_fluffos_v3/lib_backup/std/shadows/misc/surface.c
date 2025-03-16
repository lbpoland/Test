object shadowed, surface;
void setup_shadow( object thing1, object thing2 ) {
  shadow( thing1, 1 );
  shadowed = thing1;
  surface = thing2;
}
object query_shadowed( object thing ) {
  if ( thing == this_object() ) return shadowed;
  return (object)thing->query_shadowed( thing );
}
object *find_inv_match( string words ) {
  object *things;
  things = (object *)shadowed->find_inv_match( words );
  if ( surface )
    things += (object *)surface->find_inv_match( words );
  else
    call_out( "destruct_shadow", 1, this_object() );
  return things;
}
void destruct_shadow( object thing ) {
  if ( thing == this_object() ) destruct( this_object() );
  else thing->destruct_shadow( thing );
}