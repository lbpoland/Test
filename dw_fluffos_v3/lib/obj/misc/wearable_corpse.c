inherit "/obj/corpse";
inherit "/std/basic/wearable";
void create() {
  corpse::create();
  wearable::create();
}
string long( string word, int dark ) {
  return corpse::long( word, dark ) + wearable::long( word, dark );
}
void init_static_arg( mapping map ) {
   if ( map[ "corpse" ] )
      corpse::init_static_arg( map[ "corpse" ] );
   if ( map[ "wearable" ] )
      corpse::init_static_arg( map[ "wearable" ] );
}
void init_dynamic_arg( mapping map ) {
 if ( !undefinedp( map[ "corpse" ] ) )
      corpse::init_dynamic_arg( map[ "corpse" ] );
 if ( !undefinedp( map[ "wearable" ] ) )
      wearable::init_dynamic_arg( map[ "wearable" ] );
}
mapping query_static_auto_load() {
   return ([
      "corpse" : corpse::query_static_auto_load(),
      "wearable" : wearable::query_static_auto_load(),
   ]);
}
mapping query_dynamic_auto_load() {
   return ([
      "corpse" : corpse::query_dynamic_auto_load(),
      "wearable" : wearable::query_dynamic_auto_load()
   ]);
}
mixed *stats() {
	return corpse::stats() + wearable::stats();
}