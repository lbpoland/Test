#include <money.h>
#include <move_failures.h>
#define WATCH_DEFINE "fluff'n'stuff"
#define PRICE_INDEX "/obj/handlers/cpi_handler"
inherit "/std/basic/light";
inherit "/std/basic/consecrate";
inherit "/std/basic/move";
nosave int weight;
nosave int length = 1;
nosave int width = 1;
nosave int value;
nosave mapping value_info;
void check_log_status( object *parray );
void create() {
  weight = 1;
  light::create();
  if(this_object()->query_property(WATCH_DEFINE))
    call_out( "check_log_status", 1, previous_object(-1) );
  value_info = ([ ]);
}
void set_width(int w) { width = w; }
int query_width() { return width; }
void set_length(int l) { length = l; }
int query_length() { return length; }
void adjust_weight(int w) {
    if (environment()) {
        environment()->add_weight(w);
    }
    weight += w;
}
void set_weight(int w) {
    if (environment())
        environment()->add_weight(w-weight);
    weight = w;
}
int query_weight() { return weight; }
int query_complete_weight() { return (int)this_object()->query_weight(); }
varargs int adjust_money(mixed amt, string coin) {
    if (pointerp(amt)) {
        value += (int)MONEY_HAND->query_total_value(amt);
        if (value < 0) {
            value = 0;
        }
        return value;
    }
    amt = (int)MONEY_HAND->query_total_value( ({ coin, amt }) );
    value += amt;
    if (value < 0) {
        value = 0;
    }
    return value;
}
int adjust_value(int i) {
    value += i;
    return value;
}
mixed *query_money_array() {
    return (mixed *)MONEY_HAND->create_money_array(value);
}
int query_money(string type) {
    int i;
    mixed *m_a;
    m_a = (mixed *)MONEY_HAND->create_money_array(value);
    i = member_array(type, m_a);
    if (i == -1) {
        return 0;
    }
    return m_a[i+1];
}
void set_value( int number ) { value = number; }
void set_value_info( string word, int number ) {
    value_info[ word ] = number;
}
void remove_value_info( string word ) {
    if ( undefinedp( value_info[ word ] ) )
        return;
    value_info = m_delete( value_info, word );
}
int query_value() { return value; }
int query_base_value() {
   return value;
}
mapping query_value_info() { return value_info; }
int query_value_at( object place ) {
    int i, total;
    string *info;
    mixed how;
    if ( !value_info ) {
        value_info = ([ ]);
    }
    total = (int)this_object()->query_value();
    info = m_indices( value_info );
    for ( i = 0; i < sizeof( info ); i++ ) {
        how = (mixed)place->query_property( info[ i ] +" valued" );
        if ( how ) {
            switch ( info[ i ] ) {
            case "artifact" :
                total += ( value_info[ "artifact" ] * ( how[ 0 ] +
                    how[ 1 ] * (int)this_object()->query_charges() ) ) / how[ 2 ];
                break;
            case "enchantment" :
                if ( this_object()->query_max_enchant() )
                    total += ( value_info[ "enchantment" ] * how *
                      (int)this_object()->query_enchant() ) /
                    (int)this_object()->query_max_enchant();
                break;
            case "material" :
                total += (int)this_object()->query_weight() *
                (int)PRICE_INDEX->query_price( (string)this_object()->
                  query_material(), how );
                break;
            default :
                total += value_info[ info[ i ] ];
            }
        }
    }
    return total;
}
int query_value_real(string place) {
   int i;
   int total;
   string *info;
   if ( !value_info ) {
      value_info = ([ ]);
   }
   total = (int)this_object()->query_value();
   info = m_indices( value_info );
   for ( i = 0; i < sizeof( info ); i++ ) {
      switch ( info[ i ] ) {
      case "artifact" :
         total += ( value_info[ "artifact" ] * ( 3 +
             1 * (int)this_object()->query_charges() ) ) / 1;
         break;
      case "enchantment" :
         if ( this_object()->query_max_enchant() )
             total += ( value_info[ "enchantment" ] * 10 *
               (int)this_object()->query_enchant() ) /
             (int)this_object()->query_max_enchant();
         break;
      case "material" :
         total += (int)this_object()->query_weight() *
         (int)PRICE_INDEX->query_price( (string)this_object()->
           query_material(), place );
         break;
      default :
         total += value_info[ info[ i ] ];
         break;
      }
   }
   return total;
}
varargs int move( mixed dest, string messin, string messout ) {
  int i, w;
  object from;
  if( stringp(dest) ) {
   if ( strsrch( dest , "#") != -1 )
     dest = find_object(dest);
   else
     dest = load_object(dest);
  }
  if(!dest)
    return MOVE_INVALID_DEST;
  w = (int)this_object()->query_complete_weight();
  if(!(dest->add_weight(w)))
    return MOVE_TOO_HEAVY;
  from = environment();
  i = ::move(dest, messin, messout);
  if(i != MOVE_OK) {
    dest->add_weight(-w);
    return i;
  }
  if(from)
    from->add_weight(-w);
  if(query_light_needs_inform()) {
    if(from)
      inform_of_light_level_change(from);
    inform_of_light_level_change(dest);
  }
  return i;
}
void dest_me() {
    if ( environment() ) {
        environment()->add_weight( -(int)this_object()->query_complete_weight() );
        if ( query_my_light() )
            adjust_light( -query_my_light() );
    }
    ::dest_me();
}
mixed *stats() {
    int i;
    string *info;
    mixed *guff;
    guff = ({ ({ "value", value }) });
    if ( !value_info )
        value_info = ([ ]);
    info = m_indices( value_info );
    for ( i = 0; i < sizeof( info ); i++ )
        guff += ({ ({ "(info) "+ info[ i ], value_info[ info[ i ] ] }) });
    return light::stats() + consecrate::stats() + guff;
}
void check_log_status( object *parray ) {
  if ( this_object()->query_property( WATCH_DEFINE ) &&
       clonep( this_object() ) &&
       arrayp( parray ) &&
       member_array(load_object("/secure/cmds/creator/cl_one"), parray) != -1){
    log_file( "WATCH", "%s TO: %s. TP: %s.\n", ctime(time()),
              base_name( this_object() ), parray[2]->query_name() );
    this_object()->add_property( "CT", time() );
    user_event( "inform", sprintf( "[Restricted] %s cloned %s.",
                                   parray[2]->query_cap_name(),
                                   base_name( this_object() ) ), "cheat" );
  }
}