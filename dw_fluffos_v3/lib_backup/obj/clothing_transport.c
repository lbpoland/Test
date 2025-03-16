inherit "/obj/clothing";
private int _mount_difficulty_modifier;
private int _direction_difficulty_modifier;
private string _race;
void create() {
   clothing::create();
}
void set_worn_by_race(string race) {
   _race = race;
}
string query_worn_by_race() {
   return _race;
}
void set_mount_difficulty_modifier(int diff) {
   _mount_difficulty_modifier = diff;
}
int query_mount_difficulty_modifier() {
   return _mount_difficulty_modifier;
}
void set_direction_difficulty_modifier(int diff) {
   _direction_difficulty_modifier = diff;
}
int query_direction_difficulty_modifier() {
   return _direction_difficulty_modifier;
}
mapping int_query_static_auto_load() {
   return ([
      "::" : clothing::int_query_static_auto_load(),
      "worn by race" : _race,
      "mount difficulty" : _mount_difficulty_modifier,
      "direction difficulty" : _direction_difficulty_modifier
   ]);
}
mapping query_static_auto_load() {
   if ( base_name(this_object()) != __FILE__[0..<3]) {
      return ([ ]);
   }
   return int_query_static_auto_load();
}
void init_static_arg(mapping map) {
   if (map["::"]) {
      clothing::init_static_arg(map["::"]);
   }
   _race = map["worn by race"];
   _mount_difficulty_modifier = map["mount difficulty"];
   _direction_difficulty_modifier = map["direction difficulty"];
}