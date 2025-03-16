mapping map_prop;
mapping timed_properties;
mapping property_stats;
void create() {
}
varargs int add_property(string var, mixed val, int tim) {
  if (!stringp(var))
    return 0;
  if (!map_prop)
    map_prop = ([ ]);
  map_prop[var] = val;
  if (tim > 0) {
    if (!timed_properties)
      timed_properties = ([ ]);
    timed_properties[var] = tim + time();
  }
#ifdef TRACK_PROPERTY_STATS
  if (!property_stats)
    property_stats = ([ ]);
  if (previous_object())
    property_stats[var] = ({ file_name( previous_object() ), time(), tim });
  else
    property_stats[var] = ({ "No previous object.", time(), tim });
#endif
  return 1;
}
int remove_property(string var) {
  if (map_prop)
    map_delete(map_prop, var);
  if (timed_properties)
    map_delete(timed_properties, var);
#ifdef TRACK_PROPERTY_STATS
  if (property_stats)
    map_delete(property_stats, var);
#endif
  return 1;
}
mixed query_property(string str) {
  if (!map_prop)
    return ([ ])["bing"];
  if (timed_properties && timed_properties[str] &&
      timed_properties[str] < time()) {
    map_delete(timed_properties, str);
    map_delete(map_prop, str);
#ifdef TRACK_PROPERTY_STATS
    if(property_stats)
      map_delete(property_stats, str);
#endif
    return map_prop[str];
  }
  return map_prop[str];
}
int query_is_timed_property(string str) {
  if (timed_properties && timed_properties[str]) {
    if (timed_properties[str] < time()) {
      map_delete(timed_properties, str);
      map_delete(map_prop, str);
#ifdef TRACK_PROPERTY_STATS
      map_delete(property_stats, str);
#endif
      return 0;
    }
    return 1;
  }
  return 0;
}
int query_property_time_left(string str) {
  if (timed_properties &&
      timed_properties[str]) {
    if (timed_properties[str] < time()) {
      map_delete(timed_properties, str);
      map_delete(map_prop, str);
#ifdef TRACK_PROPERTY_STATS
      map_delete(property_stats, str);
#endif
      return 0;
    }
    return timed_properties[str] - time();
  }
  return 0;
}
int query_property_exists(string str) {
  if (!map_prop)
    return 0;
  if (timed_properties &&
      timed_properties[str] &&
      timed_properties[str] < time()) {
    map_delete(timed_properties, str);
    map_delete(map_prop, str);
#ifdef TRACK_PROPERTY_STATS
    map_delete(property_stats, str);
#endif
    return map_prop[str];
  }
  return !undefinedp(map_prop[str]);
}
mapping query_properties() {
  if (map_prop)
    return map_prop ;
  return ([ ]);
}
mapping query_timed_properties() {
  if (timed_properties)
    return timed_properties;
  return ([ ]);
}
void add_properties(mapping map) {
  if (!map_prop)
    map_prop = map;
  else
    map_prop += map;
}
void set_properties(mapping map) {
  map_prop = map;
}
protected void save_player_properties() {
  string prop;
  if(timed_properties)
    foreach(prop in keys(timed_properties))
      if(timed_properties[prop] < time())
        map_delete(timed_properties, prop);
      else
        timed_properties[prop] -= time();
}
protected void reload_player_properties() {
  string prop;
  if (timed_properties)
    foreach(prop in keys(timed_properties))
      if(!map_prop[prop])
        map_delete(timed_properties, prop);
      else
        timed_properties[prop] += time();
}
mixed stats() {
  int i, bing;
  mixed *k, *v, *res;
  mapping props;
  props = (mapping)this_object()->query_properties();
  if ( !props )
    return ({ });
  k = keys( props );
  v = values( props );
  res = ({ });
  for ( i = sizeof( k ) - 1; i > -1; i-- ) {
    bing = 0;
    if (timed_properties &&
        timed_properties[ k[ i ] ] &&
        timed_properties[ k[ i ] ] < time()) {
      map_delete(timed_properties, k[ i ]);
      map_delete(map_prop, k[ i ]);
#ifdef TRACK_PROPERTY_STATS
      if(property_stats)
        map_delete(property_stats, k[i]);
#endif
      continue;
    }
    if (timed_properties &&
        timed_properties[ k[ i ] ]) {
      bing = timed_properties[ k[ i ] ] - time();
    }
    if ( !stringp( k[ i ] ) || k[ i ][ 0 .. 3 ] == "news" ||
         k[ i ] [ 0 ] == '.' )
      continue;
    if ( pointerp( v[ i ] ) ) {
      res += ({ ({ "(" + k[ i ] + (bing ? ":"+bing : "") + ")",
                     array_to_string( v[ i ] ) }) });
      continue;
    }
    if ( mapp( v[ i ] ) ) {
      res += ({ ({ "(" + k[ i ] + (bing ? ":"+bing : "") + ")",
                     mapping_to_string( v[ i ] ) }) });
      continue;
    }
    res += ({ ({ "("+ k[ i ] + ( bing ? ":"+ bing : "" ) +")",
                   v[ i ] }) });
  }
  return res;
}
#ifdef TRACK_PROPERTY_STATS
mixed query_property_stats( string var ) {
  if (!property_stats || undefinedp( property_stats[var] ) )
    return ({ });
  return property_stats[ var ];
}
mapping query_stats() {
  mixed property1, property2;
  if (!property_stats)
    return ([ ]);
  foreach( property1, property2 in property_stats )
    if(undefinedp(map_prop[property1]) &&
       undefinedp(timed_properties[property1]))
      map_delete(property_stats, property1);
  return property_stats;
}
#endif