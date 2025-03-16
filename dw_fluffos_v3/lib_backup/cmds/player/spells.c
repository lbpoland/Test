#include <spells.h>
inherit "/cmds/base";
int cmd() {
   string spell, *magic;
   mapping spells;
   spells = this_player()->query_spells();
   if ( !sizeof( spells ) ) {
      write( "You don't know any magic spells.\n" );
      return 1;
   }
   magic = ({ });
   foreach ( spell in keys( spells ) ) {
      if ( !stringp( spells[ spell ][ S_OBJECT ] ) ) {
         continue;
      }
      if ( sscanf( spells[ spell ][ S_OBJECT ], "%*spriest%*s" ) == 2 ) {
         continue;
      }
      if ( sscanf( spells[ spell ][ S_OBJECT ], "%*srituals%*s" ) == 2 ) {
         continue;
      }
      if ( sscanf( spells[ spell ][ S_OBJECT ], "%*swizard%*s" ) == 2 ) {
         magic += ({ spell });
         continue;
      }
      if ( sscanf( spells[ spell ][ S_OBJECT ], "%*switch%*s" ) == 2 ) {
         magic += ({ spell });
         continue;
      }
      if ( sscanf( spells[ spell ][ S_OBJECT ], "%*sspell%*s" ) == 2 ) {
         magic += ({ spell });
         continue;
      }
   }
   if ( !sizeof( magic ) ) {
      write( "You don't know any magic spells.\n" );
      return 1;
   }
   if ( sizeof( magic ) ) {
      write( "You know the following magic spell"+
            ( sizeof( magic ) == 1 ? "" : "s" ) +":\n" );
      printf( "%#-*s\n", (int)this_player()->query_cols(),
            implode( sort_array( magic, 1 ), "\n" ) );
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "", (: cmd() :) });
}