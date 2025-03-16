varargs string query_multiple_short( mixed *args, string type,
                                     int no_dollars, int quiet,
                                     int dark ) {
   int i;
   string func;
   string ret;
   if (no_dollars && sizeof(args) && objectp(args[0]) && undefinedp(dark) &&
       this_player() && environment(this_player())) {
      dark = this_player()->check_dark(environment(this_player())->query_light());
      if (dark) {
         return "some objects you cannot make out";
      }
   }
   args = copy(args);
   if ( !type ) {
      type = "a";
   }
   for ( i = 0; i < sizeof( args ); i++ ) {
      if ( !objectp( args[ i ] ) ) {
         break;
      }
   }
   func = type + "_short";
   if ( i == sizeof( args ) && !no_dollars) {
      for ( i = 0; i < sizeof( args ); i++ ) {
         args[ i ] = call_other(args[ i ], func, quiet);
      }
      return "$M$"+ implode( args, "" ) +"$M$";
   }
   for ( i = 0; i < sizeof( args ); i++ ) {
      if ( objectp( args[ i ] ) ) {
         args[ i ] = call_other(args[ i ], func, quiet);
      } else if ( pointerp( args[ i ] ) ) {
         args[ i ] = "$"+ type +"_short:"+ file_name( args[ i ][ 1 ] ) +"$";
      }
   }
   i = sizeof( args );
   switch ( i ) {
      case 0 :
         return "";
      case 1 :
         ret = args[ 0 ];
         break;
      default :
         ret = implode( args[ 0 .. i - 2 ], ", " ) +" and "+ args[ i - 1 ];
         break;
   }
   if (no_dollars) {
      if (this_player()) {
         return this_player()->convert_message(ret);
      } else {
         return "/global/player"->convert_message(ret);
      }
   }
   return ret;
}