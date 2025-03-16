inherit "/std/effect_shadow";
int query_keep_room_loaded() {
   return 1;
}
int dont_free() {
   return 1;
}
int clean_up() {
   return 1;
}
void tent_collapsed() {
   remove_this_effect();
}