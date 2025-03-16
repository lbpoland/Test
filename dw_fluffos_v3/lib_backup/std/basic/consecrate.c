private string _god;
void set_god( string deity ) {
  if ( stringp( deity ) )
    deity = lower_case( deity );
  _god =  deity;
  return;
}
void set_deity( string deity ) {
  if ( stringp( deity ) )
    deity = lower_case( deity );
  _god = deity;
  return;
}
string query_god() { return _god; }
string query_deity() { return _god; }
int query_consecrated( string god ) {
  if ( !stringp( god ) )
    return 0;
  god = lower_case( god );
  if ( _god )
    return god == _god;
  return this_object()->query_property( god );
}
mixed *stats() {
   return
      ({
         ({ "consecrated", _god }),
      });
}
mapping query_static_auto_load() {
   return ([
      "god" : _god
   ]);
}
void init_static_arg( mapping map ) {
   if ( !undefinedp( map[ "god" ] ) )
      _god = map[ "god" ];
}