#include <learning.h>
#define SAVE SAVEPATH +"request"
mixed *requests;
void create() {
   seteuid( (string)master()->get_bb_uid() );
   unguarded( (: restore_object, SAVE :) );
   if( !requests ) requests = ({ });
}
void save_me() {
   unguarded( (: save_object, SAVE :) );
}
string query_list() {
   int i;
   string ret;
   mixed request;
   if ( !sizeof( requests ) ) {
      return "There are no requests at the moment.\n";
   }
   ret = "$P$Requests$P$The following requests have been made:\n";
   foreach( request in requests ) {
      if ( !request[ 1 ] ) {
         ret += sprintf( "%4d. $C$%s asked for %s.\n", i,
                        request[ 0 ], request[ 2 ] );
      } else {
         ret += sprintf( "%4d. $C$%s asked for %s.\n       Claimed by $C$%s\n", i,
                        request[ 0 ], request[ 2 ],
                        request[ 1 ]);
      }
   }
   return ret;
}
void add_request( string name, string words ) {
   requests += ({ ({ name, 0, words }) });
   save_me();
}
int claim_request( string name, int number ) {
   if ( number >= 0 && number < sizeof( requests ) ) {
      requests[ number ][ 1 ] = name;
      save_me();
      return 1;
   }
   return 0;
}
int remove_request( string name, int number ) {
   if ( number >= 0 && number < sizeof( requests ) ) {
      if ( requests[ number ][ 0 ] == name || name == CURRENT_LORD ) {
         requests = delete( requests, number, 1 );
         save_me();
         return 1;
      }
   }
   return 0;
}