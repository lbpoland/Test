int query_player_level( string what ) {
   if ( !this_player() )
      return 0;
   switch ( what ) {
      case "error messages" :
         return 1;
      case "trace" :
      case "wizard" :
         return (int)this_player()->query_creator();
   }
}