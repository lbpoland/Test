inherit "/std/basic/close_lock";
void set_closed() {
   ::set_closed();
   if (environment()) {
      environment()->remove_inventory_container(this_object());
   }
}
void reset_closed() {
   ::set_closed();
   if (environment()) {
      environment()->add_inventory_container(this_object());
   }
}
void we_moved(object from, object to) {
   if (!query_closed()) {
      if (from) {
         from->remove_inventory_container(this_object());
      }
      if (to) {
         to->add_inventory_container(this_object());
      }
   }
}
void dest_me() {
   if (environment()) {
      environment()->remove_inventory_container(this_object());
   }
}