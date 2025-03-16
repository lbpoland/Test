inherit "/std/object";
mixed *exits,
      *items;
string de_long,
       de_short;
int de_light;
void setup() {
  set_name("maker");
  add_adjective("room");
  set_short("Room maker");
  set_long("It is a small wooden rod about 30 centimeters long with deep "+
           "burn marks along the sides.  It has what looks like a small "+
           "lens stuck in the end and three buttons along its length.\n");
}
void init() {
  if (this_player()->query_creator()) {
    add_action("do_new", "new");
    add_action("do_set", "set");
    add_action("do_add", "add");
    add_action("do_setup", "setup");
    add_action("do_modify", "modify");
    add_action("do_map", "map");
  }
}
int do_new(string str) {
  if (!str) {
    notify_fail("Syntax: new <name>\n");
    return 0;
  }
}