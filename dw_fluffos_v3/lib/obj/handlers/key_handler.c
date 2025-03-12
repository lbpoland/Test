#define RESTORE_PATH "/save/keys/"
inherit "/std/object";
mapping keys;
mapping key_names;
nosave string _current_group;
private void init_data( string group ) {
   keys = ([ ]);
   key_names = ([ ]);
}
private int get_data_file( string group ) {
   if (_current_group == group) {
      return 1;
   }
   _current_group = group;
   if ( file_size( RESTORE_PATH + group +".o" ) > 0 ) {
      unguarded((: restore_object, RESTORE_PATH + group :));
   } else {
      init_data( group );
      return 0;
   }
   return 1;
}
private void save_data_file( ) {
   unguarded((: save_object, RESTORE_PATH + _current_group :));
}
mapping query_all_keys( string group ) {
   get_data_file( group );
   return keys;
}
private void set_keys( string group, mapping list ) {
   get_data_file( group );
   keys = list;
   save_data_file( );
}
string *query_all_key_permissions( string group, string key ) {
   get_data_file( group );
   if ( !keys[ key ] ) {
      return ({ });
   }
   return keys[ key ];
}
void set_key_permissions( string group, string key, string *types ) {
   get_data_file( group );
   if (sizeof(types)) {
      keys[ key ] = types;
   } else {
      map_delete(keys, key);
   }
   save_data_file( );
}
int query_key_permission( string group, string key, string type ) {
   get_data_file( group );
   if ( !keys[ key ] ) {
      return 0;
   }
   if ( member_array( type, keys[ key ] ) == -1 ) {
      return 0;
   }
   return 1;
}
int add_key_permission( string group, string key, string type ) {
   get_data_file( group );
   if ( !keys[ key ] ) {
       keys[ key ] = ({ });
   }
   if ( member_array( type, keys[ key ] ) != -1 ) {
      return 0;
   }
   keys[ key ] += ({ type });
   save_data_file( );
   return 1;
}
int remove_key_permission( string group, string key, string type ) {
   int i;
   get_data_file( group );
   if ( !keys[ key ] ) {
      return 0;
   }
   if ( ( i = member_array( type, keys[ key ] ) ) == -1 ) {
      return 0;
   }
   keys[ key ] = delete( keys[ key ], i, 1 );
   if (!sizeof(keys[key])) {
      map_delete(keys, key);
   }
   save_data_file( );
   return 1;
}
mapping query_all_key_names( string group ) {
   get_data_file( group );
   return key_names;
}
private void set_key_names( string group, mapping list ) {
   get_data_file( group );
   key_names = list;
   save_data_file( );
}
string query_key_name( string group, string key ) {
   get_data_file( group );
   return key_names[ key ];
}
void set_key_name( string group, string key, string name ) {
   get_data_file( group );
   key_names[ key ] = name;
   save_data_file( );
}
void delete_key_name( string group, string key ) {
   get_data_file( group );
   if ( !key_names[ key ] ) {
      return;
   }
   map_delete( key_names, key );
   save_data_file( );
}