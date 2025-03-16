#include <dirs.h>
#include <room.h>
mapping milestone_dirs = ([ ]);
mapping milestone_index = ([ ]);
mapping shorten = SHORTEN;
string topo_handler;
int *actual_room_size;
string motion_verb = "walk", short_mse;
string iroom_exit_mess = "$N $V$s away to the $T.";
string iroom_enter_mess = "$N $V$s in from the $F.";
string iroom_move_mess = "You $V a little to the $T.\n";
string *pass_mess = ({
  "You $V a long while.",
  "$N passes by heading $T.",
  "  On the way you pass $O.\n"
});
mixed other_exits = ({ });
string *other_types = ({ });
mapping look_mess = ([ ]);
mapping dirs = ([
  "north": ({ 1, 0, 0 }), "south": ({ -1, 0, 0 }),
  "east": ({ 0, 1, 0 }), "west" : ({ 0, -1, 0 }),
  "northeast": ({ 1, 1, 0 }), "northwest": ({ 1, -1, 0 }),
  "southeast": ({ -1, 1, 0 }), "southwest": ({ -1, -1, 0 }),
  "up": ({ 0, 0, 1 }), "down": ({ 0, 0, -1 })
]);
mapping opposites = ([
  "north": "south", "south": "north", "west": "east",
  "east": "west", "northeast": "southwest", "southwest": "northeast",
  "northwest": "southeast", "southeast": "northwest", "up": "down",
  "down": "up"
]);
void add_topo_exits_int();
void set_area_handler(string s) { topo_handler = s; }
void set_topo_handler(string s) { topo_handler = s; }
string query_topo_handler() { return topo_handler; }
void set_actual_room_size(int *s) { actual_room_size = copy(s); }
int *query_actual_room_size() { return actual_room_size; }
void set_motion_verb(string s) { motion_verb = s; }
string query_motion_verb() { return motion_verb; }
void set_iroom_exit_mess(string s) { iroom_exit_mess = s; }
string query_iroom_exit_mess() { return iroom_exit_mess; }
void set_iroom_enter_mess(string s) { iroom_enter_mess = s; }
string query_iroom_enter_mess() { return iroom_enter_mess; }
void set_iroom_move_mess(string s) { iroom_move_mess = s; }
string query_iroom_move_mess() { return iroom_move_mess; }
void set_pass_mess(string *s) { pass_mess = s; }
string *query_pass_mess() { return pass_mess; }
void add_look_mess(mapping m) { look_mess += m; }
mapping query_look_mess() { return look_mess; }
void add_milestone_dir(string handler, string dir) {
  if (undefinedp(milestone_dirs[handler])) {
    milestone_dirs[handler] = ({ dir });
  } else {
    milestone_dirs[handler] += ({ dir });
  }
}
mixed query(string s) { return fetch_variable(s); }
varargs void set_milestone_index(string handler, int index) {
  milestone_index[handler] = index;
}
void setup_milestone() {
  string handler;
  foreach (handler in keys(milestone_index)) {
    handler->setup_milestone(this_object());
  }
  add_topo_exits_int();
}
int add_milestone_exit(string s, string dest, string type) {
  string ss, em, xm, mm;
  add_exit(s, dest, type);
  add_exit(motion_verb + " " + s, "interroom", "hidden");
  if (!undefinedp(shorten[s])) {
    ss = shorten[s];
    add_alias(motion_verb + " " + ss, motion_verb + " " + s);
  } else {
    ss = s;
  }
  if (type != "hidden") {
    remove_exit(motion_verb + " <" + short_mse + ">");
    if (!short_mse) {
      short_mse = ss;
    } else {
      short_mse += "/" + ss;
    }
    add_exit(motion_verb + " <" + short_mse + ">", "interroom", type);
  }
  em = replace(iroom_enter_mess, ({ "$V", motion_verb, "$T", s, "$F",
                              opposites[s] }));
  xm = replace(iroom_exit_mess, ({ "$V", motion_verb, "$T", s, "$F",
                              opposites[s] }));
  mm = replace(iroom_move_mess, ({ "$V", motion_verb, "$T", s, "$F",
                              opposites[s] }));
  modify_exit(motion_verb + " " + s, ({
    "exit mess", "$N " + motion_verb + "$s away to the " + s + ".",
    "enter mess", "$N " + motion_verb + "$s in from the " + opposites[s] + ".",
    "move mess", "You " + motion_verb + " a little to the " + s + ".\n"
  }));
  return modify_exit(s, ({ "function", "passing_mess" }) );
}
int passing_mess(string dir, object ob, string special_mess) {
  int i;
  object *obs, passed;
  string mess1, mess2, handler;
  foreach (handler in keys(milestone_dirs)) {
    i = member_array(dir, milestone_dirs[handler]);
    if (i < 0) {
      continue;
    }
    obs = handler->query_irooms_inv(milestone_index[handler], -1, i);
    if (stringp(pass_mess[0])) {
      mess1 = replace(pass_mess[0], ({ "$V", motion_verb, "$T", dir, "$F",
                                         opposites[dir] }));
      if (stringp(pass_mess[2]) && sizeof(obs)) {
        mess1 += replace(pass_mess[2], "$O", query_multiple_short(obs));
      }
      mess1 += "\n";
      tell_object(ob, mess1);
    }
    if (stringp(pass_mess[1])) {
      mess2 = replace(pass_mess[1], ({ "$V", motion_verb, "$T", dir, "$F",
                                         opposites[dir], "$N",
                                         ob->a_short() }));
      foreach (passed in obs) {
        if (living(passed) && ob->query_visible(passed)) {
          tell_object(passed, mess2 + "\n");
        }
      }
    }
    return 1;
  }
  return 1;
}
varargs mixed *query_dest_other( string direc ) {
  int i;
  string verb, rest, *words, handler;
  object room;
  mixed ret;
  if (!stringp(direc)) {
    return ::query_dest_other(direc);
  }
  words = explode(direc, " ");
  verb = words[0];
  if (verb != motion_verb) {
    ret = ::query_dest_other(direc);
    if (!stringp(ret[ROOM_DEST]) || (ret[ROOM_DEST] == "/") ||
    (ret[ROOM_DEST] == "/terrain") || (ret[ROOM_DEST] == "/topography")) {
      room = (topo_handler)->find_room_at_exit(this_object(), dirs[direc],
                                               direc);
      if (!objectp(room)) {
        return 0;
      }
      ret[ROOM_DEST] = file_name(room);
    }
    return ret;
  }
  if (sizeof(words) < 2) {
    notify_fail(motion_verb + " which way?\n");
    return 0;
  }
  rest = implode(words[1..], " ");
  foreach (handler in keys(milestone_dirs)) {
    i = member_array(rest, milestone_dirs[handler]);
    if (i < 0) {
      continue;
    }
    if (i == 0) {
      room = handler->find_room_at_index(milestone_index[handler] - 1, -2);
    } else {
      room = handler->find_room_at_index(milestone_index[handler], 0);
    }
    if (!objectp(room)) {
      return 0;
    }
    ret = ::query_dest_other(direc);
    if (!sizeof(ret)) {
      return 0;
    }
    ret[ROOM_DEST] = file_name(room);
    return ret;
  }
  return 0;
}
string query_look(string direc) {
  int i, dark;
  string s, direc_s, h;
  mixed dest;
  direc_s = direc;
  foreach (h in keys(milestone_dirs)) {
    i = member_array(direc_s, milestone_dirs[h]);
    if (i >= 0) {
      direc_s = motion_verb + " " + direc_s;
      break;
    }
  }
  if (s = ::query_look(direc_s)) {
    return s;
  }
  if (s = look_mess[direc_s]) {
    return evaluate(s);
  }
  dest = query_dest_other(direc_s);
  if (!dest) {
    return 0;
  }
  dest = dest[ROOM_DEST];
  if (!dest) {
    return 0;
  }
  if (query_door_open(direc_s) != 0) {
    dest->force_load();
    this_player()->set_looked( find_object( dest ) );
    dark = (int)this_player()->check_dark((int)dest->query_light());
    s = (string)dest->long( 0, dark );
    if (s[<1] == '\n') {
      return s[0..<2];
    }
    return s;
  }
  return 0;
}
void add_topo_exits(string *e, string type) {
  other_exits += ({ e });
  other_types += ({ type });
}
void add_topo_exits_int() {
  int i;
  string s;
  for (i = 0; i < sizeof(other_exits); i++) {
    foreach (s in other_exits[i]) {
      if ((s == "compass4") || (s == "compass8")) {
        if (!query_exit("north")) add_exit("north", "/topography",
                                           other_types[i]);
        if (!query_exit("south")) add_exit("south", "/topography",
                                           other_types[i]);
        if (!query_exit("east")) add_exit("east", "/topography",
                                          other_types[i]);
        if (!query_exit("west")) add_exit("west", "/topography",
                                          other_types[i]);
        if (s == "compass8") {
          if (!query_exit("northeast")) add_exit("northeast", "/topography",
                                                 other_types[i]);
          if (!query_exit("northwest")) add_exit("northwest", "/topography",
                                                 other_types[i]);
          if (!query_exit("southeast")) add_exit("southeast", "/topography",
                                                 other_types[i]);
          if (!query_exit("southwest")) add_exit("southwest", "/topography",
                                                 other_types[i]);
        }
      } else {
        add_exit(s, "/topography", other_types[i]);
      }
    }
  }
}