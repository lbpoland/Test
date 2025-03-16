#include <money.h>
#define DEF_VALUE 1
#define SAVE_FILE "/save/money_handler"
#define USE_VAULT DEF_VALUE
mapping values;
mapping symbols;
mapping details;
mapping aliases;
mapping adjectives;
mixed *merge_money_arrays(mixed *m_array1, mixed *m_array2);
varargs object *filter_legal_money_array(mixed *m_array, string where);
varargs mixed *filter_legal_money_to_array(mixed *m_array, string where);
void create() {
   seteuid( (string)"/secure/master"->
      creator_file( file_name( this_object() ) ) );
   values = ([ "default": ({ "brass", 1, "copper", 10, "silver", 100,
                                          "gold", 2000, "platinum", 6000 }) ]);
   symbols = ([ ]);
   details = ([
      "brass": ({ "heads", "tails", "a head", "a tail", "brass", 0 }),
      "copper": ({ "heads", "tails", "a head", "a tail", "copper", 0 }),
      "silver": ({ "heads", "tails", "a head", "a tail", "silver", 0 }),
      "gold": ({ "heads", "tails", "a head", "a tail", "gold", 0 }),
      "platinum": ({ "heads", "tails", "a head", "a tail", "platinum", 0 }) ]);
   aliases = ([ ]);
   adjectives = ([ ]);
   if ( file_size( SAVE_FILE +".o" ) > 0 ) {
      unguarded((: restore_object, SAVE_FILE :));
   }
   if ( !symbols ) {
      symbols = ([ ]);
   }
   if ( !aliases ) {
      aliases = ([ ]);
   }
   if ( !adjectives ) {
      adjectives = ([ ]);
   }
}
void save_me() { unguarded( (: save_object, SAVE_FILE :) ); }
mapping query_all_values() { return copy( values ); }
string *query_all_places() {
   return keys(values);
}
mixed *query_values() { return copy( values[ "default" ] ); }
mixed *query_values_in( string where ) {
   if ( !where || ( where == "" ) ) {
      where = "default";
   }
   return copy( values[ where ] );
}
mixed *query_weighted_values_in( string where, int backwards ) {
    mixed *bits;
    int i, j;
    int max_size;
    int len;
    mixed *arr, *reversed;
    if ( !where || ( where == "" ) ) {
        return 0;
    }
    bits = copy( values[ where ] );
    arr = ({ });
    max_size = 0;
    for ( i = 0; i < sizeof( bits ); i += 2 ) {
        len = sizeof( bits[ i ] );
        if ( len > max_size ) {
            arr += ({ bits[ i ], bits[ i + 1 ] });
            max_size = len;
            continue;
        }
        for ( j = 0; j < sizeof( arr ); j += 2 ) {
            if ( len <= sizeof( arr[ j ] ) ) {
                arr = arr[ 0..j-1] + ({ bits[ i ], bits[ i + 1 ] }) + arr[j..];
                break;
            }
        }
    }
    if ( backwards ) {
        reversed = ({ });
        for ( i = sizeof( arr ) - 1; i > 0; i -= 2) {
            reversed += ({ arr[ i - 1 ], arr[ i ] });
        }
        return reversed;
    }
    else {
       return arr;
    }
}
int query_smallest_value_in(string where) {
   mixed* values;
   int value;
   int i;
   if (! where) {
      where = "default";
   }
   values = query_values_in(where);
   value = values[1];
   for (i = 2; i < sizeof(values); i += 2) {
      if (values[i + 1] < value) {
         value = values[i + 1];
      }
   }
   return value;
}
void add_type( string where, string type, int value ) {
   int i;
   if ( !values[ where ] ) {
      values[ where ] = ({ type, value });
      save_me();
      return;
   }
   if ( member_array( type, values[ where ] ) != -1 ) {
      return;
   }
   for ( i = 0; i < sizeof( values[ where ] ); i += 2 ) {
      if ( value < values[ where ][ i + 1 ] ) {
         values[ where ] = values[ where ][ 0 .. i - 1 ] + ({ type, value })
                           + values[ where ][ i .. sizeof( values ) ];
         save_me();
         return;
      }
   }
   values[ where ] += ({ type, value });
   save_me();
}
void remove_type( string where, string type ) {
   int i;
   if ( !values[ where ] ) {
      return;
   }
   i = member_array( type, values[ where ] );
   if ( i == -1 ) {
      return;
   }
   values[ where ] = delete( values[ where ], i, 2 );
   if ( !sizeof( values[ where ] ) ) {
      map_delete( values, where );
   }
   save_me();
}
mapping query_details() { return copy( details ); }
mixed *query_details_for( string word ) {
   if ( !details[ word ] ) {
      return ({ "heads", "tails", "a head", "a tail", "unknown", 0 });
   }
   return copy( details[ word ] );
}
void add_details( string word, string hd_sht, string tl_sht, string hd_lng,
                  string tl_lng, mixed composition, string plural ) {
   if ( details[ word ] ) {
      return;
   }
   details[ word ] = ({ hd_sht, tl_sht, hd_lng, tl_lng, composition, plural });
   save_me();
}
void remove_details( string word ) {
   if ( !details[ word ] ) {
      return;
   }
   map_delete( details, word );
   save_me();
}
mapping query_symbols() { return copy( symbols ); }
string query_symbol_for( string word ) {
   if ( !symbols[ word ] ) {
      return 0;
   }
   return copy( symbols[ word ] );
}
void add_symbol( string word, string symboliser ) {
   if ( symbols[ word ] ) {
      return;
   }
   symbols[ word ] = symboliser;
   save_me();
}
void remove_symbol( string word ) {
   if ( !symbols[ word ] ) {
      return;
   }
   map_delete( symbols, word );
   save_me();
}
string query_alias_for( string type ) {
   log_file("OBSOLETE_CALLS",
      sprintf("%O %s: %O called query_alias_for\n",
         this_object(),
         ctime(time()),
         previous_object()
         ));
   if ( !details[ type ] ) return "coin";
   if ( !details[ type ][ 5 ] ) return "coin";
   return explode( type, " " )[ sizeof( explode( type, " " ) ) - 1 ];
}
void set_aliases_for(string type, string *words) {
   if (!words || !sizeof(words)) {
      if (aliases[type]) {
         map_delete(aliases, type);
      }
   } else {
      aliases[type] = words;
   }
   save_me();
   return;
}
string *query_aliases_for( string type ) {
   string *ret;
   if ( !details[ type ] || !details[ type ][ MONEY_DETAILS_PLURAL ] ) {
      ret = ({ "coin" });
   } else {
      ret = ({ explode(type, " ")[<1] });
   }
   if ( aliases[ type ] ) {
      ret += aliases[ type ];
   }
   return ret;
}
void set_adjectives_for(string type, string *words) {
   if (!words || !sizeof(words)) {
      if (adjectives[type]) {
         map_delete(adjectives, type);
      }
   } else {
      adjectives[type] = words;
   }
   save_me();
   return;
}
string *query_adjectives_for( string type ) {
   string *ret;
   if ( adjectives[ type ] ) {
      ret = adjectives[ type ];
   }
   else {
      ret = ({ });
   }
   return ret;
}
string query_short_for( string type ) {
   if ( !details[ type ] ) {
      return type +" coin";
   }
   if ( !details[ type ][ MONEY_DETAILS_PLURAL ] ) {
      return type +" coin";
   }
   return type;
}
string query_plural_for( string type ) {
   if ( !details[ type ] ) {
      return "coins";
   }
   if ( !details[ type ][ MONEY_DETAILS_PLURAL ] ) {
      return "coins";
   }
   return details[ type ][ MONEY_DETAILS_PLURAL ];
}
void set_plural_for( string type, string plural ) {
   if ( !details[ type ] ) {
      return;
   }
   details[ type ][ MONEY_DETAILS_PLURAL ] = plural;
   save_me();
}
string query_main_plural_for( string type ) {
   string *type_exp;
   if ( !details[ type ] ) {
      return type +" coins";
   }
   if ( !details[ type ][ MONEY_DETAILS_PLURAL ] ) {
      return type +" coins";
   }
   type_exp = explode(type, " ");
   return implode(type_exp[0 .. <2] +
      ({ details[ type ][ MONEY_DETAILS_PLURAL ] }), " " );
}
varargs int query_value( string type, string where ) {
   int i, j, count, total;
   string *places;
   if ( !where || ( where == "" ) ) {
      where = "default";
   }
   if ( where == "mean" ) {
      places = m_indices( values );
      for ( i = 0; i < sizeof( places ); i++ ) {
         if ( ( j = member_array( type, values[ places[ i ] ] ) ) != -1 ) {
            count++;
            total += values[ places[ i ] ][ j + 1 ];
         }
      }
      if ( !count ) {
         return 0;
      }
      if ( !( total / count ) ) {
         return 0;
      }
      return total / count;
   }
   if ( !values[ where ] ) {
      return 0;
   }
   i = member_array( type, values[ where ] );
   if ( i == -1 ) {
      return 0;
   }
   return values[ where ][ i + 1 ];
}
varargs int query_total_value( mixed mon_array, string where ) {
   int i, amt;
   if ( !where || ( where == "" ) ) {
      where = "default";
   }
   for ( i = 0; i < sizeof( mon_array ); i += 2 ) {
      amt += mon_array[ i + 1 ] * query_value( mon_array[ i ], where );
   }
   return amt;
}
string money_string( mixed mon_array ) {
   int i;
   string ret;
   if ( !sizeof( mon_array ) ) {
      return "nothing";
   }
   ret = "";
   while( i < sizeof( mon_array ) ) {
      if ( !mon_array[ i + 1 ] ) {
         mon_array = delete( mon_array, i, 2 );
      } else {
         i += 2;
      }
   }
   for ( i = 0; i < sizeof( mon_array ); i += 2 ) {
      ret += mon_array[ i + 1 ] +" ";
      if ( mon_array[ i + 1 ] == 1 ) {
         ret += query_short_for( mon_array[ i ] );
      } else {
         ret += query_main_plural_for( mon_array[ i ] );
      }
      if ( i == sizeof( mon_array ) - 4 ) {
         ret += " and ";
      } else if ( i != sizeof( mon_array ) - 2 ) {
         ret += ", ";
      }
   }
   return ret;
}
varargs mixed *create_money_array( int value, string where ) {
   int i, amt;
   mixed *mon_array;
   if ( !where || ( where == "" ) ) {
      where = "default";
   }
   if ( !value ) {
      return ({ });
   }
   mon_array = ({ });
   for ( i = sizeof( values[ where ] ) - 2; i >= 0; i -= 2 ) {
      if ( value >= values[ where ][ i + 1 ] ) {
         mon_array += ({ values[ where ][ i ], amt = value /
                         values[ where ][ i + 1 ] });
         value -= amt * values[ where ][ i + 1];
      }
   }
   return mon_array;
}
varargs string money_value_string( int value, string where ) {
   string symboliser;
   if ( !where || ( where == "" ) ) {
      where = "default";
   }
   if ( !symbols[ where ] ) {
      if (value < 0) {
         return "negative " + money_string( create_money_array( -value,
                                                                where ) );
      } else {
         return money_string( create_money_array( value, where ) );
      }
   }
   symboliser = symbols[ where ];
   return (string)symboliser->symbolise_value( value );
}
mixed* money_array_from_string(string str, string where) {
   int value;
   int number;
   int i;
   int pos;
   int frog;
   int match;
   int max_match;
   string plural;
   string *bits;
   string type;
   string match_name;
   mixed *stuff;
   mixed* ret_arr;
   if (!where) {
      where = "default";
   }
   if (symbols[ where ]) {
      value = symbols[ where ]->unsymbolise_string( str );
      if (value) {
         return create_money_array(value, where);
      }
   }
   ret_arr = ({ });
   stuff = query_weighted_values_in( where, 1 );
   if (!value && stuff) {
      bits = explode(str, " ") - ({ "and", ",", "" });
      for (i = 0; i < sizeof(bits); i++) {
         if (sscanf(bits[i], "%d", number) == 1 &&
             i + 1 < sizeof(bits)) {
            i++;
            type = bits[i];
            max_match = 0;
            do {
               match = 0;
               if (type[<1] == ',') {
                  type = type[0..<2];
               }
               type = lower_case(type);
               for (pos = 0; pos < sizeof(stuff); pos += 2) {
                  plural = query_plural_for(stuff[pos]);
                  frog = strsrch(stuff[pos], " ", -1);
                  if (frog) {
                     plural = stuff[pos][0..frog] + plural;
                  }
                  if (lower_case(stuff[pos]) == type ||
                      strsrch(lower_case(stuff[pos]), type) != -1 ||
                      lower_case(plural) == type ||
                      strsrch(lower_case(plural), type) != -1) {
                     match = stuff[pos + 1];
                     match_name = stuff[pos];
                  }
               }
               if (match) {
                  i++;
                  max_match = match;
                  if (i < sizeof(bits)) {
                     type += " " + bits[i];
                  }
               }
            } while (match && i < sizeof(bits));
            if (max_match) {
               ret_arr += ({ match_name, number });
            }
            i--;
         } else {
            i++;
         }
      }
   }
   return ret_arr;
}
int value_from_string(string str, string where) {
   return query_total_value(money_array_from_string(str, where), where);
}
mixed *calc_change( int value, mixed *mon_array ) {
   int i, num;
   mixed *ret;
   ret = ({ });
   for ( i = sizeof( mon_array ) - 2; i >= 0; i -= 2 ) {
      if ( value >= mon_array[ i + 1 ] ) {
         num = value / mon_array[ i + 1 ];
         value = value % mon_array[ i + 1 ];
         ret += ({ mon_array[ i ], num });
         if ( !value ) {
            return ret;
         }
      }
   }
   return ret;
}
mixed *make_money_array_payment( string type,
                                 int value,
                                 mixed *mon_array,
                                 string where,
                                 int use_default) {
   int i;
   int j;
   int num;
   int total;
   int cur_match;
   string mon_name;
   mixed *poss_values;
   mixed *ret;
   if ( !where || ( where == "" ) ) {
      where = "default";
   }
   if (type) {
      i = member_array( type, mon_array );
      if ( i != -1 ) {
         if ( value <= mon_array[ i + 1 ] ) {
            mon_array[ i + 1] -= value;
            return ({ ({ type, value }), 0, mon_array });
         }
      }
      value *= query_value( type, where );
   }
   if (!value) {
      return 0;
   }
   total = query_total_value( mon_array, where );
   if (use_default  &&  where != "default") {
      total += query_total_value( mon_array, "default" );
   }
   if ( value > total ) {
      return 0;
   }
   poss_values = ({ });
   if ( where != "default" && use_default ) {
      poss_values += values[ "default" ];
   }
   poss_values += values[ where ];
   ret = ({ });
   for ( i = ( sizeof( poss_values ) - 2 ); i >= 0; i -= 2 ) {
      j = member_array( poss_values[ i ], mon_array );
      if ( j != - 1 ) {
         if ( poss_values[ i + 1 ] <= value ) {
            num = value / poss_values[ i + 1 ];
            if ( num > mon_array[ j + 1 ] ) {
               num = mon_array[ j + 1 ];
            }
            mon_array[ j + 1] -= num;
            value -= num * poss_values[ i + 1 ];
            ret += ({ poss_values[ i ], num });
            if ( !value ) {
               return ({ ret, value, mon_array });
            }
         }
      }
   }
   cur_match = value + 10000000;
   for (i = 0; i < sizeof(poss_values); i +=2 ) {
      j = member_array( poss_values[ i ], mon_array);
      if (j != -1 &&
          mon_array[j + 1] > 0 &&
          poss_values[i + 1] >= value &&
          poss_values[i + 1] - value <= cur_match - value) {
         cur_match = poss_values[i + 1];
         mon_name = poss_values[i];
      }
   }
   if (mon_name) {
      j = member_array(mon_name, mon_array);
      i = member_array(mon_name, poss_values);
      mon_array[j + 1] -= 1;
      value = poss_values[i + 1] - value;
      ret += ({ poss_values[ i ], 1 });
   } else {
      return 0;
   }
   return ({ ret, value, mon_array });
}
varargs mixed *make_payment( string type, int value, object thing,
                             string where ) {
   mixed *mon_array;
   mixed *stuff;
   if (!type) {
     return 0;
   }
   mon_array = copy(thing->query_money_array());
   stuff = make_money_array_payment( type, value, mon_array, where, 1);
   if (!stuff) {
      return stuff;
   }
   if (stuff[MONEY_PAY_CHANGE]) {
      return ({ stuff[MONEY_PAY_RETURN], calc_change(stuff[MONEY_PAY_CHANGE],
                                                     values[where]) });
   }
   return ({ stuff[MONEY_PAY_RETURN], stuff[MONEY_PAY_CHANGE] });
}
varargs object pay_amount_from(int value, object money, string where) {
   int i;
   object change;
   mixed *m_array, *p_array;
   mixed *change_array;
   mixed *pay_array;
   if (!where || where == "") {
      where = "default";
   }
   change_array = ({ });
   pay_array = ({ });
   m_array = create_money_array(value, where);
   for (i = 0; i < sizeof(m_array); i += 2) {
      p_array = make_payment(m_array[i], m_array[i + 1], money, where);
      if (!pointerp(p_array)) {
         continue;
      }
      if (sizeof(p_array[0]) > 0)
         pay_array = merge_money_arrays(pay_array, p_array[0]);
      if (sizeof(p_array[1]) > 0) {
         change_array = merge_money_arrays(change_array, p_array[1]);
      }
   }
   if (sizeof(pay_array) > 0)  {
      for (i = 0; i < sizeof(pay_array); i += 2) {
         pay_array[i + 1] = -pay_array[i + 1];
      }
      money->adjust_money(pay_array);
   }
   if (sizeof(change_array) == 0) {
      return 0;
   }
#ifdef USE_VAULT
   change = MONEY_VAULT->get_money_ob();
   change->set_money_array(change_array);
#else
   change = clone_object(MONEY_OBJECT);
#endif
   return change;
}
varargs object make_new_amount( int value, string where ) {
   object money;
   if ( !where || ( where == "" ) ) {
      where = "default";
   }
#ifdef USE_VAULT
   money = MONEY_VAULT->get_money_ob();
#else
   money = clone_object( MONEY_OBJECT );
#endif
   money->set_money_array( create_money_array( value, where ) );
   if ( !(int)money->query_value_in( where ) ) {
      money->dest_me();
      return 0;
   }
   return money;
}
varargs object *filter_legal_tender(object money, string where) {
   mixed *m_array;
   object *monies;
   m_array = money->query_money_array();
   monies = filter_legal_money_array(m_array, where);
#ifdef USE_VAULT
   MONEY_VAULT->add_to_list(money);
#else
   money->move("/room/rubbish");
#endif
   return monies;
}
varargs object *filter_legal_money_array(mixed *m_array, string where) {
   object good, no_good;
   mixed *money_arrays;
   money_arrays = filter_legal_money_to_array(m_array, where);
   if (sizeof(money_arrays[0]) == 0) {
      good = 0;
   } else  {
#ifdef USE_VAULT
      good = MONEY_VAULT->get_money_ob();
#else
      good = clone_object(MONEY_OBJECT);
#endif
      good->set_money_array(money_arrays[0]);
   }
   if (sizeof(money_arrays[1]) == 0) {
      no_good = 0;
   } else  {
#ifdef USE_VAULT
     no_good = MONEY_VAULT->get_money_ob();
#else
     no_good = clone_object(MONEY_OBJECT);
#endif
     no_good->set_money_array(money_arrays[1]);
   }
   return ({ good, no_good });
}
varargs mixed *filter_legal_money_to_array(mixed *m_array, string where) {
   int i;
   mixed *poss_values;
   mixed *good_array = ({ });
   mixed *no_good_array = ({ });
   if (sizeof(m_array) == 0) {
      return ({ ({ }), ({ }) });
   }
   if (!where || where == "") {
     where = "default";
   }
   if (!(poss_values = values[where])) {
      return ({ ({ }), copy(m_array) });
   }
   for (i = 0; i < sizeof(m_array); i += 2) {
      if (member_array(m_array[i], poss_values) != -1) {
         good_array += ({ m_array[i], m_array[i + 1] });
      } else {
         no_good_array += ({ m_array[i], m_array[i + 1] });
      }
   }
   return ({ good_array, no_good_array });
}
mixed *merge_money_arrays(mixed *m_array1, mixed *m_array2)  {
   int i;
   int idx;
   mixed *new_m_array;
   if (!m_array1)
      m_array1 = ({ });
   if (!m_array2)
      m_array2 = ({ });
   if (sizeof(m_array1) < sizeof(m_array2))  {
      new_m_array = copy(m_array2);
      for (i = 0; i < sizeof(m_array1); i += 2)  {
         idx = member_array(m_array1[i], new_m_array);
         if (idx > -1)  {
            new_m_array[idx + 1] += m_array1[i + 1];
            if (new_m_array[idx + 1] <= 0)
               new_m_array = delete(new_m_array, idx, 2);
         }
         else
            new_m_array += ({ m_array1[i], m_array1[i + 1] });
      }
   }
   else  {
      new_m_array = copy(m_array1);
      for (i = 0; i < sizeof(m_array2); i += 2)  {
         idx = member_array(m_array2[i], new_m_array);
         if (idx > -1)  {
            new_m_array[idx + 1] += m_array2[i + 1];
            if (new_m_array[idx + 1] <= 0)
               new_m_array = delete(new_m_array, idx, 2);
         }
         else
            new_m_array += ({ m_array2[i], m_array2[i + 1] });
      }
   }
   return new_m_array;
}
varargs mixed parse_money(string words, object player, string place) {
   object  thing;
   object *monies;
   object *things;
   mixed  *m_array;
   mixed  *m_array2;
   int     i;
   int     adjust_flag;
   things = match_objects_for_existence(words, ({ player }));
   if (sizeof(things) == 0) {
      m_array = money_array_from_string(words, place);
       if (sizeof(m_array) == 0) {
         return NO_MATCH;
      }
      thing = present(MONEY_ALIAS, player);
      if (!thing) {
         return NO_MATCH;
      }
      for (i = 0; i < sizeof(m_array); i += 2) {
         if (thing->query_money(m_array[i]) < m_array[i + 1]) {
            return NO_MATCH;
         }
      }
      adjust_flag = 1;
   }
   else {
      things = filter(things, (: $1->query_property("money") :));
      if (sizeof(things) == 0)
         return NO_MONEY;
      adjust_flag = 0;
      m_array = ({ });
      foreach (thing in things) {
         m_array = merge_money_arrays(m_array, thing->query_money_array());
#ifdef USE_VAULT
         MONEY_VAULT->add_to_list(thing);
#else
         thing->move("/room/rubbish");
#endif
      }
   }
   monies = filter_legal_money_array(m_array, place);
   if(monies[1])  {
      tell_object(player, monies[1]->the_short() +
            (monies[1]->query_number_coins() == 1 ? " is" : " are") +
            " not legal tender here.\n");
      m_array = monies[1]->query_money_array();
      if (!adjust_flag)
         this_player()->adjust_money(m_array);
#ifdef USE_VAULT
      MONEY_VAULT->add_to_list(monies[1]);
#else
      monies[1]->dest_me();
#endif
   }
   if (monies[0])  {
      if (adjust_flag)  {
         m_array2 = copy(monies[0]->query_money_array());
         for (i = 0; i < sizeof(m_array2); i += 2)
            m_array2[i + 1] = -m_array2[i + 1];
         this_player()->adjust_money(m_array2);
      }
      return monies[0];
   }
   else  {
      return NO_LEGAL;
   }
}
mixed *query_person_payments(int value, string place,
                             object payer, object payee) {
   mixed *stuff;
   mixed *mon_array;
   mixed *rabbit;
   mon_array = copy(payer->query_money_array());
   stuff = make_money_array_payment( 0, value, mon_array, place, 0);
   if (!stuff) {
      return 0;
   }
   if (stuff[MONEY_PAY_CHANGE]) {
      mon_array = copy(payee->query_money_array());
      rabbit = make_money_array_payment( 0, stuff[MONEY_PAY_CHANGE],
                                         mon_array, place, 0);
      if (!rabbit || rabbit[MONEY_PAY_CHANGE]) {
         return 0;
      }
      return ({ stuff[MONEY_PAY_RETURN], rabbit[MONEY_PAY_RETURN] });
   }
   return ({ stuff[MONEY_PAY_RETURN], ({ }) });
}
string * query_valid_types(){
  mixed *tmp;
  string *elem, *valid_types = ({ });
  int i;
  tmp = values(query_all_values());
  foreach( elem in tmp ){
    for( i = 0; i < sizeof( elem ); i += 2 ){
      if ( stringp( elem[i] ) )
        valid_types += ({ elem[i] });
    }
  } return valid_types;
}
string query_origin_of( string type ){
  string elem, *places;
  if( member_array( type, query_valid_types() ) == -1 )
    return 0;
  places = query_all_places();
  foreach( elem in places ){
    if( member_array( type,query_values_in( elem ) ) != -1 )
      return elem;
  }
}
string * query_aliases_of( string word ){
  string *types, elem, *aliases = ({ });
  types = query_valid_types();
  foreach( elem in types ){
    if( member_array( word,query_aliases_for( elem ) ) != -1 )
      aliases += ({ elem });
  } return aliases;
}
int query_value_of( string type ){
  if( member_array( type, query_valid_types() ) == -1 )
    return 0;
   return query_value( type, query_origin_of( type ) );
}
string smallest_in( string place ) {
   int i, smallest, r;
   mixed *values;
   values = query_values_in( place );
   smallest = values[1];
   r = 1;
   for ( i = 3; i < sizeof( values ); i += 2 ) {
      if ( values[i] < smallest ) {
         smallest = values[i];
         r = i;
      }
   }
   return values[r-1];
}
int smallest_value_in( string place ) {
   int i, smallest;
   mixed *values;
   values = query_values_in( place );
   smallest = values[1];
   for ( i = 3; i < sizeof( values ); i += 2 ) {
      if ( values[i] < smallest ) {
         smallest = values[i];
      }
   }
   return smallest;
}
mapping query_mapped_values_in( string where ) {
   mapping values = ([]);
  mixed * array;
  int i;
   if ( !where || ( where == "" ) )
      where = "default";
  array = query_values_in(where);
   for ( i = 1; i < sizeof(array); i += 2 )
  {
      values += ([array[i-1]:array[i]]);
   }
   return values;
}