nosave object *registered_containers;
nosave int can_export_inventory;
void create() {
   registered_containers = ({ });
}
void add_inventory_container(object cont) {
   if (member_array(cont, registered_containers) == -1 &&
       environment(cont) == this_object()) {
      registered_containers += ({ cont });
   }
}
void remove_inventory_container(object cont) {
  if(!registered_containers || !cont)
    return;
  registered_containers -= ({ cont });
}
void set_can_export_inventory() {
   can_export_inventory = 1;
}
void reset_can_export_inventory() {
   can_export_inventory = 0;
}
int query_can_export_inventory() {
   return can_export_inventory;
}
protected object *find_expanded_inv_match( string words, object looker,
                                           object *things) {
   object *stuff;
   object bing;
   stuff = ({ });
   if (can_export_inventory) {
      foreach (bing in registered_containers) {
         if (member_array(bing, things) != -1) {
            stuff += bing->find_inv_match(words, looker);
         }
      }
   }
   return stuff;
}