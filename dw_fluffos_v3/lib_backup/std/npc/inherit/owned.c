private mixed _owner;
object set_owner( mixed owner ){
  if( stringp(owner) )
    _owner = owner;
  if( objectp(owner) && living(owner) ){
    if( userp(owner) )
      _owner = owner->query_name();
    else
      _owner = owner;
  }
  return _owner;
}
object query_owner() {
  if( stringp(_owner) )
    return find_player(_owner);
  else
    return _owner;
}
object query_owner_pk_check() {
   return query_owner();
}
mixed *stats(){
  return ({
    ({ "owner", _owner }),
  });
}