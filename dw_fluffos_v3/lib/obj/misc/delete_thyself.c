inherit "/std/object";
void create() {
   ::create();
   if (clonep(this_object())) {
      call_out((: move("/room/rubbish") :), 3);
   }
}
void init_dynamic_arg(mapping map) {
}
void init_static_arg() {
}