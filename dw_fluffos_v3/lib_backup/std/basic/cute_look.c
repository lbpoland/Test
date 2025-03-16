#include <position.h>
#define NEW_PROCESS_NON_LIVING 1
mixed *process_living( object *int_livings );
string process_non_living( object *int_non_livings, int start );
void set_ignore_livings_in_inventory( int ignore );
int ignore_livings_in_inventory();
private nosave int _ignore_livings = 1;
int env_check(object ob) { return environment(ob) == this_object(); }
int living_check(object ob) { return living(ob); }
mixed there_check(object ob) { return ob->query_property("there"); }
varargs string query_contents( string start, object *things,
  int ignore_living) {
    object *livings = ({ }), *non_livings = ({ });
    mixed *bits;
    string return_string = "";
    int groups;
    if( undefinedp( ignore_living ) )
        ignore_living = ignore_livings_in_inventory();
    if ( stringp( start ) ) return_string = start;
    if ( !arrayp( things ) ) {
        things = this_object()->find_inv_match( "", this_player() );
        things -= ({ this_player() });
        things = filter_array( things, "env_check", this_object());
    }
    if ( !sizeof( things ) )
        return "";
    if (!ignore_living) {
        livings = filter(things, "living_check", this_object());
        non_livings = things - livings;
    } else non_livings = things;
    if ( sizeof( livings ) ) {
        bits = process_living( livings );
        return_string += bits[ 0 ];
        groups = bits[1];
    }
    if ( sizeof( non_livings ) ) {
        return_string += process_non_living( non_livings, groups );
    }
    if(return_string == "")
        return return_string;
    else
        return  return_string = this_player()->colour_event("inventory", "") +
        return_string[0..<2] + "%^RESET%^\n";
}
mixed *process_living( object *int_livings ) {
  int i;
  mapping positions = ([ ]);
  object live_temp;
  string my_pos, int_ret_string = "", *all_positions, current_pos, ministring;
  foreach( live_temp in int_livings ) {
    if ( undefinedp( my_pos = live_temp->query_position_short() ) )
      my_pos = POSITION_DEFAULT;
    if ( undefinedp( positions[ my_pos ] ) )
      positions[ my_pos ] = ({ live_temp });
    else
      positions[ my_pos ] += ({ live_temp });
  }
  all_positions = keys( positions );
  i = 0;
  foreach( current_pos in all_positions ) {
    if(i==0) {
      ministring = "$C$$M$";
    } else {
      ministring = "$M$";
    }
    foreach( live_temp in positions[ current_pos ] ) {
      if ( !live_temp->query_visible( this_player() ) ) {
        continue;
      }
      ministring += live_temp->a_short();
    }
    if (!positions[current_pos][0]->query_position_dont_use_is_are()) {
      if ( sizeof( positions[ current_pos ] ) > 1 ||
           positions[ current_pos ][0]->group_object() ) {
        if ( positions[ current_pos ][0]->query_position_multiple() ) {
          ministring += "$M$ are each " + current_pos;
        } else {
          ministring += "$M$ are " + current_pos;
        }
      } else {
        ministring += "$M$ is " + current_pos;
      }
    } else {
      ministring += "$M$ " + current_pos;
    }
    switch( current_pos ) {
    case SITTING:
    case STANDING:
    case KNEELING:
    case SWIMMING:
    case LYING:
    case MEDITATING:
    case CROUCHING:
      ministring += " here";
    default:
      i++;
      if(i<sizeof(all_positions)-1)
        ministring += ", ";
      else if(i<sizeof(all_positions))
        ministring += " and ";
      else
        ministring += ".\n";
      int_ret_string += ministring;
      continue;
    }
  }
  return ({ int_ret_string, sizeof( all_positions ) }) ;
}
string process_non_living( object *non_livings, int start ) {
  mapping positions;
  string position;
  object *items, item, *bulk;
  string here;
  string *room_items;
  int i;
  if(!sizeof(non_livings))
    return "";
  here = this_object()->query_property( "here" );
  if (!here)
    return query_multiple_short( non_livings ) + ".\n";
  positions = unique_mapping( non_livings, "there_check", this_object());
  if ( positions[ 0 ] ) {
    positions[ here ] = positions[ 0 ];
    map_delete( positions, 0 );
  }
  i = start;
  room_items = ({ });
  foreach( position, items in positions ) {
    bulk = ({ });
    foreach( item in items ) {
      if( ( ( item->query_continuous() || item->query_collective() ) &&
         item->query_how_many() > 1 ) || item->query_are_override() )
      {
        if( item->query_short() == item->query_plural() )
          room_items += ({ item->a_short() + " is " + position });
        else
          room_items += ({ item->a_short() + " are " + position });
      } else {
        bulk += ({ item });
      }
    }
    if ( sizeof( bulk ) ) {
      room_items += ({ "$M$" + implode( bulk->a_short(), "" ) +
                         "$M$ " + "$V$" + i + "=is,are$V$ " + position });
    }
    i++;
  }
  return "$C$" + query_multiple_short( room_items ) + ".\n";
}
void list_contents( string words ) { write( query_contents( words ) ); }
int query_last() {
    log_file( "CUTELAST", "(%s) %s called query_last.\n",
      ctime( time() ), file_name( this_object() ) );
    return 0;
}
void adjust_last( int wibble ) {
    log_file( "CUTELAST", "(%s) %s called adjust_last.\n",
      ctime( time() ), file_name( this_object() ) );
    return;
}
void set_ignore_livings_in_inventory( int ignore ) {
  _ignore_livings = !!ignore;
}
int ignore_livings_in_inventory() { return _ignore_livings; }