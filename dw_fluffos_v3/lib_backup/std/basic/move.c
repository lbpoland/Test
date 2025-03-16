#include <move_failures.h>
#define DROP 1
#define GET 2
private int move_flag;
varargs int move( mixed dest, string messin, string messout ) {
   object prev;
   if ( !objectp( dest ) ) {
      if ( !stringp( dest ) || !( dest = find_object( dest ) ) ) {
         return MOVE_EMPTY_DEST;
      }
   }
   if ( !dest->test_add( this_object(), this_object()->get(dest) ) ) {
      return MOVE_NO_GET;
   }
   if(dest == this_object()) {
      return MOVE_INVALID_DEST;
   }
   prev = environment();
   if ( prev ) {
      if ( !prev->test_remove( this_object(),
                               this_object()->drop(dest),
                               dest ) ) {
         return MOVE_NO_DROP;
      } else if (prev != find_object("/room/virtual")) {
         event( prev, "exit", messout, dest );
      }
   }
   if (dest != environment()) {
      if( environment() )
        this_object()->remove_property( "there" );
      move_object (dest);
      this_object()->event_move_object( prev, dest );
   }
   if (!(dest == find_object("/room/rubbish") || dest == find_object("/room/virtual"))) {
      event( dest, "enter", messin, prev );
   }
   this_object()->remove_hide_invis( "concealed" );
   this_object()->remove_hide_invis( "secreted" );
   return MOVE_OK;
}
void reset_get() { move_flag |= GET; }
void set_get() { move_flag &= ~GET; }
void reset_drop() { move_flag |= DROP; }
void set_drop() { move_flag &= ~DROP; }
void dest_me() {
   if ( environment() ) {
      event( environment(), "dest_me" );
   }
   this_object()->event_destruct();
   efun::destruct( this_object() );
}
nomask mixed dwep() {
   efun::destruct( this_object() );
   return "Destructed With Extreme Prejudice";
}
int drop( mixed dest ) { return move_flag & DROP; }
int get( mixed dest ) { return move_flag & GET; }
void set_move_flag( int i ) { move_flag = i; }