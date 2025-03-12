class theft_callback {
     string func_name;
     string path;
}
class theft_callback *calls = ({ });
void event_theft( object command_ob, object thief, object victim,
                  object *stolen ) {
  if ( !sizeof( calls ) )
    return;
  if ( !stolen ) {
    foreach( class theft_callback temp in calls ) {
      if ( stringp( temp->path ) && stringp( temp->func_name ) )
        call_other( temp->path, temp->func_name, this_object(), thief, victim );
    }
  }
  return;
}
int add_theft_callback( string func_name, string path ) {
class theft_callback temp = new( class theft_callback, func_name: func_name,
  path: path );
  if ( !stringp( func_name ) || !stringp( path ) )
    return -1;
  debug_printf( "Added theft callback: %s %s.\n", func_name, path );
  calls += ({ temp });
  return sizeof( calls ) - 1;
}
int remove_theft_callback( int id ) {
  if ( id >= sizeof( calls ) || id < 0 )
    return -1;
  debug_printf( "Deleting callback: %s %s.\n", calls[id]->func_name,
    calls[id]->path );
  calls -= ({ calls[id] });
  return 1;
}
string query_theft_callbacks() {
string ret = "";
int count = 0;
  if ( !sizeof( calls ) )
    return "No theft callbacks found!\n";
  foreach( class theft_callback temp in calls ) {
    ret += sprintf( "%d. %s: %s.\n", count, temp->func_name, temp->path );
    count++;
  }
  return ret;
}