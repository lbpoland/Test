inherit "/std/effect_shadow";
string *unblock_skills( string *skills ) {
  set_arg( arg() - skills );
  if( !sizeof( arg() ) ) {
    remove_this_effect();
    return ({});
  }
  return arg();
}
int query_mock_block( string mocked ) {
  if( member_array( "all", arg() ) != -1 ) {
    return 1;
  }
  foreach( string skill in arg() ) {
    if( !strsrch( mocked, skill ) ) {
      return 1;
    }
  }
}