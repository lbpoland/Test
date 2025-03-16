#define SKILL "other.perception"
private nosave mapping _hide_invis;
void create() {
  _hide_invis = ([]);
}
mapping query_hide_invis() {
  return copy( _hide_invis );
}
int add_hide_invis( string type, object who, mixed see, string *gone ) {
  if( _hide_invis[type] ) {
    return 0;
  }
  _hide_invis[type] = ({ who, see, gone });
  if( environment( this_object() ) ) {
    event( environment( this_object() ), "hide_invis", 1, type, 0 );
  }
  return 1;
}
varargs int remove_hide_invis( string type, int quiet ) {
  mixed *gone;
  if( !_hide_invis[type] ) {
    return 0;
  }
  gone = _hide_invis[type][2];
  if( sizeof( gone ) == 2 && gone[0] )
    if( quiet )
      call_other( gone[0], gone[1], quiet );
    else
      call_other( gone[0], gone[1] );
  map_delete( _hide_invis, type );
  if( environment( this_object() ) ) {
    event( environment( this_object() ), "hide_invis", 0, type, quiet );
  }
  return 1;
}
int perception_check( object thing ) {
  int perception;
  perception = thing->query_skill_bonus( SKILL );
  if( !environment( thing ) || !perception )
    return perception;
  switch( thing->check_dark( (int)environment( thing )->query_light() ) ) {
    case -2:
    case 2:
      perception /= 4;
      break;
    case -1:
    case 1:
      perception /= 2;
      break;
    default:
      break;
  }
  return perception;
}
int query_visible( object thing ) {
  int i;
  string *types;
  mixed see;
  if( thing == this_object() ) {
    return 1;
  }
  if( thing->query_creator() || thing->query_property( "demon" ) ) {
    return 1;
  }
  if( thing->query_blinded() ) {
    return 0;
  }
  types = keys( _hide_invis );
  if( !sizeof( types ) ) {
    return 1;
  }
  for( i = 0; i < sizeof( types ); i++ ) {
    if( _hide_invis[types[i]][0] == thing ) {
      continue;
    }
    see = _hide_invis[types[i]][1];
    if( intp( see ) ) {
      if( perception_check( thing ) > see ) {
        continue;
      }
      return 0;
    }
    if( stringp( see ) ) {
      if( call_other( thing, see ) ) {
        continue;
      }
      return 0;
    }
    return 0;
  }
  return 1;
}
string hide_invis_string() {
  int i;
  string list;
  string *types;
  types = keys( _hide_invis );
  if( !sizeof( types ) ) {
    return "";
  }
  list = "";
  for( i = 0; i < sizeof( types ); i++ ) {
    list += " ("+ types[i] +")";
  }
  return list;
}