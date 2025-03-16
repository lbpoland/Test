#define RESTORE_PATH "/save/cmr_library/"
inherit "/std/object";
string player_name, *materials;
void init_data( string pname ) {
  player_name = pname;
  materials = ({ });
}
int get_data_file( string pname ) {
  if ( player_name != pname ) {
    if ( file_size( RESTORE_PATH + pname +".o" ) > 0 )
      unguarded((: restore_object, RESTORE_PATH + pname :));
    else {
      init_data( pname );
      return 0;
    }
  }
  return 1;
}
void save_data_file( string word ) {
  unguarded((: save_object, RESTORE_PATH + word :));
}
string *query_known_materials( string pname ) {
  get_data_file( pname );
  if ( !materials ) {
    return ({ });
  }
  return materials + ({ });
}
int query_known_material( string pname, string material ) {
  get_data_file( pname );
  if ( !materials ) return 0;
  return ( member_array( material, materials ) != -1 );
}
int add_known_material( string pname, string material ) {
  get_data_file( pname );
  if ( member_array( material, materials ) != -1 ) {
    return 0;
  }
  materials += ({ material });
  save_data_file( player_name );
  return 1;
}