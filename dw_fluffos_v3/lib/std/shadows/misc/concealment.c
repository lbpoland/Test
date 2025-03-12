object shadowed, *concealed;
void setup_shadow( object thing ) {
   shadow( thing, 1 );
   shadowed = thing;
   concealed = ({ });
}
void destruct_shadow( object thing ) {
   if ( thing == this_object() )
      destruct( this_object() );
   else
      thing->destruct_shadow( thing );
}
void add_concealed( object thing ) {
   concealed -= ({ 0 });
   if ( member_array( thing, concealed ) == -1 )
      concealed += ({ thing });
}
int set_worn_by( object thing ) {
   int weight;
   if ( thing == (object)shadowed->query_worn_by() )
      return 1;
   if ( !shadowed->set_worn_by( thing ) )
      return 0;
   weight = (int)shadowed->query_weight();
   concealed -= ({ 0 });
   foreach ( thing in concealed ) {
      if ( (int)thing->query_complete_weight() > random( weight ) )
         thing->remove_hide_invis( "concealed" );
   }
   call_out( "destruct_shadow", 0, this_object() );
   return 1;
}
mixed *stats() {
   concealed -= ({ 0 });
   return ({
      ({ "concealing", array_to_string( concealed ) })
   }) + (mixed *)shadowed->stats();
}
int query_concealing() { return 1; }