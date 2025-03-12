#include <dirs.h>
#include <housing.h>
#include <login_handler.h>
#include <player_handler.h>
inherit "/std/room/inherit/placement";
inherit "/std/room/inherit/room_save";
#define STANDARD_EXITS ({ "north", "northeast", "east", "southeast", \
                          "south", "southwest", "west", "northwest"})
#undef PLAYTESTING
#define DEBUG
private nosave int _setup_callout;
varargs string* query_direc(object thing);
int query_relative(string direc);
varargs mixed query_door_control(string direc);
varargs mixed* query_dest_other(string direc);
int modify_exit(string dir, mixed* arr);
varargs int add_item(mixed shorts, mixed desc, int no_plural);
string the_short();
string* query_exits();
int query_exit(string direc);
void setup_doors();
void update_doors();
private void update_short_cache(string direc);
int test_occupier(string name);
string show_surface(string direc);
int allow_list();
int do_deny(string player, string location);
int do_allow(object player, string location);
int add_allowed(string pname);
int remove_allowed(string pname);
string query_owner();
class decoration {
  string short;
  string covering;
}
class exit_data {
  string long;
  string key;
  int difficulty;
  int closed;
  int locked;
  int autolock;
  int transparent;
  mixed trap_data;
}
class exit_shorts {
  string one_short;
  string a_short;
}
private class decoration *decorations;
private string base_long;
private mapping exits;
private mapping exit_shorts;
private nosave mapping coverings;
private nosave string owner;
private string *allowed = ({ });
private string *tell_denied = ({ });
private nosave string decoration_desc = "";
private nosave string quit_location;
private nosave int done_setup;
private nosave int setup_counter;
private nosave string *surfaces;
#ifdef DEBUG
void debug_log(string fmt, mixed args ...) {
    debug_printf(fmt + "\n", args ...);
  if(base_name(this_object()) == "/d/cwc/Bes_Pelargic/Pong_Ping/roads/phoenix_avenue/housing/05entrycorridor") {
    log_file("HOUSING_DEBUG", "%s (%s): " + fmt + "\n",
       ctime(time())[4..18], base_name(this_object()), args ...);
  }
}
#endif
void create() {
  room_save::create();
  exits = ([ ]);
  exit_shorts = ([ ]);
  decorations = ({ });
  tell_denied = ({ });
  this_object()->add_item("left", (: show_surface("left") :));
  this_object()->add_item("right", (: show_surface("right") :));
  this_object()->add_item("forward", (: show_surface("forward") :));
  this_object()->add_item("backward", (: show_surface("backward") :));
  this_object()->add_item("up", (: show_surface("up") :));
  this_object()->add_item("down", (: show_surface("down") :));
  done_setup = 0;
  setup_doors();
  call_out("setup_doors", 0);
}
string show_surface(string direc) {
  class decoration tmp;
  int found;
  string lstr, dstr;
  mixed tmp2;
  switch(direc) {
  case "left":
  case "right":
  case "forward":
  case "backward":
    tmp2 = this_player()->query_facing();
    direc = (string)this_player()->find_abs(direc, tmp2[0]);
    break;
  case "up":
    direc = "ceiling";
    break;
  case "down":
    direc = "floor";
    break;
  }
  if(!decorations) {
    decorations = ({ });
  } else {
    foreach(tmp in decorations) {
      if(member_array(tmp->short, surfaces) == -1)
        decorations -= ({ tmp });
      if(tmp->short == direc || tmp->short == direc + " wall") {
        found = 1;
        break;
      }
    }
  }
  if(found) {
    direc = replace(direc, ({ " wall", "" }));
    if(member_array(direc, query_direc()) != -1) {
      lstr = "$C$";
      update_short_cache(direc);
      if(exit_shorts[direc] && exit_shorts[direc]->one_short) {
        if(query_door_control(direc))
          lstr += query_door_control(direc)->one_short() + " leads";
        else
          lstr = "an exit leads";
        lstr += " to " + exit_shorts[direc]->one_short;
      } else {
        if(query_door_control(direc))
          lstr += "is the " + query_door_control(direc)->one_short();
        else
          lstr += "is an exit";
      }
      lstr += " and the ";
    } else
      lstr = "The ";
    dstr = desc_surface(direc);
    if(dstr != "")
      dstr = "  " + dstr;
    return lstr + tmp->short + " is " + tmp->covering + "." + dstr;
  }
  return "";
}
string show_corner(string direc) {
  string tmp;
  tmp = desc_surface(direc);
  if(tmp == "") {
    tmp = "The " + direc + " corner is empty.";
  }
  return tmp;
}
string exit_long() {
  string *direcs, lstr;
  int i, j;
  object door;
  direcs = query_direc();
  if(!sizeof(direcs))
    return "";
  lstr = "  $C$";
  for(i=0; i<sizeof(direcs); i++) {
    update_short_cache(direcs[i]);
    if(query_relative(direcs[i])) {
      j = member_array(this_player()->find_rel(direcs[i]), REL_DIRS);
      lstr += REL_DIRS[j+2];
      if(exit_shorts[direcs[i]]) {
        if(query_door_control(direcs[i]))
          lstr += " " + query_door_control(direcs[i])->a_short() + " leads "
            "to " + exit_shorts[direcs[i]]->a_short;
        else
          lstr += " an exit leads to " + exit_shorts[direcs[i]]->a_short;
      } else {
        if(query_door_control(direcs[i]))
          lstr += " is " + query_door_control(direcs[i])->a_short();
        else
          lstr += " is an exit";
      }
    } else {
      door = query_door_control(direcs[i]);
      if(door) {
        if(member_array("window", door->query_name()) != -1)
          lstr += door->a_short() + " looks out";
        else
          lstr += door->a_short() + " leads " + direcs[i];
      } else
        lstr += "an exit leads " + direcs[i];
    }
    if(i < sizeof(direcs)-2)
      lstr += ", ";
    if(i == sizeof(direcs)-2)
      lstr += " and ";
    if(i == sizeof(direcs)-1)
      lstr += ".";
  }
  return lstr;
}
string decoration_long() {
  class decoration tmp;
  string lstr, wstr, tmpstr, *tmparray, *names;
  int i;
#ifdef 0
  if(decoration_desc != "")
    return decoration_desc;
#endif
  lstr = "";
  if(sizeof(decorations)) {
    coverings = ([ ]);
    names = ({ "walls" });
    foreach ( tmp in decorations ) {
      if(!coverings[tmp->covering])
        coverings[tmp->covering] = ({ tmp->short });
      else
        coverings[tmp->covering] += ({ tmp->short });
      if(classp(tmp) && strsrch(tmp->short, "wall") == -1)
        names += ({ tmp->short });
    }
    i = 0;
    tmparray = sort_array(keys(coverings),
                        (: sizeof(coverings[$1]) - sizeof(coverings[$2]) :));
    if(sizeof(tmparray) > 3) {
      lstr += "  The " + query_multiple_short(names) + " are multicoloured.  ";
    } else if(sizeof(tmparray) == 1) {
      lstr += "  The surfaces are all " + decorations[0]->covering + ".  ";
    } else {
      foreach(tmpstr in tmparray) {
        if(i == 0)
          wstr = "  The ";
        else
          wstr = "the ";
        if(i == sizeof(tmparray)-1 && sizeof(coverings[tmpstr]) > 1)
          wstr += "other surfaces";
        else
          wstr += query_multiple_short(coverings[tmpstr], "", 1);
        if(sizeof(coverings[tmpstr]) > 1)
          wstr += " are ";
        else
          wstr += " is ";
        wstr += tmpstr;
        if(i < sizeof(tmparray) -2)
          wstr += ", ";
        else if(i == sizeof(tmparray) -2)
          wstr += " and ";
        else if(i == sizeof(tmparray) -1)
          wstr += ".  ";
        i++;
        lstr += wstr;
      }
    }
  }
  decoration_desc = lstr;
  return decoration_desc;
}
string query_long() {
  string lstr, tmp;
  if(base_long)
    lstr = "This is " + base_long + ".";
  else
    lstr = "";
  tmp = decoration_long();
  if(tmp != "")
    lstr += tmp;
  else
    lstr += "  ";
  return (lstr + furniture_long() + exit_long() + "\n");
}
int setup_exit(string direc, int relative) {
  if(member_array(direc, STANDARD_EXITS) != -1 && relative)
    modify_exit(direc, ({ "relative", 1 }));
  modify_exit(direc, ({ "closed", 1 }));
  return 1;
}
void set_base_desc(string desc) {
  base_long = desc;
}
string query_base_desc() {
  return base_long;
}
void set_quit_handler(string filename) {
  quit_location = filename;
}
string query_quit_handler() {
  if(this_player() && !test_occupier(this_player()->query_name()) &&
     quit_location)
    return quit_location;
  return base_name(this_object());
}
void add_surface(string short, string covering ){
  class decoration tmp;
  string dir;
  if(!surfaces)
    surfaces = ({ });
  surfaces += ({ short });
  if(!decorations)
    decorations = ({ });
  else {
    foreach(tmp in decorations)
      if(tmp->short == short) {
        add_item(tmp->short, (: show_surface($(tmp->short)) :));
        short = replace(short, ({" wall", ""}));
        foreach(dir in keys(ABS_FACING)) {
          if(ABS_FACING[short] &&
             ABS_FACING[dir] == (ABS_FACING[short] % 8 ) + 1) {
            add_item(dir+" corner", (: show_corner($(dir)) :));
            break;
          }
        }
        return;
      }
  }
  tmp = new(class decoration );
  tmp->short = short;
  tmp->covering = covering;
  decorations += ({ tmp });
  add_item(tmp->short, (: show_surface($(tmp->short)) :));
  short = replace(short, ({" wall", ""}));
  foreach(dir in keys(ABS_FACING))
    if(ABS_FACING[short] &&
       ABS_FACING[dir] == (ABS_FACING[short] + 1) % 8) {
      add_item(dir+" corner", (: show_corner($(dir)) :));
      break;
    }
  decoration_desc = "";
}
string *query_surfaces() {
  string *stmp;
  class decoration tmp;
  stmp = ({ });
  foreach(tmp in decorations) {
    stmp += ({ replace(tmp->short, ({" wall", ""})) });
  }
  return stmp;
}
int decorate_surface(string short, string covering ){
  class decoration tmp;
  foreach(tmp in decorations)
    if(tmp->short == short) {
      tmp->covering = covering;
      event(this_object(), "save");
      decoration_desc = "";
      return 1;
    }
  return 0;
}
void query_decorations() {
  printf("%O\n", decorations);
}
int test_save(object thing) {
  return thing->query_furniture() || thing->query_missing_item_receipt();
}
int test_remove(object thing, int flag, mixed dest) {
  if(!placement::test_remove(thing, flag, dest))
    return 0;
  return room_save::test_remove(thing, flag, dest);
}
object *my_process_non_living(object *int_non_livings, int start) {
  object *not_positioned;
  not_positioned = filter(int_non_livings,
                          (: !$1->query_property("current room position") &&
                           !$1->query_property("current room hidden") :) );
  return not_positioned;
}
void init() {
  placement::init();
  if(!allowed) {
    allowed = ({ });
  }
  add_command("allow", "list", (: allow_list() :));
  if(test_occupier(this_player()->query_name()) ||
     this_player()->query_creator()) {
    if(!HOUSING->query_house(base_name(this_object()))) {
      add_command("allow", "<indirect:player:here>",
                  (: do_allow($1[0], "room") :));
      add_command("deny", "<word'player'>",
                  (: do_deny($4[0], "room") :));
    } else {
      add_command("allow", "<indirect:player:here> <word'house|room'>",
                  (: do_allow($1[0], $4[1]) :));
      add_command("deny", "<word'player'> <word'house|room'>",
                  (: do_deny($4[0], $4[1]) :));
    }
  }
}
protected void event_enter_checks(object ob) {
  if(!tell_denied) {
    tell_denied = ({ });
  }
  if(ob && interactive(ob) &&
     member_array(ob->query_name(), tell_denied) != -1) {
    write("%^YELLOW%^%^BOLD%^You are no longer allowed to control this "
          "room.%^RESET%^\n");
    tell_denied -= ({ ob->query_name() });
  }
}
void event_enter(object ob, string message, object from) {
#ifdef PLAYTESTING
  if(interactive(ob) &&
     (!ob->query_creator() &&
     !"/obj/handlers/playtesters"->query_playtester(ob->query_name())) &&
     ob->query_name() != "gumboot") {
    tell_object(ob, "Sorry, this area is only open to playtesters.\n");
    ob->move(from);
  }
#endif
  event_enter_checks(ob);
}
int allow_list() {
  string *tmp;
  if(owner && owner != "For Sale" && owner != "Under Offer") {
    tmp = ({ owner }) + allowed;
  } else {
    tmp = allowed;
  }
  if (!test_occupier(this_player()->query_name()) &&
      !this_player()->query_creator()) {
    add_failed_mess("You are not allowed to control this room.\n", ({ }));
    return 0;
  }
  switch(sizeof(tmp)) {
  case 0:
    add_succeeded_mess(({"Noone is allowed to control this room.\n",
                           "$N messes with something in " + the_short() +
                           ".\n"}));
    break;
  case 1:
    add_succeeded_mess(({query_multiple_short(tmp) +
                           " is allowed to control this room.\n",
                           "$N messes with something in " + the_short() +
                           ".\n"}));
    break;
  default:
    add_succeeded_mess(({query_multiple_short(tmp) +
                           " are allowed to control this room.\n",
                           "$N messes with something in " + the_short() +
                           ".\n"}));
  }
  return 1;
}
int do_allow(object player, string location) {
  string pname;
  string *rooms;
  string room;
  int failed;
  if((query_owner() != this_player()->query_name()) &&
     !this_player()->query_creator()) {
    add_failed_mess("You are not allowed to control this room.\n", ({ }));
    return 0;
  }
  if(environment(player) != this_object()) {
    return add_failed_mess("$I is not here.\n", ({ player }));
  }
  pname = lower_case(player->query_name());
  if(test_occupier(pname)) {
    add_failed_mess("$I is already able to control this room.\n");
    return 0;
  }
  if(location == "house") {
    rooms = HOUSING->query_rooms(base_name(this_object()));
    failed = 1;
    foreach(room in rooms) {
      failed &= room->add_allowed(pname);
    }
  } else {
    failed = add_allowed(pname);
  }
  if (failed) {
     add_failed_mess("Failed to add " + pname + " as being able to control "
                     "the " + location + ".\n");
     return 0;
  }
  tell_object(player, "You are now permitted to control this " + location +
              ".\n");
  add_succeeded_mess(({ pname + " is allowed to control this " + location +
                          ".\n", ""}));
  return 1;
}
int do_deny(string player, string location) {
  object ob;
  string *rooms, room;
  if(member_array(player, allowed) == -1) {
    add_failed_mess(player + " is not on the allow list.\n");
    return 0;
  }
  if (!test_occupier(this_player()->query_name()) &&
      !this_player()->query_creator()) {
    add_failed_mess("You are not allowed to control this room.\n");
    return 0;
  }
  if(!test_occupier(player)) {
    add_failed_mess(player + " is already not allowed to control this room.\n");
    return 0;
  }
  if(location == "house") {
    rooms = HOUSING->query_rooms(base_name(this_object()));
    foreach(room in rooms)
      room->remove_allowed(player);
  } else {
    remove_allowed(player);
  }
  ob = find_player(player);
  if(ob && environment(ob) == this_object()) {
    tell_object(ob, "%^YELLOW%^%^BOLD%^You are no longer allowed to control " +
                the_short() + ".\n%^RESET%^");
  } else {
    tell_denied += ({ player });
  }
  add_succeeded_mess(({player + " is no longer allowed to control this " +
                     location + ".\n", "" }));
  return 1;
}
private void update_short_cache(string direc) {
  string ostr, astr;
  if(!exit_shorts)
    exit_shorts = ([ ]);
  if(find_object(query_dest_other(direc)[0])) {
    ostr = query_dest_other(direc)[0]->one_short();
    if(this_player())
      ostr = this_player()->convert_message(ostr);
    astr = query_dest_other(direc)[0]->a_short();
    if(this_player())
      astr = this_player()->convert_message(astr);
    if(!exit_shorts[direc] ||
       ostr != exit_shorts[direc]->one_short ||
       astr != exit_shorts[direc]->a_short) {
      exit_shorts[direc] = new(class exit_shorts,
                               one_short : ostr,
                               a_short : astr);
    }
  }
}
void update_doors() {
  string exit;
  object door_ob;
  if(!done_setup)
    setup_doors();
  if(!exits)
    exits = ([ ]);
  foreach(exit in query_exits()) {
    door_ob = query_door_control(exit);
    if(door_ob) {
      if(door_ob->query_key() == "generic_key") {
#ifdef DEBUG
        if(exits[exit])
          debug_log("update_doors", "Door %s has generic_key, exit data "
                    "has %s", exit, exits[exit]->key);
        else
          debug_log("update_doors", "Door %s has generic_key, no existing "
                    "exit data.", exit);
#endif
      }
      exits[exit] = new(class exit_data,
                        long : door_ob->query_long(),
                        key : door_ob->query_key(),
                        difficulty: door_ob->query_difficulty(),
                        closed : door_ob->query_closed(),
                        locked : door_ob->query_locked(),
                        autolock : door_ob->query_autolock(),
                        transparent : door_ob->query_transparent(),
                        trap_data : door_ob->query_trap_data());
#ifdef DEBUG2
      debug_log("update_doors: Door %s: key: %s, difficulty: %d, closed: %d, "
                "locked: %d, owner: %s", exit, exits[exit]->key,
                exits[exit]->difficulty, exits[exit]->closed,
                exits[exit]->locked, owner);
#endif
    }
  }
}
void setup_doors() {
  string exit;
  object door;
  string other, other_id;
#ifdef DEBUG2
  debug_log("Setup doors called.");
#endif
  if(!this_object()->query_exits()) {
    this_object()->calc_exits();
  }
  if(!exits || !sizeof(exits)) {
    if(!this_object()->query_exits()) {
#ifdef DEBUG2
      debug_log("Leaving setup_doors, No exits to setup.");
#endif
    } else if(query_inventory_loaded()) {
#ifdef DEBUG
      debug_log("Leaving setup_doors, exits not setup %O, autoloading: %d "
                "inventory loaded: %d.",
                exits, query_auto_loading(), query_inventory_loaded());
#endif
    }
    return;
  }
  foreach(exit in keys(exits)) {
    door = query_door_control(exit);
    if(!door) {
      if(!query_exit(exit)) {
        map_delete(exits, exit);
      }
      continue;
    }
    if(!owner)
      catch(owner = HOUSING->query_owner(base_name(this_object())));
#ifdef DEBUG2
      if(exit == "out")
        debug_log("Setting up %s: key: %s, difficulty: %d, closed: %d, "
                  "locked: %d, owner: %s", exit, exits[exit]->key,
                  exits[exit]->difficulty, exits[exit]->closed,
                  exits[exit]->locked, owner);
#endif
      modify_exit(exit, ({ "key", exits[exit]->key,
                             "difficulty", exits[exit]->difficulty,
                             "closed", exits[exit]->closed,
                             "locked", exits[exit]->locked,
                             "autolock", exits[exit]->autolock,
                             "lock owner", owner,
                             }));
      if(exits[exit]->trap_data && arrayp(exits[exit]->trap_data)) {
        door->setup_trap(exits[exit]->trap_data[0],
                         exits[exit]->trap_data[1],
                         exits[exit]->trap_data[2],
                         exits[exit]->trap_data[3],
                         exits[exit]->trap_data[4]);
        if(exits[exit]->trap_data[5])
          door->set_trap_armed(1);
      }
    other = door->query_dest();
    other_id = door->query_other_id();
#ifdef NO_SLOW_LOAD
    if(!find_object(other) && exit != "out")
      continue;
#endif
    if(!other_id) {
      door->force_other();
      other_id = door->query_other_id();
    }
    if(!other_id) {
#ifdef DEBUG2
      debug_log("No other_id, adding call_out.");
#endif
      if(!_setup_callout) {
        _setup_callout = call_out("setup_doors", 0);
        return;
      }
    }
    other->modify_exit(other_id, ({ "key", exits[exit]->key,
                                      "difficulty", exits[exit]->difficulty,
                                      "closed", exits[exit]->closed,
                                      "locked", exits[exit]->locked,
                                      "autolock", exits[exit]->autolock,
                                      "lock owner", owner,
                                      }));
    if(exits[exit]->trap_data && arrayp(exits[exit]->trap_data)) {
      door = other->query_door_control(other_id);
      if(door && objectp(door)) {
        door->setup_trap(exits[exit]->trap_data[0],
                         exits[exit]->trap_data[1],
                         exits[exit]->trap_data[2],
                         exits[exit]->trap_data[3],
                         exits[exit]->trap_data[4]);
        if(exits[exit]->trap_data[5])
          door->set_trap_armed();
      }
    }
  }
  done_setup = 1;
}
string query_owner() {
  if(owner)
    return owner;
  return HOUSING->query_owner(base_name(this_object()));
}
string set_owner(string who) { owner = who; }
int add_allowed(string pname) {
  if(test_occupier(pname))
    return 0;
  allowed += ({ pname });
  event(this_object(), "save");
  return 0;
}
int remove_allowed(string pname) {
  if(!test_occupier(pname))
    return 0;
  allowed -= ({ pname });
  event(this_object(), "save");
  return 1;
}
int test_occupier(string name) {
  if(!owner)
    catch(owner = HOUSING->query_owner(base_name(this_object())));
  if(!owner || lower_case(owner) == "for sale" ||
     lower_case(owner) == "under offer")
    return 1;
  if(PLAYER_HANDLER->test_creator(name))
    return 1;
  if(!allowed)
    allowed = ({ });
  return (owner == name || (member_array(name, allowed) != -1));
}
int ownership_change(string old_owner, string new_owner) {
  if(old_owner != new_owner) {
    owner = new_owner;
    allowed = ({ });
    return 1;
  }
  return 0;
}
string *query_allowed() {
   if (allowed) {
     return allowed;
   }
   return ({ });
}
int is_allowed(string name) {
  if((query_owner() && (lower_case(name) == lower_case(query_owner()))) ||
     (member_array(lower_case(name), query_allowed()) != -1) ||
     PLAYER_HANDLER->test_creator(name)) {
    return 1;
  }
   return 0;
}
void dest_me() {
#ifdef NOT_USED
  if (base_name(this_object()) + ".c" != __FILE__)
    update_doors();
#endif
  ::dest_me();
}
void event_open(object door, object opener) {
#ifdef DEBUG2
  debug_log("door opened by %s [%d]", opener->query_name(), done_setup);
#endif
  if(done_setup) {
    ::event_open(door, opener);
    update_doors();
  }
}
void event_close(object door, object closer) {
#ifdef DEBUG2
    debug_log("door closed by %s [%d]", closer->query_name(), done_setup);
#endif
  if(done_setup) {
    ::event_close(door, closer);
    update_doors();
  }
}
void event_unlock(object door, object unlocker) {
#ifdef DEBUG2
  debug_log("door unlocked by %s [%d]",
            unlocker?unlocker->query_name():"noone", done_setup);
#endif
  if(done_setup) {
    ::event_unlock(door, unlocker);
    update_doors();
  }
}
void event_lock(object door, object locker) {
#ifdef DEBUG2
  debug_log("door locked by %s [%d]", locker?locker->query_name():"noone",
            done_setup);
#endif
  if(done_setup) {
    ::event_lock(door, locker);
    update_doors();
  }
}