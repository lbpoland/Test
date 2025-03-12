int num;
void create() {
  seteuid("Room");
  unguarded((: restore_object, "/save/monster-handler" :));
}
string query_shadow_name() {
  num++;
  return "/tmp/mon-shad/frog-"+num;
}
void reset() {
  unguarded((: save_object, "/save/monster-handler" :));
}
void dest_me() {
  unguarded((: save_object, "/save/monster-handler" :));
}