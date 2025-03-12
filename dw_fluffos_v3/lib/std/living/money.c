#include "money.h"
object query_money_object(int force) {
   object money;
   money = present( MONEY_ALIAS, this_object() );
   if (!money && force) {
      money = MONEY_VAULT->get_money_ob();
      money->move( this_object() );
   }
   return money;
}
varargs void adjust_money( mixed amount, string type ) {
   if (!amount) return;
   query_money_object( 1 )->adjust_money( amount, type );
   this_object()->do_burden_call();
}
mixed *query_money_array() {
   return query_money_object(1)->query_money_array();
}
void set_money_array( mixed *new_array ) {
   query_money_object(1)->set_money_array( new_array );
}
int query_value() {
   object money;
   money = query_money_object(0);
   if ( ! money ) {
      return 0;
   }
   return money->query_value();
}
int query_value_in( string where ) {
   object money;
   money = query_money_object(0);
   if ( ! money ) {
      return 0;
   }
   return (int)money->query_value_in( where );
}
int query_money( string type ) {
   object money;
   money = query_money_object(0);
   if ( ! money ) {
      return 0;
   }
   return (int)money->query_money( type );
}
varargs void pay_money( mixed m_array, string where ) {
   int i, j;
   object money;
   mixed *p_array;
   money = query_money_object(0);
   if ( !money ) {
      return;
   }
   for ( i = 0; i < sizeof( m_array ); i += 2 ) {
      p_array = (mixed *)MONEY_HAND->make_payment( m_array[ i ],
         m_array[ i + 1 ], money, where );
      if ( !pointerp( p_array ) ) {
         continue;
      }
      if ( sizeof( p_array[ 1 ] ) ) {
         money->adjust_money( p_array[ 1 ] );
      }
      for ( j = 0; j < sizeof( p_array[ 0 ] ); j += 2 ) {
         money->adjust_money( - p_array[ 0 ][ j + 1 ], p_array[ 0 ][ j ] );
      }
   }
}