inherit "/obj/baggage";
int query_value() {
  int value;
  object ob;
  value = ::query_value();
  foreach(ob in all_inventory())
    value += ob->query_value();
  return value;
}
mixed query_static_auto_load() {
  if ( base_name(this_object()) + ".c" == __FILE__ )
    return int_query_static_auto_load();
  return ([ ]);
}