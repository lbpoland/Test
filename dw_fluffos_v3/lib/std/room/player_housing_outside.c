#include <dirs.h>
#include <housing.h>
#include <login_handler.h>
#include <player.h>
inherit "/std/room/outside";
inherit "/std/room/inherit/player_housing";
void create() {
  add_help_file("player_housing");
  do_setup++;
  outside::create();
  player_housing::create();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
  seteuid("Room");
  add_property("no burial", 1);
}
string query_long() {
  return player_housing::query_long();
}
string query_owner() {
   return HOUSING->query_owner(base_name(this_object()));
}
int add_exit(string direc, mixed dest, string type) {
  int tmp;
  tmp = ::add_exit(direc, dest, type);
  setup_exit(direc, 0);
  return tmp;
}
string process_non_living(object *int_non_livings, int start) {
  object *not_positioned;
  not_positioned = player_housing::my_process_non_living(int_non_livings);
  return ::process_non_living(not_positioned, start);
}
void init() {
  player_housing::init();
  outside::init();
}
void event_exit(object ob, string message, object to) {
  outside::event_exit(ob, message, to);
  player_housing::event_exit(ob, message, to);
}
int query_keep_room_loaded() { return 1; }
void dest_me() {
  player_housing::dest_me();
  outside::dest_me();
}
int test_remove(object thing, int flag, mixed dest) {
  object thief;
  mixed *stuff;
  if(!outside::test_remove(thing, flag, dest))
    return 0;
  thief = this_player();
  if(!thief)
    return player_housing::test_remove(thing, flag, dest);
  if(thief->query_caster())
    thief = find_player(thief->query_caster());
  else if(thief->query_owner())
    thief = thief->query_owner();
  stuff = thing->query_property("dropped");
  if(thief &&
     test_save(thing) &&
     !test_occupier(thief->query_name()) &&
     (!stuff || stuff[0] != thief->query_name())) {
    log_file("HOUSING_THEFT", "%s: %s stole %s from %s in %s\n",
             ctime( time() )[4..18], (string)thief->query_short(),
             thing->query_short(),
             (string)query_owner(), file_name());
    event(this_object(), "theft", thief, this_object(), ({ thing }));
  }
  return player_housing::test_remove(thing, flag, dest);
}
int test_add( object ob, int flag) {
  int retval;
  retval = outside::test_add(ob, flag);
  if(retval)
    retval = player_housing::test_add(ob, flag);
  return retval;
}