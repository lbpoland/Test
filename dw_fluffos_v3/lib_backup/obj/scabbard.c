#include <move_failures.h>
#include <virtual.h>
inherit "/std/container";
inherit "/std/basic/wearable";
string sheath;
string * types;
int _no_types_in_long;
void create() {
   do_setup++;
   container::create();
   wearable::create();
   do_setup--;
   sheath = "";
   types = ({ });
   _no_types_in_long = 0;
   add_alias( "scabbard" );
   add_plural( "scabbards" );
   if ( !query_property( "shop type" ) )
      add_property( "shop type", "armoury" );
   if ( !do_setup )
      this_object()->setup();
}
int query_scabbard() { return 1; }
string *query_types() { return types; }
void set_types( string *words ) {
   types = words;
   switch ( sizeof( types ) ) {
      case 0 :
         sheath = "";
         return;
      case 1 :
         sheath = "It could sheathe "+ add_a( types[ 0 ] ) +".\n";
         return;
      case 2 :
         sheath = "It could sheathe "+ add_a( types[ 0 ] ) +" or "+
               types[ 1 ] +".\n";
         return;
      default :
         sheath = "It could sheathe "+ add_a( types[ 0 ] ) +", "+
               implode( types[ 2 .. ], ", " ) +" or "+ types[ 1 ] +
               ".\n";
   }
}
int test_type_ok( object thing, int flag ) {
  foreach( string word in types ) {
    if( thing->full_id( word ) )
      return ::test_add( thing, flag );
  }
  return 0;
}
varargs int test_add( object thing, int flag, int noprint ) {
   int foo;
   if(flag)
      return 0;
   if( !environment( thing ) )
      return ::test_add( thing, flag );
   if( first_inventory( this_object() ) ) {
      if( !noprint )
         write( the_short() + " already holds " +
           first_inventory( this_object() )->a_short() + ".\n" );
      return 0;
   }
   foo = test_type_ok( thing, flag );
   if(foo)
      return foo;
   if( !noprint )
      write( thing->the_short() + " doesn't fit very well in "
        + the_short() + ".  " + sheath );
   return 0;
}
string long( string word, int dark ) {
   string foo = _no_types_in_long ? "" : sheath;
   if ( dark == 2 || dark == -2) {
      return container::long( word, dark );
   }
   return container::long( word, dark ) + foo +
         query_contents( "$C$"+ the_short() +" contains: " ) +
         wearable::long( word, dark );
}
int query_ac( string type, int amount ) {
   do_damage( type, amount );
}
void setup_scabbard( int number ) {
   set_max_cond( number );
   set_cond( number );
   set_lowest_cond( number );
}
int query_value() {
   return modify_value( container::query_value() );
}
int query_full_value() { return container::query_value(); }
int drop(mixed dest) {
   if ( worn_by )
      if ( living( worn_by ) )
         return 1;
   return container::drop(dest);
}
varargs int move( mixed dest, string messin, string messout ) {
   int flag;
   flag = container::move( dest, messin, messout );
   if ( ( flag == MOVE_OK ) && worn_by )
      set_worn_by( 0 );
   return flag;
}
void dest_me() {
   set_worn_by( 0 );
   container::dest_me();
}
void break_me() {
   if ( worn_by )
      all_inventory()->move( environment( worn_by ), "$N fall$s from "+
            a_short() +"." );
   else
      all_inventory()->move( environment(), "$N fall$s out of "+
            a_short() +"." );
   ::break_me();
}
mixed *stats() {
   return container::stats() + wearable::stats();
}
mapping query_static_auto_load() {
   if ( explode( file_name( this_object() ), "#" )[ 0 ] != "/obj/scabbard" )
      return ([ ]);
   return ([
      "::" : container::int_query_static_auto_load(),
      "wear" : wearable::query_static_auto_load(),
      "types" : types,
      "_no_types_in_long" : _no_types_in_long,
   ]);
}
mapping query_dynamic_auto_load() {
   return ([
      "::" : container::query_dynamic_auto_load(),
      "wear" : wearable::query_dynamic_auto_load()
   ]);
}
void init_static_arg( mapping map ) {
   if ( !mapp( map ) )
      return;
   if ( map[ "::" ] )
      container::init_static_arg( map[ "::" ] );
   if ( map[ "wear" ] )
      wearable::init_static_arg( map[ "wear" ] );
   if ( pointerp( map[ "types" ] ) )
      set_types( map[ "types" ] );
   if ( map[ "_no_types_in_long" ] )
      _no_types_in_long = map[ "_no_types_in_long" ];
}
void init_dynamic_arg( mapping map, object ob ) {
   mapping stat_temp;
   string virt_name, new_name;
   if ( map[ "::" ] )
      container::init_dynamic_arg( map[ "::" ], ob );
   if ( map[ "wear" ] )
      wearable::init_dynamic_arg( map[ "wear" ], ob );
   if( virt_name = query_property( VIRTUAL_NAME_PROP ) ) {
     if( file_size( virt_name ) == -1 ) {
       new_name = ( CLONER )->other_file( virt_name );
       if( stringp( new_name ) && ( new_name != virt_name ) ) {
         add_property( VIRTUAL_NAME_PROP, new_name );
         virt_name = new_name;
       } else {
         if( VIRTUAL_HANDLER->query_forbidden( virt_name ) ) {
           call_out( "replace_me", 1 );
         } else {
           VIRTUAL_HANDLER->add_missing( virt_name );
         }
       }
     }
     if( file_size( virt_name ) != -1 &&
         query_property( "virtual time" ) < stat( virt_name )[1] ) {
       stat_temp = ( VIRTUAL_HANDLER )->new_data( virt_name );
       if( mapp( stat_temp ) ) {
         init_static_arg( stat_temp );
         add_property( "virtual time", time() );
       }
     }
   }
}
int no_types_in_long() {
   return _no_types_in_long;
}
int set_no_types_in_long( int val ) {
   _no_types_in_long = val ? 1 : 0;
   return _no_types_in_long;
}