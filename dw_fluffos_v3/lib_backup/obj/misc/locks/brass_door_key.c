inherit "/std/key";
void set_key_number(int num) {
   set_key("small brass", "door_lock_" + num);
   set_long("A small brass key.  It has a serial number " +
            num + " engraved on it.\n");
   set_value(10);
}
mapping query_static_auto_load() {
   return int_query_static_auto_load();
}
int query_duplicatable_key() {
   return 1;
}