#define SAVE_FILE "/save/artifacts"
#define SAVE_DIR "/save/artifacts/"
mapping artifacts;
void create() {
   seteuid( (string)"/secure/master"->
         creator_file( file_name( this_object() ) ) );
   artifacts = ([ ]);
   if ( file_size( SAVE_FILE +".o" ) > 0 )
      unguarded( (: restore_object, SAVE_FILE :) );
}
mapping query_artifacts() { return artifacts; }
void save_me() { unguarded( (: save_object, SAVE_FILE :) ); }
int query_artifact( string name ) {
  if ( !artifacts[ name ] )
    return 0;
  return 1;
}
void add_artifact( string name, string file, int max, int min, int bonus,
                   int value ) {
  artifacts[ name ] = ({ file, max, min, bonus, value });
  save_me();
}
void remove_artifact( string name ) {
  if ( !artifacts[ name ] )
    return;
  artifacts = m_delete( artifacts, name );
  save_me();
}
string query_artifact_file( string name ) {
  if ( !artifacts[ name ] )
    return 0;
  return artifacts[ name ][ 0 ];
}
int query_artifact_max( string name ) {
  if ( !artifacts[ name ] )    return 0;
  return artifacts[ name ][ 1 ];
}
int query_artifact_min( string name ) {
  if ( !artifacts[ name ] )
    return 0;
  return artifacts[ name ][ 2 ];
}
int query_artifact_bonus( string name ) {
  if ( !artifacts[ name ] )
    return 0;
  return artifacts[ name ][ 3 ];
}
int query_artifact_value_info( string name ) {
  if ( !artifacts[ name ] )
    return 0;
  return artifacts[ name ][ 4 ];
}
int query_artifact_level( string name, int bonus ) {
  int number;
  if ( !artifacts[ name ] )
    return 0;
  number = artifacts[ name ][ 1 ] - artifacts[ name ][ 2 ];
  number *= number;
  number /= bonus - artifacts[ name ][ 3 ] + artifacts[ name ][ 1 ] -
      artifacts[ name ][ 2 ];
  number += artifacts[ name ][ 2 ];
  return number;
}
int query_artifact_value( string name, int bonus ) {
  int number;
  if ( !artifacts[ name ] )
    return 0;
  number = artifacts[ name ][ 4 ] * artifacts[ name ][ 1 ];
  number /= query_artifact_level( name, bonus );
  return number;
}
void diagnose_artifact( object thing, object person, object) {
   int charges;
   string type;
   if ( !thing || !person )
      return;
   type = (string)thing->query_artifact_type();
   if ( !stringp( type ) ) {
      tell_object( person, "There doesn't seem to be anything special about "+
            (string)thing->the_short() +".\n" );
      return;
   }
   charges = (int)thing->query_charges();
   tell_object( person, (string)thing->the_short() +" is a level "+
         (int)thing->query_level() +" magic "+ type +".  It has "+
         ( charges == 1 ? "one charge" : query_num( charges ) +" charges" ) +
         " remaining.\n" );
}
string query_wand_name() { return "wand of artifact probing"; }
void zap( object thing, object person, object wand ) {
  call_out( "diagnose_artifact", 0, thing, person, wand );
}
int query_known( string person, string artifact ) {
  int i;
  string *list;
  if ( !artifacts[ artifact ] )
    return 0;
  if ( unguarded((: file_length, SAVE_DIR + person :)) < 1 )
    return 0;
  list = explode( unguarded((: read_file, SAVE_DIR + person :)), "\n" );
  for ( i = 0; i < sizeof( list ); i++ ) {
    if ( list[ i ] == artifact )
      return 1;
  }
  return 0;
}
void add_known( string person, string artifact ) {
  if ( query_known( person, artifact ) )
    return;
  unguarded((: write_file, SAVE_DIR + person, artifact +"\n" :));
}