inherit "/std/effect_shadow";
mixed set_holder( object thing, int pos ) {
   this_object()->remove_hide_invis( "concealed" );
   if ( objectp( thing ) )
      if ( !thing->query_corpse() &&
            ( (string)thing->query_name() != arg() ) )
         return 0;
   return (mixed)player->set_holder( thing, pos );
}
string query_owner(){
   return (string) arg();
}