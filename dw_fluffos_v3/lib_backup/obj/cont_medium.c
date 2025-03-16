#include <move_failures.h>
#include <parse_command.h>
#include <obj_parser.h>
inherit "/std/object";
private int amount;
private int continuous;
private int collective;
private nosave string my_filename;
private int *weight_unit;
private nosave int no_join;
private float value_scale;
private string medium_alias;
private string pile_name;
private string *_sorted_amount_names;
private mapping amount_types;
private mixed *pile_types;
private nosave mixed _short_name;
object make_medium_clone( int number );
void create() {
  int junk;
  do_setup++;
  ::create();
  do_setup--;
  continuous = 0;
  collective = 0;
  weight_unit = ({ 1, 200 });
  pile_name = "pile";
  if ( !do_setup )
    this_object()->setup();
  if( !clonep( this_object() ) )
    return;
  sscanf( file_name( this_object() ), "%s#%d", my_filename, junk );
  amount = 1;
}
void set_name( string word ) {
  ::set_name( word );
  if ( continuous )
    add_plural( word );
}
int query_amount() { return amount; }
void set_amount( int number ) {
  if(environment() && continuous)
    environment()->add_volume(number - amount);
  amount = number;
  if(continuous || collective)
    set_weight((amount * weight_unit[ 0 ] ) / weight_unit[ 1 ]);
}
void adjust_amount(int number) {
  if(environment() && continuous)
    environment()->add_volume(number);
  amount += number;
  if(amount < 1) {
    no_join = 1;
    move( "/room/rubbish" );
    return;
  }
  if(continuous || collective)
    set_weight((amount * weight_unit[0]) / weight_unit[1]);
}
int query_continuous() { return continuous; }
int query_collective() { return collective; }
int query_merger() { return 1; }
void set_continuous() {
  collective = 0;
  if (continuous) {
    return;
  }
  if ( environment() ) {
    environment()->add_volume( -200*query_weight() );
  }
  continuous = 1;
  if(environment()) {
    environment()->add_volume( amount );
  }
}
void reset_continuous() {
  if (!continuous) {
    return;
  }
  continuous = 0;
  if ( environment() ) {
    environment()->add_volume( -amount );
  }
}
void set_collective() {
  collective = 1;
  continuous = 0;
  add_property( "determinate", "" );
}
void reset_collective() {
  collective = 0;
}
int *query_weight_unit() { return weight_unit; }
void set_weight_unit( int *numbers ) { weight_unit = numbers; }
int query_no_join() { return no_join; }
void set_no_join() { no_join = 1; }
void reset_no_join() { no_join = 0; }
string query_medium_alias() { return medium_alias; }
void set_medium_alias( string word ) {
   medium_alias = word;
   add_alias( medium_alias );
}
string query_pile_name() { return pile_name; }
void set_pile_name( string word ) { pile_name = word; }
mapping query_amount_types() { return amount_types; }
void set_amount_types( mapping map ) {
  amount_types = map;
  _sorted_amount_names = sort_array(m_indices( amount_types ),
      (: amount_types[$1][0] - amount_types[$2][0] :));
}
mixed query_pile_types() { return pile_types; }
void set_pile_types( mixed *args ) { pile_types = args; }
int query_max_seen() { return 12; }
int query_value() {
  if (!floatp(value_scale) || !continuous) {
    if(collective)
      return (amount * ::query_value() );
    return ::query_value();
  }
  return to_int(::query_value() * value_scale * amount);
}
void set_value_scale(float f) { value_scale = f; }
float query_value_scale() { return value_scale; }
int query_how_many() {
  int biggest_amount;
  int how_many;
  string size;
  string biggest_size;
  if(!amount)
    return 0;
  if(!m_sizeof(amount_types)) {
    if(collective)
        return amount;
    return 0;
  }
  biggest_size = _sorted_amount_names[0];
  foreach (size in _sorted_amount_names) {
    if (amount < amount_types[size][0]) {
      break;
    }
    biggest_size = size;
  }
  biggest_amount = amount_types[biggest_size][0];
  how_many = ( amount + biggest_amount / 2 ) / biggest_amount;
  return how_many;
}
varargs string amount_size(int exact) {
   int biggest_amount;
   int how_many;
   string size;
   string biggest_size;
   string biggest_plural;
   if ( !amount ) {
      return "none at all";
   }
   if ( !m_sizeof( amount_types ) ) {
      return "minus one Cornish pint";
   }
   biggest_size = _sorted_amount_names[0];
   foreach (size in _sorted_amount_names) {
     if (amount < amount_types[size][0]) {
       break;
     }
     biggest_size = size;
   }
   biggest_amount = amount_types[biggest_size][0];
   biggest_plural = amount_types[biggest_size][1];
   how_many = ( amount + biggest_amount / 2 ) / biggest_amount;
   if ( !how_many ) {
      return "apparently not containing any "+ biggest_plural;
   }
   if ( how_many == 1 ) {
      return "about one "+ biggest_size;
   }
   if ( !exact  &&  how_many > query_max_seen() ) {
      return "more "+ biggest_plural +" than you can count";
   }
   return "about "+ query_num( how_many ) +" "+ biggest_plural;
}
string amount_size_short() {
   int biggest_amount;
   int how_many;
   string size;
   string biggest_size;
   string ret;
   string biggest_plural;
   if ( !amount || !sizeof( amount_types ) ||
        (query_property("determinate") == "some ") ) {
     if(collective)
       return query_num(amount, 20) + " ";
     return "";
   }
   if (_short_name && _short_name[0] == amount) {
      return _short_name[1];
   }
   biggest_size = _sorted_amount_names[0];
   foreach (size in _sorted_amount_names) {
     if (amount < amount_types[size][0]) {
       break;
     }
     biggest_size = size;
   }
   biggest_amount = amount_types[biggest_size][0];
   biggest_plural = amount_types[biggest_size][1];
   how_many = ( amount + biggest_amount / 2 ) / biggest_amount;
   if(!how_many) {
     if(collective)
       ret = query_num(amount) + " ";
     else
       ret = "a smidgeon of ";
   } else if(collective && amount < biggest_amount) {
     ret = query_num(amount) + " ";
   } else if(how_many == 1) {
     ret = "one "+ biggest_size + " of ";
   } else {
     ret = query_num( how_many, query_max_seen()) +" "+ biggest_plural +
       " of ";
   }
   _short_name = ({ amount, ret });
   return ret;
}
string pile_size() {
   int i;
   if ( !sizeof( pile_types ) ) {
      return "a surreal "+ pile_name;
   }
   for ( i = 0; i < ( sizeof( pile_types ) - 1 ); i += 2 ) {
      if ( amount <= pile_types[ i ] ) {
         return add_a( pile_types[ i + 1 ] ) +" "+ pile_name;
      }
   }
   return add_a( pile_types[ sizeof( pile_types ) - 1 ] ) +" "+ pile_name;
}
varargs string pretty_short( object thing ) {
  if(collective) {
    if(amount > 1)
      return pretty_plural(thing);
    else
      return add_a(::pretty_short(thing));
  }
  return amount_size_short() + ::pretty_short( thing );
}
varargs string pretty_plural( object thing ) {
  if(amount > 1)
    return amount_size_short() + ::pretty_plural( thing );
  return ::pretty_plural(thing);
}
#ifdef 0
string short(int dark) {
  string ret;
  ret = ::short( dark );
  if(!ret || ret == "something" || !collective)
    return(ret);
  if(amount == 1)
    return add_a(ret);
  return( query_num(amount, 9999 ) + " " + query_main_plural());
}
#endif
string long(string words, int dark ) {
  int i;
  string ret;
  string *bits;
  if(continuous)
    return replace( ::long( words, dark ),
                    ({ "$amount_size$", amount_size(),
                         "$pile_size$", pile_size() }) );
  ret = replace( ::long( words, dark ), "$N", short( dark ) );
  if(collective && amount > 1) {
    ret = replace( ret, ",$", "$comma_dollar$" );
    ret = replace( ret, ({ ",", " $spaced_comma$", ";", " $spaced_semi$",
        ":", " $spaced_colon$", ".", " $spaced_period$" }) );
    ret = replace( ret, "$comma_dollar$", ",$");
    bits = explode(ret, " ");
    for(i = 0; i < sizeof(bits); i++) {
        switch( bits[ i ] ) {
        case "This":
          bits[i] = "These";
          break;
        case "this":
          bits[i] = "these";
          break;
        case "is":
          bits[i] = "are";
          break;
        case "a":
        case "an":
          bits[i] = amount_size_short();
          bits[i] = bits[i][0..<2];
          break;
        case "it":
           bits[i] = "they";
           break;
        case "It":
           bits[i] = "They";
           break;
        case "its":
           bits[i] = "their";
           break;
        case "Its":
           bits[i] = "Their";
           break;
        case "$a":
        case "$an":
           bits[i] = bits[i][1..];
           break;
        default:
           if( bits[i][0..1] == "$V" ) {
              bits[i] = replace_string( bits[i], "$V", "" );
              bits[i] = explode( bits[i], "$" )[1];
           };
           if( bits[i][0..1] == "$P" ) {
              bits[i] = replace_string( bits[i], "$P", "" );
              bits[i] = pluralize( bits[i] );
           };
           if( bits[i][0..1] == "$A" ) {
              bits[i] = replace_string( bits[i], "$A", "" );
              bits[i] = pluralize( bits[i] );
           };
           if(strsrch(bits[i], query_plural(dark)) == -1)
               bits[i] = replace(bits[i], short(dark), query_plural(dark));
        }
      }
    ret = implode(bits, " ");
    ret = replace(ret, ({ " $spaced_comma$", ",", " $spaced_semi$", ";",
        " $spaced_colon$", ":", " $spaced_period$", "." })  );
  } else if( collective && amount == 1 ) {
     bits = explode(ret, " ");
     for(i = 0; i < sizeof(bits); i++) {
        if( bits[i][0..1] == "$V" ) {
           bits[i] = replace_string( bits[i], "$V", "" );
           bits[i] = explode( bits[i], "$" )[0];
        };
        if( bits[i][0..1] == "$P" ) {
           bits[i] = replace_string( bits[i], "$P", "" );
        };
        if( bits[i] == "$a" || bits[i] == "$an" ) {
           bits[i] = bits[i][1..];
        };
        if( bits[i][0..1] == "$A" ) {
           bits[i] = replace_string( bits[i], "$A", "" );
           bits[i] = add_a( bits[i] );
        };
     };
     ret = implode( bits, " " );
  };
  return ret;
}
string query_long(string words, int dark)  {
   return long(words, dark);
}
object new_collective(int number) {
  object ob;
  object place;
  ob = make_medium_clone(number);
  adjust_amount(-number);
  ob->set_no_join();
  if(environment()) {
    place = (object)environment()->query_property( "medium dest" );
    if(!place)
      place = environment();
    ob->move(place);
  }
  ob->reset_no_join();
  ob->call_out("merge", 1);
  return ob;
}
int merge_criteria(object ob) {
  return medium_alias == ob->query_medium_alias();
}
void merge() {
  object *obs;
  if(environment())
     obs = filter(all_inventory(environment()) - ({ this_object() }),
                  "merge_criteria", this_object());
  if(sizeof(obs) && objectp(obs[0])) {
    no_join = 1;
    move("/room/rubbish");
    obs[0]->adjust_amount(amount);
  }
  return;
}
varargs int move( mixed dest, string messin, string messout ) {
  int check;
  if((check = ::move(dest, messin, messout)) != MOVE_OK)
    return check;
  if(no_join || !medium_alias || (!continuous && !collective))
    return MOVE_OK;
  call_out("merge", 0);
  return MOVE_OK;
}
object make_medium_clone( int number ) {
   object medium;
   mapping map;
   medium = clone_object( explode( file_name( this_object() ), "#" )[ 0 ] );
   map = (mapping)this_object()->query_dynamic_auto_load();
   medium->init_dynamic_arg( map );
   map = (mapping)this_object()->query_static_auto_load();
   if ( map ) {
      medium->init_static_arg( map );
   }
   medium->set_amount( number );
   medium->set_enchant( query_enchant() * medium->query_max_enchant() /
                        query_max_enchant() );
   return medium;
}
object cont_query_parse_id( mixed *args ) {
   int i;
   string *sizes;
   object medium, place;
   if ( args[ P_THING ] < 0 ) {
      args[ P_THING ]++;
      if ( args[ P_THING ] ) {
         return 0;
      }
      args[ P_THING ] = -99999;
      return this_object();
   }
   sizes = m_indices( amount_types );
   if ( args[ P_THING ] == 1 ) {
      for ( i = 0; i < sizeof( sizes ); i++ ) {
         if ( member_array( sizes[ i ], explode( args[ P_STR ], " " ) ) !=
               -1 ) {
            if ( amount_types[ sizes[ i ] ][ 0 ] > amount ) {
               return 0;
            }
            medium = make_medium_clone( amount_types[ sizes[ i ] ][ 0 ] );
            place = (object)environment()->query_property( "medium dest" );
            if ( !place ) {
               place = environment();
            } else {
               remove_call_out( "no_env_move" );
               call_out( "dest_old_env", 1, environment() );
            }
            adjust_amount( -amount_types[ sizes[ i ] ][ 0 ] );
            this_object()->set_no_env_move( place );
            medium->move( place );
            args[ P_THING ] = -99999;
            return medium;
         }
      }
      args[ P_THING ] = -99999;
      return this_object();
   }
   for ( i = 0; i < sizeof( sizes ); i++ ) {
      if ( member_array( amount_types[ sizes[ i ] ][ 1 ],
            explode( args[ P_STR ], " " ) ) != -1 ) {
         if ( amount_types[ sizes[ i ] ][ 0 ] * args[ P_THING ] > amount ) {
               return 0;
         }
         medium = make_medium_clone( amount_types[ sizes[ i ] ][ 0 ] *
                args[ P_THING ] );
         place = (object)environment()->query_property( "medium dest" );
         if ( !place ) {
            place = environment();
         } else {
            remove_call_out( "no_env_move" );
            call_out( "dest_old_env", 1, environment() );
         }
         adjust_amount( -amount_types[ sizes[ i ] ][ 0 ] * args[ 0 ] );
         this_object()->set_no_env_move( place );
         medium->move( place );
         args[ P_THING ] = -99999;
         return medium;
      }
   }
   return 0;
}
object coll_query_parse_id( mixed *arr ) {
   string *bits;
   if((arr[0] < 0)) {
     return 0;
   }
   if(arr[0] == 0) {
     bits = explode( arr[ 1 ], " " );
     if(sizeof(bits) == 1) {
       if(bits[0] == query_main_plural()) {
         return this_object();
       }
     }
     if(member_array(bits[sizeof(bits) - 1 ], query_plurals()) == -1) {
       return this_object();
     }
     return 0;
   }
   if(id(arr[1])) {
     return new_collective(amount - arr[0]);
   }
}
object query_parse_id( mixed *args ) {
  if(continuous)
    return cont_query_parse_id(args);
  return coll_query_parse_id(args);
}
mixed* cont_parse_match_object(string* input, object player,
                               class obj_match_context context) {
   int result;
   string size;
   mixed* amt;
   int make_amt;
   int smallest;
   int num;
   object medium;
   object place;
   result = ::is_matching_object(input, player, context);
   if (!continuous || !result) {
      if (result) {
         if (update_parse_match_context(context, 1, result)) {
            return ({ result, ({ this_object() }) });
         }
      }
      return 0;
   }
   smallest = amount;
   foreach (size, amt in amount_types) {
      if ( member_array( size, input) != -1) {
         if ( amt[ 0 ] > amount ) {
            return 0;
         }
         make_amt = amt[0];
      } else if ( member_array( amt[1], input ) != -1 ) {
         if ( amt[ 0 ] > amount ) {
            return 0;
         }
         make_amt = amt[0];
      }
      if (smallest > amt[0]) {
         smallest = amt[0];
      }
   }
   if (!make_amt) {
     if(!amount)
       make_amt = 1;
     else
       make_amt = amount;
   }
   num = update_parse_match_context(context, (amount / make_amt), result);
   if (!num) {
      return 0;
   }
   make_amt *= num;
   if (context->fraction) {
      make_amt = (make_amt * context->fraction[0]) / context->fraction[1];
   }
   if (make_amt < smallest) {
      make_amt = smallest;
   }
   if (make_amt < amount) {
      medium = make_medium_clone( make_amt );
      place = (object)environment()->query_property( "medium dest" );
      if ( !place ) {
         place = environment();
      } else {
         remove_call_out( "no_env_move" );
         call_out( "dest_old_env", 1, environment() );
      }
      adjust_amount( -make_amt );
      this_object()->set_no_env_move( place );
      medium->move( place );
      return ({ result, ({ medium }) });
   }
   return ({ result, ({ this_object() }) });
}
mixed* coll_parse_match_object(string* input, object viewer,
                               class obj_match_context context) {
  int ret;
  int num;
  int make_amt;
  string size;
  mixed *amt;
  int smallest;
  ret = ::is_matching_object(input, viewer, context);
  if (!ret) {
    return 0;
  }
  if (sizeof(input) == 1 &&
      !context->number_included &&
      !context->ordinal &&
      (member_array(input[<1], query_plurals()) != -1 ||
       input[<1] == "all" || input[<1] == "thing")) {
    return ({ OBJ_PARSER_MATCH_PLURAL, ({ this_object() }) });
  }
  if(amount_types) {
    smallest = amount;
    foreach (size, amt in amount_types) {
      if(member_array( size, input) != -1) {
        if(amt[0] > amount) {
          return 0;
        }
        make_amt = amt[0];
        ret = OBJ_PARSER_MATCH_SINGULAR;
      } else if(member_array( amt[1], input ) != -1) {
        if(amt[ 0 ] > amount) {
          return 0;
        }
        make_amt = amt[0];
        ret = OBJ_PARSER_MATCH_PLURAL;
      }
      if (smallest > amt[0]) {
        smallest = amt[0];
      }
    }
  }
  if(!make_amt)
    make_amt = 1;
  num = update_parse_match_context(context, to_int(amount / make_amt), ret);
  if (!num)
    return 0;
  num *= make_amt;
  if (context->fraction) {
    num = (num  * context->fraction[0]) / context->fraction[1];
  }
  if(num < amount) {
    new_collective(amount - num);
    return ({ ret, ({ this_object() }) });
  }
  return ({ ret, ({ this_object() }) });
}
mixed *parse_match_object(string *input, object player,
                          class obj_match_context context) {
  if(continuous)
    return cont_parse_match_object(input, player, context);
  return coll_parse_match_object(input, player, context);
}
void set_no_env_move( object dest ) {
   object place;
   if ( file_name( environment() ) == "/room/rubbish" ) {
      return;
   }
   place = clone_object( "/std/container" );
   place->add_property( "medium dest", dest );
   move( place );
   call_out( "no_env_move", 0, dest, place );
}
void no_env_move( object dest, object place ) {
   if ( environment() == place ) {
      move( dest );
   }
   call_out( "dest_old_env", 1, place );
}
void dest_old_env( object place ) {
   if ( place ) {
      place->dest_me();
   }
}
mapping query_dynamic_auto_load() {
   return ([
      "::": ::query_dynamic_auto_load(),
      "continuous": continuous,
      "collective": collective,
      "amount": amount,
   ]);
}
void init_dynamic_arg( mapping map, object ) {
  if ( !mapp( map ) )
    return;
  if ( map[ "::" ] )
    ::init_dynamic_arg( map[ "::" ]);
  if ( map[ "amount" ] )
    set_amount( map[ "amount" ] );
  if ( !undefinedp( map[ "continuous" ] ) )
    if ( map[ "continuous" ] ) {
      set_continuous();
    } else {
      reset_continuous();
    }
  if(!undefinedp(map["collective"]))
    collective = map["collective"];
}
mapping int_query_static_auto_load() {
   return ([
      "::": ::int_query_static_auto_load(),
      "weight_unit": weight_unit,
      "medium_alias": medium_alias,
      "pile_name": pile_name,
      "amount_types": amount_types,
      "pile_types": pile_types,
      "value_scale": value_scale,
   ]);
}
mapping query_static_auto_load() {
  if ( base_name(this_object()) + ".c" == __FILE__ )
      return int_query_static_auto_load();
   return 0;
}
void init_static_arg( mapping map ) {
   if ( !mapp( map ) )
      return;
   if ( map[ "::" ] )
      ::init_static_arg( map[ "::" ] );
   if ( !undefinedp( map[ "medium_alias" ] ) )
      medium_alias = map[ "medium_alias" ];
   if ( pointerp( map[ "weight_unit" ] ) )
      weight_unit = map[ "weight_unit" ];
   if ( stringp( map[ "pile_name" ] ) )
      pile_name = map[ "pile_name" ];
   if ( mapp( map[ "amount_types" ] ) )
      set_amount_types(map[ "amount_types" ]);
   if ( pointerp( map[ "pile_types" ] ) )
      pile_types = map[ "pile_types" ];
   if ( floatp( map[ "value_scale" ] ) )
      value_scale = map[ "value_scale" ];
}
mixed *stats() {
   return ::stats() + ({
      ({ "amount", amount }),
      ({ "medium alias", medium_alias }),
      ({ "continuous", continuous }),
      ({ "collective", collective }),
      ({ "value scale", value_scale }),
   });
}