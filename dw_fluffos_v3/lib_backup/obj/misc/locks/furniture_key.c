inherit "/std/key";
void set_lock_number(int num) {
   set_key("small furniture", "furniture_lock_" + num);
   set_long("A small key, it looks like it would be "
            "suitable for a piece of furniture.\n");
   set_value(10);
}
void set_key_number( int num ){
  set_lock_number(num);
}
mapping query_static_auto_load() {
   return int_query_static_auto_load();
}
int query_duplicatable_key() {
   return 1;
}