#include <terrain.h>
mixed cmd(string str) {
  mixed dest;
  string tname;
  dest = this_player()->query_last_location();
  if(!dest)
    return notify_fail("No stored location.\n");
  if (stringp(dest)) {
    dest = load_object(dest);
  } else if (arrayp(dest) && stringp(dest[0]) && arrayp(dest[1])) {
    dest = TERRAIN_MAP->find_location(dest[0], dest[1]);
  } else {
    return notify_fail("I don't understand your stored location.\n");
  }
  tname = environment(this_player())->query_property("terrain name");
  if (tname) {
    this_player()->set_last_location(
      ({ tname, environment(this_player())->query_co_ord() })
      );
  } else {
    this_player()->set_last_location(
      base_name(environment(this_player()))
      );
  }
  this_player()->move_with_look( dest,
                                 this_player()->query_mmsgin(),
                                 this_player()->query_mmsgout() );
  return 1;
}
void dest_me() {
  destruct(this_object());
}
void clean_up() {
  dest_me();
}
void reset() {
  dest_me();
}