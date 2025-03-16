#include <map.h>
inherit "/std/room";
class IROOM_INFO {
  string base;
  int *size;
  mixed *bbox;
  int sgn_n;
  int sgn_e;
  string *exits;
}
int closed;
nosave int dbg_lvl = 0;
mixed *irooms;
string *milestones;
mixed *milestone_coords;
mapping milestone_idx = ([ ]);
class IROOM_INFO *iroom_info;
mixed *overall_bbox;
string save_file;
nosave string debugger = "jeremy";
mixed *bbox(int *coord_a, int *coord_b);
int in_bbox(int *coord_a, mixed bbox);
void set_debugger(string s) { debugger = s; }
string query_debugger() { return debugger; }
void set_debug_level(int l) { dbg_lvl = l; }
int query_debug_level() { return dbg_lvl; }
mixed query(string s) { return fetch_variable(s); }
int abs(int i) {
  return (i<0)?-i:i;
}
float fabs(float i) {
  return (i<0)?-i:i;
}
void set_save_file(string s) { save_file = s; }
string query_save_file() { return save_file; }
void set_milestones(string *s) {
  int i;
  milestones = copy(s);
  if (milestones[0] == milestones[<1]) {
    closed = 1;
  }
  for (i = 0; i < sizeof(milestones) - closed; i++) {
    milestone_idx[s[i]] = i;
  }
  milestone_coords = allocate(sizeof(milestones));
  irooms = allocate(sizeof(milestones)-1);
  iroom_info = allocate(sizeof(milestones)-1);
  for (i = 0; i < sizeof(iroom_info); i++) {
    iroom_info[i] = new(class IROOM_INFO);
    iroom_info[i]->exits = allocate(2);
  }
  overall_bbox = 0;
}
string *query_milestones() { return milestones; }
string query_milestone(int i) { return milestones[i]; }
void set_milestone_coords(int i, int *c) {
  if (!arrayp(c) || (sizeof(c) != 3)) {
    return;
  }
  if (!arrayp(milestone_coords[i]) || (milestone_coords[i][0] != c[0])
  || (milestone_coords[i][1] != c[1]) || (milestone_coords[i][2] != c[2])) {
    milestone_coords[i] = copy(c);
    if ((i > 0) && arrayp(milestone_coords[i-1])) {
      iroom_info[i-1]->bbox = bbox(milestone_coords[i-1], milestone_coords[i]);
      if (milestone_coords[i-1][0] < milestone_coords[i][0]) {
        iroom_info[i-1]->sgn_n = 1;
      } else if (milestone_coords[i-1][0] > milestone_coords[i][0]) {
        iroom_info[i-1]->sgn_n = -1;
      } else {
        iroom_info[i-1]->sgn_n = 0;
      }
      if (milestone_coords[i-1][1] < milestone_coords[i][1]) {
        iroom_info[i-1]->sgn_e = 1;
      } else if (milestone_coords[i-1][1] > milestone_coords[i][1]) {
        iroom_info[i-1]->sgn_e = -1;
      } else {
        iroom_info[i-1]->sgn_e = 0;
      }
      if (!arrayp(overall_bbox)) {
        overall_bbox = copy(iroom_info[i-1]->bbox);
      } else {
        if (iroom_info[i-1]->bbox[0][0] < overall_bbox[0][0]) {
          overall_bbox[0][0] = iroom_info[i-1]->bbox[0][0];
        }
        if (iroom_info[i-1]->bbox[0][1] < overall_bbox[0][1]) {
          overall_bbox[0][1] = iroom_info[i-1]->bbox[0][1];
        }
        if (iroom_info[i-1]->bbox[1][0] > overall_bbox[1][0]) {
          overall_bbox[1][0] = iroom_info[i-1]->bbox[1][0];
        }
        if (iroom_info[i-1]->bbox[1][1] > overall_bbox[1][1]) {
          overall_bbox[1][1] = iroom_info[i-1]->bbox[1][1];
        }
      }
    }
    if ((i < sizeof(iroom_info)) && arrayp(milestone_coords[i+1])) {
      iroom_info[i]->bbox = bbox(milestone_coords[i], milestone_coords[i+1]);
      if (milestone_coords[i][0] < milestone_coords[i+1][0]) {
        iroom_info[i]->sgn_n = 1;
      } else if (milestone_coords[i][0] > milestone_coords[i+1][0]) {
        iroom_info[i]->sgn_n = -1;
      } else {
        iroom_info[i]->sgn_n = 0;
      }
      if (milestone_coords[i][1] < milestone_coords[i+1][1]) {
        iroom_info[i]->sgn_e = 1;
      } else if (milestone_coords[i][1] > milestone_coords[i+1][1]) {
        iroom_info[i]->sgn_e = -1;
      } else {
        iroom_info[i]->sgn_e = 0;
      }
      if (!arrayp(overall_bbox)) {
        overall_bbox = copy(iroom_info[i]->bbox);
      } else {
        if (iroom_info[i]->bbox[0][0] < overall_bbox[0][0]) {
          overall_bbox[0][0] = iroom_info[i]->bbox[0][0];
        }
        if (iroom_info[i]->bbox[0][1] < overall_bbox[0][1]) {
          overall_bbox[0][1] = iroom_info[i]->bbox[0][1];
        }
        if (iroom_info[i]->bbox[1][0] > overall_bbox[1][0]) {
          overall_bbox[1][0] = iroom_info[i]->bbox[1][0];
        }
        if (iroom_info[i]->bbox[1][1] > overall_bbox[1][1]) {
          overall_bbox[1][1] = iroom_info[i]->bbox[1][1];
        }
      }
    }
  }
}
mixed query_milestone_coords() { return milestone_coords; }
void set_bases(string *s) {
  int i;
  if (sizeof(s) != sizeof(iroom_info)) {
    error("Wrong number of bases (" + sizeof(s) + ") for given milestones (" +
          sizeof(milestones) + ").\n");
    return;
  }
  for (i = 0; i < sizeof(s); i++) {
    iroom_info[i]->base = s[i];
  }
}
void set_sizes(mixed *s) {
  int i;
  if (sizeof(s) != sizeof(iroom_info)) {
    error("Wrong number of sizes (" + sizeof(s) + ") for given milestones (" +
          sizeof(milestones) + ").\n");
    return;
  }
  for (i = 0; i < sizeof(s); i++) {
    iroom_info[i]->size = allocate(3);
    if (intp(s[i])) {
      iroom_info[i]->size[0] = s[i];
      iroom_info[i]->size[1] = s[i];
      iroom_info[i]->size[2] = s[i];
    } else if (arrayp(s[i])) {
      iroom_info[i]->size[0] = s[i][0];
      iroom_info[i]->size[1] = s[i][1];
      iroom_info[i]->size[2] = s[i][2];
    } else {
      error("Illegal room size given (" + i + ").\n");
      continue;
    }
  }
}
class IROOM_INFO *query_iroom_info() { return iroom_info; }
int query_endpoint(int i, int j, int dir) {
  if ((dir && (j == sizeof(irooms[i])-1)) || (!dir && (j == 0))) {
    return 1;
  }
  return 0;
}
object *query_irooms_inv(int i, int j, int dir) {
  int k;
  object *invs;
  invs = ({ });
  if (dir) {
    if (!arrayp(irooms[i])) {
      return invs;
    }
    for (k = j+1; k < sizeof(irooms[i]); k++) {
      if (objectp(irooms[i][k])) {
        invs += all_inventory(irooms[i][k]);
      }
    }
  } else {
    if (j == -1) {
      if (closed) {
        i = sizeof(milestones) - 2;
      } else {
        i--;
      }
      if (!arrayp(irooms[i])) {
        return invs;
      } else {
        j = sizeof(irooms[i]);
      }
    } else if (!arrayp(irooms[i])) {
      return invs;
    }
    for (k = j-1; k >= 0; k--) {
      if (objectp(irooms[i][k])) {
        invs += all_inventory(irooms[i][k]);
      }
    }
  }
  return invs;
}
mixed *bbox(int *coord_a, int *coord_b) {
  int c;
  mixed *bbox;
  bbox = allocate(2);
  bbox[0] = allocate(3);
  bbox[1] = allocate(3);
  for (c = 0; c < 3; c++) {
    if (coord_a[c] < coord_b[c]) {
      bbox[0][c] = coord_a[c];
      bbox[1][c] = coord_b[c];
    } else {
      bbox[0][c] = coord_b[c];
      bbox[1][c] = coord_a[c];
    }
  }
  return bbox;
}
int in_bbox(int *coord_a, mixed bbox) {
  if ((coord_a[0] < bbox[0][0]) || (coord_a[0] > bbox[1][0])
  || (coord_a[1] < bbox[0][1]) || (coord_a[1] > bbox[1][1]))
    return 0;
  return 1;
}
int number_of_irooms(int i) {
  int n;
  mixed bbox;
  class IROOM_INFO ir;
  ir = iroom_info[i];
  bbox = ir->bbox;
  if (ir->sgn_n == 0) {
    n = (bbox[1][1] - bbox[0][1])/(ir->size[1]*2);
  } else if (ir->sgn_e == 0) {
    n = (bbox[1][0] - bbox[0][0])/(ir->size[0]*2);
  } else {
    n = (bbox[1][1] - bbox[0][1])/(ir->size[1]*2);
    if (n != (bbox[1][0] - bbox[0][0])/(ir->size[0]*2)) {
      error("Interroom sizes don't match diagonal.\n");
      return 0;
    }
  }
  return n-1;
}
object clone_iroom(int i, int idx, int *icoord) {
  object iroom;
  iroom = clone_object(iroom_info[i]->base);
  iroom->set_room_size(iroom_info[i]->size);
  iroom->set_co_ord(icoord);
  iroom->set_milestone_index( ({ i, idx }) );
  iroom->add_exit(iroom_info[i]->exits[0], milestones[i], "road");
  iroom->add_exit(iroom_info[i]->exits[1], milestones[i+1], "road");
  iroom->add_milestone_dir(iroom_info[i]->exits[0]);
  iroom->add_milestone_dir(iroom_info[i]->exits[1]);
  iroom->add_topo_exits_int();
  return iroom;
}
void setup_milestone(object ms) {
  int *coord, i, j, idir;
  string *dir;
  if (undefinedp(i = milestone_idx[file_name(ms)])) {
    error("This room (" + file_name(ms) + ") is not a milestone.\n");
    return;
  }
  ms->set_milestone_index(file_name(this_object()), i);
  coord = ms->query_co_ord();
  if (arrayp(coord)) {
    set_milestone_coords(i, coord);
  } else {
    if (arrayp(milestone_coords[i])) {
      coord = milestone_coords[i];
    } else {
      coord = MAP->static_query_co_ord(file_name(ms));
      set_milestone_coords(i, coord);
    }
    ms->set_co_ord(coord);
  }
  if (closed && (i == 0)) {
    milestone_coords[<1] = milestone_coords[0];
  }
  dir = ms->query_dest_dir();
  if ((i > 0) || closed) {
    if (closed && i == 0) {
      j = sizeof(milestones) - 2;
    } else {
      j = i - 1;
    }
    if ((idir = member_array(milestones[j], dir)) < 0) {
      ms->add_milestone_dir(file_name(this_object()), 0);
    } else {
      iroom_info[j]->exits[0] = dir[idir-1];
      ms->add_milestone_dir(file_name(this_object()), dir[idir-1]);
    }
  } else {
    ms->add_milestone_dir(file_name(this_object()), 0);
  }
  if (i < sizeof(irooms)) {
    j = i + 1;
    if ((idir = member_array(milestones[j], dir)) < 0) {
      ms->add_milestone_dir(file_name(this_object()), 0);
    } else {
      iroom_info[i]->exits[1] = dir[idir-1];
      ms->add_milestone_dir(file_name(this_object()), dir[idir-1]);
    }
  }
}
varargs object find_room_at_coord(int *coord_a, int hint_idx) {
  int i, idx, in_bbox;
  int start_i, stop_i;
  int *icoord = ({ 0, 0, 0 });
  mixed bbox;
  float slope;
  class IROOM_INFO ir;
  if (dbg_lvl > 0) {
    tell_creator(debugger, "%s::find_room_at_coord()\n"
                 "  coord_a: %O\n"
                 "  hint_idx: %s\n",
                 file_name(this_object()), coord_a,
                 undefinedp(hint_idx)?"NULL":hint_idx+"");
  }
  if (!in_bbox(coord_a, overall_bbox)) {
    return 0;
  }
  in_bbox = 0;
  if (undefinedp(hint_idx)) {
    start_i = 0;
    stop_i = sizeof(iroom_info);
  } else {
    start_i = hint_idx;
    stop_i = hint_idx + 1;
  }
  for (i = start_i; i < stop_i; i++) {
    ir = iroom_info[i];
    bbox = ir->bbox;
    if (dbg_lvl > 1) {
      tell_creator(debugger, "%s::find_room_at_coord()\n"
                   "  Checking bbox(%d,%d): %O\n",
                   file_name(this_object()), i, i+1, bbox);
    }
    if (in_bbox(coord_a, bbox)) {
      if (dbg_lvl > 1) {
        tell_creator(debugger, "%s::find_room_at_coord()\n"
                     "  In bbox(%d,%d)...\n",
                     file_name(this_object()), i, i+1);
      }
      if (ir->sgn_e == 0) {
        if (abs(coord_a[1]-milestone_coords[i][1]) < ir->size[1]) {
          if (dbg_lvl > 2) {
            tell_creator(debugger, "%s::find_room_at_coord()\n"
                         "  On vline between (%d,%d)...\n",
                         file_name(this_object()), i, i+1);
          }
          break;
        }
      } else {
        slope = to_float(milestone_coords[i][0] - milestone_coords[i+1][0])
          / to_float(milestone_coords[i][1] - milestone_coords[i+1][1]);
        if (abs(slope * (coord_a[1] - milestone_coords[i+1][1]) +
            milestone_coords[i+1][0] - coord_a[0]) < ir->size[0]) {
          if (dbg_lvl > 2) {
            tell_creator(debugger, "%s::find_room_at_coord()\n"
                         "  On line between (%d,%d)...\n",
                         file_name(this_object()), i, i+1);
          }
          break;
        }
      }
    }
  }
  if (i == stop_i) {
    if (dbg_lvl > 2) {
      tell_creator(debugger, "%s::find_room_at_coord()\n"
                   "  Couldn't find a room...\n",
                   file_name(this_object()));
    }
    return 0;
  }
  if (ir->sgn_n == 0) {
    idx = abs(coord_a[1] - milestone_coords[i][1]
              + ir->size[1]*ir->sgn_e)/(ir->size[1]*2);
    icoord[0] = milestone_coords[i][0];
    icoord[1] = milestone_coords[i][1] + idx*ir->sgn_e*ir->size[1]*2;
  } else {
    idx = abs(coord_a[0] - milestone_coords[i][0]
              + ir->size[0]*ir->sgn_n)/(ir->size[0]*2);
    icoord[0] = milestone_coords[i][0] + idx*ir->sgn_n*ir->size[0]*2;
    if (ir->sgn_e == 0) {
      icoord[1] = milestone_coords[i][1];
    } else {
      icoord[1] = milestone_coords[i][1] + idx*ir->sgn_e*ir->size[1]*2;
    }
  }
  if (dbg_lvl > 2) {
    tell_creator(debugger, "%s::find_room_at_coord()\n"
                 "  idx: %O\n",
                 file_name(this_object()), idx);
  }
  if (idx == 0) {
    return load_object(milestones[i]);
  }
  if (!arrayp(irooms[i])) {
    irooms[i] = allocate(number_of_irooms(i));
  }
  if (idx == sizeof(irooms[i])+1) {
    return load_object(milestones[i+1]);
  }
  idx--;
  if (!objectp(irooms[i][idx])) {
    icoord[2] = (milestone_coords[i+1][2] - milestone_coords[i][2])
      * idx / sizeof(irooms[i]) + milestone_coords[i][2];
    irooms[i][idx] = clone_iroom(i, idx, icoord);
  }
  return irooms[i][idx];
}
object find_room_at_index(int i, int idx) {
  int *icoord = ({ 0, 0, 0 });
  class IROOM_INFO ir;
  if (dbg_lvl > 0) {
    tell_creator(debugger, "%s::find_room_at_index()\n"
                 "  i: %O, idx: %O\n",
                 file_name(this_object()), i, idx);
  }
  if (closed && (i == -1)) {
    i = sizeof(milestones) - 2;
  }
  if ((i < 0) || (i >= sizeof(irooms))) {
    return 0;
  }
  if (idx == -1) {
    return load_object(milestones[i]);
  }
  if (!arrayp(irooms[i])) {
    irooms[i] = allocate(number_of_irooms(i));
  }
  if (idx == sizeof(irooms[i])) {
    return load_object(milestones[i+1]);
  }
  if (idx == -2) {
    idx = sizeof(irooms[i]) - 1;
  }
  if ((idx < 0) || (idx >= sizeof(irooms[i]))) {
    return 0;
  }
  if (!objectp(irooms[i][idx])) {
    ir = iroom_info[i];
    if (ir->sgn_n == 0) {
      icoord[0] = milestone_coords[i][0];
      icoord[1] = milestone_coords[i][1] + (idx+1)*ir->sgn_e*ir->size[1]*2;
    } else {
      icoord[0] = milestone_coords[i][0] + (idx+1)*ir->sgn_n*ir->size[0]*2;
      if (ir->sgn_e == 0) {
        icoord[1] = milestone_coords[i][1];
      } else {
        icoord[1] = milestone_coords[i][1] + (idx+1)*ir->sgn_e*ir->size[1]*2;
      }
    }
    icoord[2] = (milestone_coords[i+1][2] - milestone_coords[i][2])
      * idx / sizeof(irooms[i]) + milestone_coords[i][2];
    irooms[i][idx] = clone_iroom(i, idx, icoord);
  }
  return irooms[i][idx];
}
int query_region(int *coord, mixed bbox) {
  int ret;
  if (coord[0] < bbox[0][0]) {
    ret += 1;
  } else if (coord[0] > bbox[1][0]) {
    ret += 2;
  }
  if (coord[1] < bbox[0][1]) {
    ret += 4;
  } else if (coord[1] > bbox[1][1]) {
    ret += 8;
  }
  return ret;
}
object find_room_at_crossing(int *coord_a, int *coord_b) {
  int i, a, b, c, d, dist2, ret_dist2;
  float e, f, det;
  int *isect;
  object ret;
  mixed bbox, road_a, road_b;
  if (dbg_lvl > 0) {
    tell_creator(debugger, "%s::find_room_at_crossing()\n"
                 "  coord_a: %O\n"
                 "  coord_b: %O\n",
                 file_name(this_object()), coord_a, coord_b);
  }
  if (query_region(coord_a, overall_bbox)
      & query_region(coord_b, overall_bbox)) {
    return 0;
  }
  for (i = 0; i < sizeof(iroom_info); i++) {
    bbox = iroom_info[i]->bbox;
    if (query_region(coord_a, iroom_info[i]->bbox)
        & query_region(coord_b, iroom_info[i]->bbox)) {
      continue;
    }
    road_a = allocate(3);
    road_b = allocate(3);
    if (iroom_info[i]->sgn_n > 0) {
      road_a[0] = bbox[0][0];
      road_b[0] = bbox[1][0];
    } else {
      road_a[0] = bbox[1][0];
      road_b[0] = bbox[0][0];
    }
    if (iroom_info[i]->sgn_e > 0) {
      road_a[1] = bbox[0][1];
      road_b[1] = bbox[1][1];
    } else {
      road_a[1] = bbox[1][1];
      road_b[1] = bbox[0][1];
    }
    a = coord_b[0] - coord_a[0];
    b = coord_a[1] - coord_b[1];
    c = road_b[0] - road_a[0];
    d = road_a[1] - road_b[1];
    e = to_float(a)*coord_a[1] + to_float(b)*coord_a[0];
    f = to_float(c)*road_a[1] + to_float(d)*road_a[0];
    det = a*d - b*c;
    if (fabs(det) < 0.0000000000001) {
      continue;
    }
    isect = allocate(3);
    isect[0] = to_int(floor((a*f - e*c)/det + 0.5));
    isect[1] = to_int(floor((e*d - b*f)/det + 0.5));
    if (!in_bbox(isect, bbox) || !in_bbox(isect, bbox(coord_a, coord_b))) {
      continue;
    }
    dist2 = (isect[0]-coord_a[0])*(isect[0]-coord_a[0]) +
      (isect[1]-coord_a[1])*(isect[1]-coord_a[1]);
    if (objectp(ret) && (dist2 >= ret_dist2)) {
      continue;
    }
    ret = find_room_at_coord(isect, i);
    if (dbg_lvl > 0) {
      tell_creator(debugger, "%s::find_room_at_crossing()\n"
                   "  find_room_at_coord() returned %O\n",
                   file_name(this_object()), ret);
    }
    ret_dist2 = dist2;
    if (!objectp(ret)) {
      error("Couldn't find a room where there should be one!\n");
    }
  }
  return ret;
}
void create() {
  string std_euid;
  std_euid = "/secure/master"->creator_file(file_name(this_object()));
  seteuid(std_euid);
  do_setup++;
  ::create();
  do_setup--;
  if ( !do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
  set_keep_room_loaded(1);
}
void dest_me() {
  if (stringp(save_file)) {
    unguarded( (: save_object, save_file :) );
  }
  ::dest_me();
}
int goto_room_at_coord(int *coord) {
  return this_player()->move_with_look(find_room_at_coord(coord));
}
int goto_room_at_index(int i, int j) {
  return this_player()->move_with_look(find_room_at_index(i, j));
}
int goto_room_at_crossing(int *a, int *b) {
  return this_player()->move_with_look(find_room_at_crossing(a, b));
}
void recalc_milestones(int idx, int callouts, object tp) {
  int *c;
  string ms;
  if (callouts > 10) {
    error(sprintf("Too many callouts in %s:recalc_iroom_info(%d, %d)\n",
          file_name(this_object()), idx, callouts));
    return;
  }
  if (!idx && !callouts && !tp) {
    rm(save_file);
    this_object()->setup();
    idx = 0;
    tp = this_player();
  }
  ms = milestones[idx];
  if (!arrayp(c = ms->query_co_ord())) {
    call_out("recalc_milestones", 0, idx, callouts+1, tp);
    tell_object(tp, sprintf("Waiting on %s (%d, %d)...\n",
                          ms, idx, callouts));
    return;
  }
  ms->setup_milestone(ms);
  tell_object(tp, sprintf("Loaded room %s at (%d, %d, %d)...\n",
                          ms, c[0], c[1], c[2]));
  idx++;
  if (idx < sizeof(milestones)) {
    call_out("recalc_milestones", 0, idx, 0, tp);
    return;
  }
  tell_object(tp, "IRoom info successfully recalculated.\n");
}
void clear_map_handler() {
  int i;
  string ms, directory, troom;
  for (i = 0; i < sizeof(milestones); i++) {
    ms = milestones[i];
    directory = implode( explode( ms, "/" )[ 0..<2 ], "/" );
    troom = explode( ms, "/" )[ <1 ];
    if ( troom[ <2.. ] == ".c" ) {
      troom = troom[ 0..<3];
    }
    MAP->del(directory, troom);
    printf("Deleting %s in %s from map handler.\n", directory, troom);
  }
}
int sanity_checks() {
  int i, success = 1;
  for (i = 0; i < sizeof(milestone_coords); i++) {
    if (sizeof(milestone_coords[i]) != 3) {
      printf("Milestone %d (%s) doesn't have proper coordinates: %O\n",
             i, milestones[i], milestone_coords[i]);
      success = 0;
    }
  }
  for (i = 0; i < sizeof(iroom_info); i++) {
    if (sizeof(iroom_info[i]->size) != 3) {
      printf("Interroom segment %d has improper size: %O\n",
             i, iroom_info[i]->size);
      success = 0;
    }
    if ((sizeof(iroom_info[i]->bbox) != 2) ||
        (sizeof(iroom_info[i]->bbox[0]) != 3) ||
        (sizeof(iroom_info[i]->bbox[1]) != 3)) {
      printf("Interroom segment %d has improper bounding box: %O\n",
             i, iroom_info[i]->bbox);
      success = 0;
    }
  }
  return success;
}