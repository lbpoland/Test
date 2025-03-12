#include <shops/pub_shop.h>
#include <armoury.h>
#include <money.h>
#include <move_failures.h>
#include <map.h>
inherit "/std/shops/inherit/open_shop";
inherit "/std/shops/inherit/shop_event";
void add_hidden_object(object ob);
private mapping _menu_items;
private mapping _menu_aliases;
private string _menu_header;
private string _language;
private int _display_header;
private string *_menu_subheadings;
private int _display_subheadings;
private int no_standard_alias;
private object _menu_object;
private object _counter;
void add_menu_alias( mixed alias, string actual );
string *calc_standard_aliases( string *aliases );
int do_buy( object *obs, string dir, string indir, mixed *args );
float query_discount( object ob );
object make_counter();
void create() {
   shop_event::create();
   _menu_items = ([ ]);
   _menu_aliases = ([ ]);
   _menu_header = "The menu reads:";
   _display_header = 1;
   _menu_subheadings = ({ "Appetisers", "Main Courses", "Desserts",
                         "Alcoholic Beverages", "Soft Drinks",
                         "Hot Drinks" });
   _display_subheadings = 1;
   if( base_name( this_object() ) + ".c" != __FILE__ ) {
      _menu_object = clone_object( PUB_MENU_FILE );
      _menu_object->set_pub( this_object() );
      add_hidden_object( _menu_object );
      _counter = make_counter();
   }
}
void init() {
   this_player()->add_command( "buy", this_object(), "<string>" );
   this_player()->add_command( "buy", this_object(),
                     "<string> for <indirect:living:here>" );
   this_player()->add_command( "order", this_object(), "<string>",
                     (: do_buy( $1, $2, $3, $4 ) :) );
   this_player()->add_command( "order", this_object(),
                     "<string> for <indirect:living:here>",
                     (: do_buy( $1, $2, $3, $4 ) :) );
}
varargs void add_menu_item(
   string name,
   int type,
   int cost,
   string item,
   string container,
   int volume,
   int intox
) {
   class menu_item new_item;
   string noun, alias;
   string *adjectives, *aliases;
   if( intox < 0 )
      intox = 0;
   if( intox > 10 )
      intox = 10;
   new_item = new( class menu_item );
   new_item->type = type;
   new_item->cost = cost;
   new_item->item = item;
   new_item->container = container;
   new_item->volume = volume;
   new_item->intox = intox;
   _menu_items[name] = new_item;
   if( no_standard_alias ) {
      if( lower_case( name ) != name )
         add_menu_alias( lower_case( name ), name );
      return;
   }
   adjectives = explode( lower_case( name ), " " );
   noun = adjectives[sizeof(adjectives) - 1];
   adjectives = adjectives[0..sizeof(adjectives) - 2];
   aliases = calc_standard_aliases( adjectives );
   foreach( alias in aliases ) {
      add_menu_alias( implode( ({ alias, noun }), " " ), name );
   }
}
string *calc_standard_aliases( string *array ) {
   int i, num_aliases;
   string *new_alias, *aliases;
   if( !sizeof( array ) )
      return ({ 0 });
   if( sizeof( array ) == 1 )
      return ({ array[0], 0 });
   aliases = calc_standard_aliases( array[0..sizeof( array ) - 2] );
   num_aliases = sizeof( aliases );
   for( i = 0; i < num_aliases; i++ ) {
      new_alias = ({ aliases[i], array[ sizeof( array ) - 1] });
      aliases += ({ implode( new_alias, " " ) });
   }
   return aliases;
}
mapping query_menu_items() {
   return _menu_items;
}
int query_pub() {
   return 1;
}
void set_language(string language) {
   _language = language;
}
string query_language() {
   return _language;
}
int remove_menu_item( string name ) {
   if( !_menu_items[name] ) {
      return 0;
   }
   map_delete( _menu_items, name );
   return 1;
}
string string_menu( string *items ) {
   int loop;
   string str, place;
   str = "";
   place = this_object()->query_property( "place" );
   if( !place || ( place == "" ) ) {
      place = "default";
   }
   for( loop = 0; loop < sizeof(items); loop++ ) {
      str += sprintf( "    %-30s %s\n", items[loop],
             MONEY_HAND->money_value_string(
             _menu_items[items[loop]]->cost, place ) );
   }
   return str;
}
string *query_items_of_type( int type ) {
   int i;
   string *selected;
   string *items;
   selected = ({ });
   items = keys( _menu_items );
   for( i = 0; i < sizeof(items); i++ ) {
      if( _menu_items[items[i]]->type == type ) {
         selected += ({ items[i] });
      }
   }
   selected = sort_array( selected, (: _menu_items[$1]->cost -
                                       _menu_items[$2]->cost :) );
   return selected;
}
string string_menu_of_type( int type ) {
   string str;
   string *items;
   items = query_items_of_type( type );
   if( !sizeof(items) ) {
      return "";
   }
   if( _display_subheadings ) {
      str = _menu_subheadings[ type ] + "\n";
   }
   str += string_menu( items );
   return sprintf( "%-=*s\n", (int)this_player()->query_cols(), str );
}
string read() {
   string ret;
   ret = "\n";
   if( _display_header ) {
      ret += _menu_header + "\n";
   }
   ret += string_menu_of_type( PUB_APPETISER );
   ret += string_menu_of_type( PUB_MAINCOURSE );
   ret += string_menu_of_type( PUB_DESSERT );
   ret += string_menu_of_type( PUB_ALCOHOL );
   ret += string_menu_of_type( PUB_SOFTDRINK );
   ret += string_menu_of_type( PUB_HOTDRINK );
   return ret;
}
void set_display_header( int value ) {
   _display_header = value;
}
int query_display_header() {
   return _display_header;
}
void set_menu_header( string header ) {
   _menu_header = header;
}
string query_menu_header() {
   return _menu_header;
}
void set_display_subheadings( int value ) {
   _display_subheadings = value;
}
int query_display_subheadings() {
   return _display_subheadings;
}
void set_menu_subheadings( int subheading, string text ) {
   _menu_subheadings[ subheading ] = text;
}
string *query_menu_subheadings() {
   return _menu_subheadings;
}
void add_menu_alias( mixed alias, string actual ) {
   string bing;
   if (arrayp(alias)) {
      foreach (bing in alias) {
         add_menu_alias(bing, actual);
      }
   }
   _menu_aliases[alias] = actual;
}
void add_menu_aliases( string *aliases, string actual ) {
   string alias;
   foreach( alias in aliases ) {
      add_menu_alias( alias, actual );
   }
}
mapping query_menu_aliases() {
   return _menu_aliases;
}
int remove_menu_alias( string alias ) {
   if( !_menu_aliases[alias] ) {
      return 0;
   }
   map_delete( _menu_aliases, alias );
   return 1;
}
void set_no_standard_alias( int flag ) {
   no_standard_alias = flag;
}
int query_no_standard_alias() {
   return no_standard_alias;
}
object create_real_object( string name ) {
   object item, container;
   if( _menu_items[name]->container ) {
      container = this_object()->create_container(
                                    _menu_items[name]->container );
      if( !container ) {
         container = clone_object( _menu_items[name]->container );
      }
      if( !container ) {
         container = ARMOURY->request_item(
                                 _menu_items[name]->container, 100 );
      }
   }
   if( _menu_items[name]->item ) {
      item = this_object()->create_item( _menu_items[name]->item );
      if( !item ) {
         item = clone_object( _menu_items[name]->item );
      }
      if( !item ) {
         item = ARMOURY->request_item( _menu_items[name]->item, 100 );
      }
   }
   if( item && _menu_items[name]->volume ) {
      item->set_amount( _menu_items[name]->volume );
   } else if ( item && !_menu_items[name]->volume &&
              ( _menu_items[name]->type == PUB_ALCOHOL ||
                _menu_items[name]->type == PUB_HOTDRINK ||
                _menu_items[name]->type == PUB_SOFTDRINK ) ) {
      item->set_amount( container->query_max_volume() -
                        container->query_volume() );
   }
   if( item && container ) {
      if( (int)item->move( container ) != MOVE_OK ) {
         write( "The " + container->short() + " is too small to hold " +
            item->the_short() + ".  Please file a bug report.\n" );
         item->move( "/room/rubbish" );
      }
   }
   if( container ) {
      return container;
   }
   if( item ) {
      return item;
   }
   return 0;
}
int do_buy( object *obs, string dir, string indir, mixed *args ) {
   int value, cost;
   string str, place;
   object person, thing;
   object *succeededpeople, *deadpeople, *failedpeople, *poorpeople;
   succeededpeople = ({ });
   deadpeople = ({ });
   failedpeople = ({ });
   poorpeople = ({ });
   str = args[0];
   if( this_player()->query_property( "dead" ) ) {
      add_failed_mess( "How can you expect to buy " + str + " when you're "
         "dead?\n" );
      return 0;
   }
   if( _menu_aliases[str] ) {
      str = _menu_aliases[str];
   }
   if( !_menu_items[str] ) {
      if (!broadcast_shop_event(PUB_EVENT_NOT_AVAILABLE, this_player(), str)) {
         add_failed_mess( "Sorry, " + str + " is not on the menu.\n" );
      }
      return 0;
   }
   if ( !is_open( this_player(), _menu_items[str]->type ) ) {
      broadcast_shop_event(PUB_EVENT_NOT_OPEN, this_player());
      return 0;
   }
   if( !sizeof( obs ) ) {
      obs = ({ this_player() });
   }
   foreach( person in obs ) {
      if( person->query_property( "dead" ) ) {
         deadpeople += ({ person });
         continue;
      }
      if( !living( person ) ||
          !interactive( person ) && !person->query_property( "npc" ) ) {
         failedpeople += ({ person });
         continue;
      }
      cost = ( _menu_items[str]->cost ) * query_discount( this_player() );
      place = this_object()->query_property( "place" );
      if( !place || ( place == "" ) ) {
         place = "default";
      }
      value = (int)this_player()->query_value_in( place );
      if( place != "default" ) {
         value += (int)this_player()->query_value_in( "default" );
      }
      if( cost > value ) {
         poorpeople += ({ person });
         continue;
      }
      thing = create_real_object( str );
      if( !thing ) {
         add_failed_mess( "Something is buggered.  Please file a bug report.  "
            "Thank you.\n" );
         return 0;
      }
      this_player()->pay_money( (mixed *)MONEY_HAND->create_money_array(
                        cost, place ), place );
      succeededpeople += ({ person });
      if( (int)thing->move( person ) != MOVE_OK ) {
         if( (int)thing->move( _counter ) != MOVE_OK ) {
            thing->move( this_object() );
            write("You cannot pick " + thing->a_short() +
               " up.  It's left on the floor for you.\n" );
         } else {
           write("You cannot pick " + thing->a_short() +
              " up.  It's left on the counter for you.\n" );
         }
      }
   }
   if( sizeof( succeededpeople ) ) {
      if (!broadcast_shop_event(PUB_EVENT_BOUGHT_STUFF, this_player(),
                           succeededpeople, str)) {
         if( !MAP_HANDLER->compare_arrays( succeededpeople,
                                           ({ this_player() }) ) ) {
            this_player()->add_succeeded_mess( this_object(),
               "$N $V $I.\n", ({ add_a(str) }) );
         } else {
            add_succeeded_mess("$N $V "
               + query_multiple_short( ({ thing }), "a" ) + " for $I.\n",
               succeededpeople);
         }
      }
   } else {
      if( sizeof( deadpeople ) ) {
         if (!broadcast_shop_event(PUB_EVENT_DEAD_PEOPLE, this_player(),
                              deadpeople, str)) {
            add_failed_mess("What use " +
               ( sizeof( deadpeople ) > 1?"have ":"has " ) +
               query_multiple_short( deadpeople, "one" ) + " got for " + str +
               "?\n" );
         }
      }
      if( sizeof( failedpeople ) ) {
         if (!broadcast_shop_event(PUB_EVENT_FAILED_PEOPLE, this_player(),
                              failedpeople, str)) {
            add_failed_mess("You can't buy anything for " +
               query_multiple_short( failedpeople, "one" ) + ".\n" );
         }
      }
      if( sizeof( poorpeople ) ) {
         if (!broadcast_shop_event(PUB_EVENT_POOR_PERSON, this_player(),
                              poorpeople, str)) {
            add_failed_mess("You cannot afford to order " + str +
               " for " + query_multiple_short( poorpeople, "one" ) + ".\n" );
         }
      }
      return 0;
   }
   return 1;
}
void dest_me() {
   if( _menu_object ) {
      _menu_object->dest_me();
   }
}
float query_discount( object ob ) {
   return 1.0;
}
object make_counter() {
   object ob;
   ob = clone_object( PUB_COUNTER_FILE );
   add_hidden_object( ob );
   return ob;
}
object query_counter() {
   return _counter;
}
object query_menu() {
   return _menu_object;
}