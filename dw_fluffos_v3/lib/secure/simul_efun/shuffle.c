mixed *shuffle( mixed *args ) {
   int i, j;
   mixed temp;
   if ( !pointerp( args ) )
      return ({ });
   if ( sizeof( args ) < 2 )
      return args;
   for ( i = 0; i < sizeof( args ); i++ ) {
      j = random( i + 1 );
      if ( i == j )
         continue;
      temp = args[ i ];
      args[ i ] = args[ j ];
      args[ j ] = temp;
   }
   return args;
}