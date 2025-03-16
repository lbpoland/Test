inherit "/std/room/outside";
inherit "/std/room/basic/water";
private int _setting_water_light = 0;
void init() {
  water::init();
  outside::init();
}
int is_allowed_position(string poss) {
  return water::is_allowed_position(poss);
}
mixed *query_default_position(object ob) {
  return water::query_default_position(ob);
}
int add_exit(string direc, mixed dest, string type) {
  int retval = outside::add_exit(direc, dest, type);
  water::add_exit(direc, dest, type);
  return retval;
}
int query_light() {
  update_water_light();
  if (query_surface()) {
    return ::query_light();
  }
  return ::query_light()*query_clarity()/100;
}
int set_water_light(int number) {
  _setting_water_light = 1;
  set_light(number);
  _setting_water_light = 0;
}
int adjust_light(int number) {
  if (!_setting_water_light) {
    set_use_surface_light(0);
  }
  return ::adjust_light(number);
}
mixed query_property(string tag) {
  if ("location" == tag && !query_surface()) {
    return "underwater";
  }
  return ::query_property(tag);
}
int attack_speed() { return 5; }